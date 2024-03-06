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
* �ļ�����          zf_device_type
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

#ifndef _zf_device_type_h_
#define _zf_device_type_h_

#include "zf_common_typedef.h"

typedef enum
{
    NO_CAMERE = 0,                                                              // ������ͷ
    CAMERA_BIN_IIC,                                                             // С��� IIC �汾
    CAMERA_BIN_UART,                                                            // С��� UART �汾
    CAMERA_GRAYSCALE,                                                           // �����
    CAMERA_COLOR,                                                               // ��ͫ
}camera_type_enum;

typedef enum
{
    NO_WIRELESS = 0,                                                            // ���豸
    WIRELESS_UART,                                                              // ���ߴ���
    BLUETOOTH_CH9141,                                                           // ���� CH9141
    WIFI_UART,                                                                  // Wi-Fi ����
    WIFI_SPI,                                                                   // Wi-Fi SPI
}wireless_type_enum;

typedef enum
{
    NO_TOF = 0,                                                                 // ���豸
    TOF_DL1A,                                                                   // DL1A
    TOF_DL1B,                                                                   // DL1B
}tof_type_enum;

typedef     void (*callback_function)       (void);

extern      camera_type_enum                camera_type;                           
extern      callback_function               camera_uart_handler;                                          

extern      tof_type_enum                   tof_type;

extern      camera_type_enum                flexio_camera_type;                           
extern      callback_function               flexio_camera_vsync_handler;                                  
extern      callback_function               flexio_camera_uart_handler;                                   
            
extern      wireless_type_enum              wireless_type;
extern      callback_function               wireless_module_uart_handler;    
extern      callback_function               wireless_module_spi_handler;

extern      callback_function               tof_module_exti_handler;

void        type_default_callback           (void);
void        set_camera_type                 (camera_type_enum type_set, callback_function vsync_callback, callback_function dma_callback, callback_function uart_callback);
void        set_flexio_camera_type          (camera_type_enum type_set, callback_function vsync_callback, callback_function dma_callback, callback_function uart_callback);
void        set_wireless_type               (wireless_type_enum type_set, callback_function wireless_callback);

void        set_tof_type                    (tof_type_enum type_set, callback_function exti_callback);


#endif
