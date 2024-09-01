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
* 文件名称          zf_driver_delay
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
#include "zf_driver_delay.h"


#define SYSTEM_DELAY_LPTMR 					LPTMR0	                                    // 选择使用的GPT定时器

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     system 延时函数 ms 级别
// 参数说明     time        需要延时的时间 ms 级别
// 返回参数     void
// 使用示例     system_delay_ms(100);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void system_delay_ms (uint32_t time)
{
    while(time --)
    {
        LPTMR_SetTimerPeriod(SYSTEM_DELAY_LPTMR, MSEC_TO_COUNT(1, 16000));
        LPTMR_StartTimer(SYSTEM_DELAY_LPTMR);   // 启动定时器
        while(!LPTMR_GetStatusFlags(SYSTEM_DELAY_LPTMR));
        LPTMR_ClearStatusFlags(SYSTEM_DELAY_LPTMR, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(SYSTEM_DELAY_LPTMR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     system 延时函数 us 级别
// 参数说明     time        需要延时的时间 us 级别
// 返回参数     void
// 使用示例     system_delay_us(100);
// 备注信息     受限于程序运行跳转 此延时会比输入值高出一些
//-------------------------------------------------------------------------------------------------------------------
void system_delay_us (uint32_t time)
{
    while(time --)
    {
        LPTMR_SetTimerPeriod(SYSTEM_DELAY_LPTMR, USEC_TO_COUNT(1, 16000));
        LPTMR_StartTimer(SYSTEM_DELAY_LPTMR);   // 启动定时器
        while(!LPTMR_GetStatusFlags(SYSTEM_DELAY_LPTMR));
        LPTMR_ClearStatusFlags(SYSTEM_DELAY_LPTMR, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(SYSTEM_DELAY_LPTMR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      lptmr作为延时初始化
//  @param      void            
//  @return     void
//  Sample usage:               无需用户调用
//-------------------------------------------------------------------------------------------------------------------
void system_delay_init(void)
{
    lptmr_config_t lptmrConfig;
    
    CLOCK_SetupClk16KClocking(kCLOCK_Clk16KToVsys);
    LPTMR_GetDefaultConfig(&lptmrConfig);     
    
    LPTMR_Init(SYSTEM_DELAY_LPTMR, &lptmrConfig);       
    LPTMR_Deinit(SYSTEM_DELAY_LPTMR);                                       
    LPTMR_Init(SYSTEM_DELAY_LPTMR, &lptmrConfig);       
    
    EnableIRQ(LPTMR0_IRQn);       
}