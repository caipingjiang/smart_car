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
* �ļ�����          zf_driver_pwm
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

#ifndef _zf_driver_pwm_h_
#define _zf_driver_pwm_h_

#include "zf_common_typedef.h"

#define PWM_DUTY_MAX        (10000)                                                                     // PWMռ�ձ����ֵ �ɸ������������޸�

typedef enum                                                                                            // ö�� PWM ͨ�� ��ö�ٶ��岻�����û��޸�
{
    //ͬһ����ģ�鲻ͬͨ��ֻ�������ͬƵ�ʵ�PWM��ռ�ձȿ����ò�ͬ
    //����PWM1_MODULE0_CHB��PWM1_MODULE0_CHA����ͬһ����ģ�飬Ƶ��ֻ��һ��������ռ�ձȿ��Բ�һ��
    //PWM1_MODULE0_CHA_D12��PWM1_MODULE1_CHA_D14��Ȼ��ͬһ��PWMģ�鵫�����ڲ�ͬ����ģ����������ͬƵ�ʵ�PWM
    
    PWM1_MODULE0_CHB_D13=1*40+5*0,                                                                      // PWM1 ��ģ��0 ͨ��B  ���ſ�ѡ��Χ
    PWM1_MODULE0_CHA_D12=1*40+5*1,                                                                      // PWM1 ��ģ��0 ͨ��A  ���ſ�ѡ��Χ 
                                                                                                            
    PWM1_MODULE1_CHB_D15=1*40+5*2,                                                                      // PWM1 ��ģ��1 ͨ��B  ���ſ�ѡ��Χ
    PWM1_MODULE1_CHA_D14=1*40+5*3,                                                                      // PWM1 ��ģ��1 ͨ��A  ���ſ�ѡ��Χ
                                                                                                            
    PWM1_MODULE2_CHB_D17=1*40+5*4,                                                                      // PWM1 ��ģ��2 ͨ��B  ���ſ�ѡ��Χ
    PWM1_MODULE2_CHA_D16=1*40+5*5,                                                                      // PWM1 ��ģ��2 ͨ��A  ���ſ�ѡ��Χ

    PWM1_MODULE3_CHB_B11=1*40+5*6,  PWM1_MODULE3_CHB_C17,   PWM1_MODULE3_CHB_D1,                        // PWM1 ��ģ��3 ͨ��B  ���ſ�ѡ��Χ
    PWM1_MODULE3_CHA_B10=1*40+5*7,  PWM1_MODULE3_CHA_C16,   PWM1_MODULE3_CHA_D0,                        // PWM1 ��ģ��3 ͨ��A  ���ſ�ѡ��Χ
    
    //-----------------------------------------------------------------------------
    PWM2_MODULE0_CHB_C7 =2*40+5*0,                                                                      // PWM2 ��ģ��0 ͨ��B  ���ſ�ѡ��Χ
    PWM2_MODULE0_CHA_C6 =2*40+5*1,                                                                      // PWM2 ��ģ��0 ͨ��A  ���ſ�ѡ��Χ
                                                                                                            
    PWM2_MODULE1_CHB_C9 =2*40+5*2,                                                                      // PWM2 ��ģ��1 ͨ��B  ���ſ�ѡ��Χ
    PWM2_MODULE1_CHA_C8 =2*40+5*3,                                                                      // PWM2 ��ģ��1 ͨ��A  ���ſ�ѡ��Χ
                                                                                                            
    PWM2_MODULE2_CHB_C11=2*40+5*4,                                                                      // PWM2 ��ģ��2 ͨ��B  ���ſ�ѡ��Χ
    PWM2_MODULE2_CHA_C10=2*40+5*5,                                                                      // PWM2 ��ģ��2 ͨ��A  ���ſ�ѡ��Χ
                        
    PWM2_MODULE3_CHB_B1 =2*40+5*6,  PWM2_MODULE3_CHB_C19,   PWM2_MODULE3_CHB_D3,                        // PWM2 ��ģ��3 ͨ��B  ���ſ�ѡ��Χ
    PWM2_MODULE3_CHA_B0 =2*40+5*7,  PWM2_MODULE3_CHA_C18,   PWM2_MODULE3_CHA_D2,    PWM2_MODULE3_CHA_B9,// PWM2 ��ģ��3 ͨ��A  ���ſ�ѡ��Χ
    
    //-----------------------------------------------------------------------------
    //PWM3ģ�������ȫ����SDRAM��ռ��
    
    //-----------------------------------------------------------------------------
    PWM4_MODULE0_CHA_B24=4*40+5*1,                                                                      // PWM4 ��ģ��0 ͨ��A  ���ſ�ѡ��Χ
                                                                                                           
    PWM4_MODULE1_CHA_B25=4*40+5*3,                                                                      // PWM4 ��ģ��1 ͨ��A  ���ſ�ѡ��Χ
                                                                                                           
    PWM4_MODULE2_CHA_C30=4*40+5*5,                                                                      // PWM4 ��ģ��2 ͨ��A  ���ſ�ѡ��Χ
                                                                                                           
    PWM4_MODULE3_CHA_C31=4*40+5*7,                                                                      // PWM4 ��ģ��3 ͨ��A  ���ſ�ѡ��Χ
}pwm_channel_enum;


void    pwm_set_duty    (pwm_channel_enum pin, const uint32 duty);
void    pwm_init        (pwm_channel_enum pin, const uint32 freq, const uint32 duty);

#endif
