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
* 文件名称          zf_driver_adc
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

#ifndef _zf_driver_adc_h_
#define _zf_driver_adc_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举 ADC 引脚通道  此枚举定义不允许用户修改
{
    ADC1_CH0_B27 = 1*16,    
    ADC1_CH1_B12,    
    ADC1_CH2_B13,    
    ADC1_CH3_B14,    
    ADC1_CH4_B15,    
    ADC1_CH5_B16,    
    ADC1_CH6_B17,    
    ADC1_CH7_B18,        
    ADC1_CH8_B19,        
    ADC1_CH9_B20,        
    ADC1_CH10_B21,       
    ADC1_CH11_B22,
    ADC1_CH12_B23,
    ADC1_CH13_B24,
    ADC1_CH14_B25,
    ADC1_CH15_B26,
    
    ADC2_CH0_B27,    
    ADC2_CH1_B28,    
    ADC2_CH2_B29,    
    ADC2_CH3_B30,    
    ADC2_CH4_B31,    
    ADC2_CH5_B16,    
    ADC2_CH6_B17,    
    ADC2_CH7_B18,        
    ADC2_CH8_B19,        
    ADC2_CH9_B20,        
    ADC2_CH10_B21,       
    ADC2_CH11_B22,
    ADC2_CH12_B23,
    ADC2_CH13_B24,
    ADC2_CH14_B25,
    ADC2_CH15_B26,
}adc_channel_enum;

typedef enum                                                                    // 枚举 ADC 分辨率   此枚举定义不允许用户修改
{
    ADC_8BIT,                                                                   // 8位分辨率
    ADC_10BIT,                                                                  // 10位分辨率
    ADC_12BIT,                                                                  // 12位分辨率
}adc_resolution_enum;

uint16      adc_convert             (adc_channel_enum ch);
uint16      adc_mean_filter_convert (adc_channel_enum ch, const uint8 count);
void        adc_init                (adc_channel_enum ch, adc_resolution_enum resolution);

#endif
