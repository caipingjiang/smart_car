/*
 *  TAP-Win32 -- A kernel driver to provide virtual tap device functionality
 *               on Windows.  Originally derived from the CIPE-Win32
 *               project by Damion K. Wilson, with extensive modifications by
 *               James Yonan.
 *
 *  All source code which derives from the CIPE-Win32 project is
 *  Copyright (C) Damion K. Wilson, 2003, and is released under the
 *  GPL version 2 (see below).
 *
 *  All other source code is Copyright (C) James Yonan, 2003-2004,
 *  and is released under the GPL version 2 (see below).
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program (see the file COPYING included with this
 *  distribution); if not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <windows.h>
#include <winioctl.h>
#include <rtthread.h>
#include <netif/ethernetif.h>

#define MAX_ADDR_LEN 6
#define TAP_IFNAME	"RT-net"

//=============
// TAP IOCTLs
//=============

#define TAP_CONTROL_CODE(request,method) \
  CTL_CODE (FILE_DEVICE_UNKNOWN, request, method, FILE_ANY_ACCESS)

#define TAP_IOCTL_GET_MAC               TAP_CONTROL_CODE (1, METHOD_BUFFERED)
#define TAP_IOCTL_GET_VERSION           TAP_CONTROL_CODE (2, METHOD_BUFFERED)
#define TAP_IOCTL_GET_MTU               TAP_CONTROL_CODE (3, METHOD_BUFFERED)
#define TAP_IOCTL_GET_INFO              TAP_CONTROL_CODE (4, METHOD_BUFFERED)
#define TAP_IOCTL_CONFIG_POINT_TO_POINT TAP_CONTROL_CODE (5, METHOD_BUFFERED)
#define TAP_IOCTL_SET_MEDIA_STATUS      TAP_CONTROL_CODE (6, METHOD_BUFFERED)
#define TAP_IOCTL_CONFIG_DHCP_MASQ      TAP_CONTROL_CODE (7, METHOD_BUFFERED)
#define TAP_IOCTL_GET_LOG_LINE          TAP_CONTROL_CODE (8, METHOD_BUFFERED)
#define TAP_IOCTL_CONFIG_DHCP_SET_OPT   TAP_CONTROL_CODE (9, METHOD_BUFFERED)

//=================
// Registry keys
//=================

#define ADAPTER_KEY "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E972-E325-11CE-BFC1-08002BE10318}"

#define NETWORK_CONNECTIONS_KEY "SYSTEM\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}"

//======================
// Filesystem prefixes
//======================

#define USERMODEDEVICEDIR "\\\\.\\Global\\"
#define TAPSUFFIX         ".tap"

//======================
// Compile time configuration
//======================

//#define DEBUG_TAP_WIN32

#define TUN_ASYNCHRONOUS_WRITES 1

#define TUN_BUFFER_SIZE 1560
#define TUN_MAX_BUFFER_COUNT 32

/*
 * The data member "buffer" must be the first element in the tun_buffer
 * structure. See the function, tap_win32_free_buffer.
 */
typedef struct tun_buffer_s {
    unsigned char buffer [TUN_BUFFER_SIZE];
    unsigned long read_size;
    struct tun_buffer_s* next;
} tun_buffer_t;

typedef struct tap_win32_overlapped {
    HANDLE handle;
    HANDLE read_event;
    HANDLE write_event;
    HANDLE output_queue_semaphore;
    HANDLE free_list_semaphore;
    HANDLE tap_semaphore;
    CRITICAL_SECTION output_queue_cs;
    CRITICAL_SECTION free_list_cs;
    OVERLAPPED read_overlapped;
    OVERLAPPED write_overlapped;
    tun_buffer_t buffers[TUN_MAX_BUFFER_COUNT];
    tun_buffer_t* free_list;
    tun_buffer_t* output_queue_front;
    tun_buffer_t* output_queue_back;
} tap_win32_overlapped_t;

static tap_win32_overlapped_t tap_overlapped;

/************************************************************************/
/* RT-Thread Network Interface                                          */
/************************************************************************/
struct tap_netif
{
	/* inherit from ethernet device */
	struct eth_device parent;

	tap_win32_overlapped_t *handle;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];		/* hw address	*/
};
#define NETIF_DEVICE(netif) ((struct tap_netif*)(netif))
#define NETIF_TAP(netif)   (NETIF_DEVICE(netif)->handle)

static struct tap_netif tap_netif_device;
static struct rt_semaphore sem_lock;

