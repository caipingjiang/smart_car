/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ����� lib_scs.h
 *�� �ߣ� Liut
 *�� ���� V1.00
 *�� �ڣ� 2017/07/14
 *�� ���� �ں�ģ��⺯��ͷ�ļ�
 *�� ע�� ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#ifndef __LIBNVIC_H__
#define __LIBNVIC_H__

#include "ES8P508x.h"
#include "type.h"

/* �ж�Դѡ�� */
typedef enum
{
    NVIC_PINT0_IRQn = 0,
    NVIC_PINT1_IRQn = 1,
    NVIC_PINT2_IRQn = 2,
    NVIC_PINT3_IRQn = 3,
    NVIC_PINT4_IRQn = 4,
    NVIC_PINT5_IRQn = 5,
    NVIC_PINT6_IRQn = 6,
    NVIC_PINT7_IRQn = 7,
    NVIC_T16N0_IRQn = 8,
    NVIC_T16N1_IRQn = 9,
    NVIC_T16N2_IRQn = 10,
    NVIC_T16N3_IRQn = 11,
    NVIC_T32N0_IRQn = 12,
    NVIC_IWDT_IRQn = 14,
    NVIC_WWDT_IRQn = 15,
    NVIC_CCM_IRQn = 16,
    NVIC_PLK_IRQn = 17,
    NVIC_LVD_IRQn = 18,
    NVIC_KINT_IRQn = 19,
    NVIC_RTC_IRQn = 20,
    NVIC_ADC_IRQn = 21,
    NVIC_AES_IRQn = 23,
    NVIC_UART0_IRQn = 24,
    NVIC_UART1_IRQn = 25,
    NVIC_UART2_IRQn = 26,
    NVIC_UART3_IRQn = 27,
    NVIC_UART4_IRQn = 28,
    NVIC_UART5_IRQn = 29,
    NVIC_SPI0_IRQn = 30,
    NVIC_I2C0_IRQn = 31,
}NVIC_IRQChannel;

/* ���ȼ� */
typedef enum
{
    NVIC_Priority_0 = 0x0 ,
    NVIC_Priority_1 = 0x1 ,
    NVIC_Priority_2 = 0x2 ,
    NVIC_Priority_3 = 0x3 ,
}NVIC_IRQPriority;

/* ����ģʽ */
typedef enum
{
    SCB_LP_SleepOnExit = 0x02 , //��ISR�жϴ�����򷵻ص��߳�ģʽʱ���Ƿ�����
    SCB_LP_SleepDeep = 0x04 ,   //���˯��
    SCB_LP_SEVOPend = 0x10 ,    //�жϹ���ʱ���Ƿ���Ϊ���ѵ�ѡ��λ
}SCB_TYPE_SCR;

/* SysTickʱ��Դѡ�� */
typedef enum
{
    SysTick_ClkS_Base = 0x0 , //��׼ʱ��(Hclk/3)
    SysTick_ClkS_Cpu = 0x1 ,  //������ʱ��(Hclk)
}SYST_TYPE_CLKS;

/* SysTick��ʼ�����ýṹ�嶨�� */
typedef struct
{
    uint32_t  SysTick_Value;           //�ݼ���ֵ��24λ���Ҷ���
    SYST_TYPE_CLKS  SysTick_ClkSource; //ʱ��Դѡ��
    TYPE_FUNCEN  SysTick_ITEnable;     //�ж�ʹ�ܡ�ʧ��
}SYSTICK_InitStruType;

/**************ģ��궨��*************/

/*SysTickʹ��*/
#define SysTick_Enable()  (SysTick->CTRL |= 0x00000001)
#define SysTick_Disable() (SysTick->CTRL &= 0xFFFFFFFE)

/************SCSģ�麯������***********/
void NVIC_Init(NVIC_IRQChannel Channel,NVIC_IRQPriority Priority,TYPE_FUNCEN Cmd);
void SCB_SystemLPConfig(SCB_TYPE_SCR LowPowerMode, TYPE_FUNCEN NewState);
uint32_t SCB_GetCpuID(void);
void SysTick_Init(SYSTICK_InitStruType* SysT_InitStruct);
 
#endif

/*************************END OF FILE**********************/
