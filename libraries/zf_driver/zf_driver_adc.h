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

#ifndef _zf_driver_adc_h_
#define _zf_driver_adc_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // ö�� ADC ����ͨ��  ��ö�ٶ��岻�����û��޸�
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

typedef enum                                                                    // ö�� ADC �ֱ���   ��ö�ٶ��岻�����û��޸�
{
    ADC_8BIT,                                                                   // 8λ�ֱ���
    ADC_10BIT,                                                                  // 10λ�ֱ���
    ADC_12BIT,                                                                  // 12λ�ֱ���
}adc_resolution_enum;

uint16      adc_convert             (adc_channel_enum ch);
uint16      adc_mean_filter_convert (adc_channel_enum ch, const uint8 count);
void        adc_init                (adc_channel_enum ch, adc_resolution_enum resolution);

#endif
