/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *�ļ�����  lib_timer.c
 *��  �ߣ�  Liut
 *��  ����  V1.00
 *��  �ڣ�  2017/07/14
 *��  ����  ADCģ��⺯��
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#include "lib_adc.h"

/***************************************************************
  ��������ADC_Init
  ��  ������ʼ��ADCģ��
  ����ֵ����ʼ�����ýṹ���ַ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void ADC_Init(ADC_InitStruType * ADC_InitStruct)
{
		ADC->VREFCON.VREF_EN = ENABLE;    //�ڲ�VREFPʹ��
	  ADC->VREFCON.IREF_EN = ENABLE;    //IREFʹ��λ
	  ADC->CON1.VCMBUF_EN = ENABLE;     //ADC��ģ��ѹVCM BUFʹ��
	  ADC ->CON1.VCMBUF_HS = ENABLE;    //ADC��ģ��ѹVCM BUF����ģʽʹ��
	  ADC->CON1.HSEN = ENABLE;          //ADCת���ٶȣ����� 
	  ADC->CHS.VDD5_FLAG_EN = DISABLE;        //����VDD������
	
    ADC->CON1.CLKS = ADC_InitStruct->ADC_ClkS;     //ADCCON1:bit3 ADCʱ��Դѡ��
    ADC->CON1.CLKDIV = ADC_InitStruct->ADC_ClkDiv; //ADCCON1:bit2-0 ADCʱ��ԴԤ��Ƶ
    ADC->CON1.VREFP = ADC_InitStruct->ADC_VrefP;   //ADCCON1:bit9-8 ADC����ο���ѹѡ��
    ADC->CON1.SMPS = ADC_InitStruct->ADC_SampS;    //ADCCON1:bit12 ADC����ģʽѡ��
    ADC->CHS.CHS = ADC_InitStruct->ADC_ChS;        //ADCCHS:bit0-3 ADCģ��ͨ��ѡ��
		ADC->CON1.ST = ADC_InitStruct->ST;             //ADCCON1:bit20-16 ADC����ʱ��ѡ�� ST*2+1��Tadclk 
	  //ADC->VREFCON.VREF_SEL=ADC_InitStruct->VREF_SEL;//�ڲ��ο���ѹѡ��
	
    ADC->CON1.VREFN = ADC_InitStruct->ADC_VREFN;                    //����ο���ѹʹ��λ
    ADC->CON1.VRBUF_EN = ADC_InitStruct->ADC_VRBUF_EN;              //VREF BUFʹ��λ
}


/***************************************************************
  ��������ADC_Set_CH
  ��  ����ѡ��ADCģ��ͨ��
  ����ֵ��ͨ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void ADC_Set_CH(ADC_TYPE_CHS AdcCH)
{
    ADC->CHS.CHS = AdcCH;
}

/***************************************************************
  ��������ADC_GetConvValue
  ��  ������ȡADCת�����
  ����ֵ����
  ���ֵ����
  ����ֵ��ת��ֵ
 ***************************************************************/
uint16_t ADC_GetConvValue(void)
{   
    return ((uint16_t)ADC->DR.DR);
}

/***************************************************************
  ��������ADC_GetConvStatus
  ��  ������ȡADCת��״̬
  ����ֵ����
  ���ֵ����
  ����ֵ��RESET(���)/SET(����ת��)
 ***************************************************************/
FlagStatus ADC_GetConvStatus(void)
{
    FlagStatus bitstatus = RESET;

    /* ���ת��״̬�Ĵ��� */
    if ((ADC->CON0.TRIG != (uint32_t)RESET))
        bitstatus = SET;                    //����ת��
    else
        bitstatus = RESET;                  //ת�����

    return  bitstatus;
}

/***************************************************************
  ��������ADC_ACPConfig
  ��  ����ADC �Զ��ȽϹ��ܳ�ʼ��
  ����ֵ��ADC_ACP_InitStruct �Զ��ȽϹ��ܳ�ʼ���ṹ��
  ���ֵ����
  ����ֵ��SUCCESS �ɹ�
  ERROR ʧ��
 ***************************************************************/
ErrorStatus ADC_ACPConfig(ADC_ACP_TypeDef *ADC_ACP_InitStruct)
{
    if(ADC_ACP_InitStruct->ACPC_OVER_TIME > ADC_ACPC_OVFL_TIME_MAX
       ||ADC_ACP_InitStruct->ACPC_TIMES > ADC_ACPC_TIMES_MAX
       ||ADC_ACP_InitStruct->ACPC_MIN_TARGET > ADC_ACP_MIN_MAX
       ||ADC_ACP_InitStruct->ACPC_MAX_TARGET > ADC_ACP_MAX_MAX)
    {
        return ERROR;
    }

    if(ADC_ACP_InitStruct->ACP_EN == ENABLE)
    {
        if(ADC->CON1.CLKS == ADC_ClkS_PCLK)
        {
            ADC->ACPC.CLKS = ADC_ACPC_CLKS_PCLK;
        }
        else
        {
            ADC->ACPC.CLKS = ADC_ACPC_CLKS_LRC;
        }

        ADC->ACPC.OVFL_TIME = ADC_ACP_InitStruct ->ACPC_OVER_TIME;
        ADC->ACPC.TIMES = ADC_ACP_InitStruct->ACPC_TIMES;
        ADC->IE.ACPOVIE = ENABLE;

        /* �����û����߷�ֵ���ó�0(��Сֵ)�����ǿ�����Ϊ����رոù��� */
        if(ADC_ACP_InitStruct ->ACPC_MAX_TARGET ==0x0)
        {
            ADC->IE.ACPMAXIE = DISABLE;
        }
        else
        {
            ADC->ACPCMP.CMP_MAX =ADC_ACP_InitStruct ->ACPC_MAX_TARGET;
            ADC->IE.ACPMAXIE = ENABLE;
        }

        /* �����û����ͷ�ֵ���ó�0xfff(���ֵ)�����ǿ�����Ϊ����رոù��� */
        if(ADC_ACP_InitStruct ->ACPC_MIN_TARGET == 0xfff)
        {
            ADC->IE.ACPMINIE = DISABLE;
        }
        else
        {
            ADC->ACPCMP.CMP_MIN =ADC_ACP_InitStruct ->ACPC_MIN_TARGET;
            ADC->IE.ACPMINIE = ENABLE;
        }

        ADC->CON0.ACP_EN = ENABLE;

    }
    else
    {
        ADC->CON0.ACP_EN = DISABLE;
    }

    return SUCCESS;
}

