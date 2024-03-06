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
* �ļ�����          zf_driver_timer
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

#include "fsl_gpt.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_timer.h"

GPT_Type *timer_index[] = GPT_BASE_PTRS;

//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER ��ʼ��ʱ
// ����˵��     index           TIMER ����ģ���
// ���ز���     void
// ʹ��ʾ��     timer_start(TIM_1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void timer_start (timer_index_enum index)
{
    GPT_StartTimer(timer_index[index]);                 // ������ʱ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER ֹͣ��ʱ
// ����˵��     index           TIMER ����ģ���
// ���ز���     void
// ʹ��ʾ��     timer_stop(TIM_1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void timer_stop (timer_index_enum index)
{
    GPT_StopTimer(timer_index[index]);                  // ֹͣ��ʱ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER ��ȡ��ʱ������
// ����˵��     index           TIMER ����ģ���
// ���ز���     uint16          ����ֵ
// ʹ��ʾ��     timer_get(TIM_1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint32 timer_get (timer_index_enum index)
{
    return GPT_GetCurrentTimerCount(timer_index[index]);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER �����ʱ������
// ����˵��     index           TIMER ����ģ���
// ���ز���     void
// ʹ��ʾ��     timer_clear(TIM_1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void timer_clear (timer_index_enum index)
{
    // ֻ�ڶ�ʱ���ѿ�����״̬���
    if(timer_index[index]->CR & GPT_CR_EN_MASK)
    {
        timer_stop(index);
        timer_start(index);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     TIMER ��ʱ����ʼ��
// ����˵��     index           TIMER ����ģ���
// ����˵��     mode            ��ʱ��ʽ
// ���ز���     void
// ʹ��ʾ��     timer_init(TIM_1, TIMER_US);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void timer_init (timer_index_enum index, timer_mode_enum mode)
{
    gpt_config_t gptConfig;
    
    GPT_GetDefaultConfig(&gptConfig);                   // ��ȡĬ������
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
        
    GPT_Init(timer_index[index], &gptConfig);           // GPT��ʼ�� ���ڴ�ʱ��
    GPT_Deinit(timer_index[index]);                     // GPT����ʼ��
    GPT_Init(timer_index[index], &gptConfig);           // GPT��ʼ��
    
    GPT_SetOscClockDivider(timer_index[index], 12);
}

