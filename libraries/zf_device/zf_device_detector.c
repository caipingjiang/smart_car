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

#include "zf_driver_uart.h"
#include "zf_common_fifo.h"
#include "zf_device_wireless_uart.h"
#include "zf_device_bluetooth_ch9141.h"
#include "zf_device_wifi_uart.h"
#include "zf_device_wifi_spi.h"

#include "zf_device_detector.h"


typedef uint32 (*detector_transfer_callback_function)   (const uint8 *buff, uint32 length);
typedef uint32 (*detector_receive_callback_function)    (uint8 *buff, uint32 length);

detector_transfer_type_enum             detector_transfer_type;                             // ���ݴ��䷽ʽ

detector_transfer_callback_function     detector_transfer_callback;                         // ���ݷ��ͺ���ָ��
detector_receive_callback_function      detector_receive_callback;                          // ���ݽ��պ���ָ��

detector_oscilloscope_struct            detector_oscilloscope_data;                         // ����ʾ��������
static detector_camera_struct           detector_camera_data;                               // ͼ����λ��Э������
static detector_camera_dot_struct       detector_camera_dot_data;                           // ͼ����λ�����Э������
static detector_camera_buffer_struct    detector_camera_buffer;                             // ͼ���Լ��߽绺������Ϣ

static fifo_struct                      detector_fifo;
static uint8                            detector_buffer[DETECTOR_BUFFER_SIZE];              // ���ݴ������
float                                   detector_parameter[DETECTOR_SET_PARAMETR_COUNT];    // ������յ��Ĳ���

////-------------------------------------------------------------------------------------------------------------------
//// �������     �δ�����ߴ��ڷ��ͺ���
//// ����˵��     *buff           ��Ҫ���͵����ݵ�ַ
//// ����˵��     length          ��Ҫ���͵ĳ���
//// ���ز���     uint32          ʣ��δ�������ݳ���
//// ʹ��ʾ��     
////-------------------------------------------------------------------------------------------------------------------
//uint32 detector_debug_uart_transfer (const uint8 *buff, uint32 length)
//{
//    uart_write_buffer(DEBUG_UART_INDEX, buff, length);
//    return 0;
//}