static tun_buffer_t* get_buffer_from_free_list(tap_win32_overlapped_t* const overlapped)
{
    tun_buffer_t* buffer = NULL;
    WaitForSingleObject(overlapped->free_list_semaphore, INFINITE);
    EnterCriticalSection(&overlapped->free_list_cs);
    buffer = overlapped->free_list;
    overlapped->free_list = buffer->next;
    LeaveCriticalSection(&overlapped->free_list_cs);
    buffer->next = NULL;
    return buffer;
}

static void put_buffer_on_free_list(tap_win32_overlapped_t* const overlapped, tun_buffer_t* const buffer)
{
    EnterCriticalSection(&overlapped->free_list_cs);
    buffer->next = overlapped->free_list;
    overlapped->free_list = buffer;
    LeaveCriticalSection(&overlapped->free_list_cs);
    ReleaseSemaphore(overlapped->free_list_semaphore, 1, NULL);
}

static tun_buffer_t* get_buffer_from_output_queue(tap_win32_overlapped_t* const overlapped, const int block)
{
    tun_buffer_t* buffer = NULL;
    DWORD result, timeout = block ? INFINITE : 0L;

    // Non-blocking call
    result = WaitForSingleObject(overlapped->output_queue_semaphore, timeout);

    switch (result)
    {
        // The semaphore object was signaled.
        case WAIT_OBJECT_0:
            EnterCriticalSection(&overlapped->output_queue_cs);

            buffer = overlapped->output_queue_front;
            overlapped->output_queue_front = buffer->next;

            if(overlapped->output_queue_front == NULL) {
                overlapped->output_queue_back = NULL;
            }

            LeaveCriticalSection(&overlapped->output_queue_cs);
            break;

        // Semaphore was nonsignaled, so a time-out occurred.
        case WAIT_TIMEOUT:
            // Cannot open another window.
            break;
    }

    return buffer;
}

static tun_buffer_t* get_buffer_from_output_queue_immediate (tap_win32_overlapped_t* const overlapped)
{
    return get_buffer_from_output_queue(overlapped, 0);
}

static void put_buffer_on_output_queue(tap_win32_overlapped_t* const overlapped, tun_buffer_t* const buffer)
{
    EnterCriticalSection(&overlapped->output_queue_cs);

    if(overlapped->output_queue_front == NULL && overlapped->output_queue_back == NULL) {
        overlapped->output_queue_front = overlapped->output_queue_back = buffer;
    } else {
        buffer->next = NULL;
        overlapped->output_queue_back->next = buffer;
        overlapped->output_queue_back = buffer;
    }

    LeaveCriticalSection(&overlapped->output_queue_cs);

    ReleaseSemaphore(overlapped->output_queue_semaphore, 1, NULL);
}


static int is_tap_win32_dev(const char *guid)
{
    HKEY netcard_key;
    LONG status;
    DWORD len;
    int i = 0;

    status = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        ADAPTER_KEY,
        0,
        KEY_READ,
        &netcard_key);

    if (status != ERROR_SUCCESS) {
        return FALSE;
    }

    for (;;) {
        char enum_name[256];
        char unit_string[256];
        HKEY unit_key;
        char component_id_string[] = "ComponentId";
        char component_id[256];
        char net_cfg_instance_id_string[] = "NetCfgInstanceId";
        char net_cfg_instance_id[256];
        DWORD data_type;

        len = sizeof (enum_name);
        status = RegEnumKeyEx(
            netcard_key,
            i,
            enum_name,
            &len,
            NULL,
            NULL,
            NULL,
            NULL);

        if (status == ERROR_NO_MORE_ITEMS)
            break;
        else if (status != ERROR_SUCCESS) {
            return FALSE;
        }

        rt_snprintf (unit_string, sizeof(unit_string), "%s\\%s",
                  ADAPTER_KEY, enum_name);

        status = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            unit_string,
            0,
            KEY_READ,
            &unit_key);

        if (status != ERROR_SUCCESS) {
            return FALSE;
        } else {
            len = sizeof (component_id);
            status = RegQueryValueEx(
                unit_key,
                component_id_string,
                NULL,
                &data_type,
                (LPBYTE)component_id,
                &len);

            if (!(status != ERROR_SUCCESS || data_type != REG_SZ)) {
                len = sizeof (net_cfg_instance_id);
                status = RegQueryValueEx(
                    unit_key,
                    net_cfg_instance_id_string,
                    NULL,
                    &data_type,
                    (LPBYTE)net_cfg_instance_id,
                    &len);

                if (status == ERROR_SUCCESS && data_type == REG_SZ) {
                    if (/* !strcmp (component_id, TAP_COMPONENT_ID) &&*/
                        !strcmp (net_cfg_instance_id, guid)) {
                        RegCloseKey (unit_key);
                        RegCloseKey (netcard_key);
                        return TRUE;
                    }
                }
            }
            RegCloseKey (unit_key);
        }
        ++i;
    }

    RegCloseKey (netcard_key);
    return FALSE;
}

