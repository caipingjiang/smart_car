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

#ifndef _zf_driver_gpio_h_
#define _zf_driver_gpio_h_

#include "MIMXRT1064.h"
#include "zf_common_typedef.h"
#include "fsl_gpio.h"


extern GPIO_Type * PORTPTR[];



typedef enum                                                                    // 枚举 GPIO 引脚  此枚举定义不允许用户修改
{
    B0  = (32* 1 + 0 ), B1 ,    B2 ,    B3 ,    
    B9  = (32* 1 + 9 ), B10,    B11,    B12,    B13,    B14,    B15,
    B16 ,               B17,    B18,    B19,    B20,    B21,    B22,    B23,
    B24 ,               B25,    B26,    B27,    B28,    B29,    B30,    B31,
    
    C0  = (32* 2 + 0 ), C1 ,    C2 ,    C3 ,    C4 ,    C5 ,    C6 ,    C7 ,
    C8 ,                C9 ,    C10,    C11,    C12,    C13,    C14,    C15,
    C16,                C17,    C18,    C19,    C20,    C21,    C22,    C23,
    C24,                C25,    C26,    C27,    C28,    C29,    C30,    C31,

    D0  = (32* 3 + 0 ), D1 ,    D2 ,    D3 ,    D4 ,
    D12 = (32* 3 + 12), D13,    D14,    D15,
    D16,                D17,    
    D26 = (32* 3 + 26), D27,    
}gpio_pin_enum;



typedef enum                                                                    // 枚举端口复用   此枚举定义不允许用户修改
{
    GPIO_AF0            = 0x00,                                                 // 引脚复用功能选项  0
    GPIO_AF1            = 0x01,                                                 // 引脚复用功能选项  1
    GPIO_AF2            = 0x02,                                                 // 引脚复用功能选项  2
    GPIO_AF3            = 0x03,                                                 // 引脚复用功能选项  3
    GPIO_AF4            = 0x04,                                                 // 引脚复用功能选项  4
    GPIO_AF5            = 0x05,                                                 // 引脚复用功能选项  5
    GPIO_AF6            = 0x06,                                                 // 引脚复用功能选项  6
    GPIO_AF7            = 0x07,                                                 // 引脚复用功能选项  7
    GPIO_AF8            = 0x08,                                                 // 引脚复用功能选项  8
    GPIO_AF9            = 0x09,                                                 // 引脚复用功能选项  9
    GPIO_AF10           = 0x0A,                                                 // 引脚复用功能选项 10
    GPIO_AF11           = 0x0B,                                                 // 引脚复用功能选项 11
    GPIO_AF12           = 0x0C,                                                 // 引脚复用功能选项 12
    GPIO_AF13           = 0x0D,                                                 // 引脚复用功能选项 13
    GPIO_AF14           = 0x0E,                                                 // 引脚复用功能选项 14
    GPIO_AF15           = 0x0F,                                                 // 引脚复用功能选项 15
}gpio_af_enum;


