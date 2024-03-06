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
* 文件名称          zf_driver_pit
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

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"


#include "zf_driver_pit.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 中断使能
// 参数说明     pit_chn             PIT 外设模块号
// 返回参数     void
// 使用示例     pit_enable(PIT_CH0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pit_enable (pit_index_enum pit_chn)
{
    PIT_StartTimer(PIT, (pit_chnl_t)pit_chn);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 中断禁止
// 参数说明     pit_chn             PIT 外设模块号
// 返回参数     void
// 使用示例     pit_disable(PIT_CH0);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pit_disable (pit_index_enum pit_chn)
{
    PIT_StopTimer(PIT, (pit_chnl_t)pit_chn);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 初始化 一般调用 pit_ms_init 或 pit_us_init
// 参数说明     pit_chn             PIT 外设模块号
// 参数说明     period              PIT 周期 一般是芯片或者模块时钟频率计算
// 返回参数     void
// 使用示例     pit_init(PIT_CH0, 120);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void pit_init (pit_index_enum pit_chn, uint32 period)
{
    static uint8 init_flag;
    
    if(0 == init_flag)
    {
        init_flag = 1;
        pit_config_t pitConfig;
    
        PIT_GetDefaultConfig(&pitConfig);   //默认配置为false
                  
        PIT_Init(PIT, &pitConfig);          //第一次初始化便于打开时钟
        PIT_Deinit(PIT);                    //复位外设
        PIT_Init(PIT, &pitConfig);          //重新初始化设置正确的参数
    }
    
    
    PIT_SetTimerPeriod(PIT, (pit_chnl_t)pit_chn, period);
    PIT_EnableInterrupts(PIT, (pit_chnl_t)pit_chn, kPIT_TimerInterruptEnable);//打开PIT通道0中断
	PIT_SetTimerChainMode(PIT, (pit_chnl_t)pit_chn, false);
    PIT_StartTimer(PIT, (pit_chnl_t)pit_chn);
    EnableIRQ(PIT_IRQn);
}
