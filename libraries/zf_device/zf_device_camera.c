/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_device_camera
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
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
// 函数简介     摄像头二进制图像数据解压为十六进制八位数据 小钻风用
// 参数说明     *data1          摄像头图像数组
// 参数说明     *data2          存放解压数据的地址
// 参数说明     image_size      图像的大小
// 返回参数     void
// 使用示例     camera_binary_image_decompression(&ov7725_image_binary[0][0], &data_buffer[0][0], OV7725_SIZE);
// 备注信息     
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
// 函数简介     摄像头图像发送至上位机查看图像
// 参数说明     uartn           使用的串口号
// 参数说明     *image_addr     需要发送的图像地址
// 参数说明     image_size      图像的大小
// 返回参数     void
// 使用示例     camera_send_image(DEBUG_UART_INDEX, &mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void camera_send_image (uart_index_enum uartn, const uint8 *image_addr, uint32 image_size)
{
    // 发送命令
    uart_write_buffer(uartn, camera_send_image_frame_header, 4);

    // 发送图像
    uart_write_buffer(uartn, (uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     摄像头串口 FIFO 初始化
// 参数说明     void
// 返回参数     void
// 使用示例     camera_fifo_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void camera_fifo_init (void)
{
    fifo_init(&camera_receiver_fifo, FIFO_DATA_8BIT, camera_receiver_buffer, CAMERA_RECEIVER_BUFFER_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     摄像头初始化
// 参数说明     image_size      图像的大小
// 返回参数     void
// 参数说明     image_size      图像的大小
// 参数说明     data_addr       数据来源外设地址
// 参数说明     buffer_addr     图像缓冲区地址
// 返回参数     void
// 使用示例     camera_init(MT9V03X_IMAGE_SIZE, (uint32)MT9V03X_DATA_ADD, (uint32)&mt9v03x_image[0][0]);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void camera_init (const uint32 image_size, uint32 data_addr, uint32 buffer_addr)
{
//    switch(camera_type)
//    {
//        case CAMERA_BIN_IIC:                                                    // IIC 小钻风
//        case CAMERA_BIN_UART:                                                   // UART 小钻风
//            interrupt_set_priority(OV7725_VSYNC_IRQN, 0x01);                    // 设置 VSY 场中断优先级
//            interrupt_set_priority(OV7725_DMA_IRQN, 0x02);                      // 设置 DMA 完成中断优先级

//            dma_camera_init(                                                    // 摄像头 DMA 关联初始化
//                OV7725_DMA_CH,                                                  // DMA 通道
//                image_size,                                                     // 图像大小
//                data_addr,                                                      // 指定数据输入的外设地址
//                buffer_addr);                                                   // 指定数据存放首地址
//            timer_etr_init(OV7725_PCLK_PIN, TIM_ETR_FALLING);                   // 初始化对应的触发定时器
//            exti_init(OV7725_VSYNC_PIN, EXTI_TRIGGER_FALLING);                  // 初始化场中断对应的外部中断
//            break;
//        case CAMERA_GRAYSCALE:                                                  // 总钻风
//            interrupt_set_priority(MT9V03X_VSYNC_IRQN, 0x01);                   // 设置 VSY 场中断优先级
//            interrupt_set_priority(MT9V03X_DMA_IRQN, 0x02);                     // 设置 DMA 完成中断优先级

//            dma_camera_init(                                                    // 摄像头 DMA 关联初始化
//                MT9V03X_DMA_CH,                                                 // DMA 通道
//                image_size,                                                     // 图像大小
//                data_addr,                                                      // 指定数据输入的外设地址
//                buffer_addr);                                                   // 指定数据存放首地址
//            if(MT9V03X_W > 188)
//            {
//                timer_etr_init(MT9V03X_PCLK_PIN, TIM_ETR_FALLING);              // 初始化对应的触发定时器
//            }
//            else
//            {
//                timer_etr_init(MT9V03X_PCLK_PIN, TIM_ETR_RISING);               // 初始化对应的触发定时器
//            }
//            exti_init(MT9V03X_VSYNC_PIN, EXTI_TRIGGER_FALLING);                 // 初始化场中断对应的外部中断
//            break;
//        case CAMERA_COLOR:                                                      // 凌瞳
//            interrupt_set_priority(SCC8660_VSYNC_IRQN, 0x01);                   // 设置 VSY 场中断优先级
//            interrupt_set_priority(SCC8660_DMA_IRQN, 0x02);                     // 设置 DMA 完成中断优先级

//            dma_camera_init(                                                    // 摄像头 DMA 关联初始化
//                SCC8660_DMA_CH,                                                 // DMA 通道
//                image_size,                                                     // 图像大小
//                data_addr,                                                      // 指定数据输入的外设地址
//                buffer_addr);                                                   // 指定数据存放首地址
//            timer_etr_init(SCC8660_PCLK_PIN, TIM_ETR_RISING);                   // 初始化对应的触发定时器
//            exti_init(SCC8660_VSYNC_PIN, EXTI_TRIGGER_FALLING);                 // 初始化场中断对应的外部中断
//            break;
//        default:
//            break;
//    }
}
