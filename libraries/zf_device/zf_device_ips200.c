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
*                   VCC                 3.3V电源
*                   GND                 电源地
*
*                   // 单排排针 SPI 两寸屏 硬件引脚
*                   SCL                 查看 zf_device_ips200.h 中 IPS200_SCL_PIN_SPI  宏定义
*                   SDA                 查看 zf_device_ips200.h 中 IPS200_SDA_PIN_SPI  宏定义
*                   RST                 查看 zf_device_ips200.h 中 IPS200_RST_PIN_SPI  宏定义
*                   DC                  查看 zf_device_ips200.h 中 IPS200_DC_PIN_SPI   宏定义
*                   CS                  查看 zf_device_ips200.h 中 IPS200_CS_PIN_SPI   宏定义
*                   BLk                 查看 zf_device_ips200.h 中 IPS200_BLk_PIN_SPI  宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   最大分辨率 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"

#include "zf_device_ips200.h"

static uint16                   ips200_pencolor         = IPS200_DEFAULT_PENCOLOR;
static uint16                   ips200_bgcolor          = IPS200_DEFAULT_BGCOLOR;

static ips200_type_enum         ips200_display_type     = IPS200_TYPE_SPI;
static ips200_dir_enum          ips200_display_dir      = IPS200_DEFAULT_DISPLAY_DIR;
static ips200_font_size_enum    ips200_display_font     = IPS200_DEFAULT_DISPLAY_FONT;

static uint16                   ips200_x_max            = 240;
static uint16                   ips200_y_max            = 320;

static gpio_pin_enum            ips_rst_pin             = IPS200_RST_PIN_SPI;
static gpio_pin_enum            ips_bl_pin              = IPS200_BLk_PIN_SPI;
gpio_pin_enum                   ips_cs_pin              = IPS200_CS_PIN_SPI;

