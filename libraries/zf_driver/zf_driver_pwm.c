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

#include "fsl_pwm.h"
#include "fsl_iomuxc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"

#include "zf_driver_pwm.h"

#define PWM_SRC_CLK_FREQ    CLOCK_GetFreq(kCLOCK_IpgClk)                        // ����PWM����ʱ��ԴƵ��
#define PWM_PIN_CONF        SPEED_100MHZ | KEEPER_EN | DSE_R0_6                 // ����PWM����Ĭ������   

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
// �������     PWM ����ռ�ձ�
// ����˵��     pin             ѡ�� PWM ����
// ����˵��     duty            ����ռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_set_duty(PWM1_MODULE0_CHB_D13, PWM_DUTY_MAX / 4);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_duty (pwm_channel_enum pin, const uint32 duty)
{
    uint16 temp_duty;
    // �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
    zf_assert(PWM_DUTY_MAX >= duty);                                            // ռ�ձ�д�����

    uint8  pwm_num;
    uint8  pwm_module;
    uint8  pwm_module_ch;
    
    pwm_num = pin/40;                                                           // ����ģ����
    pwm_module = pin%40/10;                                                     // ������ģ����
    pwm_module_ch = pin%40%10/5;                                                // ������ģ���ͨ��
    
    temp_duty = (uint32)duty * 65535/ PWM_DUTY_MAX;
    // ���LOAD OKAYλ  �������µĲ���
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_UpdatePwmDutycycleHighAccuracy(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, (pwm_channels_t)(pwm_module_ch), kPWM_EdgeAligned, temp_duty);
    // ����LOAD OKAYλ  �Ը�������
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     PWM ��ʼ��
// ����˵��     pin             ѡ�� PWM ����
// ����˵��     freq            ����Ƶ�� ͬ��ģ��ֻ�����һ��������Ч
// ����˵��     duty            ����ռ�ձ�
// ���ز���     void
// ʹ��ʾ��     pwm_init(PWM1_MODULE0_CHB_D13, 17000, PWM_DUTY_MAX / 2);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void pwm_init (pwm_channel_enum pin, const uint32 freq, const uint32 duty)
{
    // �������һ�б��� �����ȥ�������ռ�ձ����޶��Ķ��� ռ�ձ�д�����
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
    

    //�����Ƶϵ��
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
        zf_assert(0) ;                                                      // Ƶ�ʹ�С ����IPGƵ�ʹ���
    }

    pwm_num = pin/40;                                                       // ����ģ����
    pwm_module = pin%40/10;                                                 // ������ģ����
    pwm_module_ch = pin%40%10/5;                                            // ������ģ���ͨ��

    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)
    {
        zf_assert(0) ;                                                      // ��ʼ��ʧ��
    }
    PWM_Deinit(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module);
    
    if (PWM_Init(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmConfig) == kStatus_Fail)
    {
        zf_assert(0) ;                                                      //��ʼ��ʧ��
    }
 
    // ����Ƶ��ռ�ձȵȲ���
    pwm_signal_param_t pwmSignal;

    pwmSignal.pwmChannel = (pwm_channels_t)(pwm_module_ch); 
    pwmSignal.level = kPWM_HighTrue;
    pwmSignal.dutyCyclePercent = 0;
    pwmSignal.deadtimeValue = 0;

    // ���LOAD OKAYλ  �������µĲ���
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), false);
    PWM_SetupPwm(PWMPTR[pwm_num], (pwm_submodule_t)pwm_module, &pwmSignal, 1, kPWM_EdgeAligned, freq, PWM_SRC_CLK_FREQ);     
    //����LOAD OKAYλ  �Ը�������
    PWM_SetPwmLdok(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)), true);

    // ������ʱ��
    PWM_StartTimer(PWMPTR[pwm_num], (pwm_module_control_t)(1<<(pwm_module)));
    
    PWMPTR[pwm_num]->SM[pwm_module].DISMAP[0]=0;

    pwm_set_duty(pin, duty);
}