static int get_device_guid(
    char *name,
    int name_size,
    char *actual_name,
    int actual_name_size)
{
    LONG status;
    HKEY control_net_key;
    DWORD len;
    int i = 0;
    int stop = 0;

    status = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        NETWORK_CONNECTIONS_KEY,
        0,
        KEY_READ,
        &control_net_key);

    if (status != ERROR_SUCCESS) {
        return -1;
    }

    while (!stop)
    {
        char enum_name[256];
        char connection_string[256];
        HKEY connection_key;
        char name_data[256];
        DWORD name_type;
        const char name_string[] = "Name";

        len = sizeof (enum_name);
        status = RegEnumKeyEx(
            control_net_key,
            i,
            enum_name,
            &len,
            NULL,
            NULL,
            NULL,
            NULL);

        if (status == ERROR_NO_MORE_ITEMS)
            break;
        else if (status != ERROR_SUCCESS) {
            return -1;
        }

        rt_snprintf(connection_string,
             sizeof(connection_string),
             "%s\\%s\\Connection",
             NETWORK_CONNECTIONS_KEY, enum_name);

        status = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            connection_string,
            0,
            KEY_READ,
            &connection_key);

        if (status == ERROR_SUCCESS) {
            len = sizeof (name_data);
            status = RegQueryValueEx(
                connection_key,
                name_string,
                NULL,
                &name_type,
                (LPBYTE)name_data,
                &len);

            if (status != ERROR_SUCCESS || name_type != REG_SZ) {
                    return -1;
            }
            else {
                if (is_tap_win32_dev(enum_name)) {
                    rt_snprintf(name, name_size, "%s", enum_name);
                    if (actual_name) {
                        if (strcmp(actual_name, "") != 0) {
                            if (strcmp(name_data, actual_name) != 0) {
                                RegCloseKey (connection_key);
                                ++i;
                                continue;
                            }
                        }
                        else {
                            rt_snprintf(actual_name, actual_name_size, "%s", name_data);
                        }
                    }
                    stop = 1;
                }
            }

            RegCloseKey (connection_key);
        }
        ++i;
    }

    RegCloseKey (control_net_key);

    if (stop == 0)
        return -1;

    return 0;
}

static int tap_win32_set_status(HANDLE handle, int status)
{
    unsigned long len = 0;

    return DeviceIoControl(handle, TAP_IOCTL_SET_MEDIA_STATUS,
                &status, sizeof (status),
                &status, sizeof (status), &len, NULL);
}

static void tap_win32_overlapped_init(tap_win32_overlapped_t* const overlapped, const HANDLE handle)
{
    overlapped->handle = handle;

    overlapped->read_event = CreateEvent(NULL, FALSE, FALSE, NULL);
    overlapped->write_event = CreateEvent(NULL, FALSE, FALSE, NULL);

    overlapped->read_overlapped.Offset = 0;
    overlapped->read_overlapped.OffsetHigh = 0;
    overlapped->read_overlapped.hEvent = overlapped->read_event;

    overlapped->write_overlapped.Offset = 0;
    overlapped->write_overlapped.OffsetHigh = 0;
    overlapped->write_overlapped.hEvent = overlapped->write_event;

    InitializeCriticalSection(&overlapped->output_queue_cs);
    InitializeCriticalSection(&overlapped->free_list_cs);

    overlapped->output_queue_semaphore = CreateSemaphore(
        NULL,   // default security attributes
        0,   // initial count
        TUN_MAX_BUFFER_COUNT,   // maximum count
        NULL);  // unnamed semaphore

    if(!overlapped->output_queue_semaphore)  {
        fprintf(stderr, "error creating output queue semaphore!\n");
    }

    overlapped->free_list_semaphore = CreateSemaphore(
        NULL,   // default security attributes
        TUN_MAX_BUFFER_COUNT,   // initial count
        TUN_MAX_BUFFER_COUNT,   // maximum count
        NULL);  // unnamed semaphore

    if(!overlapped->free_list_semaphore)  {
        fprintf(stderr, "error creating free list semaphore!\n");
    }

    overlapped->free_list = overlapped->output_queue_front = overlapped->output_queue_back = NULL;

    {
        unsigned index;
        for(index = 0; index < TUN_MAX_BUFFER_COUNT; index++) {
            tun_buffer_t* element = &overlapped->buffers[index];
            element->next = overlapped->free_list;
            overlapped->free_list = element;
        }
    }
    /* To count buffers, initially no-signal. */
    overlapped->tap_semaphore = CreateSemaphore(NULL, 0, TUN_MAX_BUFFER_COUNT, NULL);
    if(!overlapped->tap_semaphore)
        fprintf(stderr, "error creating tap_semaphore.\n");
}

