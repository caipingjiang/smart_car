/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ����� lib_scu.h
 *�� �ߣ� Liut
 *�� ���� V1.00
 *�� �ڣ� 2017/07/14
 *�� ���� �ں�ģ��⺯��ͷ�ļ�
 *�� ע�� ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#ifndef __LIBSCU_H
#define __LIBSCU_H

#include "system_ES8P508x.h"
#include "ES8P508x.h"
#include "type.h"

/* NMI���������ж�ѡ�� */
typedef enum
{
    SCU_PINT0_IRQn = 0,
    SCU_PINT1_IRQn = 1,
    SCU_PINT2_IRQn = 2,
    SCU_PINT3_IRQn = 3,
    SCU_PINT4_IRQn = 4,
    SCU_PINT5_IRQn = 5,
    SCU_PINT6_IRQn = 6,
    SCU_PINT7_IRQn = 7,
    SCU_T16N0_IRQn = 8,
    SCU_T16N1_IRQn = 9,
    SCU_T16N2_IRQn = 10,
    SCU_T16N3_IRQn = 11,
    SCU_T32N0_IRQn = 12,
    SCU_IWDT_IRQn = 14,
    SCU_WWDT_IRQn = 15,
    SCU_CCM_IRQn = 16,
    SCU_PLK_IRQn = 17,
    SCU_LVD_IRQn = 18,
    SCU_KINT_IRQn = 19,
    SCU_RTC_IRQn = 20,
    SCU_ADC_IRQn = 21,
    SCU_AES_IRQn = 23,
    SCU_UART0_IRQn = 24,
    SCU_UART1_IRQn = 25,
    SCU_UART2_IRQn = 26,
    SCU_UART3_IRQn = 27,
    SCU_UART4_IRQn = 28,
    SCU_UART5_IRQn = 29,
    SCU_SPI0_IRQn = 30,
    SCU_I2C0_IRQn = 31,
}SCU_TYPE_NMICS;

/* PWRC��λ״̬�Ĵ�����־λ */
typedef enum
{
    SCU_PWRC_PORF= 0X00001,         //POR��λ��־λ
    SCU_PWRC_RRCF = 0X00002,        //PORC��λ��־λ
    SCU_PWRC_PORRSTF = 0x00004,     //POR�ܸ�λ��־
    SCU_PWRC_BORF = 0x00008,        //BOR�ܸ�λ��־
    SCU_PWRC_WWDTRSTF = 0x00010,    //WWDT��λ��־
    SCU_PWRC_IWDTRSTF = 0x00020,    //IWDT��λ��־
    SCU_PWRC_MRSTF = 0x00040,       //MRSTn��λ��־
    SCU_PWRC_SOFTRSTF = 0x00080,    //�����λ��־
}SCU_TYPE_PWRC;

/* LVD�Ĵ�����־λ */
typedef enum
{
    SCU_LVDFlag_IF = 0x0100,  //LVD�жϱ�־
    SCU_LVDFlag_Out = 0x8000, //���״̬λ
}SCU_TYPE_LVD0CON;

/* ʱ��ѡ�� */
typedef enum
{
    SCU_SysClk_HRC  = 0x0 ,  //�ڲ�20MHZ RCʱ��
    SCU_SysClk_XTAL = 0x1 ,   //�ⲿ������ʱ��
    SCU_SysClk_PLL  = 0x2 ,   //PLL
}SCU_TYPE_SYSCLK;

/*clk_selʱ��Դѡ��*/
typedef enum
{
    CLK_SEL_HRC    = 0x0,   //HRC 20M
    CLK_SEL_LRC    = 0x1,   //LRC 32KHz
    CLK_SEL_XTAL   = 0x2,   //��Ӿ���XTAL
}SCU_TYPE_CLK_SEL;