/***************************************************************
  ��������ADC_SampStart
  ��  ����ADC �����������-��������
  ����ֵ����
  ���ֵ����
  ����ֵ��SUCCESS �ɹ�
  ERROR ʧ��
 ***************************************************************/
ErrorStatus ADC_SoftStart(void)
{
    if(ADC->CON1.SMPS == ADC_SMPS_HARD)
        return ERROR;

    ADC ->CON1.SMPON = SET;
    return SUCCESS;
}

/***************************************************************
  ��������ADC_SampStop
  ��  ����ADC �����������-ֹͣ����
  ����ֵ����
  ���ֵ����
  ����ֵ��SUCCESS �ɹ�
  ERROR ʧ��
 ***************************************************************/
ErrorStatus ADC_SoftStop(void)
{
    if(ADC->CON1.SMPS == ADC_SMPS_HARD)
        return ERROR;

    ADC->CON1.SMPON = RESET;
    return SUCCESS;
}

/***************************************************************
  ��������ADC_GetACPMeanValue
  ��  ����ADC ��õ����Զ��Ƚ�ƽ��ֵ
  ����ֵ����
  ���ֵ����
  ����ֵ����������
 ***************************************************************/
uint16_t ADC_GetACPMeanValue(void)
{
    return ((uint16_t)ADC->ACPMEAN.MEAN_DATA);
}

/***************************************************************
  ��������ADC_GetACPMINValue
  ��  ����ADC ��õ����Զ��Ƚ�ƽ��ֵ
  ����ֵ����
  ���ֵ����
  ����ֵ����������
 ***************************************************************/
uint16_t ADC_GetACPMinValue(void)
{
    return ((uint16_t)ADC->ACPCMP.CMP_MIN);
}

/***************************************************************
  ��������ADC_GetACPMAXValue
  ��  ����ADC ��õ����Զ��Ƚ�ƽ��ֵ
  ����ֵ����
  ���ֵ����
  ����ֵ����������
 ***************************************************************/
uint16_t ADC_GetACPMaxValue(void)
{
    return ((uint16_t)ADC->ACPCMP.CMP_MAX);
}

/***************************************************************
  ��������ADC_GetFlagStatus
  ��  ������ȡADC��־λ״̬
  ����ֵ��IFName��ADC�жϱ�־
  ���ֵ����
  ����ֵ��SET/RESET
 ***************************************************************/
FlagStatus ADC_GetFlagStatus(ADC_TYPE_IF IFName)
{
    FlagStatus bitstatus = RESET;

    /* ����жϱ�־λ */
    if (((ADC->IF.Word & IFName) != (uint32_t)RESET))
        bitstatus = SET;                    //ת�����
    else
        bitstatus = RESET;                  //���ж�

    return  bitstatus;
}

/***************************************************************
  ��������ADC_GetITStatus
  ��  ������ȡADC�ж�״̬��δʹ����Ӧ�ж�ʱ���᷵��SET
  ����ֵ����
  ���ֵ����
  ����ֵ��SET���жϣ�/RESET�����жϣ�
 ***************************************************************/
ITStatus ADC_GetITStatus(ADC_TYPE_IE IEName)
{
    ITStatus bitstatus = RESET;

    /* ����жϱ�־λ */
    if (((ADC->IE.Word & IEName) != (uint32_t)RESET))
        bitstatus = SET;                    //ת����ɣ����ж�
    else
        bitstatus = RESET;                  //���ж�

    return  bitstatus;
}

/***************************************************************
  ��������ADC_ClearIFStatus
  ��  ����ADC ����ض������ж�
  ����ֵ��IFName �ж�����ѡ��
  ADC_IF            ADC�ж�
  ADC_IF_ACPMIN �Զ�ת���ͷ�ֵ�����ж�
  ADC_IF_ACPMAX �Զ�ת���߷�ֵ�����ж�
  ADC_IF_ACPOVER    �Զ�ת������ж�
  ���ֵ����
  ����ֵ��SUCCESS �ɹ�
  ERROR ʧ��
 ***************************************************************/
ErrorStatus ADC_ClearIFStatus(ADC_TYPE_IF IFName)
{
    ADC->IF.Word = (uint32_t)IFName;

    return SUCCESS;
}
/***************************************************************
  ��������ADC_Reset
  ��  ����ADC��λ
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void ADC_Reset(void)
{
    ADC->CON0.Word = 0x00000030;
    ADC->CON1.Word = 0x00041000;
    ADC->CHS.Word = 0x00000100;
    ADC->IE.Word = 0x00000000;
    ADC->IF.Word = 0x00000000;
    ADC->ACPC.Word = 0x00000000;
    ADC->ACPCMP.Word = 0x0FFF0000;
    ADC->VREFCON.Word = 0x00000000;
}

/*************************END OF FILE**********************/


