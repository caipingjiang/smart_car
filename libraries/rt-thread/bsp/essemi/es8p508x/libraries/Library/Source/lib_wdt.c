/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *�ļ�����  lib_wdt.c
 *��  �ߣ�  Liut
 *��  ����  V1.00
 *��  �ڣ�  2017/02/04
 *��  ����  ���Ź�ģ��⺯��
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#include "lib_wdt.h"

/*************************************
  ��������IWDT_Init
  ��  ����IWDT��ʼ��
  ����ֵ����ʼ���ṹ��
  ����ֵ����
 **************************************/
void IWDT_Init(IWDT_InitStruType *WDT_InitStruct)
{
    uint32_t tmp;

    if (WDT_InitStruct->WDT_Clock != WDT_CLOCK_PCLK)
        tmp = (uint32_t)(32 * WDT_InitStruct->WDT_Tms);
    else
        tmp = SystemCoreClock / 1000 * WDT_InitStruct->WDT_Tms;

    IWDT->LOAD.LOAD = tmp;
    IWDT->CON.CLKS = WDT_InitStruct->WDT_Clock;
    IWDT->CON.IE = WDT_InitStruct->WDT_IE;
    IWDT->CON.RSTEN = WDT_InitStruct->WDT_Rst;

    return;
}

/*************************************
  ��������IWDT_SetReloadValue
  ��  ��������WDT���صĳ�ֵ
  ����ֵ����ʼֵ��32-bit�޷�������
  ����ֵ����
 **************************************/
void IWDT_SetReloadValue(uint32_t Value)
{
    IWDT->LOAD.LOAD = Value;
    return;
}

/*************************************
  ��������IWDT_GetValue
  ��  ������ȡWDT��ǰֵ
  ����ֵ����
  ����ֵ����ǰֵ
 **************************************/
uint32_t IWDT_GetValue(void)
{
    return (uint32_t)IWDT->VALUE.VALUE;
}

/*************************************
  ��������IWDT_GetFlagStatus
  ��  ������ȡWDT�ж�״̬
  ����ֵ����
  ����ֵ��SET/RESET
 **************************************/
FlagStatus IWDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (IWDT->RIS.WDTIF != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  ��������IWDT_GetITStatus
  ��  ������ȡWDTʹ���ж�״̬
  ����ֵ����
  ����ֵ��SET/RESET
 **************************************/
FlagStatus IWDT_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (IWDT->CON.IE != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  ��������WWDT_Init
  ��  ����WWDT��ʼ��
  ����ֵ����ʼ���ṹ��
  ����ֵ����
 **************************************/
void WWDT_Init(WWDT_InitStruType *WDT_InitStruct)
{
    uint32_t tmp;

    if (WDT_InitStruct->WDT_Clock != WDT_CLOCK_PCLK)
        tmp = (uint32_t)(32 * WDT_InitStruct->WDT_Tms);
    else
        tmp = SystemCoreClock / 1000 * WDT_InitStruct->WDT_Tms;

    WWDT->LOAD.LOAD = tmp;
    WWDT->CON.CLKS = WDT_InitStruct->WDT_Clock;
    WWDT->CON.IE = WDT_InitStruct->WDT_IE;
    WWDT->CON.RSTEN = WDT_InitStruct->WDT_Rst;
    WWDT->CON.WWDTWIN = WDT_InitStruct->WDT_Win;

    return;
}

/*************************************
  ��������WWDT_SetReloadValue
  ��  ��������WDT���صĳ�ֵ
  ����ֵ����ʼֵ��32-bit�޷�������
  ����ֵ����
 **************************************/
void WWDT_SetReloadValue(uint32_t Value)
{
    WWDT->LOAD.LOAD = Value;
    return;
}

/*************************************
  ��������WWDT_GetValue
  ��  ������ȡWDT��ǰֵ
  ����ֵ����
  ����ֵ����ǰֵ
 **************************************/
uint32_t WWDT_GetValue(void)
{
    return (uint32_t)WWDT->VALUE.VALUE;
}

/*************************************
  ��������WWDT_GetFlagStatus
  ��  ������ȡWDT�ж�״̬
  ����ֵ����
  ����ֵ��SET/RESET
 **************************************/
FlagStatus WWDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (WWDT->RIS.WWDTIF != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  ��������WWDT_GetIEStatus
  ��  ������ȡWDT�ж�ʹ��״̬
  ����ֵ����
  ����ֵ��SET/RESET
 **************************************/
FlagStatus WWDT_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (WWDT->CON.IE != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************END OF FILE**********************/


