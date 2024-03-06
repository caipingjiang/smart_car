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
* 文件名称          zf_driver_csi
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

#ifndef _zf_driver_csi_h_
#define _zf_driver_csi_h_

#include "zf_common_typedef.h"
#include "fsl_csi.h"

extern csi_handle_t csi_handle;        //csi事务结构体


//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
    CSI_VSYNC_B14,
    CSI_VSYNC_B22,
    CSI_VSYNC_C29,
}vsync_pin_enum;

//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
    CSI_PIXCLK_B20,
    CSI_PIXCLK_C28,
}pixclk_pin_enum;

//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
    CSI_PIXCLK_RISING  = kCSI_DataLatchOnRisingEdge,    // 上升沿触发
    CSI_PIXCLK_FALLING = kCSI_DataLatchOnFallingEdge,   // 下降沿触发
}pixclk_polarity_enum;

void csi_add_empty_buffer(csi_handle_t *handle, uint8 *buff);
uint8 csi_get_full_buffer(csi_handle_t *handle, uint32 *buffaddr);
void csi_start(csi_handle_t *handle);
void csi_stop(csi_handle_t *handle);
void csi_init(uint16 width, uint16 height, csi_handle_t *handle, csi_transfer_callback_t callback, vsync_pin_enum vsync, pixclk_pin_enum pixclk, pixclk_polarity_enum pixclk_polarity);



#endif
