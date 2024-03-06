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
* 文件名称          zf_driver_exti
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

#include "zf_driver_exti.h"


#define GPIO_EXTI_CONFIG         SPEED_100MHZ | HYS_EN | PULL_EN | PULLUP_100K   // GPIO中断引脚参数配置

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断使能
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     exti_enable(B0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void exti_enable (gpio_pin_enum pin)
{
    GPIO_PortEnableInterrupts(PORTPTR[pin >> 5],1 << (pin & 0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断失能
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     exti_disable(B0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void exti_disable (gpio_pin_enum pin)
{
    GPIO_PortDisableInterrupts(PORTPTR[pin >> 5],1 << (pin & 0x1f)); 
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     EXTI 中断初始化
// 参数说明     pin             选择 EXTI 引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 参数说明     trigger         选择触发的信号方式 [EXTI_TRIGGER_RISING/EXTI_TRIGGER_FALLING/EXTI_TRIGGER_BOTH]
// 返回参数     void
// 使用示例     exti_init(B0, EXTI_TRIGGER_RISING);
// 备注信息     同一下标的引脚不能同时初始化为外部中断输入 例如 A0 和 B0 不能同时初始化为外部中断输入
//-------------------------------------------------------------------------------------------------------------------
void exti_init (gpio_pin_enum pin, exti_trigger_enum trigger)
{
    gpio_pin_config_t gpio_config;
    
    gpio_iomuxc(pin, GPIO_EXTI_CONFIG);
    
    gpio_config.direction = kGPIO_DigitalInput;         
    gpio_config.interruptMode = (gpio_interrupt_mode_t)trigger;  
    GPIO_PinInit(PORTPTR[pin >> 5], pin & 0x1f, &gpio_config);                      // 初始化GPIO
    GPIO_PortEnableInterrupts(PORTPTR[pin >> 5],1 << (pin & 0x1f));                 // 打开GPIO的中断

    EnableIRQ((IRQn_Type)((IRQn_Type)((pin >> 4) - 2) + GPIO1_Combined_0_15_IRQn)); // 使用IRQ
    
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)((pin>>4)-2) + GPIO1_Combined_0_15_IRQn),0);// 优先级设置 范围0-15 越小优先级越高
}