/* PLLʱ��Դѡ�� */
typedef enum
{
    SCU_PLL_HRC   = 0x0 ,   //PLLʱ��ԴHRC
    SCU_PLL_LRC  = 0x2 ,    //PLLʱ��ԴLRC
    SCU_PLL_XTAL_32K  = 0x3 ,    //PLLʱ��ԴXTAL
    SCU_PLL_XTAL_4M  = 0x4 ,    //PLLʱ��ԴXTAL
    SCU_PLL_XTAL_8M  = 0x5,     //PLLʱ��ԴXTAL
    SCU_PLL_XTAL_16M = 0x6,     //PLLʱ��ԴXTAL
    SCU_PLL_XTAL_20M = 0x7,     //PLLʱ��ԴXTAL
} SCU_PLL_Origin;

/* PLLʱ�����Ƶ������ */
typedef enum
{
    SCU_PLL_32M   = 0x0 ,   //PLLʱ�����Ϊ32MHz
    SCU_PLL_48M   = 0x1 ,   //PLLʱ�����Ϊ48Mhz
} SCU_PLL_Out;

/************SCUģ��궨��***********/
/* SCUд�������� */
#define SCU_RegUnLock() (SCU->PROT.Word = 0x55AA6996)
#define SCU_RegLock()   (SCU->PROT.Word = 0x00000000)

/* NMIʹ�ܿ��� */
#define SCU_NMI_Enable()  (SCU->NMICON.NMIEN = 0x1)
#define SCU_NMI_Disable() (SCU->NMICON.NMIEN = 0x0)

/*-------LVDģ��-------*/

/* LVDʹ�ܿ��� */
#define SCU_LVD_Enable()  (SCU->LVDCON.EN = 0x1)
#define SCU_LVD_Disable() (SCU->LVDCON.EN = 0x0)

/* LVD�˲�ʹ�ܿ��� */
#define SCU_LVDFLT_Enable()  (SCU->LVDCON.FLTEN = 0x1)
#define SCU_LVDFLT_Disable() (SCU->LVDCON.FLTEN = 0x0)

/* LVD������ѹѡ�� */
#define SCU_LVDVS_2V0() (SCU->LVDCON.VS = 0x0)
#define SCU_LVDVS_2V1() (SCU->LVDCON.VS = 0x1)
#define SCU_LVDVS_2V2() (SCU->LVDCON.VS = 0x2)
#define SCU_LVDVS_2V4() (SCU->LVDCON.VS = 0x3)
#define SCU_LVDVS_2V6() (SCU->LVDCON.VS = 0x4)
#define SCU_LVDVS_2V8() (SCU->LVDCON.VS = 0x5)
#define SCU_LVDVS_3V0() (SCU->LVDCON.VS = 0x6)
#define SCU_LVDVS_3V6() (SCU->LVDCON.VS = 0x7)
#define SCU_LVDVS_4V()  (SCU->LVDCON.VS = 0x8)
#define SCU_LVDVS_4V6() (SCU->LVDCON.VS = 0x9)
#define SCU_LVDVS_2V3() (SCU->LVDCON.VS = 0xA)
#define SCU_LVDVS_LVDIN() (SCU->LVDCON.VS = 0xE)

/* LVD�ж�ʹ�ܿ��� */
#define SCU_LVDIT_Enable()  (SCU->LVDCON.IE = 0x1)
#define SCU_LVDIT_Disable() (SCU->LVDCON.IE = 0x0)

/* LVD�жϱ�־λ��� */
#define SCU_LVDClearIFBit() (SCU->LVDCON.IF = 1)

/* LVD�жϲ���ģʽѡ�� */
#define SCU_LVDIFS_Rise() (SCU->LVDCON.IFS = 0x0) //LVDO�����ز����ж�
#define SCU_LVDIFS_Fall() (SCU->LVDCON.IFS = 0x1) //LVDO�½��ز����ж�
#define SCU_LVDIFS_High() (SCU->LVDCON.IFS = 0x2) //LVDO�ߵ�ƽ�����ж�
#define SCU_LVDIFS_Low()  (SCU->LVDCON.IFS = 0x3)   //LVDO�͵�ƽ�����ж� 
#define SCU_LVDIFS_Change() (SCU->LVDCON.IFS = 0x4) //LVDO��ƽ�仯�����ж�

