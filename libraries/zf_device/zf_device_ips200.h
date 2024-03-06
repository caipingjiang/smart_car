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
* 文件名称          zf_device_ips200
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
*                   // 双排排针 并口两寸屏 硬件引脚
*                   RD                  查看 zf_device_ips200.h 中 IPS200_RD_PIN_PARALLEL8     宏定义
*                   WR                  查看 zf_device_ips200.h 中 IPS200_WR_PIN_PARALLEL8     宏定义
*                   RS                  查看 zf_device_ips200.h 中 IPS200_RS_PIN_PARALLEL8     宏定义
*                   RST                 查看 zf_device_ips200.h 中 IPS200_RST_PIN_PARALLEL8    宏定义
*                   CS                  查看 zf_device_ips200.h 中 IPS200_CS_PIN_PARALLEL8     宏定义
*                   BL                  查看 zf_device_ips200.h 中 IPS200_BL_PIN_PARALLEL8     宏定义
*                   D0-D7               查看 zf_device_ips200.h 中 IPS200_Dx_PIN_PARALLEL8     宏定义
*                   // 单排排针 SPI 两寸屏 硬件引脚
*                   SCL                 查看 zf_device_ips200.h 中 IPS200_SCL_PIN_SPI  宏定义
*                   SDA                 查看 zf_device_ips200.h 中 IPS200_SDA_PIN_SPI  宏定义
*                   RST                 查看 zf_device_ips200.h 中 IPS200_RST_PIN_SPI  宏定义
*                   DC                  查看 zf_device_ips200.h 中 IPS200_DC_PIN_SPI   宏定义
*                   CS                  查看 zf_device_ips200.h 中 IPS200_CS_PIN_SPI   宏定义
*                   BLk                 查看 zf_device_ips200.h 中 IPS200_BLk_PIN_SPI  宏定义
*                   电源引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips200_h_
#define _zf_device_ips200_h_

#include "zf_common_typedef.h"
#include "zf_driver_gpio.h"

#define IPS200_USE_SOFT_SPI             (0 )                                    // 默认使用硬件 SPI 方式驱动 建议使用硬件 SPI 方式驱动
#if IPS200_USE_SOFT_SPI                                                         // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 SPI 驱动====================================================
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SOFT_SPI_DELAY           (1 )                                    // 软件 SPI 的时钟延时周期 数值越小 SPI 通信速率越快
#define IPS200_SCL_PIN                  (B0)                                    // 软件 SPI SCK 引脚
#define IPS200_SDA_PIN                  (B1)                                    // 软件 SPI MOSI 引脚
//====================================================软件 SPI 驱动====================================================
#else
//====================================================硬件 SPI 驱动====================================================
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_SPI_SPEED                (60 * 1000 * 1000)                      // 硬件 SPI 速率 这里设置为系统时钟二分频
#define IPS200_SPI                      (SPI_3           )                      // 硬件 SPI 号
#define IPS200_SCL_PIN_SPI              (SPI3_SCK_B0     )                      // 硬件 SPI SCK 引脚
#define IPS200_SDA_PIN_SPI              (SPI3_MOSI_B1    )                      // 硬件 SPI MOSI 引脚
//====================================================硬件 SPI 驱动====================================================
#endif
// 如果使用的是单排排针的两寸屏幕 SPI 驱动控制引脚 可以修改
#define IPS200_RST_PIN_SPI              (B2 )                                   // 液晶复位引脚定义
#define IPS200_DC_PIN_SPI               (C19)                                   // 液晶命令位引脚定义
#define IPS200_CS_PIN_SPI               (B3 )
#define IPS200_BLk_PIN_SPI              (C18)

// 如果使用的是双排排针的两寸屏幕 并口驱动控制引脚 可以修改
#define IPS200_RD_PIN_PARALLEL8         (B0 )
#define IPS200_WR_PIN_PARALLEL8         (B1 )
#define IPS200_RS_PIN_PARALLEL8         (B2 )
#define IPS200_RST_PIN_PARALLEL8        (C19 )
#define IPS200_CS_PIN_PARALLEL8         (B3 )
#define IPS200_BL_PIN_PARALLEL8         (C18)

