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
* 文件名称          zf_device_type
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
#include "zf_common_headfile.h"
#include "zf_device_bluetooth_ch9141.h"

#include "zf_device_type.h"


camera_type_enum    camera_type                     = NO_CAMERE;                    // 摄像头类型变量
callback_function   camera_uart_handler             = type_default_callback;        // 串口通讯中断函数指针，根据初始化时设置的函数进行跳转

camera_type_enum    flexio_camera_type              = NO_CAMERE;                    // FLEXIO接口摄像头类型变量
callback_function   flexio_camera_vsync_handler     = type_default_callback;        // 场中断函数指针，根据初始化时设置的函数进行跳转
callback_function   flexio_camera_uart_handler      = type_default_callback;        // 串口通讯中断函数指针，根据初始化时设置的函数进行跳转

wireless_type_enum  wireless_type                   = NO_WIRELESS;
callback_function   wireless_module_uart_handler    = wireless_uart_callback;//type_default_callback;        // 无线串口接收中断函数指针，根据初始化时设置的函数进行跳转
callback_function   wireless_module_spi_handler     = type_default_callback;        // WIFI SPI GPIO中断函数指针，根据初始化时设置的函数进行跳转

tof_type_enum       tof_type                        = NO_TOF;
callback_function   tof_module_exti_handler         = type_default_callback;        // ToF 模块 INT 更新中断
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     空回调函数
// 参数说明     void        
// 返回参数     void
// 使用示例     set_camera_type(CAMERA_GRAYSCALE);
// 备注信息     一般由各摄像头初始化内部调用
//-------------------------------------------------------------------------------------------------------------------
void type_default_callback(void)
{
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置摄像头类型
// 参数说明     type_set        选定的摄像头类型
// 参数说明     vsync_callback  设备的场中断回调函数
// 参数说明     dma_callback    设备的 DMA 完成中断回调函数
// 参数说明     uart_callback   设备的串口回调函数
// 返回参数     void
// 使用示例     set_camera_type(CAMERA_GRAYSCALE);
// 备注信息     一般由各摄像头初始化内部调用
//-------------------------------------------------------------------------------------------------------------------
void  set_camera_type (camera_type_enum type_set, callback_function vsync_callback, callback_function dma_callback, callback_function uart_callback)
{
    camera_type = type_set;
    camera_uart_handler = ((uart_callback == NULL) ? (type_default_callback) : (uart_callback));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置摄像头类型
// 参数说明     type_set        选定的摄像头类型
// 返回参数     void
// 使用示例     set_camera_type(CAMERA_GRAYSCALE);
// 备注信息     一般由各摄像头初始化内部调用
//-------------------------------------------------------------------------------------------------------------------
void set_flexio_camera_type (camera_type_enum type_set, callback_function vsync_callback, callback_function dma_callback, callback_function uart_callback)
{
    flexio_camera_type = type_set;
    flexio_camera_uart_handler = ((uart_callback == NULL) ? (type_default_callback) : (uart_callback));
    flexio_camera_vsync_handler = ((vsync_callback == NULL) ? (type_default_callback) : (vsync_callback));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置无线模块类型
// 参数说明     type_set        	选定的无线模块类型
// 参数说明     wireless_callback   设备的串口回调函数
// 返回参数     void
// 使用示例     set_wireless_type(WIRELESS_UART);
// 备注信息     一般由各无线模块初始化内部调用
//-------------------------------------------------------------------------------------------------------------------
void set_wireless_type (wireless_type_enum type_set, callback_function wireless_callback)
{
    wireless_type = type_set;
    if(WIFI_SPI == wireless_type)
    {
        wireless_module_spi_handler = ((wireless_callback == NULL) ? (type_default_callback) : (wireless_callback));
    }
    else
    {
        wireless_module_uart_handler = ((wireless_callback == NULL) ? (type_default_callback) : (wireless_callback));
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置 ToF 模块类型
// 参数说明     type_set        选定的 ToF 模块类型
// 参数说明     exti_callback   设备的外部中断回调函数
// 返回参数     void
// 使用示例     set_tof_type(TOF_DL1A, dl1a_int_handler);
// 备注信息     一般由各摄像头初始化内部调用
//-------------------------------------------------------------------------------------------------------------------
void set_tof_type (tof_type_enum type_set, callback_function exti_callback)
{
    tof_type = type_set;
    tof_module_exti_handler = ((exti_callback == NULL) ? (type_default_callback) : (exti_callback));
}