/* FLASH���ʵȴ�ʱ��ѡ�� */
#define SCU_FlashWait_1Tclk()  (SCU->FLASHWAIT.ACCT = 0x0)
#define SCU_FlashWait_2Tclk()  (SCU->FLASHWAIT.ACCT = 0x1)
#define SCU_FlashWait_3Tclk()  (SCU->FLASHWAIT.ACCT = 0x2)
#define SCU_FlashWait_4Tclk()  (SCU->FLASHWAIT.ACCT = 0x3)
#define SCU_FlashWait_5Tclk()  (SCU->FLASHWAIT.ACCT = 0x4)
#define SCU_FlashWait_6Tclk()  (SCU->FLASHWAIT.ACCT = 0x5)
#define SCU_FlashWait_7Tclk()  (SCU->FLASHWAIT.ACCT = 0x6)
#define SCU_FlashWait_8Tclk()  (SCU->FLASHWAIT.ACCT = 0x7)
#define SCU_FlashWait_9Tclk()  (SCU->FLASHWAIT.ACCT = 0x8)
#define SCU_FlashWait_10Tclk() (SCU->FLASHWAIT.ACCT = 0x9)
#define SCU_FlashWait_11Tclk() (SCU->FLASHWAIT.ACCT = 0xA)
#define SCU_FlashWait_12Tclk() (SCU->FLASHWAIT.ACCT = 0xB)
#define SCU_FlashWait_13Tclk() (SCU->FLASHWAIT.ACCT = 0xC)
#define SCU_FlashWait_14Tclk() (SCU->FLASHWAIT.ACCT = 0xD)
#define SCU_FlashWait_15Tclk() (SCU->FLASHWAIT.ACCT = 0xE)
#define SCU_FlashWait_16Tclk() (SCU->FLASHWAIT.ACCT = 0xF)

/* ϵͳʱ�Ӻ��Ƶѡ�� */
#define SCU_SysClk_Div1()   (SCU->SCLKEN0.SYSCLK_DIV = 0)
#define SCU_SysClk_Div2()   (SCU->SCLKEN0.SYSCLK_DIV = 1)
#define SCU_SysClk_Div4()   (SCU->SCLKEN0.SYSCLK_DIV = 2)
#define SCU_SysClk_Div8()  (SCU->SCLKEN0.SYSCLK_DIV = 3)
#define SCU_SysClk_Div16()  (SCU->SCLKEN0.SYSCLK_DIV = 4)
#define SCU_SysClk_Div32()  (SCU->SCLKEN0.SYSCLK_DIV = 5)
#define SCU_SysClk_Div64()  (SCU->SCLKEN0.SYSCLK_DIV = 6)
#define SCU_SysClk_Div128() (SCU->SCLKEN0.SYSCLK_DIV = 7)

/* HRCʹ�ܿ��� (�ڲ�20Mhz) */
#define SCU_HRC_Enable()  (SCU->SCLKEN1.HRC_EN = 1)
#define SCU_HRC_Disable() (SCU->SCLKEN1.HRC_EN = 0)

/* XTALʹ�ܿ��� */
#define SCU_XTAL_Enable()  (SCU->SCLKEN1.XTAL_EN = 1)
#define SCU_XTAL_Disable() (SCU->SCLKEN1.XTAL_EN = 0)

/* PLLģʽʹ�ܿ��� */
#define SCU_PLL_Enable()  (SCU->SCLKEN1.PLL_EN = 1)
#define SCU_PLL_Disable() (SCU->SCLKEN1.PLL_EN = 0)

