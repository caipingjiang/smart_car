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
* 文件名称          zf_device_bluetooth_ch9141
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
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   RX                  查看 zf_device_bluetooth_ch9141.h 中 CH9141_RX_PINx 宏定义
*                   TX                  查看 zf_device_bluetooth_ch9141.h 中 CH9141_TX_PINx 宏定义
*                   RTS                 查看 zf_device_bluetooth_ch9141.h 中 CH9141_RTS_PINx 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/
#ifndef _zf_device_bluetooth_ch9141_h_
#define _zf_device_bluetooth_ch9141_h_

#include "zf_common_typedef.h"

#define BLUETOOTH_CH9141_INDEX                  (UART_8)                        // 蓝牙模块对应使用的串口号
#define BLUETOOTH_CH9141_BUAD_RATE              (115200)                        // 蓝牙模块对应使用的串口波特率
#define BLUETOOTH_CH9141_TX_PIN                 (UART8_RX_D17)                  // 蓝牙模块对应模块的 TX 要接到单片机的 RX
#define BLUETOOTH_CH9141_RX_PIN                 (UART8_TX_D16)                  // 蓝牙模块对应模块的 RX 要接到单片机的 TX
#define BLUETOOTH_CH9141_RTS_PIN                (D26)                           // 蓝牙模块对应模块的 RTS 引脚

#define BLUETOOTH_CH9141_BUFFER_SIZE            (64)                            // 默认的蓝牙模块使用的接收缓冲区大小
#define BLUETOOTH_CH9141_TIMEOUT_COUNT          (500)

uint32      bluetooth_ch9141_send_byte          (const uint8 data);
uint32      bluetooth_ch9141_send_buffer        (const uint8 *buff, uint32 len);
uint32      bluetooth_ch9141_send_string        (const char *str);
void        bluetooth_ch9141_send_image         (const uint8 *image_addr, uint32 image_size);

uint32      bluetooth_ch9141_read_buffer        (uint8 *buff, uint32 len);

void        bluetooth_ch9141_uart_callback      (void);

uint8       bluetooth_ch9141_init               (void);

#endif
