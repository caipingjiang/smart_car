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
* 文件名称          zf_driver_gpio
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

#include "fsl_iomuxc.h"
#include "zf_driver_gpio.h"

GPIO_Type * PORTPTR[] = GPIO_BASE_PTRS;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      引脚复用设置(内部调用)
//  @return     void
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void afio_init(uint32 muxRegister, uint32 muxMode, uint32 inputRegister, uint32 inputDaisy, uint32 configRegister, uint32 inputOnfield, uint32 pinconf)
{
    IOMUXC_SetPinMux(muxRegister, muxMode, inputRegister, inputDaisy, configRegister, inputOnfield);
    IOMUXC_SetPinConfig(muxRegister, muxMode, inputRegister, inputDaisy, configRegister, pinconf);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      引脚复用为GPIO
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      pinconf     引脚配置（可设置参数由zf_iomuxc.h文件内PINCONF_enum枚举值确定，多个条件使用 | 相或）
//  @return     void
//  Sample usage:         
//-------------------------------------------------------------------------------------------------------------------
void gpio_iomuxc(gpio_pin_enum pin, uint32 pinconf)
{
    if((pin >= B0) && (pin <= C31))
    {
        *((volatile uint32_t *)(0x401F80BCU + 4 * (pin - B0))) = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5) | IOMUXC_SW_MUX_CTL_PAD_SION(0);
        *((volatile uint32_t *)(0x401F82ACU + 4 * (pin - B0))) = pinconf;
    }
    
    if((pin >= D0) && (pin <= D4))
    {
        *((volatile uint32_t *)(0x401F81D4U + 4 * (pin - D0))) = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5) | IOMUXC_SW_MUX_CTL_PAD_SION(0);
        *((volatile uint32_t *)(0x401F83C4U + 4 * (pin - D0))) = pinconf;
    }
    
    if((pin >= D12) && (pin <= D17))
    {
        *((volatile uint32_t *)(0x401F81BCU + 4 * (pin - D12))) = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5) | IOMUXC_SW_MUX_CTL_PAD_SION(0);
        *((volatile uint32_t *)(0x401F83ACU + 4 * (pin - D12))) = pinconf;
    }
    
    if((pin >= D26) && (pin <= D27))
    {
        *((volatile uint32_t *)(0x401F80B4U + 4 * (pin - D26))) = IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5) | IOMUXC_SW_MUX_CTL_PAD_SION(0);
        *((volatile uint32_t *)(0x401F82A4U + 4 * (pin - D26))) = pinconf;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           gpio_set(B9, 1);//B9 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_level(gpio_pin_enum pin, uint8 dat)
{
    if(dat) GPIO_SetPinsOutput(PORTPTR[pin>>5],1<<(pin&0x1f));
    else    GPIO_ClearPinsOutput(PORTPTR[pin>>5],1<<(pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO状态获取
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = gpio_get(B9);//获取B9引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get_level(gpio_pin_enum pin)
{
    return (GPIO_ReadPadStatus(PORTPTR[pin>>5],pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO 翻转
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @return     void        
//  Sample usage:           gpio_toggle(B9);//B9引脚电平翻转
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle_level(gpio_pin_enum pin)
{
    GPIO_PortToggle(PORTPTR[pin>>5],1<<(pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO方向设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @return     void        
//  Sample usage:           gpio_dir(B9, GPO);//设置B9为输出模式
//-------------------------------------------------------------------------------------------------------------------
void gpio_set_dir(gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum pinconf)
{
    if (GPI == dir) PORTPTR[pin>>5]->GDIR &= ~(1U << (pin&0x1f));
    else            PORTPTR[pin>>5]->GDIR |= (1U << (pin&0x1f));
    gpio_iomuxc(pin, pinconf);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO初始化
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @param      dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
//  @param      pinconf     引脚配置（可设置参数由zf_driver_gpio.h文件内gpio_mode_enum枚举值确定，多个条件使用 | 相或）
//  @return     void
//  Sample usage:           gpio_init(B9, GPO, 1, GPO_PUSH_PULL);//B9初始化为GPIO功能、输出模式、推挽输出
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(gpio_pin_enum pin, gpio_dir_enum dir, uint8 dat, uint32 pinconf)
{
    gpio_pin_config_t gpio_config;

    if(GPO == dir)      gpio_config.direction = kGPIO_DigitalOutput; 
    else if(GPI == dir) gpio_config.direction = kGPIO_DigitalInput;
    
    if(dat)     gpio_config.outputLogic =  1;
    else        gpio_config.outputLogic =  0;

    gpio_config.interruptMode = kGPIO_NoIntmode;
    gpio_iomuxc(pin, pinconf);

    GPIO_PinInit(PORTPTR[pin>>5], pin&0x1f, &gpio_config);
}






//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           fast_gpio_set(B9,1);//B9 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_set_level(gpio_pin_enum pin, uint8 dat)
{
    if(dat) GPIO_SetPinsOutput  (PORTPTR[(pin>>5) + 5],1<<(pin&0x1f));
    else    GPIO_ClearPinsOutput(PORTPTR[(pin>>5) + 5],1<<(pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = fast_gpio_get(B9);//获取B9引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 fast_gpio_get_level(gpio_pin_enum pin)
{
    return (GPIO_ReadPinInput(PORTPTR[(pin>>5) + 5],pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO 翻转
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @return     void        
//  Sample usage:           fast_gpio_toggle(B9);//B9引脚电平翻转
//  @note                   使用本函数进行翻转IO，最多只能达到20多M的IO翻转速率，如果使用h文件的寄存器宏定义可以达到最高150M
//                          但是需要注意，如果使用while(1)+宏定义寄存器来翻转IO，会发现频率最多只有100M，那是因为while(1)也占用了指令
//                          想达到最高频率，需要牺牲代码大小来增加速度，也就是写很多宏定义寄存器来翻转IO，这样就没有while(1)指令了
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_toggle_level(gpio_pin_enum pin)
{
    GPIO_PortToggle(PORTPTR[(pin>>5) + 5],1<<(pin&0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO方向设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @return     void        
//  Sample usage:           fast_gpio_dir(B9,GPO);//设置B9为输出模式
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_set_dir(gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum pinconf)
{
    if (GPI == dir) PORTPTR[(pin>>5) + 5]->GDIR &= ~(1U << (pin&0x1f));
    else            PORTPTR[(pin>>5) + 5]->GDIR |= (1U << (pin&0x1f));
    gpio_iomuxc(pin, pinconf);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      快速GPIO初始化
//  @param      pin         选择的引脚 (可选择范围由 common.h 内gpio_pin_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @param      dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
//  @param      pinconf     引脚配置（可设置参数由zf_iomuxc.h文件内PINCONF_enum枚举值确定，多个条件使用 | 相或）
//  @return     void
//  Sample usage:           fast_gpio_init(B9, GPO, 1, FAST_GPO_PUSH_PULL);//B9初始化为GPIO功能、输出模式、输出高电平、上拉47K IO速度2000MHZ 驱动强度R0
//                          快速GPIO 最高可达150M的翻转输出，需要达到最高速度不能使用库函数来输出电平，需要直接操作寄存器来控制引脚，具体可以查看h文件中有宏定义
//-------------------------------------------------------------------------------------------------------------------
void fast_gpio_init(gpio_pin_enum pin, gpio_dir_enum dir, uint8 dat, uint32 pinconf)
{
    uint16 temp_pin;
    gpio_iomuxc(pin, pinconf);
    
    switch(pin>>5)
    {
        case 1:
        {
            IOMUXC_GPR->GPR26 |= 1<<(pin&0x1f);
        }break;
        case 2:
        {
            IOMUXC_GPR->GPR27 |= 1<<(pin&0x1f);
        }break;
        case 3:
        {
            IOMUXC_GPR->GPR28 |= 1<<(pin&0x1f);
        }break;
    }
    
    temp_pin = (pin + 32*5);

    PORTPTR[temp_pin>>5]->IMR &= ~(1U << (temp_pin&0x1f));

    if (GPI == dir)
    {
        PORTPTR[temp_pin>>5]->GDIR &= ~(1U << (temp_pin&0x1f));
    }
    else
    {
        GPIO_PinWrite(PORTPTR[temp_pin>>5], (temp_pin&0x1f), dat);
        PORTPTR[temp_pin>>5]->GDIR |= (1U << (temp_pin&0x1f));
    }

    GPIO_SetPinInterruptConfig(PORTPTR[temp_pin>>5], (temp_pin&0x1f), kGPIO_NoIntmode);
}