static int tap_win32_write(tap_win32_overlapped_t *overlapped,
                           const void *buffer, unsigned long size)
{
    unsigned long write_size;
    BOOL result;
    DWORD error;

    result = GetOverlappedResult( overlapped->handle, &overlapped->write_overlapped,
                                  &write_size, FALSE);

    if (!result && GetLastError() == ERROR_IO_INCOMPLETE)
        WaitForSingleObject(overlapped->write_event, INFINITE);

    result = WriteFile(overlapped->handle, buffer, size,
                       &write_size, &overlapped->write_overlapped);

    if (!result) {
        switch (error = GetLastError())
        {
        case ERROR_IO_PENDING:
#ifndef TUN_ASYNCHRONOUS_WRITES
            WaitForSingleObject(overlapped->write_event, INFINITE);
#endif
            break;
        default:
            return -1;
        }
    }

    return write_size;
}

static void tap_win32_thread_entry(void* param)
{
    tap_win32_overlapped_t *overlapped;
    unsigned long read_size;
    BOOL result;
    DWORD dwError;
	tun_buffer_t* buffer;
	struct eth_device* eth;

	eth = (struct eth_device*) &tap_netif_device;
	overlapped = NETIF_TAP(&tap_netif_device);
	buffer = get_buffer_from_free_list(overlapped);

    for (;;) {
        result = ReadFile(overlapped->handle,
                          buffer->buffer,
                          sizeof(buffer->buffer),
                          &read_size,
                          &overlapped->read_overlapped);
        if (!result) {
            dwError = GetLastError();
            if (dwError == ERROR_IO_PENDING) {
                WaitForSingleObject(overlapped->read_event, INFINITE);
                result = GetOverlappedResult( overlapped->handle, &overlapped->read_overlapped,
                                              &read_size, FALSE);
                if (!result) {
#ifdef DEBUG_TAP_WIN32
                    LPVOID lpBuffer;
                    dwError = GetLastError();
                    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                   NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                   (LPTSTR) & lpBuffer, 0, NULL );
                    fprintf(stderr, "Tap-Win32: Error GetOverlappedResult %d - %s\n", dwError, lpBuffer);
                    LocalFree( lpBuffer );
#endif
                }
            } else {
#ifdef DEBUG_TAP_WIN32
                LPVOID lpBuffer;
                FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                               NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                               (LPTSTR) & lpBuffer, 0, NULL );
                fprintf(stderr, "Tap-Win32: Error ReadFile %d - %s\n", dwError, lpBuffer);
                LocalFree( lpBuffer );
#endif
            }
        }

        if(read_size > 0) {
			// rt_kprintf("rx packet, length=%d\n", read_size);

			buffer->read_size = read_size;
            put_buffer_on_output_queue(overlapped, buffer);

			/* notify eth rx thread to receive packet */
			eth_device_ready(eth);

			buffer = get_buffer_from_free_list(overlapped);
        }
    }
}

static int tap_win32_read(tap_win32_overlapped_t *overlapped,
                          rt_uint8_t **pbuf, int max_size)
{
    int size = 0;

    tun_buffer_t* buffer = get_buffer_from_output_queue_immediate(overlapped);

    if(buffer != NULL) {
        *pbuf = buffer->buffer;
        size = (int)buffer->read_size;
        if(size > max_size) {
            size = max_size;
        }
    }

    return size;
}

static void tap_win32_free_buffer(tap_win32_overlapped_t *overlapped,
                                  rt_uint8_t *pbuf)
{
    tun_buffer_t* buffer = (tun_buffer_t*)pbuf;
    put_buffer_on_free_list(overlapped, buffer);
}

