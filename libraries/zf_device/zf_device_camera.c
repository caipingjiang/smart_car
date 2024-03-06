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
* �ļ�����          zf_device_camera
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

#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_exti.h"
#include "zf_driver_timer.h"
#include "zf_device_type.h"
#include "zf_device_mt9v03x.h"
#include "zf_device_ov7725.h"
#include "zf_device_scc8660.h"

#include "zf_device_camera.h"

fifo_struct camera_receiver_fifo;
uint8 camera_receiver_buffer[CAMERA_RECEIVER_BUFFER_SIZE];

uint8 camera_send_image_frame_header[4] = {0x00, 0xFF, 0x01, 0x01};

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷ������ͼ�����ݽ�ѹΪʮ�����ư�λ���� С�����
// ����˵��     *data1          ����ͷͼ������
// ����˵��     *data2          ��Ž�ѹ���ݵĵ�ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     camera_binary_image_decompression(&ov7725_image_binary[0][0], &data_buffer[0][0], OV7725_SIZE);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void camera_binary_image_decompression (const uint8 *data1, uint8 *data2, uint32 image_size)
{
    uint8  i = 8;

    while(image_size --)
    {
        i = 8;
        while(i --)
        {
            *data2 ++ = (((*data1 >> i) & 0x01) ? 255 : 0);
        }
        data1 ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷͼ��������λ���鿴ͼ��
// ����˵��     uartn           ʹ�õĴ��ں�
// ����˵��     *image_addr     ��Ҫ���͵�ͼ���ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     camera_send_image(DEBUG_UART_INDEX, &mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void camera_send_image (uart_index_enum uartn, const uint8 *image_addr, uint32 image_size)
{
    // ��������
    uart_write_buffer(uartn, camera_send_image_frame_header, 4);

    // ����ͼ��
    uart_write_buffer(uartn, (uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷ���� FIFO ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     camera_fifo_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void camera_fifo_init (void)
{
    fifo_init(&camera_receiver_fifo, FIFO_DATA_8BIT, camera_receiver_buffer, CAMERA_RECEIVER_BUFFER_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͷ��ʼ��
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ����˵��     image_size      ͼ��Ĵ�С
// ����˵��     data_addr       ������Դ�����ַ
// ����˵��     buffer_addr     ͼ�񻺳�����ַ
// ���ز���     void
// ʹ��ʾ��     camera_init(MT9V03X_IMAGE_SIZE, (uint32)MT9V03X_DATA_ADD, (uint32)&mt9v03x_image[0][0]);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void camera_init (const uint32 image_size, uint32 data_addr, uint32 buffer_addr)
{
//    switch(camera_type)
//    {
//        case CAMERA_BIN_IIC:                                                    // IIC С���
//        case CAMERA_BIN_UART:                                                   // UART С���
//            interrupt_set_priority(OV7725_VSYNC_IRQN, 0x01);                    // ���� VSY ���ж����ȼ�
//            interrupt_set_priority(OV7725_DMA_IRQN, 0x02);                      // ���� DMA ����ж����ȼ�

//            dma_camera_init(                                                    // ����ͷ DMA ������ʼ��
//                OV7725_DMA_CH,                                                  // DMA ͨ��
//                image_size,                                                     // ͼ���С
//                data_addr,                                                      // ָ����������������ַ
//                buffer_addr);                                                   // ָ�����ݴ���׵�ַ
//            timer_etr_init(OV7725_PCLK_PIN, TIM_ETR_FALLING);                   // ��ʼ����Ӧ�Ĵ�����ʱ��
//            exti_init(OV7725_VSYNC_PIN, EXTI_TRIGGER_FALLING);                  // ��ʼ�����ж϶�Ӧ���ⲿ�ж�
//            break;
//        case CAMERA_GRAYSCALE:                                                  // �����
//            interrupt_set_priority(MT9V03X_VSYNC_IRQN, 0x01);                   // ���� VSY ���ж����ȼ�
//            interrupt_set_priority(MT9V03X_DMA_IRQN, 0x02);                     // ���� DMA ����ж����ȼ�

//            dma_camera_init(                                                    // ����ͷ DMA ������ʼ��
//                MT9V03X_DMA_CH,                                                 // DMA ͨ��
//                image_size,                                                     // ͼ���С
//                data_addr,                                                      // ָ����������������ַ
//                buffer_addr);                                                   // ָ�����ݴ���׵�ַ
//            if(MT9V03X_W > 188)
//            {
//                timer_etr_init(MT9V03X_PCLK_PIN, TIM_ETR_FALLING);              // ��ʼ����Ӧ�Ĵ�����ʱ��
//            }
//            else
//            {
//                timer_etr_init(MT9V03X_PCLK_PIN, TIM_ETR_RISING);               // ��ʼ����Ӧ�Ĵ�����ʱ��
//            }
//            exti_init(MT9V03X_VSYNC_PIN, EXTI_TRIGGER_FALLING);                 // ��ʼ�����ж϶�Ӧ���ⲿ�ж�
//            break;
//        case CAMERA_COLOR:                                                      // ��ͫ
//            interrupt_set_priority(SCC8660_VSYNC_IRQN, 0x01);                   // ���� VSY ���ж����ȼ�
//            interrupt_set_priority(SCC8660_DMA_IRQN, 0x02);                     // ���� DMA ����ж����ȼ�

//            dma_camera_init(                                                    // ����ͷ DMA ������ʼ��
//                SCC8660_DMA_CH,                                                 // DMA ͨ��
//                image_size,                                                     // ͼ���С
//                data_addr,                                                      // ָ����������������ַ
//                buffer_addr);                                                   // ָ�����ݴ���׵�ַ
//            timer_etr_init(SCC8660_PCLK_PIN, TIM_ETR_RISING);                   // ��ʼ����Ӧ�Ĵ�����ʱ��
//            exti_init(SCC8660_VSYNC_PIN, EXTI_TRIGGER_FALLING);                 // ��ʼ�����ж϶�Ӧ���ⲿ�ж�
//            break;
//        default:
//            break;
//    }
}
