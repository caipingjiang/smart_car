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
* 文件名称          zf_device_detector
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

#include "zf_driver_uart.h"
#include "zf_common_fifo.h"
#include "zf_device_wireless_uart.h"
#include "zf_device_bluetooth_ch9141.h"
#include "zf_device_wifi_uart.h"
#include "zf_device_wifi_spi.h"

#include "zf_device_detector.h"


typedef uint32 (*detector_transfer_callback_function)   (const uint8 *buff, uint32 length);
typedef uint32 (*detector_receive_callback_function)    (uint8 *buff, uint32 length);

detector_transfer_type_enum             detector_transfer_type;                             // 数据传输方式

detector_transfer_callback_function     detector_transfer_callback;                         // 数据发送函数指针
detector_receive_callback_function      detector_receive_callback;                          // 数据接收函数指针

detector_oscilloscope_struct            detector_oscilloscope_data;                         // 虚拟示波器数据
static detector_camera_struct           detector_camera_data;                               // 图像上位机协议数据
static detector_camera_dot_struct       detector_camera_dot_data;                           // 图像上位机打点协议数据
static detector_camera_buffer_struct    detector_camera_buffer;                             // 图像以及边界缓冲区信息

static fifo_struct                      detector_fifo;
static uint8                            detector_buffer[DETECTOR_BUFFER_SIZE];              // 数据存放数组
float                                   detector_parameter[DETECTOR_SET_PARAMETR_COUNT];    // 保存接收到的参数

////-------------------------------------------------------------------------------------------------------------------
//// 函数简介     滴答客有线串口发送函数
//// 参数说明     *buff           需要发送的数据地址
//// 参数说明     length          需要发送的长度
//// 返回参数     uint32          剩余未发送数据长度
//// 使用示例     
////-------------------------------------------------------------------------------------------------------------------
//uint32 detector_debug_uart_transfer (const uint8 *buff, uint32 length)
//{
//    uart_write_buffer(DEBUG_UART_INDEX, buff, length);
//    return 0;
//}