////-------------------------------------------------------------------------------------------------------------------
//// �������     �δ�����ߴ��ڽ��պ���
//// ����˵��     *buff           ��Ҫ���յ����ݵ�ַ
//// ����˵��     length          ��Ҫ���յĳ���
//// ���ز���     uint32          ʵ�ʽ��ճ���
//// ʹ��ʾ��     
////-------------------------------------------------------------------------------------------------------------------
//uint32 detector_debug_uart_receive (uint8 *buff, uint32 length)
//{
//    return debug_read_ring_buffer(buff, length);
//}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ���Զ����ֽڷ��ͺ���
// ����˵��     data            ��Ҫ���͵����ݵ�ַ
// ���ز���     uint8           
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
static uint8 detector_custom_write_byte(const uint8 data)
{
    // ����ʵ���ֽڷ���
    
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ���Զ��巢�ͺ���
// ����˵��     *buff           ��Ҫ���͵����ݵ�ַ
// ����˵��     length          ��Ҫ���͵ĳ���
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��     ������ݴ��䷽ʽ������֧�ַ�Χ���������ʵ��
//-------------------------------------------------------------------------------------------------------------------
uint32 detector_custom_transfer (const uint8 *buff, uint32 length)
{
    uint32 send_length;
    send_length = length;

    while(send_length--)
    {
        detector_custom_write_byte(*buff);
        buff++;
    }
    
    return send_length;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ���Զ�����պ��� ���ֽڽ���
// ����˵��     *data           ��Ҫ���͵����ݵ�ַ
// ���ز���     uint8           0:���ճɹ� 1������ʧ��
// ע������     detector_custom_receive_byte �� detector_custom_receive���� ֻ��Ҫ��������һ����������
//-------------------------------------------------------------------------------------------------------------------
uint8 detector_custom_receive_byte (uint8 data)
{
    uint8 return_state = 0;
    // ����ʵ���ֽڷ���
    if(FIFO_SUCCESS != fifo_write_buffer(&detector_fifo, &data, 1))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ���Զ�����պ��� ���������
// ����˵��     *buff           ��Ҫ���͵����ݵ�ַ
// ����˵��     length          ��Ҫ���͵ĳ���
// ���ز���     uint8           0:���ճɹ� 1������ʧ��
// ע������     detector_custom_receive_byte �� detector_custom_receive���� ֻ��Ҫ��������һ����������
//-------------------------------------------------------------------------------------------------------------------
uint8 detector_custom_receive (uint8 *buff, uint32 length)
{
    uint8 return_state = 0;
    
    // �����յ�������д��FIFO
    if(FIFO_SUCCESS != fifo_write_buffer(&detector_fifo, buff, length))
    {
        return_state = 1;
    }

    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�ͷ��ͺ���
// ����˵��     *send_data      ��Ҫ���͵����ݵ�ַ
// ����˵��     send_length     ��Ҫ���͵ĳ���
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
static uint32 detector_transfer (void *send_data, uint32 send_length)
{
    return detector_transfer_callback((const uint8 *)send_data, send_length);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ����ͺ���
// ����˵��     *buffer         ��ҪУ������ݵ�ַ
// ����˵��     length          У�鳤��
// ���ز���     uint8           ��ֵ
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
static uint8 detector_sum (uint8 *buffer, uint32 length)
{
    uint8 temp_sum = 0;
    
    while(length--)
    {
        temp_sum += *buffer++;
    }
    
    return temp_sum;
}



//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�� ͼ���ͺ���
// ����˵��     camera_type     ����ͷ����
// ����˵��     *image_addr     ͼ���׵�ַ
// ����˵��     boundary_num    ͼ���а����߽�����
// ����˵��     width           ͼ����
// ����˵��     height          ͼ��߶�
// ���ز���     void           
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_data_send (detector_image_type_enum camera_type, void *image_addr, uint8 boundary_num, uint16 width, uint16 height)
{
    uint32 image_size = 0;

    detector_camera_data.head           = DETECTOR_SEND_HEAD;
    detector_camera_data.function       = DETECTOR_CAMERA_FUNCTION;
    detector_camera_data.camera_type    = (camera_type << 5) | ((image_addr != NULL ? 0 : 1) << 4) | boundary_num;
    // д���������Ϣ��������Э�鲿��
    detector_camera_data.length         = sizeof(detector_camera_struct);
    detector_camera_data.image_width    = width;
    detector_camera_data.image_height   = height;

    // ���ȷ���֡ͷ�����ܡ�����ͷ���͡��Լ���ȸ߶ȵ���Ϣ
    detector_transfer(&detector_camera_data, sizeof(detector_camera_struct));
    
    // ��������ͷ���ͼ���ͼ���С
    switch(camera_type)
    {
        case DETECTOR_OV7725_BIN:
        {
            image_size = width * height / 8;
        }break;
        
        case DETECTOR_MT9V03X:
        {
            image_size = width * height;
        }break;
        
        case DETECTOR_SCC8660:
        {
            image_size = width * height * 2;
        }break;
    }
    
    // ����ͼ������
    if(NULL != image_addr)
    {
        detector_transfer(image_addr, image_size);
    }
    
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�� ͼ����߻��ƺ���
// ����˵��     boundary_id     ����ID
// ����˵��     dot_num         ������
// ����˵��     *dot_x          �����������׵�ַ
// ����˵��     *dot_y          �����������׵�ַ
// ����˵��     width           ͼ����
// ����˵��     height          ͼ��߶�
// ���ز���     void           
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_dot_send (detector_camera_buffer_struct *buffer)
{
    uint8  i;
    uint16 dot_bytes = 0;   // ���ֽ�����
    wifi_spi_send_multi_struct multi_buffer;
    
    dot_bytes = detector_camera_dot_data.dot_num;
    
    if(detector_camera_dot_data.dot_type & (1 << 5))
    {
        dot_bytes *= 2;
    }
    
    // ���߷���ʱ WIFI SPI���ö�Դ��ַ���ͺ���,���Լ�����߷����ٶ�
    if(DETECTOR_WIFI_SPI == detector_transfer_type)
    {
        multi_buffer.source[0] = (uint8 *)&detector_camera_dot_data;
        multi_buffer.length[0] = sizeof(detector_camera_dot_struct);

        for(i=0; i < DETECTOR_CAMERA_MAX_BOUNDARY; i++)
        {
            multi_buffer.source[i * 2 + 1]  = buffer->boundary_x[i];
            multi_buffer.source[i * 2 + 2]  = buffer->boundary_y[i];
            
            multi_buffer.length[i * 2 + 1]      = dot_bytes;
            multi_buffer.length[i * 2 + 2]      = dot_bytes;
        }
        
        wifi_spi_send_buffer_multi(&multi_buffer);
    }
    else
    {
        // ���ȷ���֡ͷ�����ܡ��߽��š����곤�ȡ������
        detector_transfer(&detector_camera_dot_data, sizeof(detector_camera_dot_struct));
        
        for(i=0; i < DETECTOR_CAMERA_MAX_BOUNDARY; i++)
        {
            // �ж��Ƿ��ͺ���������
            if(NULL != buffer->boundary_x[i])
            {
                detector_transfer(buffer->boundary_x[i], dot_bytes);
            }
            
            // �ж��Ƿ�������������
            if(NULL != buffer->boundary_y[i])
            {
                // ���û�����������ݣ����ʾÿһ��ֻ��һ���߽�
                // ָ���˺����������ݣ����ַ�ʽ����ʵ��ͬһ�ж���߽����������������㷨�ܹ����������䡣
                detector_transfer(buffer->boundary_y[i], dot_bytes);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�� ����ʾ�������ͺ���
// ����˵��     *detector_oscilloscope  ʾ�������ݽṹ��
// ���ز���     void           
// ʹ��ʾ��     detector_oscilloscope_send(&detector_oscilloscope_data);
//-------------------------------------------------------------------------------------------------------------------
void detector_oscilloscope_send (detector_oscilloscope_struct *detector_oscilloscope)
{
    uint8 packet_size;
    
    // ������λ���
    detector_oscilloscope->channel_num &= 0x0f;
    
    zf_assert(DETECTOR_SET_OSCILLOSCOPE_COUNT >= detector_oscilloscope->channel_num);
    
    // ֡ͷ
    detector_oscilloscope->head         = DETECTOR_SEND_HEAD;

    // д���������Ϣ
    packet_size                         = sizeof(detector_oscilloscope_struct) - (DETECTOR_SET_OSCILLOSCOPE_COUNT - detector_oscilloscope->channel_num) * 4;
    detector_oscilloscope->length       = packet_size;
    
    // д�빦������ͨ������
    detector_oscilloscope->channel_num |= DETECTOR_CAMERA_OSCILLOSCOPE;

    // ��У�����
    detector_oscilloscope->check_sum    = 0;
    detector_oscilloscope->check_sum    = detector_sum((uint8 *)detector_oscilloscope, packet_size);
    
    // �����ڵ��ñ�����֮ǰ�����û�����Ҫ���͵�����д��detector_oscilloscope_data.data[]
    
    detector_transfer((uint8 *)detector_oscilloscope, packet_size);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ��ͼ����Ϣ���ú���
// ����˵��     camera_type     ͼ������
// ����˵��     image_addr      ͼ���ַ    �������NULL�������ʾֻ���ͱ�����Ϣ����λ��
// ����˵��     width           ͼ����
// ����˵��     height          ͼ��߶�
// ���ز���     void
// ʹ��ʾ��                     detector_camera_information_config(DETECTOR_MT9V03X, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_information_config (detector_image_type_enum camera_type, void *image_addr, uint16 width, uint16 height)
{
    detector_camera_dot_data.head       = DETECTOR_SEND_HEAD;
    detector_camera_dot_data.function   = DETECTOR_CAMERA_DOT_FUNCTION;
    // д���������Ϣ
    detector_camera_dot_data.length     = sizeof(detector_camera_dot_struct);

    detector_camera_buffer.camera_type  = camera_type;
    detector_camera_buffer.image_addr   = image_addr;
    detector_camera_buffer.width        = width;
    detector_camera_buffer.height       = height;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ��ͼ����߷������ú���
// ����˵��     boundary_type   �߽�����
// ����˵��     dot_num         һ���߽��ж��ٸ���
// ����˵��     dot_x1          ��ű���1������ĵ�ַ  �������NULL�������ʾ�����ͱ���1
// ����˵��     dot_x2          ��ű���2������ĵ�ַ  �������NULL�������ʾ�����ͱ���2
// ����˵��     dot_x3          ��ű���3������ĵ�ַ  �������NULL�������ʾ�����ͱ���3
// ����˵��     dot_y1          ��ű���1������ĵ�ַ  �������NULL�������ʾ�����ͱ���1
// ����˵��     dot_y2          ��ű���2������ĵ�ַ  �������NULL�������ʾ�����ͱ���2
// ����˵��     dot_y3          ��ű���3������ĵ�ַ  �������NULL�������ʾ�����ͱ���3
// ���ز���     void
// ʹ��ʾ��                     detector_camera_config(X_BOUNDARY, MT9V03X_H, x1_boundary, x2_boundary, x3_boundary, NULL, NULL, NULL);     // ͼ����ʱ�����������ߣ�����ֻ�к�����
// ʹ��ʾ��                     detector_camera_config(Y_BOUNDARY, MT9V03X_W, NULL, NULL, NULL, y1_boundary, y2_boundary, y3_boundary);     // ͼ����ʱ�����������ߣ�����ֻ��������
// ʹ��ʾ��                     detector_camera_config(XY_BOUNDARY, 160, xy_x1_boundary, xy_x2_boundary, xy_x3_boundary, xy_y1_boundary, xy_y2_boundary, xy_y3_boundary);   // ͼ����ʱ�����������ߣ����߰�����������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_boundary_config (detector_boundary_type_enum boundary_type, uint16 dot_num, void *dot_x1, void *dot_x2, void *dot_x3, void *dot_y1, void *dot_y2, void *dot_y3)
{
    uint8 i = 0;
    uint8 boundary_num = 0;
    uint8 boundary_data_type = 0;
    
    // ���ͼ���ͻ������Ƿ�׼������, ���ô˺���֮ǰ��Ҫ�ȵ���detector_camera_config���ú�ͼ����Ϣ
    zf_assert(0 != detector_camera_buffer.camera_type);
    
    detector_camera_dot_data.dot_num    = dot_num;
    
    detector_camera_dot_data.valid_flag = 0;
    for(i = 0; i < 3; i++)
    {
        detector_camera_buffer.boundary_x[i] = NULL;
        detector_camera_buffer.boundary_y[i] = NULL;
    }
    
    switch(boundary_type)
    {
        case X_BOUNDARY:
        {
            if(NULL != dot_x1)  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 0;
                detector_camera_buffer.boundary_x[i++] = dot_x1;
            }
            if(NULL != dot_x2)  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 1;
                detector_camera_buffer.boundary_x[i++] = dot_x2;
            }
            if(NULL != dot_x3)  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 2;
                detector_camera_buffer.boundary_x[i++] = dot_x3;
            }
            
            if(255 < detector_camera_buffer.height)
            {
                boundary_data_type = 1;
            }
        }break;
        
        case Y_BOUNDARY:
        {
            if(NULL != dot_y1)  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 0;
                detector_camera_buffer.boundary_y[i++] = dot_y1;
            }
            if(NULL != dot_y2)  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 1;
                detector_camera_buffer.boundary_y[i++] = dot_y2;
            }
            if(NULL != dot_y3)  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 2;
                detector_camera_buffer.boundary_y[i++] = dot_y3;
            }
    
            if(255 < detector_camera_buffer.width)
            {
                boundary_data_type = 1;
            }
        }break;
        
        case XY_BOUNDARY:
        {
            if((NULL != dot_x1) && (NULL != dot_y1))  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 0;
                detector_camera_buffer.boundary_x[i]   = dot_x1;
                detector_camera_buffer.boundary_y[i++] = dot_y1;
            }
            if((NULL != dot_x2) && (NULL != dot_y2))  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 1;
                detector_camera_buffer.boundary_x[i]   = dot_x2;
                detector_camera_buffer.boundary_y[i++] = dot_y2;
            }
            if((NULL != dot_x3) && (NULL != dot_y3))  
            {
                boundary_num++;
                detector_camera_dot_data.valid_flag |= 1 << 2;
                detector_camera_buffer.boundary_x[i]   = dot_x3;
                detector_camera_buffer.boundary_y[i++] = dot_y3;
            }
    
            if((255 < detector_camera_buffer.width) || (255 < detector_camera_buffer.height))
            {
                boundary_data_type = 1;
            }
        }break;
        
        case NO_BOUNDARY:break;
    }
    
    detector_camera_dot_data.dot_type   = (boundary_type << 6) | (boundary_data_type << 5) | boundary_num;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�ͷ�������ͷͼ��
// ����˵��     void     
// ���ز���     void
// ʹ��ʾ��     
// ��ע��Ϣ     �ڵ���ͼ���ͺ���֮ǰ������ص���һ��detector_camera_config����������Ӧ�Ĳ������ú�
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_send (void)
{
    // ���ͼ���ͻ������Ƿ�׼������
    zf_assert(0 != detector_camera_buffer.camera_type);
    
    detector_camera_data_send(detector_camera_buffer.camera_type, detector_camera_buffer.image_addr, detector_camera_dot_data.dot_type & 0x0f, detector_camera_buffer.width, detector_camera_buffer.height);
    
    if(detector_camera_dot_data.dot_type & 0x0f)
    {
        detector_camera_dot_send(&detector_camera_buffer);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�ͽ������յ�������
// ����˵��     void            
// ���ز���     void           
// ʹ��ʾ��     ����ֻ��Ҫ�ŵ��������е�PIT�жϻ�����ѭ������
//-------------------------------------------------------------------------------------------------------------------
void detector_data_analysis (void)
{
    uint8  temp_sum;
    uint32 read_length;
    detector_parameter_struct *receive_packet;
    
    // ����ʹ��uint32���ж��壬Ŀ����Ϊ�˱�֤�������ֽڶ���
    uint32  temp_buffer[DETECTOR_BUFFER_SIZE / 4];

    // ���Զ�ȡ����, ��������Զ���Ĵ��䷽ʽ��ӽ��ջص��ж�ȡ����
    if(DETECTOR_CUSTOM != detector_transfer_type)
    {
        read_length = detector_receive_callback((uint8 *)temp_buffer, DETECTOR_BUFFER_SIZE);
        if(read_length)
        {
            // ����ȡ��������д��FIFO
            fifo_write_buffer(&detector_fifo, (uint8 *)temp_buffer, read_length);
        }
    }
    
    while(sizeof(detector_parameter_struct) <= fifo_used(&detector_fifo))
    {
        read_length = sizeof(detector_parameter_struct);
        fifo_read_buffer(&detector_fifo, (uint8 *)temp_buffer, &read_length, FIFO_READ_ONLY);
        
        if(DETECTOR_RECEIVE_HEAD != ((uint8 *)temp_buffer)[0])
        {
            // û��֡ͷ���FIFO��ȥ����һ������
            read_length = 1;
        }
        else
        {
            // �ҵ�֡ͷ
            receive_packet = (detector_parameter_struct *)temp_buffer;
            temp_sum = receive_packet->check_sum;
            receive_packet->check_sum = 0;
            if(temp_sum == detector_sum((uint8 *)temp_buffer, sizeof(detector_parameter_struct)))
            {
                // ��У��ɹ���������
                detector_parameter[receive_packet->channel - 1] = receive_packet->data;
            }
            else
            {
                read_length = 1;
            }
        }
        
        // ��������ʹ�õ�����
        fifo_read_buffer(&detector_fifo, NULL, &read_length, FIFO_READ_AND_CLEAN);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �δ�� ��ʼ��
// ����˵��     transfer_type   ѡ��ʹ�����ַ�ʽ��������
// ���ز���     void            
// ʹ��ʾ��     
//-------------------------------------------------------------------------------------------------------------------
void detector_init (detector_transfer_type_enum transfer_type)
{
    detector_transfer_type = transfer_type;
    
    fifo_init(&detector_fifo, FIFO_DATA_8BIT, detector_buffer, DETECTOR_BUFFER_SIZE);
    
    switch(detector_transfer_type)
    {
        case DETECTOR_DEBUG_UART:
        {
            detector_transfer_callback = debug_send_buffer;
            detector_receive_callback = debug_read_ring_buffer;
        }break;
        
        case DETECTOR_WIRELESS_UART:
        {
            detector_transfer_callback = wireless_uart_send_buffer;
            detector_receive_callback = wireless_uart_read_buffer;
        }break;
        
        case DETECTOR_CH9141:
        {
            detector_transfer_callback = bluetooth_ch9141_send_buffer;
            detector_receive_callback = bluetooth_ch9141_read_buffer;
        }break;
        
        case DETECTOR_WIFI_UART:
        {
            detector_transfer_callback = wifi_uart_send_buffer;
            detector_receive_callback = wifi_uart_read_buffer;
        }break;
        
        case DETECTOR_WIFI_SPI:
        {
            detector_transfer_callback = wifi_spi_send_buffer;
            detector_receive_callback = wifi_spi_read_buffer;
        }break;
        
        case DETECTOR_CUSTOM:
        {
            // �����Լ������� ����ʵ��detector_custom_write_byte������������ݵĴ���
            detector_transfer_callback = detector_custom_transfer;
            
            // �������ý��ջص�
            
            // �ں��ʵ�λ�õ���detector_custom_receive ���� detector_custom_receive_byte��������ʵ�����ݽ���
            // detector_custom_receive ���� detector_custom_receive_byte���� ֻ�����һ���������ɣ������Լ��������ǰ��ֽڽ������ݻ��ǰ������ݽ�������
            // ���յ������ݻᱻд��detector_fifo�У� �Ա���������ʹ��
            //detector_receive_callback = detector_custom_receive;
            
        }break;
    }
}