#if IPS200_USE_SOFT_SPI
static soft_spi_info_struct                 ips200_spi;
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 SPI 写 8bit 数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips200_write_8bit_data_spi(command);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_8bit_data_spi(data)    (soft_spi_write_8bit(&ips200_spi, (data)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 SPI 写 16bit 数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips200_write_16bit_data_spi(dat);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_16bit_data_spi(data)   (soft_spi_write_16bit(&ips200_spi, (data)))
#else
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 SPI 写 8bit 数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips200_write_8bit_data_spi(command);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_8bit_data_spi(data)    (spi_write_8bit(IPS200_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 SPI 写 16bit 数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips200_write_16bit_data_spi(dat);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define ips200_write_16bit_data_spi(data)   (spi_write_16bit(IPS200_SPI, (data)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 SPI 写数据
// 参数说明     data            数据
// 返回参数     void
// 使用示例     ips200_write_16bit_data_spi(dat);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_data (const uint8 dat)
{
    //在发送低四位
    IPS200_DATA_ADD1 = (dat << (IPS200_D0_PIN_PARALLEL8 & 0x1f)) | (IPS200_DATA_ADD1 & ~((uint32)(0x0F << (IPS200_D0_PIN_PARALLEL8 & 0x1f))) );
    //先发送高4位
    IPS200_DATA_ADD2 = ((dat>>4) << (IPS200_D4_PIN_PARALLEL8 & 0x1f)) | (IPS200_DATA_ADD2 & ~((uint32)(0x0F << (IPS200_D4_PIN_PARALLEL8 & 0x1f))) );
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 写命令
// 参数说明     command         命令
// 返回参数     void
// 使用示例     ips200_write_command(0x2a);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_command (const uint8 command)
{
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_DC(0);
        ips200_write_8bit_data_spi(command);
        IPS200_DC(1);
    }
    else
    {
        IPS200_CS(0); 
        IPS200_RS(0);
        IPS200_RD(1);
        IPS200_WR(0);
        ips200_write_data(command);
        IPS200_WR(1);	
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 向液晶屏写 8bit 数据
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips200_write_8bit_data(0x0C);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_8bit_data (const uint8 dat)
{
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        ips200_write_8bit_data_spi(dat);
    }
    else
    {
        IPS200_CS(0); 
        IPS200_RS(1);
        IPS200_RD(1);
        IPS200_WR(0);
        ips200_write_data(dat);
        IPS200_WR(1);
        IPS200_CS(1); 
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 向液晶屏写 16bit 数据
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips200_write_16bit_data(x1);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_16bit_data (const uint16 dat)
{
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        ips200_write_16bit_data_spi(dat);
    }
    else
    {
        IPS200_CS(0); 
        IPS200_RS(1);
        IPS200_RD(1);
        IPS200_WR(0);
        ips200_write_data(dat>>8);
        IPS200_WR(1);
        IPS200_WR(0);
        ips200_write_data(dat);
        IPS200_WR(1);
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示区域
// 参数说明     x1              起始x轴坐标
// 参数说明     y1              起始y轴坐标
// 参数说明     x2              结束x轴坐标
// 参数说明     y2              结束y轴坐标
// 返回参数     void
// 使用示例     ips200_set_region(0, 0, ips200_x_max - 1, ips200_y_max - 1);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_set_region (uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    // 检查一下你的显示调用的函数 自己计算一下哪里超过了屏幕显示范围
    zf_assert(x1 < ips200_x_max);
    zf_assert(y1 < ips200_y_max);
    zf_assert(x2 < ips200_x_max);
    zf_assert(y2 < ips200_y_max);

    ips200_write_command(0x2a);
    ips200_write_16bit_data(x1);
    ips200_write_16bit_data(x2);
    
    ips200_write_command(0x2b);
    ips200_write_16bit_data(y1);
    ips200_write_16bit_data(y2);
    
    ips200_write_command(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示DEBUG信息初始化
// 参数说明     void
// 返回参数     void
// 使用示例     ips200_debug_init();
// 备注信息     内部使用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);

    info.type_index = 1;
    info.display_x_max = ips200_x_max;
    info.display_y_max = ips200_y_max;

    switch(ips200_display_font)
    {
        case IPS200_6X8_FONT:
        {
            info.font_x_size = 6;
            info.font_y_size = 8;
        }break;
        case IPS200_8X16_FONT:
        {
            info.font_x_size = 8;
            info.font_y_size = 16;
        }break;
        case IPS200_16X16_FONT:
        {
            // 暂不支持
        }break;
    }
    info.output_screen = ips200_show_string;
    info.output_screen_clear = ips200_clear;
        
    debug_output_init(&info);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 清屏函数
// 参数说明     void
// 返回参数     void
// 使用示例     ips200_clear();
// 备注信息     将屏幕清空成背景颜色
//-------------------------------------------------------------------------------------------------------------------
void ips200_clear (void)
{
    uint16 i = 0, j = 0;
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(0, 0, ips200_x_max - 1, ips200_y_max - 1);
    for(i = 0; i < ips200_x_max; i ++)
    {
        for (j = 0; j < ips200_y_max; j ++)
        {
            ips200_write_16bit_data(ips200_bgcolor);                 
        }
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 屏幕填充函数
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_full(RGB565_BLACK);
// 备注信息     将屏幕填充成指定颜色
//-------------------------------------------------------------------------------------------------------------------
void ips200_full (const uint16 color)
{
    uint16 i = 0, j = 0;
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(0, 0, ips200_x_max - 1, ips200_y_max - 1);
    for(i = 0; i < ips200_x_max; i ++)
    {
        for (j = 0; j < ips200_y_max; j ++)
        {
            ips200_write_16bit_data(color);                 
        }
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示方向
// 参数说明     dir             显示方向  参照 zf_device_ips200.h 内 ips200_dir_enum 枚举体定义
// 返回参数     void
// 使用示例     ips200_set_dir(IPS200_PORTAIT);
// 备注信息     这个函数只有在初始化屏幕之前调用才生效
//-------------------------------------------------------------------------------------------------------------------
void ips200_set_dir (ips200_dir_enum dir)
{
    ips200_display_dir = dir;
    switch(ips200_display_dir)
    {
        case IPS200_PORTAIT:
        case IPS200_PORTAIT_180:
        {
            ips200_x_max = 240;
            ips200_y_max = 320;
        }break;
        case IPS200_CROSSWISE:
        case IPS200_CROSSWISE_180:
        {
            ips200_x_max = 320;
            ips200_y_max = 240;
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示字体
// 参数说明     dir             显示方向  参照 zf_device_ips200.h 内 ips200_font_size_enum 枚举体定义
// 返回参数     void
// 使用示例     ips200_set_font(IPS200_8x16_FONT);
// 备注信息     字体可以随时自由设置 设置后生效 后续显示就是新的字体大小
//-------------------------------------------------------------------------------------------------------------------
void ips200_set_font (ips200_font_size_enum font)
{
    ips200_display_font = font;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示颜色
// 参数说明     pen             颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 参数说明     bgcolor         颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_set_color(RGB565_RED, RGB565_GRAY);
// 备注信息     字体颜色和背景颜色也可以随时自由设置 设置后生效
//-------------------------------------------------------------------------------------------------------------------
void ips200_set_color (const uint16 pen, const uint16 bgcolor)
{
    ips200_pencolor = pen;
    ips200_bgcolor = bgcolor;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 画点
// 参数说明     x               坐标x方向的起点 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 [0, ips200_y_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_draw_point(0, 0, RGB565_RED);            //坐标0,0画一个红色的点
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_draw_point (uint16 x, uint16 y, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);

    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(x, y, x, y);
    ips200_write_16bit_data(color);
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 画线
// 参数说明     x_start         坐标x方向的起点 [0, ips200_x_max-1]
// 参数说明     y_start         坐标y方向的起点 [0, ips200_y_max-1]
// 参数说明     x_end           坐标x方向的终点 [0, ips200_x_max-1]
// 参数说明     y_end           坐标y方向的终点 [0, ips200_y_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_draw_line(0, 0, 10, 10, RGB565_RED);     // 坐标 0,0 到 10,10 画一条红色的线
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x_start < ips200_x_max);
    zf_assert(y_start < ips200_y_max);
    zf_assert(x_end < ips200_x_max);
    zf_assert(y_end < ips200_y_max);

    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if(x_start != x_end)
        {
            temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
            temp_b = (float)y_start - (float)x_start * temp_rate;
        }
        else
        {
            while(y_start != y_end)
            {
                ips200_draw_point(x_start, y_start, color);
                y_start += y_dir;
            }
            break;
        }
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                ips200_draw_point(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
        }
        else
        {
            while(x_start != x_end)
            {
                ips200_draw_point(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示字符
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的字符
// 返回参数     void
// 使用示例     ips200_show_char(0, 0, 'x');                     // 坐标0,0写一个字符x
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_char (uint16 x, uint16 y, const char dat)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);

    uint8 i = 0, j = 0;

    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    switch(ips200_display_font)
    {
        case IPS200_6X8_FONT:
        {
            for(i = 0; 6 > i; i ++)
            {
                ips200_set_region(x + i, y, x + i, y + 8);
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips200_write_16bit_data(ips200_pencolor);
                    }
                    else
                    {
                        ips200_write_16bit_data(ips200_bgcolor);
                    }
                    temp_top >>= 1;
                }
            }
        }break;
        case IPS200_8X16_FONT:
        {
            for(i = 0; 8 > i; i ++)
            {
                ips200_set_region(x + i, y, x + i, y + 15);
                // 减 32 因为是取模是从空格开始取得 空格在 ascii 中序号是 32
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips200_write_16bit_data(ips200_pencolor);
                    }
                    else
                    {
                        ips200_write_16bit_data(ips200_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        ips200_write_16bit_data(ips200_pencolor);
                    }
                    else
                    {
                        ips200_write_16bit_data(ips200_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
        }break;
        case IPS200_16X16_FONT:
        {
            // 暂不支持
        }break;
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示字符串
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的字符串
// 返回参数     void
// 使用示例     ips200_show_string(0, 0, "seekfree");
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_string (uint16 x, uint16 y, const char dat[])
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    
    uint16 j = 0;
    while('\0' != dat[j])
    {
        switch(ips200_display_font)
        {
            case IPS200_6X8_FONT:   ips200_show_char(x + 6 * j, y, dat[j]); break;
            case IPS200_8X16_FONT:  ips200_show_char(x + 8 * j, y, dat[j]); break;
            case IPS200_16X16_FONT: break;                                      // 暂不支持
        }
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示32位有符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 int32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips200_show_int(0, 0, x, 3);                    // x 可以为 int32 int16 int8 类型
// 备注信息     负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num+1);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    ips200_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示32位无符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips114_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips114_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 uint32
// 参数说明     num             需要显示的位数 最高10位  不包含正负号
// 返回参数     void
// 使用示例     ips200_show_uint(0, 0, x, 3);                   // x 可以为 uint32 uint16 uint8 类型
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    ips200_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示浮点数(去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 float
// 参数说明     num             整数位显示长度   最高8位  
// 参数说明     pointnum        小数位显示长度   最高6位
// 返回参数     void
// 使用示例     ips200_show_float(0, 0, x, 2, 3);               // 显示浮点数   整数显示2位   小数显示三位
// 备注信息     特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//              负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_float (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(0 < num);
    zf_assert(8 >= num);
    zf_assert(0 < pointnum);
    zf_assert(6 >= pointnum);

    double dat_temp = dat;
    double offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num+pointnum+2);

    // 用来计算余数显示 123 显示 2 位则应该显示 23
    for(; 0 < num; num --)
    {
        offset *= 10;
    }
    dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    func_double_to_str(data_buffer, dat_temp, pointnum);
    ips200_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示二值图像 数据每八个点组成一个字节数据
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips200_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips200_y_max]
// 返回参数     void
// 使用示例     ips200_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W, OV7725_H);
// 备注信息     用于显示小钻风的未解压的压缩二值化图像
//              这个函数不可以用来直接显示总钻风的未压缩的二值化图像
//              这个函数不可以用来直接显示总钻风的未压缩的二值化图像
//              这个函数不可以用来直接显示总钻风的未压缩的二值化图像
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_binary_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint8 temp = 0;
    uint32 width_index = 0, height_index = 0;

    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width / 8 + width_index / 8);       // 读取像素点
            if(0x80 & (temp << (width_index % 8)))
            {
                ips200_write_16bit_data(RGB565_WHITE);
            }
            else
            {
                ips200_write_16bit_data(RGB565_BLACK);
            }
        }
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示 8bit 灰度图像 带二值化阈值
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips200_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips200_y_max]
// 参数说明     threshold       二值化显示阈值 0-不开启二值化
// 返回参数     void
// 使用示例     ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
// 备注信息     用于显示总钻风的图像
//              如果要显示二值化图像 直接修改最后一个参数为需要的二值化阈值即可
//              如果要显示二值化图像 直接修改最后一个参数为需要的二值化阈值即可
//              如果要显示二值化图像 直接修改最后一个参数为需要的二值化阈值即可
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_gray_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0,temp = 0;
    uint32 width_index = 0, height_index = 0;

    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width + width_index);               // 读取像素点
            if(threshold == 0)
            {
                color = (0x001f & ((temp) >> 3)) << 11;
                color = color | (((0x003f) & ((temp) >> 2)) << 5);
                color = color | (0x001f & ((temp) >> 3));
                ips200_write_16bit_data(color);
            }
            else if(temp < threshold)
            {
                ips200_write_16bit_data(RGB565_BLACK);
            }
            else
            {
                ips200_write_16bit_data(RGB565_WHITE);
            }
        }
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示 RGB565 彩色图像
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     *image          图像数组指针
// 参数说明     width           图像实际宽度
// 参数说明     height          图像实际高度
// 参数说明     dis_width       图像显示宽度 参数范围 [0, ips200_x_max]
// 参数说明     dis_height      图像显示高度 参数范围 [0, ips200_y_max]
// 参数说明     color_mode      色彩模式 0-低位在前 1-高位在前
// 返回参数     void
// 使用示例     ips200_show_rgb565_image(0, 0, scc8660_image[0], SCC8660_W, SCC8660_H, SCC8660_W, SCC8660_H, 1);
// 备注信息     用于显示凌瞳的 RGB565 的图像
//              如果要显示低位在前的其他 RGB565 图像 修改最后一个参数即可
//              如果要显示低位在前的其他 RGB565 图像 修改最后一个参数即可
//              如果要显示低位在前的其他 RGB565 图像 修改最后一个参数即可
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_rgb565_image (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0;
    uint32 width_index = 0, height_index = 0;

    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // 设置显示区域

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            color = *(image + height_index * width + width_index);              // 读取像素点
            if(color_mode)
            {
                color = ((color & 0xff) << 8) | (color >> 8);
            }
            ips200_write_16bit_data(color);
        }
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示波形
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     *wave           波形数组指针
// 参数说明     width           波形实际宽度
// 参数说明     value_max       波形实际最大值
// 参数说明     dis_width       波形显示宽度 参数范围 [0, ips200_x_max]
// 参数说明     dis_value_max   波形显示最大值 参数范围 [0, ips200_y_max]
// 返回参数     void
// 使用示例     ips200_show_wave(0, 0, data, 128, 64, 64, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(NULL != wave);

    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;

    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // 设置显示区域
    for(i = 0; i < dis_value_max; i ++)
    {
        for(j = 0; j < dis_width; j ++)
        {
            ips200_write_16bit_data(ips200_bgcolor); 
        }
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }

    for(i = 0; i < dis_width; i ++)
    {
        width_index = i * width / dis_width;
        value_max_index = *(wave + width_index) * (dis_value_max - 1) / value_max;
        ips200_draw_point(i + x, (dis_value_max - 1) - value_max_index + y, ips200_pencolor);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     汉字显示
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     size            取模的时候设置的汉字字体大小 也就是一个汉字占用的点阵长宽为多少个点 取模的时候需要长宽是一样的
// 参数说明     *chinese_buffer 需要显示的汉字数组
// 参数说明     number          需要显示多少位
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_show_chinese(0, 0, 16, chinese_test[0], 4, RGB565_RED);//显示font文件里面的 示例
// 备注信息     使用PCtoLCD2002软件取模           阴码、逐行式、顺向   16*16
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_chinese (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color)
{
    // 如果程序在输出了断言信息 并且提示出错位置在这里
    // 那么一般是屏幕显示的时候超过屏幕分辨率范围了
    zf_assert(x < ips200_x_max);
    zf_assert(y < ips200_y_max);
    zf_assert(NULL != chinese_buffer);

    int i = 0, j = 0, k = 0; 
    uint8 temp = 0, temp1 = 0, temp2 = 0;
    const uint8 *p_data = chinese_buffer;
    
    temp2 = size / 8;
    
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_set_region(x, y, number * size - 1 + x, y + size - 1);
    
    for(i = 0; i < size; i ++)
    {
        temp1 = number;
        p_data = chinese_buffer + i * temp2;
        while(temp1 --)
        {
            for(k = 0; k < temp2; k ++)
            {
                for(j = 8; 0 < j; j --)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if(temp)
                    {
                        ips200_write_16bit_data(color);
                    }
                    else
                    {
                        ips200_write_16bit_data(ips200_bgcolor);
                    }
                }
                p_data ++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }   
    }
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     2寸 IPS液晶初始化
// 参数说明     type_select     两寸屏接口类型 IPS200_TYPE_SPI 为 SPI 接口串口两寸屏 IPS200_TYPE_PARALLEL8 为 8080 协议八位并口两寸屏
// 返回参数     void
// 使用示例     ips200_init(IPS200_TYPE_PARALLEL8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_init (ips200_type_enum type_select)
{
    if(IPS200_TYPE_SPI == type_select)
    {
        ips200_display_type = IPS200_TYPE_SPI;
        ips_rst_pin = IPS200_RST_PIN_SPI;
        ips_bl_pin =  IPS200_BLk_PIN_SPI;
        ips_cs_pin =  IPS200_CS_PIN_SPI;
#if IPS200_USE_SOFT_SPI
        soft_spi_init(&ips200_spi, 0, IPS200_SOFT_SPI_DELAY, IPS200_SCL_PIN, IPS200_SDA_PIN, SOFT_SPI_PIN_NULL, SOFT_SPI_PIN_NULL);
#else
        spi_init(IPS200_SPI, SPI_MODE0, IPS200_SPI_SPEED, IPS200_SCL_PIN_SPI, IPS200_SDA_PIN_SPI, SPI_MISO_NULL, SPI_CS_NULL);
#endif

        fast_gpio_init(IPS200_DC_PIN_SPI,   GPO, GPIO_LOW , FAST_GPO_PUSH_PULL);
        fast_gpio_init(ips_rst_pin,         GPO, GPIO_LOW , FAST_GPO_PUSH_PULL);
        fast_gpio_init(ips_cs_pin,  		GPO, GPIO_HIGH, FAST_GPO_PUSH_PULL);
        fast_gpio_init(ips_bl_pin,          GPO, GPIO_HIGH, FAST_GPO_PUSH_PULL);
    }
    else
    {
        ips200_display_type = IPS200_TYPE_PARALLEL8;
        ips_rst_pin = IPS200_RST_PIN_PARALLEL8;
        ips_bl_pin = IPS200_BL_PIN_PARALLEL8;
        ips_cs_pin =  IPS200_CS_PIN_PARALLEL8;

        fast_gpio_init(IPS200_D0_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL); 
        fast_gpio_init(IPS200_D1_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_D2_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_D3_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_D4_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_D5_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_D6_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_D7_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL); 
        
        fast_gpio_init(ips_bl_pin             , GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_CS_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(ips_rst_pin            , GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_RS_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_WR_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
        fast_gpio_init(IPS200_RD_PIN_PARALLEL8, GPO, 0, FAST_GPO_PUSH_PULL);
    }

    ips200_set_dir(ips200_display_dir);
    ips200_set_color(ips200_pencolor, ips200_bgcolor);
    
    IPS200_BL(1);
    IPS200_RST(0);  
    system_delay_ms(5);
    IPS200_RST(1);      
    system_delay_ms(5);
    
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(0);
    }
    ips200_write_command(0x11);
    system_delay_ms(120);

    ips200_write_command(0x36);
    switch(ips200_display_dir)
    {
        case IPS200_PORTAIT:        ips200_write_8bit_data(0x00);   break;
        case IPS200_PORTAIT_180:    ips200_write_8bit_data(0xC0);   break;
        case IPS200_CROSSWISE:      ips200_write_8bit_data(0x70);   break;
        case IPS200_CROSSWISE_180:  ips200_write_8bit_data(0xA0);   break;
    }

    ips200_write_command(0x3A);            
    ips200_write_8bit_data(0x05);
    
    ips200_write_command(0xB2);            
    ips200_write_8bit_data(0x0C);
    ips200_write_8bit_data(0x0C); 
    ips200_write_8bit_data(0x00); 
    ips200_write_8bit_data(0x33); 
    ips200_write_8bit_data(0x33);           

    ips200_write_command(0xB7);            
    ips200_write_8bit_data(0x35);

    ips200_write_command(0xBB);            
    ips200_write_8bit_data(0x29);                                               // 32 Vcom=1.35V
                                                            
    ips200_write_command(0xC2);            
    ips200_write_8bit_data(0x01);

    ips200_write_command(0xC3);            
    ips200_write_8bit_data(0x19);                                               // GVDD=4.8V 
                                                            
    ips200_write_command(0xC4);            
    ips200_write_8bit_data(0x20);                                               // VDV, 0x20:0v

    ips200_write_command(0xC5);            
    ips200_write_8bit_data(0x1A);                                               // VCOM Offset Set

    ips200_write_command(0xC6);            
    ips200_write_8bit_data(0x01F);                                              // 0x0F:60Hz          

    ips200_write_command(0xD0);            
    ips200_write_8bit_data(0xA4);
    ips200_write_8bit_data(0xA1);                                                                                                                                                                                           
                
    ips200_write_command(0xE0);     
    ips200_write_8bit_data(0xD0);   
    ips200_write_8bit_data(0x08);   
    ips200_write_8bit_data(0x0E);   
    ips200_write_8bit_data(0x09);   
    ips200_write_8bit_data(0x09);   
    ips200_write_8bit_data(0x05);   
    ips200_write_8bit_data(0x31);   
    ips200_write_8bit_data(0x33);   
    ips200_write_8bit_data(0x48);   
    ips200_write_8bit_data(0x17);   
    ips200_write_8bit_data(0x14);   
    ips200_write_8bit_data(0x15);   
    ips200_write_8bit_data(0x31);   
    ips200_write_8bit_data(0x34);   

    ips200_write_command(0xE1);     
    ips200_write_8bit_data(0xD0);   
    ips200_write_8bit_data(0x08);   
    ips200_write_8bit_data(0x0E);   
    ips200_write_8bit_data(0x09);   
    ips200_write_8bit_data(0x09); 
    ips200_write_8bit_data(0x15);   
    ips200_write_8bit_data(0x31);   
    ips200_write_8bit_data(0x33);   
    ips200_write_8bit_data(0x48);   
    ips200_write_8bit_data(0x17);   
    ips200_write_8bit_data(0x14);   
    ips200_write_8bit_data(0x15);   
    ips200_write_8bit_data(0x31);   
    ips200_write_8bit_data(0x34);   

    ips200_write_command(0x21);
    
    ips200_write_command(0x29);
    if(IPS200_TYPE_SPI == ips200_display_type)
    {
        IPS200_CS(1);
    }

    ips200_clear();                                                             // 初始化为白屏
    ips200_debug_init();
}



//---------------自定义函数-----------------
void ips200_draw_square(uint16 x, uint16 y, uint8 lenth, const uint16 color)
{
	for(uint8 i=0; i<lenth; i++)
	{
		ips200_draw_point(x+i, y, color);
		ips200_draw_point(x, y+i, color);
		ips200_draw_point(x+i, y+lenth-1, color);
		ips200_draw_point(x+lenth-1, y+i, color);
	}
	
}

void ips200_draw_circle(uint16 center_x, uint16 center_y, uint16 radius, const uint16 color)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        ips200_draw_point(center_x + x, center_y + y, color);
        ips200_draw_point(center_x + y, center_y + x, color);
        ips200_draw_point(center_x - y, center_y + x, color);
        ips200_draw_point(center_x - x, center_y + y, color);
        ips200_draw_point(center_x - x, center_y - y, color);
        ips200_draw_point(center_x - y, center_y - x, color);
        ips200_draw_point(center_x + y, center_y - x, color);
        ips200_draw_point(center_x + x, center_y - y, color);

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
