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
* �ļ�����          zf_device_bluetooth_ch9141
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
*                   RX                  �鿴 zf_device_bluetooth_ch9141.h �� CH9141_RX_PINx �궨��
*                   TX                  �鿴 zf_device_bluetooth_ch9141.h �� CH9141_TX_PINx �궨��
*                   RTS                 �鿴 zf_device_bluetooth_ch9141.h �� CH9141_RTS_PINx �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/
#ifndef _zf_device_bluetooth_ch9141_h_
#define _zf_device_bluetooth_ch9141_h_

#include "zf_common_typedef.h"

#define BLUETOOTH_CH9141_INDEX                  (UART_8)                        // ����ģ���Ӧʹ�õĴ��ں�
#define BLUETOOTH_CH9141_BUAD_RATE              (115200)                        // ����ģ���Ӧʹ�õĴ��ڲ�����
#define BLUETOOTH_CH9141_TX_PIN                 (UART8_RX_D17)                  // ����ģ���Ӧģ��� TX Ҫ�ӵ���Ƭ���� RX
#define BLUETOOTH_CH9141_RX_PIN                 (UART8_TX_D16)                  // ����ģ���Ӧģ��� RX Ҫ�ӵ���Ƭ���� TX
#define BLUETOOTH_CH9141_RTS_PIN                (D26)                           // ����ģ���Ӧģ��� RTS ����

#define BLUETOOTH_CH9141_BUFFER_SIZE            (64)                            // Ĭ�ϵ�����ģ��ʹ�õĽ��ջ�������С
#define BLUETOOTH_CH9141_TIMEOUT_COUNT          (500)

uint32      bluetooth_ch9141_send_byte          (const uint8 data);
uint32      bluetooth_ch9141_send_buffer        (const uint8 *buff, uint32 len);
uint32      bluetooth_ch9141_send_string        (const char *str);
void        bluetooth_ch9141_send_image         (const uint8 *image_addr, uint32 image_size);

uint32      bluetooth_ch9141_read_buffer        (uint8 *buff, uint32 len);

void        bluetooth_ch9141_uart_callback      (void);

uint8       bluetooth_ch9141_init               (void);

#endif
