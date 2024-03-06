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

#ifndef _zf_driver_pwm_h_
#define _zf_driver_pwm_h_

#include "zf_common_typedef.h"

#define PWM_DUTY_MAX        (10000)                                                                     // PWM占空比最大值 可根据需求自行修改

typedef enum                                                                                            // 枚举 PWM 通道 此枚举定义不允许用户修改
{
    //同一个子模块不同通道只能输出相同频率的PWM，占空比可设置不同
    //例如PWM1_MODULE0_CHB与PWM1_MODULE0_CHA属于同一个子模块，频率只能一样，但是占空比可以不一样
    //PWM1_MODULE0_CHA_D12与PWM1_MODULE1_CHA_D14虽然是同一个PWM模块但是属于不同的子模块可以输出不同频率的PWM
    
    PWM1_MODULE0_CHB_D13=1*40+5*0,                                                                      // PWM1 子模块0 通道B  引脚可选范围
    PWM1_MODULE0_CHA_D12=1*40+5*1,                                                                      // PWM1 子模块0 通道A  引脚可选范围 
                                                                                                            
    PWM1_MODULE1_CHB_D15=1*40+5*2,                                                                      // PWM1 子模块1 通道B  引脚可选范围
    PWM1_MODULE1_CHA_D14=1*40+5*3,                                                                      // PWM1 子模块1 通道A  引脚可选范围
                                                                                                            
    PWM1_MODULE2_CHB_D17=1*40+5*4,                                                                      // PWM1 子模块2 通道B  引脚可选范围
    PWM1_MODULE2_CHA_D16=1*40+5*5,                                                                      // PWM1 子模块2 通道A  引脚可选范围

    PWM1_MODULE3_CHB_B11=1*40+5*6,  PWM1_MODULE3_CHB_C17,   PWM1_MODULE3_CHB_D1,                        // PWM1 子模块3 通道B  引脚可选范围
    PWM1_MODULE3_CHA_B10=1*40+5*7,  PWM1_MODULE3_CHA_C16,   PWM1_MODULE3_CHA_D0,                        // PWM1 子模块3 通道A  引脚可选范围
    
    //-----------------------------------------------------------------------------
    PWM2_MODULE0_CHB_C7 =2*40+5*0,                                                                      // PWM2 子模块0 通道B  引脚可选范围
    PWM2_MODULE0_CHA_C6 =2*40+5*1,                                                                      // PWM2 子模块0 通道A  引脚可选范围
                                                                                                            
    PWM2_MODULE1_CHB_C9 =2*40+5*2,                                                                      // PWM2 子模块1 通道B  引脚可选范围
    PWM2_MODULE1_CHA_C8 =2*40+5*3,                                                                      // PWM2 子模块1 通道A  引脚可选范围
                                                                                                            
    PWM2_MODULE2_CHB_C11=2*40+5*4,                                                                      // PWM2 子模块2 通道B  引脚可选范围
    PWM2_MODULE2_CHA_C10=2*40+5*5,                                                                      // PWM2 子模块2 通道A  引脚可选范围
                        
    PWM2_MODULE3_CHB_B1 =2*40+5*6,  PWM2_MODULE3_CHB_C19,   PWM2_MODULE3_CHB_D3,                        // PWM2 子模块3 通道B  引脚可选范围
    PWM2_MODULE3_CHA_B0 =2*40+5*7,  PWM2_MODULE3_CHA_C18,   PWM2_MODULE3_CHA_D2,    PWM2_MODULE3_CHA_B9,// PWM2 子模块3 通道A  引脚可选范围
    
    //-----------------------------------------------------------------------------
    //PWM3模块的引脚全部被SDRAM所占用
    
    //-----------------------------------------------------------------------------
    PWM4_MODULE0_CHA_B24=4*40+5*1,                                                                      // PWM4 子模块0 通道A  引脚可选范围
                                                                                                           
    PWM4_MODULE1_CHA_B25=4*40+5*3,                                                                      // PWM4 子模块1 通道A  引脚可选范围
                                                                                                           
    PWM4_MODULE2_CHA_C30=4*40+5*5,                                                                      // PWM4 子模块2 通道A  引脚可选范围
                                                                                                           
    PWM4_MODULE3_CHA_C31=4*40+5*7,                                                                      // PWM4 子模块3 通道A  引脚可选范围
}pwm_channel_enum;


void    pwm_set_duty    (pwm_channel_enum pin, const uint32 duty);
void    pwm_init        (pwm_channel_enum pin, const uint32 freq, const uint32 duty);

#endif
