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
* 文件名称          zf_driver_pwm
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

#include "fsl_pwm.h"
#include "fsl_iomuxc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"

#include "zf_driver_pwm.h"

#define PWM_SRC_CLK_FREQ    CLOCK_GetFreq(kCLOCK_IpgClk)                        // 定义PWM输入时钟源频率
#define PWM_PIN_CONF        SPEED_100MHZ | KEEPER_EN | DSE_R0_6                 // 配置PWM引脚默认配置   

static PWM_Type * PWMPTR[] = PWM_BASE_PTRS;

void pwm_iomuxc(pwm_channel_enum pin)
{
    switch(pin)
    {
        case PWM1_MODULE0_CHA_D12:  afio_init(IOMUXC_GPIO_SD_B0_00_FLEXPWM1_PWMA00, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE0_CHB_D13:  afio_init(IOMUXC_GPIO_SD_B0_01_FLEXPWM1_PWMB00, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE1_CHA_D14:  afio_init(IOMUXC_GPIO_SD_B0_02_FLEXPWM1_PWMA01, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE1_CHB_D15:  afio_init(IOMUXC_GPIO_SD_B0_03_FLEXPWM1_PWMB01, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE2_CHA_D16:  afio_init(IOMUXC_GPIO_SD_B0_04_FLEXPWM1_PWMA02, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE2_CHB_D17:  afio_init(IOMUXC_GPIO_SD_B0_05_FLEXPWM1_PWMB02, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_B10:  afio_init(IOMUXC_GPIO_AD_B0_10_FLEXPWM1_PWMA03, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_C16:  afio_init(IOMUXC_GPIO_B1_00_FLEXPWM1_PWMA03,    0, PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHA_D0 :  afio_init(IOMUXC_GPIO_SD_B1_00_FLEXPWM1_PWMA03, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_B11:  afio_init(IOMUXC_GPIO_AD_B0_11_FLEXPWM1_PWMB03, 0, PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_C17:  afio_init(IOMUXC_GPIO_B1_01_FLEXPWM1_PWMB03,    0, PWM_PIN_CONF); break;
        case PWM1_MODULE3_CHB_D1 :  afio_init(IOMUXC_GPIO_SD_B1_01_FLEXPWM1_PWMB03, 0, PWM_PIN_CONF); break;
                                                   
        case PWM2_MODULE0_CHA_C6 :  afio_init(IOMUXC_GPIO_B0_06_FLEXPWM2_PWMA00 ,   0, PWM_PIN_CONF); break;
        case PWM2_MODULE0_CHB_C7 :  afio_init(IOMUXC_GPIO_B0_07_FLEXPWM2_PWMB00 ,   0, PWM_PIN_CONF); break;
        case PWM2_MODULE1_CHA_C8 :  afio_init(IOMUXC_GPIO_B0_08_FLEXPWM2_PWMA01 ,   0, PWM_PIN_CONF); break;
        case PWM2_MODULE1_CHB_C9 :  afio_init(IOMUXC_GPIO_B0_09_FLEXPWM2_PWMB01 ,   0, PWM_PIN_CONF); break;
        case PWM2_MODULE2_CHA_C10:  afio_init(IOMUXC_GPIO_B0_10_FLEXPWM2_PWMA02,    0, PWM_PIN_CONF); break;
        case PWM2_MODULE2_CHB_C11:  afio_init(IOMUXC_GPIO_B0_11_FLEXPWM2_PWMB02,    0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_B0 :  afio_init(IOMUXC_GPIO_AD_B0_00_FLEXPWM2_PWMA03, 0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_C18:  afio_init(IOMUXC_GPIO_B1_02_FLEXPWM2_PWMA03,    0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_D2 :  afio_init(IOMUXC_GPIO_SD_B1_02_FLEXPWM2_PWMA03, 0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHA_B9 :  afio_init(IOMUXC_GPIO_AD_B0_09_FLEXPWM2_PWMA03, 0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHB_B1 :  afio_init(IOMUXC_GPIO_AD_B0_01_FLEXPWM2_PWMB03, 0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHB_C19:  afio_init(IOMUXC_GPIO_B1_03_FLEXPWM2_PWMB03,    0, PWM_PIN_CONF); break;
        case PWM2_MODULE3_CHB_D3 :  afio_init(IOMUXC_GPIO_SD_B1_03_FLEXPWM2_PWMB03, 0, PWM_PIN_CONF); break;
                                                   
        case PWM4_MODULE0_CHA_B24:  afio_init(IOMUXC_GPIO_AD_B1_08_FLEXPWM4_PWMA00, 0, PWM_PIN_CONF); break;
        case PWM4_MODULE1_CHA_B25:  afio_init(IOMUXC_GPIO_AD_B1_09_FLEXPWM4_PWMA01, 0, PWM_PIN_CONF); break;
        case PWM4_MODULE2_CHA_C30:  afio_init(IOMUXC_GPIO_B1_14_FLEXPWM4_PWMA02,    0, PWM_PIN_CONF); break;
        case PWM4_MODULE3_CHA_C31:  afio_init(IOMUXC_GPIO_B1_15_FLEXPWM4_PWMA03,    0, PWM_PIN_CONF); break;

        default :zf_assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM 更新占空比
// 参数说明     pin             选择 PWM 引脚
// 参数说明     duty            设置占空比
// 返回参数     void
// 使用示例     pwm_set_duty(PWM1_MODULE0_CHB_D13, PWM_DUTY_MAX / 4);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty (pwm_channel_enum pin, const uint32 duty)
{
    uint16 temp_duty;
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);                                            // 占空比写入错误

    uint8  pwm_num;
    uint8  pwm_module;
    uint8  pwm_module_ch;
    
    pwm_num = pin/40;                                                           // 计算模块编号
    pwm_module = pin%40/10;                                                     // 计算子模块编号
    pwm_module_ch = pin%40%10/5;                                                // 计算子模块的通道
    
    temp_duty = (uint32)duty * 65535/ PWM_DUTY_MAX;
    // 清除LOAD OKAY位  以设置新的参数
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_UpdatePwmDutycycleHighAccuracy(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, (pwm_channels_t)(pwm_module_ch), kPWM_EdgeAligned, temp_duty);
    // 设置LOAD OKAY位  以更新设置
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PWM 初始化
// 参数说明     pin             选择 PWM 引脚
// 参数说明     freq            设置频率 同个模块只有最后一次设置生效
// 参数说明     duty            设置占空比
// 返回参数     void
// 使用示例     pwm_init(PWM1_MODULE0_CHB_D13, 17000, PWM_DUTY_MAX / 2);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pwm_init (pwm_channel_enum pin, const uint32 freq, const uint32 duty)
{
    // 如果是这一行报错 那你得去看看最大占空比是限定的多少 占空比写入错误
    zf_assert(PWM_DUTY_MAX >= duty);

    uint8  pwm_num;
    uint8  pwm_module;
    uint8  pwm_module_ch;
    uint32 temp_prsc;
    pwm_config_t pwmConfig;
    
    pwm_iomuxc(pin);

    //pwmConfig.enableDebugMode = false;
    //pwmConfig.enableWait = false;
    //pwmConfig.reloadSelect = kPWM_LocalReload;
    //pwmConfig.faultFilterCount = 0;
    //pwmConfig.faultFilterPeriod = 0;
    //pwmConfig.clockSource = kPWM_BusClock;
    //pwmConfig.prescale = kPWM_Prescale_Divide_1;
    //pwmConfig.initializationControl = kPWM_Initialize_LocalSync;
    //pwmConfig.forceTrigger = kPWM_Force_Local;
    //pwmConfig.reloadFrequency = kPWM_LoadEveryOportunity;
    //pwmConfig.reloadLogic = kPWM_ReloadImmediate;
    //pwmConfig.pairOperation = kPWM_Independent;

    PWM_GetDefaultConfig(&pwmConfig);

    pwmConfig.reloadLogic = kPWM_ReloadPwmFullCycle;
    pwmConfig.pairOperation = kPWM_Independent;
    pwmConfig.enableDebugMode = true;
    

    //计算分频系数
    temp_prsc = (PWM_SRC_CLK_FREQ/freq)>>16;
	if(PWM_SRC_CLK_FREQ%(freq<<16))	temp_prsc++;

    if      (1   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_1;
    else if (2   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_2;
    else if (4   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_4;
    else if (8   >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_8;
    else if (16  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_16;
    else if (32  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_32;
    else if (64  >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_64;
    else if (128 >= temp_prsc)  pwmConfig.prescale = kPWM_Prescale_Divide_128;
    else
    {
        zf_assert(0) ;                                                      // 频率过小 或者IPG频率过高
    }

    pwm_num = pin/40;                                                       // 计算模块编号
    pwm_module = pin%40/10;                                                 // 计算子模块编号
    pwm_module_ch = pin%40%10/5;                                            // 计算子模块的通道

    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)
    {
        zf_assert(0) ;                                                      // 初始化失败
    }
    PWM_Deinit(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module);
    
    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)
    {
        zf_assert(0) ;                                                      //初始化失败
    }
 
    // 设置频率占空比等参数
    pwm_signal_param_t pwmSignal;

    pwmSignal.pwmChannel = (pwm_channels_t)(pwm_module_ch); 
    pwmSignal.level = kPWM_HighTrue;
    pwmSignal.dutyCyclePercent = 0;
    pwmSignal.deadtimeValue = 0;

    // 清除LOAD OKAY位  以设置新的参数
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_SetupPwm(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmSignal, 1, kPWM_EdgeAligned, freq, PWM_SRC_CLK_FREQ);     
    //设置LOAD OKAY位  以更新设置
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);

    // 启动定时器
    PWM_StartTimer(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)));
    
    PWMPTR[pwm_num]->SM[pwm_module].DISMAP[0]=0;

    pwm_set_duty(pin, duty);
}