////-------------------------------------------------------------------------------------------------------------------
//// 函数简介     滴答客有线串口接收函数
//// 参数说明     *buff           需要接收的数据地址
//// 参数说明     length          需要接收的长度
//// 返回参数     uint32          实际接收长度
//// 使用示例     
////-------------------------------------------------------------------------------------------------------------------
//uint32 detector_debug_uart_receive (uint8 *buff, uint32 length)
//{
//    return debug_read_ring_buffer(buff, length);
//}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客自定义字节发送函数
// 参数说明     data            需要发送的数据地址
// 返回参数     uint8           
// 使用示例     
//-------------------------------------------------------------------------------------------------------------------
static uint8 detector_custom_write_byte(const uint8 data)
{
    // 自行实现字节发送
    
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客自定义发送函数
// 参数说明     *buff           需要发送的数据地址
// 参数说明     length          需要发送的长度
// 返回参数     uint32          剩余未发送数据长度
// 使用示例     如果数据传输方式并不在支持范围则可以自行实现
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
// 函数简介     滴答客自定义接收函数 按字节接收
// 参数说明     *data           需要发送的数据地址
// 返回参数     uint8           0:接收成功 1：接收失败
// 注意事项     detector_custom_receive_byte 与 detector_custom_receive函数 只需要调用其中一个函数即可
//-------------------------------------------------------------------------------------------------------------------
uint8 detector_custom_receive_byte (uint8 data)
{
    uint8 return_state = 0;
    // 自行实现字节发送
    if(FIFO_SUCCESS != fifo_write_buffer(&detector_fifo, &data, 1))
    {
        return_state = 1;
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客自定义接收函数 按数组接收
// 参数说明     *buff           需要发送的数据地址
// 参数说明     length          需要发送的长度
// 返回参数     uint8           0:接收成功 1：接收失败
// 注意事项     detector_custom_receive_byte 与 detector_custom_receive函数 只需要调用其中一个函数即可
//-------------------------------------------------------------------------------------------------------------------
uint8 detector_custom_receive (uint8 *buff, uint32 length)
{
    uint8 return_state = 0;
    
    // 将接收到的数据写入FIFO
    if(FIFO_SUCCESS != fifo_write_buffer(&detector_fifo, buff, length))
    {
        return_state = 1;
    }

    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客发送函数
// 参数说明     *send_data      需要发送的数据地址
// 参数说明     send_length     需要发送的长度
// 返回参数     uint32          剩余未发送数据长度
// 使用示例     
//-------------------------------------------------------------------------------------------------------------------
static uint32 detector_transfer (void *send_data, uint32 send_length)
{
    return detector_transfer_callback((const uint8 *)send_data, send_length);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客求和函数
// 参数说明     *buffer         需要校验的数据地址
// 参数说明     length          校验长度
// 返回参数     uint8           和值
// 使用示例     
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
// 函数简介     滴答客 图像发送函数
// 参数说明     camera_type     摄像头类型
// 参数说明     *image_addr     图像首地址
// 参数说明     boundary_num    图像中包含边界数量
// 参数说明     width           图像宽度
// 参数说明     height          图像高度
// 返回参数     void           
// 使用示例     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_data_send (detector_image_type_enum camera_type, void *image_addr, uint8 boundary_num, uint16 width, uint16 height)
{
    uint32 image_size = 0;

    detector_camera_data.head           = DETECTOR_SEND_HEAD;
    detector_camera_data.function       = DETECTOR_CAMERA_FUNCTION;
    detector_camera_data.camera_type    = (camera_type << 5) | ((image_addr != NULL ? 0 : 1) << 4) | boundary_num;
    // 写入包长度信息，仅包含协议部分
    detector_camera_data.length         = sizeof(detector_camera_struct);
    detector_camera_data.image_width    = width;
    detector_camera_data.image_height   = height;

    // 首先发送帧头、功能、摄像头类型、以及宽度高度等信息
    detector_transfer(&detector_camera_data, sizeof(detector_camera_struct));
    
    // 根据摄像头类型计算图像大小
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
    
    // 发送图像数据
    if(NULL != image_addr)
    {
        detector_transfer(image_addr, image_size);
    }
    
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客 图像边线绘制函数
// 参数说明     boundary_id     边线ID
// 参数说明     dot_num         点数量
// 参数说明     *dot_x          横坐标数据首地址
// 参数说明     *dot_y          纵坐标数据首地址
// 参数说明     width           图像宽度
// 参数说明     height          图像高度
// 返回参数     void           
// 使用示例     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_dot_send (detector_camera_buffer_struct *buffer)
{
    uint8  i;
    uint16 dot_bytes = 0;   // 点字节数量
    wifi_spi_send_multi_struct multi_buffer;
    
    dot_bytes = detector_camera_dot_data.dot_num;
    
    if(detector_camera_dot_data.dot_type & (1 << 5))
    {
        dot_bytes *= 2;
    }
    
    // 边线发送时 WIFI SPI采用多源地址发送函数,可以极大提高发送速度
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
        // 首先发送帧头、功能、边界编号、坐标长度、点个数
        detector_transfer(&detector_camera_dot_data, sizeof(detector_camera_dot_struct));
        
        for(i=0; i < DETECTOR_CAMERA_MAX_BOUNDARY; i++)
        {
            // 判断是否发送横坐标数据
            if(NULL != buffer->boundary_x[i])
            {
                detector_transfer(buffer->boundary_x[i], dot_bytes);
            }
            
            // 判断是否发送纵坐标数据
            if(NULL != buffer->boundary_y[i])
            {
                // 如果没有纵坐标数据，则表示每一行只有一个边界
                // 指定了横纵坐标数据，这种方式可以实现同一行多个边界的情况，例如搜线算法能够搜索出回弯。
                detector_transfer(buffer->boundary_y[i], dot_bytes);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客 虚拟示波器发送函数
// 参数说明     *detector_oscilloscope  示波器数据结构体
// 返回参数     void           
// 使用示例     detector_oscilloscope_send(&detector_oscilloscope_data);
//-------------------------------------------------------------------------------------------------------------------
void detector_oscilloscope_send (detector_oscilloscope_struct *detector_oscilloscope)
{
    uint8 packet_size;
    
    // 将高四位清空
    detector_oscilloscope->channel_num &= 0x0f;
    
    zf_assert(DETECTOR_SET_OSCILLOSCOPE_COUNT >= detector_oscilloscope->channel_num);
    
    // 帧头
    detector_oscilloscope->head         = DETECTOR_SEND_HEAD;

    // 写入包长度信息
    packet_size                         = sizeof(detector_oscilloscope_struct) - (DETECTOR_SET_OSCILLOSCOPE_COUNT - detector_oscilloscope->channel_num) * 4;
    detector_oscilloscope->length       = packet_size;
    
    // 写入功能字与通道数量
    detector_oscilloscope->channel_num |= DETECTOR_CAMERA_OSCILLOSCOPE;

    // 和校验计算
    detector_oscilloscope->check_sum    = 0;
    detector_oscilloscope->check_sum    = detector_sum((uint8 *)detector_oscilloscope, packet_size);
    
    // 数据在调用本函数之前，由用户将需要发送的数据写入detector_oscilloscope_data.data[]
    
    detector_transfer((uint8 *)detector_oscilloscope, packet_size);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客图像信息配置函数
// 参数说明     camera_type     图像类型
// 参数说明     image_addr      图像地址    如果传递NULL参数则表示只发送边线信息到上位机
// 参数说明     width           图像宽度
// 参数说明     height          图像高度
// 返回参数     void
// 使用示例                     detector_camera_information_config(DETECTOR_MT9V03X, mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_information_config (detector_image_type_enum camera_type, void *image_addr, uint16 width, uint16 height)
{
    detector_camera_dot_data.head       = DETECTOR_SEND_HEAD;
    detector_camera_dot_data.function   = DETECTOR_CAMERA_DOT_FUNCTION;
    // 写入包长度信息
    detector_camera_dot_data.length     = sizeof(detector_camera_dot_struct);

    detector_camera_buffer.camera_type  = camera_type;
    detector_camera_buffer.image_addr   = image_addr;
    detector_camera_buffer.width        = width;
    detector_camera_buffer.height       = height;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客图像边线发送配置函数
// 参数说明     boundary_type   边界类型
// 参数说明     dot_num         一条边界有多少个点
// 参数说明     dot_x1          存放边线1横坐标的地址  如果传递NULL参数则表示不发送边线1
// 参数说明     dot_x2          存放边线2横坐标的地址  如果传递NULL参数则表示不发送边线2
// 参数说明     dot_x3          存放边线3横坐标的地址  如果传递NULL参数则表示不发送边线3
// 参数说明     dot_y1          存放边线1纵坐标的地址  如果传递NULL参数则表示不发送边线1
// 参数说明     dot_y2          存放边线2纵坐标的地址  如果传递NULL参数则表示不发送边线2
// 参数说明     dot_y3          存放边线3纵坐标的地址  如果传递NULL参数则表示不发送边线3
// 返回参数     void
// 使用示例                     detector_camera_config(X_BOUNDARY, MT9V03X_H, x1_boundary, x2_boundary, x3_boundary, NULL, NULL, NULL);     // 图像发送时包含三条边线，边线只有横坐标
// 使用示例                     detector_camera_config(Y_BOUNDARY, MT9V03X_W, NULL, NULL, NULL, y1_boundary, y2_boundary, y3_boundary);     // 图像发送时包含三条边线，边线只有纵坐标
// 使用示例                     detector_camera_config(XY_BOUNDARY, 160, xy_x1_boundary, xy_x2_boundary, xy_x3_boundary, xy_y1_boundary, xy_y2_boundary, xy_y3_boundary);   // 图像发送时包含三条边线，边线包含横纵坐标
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_boundary_config (detector_boundary_type_enum boundary_type, uint16 dot_num, void *dot_x1, void *dot_x2, void *dot_x3, void *dot_y1, void *dot_y2, void *dot_y3)
{
    uint8 i = 0;
    uint8 boundary_num = 0;
    uint8 boundary_data_type = 0;
    
    // 检查图像发送缓冲区是否准备就绪, 调用此函数之前需要先调用detector_camera_config设置好图像信息
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
// 函数简介     滴答客发送摄像头图像
// 参数说明     void     
// 返回参数     void
// 使用示例     
// 备注信息     在调用图像发送函数之前，请务必调用一次detector_camera_config函数，将对应的参数设置好
//-------------------------------------------------------------------------------------------------------------------
void detector_camera_send (void)
{
    // 检查图像发送缓冲区是否准备就绪
    zf_assert(0 != detector_camera_buffer.camera_type);
    
    detector_camera_data_send(detector_camera_buffer.camera_type, detector_camera_buffer.image_addr, detector_camera_dot_data.dot_type & 0x0f, detector_camera_buffer.width, detector_camera_buffer.height);
    
    if(detector_camera_dot_data.dot_type & 0x0f)
    {
        detector_camera_dot_send(&detector_camera_buffer);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客解析接收到的数据
// 参数说明     void            
// 返回参数     void           
// 使用示例     函数只需要放到周期运行的PIT中断或者主循环即可
//-------------------------------------------------------------------------------------------------------------------
void detector_data_analysis (void)
{
    uint8  temp_sum;
    uint32 read_length;
    detector_parameter_struct *receive_packet;
    
    // 这里使用uint32进行定义，目的是为了保证数组四字节对齐
    uint32  temp_buffer[DETECTOR_BUFFER_SIZE / 4];

    // 尝试读取数据, 如果不是自定义的传输方式则从接收回调中读取数据
    if(DETECTOR_CUSTOM != detector_transfer_type)
    {
        read_length = detector_receive_callback((uint8 *)temp_buffer, DETECTOR_BUFFER_SIZE);
        if(read_length)
        {
            // 将读取到的数据写入FIFO
            fifo_write_buffer(&detector_fifo, (uint8 *)temp_buffer, read_length);
        }
    }
    
    while(sizeof(detector_parameter_struct) <= fifo_used(&detector_fifo))
    {
        read_length = sizeof(detector_parameter_struct);
        fifo_read_buffer(&detector_fifo, (uint8 *)temp_buffer, &read_length, FIFO_READ_ONLY);
        
        if(DETECTOR_RECEIVE_HEAD != ((uint8 *)temp_buffer)[0])
        {
            // 没有帧头则从FIFO中去掉第一个数据
            read_length = 1;
        }
        else
        {
            // 找到帧头
            receive_packet = (detector_parameter_struct *)temp_buffer;
            temp_sum = receive_packet->check_sum;
            receive_packet->check_sum = 0;
            if(temp_sum == detector_sum((uint8 *)temp_buffer, sizeof(detector_parameter_struct)))
            {
                // 和校验成功保存数据
                detector_parameter[receive_packet->channel - 1] = receive_packet->data;
            }
            else
            {
                read_length = 1;
            }
        }
        
        // 丢弃无需使用的数据
        fifo_read_buffer(&detector_fifo, NULL, &read_length, FIFO_READ_AND_CLEAN);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     滴答客 初始化
// 参数说明     transfer_type   选择使用哪种方式传输数据
// 返回参数     void            
// 使用示例     
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
            // 根据自己的需求 自行实现detector_custom_write_byte函数，完成数据的传输
            detector_transfer_callback = detector_custom_transfer;
            
            // 无需设置接收回调
            
            // 在合适的位置调用detector_custom_receive 或者 detector_custom_receive_byte函数即可实现数据接收
            // detector_custom_receive 或者 detector_custom_receive_byte函数 只需调用一个函数即可，根据自己的需求是按字节接收数据还是按照数据接收数据
            // 接收到的数据会被写入detector_fifo中， 以备解析函数使用
            //detector_receive_callback = detector_custom_receive;
            
        }break;
    }
}