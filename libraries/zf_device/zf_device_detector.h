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

#ifndef _zf_device_detector_h_
#define _zf_device_detector_h_

#include "zf_common_typedef.h"
#include "zf_common_debug.h"

// 定义接收FIFO大小
#define DETECTOR_BUFFER_SIZE             ( 0x40 )

// 定义示波器的最大通道数量
#define DETECTOR_SET_OSCILLOSCOPE_COUNT  ( 0x08 )

// 定义参数调试的最大通道数量
#define DETECTOR_SET_PARAMETR_COUNT      ( 0x08 )

// 定义图像边线最大数量
#define DETECTOR_CAMERA_MAX_BOUNDARY     ( 0x08 )

// 单片机往上位机发送的帧头
#define DETECTOR_SEND_HEAD               ( 0xAA )

// 摄像头类
#define DETECTOR_CAMERA_FUNCTION         ( 0x02 ) 
#define DETECTOR_CAMERA_DOT_FUNCTION     ( 0x03 ) 
#define DETECTOR_CAMERA_OSCILLOSCOPE     ( 0x10 )

// 上位机往单片机发送的帧头
#define DETECTOR_RECEIVE_HEAD            ( 0x55 )

// 参数设置类
#define DETECTOR_RECEIVE_SET_PARAMETER   ( 0x20 )


// 数据发送设备枚举
typedef enum
{
    DETECTOR_DEBUG_UART,                            // 调试串口    使用的串口由DEBUG_UART_INDEX宏定义指定
    DETECTOR_WIRELESS_UART,                         // 无线转串口
    DETECTOR_CH9141,                                // 9141蓝牙
    DETECTOR_WIFI_UART,                             // WIFI转串口
    DETECTOR_WIFI_SPI,                              // 高速WIFI SPI
    DETECTOR_CUSTOM,                                // 自定义通讯方式 需要自行detector_custom_write_byte函数中实现数据发送
}detector_transfer_type_enum;


// 摄像头类型枚举
typedef enum
{
    // 按照摄像头型号定义
    DETECTOR_OV7725_BIN = 1,
    DETECTOR_MT9V03X,
    DETECTOR_SCC8660,
    
    // 按照图像类型定义
    DETECTOR_BINARY = 1,
    DETECTOR_GRAY,
    DETECTOR_RGB565,
}detector_image_type_enum;

// 摄像头类型枚举
typedef enum
{
    // 按照摄像头型号定义
    X_BOUNDARY,     // 发送的图像中边界信息只包含X，也就是只有横坐标信息，纵坐标根据图像高度得到
    Y_BOUNDARY,     // 发送的图像中边界信息只包含Y，也就是只有纵坐标信息，横坐标根据图像宽度得到，通常很少有这样的需求
    XY_BOUNDARY,    // 发送的图像中边界信息包含X与Y，这样可以指定点在任意位置，就可以方便显示出回弯的效果
    NO_BOUNDARY,    // 发送的图像中没有边线信息
}detector_boundary_type_enum;

typedef struct
{
    uint8 head;                                     // 帧头
    uint8 channel_num;                              // 高四位为功能字  低四位为通道数量
    uint8 check_sum;                                // 和校验
    uint8 length;                                   // 包长度
    float data[DETECTOR_SET_OSCILLOSCOPE_COUNT];    // 通道数据
}detector_oscilloscope_struct;


typedef struct
{
    uint8 head;                                     // 帧头
    uint8 function;                                 // 功能字
    uint8 camera_type;                              // 低四位表示边界数量 第四位表示是否有图像数据  例如0x13：其中3表示一副图像有三条边界（通常是左边界、中线、右边界）、1表示没有图像数据
    uint8 length;                                   // 包长度（仅包含协议部分）
    uint16 image_width;                             // 图像宽度
    uint16 image_height;                            // 图像高度
}detector_camera_struct;


typedef struct
{
    uint8 head;                                     // 帧头
    uint8 function;                                 // 功能字
    uint8 dot_type;                                 // 点类型  BIT5：1：坐标是16位的 0：坐标是8位的    BIT7-BIT6：0：只有X坐标 1：只有Y坐标 2：X和Y坐标都有    BIT3-BIT0：边界数量
    uint8 length;                                   // 包长度（仅包含协议部分）
    uint16 dot_num;                                 // 画点数量
    uint8  valid_flag;                              // 通道标识 
    uint8  reserve;                                 // 保留
}detector_camera_dot_struct;

typedef struct
{
    void *image_addr;                               // 摄像头地址
    uint16 width;                                   // 图像宽度
    uint16 height;                                  // 图像高度
    detector_image_type_enum camera_type;           // 摄像头类型
    void *boundary_x[DETECTOR_CAMERA_MAX_BOUNDARY]; // 边界横坐标数组地址
    void *boundary_y[DETECTOR_CAMERA_MAX_BOUNDARY]; // 边界纵坐标数组地址
}detector_camera_buffer_struct;

typedef struct
{
    uint8 head;                                     // 帧头
    uint8 function;                                 // 功能字
    uint8 channel;                                  // 通道
    uint8 check_sum;                                // 和校验
    float data;                                     // 数据
}detector_parameter_struct;


extern detector_oscilloscope_struct                 detector_oscilloscope_data;                         // 虚拟示波器数据
extern float                                        detector_parameter[DETECTOR_SET_PARAMETR_COUNT];    // 保存接收到的参数


void    detector_oscilloscope_send                  (detector_oscilloscope_struct *detector_oscilloscope);

void    detector_camera_information_config          (detector_image_type_enum camera_type, void *image_addr, uint16 width, uint16 height);
void    detector_camera_boundary_config             (detector_boundary_type_enum boundary_type, uint16 dot_num, void *dot_x1, void *dot_x2, void *dot_x3, void *dot_y1, void *dot_y2, void *dot_y3);
void    detector_camera_send                        (void);

void    detector_data_analysis                      (void);
void    detector_init                               (detector_transfer_type_enum transfer_type);



#endif

