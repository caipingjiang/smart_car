/*********************************************************************************************************************
* MCX Vision Opensourec Library ����MCX Vision ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2024 SEEKFREE ��ɿƼ�
* 
* ���ļ��� MCX Vision ��Դ���һ����
* 
* MCX Vision ��Դ�� ��������
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
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_delay
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.38a
* ����ƽ̨          MCX Vision
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_driver_delay.h"


#define SYSTEM_DELAY_LPTMR 					LPTMR0	                                    // ѡ��ʹ�õ�GPT��ʱ��

//-------------------------------------------------------------------------------------------------------------------
// �������     system ��ʱ���� ms ����
// ����˵��     time        ��Ҫ��ʱ��ʱ�� ms ����
// ���ز���     void
// ʹ��ʾ��     system_delay_ms(100);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void system_delay_ms (uint32_t time)
{
    while(time --)
    {
        LPTMR_SetTimerPeriod(SYSTEM_DELAY_LPTMR, MSEC_TO_COUNT(1, 16000));
        LPTMR_StartTimer(SYSTEM_DELAY_LPTMR);   // ������ʱ��
        while(!LPTMR_GetStatusFlags(SYSTEM_DELAY_LPTMR));
        LPTMR_ClearStatusFlags(SYSTEM_DELAY_LPTMR, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(SYSTEM_DELAY_LPTMR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     system ��ʱ���� us ����
// ����˵��     time        ��Ҫ��ʱ��ʱ�� us ����
// ���ز���     void
// ʹ��ʾ��     system_delay_us(100);
// ��ע��Ϣ     �����ڳ���������ת ����ʱ�������ֵ�߳�һЩ
//-------------------------------------------------------------------------------------------------------------------
void system_delay_us (uint32_t time)
{
    while(time --)
    {
        LPTMR_SetTimerPeriod(SYSTEM_DELAY_LPTMR, USEC_TO_COUNT(1, 16000));
        LPTMR_StartTimer(SYSTEM_DELAY_LPTMR);   // ������ʱ��
        while(!LPTMR_GetStatusFlags(SYSTEM_DELAY_LPTMR));
        LPTMR_ClearStatusFlags(SYSTEM_DELAY_LPTMR, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(SYSTEM_DELAY_LPTMR);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      lptmr��Ϊ��ʱ��ʼ��
//  @param      void            
//  @return     void
//  Sample usage:               �����û�����
//-------------------------------------------------------------------------------------------------------------------
void system_delay_init(void)
{
    lptmr_config_t lptmrConfig;
    
    CLOCK_SetupClk16KClocking(kCLOCK_Clk16KToVsys);
    LPTMR_GetDefaultConfig(&lptmrConfig);     
    
    LPTMR_Init(SYSTEM_DELAY_LPTMR, &lptmrConfig);       
    LPTMR_Deinit(SYSTEM_DELAY_LPTMR);                                       
    LPTMR_Init(SYSTEM_DELAY_LPTMR, &lptmrConfig);       
    
    EnableIRQ(LPTMR0_IRQn);       
}