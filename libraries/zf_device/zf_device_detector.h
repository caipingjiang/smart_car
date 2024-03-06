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
* �ļ�����          zf_device_detector
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

#ifndef _zf_device_detector_h_
#define _zf_device_detector_h_

#include "zf_common_typedef.h"
#include "zf_common_debug.h"

// �������FIFO��С
#define DETECTOR_BUFFER_SIZE             ( 0x40 )

// ����ʾ���������ͨ������
#define DETECTOR_SET_OSCILLOSCOPE_COUNT  ( 0x08 )

// ����������Ե����ͨ������
#define DETECTOR_SET_PARAMETR_COUNT      ( 0x08 )

// ����ͼ������������
#define DETECTOR_CAMERA_MAX_BOUNDARY     ( 0x08 )

// ��Ƭ������λ�����͵�֡ͷ
#define DETECTOR_SEND_HEAD               ( 0xAA )

// ����ͷ��
#define DETECTOR_CAMERA_FUNCTION         ( 0x02 ) 
#define DETECTOR_CAMERA_DOT_FUNCTION     ( 0x03 ) 
#define DETECTOR_CAMERA_OSCILLOSCOPE     ( 0x10 )

// ��λ������Ƭ�����͵�֡ͷ
#define DETECTOR_RECEIVE_HEAD            ( 0x55 )

// ����������
#define DETECTOR_RECEIVE_SET_PARAMETER   ( 0x20 )


// ���ݷ����豸ö��
typedef enum
{
    DETECTOR_DEBUG_UART,                            // ���Դ���    ʹ�õĴ�����DEBUG_UART_INDEX�궨��ָ��
    DETECTOR_WIRELESS_UART,                         // ����ת����
    DETECTOR_CH9141,                                // 9141����
    DETECTOR_WIFI_UART,                             // WIFIת����
    DETECTOR_WIFI_SPI,                              // ����WIFI SPI
    DETECTOR_CUSTOM,                                // �Զ���ͨѶ��ʽ ��Ҫ����detector_custom_write_byte������ʵ�����ݷ���
}detector_transfer_type_enum;


// ����ͷ����ö��
typedef enum
{
    // ��������ͷ�ͺŶ���
    DETECTOR_OV7725_BIN = 1,
    DETECTOR_MT9V03X,
    DETECTOR_SCC8660,
    
    // ����ͼ�����Ͷ���
    DETECTOR_BINARY = 1,
    DETECTOR_GRAY,
    DETECTOR_RGB565,
}detector_image_type_enum;

// ����ͷ����ö��
typedef enum
{
    // ��������ͷ�ͺŶ���
    X_BOUNDARY,     // ���͵�ͼ���б߽���Ϣֻ����X��Ҳ����ֻ�к�������Ϣ�����������ͼ��߶ȵõ�
    Y_BOUNDARY,     // ���͵�ͼ���б߽���Ϣֻ����Y��Ҳ����ֻ����������Ϣ�����������ͼ���ȵõ���ͨ������������������
    XY_BOUNDARY,    // ���͵�ͼ���б߽���Ϣ����X��Y����������ָ����������λ�ã��Ϳ��Է�����ʾ�������Ч��
    NO_BOUNDARY,    // ���͵�ͼ����û�б�����Ϣ
}detector_boundary_type_enum;

typedef struct
{
    uint8 head;                                     // ֡ͷ
    uint8 channel_num;                              // ����λΪ������  ����λΪͨ������
    uint8 check_sum;                                // ��У��
    uint8 length;                                   // ������
    float data[DETECTOR_SET_OSCILLOSCOPE_COUNT];    // ͨ������
}detector_oscilloscope_struct;


typedef struct
{
    uint8 head;                                     // ֡ͷ
    uint8 function;                                 // ������
    uint8 camera_type;                              // ����λ��ʾ�߽����� ����λ��ʾ�Ƿ���ͼ������  ����0x13������3��ʾһ��ͼ���������߽磨ͨ������߽硢���ߡ��ұ߽磩��1��ʾû��ͼ������
    uint8 length;                                   // �����ȣ�������Э�鲿�֣�
    uint16 image_width;                             // ͼ����
    uint16 image_height;                            // ͼ��߶�
}detector_camera_struct;


typedef struct
{
    uint8 head;                                     // ֡ͷ
    uint8 function;                                 // ������
    uint8 dot_type;                                 // ������  BIT5��1��������16λ�� 0��������8λ��    BIT7-BIT6��0��ֻ��X���� 1��ֻ��Y���� 2��X��Y���궼��    BIT3-BIT0���߽�����
    uint8 length;                                   // �����ȣ�������Э�鲿�֣�
    uint16 dot_num;                                 // ��������
    uint8  valid_flag;                              // ͨ����ʶ 
    uint8  reserve;                                 // ����
}detector_camera_dot_struct;

typedef struct
{
    void *image_addr;                               // ����ͷ��ַ
    uint16 width;                                   // ͼ����
    uint16 height;                                  // ͼ��߶�
    detector_image_type_enum camera_type;           // ����ͷ����
    void *boundary_x[DETECTOR_CAMERA_MAX_BOUNDARY]; // �߽�����������ַ
    void *boundary_y[DETECTOR_CAMERA_MAX_BOUNDARY]; // �߽������������ַ
}detector_camera_buffer_struct;

typedef struct
{
    uint8 head;                                     // ֡ͷ
    uint8 function;                                 // ������
    uint8 channel;                                  // ͨ��
    uint8 check_sum;                                // ��У��
    float data;                                     // ����
}detector_parameter_struct;


extern detector_oscilloscope_struct                 detector_oscilloscope_data;                         // ����ʾ��������
extern float                                        detector_parameter[DETECTOR_SET_PARAMETR_COUNT];    // ������յ��Ĳ���


void    detector_oscilloscope_send                  (detector_oscilloscope_struct *detector_oscilloscope);

void    detector_camera_information_config          (detector_image_type_enum camera_type, void *image_addr, uint16 width, uint16 height);
void    detector_camera_boundary_config             (detector_boundary_type_enum boundary_type, uint16 dot_num, void *dot_x1, void *dot_x2, void *dot_x3, void *dot_y1, void *dot_y2, void *dot_y3);
void    detector_camera_send                        (void);

void    detector_data_analysis                      (void);
void    detector_init                               (detector_transfer_type_enum transfer_type);



#endif

