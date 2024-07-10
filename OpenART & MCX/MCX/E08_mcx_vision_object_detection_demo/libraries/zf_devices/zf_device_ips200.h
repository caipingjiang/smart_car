/*********************************************************************************************************************
* MCX Vision Opensourec Library 即（MCX Vision 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2024 SEEKFREE 逐飞科技
* 
* 本文件是 MCX Vision 开源库的一部分
* 
* MCX Vision 开源库 是免费软件
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
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_device_ips200
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.38a
* 适用平台          MCX Vision
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#ifndef _zf_device_ips200_h_
#define _zf_device_ips200_h_

#include "zf_common_headfile.h"

typedef enum
{
    IPS200_CROSSWISE                    = 0,                                    // 横屏模式
    IPS200_CROSSWISE_180                = 1,                                    // 横屏模式  旋转180
}ips200_dir_enum;

#define IPS200_SPI                      (LPSPI1)
#define IPS200_SPI_BAUDRATE             (60000000U)

#define IPS200_RST_PIN                  {GPIO0, 22u}
#define IPS200_DC_PIN                   {GPIO0, 23u}
#define IPS200_BLK_PIN                  {GPIO0, 30u}

#define IPS200_RST(x)      	            gpio_set_level(ips200_rst_pin,x)
#define IPS200_BLK(x)		            gpio_set_level(ips200_blk_pin,x)
#define IPS200_DC(x)                    gpio_set_level(ips200_dc_pin,x)

#define IPS200_DEFAULT_DISPLAY_DIR      (IPS200_CROSSWISE)                        // 默认的显示方向

void    ips200_full                     (const uint16_t color);
void    ips200_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips200_show_char                (uint16 x, uint16 y, const char dat);
void    ips200_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips200_show_int                 (uint16 x, uint16 y, const int32 dat);
void    ips200_show_float               (uint16 x, uint16 y, const float dat);

void    ips200_show_scc8660             (uint16_t* data);

void    ips200_init                     (void);

#endif
