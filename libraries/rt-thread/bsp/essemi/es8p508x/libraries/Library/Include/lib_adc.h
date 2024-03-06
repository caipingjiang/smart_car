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
#ifndef __LIBADC_H__
#define __LIBADC_H__

#include "ES8P508x.h"
#include "type.h"

/* �ڲ��ο���ѹѡ�� */
typedef enum {
	ADC_VREF_SEL_2_0 = 0,	/* �ڲ��ο���ѹ2.048v*/
	ADC_VREF_SEL_1_6 = 1,	/* �ڲ��ο���ѹ1.6v*/
	ADC_VREF_SEL_MAX = 1,
}ADC_TYPE_VREF_SEL;

/* ADCʱ��Դѡ�� */
typedef enum
{
    ADC_ClkS_PCLK = 0x0 ,   //ʱ�ӣ�PCLK
    ADC_ClkS_PLL = 0x1 ,    //ʱ�ӣ�PLL
    ADC_ClkS_32K = 0x2 ,    //ʱ�ӣ�ADCCLK(32KHZ)
}ADC_TYPE_CLKS;

/* ADCʱ��ԴԤ��Ƶ */
typedef enum
{
    ADC_ClkDiv_1 = 0x0 ,   //Ԥ��Ƶ��1:1
    ADC_ClkDiv_2 = 0x1 ,   //Ԥ��Ƶ��1:2
    ADC_ClkDiv_4 = 0x2 ,   //Ԥ��Ƶ��1:4
    ADC_ClkDiv_8 = 0x3 ,   //Ԥ��Ƶ��1:8
    ADC_ClkDiv_16 = 0x4 ,  //Ԥ��Ƶ��1:16
    ADC_ClkDiv_32 = 0x5 ,  //Ԥ��Ƶ��1:32
    ADC_ClkDiv_64 = 0x6 ,  //Ԥ��Ƶ��1:64
    ADC_ClkDiv_256 = 0x7 , //Ԥ��Ƶ��1:256
}ADC_TYPE_CLKDIV;

/* ����ο���ѹѡ�� */
typedef enum
{
    ADC_VrefP_Vcc = 0x0 ,    //����ο���ѹ��VDD��ѹ
    ADC_VrefP_Exter = 0x3 ,  //����ο���ѹ���ⲿ�ο���ѹ
}ADC_TYPE_VREFP;

/* ����ģʽѡ�� */
typedef enum
{
    ADC_SMPS_SOFT = 0,      /* ������� */
    ADC_SMPS_HARD = 1,  /* Ӳ������ */
}ADC_TYPE_SMPS;


/* ת���ٶ�ѡ�� */
typedef enum
{
    ADC_ConvSpeed_Low = 0x0 ,  //ADת���ٶȣ�����
    ADC_ConvSpeed_High = 0x1 , //ADת���ٶȣ�����
}ADC_TYPE_HSEN;

/* ADCͨ��ѡ�� */
typedef enum
{
    ADC_CHS_AIN0 = 0,       /* ͨ�� 0 */
    ADC_CHS_AIN1 = 1,       /* ͨ�� 1 */
    ADC_CHS_AIN2 = 2,       /* ͨ�� 2 */
    ADC_CHS_AIN3 = 3,       /* ͨ�� 3 */
    ADC_CHS_AIN4 = 4,       /* ͨ�� 4 */
    ADC_CHS_AIN5 = 5,       /* ͨ�� 5 */
    ADC_CHS_AIN6 = 6,       /* ͨ�� 6 */
    ADC_CHS_AIN7 = 7,       /* ͨ�� 7 */
    ADC_CHS_AIN8 = 8,       /* ͨ�� 8 */
    ADC_CHS_AIN9 = 9,       /* ͨ�� 9 */
    ADC_CHS_AIN10 = 10,     /* ͨ�� 10 */
    ADC_CHS_AIN11 = 11,     /* ͨ�� 11 */
    ADC_CHS_AIN12 = 12,     /* ͨ�� 12 */
    ADC_CHS_AIN13 = 13,     /* ͨ�� 13 */
    ADC_CHS_AIN14 = 14,     /* ͨ�� 14 */
    ADC_CHS_AIN15 = 15,     /* ͨ�� 15 */
}ADC_TYPE_CHS;