/*-------����ʱ�ӿ���-------*/
/* SCUʱ��ʹ�ܿ��� */
#define SCU_SCUCLK_Enable()  (SCU->PCLKEN0.SCU_EN = 1)
#define SCU_SCUCLK_Disable() (SCU->PCLKEN0.SCU_EN = 0)

/* GPIOʱ��ʹ�ܿ��� */
#define SCU_GPIOCLK_Enable()  (SCU->PCLKEN0.GPIO_EN = 1)
#define SCU_GPIOCLK_Disable() (SCU->PCLKEN0.GPIO_EN = 0)

/* FLASH IAPʱ��ʹ�ܿ��� */
#define SCU_IAPCLK_Enable()  (SCU->PCLKEN0.IAP_EN = 1)
#define SCU_IAPCLK_Disable() (SCU->PCLKEN0.IAP_EN = 0)

/* CRCʱ��ʹ�ܿ��� */
#define SCU_CRCCLK_Enable()  (SCU->PCLKEN0.CRC_EN = 1)
#define SCU_CRCCLK_Disable() (SCU->PCLKEN0.CRC_EN = 0)

/* ADCʱ��ʹ�ܿ��� */
#define SCU_ADCCLK_Enable()  (SCU->PCLKEN0.ADC_EN = 1)
#define SCU_ADCCLK_Disable() (SCU->PCLKEN0.ADC_EN = 0)

/* RTCʱ��ʹ�ܿ��� */
#define SCU_RTCCLK_Enable()  (SCU->PCLKEN0.RTC_EN = 1)
#define SCU_RTCCLK_Disable() (SCU->PCLKEN0.RTC_EN = 0)

/* IWDTʱ��ʹ�ܿ��� */
#define SCU_IWDTCLK_Enable()  (SCU->PCLKEN0.IWDT_EN = 1)
#define SCU_IWDTCLK_Disable() (SCU->PCLKEN0.IWDT_EN = 0)

/* WWDTʱ��ʹ�ܿ��� */
#define SCU_WWDTCLK_Enable()  (SCU->PCLKEN0.WWDT_EN = 1)
#define SCU_WWDTCLK_Disable() (SCU->PCLKEN0.WWDT_EN = 0)

/* AESʱ��ʹ�ܿ��� */
#define SCU_AESCLK_Enable()  (SCU->PCLKEN0.AES_EN = 1)
#define SCU_AESCLK_Disable() (SCU->PCLKEN0.AES_EN = 0)

/* T16N0ʱ��ʹ�ܿ��� */
#define SCU_T16N0CLK_Enable()  (SCU->PCLKEN1.T16N0_EN = 1)
#define SCU_T16N0CLK_Disable() (SCU->PCLKEN1.T16N0_EN = 0)

/* T16N1ʱ��ʹ�ܿ��� */
#define SCU_T16N1CLK_Enable()  (SCU->PCLKEN1.T16N1_EN = 1)
#define SCU_T16N1CLK_Disable() (SCU->PCLKEN1.T16N1_EN = 0)

/* T16N2ʱ��ʹ�ܿ��� */
#define SCU_T16N2CLK_Enable()  (SCU->PCLKEN1.T16N2_EN = 1)
#define SCU_T16N2CLK_Disable() (SCU->PCLKEN1.T16N2_EN = 0)

/* T16N3ʱ��ʹ�ܿ��� */
#define SCU_T16N3CLK_Enable()  (SCU->PCLKEN1.T16N3_EN = 1)
#define SCU_T16N3CLK_Disable() (SCU->PCLKEN1.T16N3_EN = 0)

/* T32N0ʱ��ʹ�ܿ��� */
#define SCU_T32N0CLK_Enable()  (SCU->PCLKEN1.T32N0_EN = 1)
#define SCU_T32N0CLK_Disable() (SCU->PCLKEN1.T32N0_EN = 0)

