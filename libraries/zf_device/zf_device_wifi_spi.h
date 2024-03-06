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
* �ļ�����          zf_device_wifi_spi
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   RST                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_RST_PIN �궨��
*                   INT                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_INT_PIN �궨��
*                   CS                  �鿴 zf_device_wifi_spi.h �� WIFI_SPI_CS_PIN �궨��
*                   MISO                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MISO_PIN �궨��
*                   SCK                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_SCK_PIN �궨��
*                   MOSI                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MOSI_PIN �궨��
*                   5V                  5V ��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/

#ifndef _zf_device_wifi_spi_h
#define _zf_device_wifi_spi_h

#include "zf_common_typedef.h"

#define WIFI_SPI_INDEX              (SPI_1)                     // ����ʹ�õ�SPI��
#define WIFI_SPI_SPEED              (20 * 1000 * 1000)          // Ӳ�� SPI ����
#define WIFI_SPI_SCK_PIN            (SPI1_SCK_D12)              // ����SPI_SCK����
#define WIFI_SPI_MOSI_PIN           (SPI1_MOSI_D14)             // ����SPI_MOSI����
#define WIFI_SPI_MISO_PIN           (SPI1_MISO_D15)             // ����SPI_MISO����  IPSû��MISO���ţ�����������Ȼ��Ҫ���壬��spi�ĳ�ʼ��ʱ��Ҫʹ��
#define WIFI_SPI_CS_PIN             (D13)                       // ����SPI_CS���� �������CS����
#define WIFI_SPI_INT_PIN            (B17)                       // �����ж�����
#define WIFI_SPI_RST_PIN            (B16)                       // ���帴λ����
                                
                                
#define WIFI_SPI_BUFFER_SIZE        (1024)                      // ����SPI���յĻ�������С

#define WIFI_SPI_AUTO_CONNECT       (0)                         // �����Ƿ��ʼ��ʱ����TCP����UDP����    0-������  1-�Զ�����TCP������������͸��ģʽ  2-�Զ�����UDP������������͸��ģʽ
    
#if     (WIFI_SPI_AUTO_CONNECT > 2)    
#error "WIFI_SPI_AUTO_CONNECT ��ֵֻ��Ϊ [0,1,2]" 
#else   
#define WIFI_SPI_TARGET_IP          "192.168.137.1"             // ����Ŀ��� IP
#define WIFI_SPI_TARGET_PORT        "8080"                      // ����Ŀ��Ķ˿�
#define WIFI_SPI_LOCAL_PORT         "8080"                      // �����˿�
#endif

#define WIFI_SPI_MAX_MULTI          (17)                        // ���ַ���ͣ����8����ַ

typedef enum    
{   
    BUFFER_IDLE,                                                // ģ��Ļ������ǿ��е�
    BUFFER_READ,                                                // ģ��Ļ�������������Ҫ��ȡ
    BUFFER_WRITE,                                               // ģ��Ļ������ǿ�д��
}wifi_spi_buffer_state_enum;            

typedef enum
{       
    TRANSMIT_IDLE,                                              // ��ǰû�д���
    TRANSMIT_WRITE_REQUEST,                                     // ��ģ�鷢����һ����������
    TRANSMIT_READ_STATE,                                        // ��ȡģ��״̬
    TRANSMIT_READ,                                              // ���ڶ�ȡģ���ڲ�����
    TRANSMIT_WRITE,                                             // ������ģ��д������
}wifi_spi_transmit_state_enum;

typedef enum    
{   
    WIFI_SPI_STATION,                                           // �豸ģʽ
    WIFI_SPI_SOFTAP,                                            // APģʽ
}wifi_spi_mode_enum;        
        
typedef enum        
{       
    WIFI_SPI_COMMAND,                                           // ʹ������ķ�ʽ��������
    WIFI_SPI_SERIANET,                                          // ʹ��͸���ķ�ʽ��������
}wifi_spi_transfer_mode_enum;       
        
typedef enum        
{       
    WIFI_SPI_TCP_CLIENT,                                        // ģ������TCP������
    WIFI_SPI_TCP_SERVER,                                        // ģ����ΪTCP������
    WIFI_SPI_UDP_CLIENT,                                        // ģ������UDP����
}wifi_spi_connect_mode_enum;        
        
typedef enum        
{       
    WIFI_SPI_SERVER_OFF,                                        // ģ��δ���ӷ�����
    WIFI_SPI_SERVER_ON,                                         // ģ���Ѿ����ӷ�����
}wifi_spi_connect_state_enum;       
        
typedef struct
{
    uint8 reserve;
    uint8 cmd;
    uint8 addr;
    uint8 dummy;
    uint8 magic;
    uint8 sequence;
    uint16 length;
}wifi_spi_buffer_struct;

typedef struct      
{       
    uint8                           version[12];                // �̼��汾         �ַ�����ʽ
    uint8                           mac[20];                    // ���� MAC ��ַ    �ַ�����ʽ
    uint8                           local_ip[17];               // ���� IP ��ַ     �ַ�����ʽ
    uint8                           local_port[10];             // �����˿ں�       �ַ�����ʽ
    uint8                           remote_ip[5][17];           // Զ�� IP ��ַ     �ַ�����ʽ
    wifi_spi_mode_enum              mode;                       // WIFI ģʽ
    wifi_spi_transfer_mode_enum     transfer_mode;              // ��ǰ����ģʽ
    wifi_spi_connect_mode_enum      connect_mode;               // ��������ģʽ
    wifi_spi_connect_state_enum     connect_state;              // �������������
}wifi_spi_information_struct;

typedef struct
{
    uint8  *source[WIFI_SPI_MAX_MULTI];
    uint16 length[WIFI_SPI_MAX_MULTI];
}wifi_spi_send_multi_struct;

extern wifi_spi_information_struct wifi_spi_information;


uint8   wifi_spi_disconnected_wifi         (void);                                                                      // �Ͽ� WIFI ����
uint8   wifi_spi_entry_serianet            (void);                                                                      // ��͸��ģʽ
uint8   wifi_spi_exit_serianet             (void);                                                                      // �ر�͸��ģʽ
    
uint8   wifi_spi_connect_tcp_servers       (char *ip, char *port, wifi_spi_transfer_mode_enum mode);                    // ���� TCP Server
uint8   wifi_spi_connect_udp_client        (char *ip, char *port, char *local_port, wifi_spi_transfer_mode_enum mode);  // ���� UDP ����
uint8   wifi_spi_disconnect_link           (void);                                                                      // �Ͽ����� TCP Server ʹ�ñ��ӿڽ���Ͽ���������

uint32  wifi_spi_send_byte                 (uint8 data);                                                                // WIFI ģ�鷢���ֽں���
uint32  wifi_spi_send_buffer               (const uint8 *buff, uint32 length);                                          // WIFI ģ�鷢�ͻ���������
uint32  wifi_spi_send_buffer_multi         (wifi_spi_send_multi_struct *multi_buffer);                                  // WIFI ģ�鷢�Ͷ໺��������
uint32  wifi_spi_send_string               (const char *str);                                                           // WIFI ģ�鷢���ַ�������

uint32  wifi_spi_read_buffer               (uint8 *buff, uint32 len);                                                   // WIFI ģ�����ݽ��պ���
    
uint8   wifi_spi_init                      (char *wifi_ssid, char *pass_word, wifi_spi_mode_enum wifi_mode);            // WIFI ģ���ʼ������

#endif