typedef enum
{
    // 单一设置参数，可以根据需求自己组合
    HYS_EN              = 1<<IOMUXC_SW_PAD_CTL_PAD_HYS_SHIFT,                   //滞后使能
            
    PULLDOWN_100K       = 0<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //端口为输入时有效
    PULLUP_47K          = 1<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //端口为输入时有效
    PULLUP_100K         = 2<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //端口为输入时有效
    PULLUP_22K          = 3<<IOMUXC_SW_PAD_CTL_PAD_PUS_SHIFT,                   //端口为输入时有效
        
    PULL_EN             = 1<<IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT | 1<<IOMUXC_SW_PAD_CTL_PAD_PUE_SHIFT,
    KEEPER_EN           = 1<<IOMUXC_SW_PAD_CTL_PAD_PKE_SHIFT,                   //保持器使能
                
    OD_EN               = 1<<IOMUXC_SW_PAD_CTL_PAD_ODE_SHIFT,                   //开漏使能
        
    SPEED_50MHZ         = 0<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    SPEED_100MHZ        = 1<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
    SPEED_200MHZ        = 3<<IOMUXC_SW_PAD_CTL_PAD_SPEED_SHIFT,
        
    DSE_DIS             = 0<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //禁用输出强度设置
    DSE_R0              = 1<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //3.3V时150ohm  1.8V时260ohm
    DSE_R0_2            = 2<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/2
    DSE_R0_3            = 3<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/3
    DSE_R0_4            = 4<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/4
    DSE_R0_5            = 5<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/5
    DSE_R0_6            = 6<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/6
    DSE_R0_7            = 7<<IOMUXC_SW_PAD_CTL_PAD_DSE_SHIFT,                   //R/7
            
    SRE_SLOW            = 0<<IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT,
    SRE_FAST            = 1<<IOMUXC_SW_PAD_CTL_PAD_SRE_SHIFT,
    
    // 组合设置参数，快捷调节参数
    GPI_ANAOG_IN        = SPEED_100MHZ | DSE_R0_6,                              // 模拟输入
    GPI_FLOATING_IN     = SPEED_100MHZ | DSE_R0,                                // 浮空输入
    GPI_PULL_DOWN       = SPEED_100MHZ | DSE_R0 | PULLDOWN_100K | PULL_EN,      // 下拉输入
    GPI_PULL_UP         = SPEED_100MHZ | DSE_R0 | PULLUP_47K    | PULL_EN,      // 上拉输入
        
    GPO_PUSH_PULL       = SPEED_100MHZ | DSE_R0,                                // 推挽输出
    GPO_OPEN_DTAIN      = SPEED_100MHZ | DSE_R0 | OD_EN,                        // 开漏输出
    GPO_AF_PUSH_PULL    = SPEED_100MHZ | DSE_R0,                                // 复用推挽输出
    GPO_AF_OPEN_DTAIN   = SPEED_100MHZ | DSE_R0 | OD_EN,                        // 复用开漏输出
    
    // 快速GPIO配置参数
    FAST_GPI_PULL_DOWN  = SPEED_200MHZ | DSE_R0 | PULLDOWN_100K | PULL_EN,      // 下拉输入
    FAST_GPI_PULL_UP    = SPEED_200MHZ | DSE_R0 | PULLUP_47K    | PULL_EN,      // 上拉输入
    
    FAST_GPO_PUSH_PULL  = SPEED_200MHZ | DSE_R0,

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


//引脚复用设置----------------------------------------------------
void        afio_init(uint32 muxRegister, uint32 muxMode, uint32 inputRegister, uint32 inputDaisy, uint32 configRegister, uint32 inputOnfield, uint32 pinconf);
void        gpio_iomuxc(gpio_pin_enum pin, uint32 pinconf);


//通用GPIO操作---------------------------------------------------
void        gpio_set_level              (gpio_pin_enum pin, uint8 dat);
uint8       gpio_get_level              (gpio_pin_enum pin);
void        gpio_toggle_level           (gpio_pin_enum pin);
void        gpio_set_dir                (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum pinconf);
void        gpio_init                   (gpio_pin_enum pin, gpio_dir_enum dir, uint8 dat, uint32 pinconf);

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对应 IO 复位为低电平
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_low(B5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_low(pin)               GPIO_ClearPinsOutput(PORTPTR[pin >> 5],1 << (pin & 0x1f))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对应 IO 置位为高电平
// 参数说明     x           选择的引脚 (可选择范围由 zf_driver_gpio.h 内 gpio_pin_enum 枚举值确定)
// 返回参数     void
// 使用示例     gpio_high(B5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
#define     gpio_high(pin)              GPIO_SetPinsOutput(PORTPTR[pin >> 5],1 << (pin & 0x1f))


#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define     gpio_set(pin, dat)          (gpio_set_level((pin), (dat)))
#define     gpio_get(pin)               (gpio_get_level((pin)))
#define     gpio_dir(pin, dir, mode)    (gpio_set_dir((pin), (dir), (mode)))
#define     gpio_toggle(pin)            (gpio_toggle_level((pin)))
#endif


#define     PORTB_DR           		    GPIO1->DR                   // B端口数据输出寄存器
#define     PORTC_DR           		    GPIO2->DR                   // C端口数据输出寄存器
#define     PORTD_DR           		    GPIO3->DR                   // D端口数据输出寄存器


//------------------------------------------------------
//以下函数用于实现快速GPIO的操作，快速GPIO最高可达150M的IO翻转速度


void        fast_gpio_set_level         (gpio_pin_enum pin, uint8 dat);
uint8       fast_gpio_get_level         (gpio_pin_enum pin);
void        fast_gpio_toggle_level      (gpio_pin_enum pin);
void        fast_gpio_set_dir           (gpio_pin_enum pin, gpio_dir_enum dir, gpio_mode_enum pinconf);
void        fast_gpio_init              (gpio_pin_enum pin, gpio_dir_enum dir, uint8 dat, uint32 pinconf);

#define     PORTB_FAST_DR               GPIO6->DR                   // B端口数据输出寄存器
#define     PORTC_FAST_DR               GPIO7->DR                   // C端口数据输出寄存器
#define     PORTD_FAST_DR               GPIO8->DR                   // D端口数据输出寄存器
                                                                    
#define     PORTB_FAST_PSR              GPIO6->PSR                  // B端口数据输入寄存器
#define     PORTC_FAST_PSR              GPIO7->PSR                  // C端口数据输入寄存器
#define     PORTD_FAST_PSR              GPIO8->PSR                  // D端口数据输入寄存器
                                                                    
#define     PORTB_FAST_SET(X)           GPIO6->DR_SET    = 1<<X     // B端口快速GPIO置一寄存器     X选择端口号 5：表示B5
#define     PORTC_FAST_SET(X)           GPIO7->DR_SET    = 1<<X     // C端口快速GPIO置一寄存器     X选择端口号 5：表示C5
#define     PORTD_FAST_SET(X)           GPIO8->DR_SET    = 1<<X     // D端口快速GPIO置一寄存器     X选择端口号 5：表示D5
                                                                                                
#define     PORTB_FAST_CLR(X)           GPIO6->DR_CLEAR  = 1<<X     // B端口快速GPIO置低寄存器     X选择端口号 5：表示B5
#define     PORTC_FAST_CLR(X)           GPIO7->DR_CLEAR  = 1<<X     // C端口快速GPIO置低寄存器     X选择端口号 5：表示C5
#define     PORTD_FAST_CLR(X)           GPIO8->DR_CLEAR  = 1<<X     // D端口快速GPIO置低寄存器     X选择端口号 5：表示D5
                                                                                                
#define     PORTB_FAST_TOGGLE(X)        GPIO6->DR_TOGGLE = 1<<X     // B端口快速GPIO取反寄存器     X选择端口号 5：表示B5
#define     PORTC_FAST_TOGGLE(X)        GPIO7->DR_TOGGLE = 1<<X     // C端口快速GPIO取反寄存器     X选择端口号 5：表示C5
#define     PORTD_FAST_TOGGLE(X)        GPIO8->DR_TOGGLE = 1<<X     // D端口快速GPIO取反寄存器     X选择端口号 5：表示D5






#endif
