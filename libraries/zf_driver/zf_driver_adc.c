/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_adc
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
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
// �������     adc ת��һ��
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ���ز���     uint16          ת���� adc ֵ
// ʹ��ʾ��     adc_convert(ADC1_CH0_B27);
// ��ע��Ϣ     
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
// �������     adc ��ֵ�˲�ת��
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ����˵��     count           ��ֵ�˲�����
// ���ز���     uint16          ת���� adc ֵ
// ʹ��ʾ��     adc_mean_filter_convert(ADC1_CH0_B27, 5);                        // �ɼ�5�� Ȼ�󷵻�ƽ��ֵ
// ��ע��Ϣ     
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
// �������     adc ��ʼ��
// ����˵��     ch              ѡ�� adc ͨ�� (��� zf_driver_adc.h ��ö�� adc_channel_enum ����)
// ����˵��     resolution      ѡ��ѡ��ͨ���ֱ���(���ͬһ�� adc ģ���ʼ��ʱ�����˲�ͬ�ķֱ��� �����һ����ʼ���ķֱ�����Ч)
// ���ز���     void
// ʹ��ʾ��     adc_init(ADC1_CH0_B27, ADC_8BIT);                                // ��ʼ�� A0 Ϊ ADC1 �� channel0 ���빦�� �ֱ���Ϊ8λ
// ��ע��Ϣ     
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
