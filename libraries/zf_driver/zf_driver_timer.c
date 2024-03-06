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
* 文件名称          zf_driver_timer
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

#include "fsl_gpt.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_timer.h"

GPT_Type *timer_index[] = GPT_BASE_PTRS;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 开始计时
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_start(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_start (timer_index_enum index)
{
    GPT_StartTimer(timer_index[index]);                 // 启动定时器
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 停止计时
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_stop(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_stop (timer_index_enum index)
{
    GPT_StopTimer(timer_index[index]);                  // 停止定时器
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 获取计时器计数
// 参数说明     index           TIMER 外设模块号
// 返回参数     uint16          计数值
// 使用示例     timer_get(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint32 timer_get (timer_index_enum index)
{
    return GPT_GetCurrentTimerCount(timer_index[index]);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 清除计时器计数
// 参数说明     index           TIMER 外设模块号
// 返回参数     void
// 使用示例     timer_clear(TIM_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_clear (timer_index_enum index)
{
    // 只在定时器已开启的状态清除
    if(timer_index[index]->CR & GPT_CR_EN_MASK)
    {
        timer_stop(index);
        timer_start(index);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     TIMER 计时器初始化
// 参数说明     index           TIMER 外设模块号
// 参数说明     mode            计时方式
// 返回参数     void
// 使用示例     timer_init(TIM_1, TIMER_US);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void timer_init (timer_index_enum index, timer_mode_enum mode)
{
    gpt_config_t gptConfig;
    
    GPT_GetDefaultConfig(&gptConfig);                   // 获取默认配置
    switch(mode)
    {
        case TIMER_IPG1_2_CLOCK:
        {
            gptConfig.divider = 1;
        }break;
        
        case TIMER_US:
        {
            gptConfig.divider = CLOCK_GetFreq(kCLOCK_PerClk) / 1000000;
        }break;
        
        case TIMER_MS:
        {
            gptConfig.clockSource = kGPT_ClockSource_Osc;
            gptConfig.divider = BOARD_XTAL_FREQ / 12 / 1000;
            
        }break;
    }
        
    GPT_Init(timer_index[index], &gptConfig);           // GPT初始化 便于打开时钟
    GPT_Deinit(timer_index[index]);                     // GPT反初始化
    GPT_Init(timer_index[index], &gptConfig);           // GPT初始化
    
    GPT_SetOscClockDivider(timer_index[index], 12);
}