/*ADC core����ѡ��λ*/
typedef enum
{
    ADC_LP_86ua = 2,     //ADC Core ����Ϊ86���Ƽ�ʹ��
    ADC_LP_215ua = 0,    //ADC Core ����Ϊ215uA
    ADC_LP_120ua = 1,    //ADC Core ����Ϊ120uA
    ADC_LP_70ua = 3,    //ADC Core ����Ϊ70uA
}ADC_TYPE_BUFLP;

/*ADC ����buff����ѡ��λ*/
typedef enum
{
    ADC_BUFF_0ua = 0,     //ADC ����buff����Ϊ0uA���Ƽ�ʹ��
    ADC_BUFF_34ua = 1,    //ADC ����buff����Ϊ34uA
    ADC_BUFF_95ua = 2,     //ADC ����buff����Ϊ95uA
}ADC_TYPE_BUFEN;

/* ADC IF ״̬ */
typedef enum 
{
    ADC_IF = 0x01,
    ADC_IF_ACPMIN = 0x02,
    ADC_IF_ACPMAX =0x04,
    ADC_IF_ACPOVER = 0x08,
}ADC_TYPE_IF;

/* ADC IE ״̬ */
typedef enum 
{
    ADC_IE = 0x01,
    ADC_IE_ACPMIN = 0x02,
    ADC_IE_ACPMAX =0x04,
    ADC_IE_ACPOVER = 0x08,
}ADC_TYPE_IE;

/* ADC��ʼ�����ýṹ�嶨�� */
typedef struct
{
    ADC_TYPE_CLKS  ADC_ClkS;      //ADCCON1:bit3 ADCʱ��Դѡ�� 
    ADC_TYPE_CLKDIV  ADC_ClkDiv;  //ADCCON1:bit2-0 ADCʱ��ԴԤ��Ƶ 
    ADC_TYPE_VREFP  ADC_VrefP;    //ADCCON1:bit9-8 ADC����ο���ѹѡ��
    ADC_TYPE_SMPS  ADC_SampS;     //ADCCON1:bit12 ADC����ģʽѡ��
    ADC_TYPE_CHS  ADC_ChS;        //ADCCHS:bit0-3 ADCģ��ͨ��ѡ��
		//ADC_TYPE_VREF_SEL VREF_SEL;	  //�ο���ѹѡ��
		uint8_t ST;							      //Ӳ������ʱ�� (������ģʽΪӲ��ʱ����) 0~31
    TYPE_FUNCEN ADC_VREFN;        //����ο���ѹѡ��λ
    TYPE_FUNCEN ADC_VRBUF_EN;
}ADC_InitStruType;

/* �Զ��Ƚϵͷ�ֵ ѡ��*/
typedef enum
{
    ADC_ACP_MIN_MIN = 0x0,      /* �������С�ͷ�ֵ*/
    ADC_ACP_MIN_MAX = 0xfff,    /* ��������ͷ�ֵ*/
}ADC_TYPE_ACP_MIN;

/* �Զ��Ƚϸ߷�ֵ ѡ��*/
typedef enum
{
    ADC_ACP_MAX_MIN = 0x0,  /* �������С�߷�ֵ*/
    ADC_ACP_MAX_MAX = 0xfff,    /* ��������߷�ֵ*/
}ADC_TYPE_ACP_MAX;

/* ÿ���Զ�ת���Ƚ����ʱ��ѡ�� */
typedef enum
{
    ADC_ACPC_OVFL_TIME_MAX = 0x9c3, /* �����������ʱ�� */
}ADC_TYPE_ACPC_OVFL_TIME;

/* �Զ�ת���Ƚϴ��� */
typedef enum
{
    ADC_ACPC_TIMES_1 = 0,   /* 1�� */
    ADC_ACPC_TIMES_2 = 1,   /* 2�� */
    ADC_ACPC_TIMES_4 = 2,   /* 4�� */
    ADC_ACPC_TIMES_8 = 3,   /* 8�� */
    ADC_ACPC_TIMES_MAX = 3,
}ADC_TYPE_ACPC_TIMES;

