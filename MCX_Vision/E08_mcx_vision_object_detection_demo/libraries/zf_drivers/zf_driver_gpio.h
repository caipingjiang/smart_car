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
* 文件名称          zf_driver_gpio
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
#ifndef _zf_driver_gpio_h_
#define _zf_driver_gpio_h_

#include "MCXN947_cm33_core0.h"
#include "zf_common_typedef.h"
#include "fsl_port.h"
#include "fsl_gpio.h"


typedef struct gpio_pin_struct// GPIO
{
    GPIO_Type       *gpio;    
    uint32          pin;
}gpio_struct;

typedef enum
{
    PULL_UP = 0,    // 上拉
    PULL_DOWN,      // 下拉
    OPEN_DTAIN      // 开漏
}gpio_mode_enum;

typedef enum // 枚举端口方向
{
    GPI         = 0x00, // 定义管脚输入方向      
    GPO         = 0x01, // 定义管脚输出方向
}gpio_dir_enum;

typedef enum // 枚举端口电平
{
    GPIO_LOW    = 0x00, // 定义管脚初始化电平为低      
    GPIO_HIGH   = 0x01, // 定义管脚初始化电平为高
}gpio_level_enum;




void    gpio_set_dir        (gpio_struct gpio_t, gpio_dir_enum dir);
void    gpio_set_level      (gpio_struct gpio_t, uint8 dat);
uint8   gpio_get_level      (gpio_struct gpio_t);
void    gpio_toggle_level   (gpio_struct gpio_t);
void    gpio_init           (gpio_struct gpio_t, gpio_dir_enum dir, uint8 dat, gpio_mode_enum mode);


#define     gpio_low(gpio_t)               gpio_set_level(gpio_t, 0)
#define     gpio_high(gpio_t)              gpio_set_level(gpio_t, 1)


#endif