static int tap_win32_open(tap_win32_overlapped_t **phandle,
                          const char *preferred_name)
{
    char device_path[256];
    char device_guid[0x100];
    int rc;
    HANDLE handle;
    BOOL bret;
    char name_buffer[0x100] = {0, };
    struct {
        unsigned long major;
        unsigned long minor;
        unsigned long debug;
    } version;
    DWORD version_len;

    if (preferred_name != NULL) {
        rt_snprintf(name_buffer, sizeof(name_buffer), "%s", preferred_name);
    }

    rc = get_device_guid(device_guid, sizeof(device_guid), name_buffer, sizeof(name_buffer));
    if (rc)
        return -1;

    rt_snprintf (device_path, sizeof(device_path), "%s%s%s",
              USERMODEDEVICEDIR,
              device_guid,
              TAPSUFFIX);

    handle = CreateFile (
        device_path,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_OVERLAPPED,
        0 );

    if (handle == INVALID_HANDLE_VALUE) {
        return -1;
    }

    bret = DeviceIoControl(handle, TAP_IOCTL_GET_VERSION,
                           &version, sizeof (version),
                           &version, sizeof (version), &version_len, NULL);

    if (bret == FALSE) {
        CloseHandle(handle);
        return -1;
    }

    if (!tap_win32_set_status(handle, TRUE)) {
        return -1;
    }

    tap_win32_overlapped_init(&tap_overlapped, handle);

    *phandle = &tap_overlapped;
    return 0;
}

static rt_err_t tap_netif_init(rt_device_t dev)
{
	rt_thread_t tid;
	tap_win32_overlapped_t *handle;

	if (tap_win32_open(&handle, TAP_IFNAME) < 0) {
		printf("tap: Could not open '%s'\n", TAP_IFNAME);
		return -RT_ERROR;
	}

	tap_netif_device.handle = handle;

	/* create recv thread */
	tid = rt_thread_create("tap", tap_win32_thread_entry, RT_NULL, 
		2048, RT_THREAD_PRIORITY_MAX - 1, 10);
	if (tid != RT_NULL)
	{
		rt_thread_startup(tid);
	}

	rt_thread_sleep(RT_TICK_PER_SECOND);

	return RT_EOK;
}

static rt_err_t tap_netif_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t tap_netif_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t tap_netif_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t tap_netif_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t tap_netif_control(rt_device_t dev, int cmd, void *args)
{
	switch (cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if (args) rt_memcpy(args, tap_netif_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

rt_err_t tap_netif_tx( rt_device_t dev, struct pbuf* p)
{
	struct pbuf *q;
	char buffer[2048];
	int length;
	tap_win32_overlapped_t *handle;
	unsigned char* ptr;

	handle = NETIF_TAP(dev);

	/* lock EMAC device */
	rt_sem_take(&sem_lock, RT_WAITING_FOREVER);

	/* copy data to tx buffer */
	q = p;
	ptr = (rt_uint8_t*)buffer;
	while (q)
	{
		memcpy(ptr, q->payload, q->len);
		ptr += q->len;
		q = q->next;
	}
	length = p->tot_len;

	tap_win32_write(handle, buffer, length);

	/* unlock EMAC device */
	rt_sem_release(&sem_lock);

	return RT_EOK;
}

struct pbuf *tap_netif_rx(rt_device_t dev)
{
	struct pbuf* p = RT_NULL;
	tap_win32_overlapped_t *handle;
	rt_uint8_t *buf;
	int max_size = 4096;
	int size;

	handle = NETIF_TAP(dev);

	size = tap_win32_read(handle, &buf, max_size);
	if (size > 0) {
		p = pbuf_alloc(PBUF_LINK, size, PBUF_RAM);
		pbuf_take(p, buf, size);

		tap_win32_free_buffer(handle, buf);
	}

	return p;
}

void tap_netif_hw_init(void)
{
	rt_sem_init(&sem_lock, "eth_lock", 1, RT_IPC_FLAG_FIFO);

	tap_netif_device.dev_addr[0] = 0x00;
	tap_netif_device.dev_addr[1] = 0x60;
	tap_netif_device.dev_addr[2] = 0x37;
	/* set mac address: (only for test) */
	tap_netif_device.dev_addr[3] = 0x12;
	tap_netif_device.dev_addr[4] = 0x34;
	tap_netif_device.dev_addr[5] = 0x56;

	tap_netif_device.parent.parent.init		= tap_netif_init;
	tap_netif_device.parent.parent.open		= tap_netif_open;
	tap_netif_device.parent.parent.close	= tap_netif_close;
	tap_netif_device.parent.parent.read		= tap_netif_read;
	tap_netif_device.parent.parent.write	= tap_netif_write;
	tap_netif_device.parent.parent.control	= tap_netif_control;
	tap_netif_device.parent.parent.user_data= RT_NULL;

	tap_netif_device.parent.eth_rx			= tap_netif_rx;
	tap_netif_device.parent.eth_tx			= tap_netif_tx;

	eth_device_init(&(tap_netif_device.parent), "e0");
}
