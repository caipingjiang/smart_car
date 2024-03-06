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
* �ļ�����          zf_driver_delay
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
// ------------------
//��ֲrt-tread
//-------------------
#include "rtthread.h"

#include "zf_common_clock.h"
#include "fsl_gpt.h"

#include "zf_driver_delay.h"

#define SYSTEM_DELAY_GPT 					GPT2	                                    // ѡ��ʹ�õ�GPT��ʱ��

//-------------------------------------------------------------------------------------------------------------------
// �������     system ��ʱ���� ms ����
// ����˵��     time        ��Ҫ��ʱ��ʱ�� ms ����
// ���ز���     void
// ʹ��ʾ��     system_delay_ms(100);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void system_delay_ms (uint32 time)
{
    while(time --)
    {
        GPT_SetOutputCompareValue(SYSTEM_DELAY_GPT, kGPT_OutputCompare_Channel1, BOARD_XTAL_FREQ/1000);
        GPT_StartTimer(SYSTEM_DELAY_GPT);   // ������ʱ��
        while(!GPT_GetStatusFlags(SYSTEM_DELAY_GPT, kGPT_OutputCompare1Flag));
        GPT_ClearStatusFlags(SYSTEM_DELAY_GPT, kGPT_OutputCompare1Flag);
        GPT_StopTimer(SYSTEM_DELAY_GPT);
    }

}

//-------------------------------------------------------------------------------------------------------------------
// �������     system ��ʱ���� us ����
// ����˵��     time        ��Ҫ��ʱ��ʱ�� us ����
// ���ز���     void
// ʹ��ʾ��     system_delay_us(100);
// ��ע��Ϣ     �����ڳ���������ת ����ʱ�������ֵ�߳�һЩ
//-------------------------------------------------------------------------------------------------------------------
void system_delay_us (uint32 time)
{
    while(time --)
    {
        GPT_SetOutputCompareValue(SYSTEM_DELAY_GPT, kGPT_OutputCompare_Channel1, BOARD_XTAL_FREQ / 1000 / 1000);
        GPT_StartTimer(SYSTEM_DELAY_GPT);   // ������ʱ��
        while(!GPT_GetStatusFlags(SYSTEM_DELAY_GPT, kGPT_OutputCompare1Flag));
        GPT_ClearStatusFlags(SYSTEM_DELAY_GPT, kGPT_OutputCompare1Flag);
        GPT_StopTimer(SYSTEM_DELAY_GPT);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      gpt��Ϊ��ʱ��ʼ��
//  @param      void            
//  @return     void
//  Sample usage:               �����û�����
//-------------------------------------------------------------------------------------------------------------------
void system_delay_init(void)
{
    gpt_config_t gptConfig;
    
    GPT_GetDefaultConfig(&gptConfig);                                                   // ��ȡĬ������
    gptConfig.clockSource = kGPT_ClockSource_Osc;
    gptConfig.divider = 1;
    GPT_Init(SYSTEM_DELAY_GPT, &gptConfig);                                             // GPT��ʼ�� ���ڴ�ʱ��
    GPT_Deinit(SYSTEM_DELAY_GPT);                                                       // GPT����ʼ��
    GPT_Init(SYSTEM_DELAY_GPT, &gptConfig);                                             // GPT��ʼ��
}