// 如果使用的是双排排针的两寸屏幕 并口驱动数据引脚 不可随意修改
#define IPS200_D0_PIN_PARALLEL8         (B16)
#define IPS200_D1_PIN_PARALLEL8         (B17)
#define IPS200_D2_PIN_PARALLEL8         (B18)
#define IPS200_D3_PIN_PARALLEL8         (B19)
#define IPS200_D4_PIN_PARALLEL8         (D12)
#define IPS200_D5_PIN_PARALLEL8         (D13)
#define IPS200_D6_PIN_PARALLEL8         (D14)
#define IPS200_D7_PIN_PARALLEL8         (D15)

#define IPS200_DEFAULT_DISPLAY_DIR      (IPS200_PORTAIT)                        // 默认的显示方向
#define IPS200_DEFAULT_PENCOLOR         (RGB565_RED    )                        // 默认的画笔颜色
#define IPS200_DEFAULT_BGCOLOR          (RGB565_WHITE  )                        // 默认的背景颜色
#define IPS200_DEFAULT_DISPLAY_FONT     (IPS200_8X16_FONT)                      // 默认的字体模式

// 数据对应地址 不可更改
#define IPS200_DATA_ADD1                (PORTB_FAST_DR)
#define IPS200_DATA_ADD2                (PORTD_FAST_DR)

// 控制语句
#define IPS200_RD(x)       	            fast_gpio_set_level(IPS200_RD_PIN_PARALLEL8,x)
#define IPS200_WR(x)       	            fast_gpio_set_level(IPS200_WR_PIN_PARALLEL8,x)
#define IPS200_RS(x)       	            fast_gpio_set_level(IPS200_RS_PIN_PARALLEL8,x)
#define IPS200_RST(x)      	            fast_gpio_set_level(ips_rst_pin,x)
#define IPS200_CS(x)       	            fast_gpio_set_level(ips_cs_pin,x)
#define IPS200_BL(x)		            fast_gpio_set_level(ips_bl_pin,x)
                    
#define IPS200_DC(x)                    fast_gpio_set_level(IPS200_DC_PIN_SPI,x)


typedef enum
{
    IPS200_TYPE_SPI,                                                            // SPI 驱动
    IPS200_TYPE_PARALLEL8,                                                      // 并口驱动
}ips200_type_enum;

typedef enum
{
    IPS200_PORTAIT                      = 0,                                    // 竖屏模式
    IPS200_PORTAIT_180                  = 1,                                    // 竖屏模式  旋转180
    IPS200_CROSSWISE                    = 2,                                    // 横屏模式
    IPS200_CROSSWISE_180                = 3,                                    // 横屏模式  旋转180
}ips200_dir_enum;

typedef enum
{
    IPS200_6X8_FONT                     = 0,                                    // 6x8      字体
    IPS200_8X16_FONT                    = 1,                                    // 8x16     字体
    IPS200_16X16_FONT                   = 2,                                    // 16x16    字体 目前不支持
}ips200_font_size_enum;


extern  gpio_pin_enum                   ips_cs_pin;


void    ips200_clear                    (void);
void    ips200_full                     (const uint16 color);
void    ips200_set_dir                  (ips200_dir_enum dir);
void    ips200_set_font                 (ips200_font_size_enum font);
void    ips200_set_color                (const uint16 pen, const uint16 bgcolor);
void    ips200_draw_point               (uint16 x, uint16 y, const uint16 color);
void    ips200_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips200_show_char                (uint16 x, uint16 y, const char dat);
void    ips200_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips200_show_int                 (uint16 x, uint16 y, const int32 dat, uint8 num);
void    ips200_show_uint                (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    ips200_show_float               (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    ips200_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    ips200_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);
void    ips200_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);

void    ips200_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    ips200_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);


//-------------------自定义函数-----------------
void ips200_draw_square(uint16 x, uint16 y, uint8 lenth, const uint16 color);
void ips200_draw_circle(uint16 center_x, uint16 center_y, uint16 radius, const uint16 color);
//-------------------自定义函数-----------------

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示小钻风图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips200_displayimage7725(ov7725_image_binary[0], 80, 60);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage7725(p, width, height)       (ips200_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示总钻风图像 不带二值化 显示灰度图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips200_displayimage03x(mt9v03x_image[0], 94, 60);
// 备注信息     如果要显示二值化图像就去调用 ips200_show_gray_image 函数
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage03x(p, width, height)        (ips200_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示凌瞳图像
// 参数说明     p               图像数组
// 参数说明     width           显示宽度
// 参数说明     height          显示高度
// 返回参数     void
// 使用示例     ips200_displayimage8660(scc8660_image[0], 80, 60);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage8660(p, width, height)       (ips200_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

void    ips200_init                     (ips200_type_enum type_select);

#endif
