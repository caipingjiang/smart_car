/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          seekfree_assistant_interface
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����             ����             ��ע
* 2024-1-11        SeekFree         first version
********************************************************************************************************************/

#include "zf_common_typedef.h"
#include "zf_common_fifo.h"
#include "zf_common_debug.h"
#include "zf_driver_uart.h"
#include "zf_common_fifo.h"
#include "zf_common_debug.h"
#include "zf_driver_uart.h"
#include "zf_device_wireless_uart.h"
#include "zf_device_bluetooth_ch9141.h"
#include "zf_device_wifi_uart.h"
#include "zf_device_wifi_spi.h"
#include "seekfree_assistant.h"

#include "seekfree_assistant_interface.h"


extern seekfree_assistant_transfer_callback_function   seekfree_assistant_transfer_callback;    // ���ݷ��ͺ���ָ��
extern seekfree_assistant_receive_callback_function    seekfree_assistant_receive_callback;     // ���ݽ��պ���ָ��


//-------------------------------------------------------------------------------------------------------------------
// �������     ������ַ��ͺ���
// ����˵��     *buff           ��Ҫ���͵����ݵ�ַ
// ����˵��     length          ��Ҫ���͵ĳ���
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
ZF_WEAK uint32 seekfree_assistant_transfer (const uint8 *buff, uint32 length)
{
    
    // ��ѡ���Զ���ͨѶ��ʽʱ ��Ҫ����������ݷ��͹���
    return length;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ֽ������ݺ���
// ����˵��     *buff           ��Ҫ���յ����ݵ�ַ
// ����˵��     length          Ҫ���յ�������󳤶�
// ���ز���     uint32          ���յ������ݳ���
// ʹ��ʾ��
//-------------------------------------------------------------------------------------------------------------------
ZF_WEAK uint32 seekfree_assistant_receive (uint8 *buff, uint32 length)
{
    // ��ѡ���Զ���ͨѶ��ʽʱ ��Ҫ����������ݽ��չ���
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ֽӿ� ��ʼ��
// ����˵��
// ���ز���     void
// ʹ��ʾ��     seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI); ʹ�ø���WIFI SPIģ����������շ�
// ��ע         ��Ҫ���е����豸�ĳ�ʼ��������ʹ������ת���ڽ������ݵ��շ�������Ҫ���е�������ת���ڵĳ�ʼ����Ȼ���ٵ���seekfree_assistant_interface_init���������ֵĽӿڳ�ʼ��
//-------------------------------------------------------------------------------------------------------------------
ZF_WEAK void seekfree_assistant_interface_init (seekfree_assistant_transfer_device_enum transfer_device)
{
    switch(transfer_device)
    {
        case SEEKFREE_ASSISTANT_DEBUG_UART:
        {
            seekfree_assistant_transfer_callback = debug_send_buffer;
            seekfree_assistant_receive_callback = debug_read_ring_buffer;
        }break;
        
        case SEEKFREE_ASSISTANT_WIRELESS_UART:
        {
            seekfree_assistant_transfer_callback = wireless_uart_send_buffer;
            seekfree_assistant_receive_callback = wireless_uart_read_buffer;
        }break;
        
        case SEEKFREE_ASSISTANT_CH9141:
        {
            seekfree_assistant_transfer_callback = bluetooth_ch9141_send_buffer;
            seekfree_assistant_receive_callback = bluetooth_ch9141_read_buffer;
        }break;
        
        case SEEKFREE_ASSISTANT_WIFI_UART:
        {
            seekfree_assistant_transfer_callback = wifi_uart_send_buffer;
            seekfree_assistant_receive_callback = wifi_uart_read_buffer;
        }break;
        
        case SEEKFREE_ASSISTANT_WIFI_SPI:
        {
            seekfree_assistant_transfer_callback = wifi_spi_send_buffer;
            seekfree_assistant_receive_callback = wifi_spi_read_buffer;
        }break;
        
        case SEEKFREE_ASSISTANT_CUSTOM:
        {         
            // �����Լ������� ����ʵ��seekfree_assistant_transfer��seekfree_assistant_receive������������ݵ��շ�
            
        }break;
    }
}