/* ACP���ʱ�ӵ�ʱ��Դ */
typedef enum
{
    ADC_ACPC_CLKS_PCLK = 0,              /* PCLK */
    ADC_ACPC_CLKS_LRC = 1,               /* LRC(32KHz) */
}ADC_TYPE_ACPC_CLKS;

typedef FuncState ADC_TYPE_CHOP_EN1, ADC_TYPE_CHOP_EN;
typedef FuncState ADC_TYPE_VREF_EN,ADC_TYPE_IREF_EN;
typedef FuncState ADC_TYPE_EN,ADC_TYPE_ACP_EN;

/* �Զ��ȽϹ��ܳ�ʼ���ṹ��*/
typedef struct
{
    ADC_TYPE_ACP_EN ACP_EN;                 /* �Զ��ȽϹ���ʹ��λ*/
    uint16_t ACPC_OVER_TIME;                /* �����Զ��Ƚ����ʱ��(��ʹ�������������ó�0) 0~0x9c3 */
    ADC_TYPE_ACPC_TIMES ACPC_TIMES;         /* �����Զ��Ƚϴ���(���ȼ��������ʱ��) */
    uint16_t ACPC_MIN_TARGET;               /* ƽ��ֵ��ͷ�ֵ (����0xfff�ر�) 0~0xfff */
    uint16_t ACPC_MAX_TARGET;               /* ƽ��ֵ��߷�ֵ (����0x0�ر�)     0~0xfff */
}ADC_ACP_TypeDef;

/************ADCģ��궨��***********/
/* ADCʹ�ܿ��� */
#define ADC_Enable()  (ADC->CON0.EN = 0x1)
#define ADC_Disable() (ADC->CON0.EN = 0x0)

/* �Զ��ȽϹ���ʹ��*/
#define ADC_ACP_Enable() (ADC->CON0.ACP_EN = 1)
#define ADC_ACP_Disable() (ADC->CON0.ACP_EN = 0)

/* ADC��ʼת�� */
#define ADC_Start() (ADC->CON0.TRIG = 0x1)

/* ADC����������� */
#define ADC_SampStart() (ADC->CON1.SMPON = 0x1)
#define ADC_SampStop()  (ADC->CON1.SMPON = 0x0)

/* ADC VDD������ */
#define ADC_VDD5_FLAG_Enable() (ADC->CHS.VDD5_FLAG_EN = 0x1)
#define ADC_VDD5_FLAG_Disable()  (ADC->CHS.VDD5_FLAG_EN = 0x0)

/* ADC�ж�ʹ�ܿ��� */
#define ADC_IE_Enable()  (ADC->IE.IE = 0x1)
#define ADC_IE_Disable() (ADC->IE.IE = 0x0)

#define ADC_ACPMINIE_Enable() (ADC->IE.ACPMINIE = 1)
#define ADC_ACPMINIE_Disable() (ADC->IE.ACPMINIE = 0)

#define ADC_ACPMAXIE_Enable() (ADC->IE.ACPMAXIE = 1)
#define ADC_ACPMAXIE_Disable() (ADC->IE.ACPMAXIE = 0)

#define ADC_ACPOVIE_Enable() (ADC->IE.ACPOVIE = 1)
#define ADC_ACPOVIE_Disable() (ADC->IE.ACPOVIE = 0)

/************ADCģ�麯������***********/
void ADC_Init(ADC_InitStruType * ADC_InitStruct);
void ADC_Set_CH(ADC_TYPE_CHS AdcCH);
uint16_t ADC_GetConvValue(void);
FlagStatus ADC_GetConvStatus(void);
ErrorStatus ADC_ACPConfig(ADC_ACP_TypeDef *ADC_ACP_InitStruct);
ErrorStatus ADC_SoftStart(void);
ErrorStatus ADC_SoftStop(void);
uint16_t ADC_GetACPMeanValue(void);
uint16_t ADC_GetACPMinValue(void);
uint16_t ADC_GetACPMaxValue(void);
FlagStatus ADC_GetFlagStatus(ADC_TYPE_IF IFName);
ITStatus ADC_GetITStatus(ADC_TYPE_IE IEName);
ErrorStatus ADC_ClearIFStatus(ADC_TYPE_IF IFName);
void ADC_Reset(void);

#endif

/*************************END OF FILE**********************/
