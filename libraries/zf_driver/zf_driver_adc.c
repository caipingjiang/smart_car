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

#include "fsl_adc.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_adc.h"

static  ADC_Type    *adc_index[]        = ADC_BASE_PTRS;


void adc_iomuxc(adc_channel_enum ch)
{
    switch(ch)
    {
        case ADC1_CH0_B27:
        case ADC2_CH0_B27:  gpio_iomuxc(B27 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH1_B12:  gpio_iomuxc(B12 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH2_B13:  gpio_iomuxc(B13 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH3_B14:  gpio_iomuxc(B14 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH4_B15:  gpio_iomuxc(B15 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH5_B16:
        case ADC2_CH5_B16:  gpio_iomuxc(B16 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH6_B17:
        case ADC2_CH6_B17:  gpio_iomuxc(B17 ,GPI_ANAOG_IN);break;
        
        case ADC2_CH7_B18:
        case ADC1_CH7_B18:  gpio_iomuxc(B18 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH8_B19:
        case ADC2_CH8_B19:  gpio_iomuxc(B19 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH9_B20:  
        case ADC2_CH9_B20:  gpio_iomuxc(B20 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH10_B21:  
        case ADC2_CH10_B21: gpio_iomuxc(B21 ,GPI_ANAOG_IN);break;
                            
        case ADC1_CH11_B22: 
        case ADC2_CH11_B22: gpio_iomuxc(B22 ,GPI_ANAOG_IN);break;
                            
        case ADC1_CH12_B23: 
        case ADC2_CH12_B23: gpio_iomuxc(B23 ,GPI_ANAOG_IN);break;
                            
        case ADC1_CH13_B24: 
        case ADC2_CH13_B24: gpio_iomuxc(B24 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH14_B25:  
        case ADC2_CH14_B25: gpio_iomuxc(B25 ,GPI_ANAOG_IN);break;
        
        case ADC1_CH15_B26:  
        case ADC2_CH15_B26: gpio_iomuxc(B26 ,GPI_ANAOG_IN);break;
        
        case ADC2_CH1_B28:  gpio_iomuxc(B28 ,GPI_ANAOG_IN);break;
        
        case ADC2_CH2_B29:  gpio_iomuxc(B29 ,GPI_ANAOG_IN);break;
        
        case ADC2_CH3_B30:  gpio_iomuxc(B30 ,GPI_ANAOG_IN);break;
        
        case ADC2_CH4_B31:  gpio_iomuxc(B31 ,GPI_ANAOG_IN);break;
        
        default:assert(0);break;
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 转换一次
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 返回参数     uint16          转换的 adc 值
// 使用示例     adc_convert(ADC1_CH0_B27);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert (adc_channel_enum ch)
{
    adc_channel_config_t adcChannelConfigStruct;
    
    adcChannelConfigStruct.channelNumber = ch&0xf;
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;
    
    ADC_SetChannelConfig(adc_index[ch / 16], 0, &adcChannelConfigStruct);
    while (0U == ADC_GetChannelStatusFlags(adc_index[ch / 16], 0));
    return ADC_GetChannelConversionValue(adc_index[ch / 16], 0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 均值滤波转换
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     count           均值滤波次数
// 返回参数     uint16          转换的 adc 值
// 使用示例     adc_mean_filter_convert(ADC1_CH0_B27, 5);                        // 采集5次 然后返回平均值
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum ch, const uint8 count)
{
    uint8 i = 0;
    uint32 sum = 0;

    for(i = 0; i < count; i ++)
    {
        sum += adc_convert(ch);
    }

    return (sum / count);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     adc 初始化
// 参数说明     ch              选择 adc 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     resolution      选择选择通道分辨率(如果同一个 adc 模块初始化时设置了不同的分辨率 则最后一个初始化的分辨率生效)
// 返回参数     void
// 使用示例     adc_init(ADC1_CH0_B27, ADC_8BIT);                                // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum ch, adc_resolution_enum resolution)
{
    adc_config_t adcConfigStrcut;

    adc_iomuxc(ch);
    
    /*
    *  config->enableAsynchronousClockOutput = true;
     *  config->enableOverWrite =               false;
       *  config->enableContinuousConversion =    false;
       *  config->enableHighSpeed =               false;
       *  config->enableLowPower =                false;
       *  config->enableLongSample =              false;
       *  config->referenceVoltageSource =        kADC_ReferenceVoltageSourceVref;
       *  config->samplePeriodMode =              kADC_SamplePeriod2or12Clocks;
       *  config->clockSource =                   kADC_ClockSourceAD;
       *  config->clockDriver =                   kADC_ClockDriver1;
       */
    ADC_GetDefaultConfig(&adcConfigStrcut);
    adcConfigStrcut.resolution = (adc_resolution_t)(resolution);
    ADC_Init(adc_index[ch / 16], &adcConfigStrcut);
    if (kStatus_Success == ADC_DoAutoCalibration(adc_index[ch / 16]));
    else    zf_assert(0);
}