/* UART0ʱ��ʹ�ܿ��� */
#define SCU_UART0CLK_Enable()  (SCU->PCLKEN1.UART0_EN = 1)
#define SCU_UART0CLK_Disable() (SCU->PCLKEN1.UART0_EN = 0)

/* UART1ʱ��ʹ�ܿ��� */
#define SCU_UART1CLK_Enable()  (SCU->PCLKEN1.UART1_EN = 1)
#define SCU_UART1CLK_Disable() (SCU->PCLKEN1.UART1_EN = 0)

/* UART2ʱ��ʹ�ܿ��� */
#define SCU_UART2CLK_Enable()  (SCU->PCLKEN1.UART2_EN = 1)
#define SCU_UART2CLK_Disable() (SCU->PCLKEN1.UART2_EN = 0)

/* UART3ʱ��ʹ�ܿ��� */
#define SCU_UART3CLK_Enable()  (SCU->PCLKEN1.UART3_EN = 1)
#define SCU_UART3CLK_Disable() (SCU->PCLKEN1.UART3_EN = 0)

/* UART4ʱ��ʹ�ܿ��� */
#define SCU_UART4CLK_Enable()  (SCU->PCLKEN1.UART4_EN = 1)
#define SCU_UART4CLK_Disable() (SCU->PCLKEN1.UART4_EN = 0)

/* UART5ʱ��ʹ�ܿ��� */
#define SCU_UART5CLK_Enable()  (SCU->PCLKEN1.UART5_EN = 1)
#define SCU_UART5CLK_Disable() (SCU->PCLKEN1.UART5_EN = 0)

/* SPI0ʱ��ʹ�ܿ��� */
#define SCU_SPI0CLK_Enable()  (SCU->PCLKEN1.SPI0_EN = 1)
#define SCU_SPI0CLK_Disable() (SCU->PCLKEN1.SPI0_EN = 0)

/* IIC0ʱ��ʹ�ܿ��� */
#define SCU_IIC0CLK_Enable()  (SCU->PCLKEN1.I2C0_EN = 1)
#define SCU_IIC0CLK_Disable() (SCU->PCLKEN1.I2C0_EN = 0)

/* �ж���������ӳ��ʹ�ܿ��� */
#define SCU_TBLRemap_Enable()  (SCU->TBLREMAPEN.EN= 1)
#define SCU_TBLRemap_Disable() (SCU->TBLREMAPEN.EN= 0)

/* �ж�������ƫ�ƼĴ��� x���Ϊ2^24=16777216 */
#define SCU_TBL_Offset(x) (SCU->TBLOFF.TBLOFF = (uint32_t)x)

/************SCUģ�麯������***********/
void SCU_OpenXTAL(void);
void SCU_NMISelect(SCU_TYPE_NMICS NMI_Type);
FlagStatus SCU_GetPWRCFlagStatus(SCU_TYPE_PWRC PWRC_Flag);
void SCU_ClearPWRCFlagBit(SCU_TYPE_PWRC PWRC_Flag);
FlagStatus SCU_GetLVDFlagStatus(SCU_TYPE_LVD0CON LVD_Flag);
void SCU_SysClkSelect(SCU_TYPE_SYSCLK Sysclk);
SCU_TYPE_SYSCLK SCU_GetSysClk(void);
FlagStatus SCU_HRCReadyFlag(void);
FlagStatus  SCU_XTALReadyFlag(void);
FlagStatus  SCU_PLLReadyFlag(void);
void SystemClockConfig(void);
void SystemClockConfig_1(void);
void DeviceClockAllEnable(void);
void DeviceClockAllDisable(void);
void SystemClockSelect(SCU_TYPE_SYSCLK SYSCLKx , SCU_TYPE_CLK_SEL CLK_SEL);
void PLLClock_Config(TYPE_FUNCEN pll_en , SCU_PLL_Origin  pll_origin ,SCU_PLL_Out pll_out,TYPE_FUNCEN sys_pll);
#endif
/*************************END OF FILE**********************/





