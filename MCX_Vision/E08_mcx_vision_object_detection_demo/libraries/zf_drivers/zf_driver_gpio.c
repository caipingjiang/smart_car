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
#include "zf_driver_gpio.h"

#define PORT_CLOCKS                                                          \
    {                                                                        \
        kCLOCK_Port0, kCLOCK_Port1, kCLOCK_Port2, kCLOCK_Port3, kCLOCK_Port4 \
    }
    
static GPIO_Type *const s_gpioBases[] = GPIO_BASE_PTRS;
static const clock_ip_name_t s_gpioclock[] = GPIO_CLOCKS;
static const clock_ip_name_t s_portclock[] = PORT_CLOCKS;
static PORT_Type *s_portbaseptrs[] = PORT_BASE_PTRS;

const port_pin_config_t pullup_config = {
                                            kPORT_PullUp,
                                            kPORT_LowPullResistor,
                                            kPORT_FastSlewRate,
                                            kPORT_PassiveFilterDisable,
                                            kPORT_OpenDrainDisable,
                                            kPORT_HighDriveStrength,
                                            kPORT_MuxAlt0,
                                            kPORT_InputBufferEnable,
                                            kPORT_InputNormal,
                                            kPORT_UnlockRegister};

const port_pin_config_t pulldown_config = {
                                            kPORT_PullDown,
                                            kPORT_LowPullResistor,
                                            kPORT_FastSlewRate,
                                            kPORT_PassiveFilterDisable,
                                            kPORT_OpenDrainDisable,
                                            kPORT_LowDriveStrength,
                                            kPORT_MuxAlt0,
                                            kPORT_InputBufferEnable,
                                            kPORT_InputNormal,
                                            kPORT_UnlockRegister};

const port_pin_config_t opendrain_config = {
                                            kPORT_PullDisable,
                                            kPORT_LowPullResistor,
                                            kPORT_FastSlewRate,
                                            kPORT_PassiveFilterDisable,
                                            kPORT_OpenDrainEnable,
                                            kPORT_LowDriveStrength,
                                            kPORT_MuxAlt0,
                                            kPORT_InputBufferEnable,
                                            kPORT_InputNormal,
                                            kPORT_UnlockRegister};    
                                            
//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           gpio_set(B9, 1);//B9 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level(gpio_struct gpio_t, uint8 dat)
{
    GPIO_PinWrite(gpio_t.gpio, (gpio_t.pin), dat);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO状态获取
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = gpio_get(B9);//获取B9引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level(gpio_struct gpio_t)
{
    return (GPIO_PinRead(gpio_t.gpio,(gpio_t.pin)));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO 翻转
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @return     void        
//  Sample usage:           gpio_toggle(B9);//B9引脚电平翻转
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level(gpio_struct gpio_t)
{
    GPIO_PortToggle(gpio_t.gpio,1<<(gpio_t.pin));
}

void gpio_set_dir(gpio_struct gpio_t, gpio_dir_enum dir)
{
    if (GPI == dir)
    {
        gpio_t.gpio->PDDR &= GPIO_FIT_REG(~(1UL << gpio_t.pin));
    }
    else
    {
        gpio_t.gpio->PDDR |= GPIO_FIT_REG((1UL << gpio_t.pin));
    }
}

void gpio_init(gpio_struct gpio_t, gpio_dir_enum dir, uint8 dat, gpio_mode_enum mode)
{
    gpio_pin_config_t gpio_config;
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_gpioBases); instance++)
    {
        if (s_gpioBases[instance] == gpio_t.gpio)
        {
            break;
        }
    }
    
    if ((instance < ARRAY_SIZE(s_gpioclock)) && (kCLOCK_IpInvalid != s_gpioclock[instance]))
    {
        CLOCK_EnableClock(s_gpioclock[instance]);
        CLOCK_EnableClock(s_portclock[instance]);
    }
    
    switch(mode)
    {
        case PULL_UP:
        {
            PORT_SetPinConfig(s_portbaseptrs[instance], gpio_t.pin, &pullup_config);
            break;
        }
        case PULL_DOWN:
        {
            PORT_SetPinConfig(s_portbaseptrs[instance], gpio_t.pin, &pulldown_config);
            break;
        }
        case OPEN_DTAIN:
        {
            PORT_SetPinConfig(s_portbaseptrs[instance], gpio_t.pin, &opendrain_config);
            break;
        }
    }
    
    if(GPO == dir)      
    {
        gpio_config.pinDirection = kGPIO_DigitalOutput; 
        
    }
    else if(GPI == dir) 
    {
        gpio_config.pinDirection = kGPIO_DigitalInput;
    }
    
    if(dat)     gpio_config.outputLogic =  1;
    else        gpio_config.outputLogic =  0;

    GPIO_PinInit(gpio_t.gpio, gpio_t.pin, &gpio_config);
}