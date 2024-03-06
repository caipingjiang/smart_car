/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *�ļ�����  lib_scu.c
 *��  �ߣ�  Liut
 *��  ����  V1.00
 *��  �ڣ�  2017/07/14
 *��  ����  ϵͳ����ģ��⺯��
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#include "lib_scu.h"

/***************************************************************
  ��������SCU_OpenXTAL
  ��  ��: �����ⲿʱ��
  ����ֵ����
  ���ֵ����
  ����ֵ��ϵͳʱ��Դ
 ***************************************************************/
void SCU_OpenXTAL(void)
{
	SCU_RegUnLock();
	SCU->SCLKEN1.XTAL_EN = 1;
	SCU->SCLKEN0.XTAL_LP = 0;
	while(SCU->SCLKEN1.XTAL_RDY == 0); //�ȴ��ⲿʱ���ȶ�
	SCU_RegLock() ;
}

/***************************************************************
  ��������SCU_NMISelect
  ��  ��������NMI���������ж�
  ����ֵ�����������ж�
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void SCU_NMISelect(SCU_TYPE_NMICS NMI_Type)
{
	  SCU_RegUnLock();
    SCU->NMICON.NMICS = NMI_Type;
	  SCU_RegLock() ;
}

/***************************************************************
  ��������SCU_GetPWRCFlagStatus
  ��  ������ȡPWRC��λ״̬�Ĵ�����־λ״̬
  ����ֵ��PWRC�Ĵ�����־λ
  ���ֵ����
  ����ֵ��RESET/SET
 ***************************************************************/
FlagStatus  SCU_GetPWRCFlagStatus(SCU_TYPE_PWRC PWRC_Flag)
{
    FlagStatus bitstatus = RESET;
    if((SCU->PWRC.Word & (uint32_t)PWRC_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  ��������SCU_ClearPWRCFlagBit
  ��  �������PWRC��λ״̬�Ĵ�����־λ
  ����ֵ��PWRC�Ĵ�����־λ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void SCU_ClearPWRCFlagBit(SCU_TYPE_PWRC PWRC_Flag)
{
	  SCU_RegUnLock() ;
    SCU->PWRC.Word &= ~((uint32_t)PWRC_Flag);
	  SCU_RegLock() ;
}

/***************************************************************
  ��������SCU_GetLVDFlagStatus
  ��  ������ȡLVDD�Ĵ�����־λ״̬
  ����ֵ��LVD�Ĵ�����־λ
  ���ֵ����
  ����ֵ��RESET/SET
 ***************************************************************/
FlagStatus  SCU_GetLVDFlagStatus(SCU_TYPE_LVD0CON LVD_Flag)
{
    FlagStatus bitstatus = RESET;

    if((SCU->LVDCON.Word & (uint32_t)LVD_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  ��������SCU_SysClkSelect
  ��  ����ѡ��ϵͳʱ��
  ����ֵ��ʱ��Դ
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void SCU_SysClkSelect(SCU_TYPE_SYSCLK Sysclk)
{
	  SCU_RegUnLock() ;
    SCU->SCLKEN0.CLK_SEL = Sysclk;
	  SCU_RegLock() ;
}

/***************************************************************
  ��������SCU_GetSysClk
  ��  ������ȡϵͳʱ��Դ
  ����ֵ����
  ���ֵ����
  ����ֵ��ϵͳʱ��Դ
 ***************************************************************/
SCU_TYPE_SYSCLK SCU_GetSysClk(void)
{
    return (SCU_TYPE_SYSCLK)(SCU->SCLKEN0.CLK_SEL);
}

/***************************************************************
  ��������SCU_HRCReadyFlag
  ��  ������ȡHRC�ȶ���־λ
  ����ֵ����
  ���ֵ����
  ����ֵ��RESET�����ȶ���/SET���ȶ���
 ***************************************************************/
FlagStatus SCU_HRCReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((SCU->SCLKEN1.HRC_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  ��������SCU_XTALReadyFlag
  ��  ������ȡXTAL�ȶ���־λ
  ����ֵ����
  ���ֵ����
  ����ֵ��RESET�����ȶ���/SET���ȶ���
 ***************************************************************/
FlagStatus  SCU_XTALReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((SCU->SCLKEN1.XTAL_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
  ��������SCU_LOSCReadyFlag
  ��  ������ȡLOSC�ȶ���־λ
  ����ֵ����
  ���ֵ����
  ����ֵ��RESET�����ȶ���/SET���ȶ���
 ***************************************************************/
FlagStatus  SCU_PLLReadyFlag(void)
{
    FlagStatus bitstatus = RESET;

    if((SCU->SCLKEN1.PLL_RDY) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return  bitstatus;
}

/***************************************************************
 ��������SystemClockConfig
 ��  ����ϵͳʱ�����ã��ڲ�ʱ�ӣ�20MHZ������������ʱ��
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void SystemClockConfig(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;

    if(Prot_Temp != 0)                      //д������
        SCU_RegUnLock();                    //����

    SCU_HRC_Enable();                       //ʹ���ڲ�20MHZ
    while(SCU_HRCReadyFlag() != SET);       //�ȴ�ʱ�ӿ���
    SCU_SysClkSelect(SCU_SysClk_HRC);       //ѡ���ڲ�20MHZΪϵͳʱ��
	
    SCU_SysClk_Div1();                      //ϵͳʱ�Ӻ��Ƶ1:1    
    
    SystemCoreClock = 20000000;

    if(Prot_Temp != 0)                      //д������
        SCU_RegLock();                      //��д����
}

/***************************************************************
  ��������DeviceClockAllEnable
  ��  ��������������ʱ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void DeviceClockAllEnable(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;
    if(Prot_Temp != 0)                      //д������
        SCU_RegUnLock();                    //����

    SCU->PCLKEN0.Word = 0xFFFFFFFF;
    SCU->PCLKEN1.Word = 0xFFFFFFFF;         //����������ʱ��

    if(Prot_Temp != 0)                      //д������
        SCU_RegLock();                      //��д����
}

/***************************************************************
  ��������DeviceClockAllDisable
  ��  �����ر���������ʱ��
  ����ֵ����
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void DeviceClockAllDisable(void)
{
    uint32_t Prot_Temp;

    Prot_Temp = SCU->PROT.PROT;
    if(Prot_Temp != 0)                      //д������
        SCU_RegUnLock();                    //����

    SCU->PCLKEN0.Word = 0x00000000;         //�ر���������ʱ�ӣ�scu�޷��ر�
    SCU->PCLKEN1.Word = 0x00000000;

    if(Prot_Temp != 0)                      //д������
        SCU_RegLock();                  //��д����
}

/***************************************************************
  ��������SystemClockConfig
  ��  ����ϵͳʱ��ѡ��
  ����ֵ��CLKx ϵͳʱ��Դѡ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void SystemClockSelect(SCU_TYPE_SYSCLK SYSCLKx , SCU_TYPE_CLK_SEL CLK_SEL)
{
    SCU_RegUnLock();                        //����

    switch(SYSCLKx)
    {
        case 0:
            SCU_HRC_Enable();
            while(SCU_HRCReadyFlag() != SET);
            break;
        case 1:
            SCU_XTAL_Enable();
            while(SCU_XTALReadyFlag() != SET);
            break;
        case 2:
            SCU_PLL_Enable();
            while(SCU_PLLReadyFlag() != SET);
            break;
        default:break;
    }

    SCU->SCLKEN0.SYSCLK_DIV = 0;
    SCU->SCLKEN0.CLK_SEL = CLK_SEL;

    SCU_RegLock();
}


/***************************************************************
  ��������PLLClock_Config
  ��  ����PLLʱ������,������PLLʱ��Ϊϵͳʱ��
  ����ֵ��pll_en:�Ƿ���PLL��pll_origin��pllʱ��Դѡ��pll_out��pll���Ƶ��ѡ��sys_pll��ϵͳʱ���Ƿ�ʹ��PLLʱ��
  ���ֵ����
  ����ֵ����
 ***************************************************************/
void PLLClock_Config(TYPE_FUNCEN pll_en , SCU_PLL_Origin  pll_origin ,SCU_PLL_Out pll_out,TYPE_FUNCEN sys_pll)
{
    SCU_RegUnLock();

    if(pll_en == DISABLE)  //���PLL����Ϊ��ֹ����ֱ�ӽ�ֹPLL��������
    {
        SCU->SCLKEN0.PLL_MUX = 0;
        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.CLKFLT_BY = 0x00;
        SCU->SCLKEN1.PLL_EN = 0;
        return;
    }

    if((pll_origin == SCU_PLL_HRC))         //���ʹ���ڲ�����ʱ�ӣ��迪���ڲ�����ʱ��
    {
        if(SCU->SCLKEN1.HRC_RDY == 0)
        {
            SCU->SCLKEN1.HRC_EN = 1;
            while(SCU->SCLKEN1.HRC_RDY == 0);  //�ȴ�HRC����
        }
    }

    if((pll_origin == SCU_PLL_XTAL_32K)
       || (pll_origin == SCU_PLL_XTAL_4M)
       ||(pll_origin == SCU_PLL_XTAL_8M)
       || (pll_origin == SCU_PLL_XTAL_16M)
       || (pll_origin == SCU_PLL_XTAL_20M))          //���ʹ���ⲿʱ�ӣ��迪���ⲿʱ��
    {
        if(SCU->SCLKEN1.XTAL_RDY == 0)
        {
            SCU->SCLKEN1.XTAL_EN = 1;
					  SCU->SCLKEN0.XTAL_LP = 0;
            while(SCU->SCLKEN1.XTAL_RDY == 0);  //�ȴ�XTAL����
        }
    }

    switch(pll_origin)
    {
        case SCU_PLL_HRC:
            SCU->SCLKEN1.PLL_REF_SEL = 0x00;
            break;
        case SCU_PLL_LRC:
            SCU->SCLKEN1.PLL_REF_SEL = 0x02;
            break;
        case SCU_PLL_XTAL_32K:
            SCU->SCLKEN1.PLL_REF_SEL = 0x03;
            break;
        case SCU_PLL_XTAL_4M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x04;
            break;
        case SCU_PLL_XTAL_8M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x05;
            break;
        case SCU_PLL_XTAL_16M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x06;
            break;
        case SCU_PLL_XTAL_20M:
            SCU->SCLKEN1.PLL_REF_SEL = 0x07;
            break;
        default:
            break;
    }

    SCU->SCLKEN1.PLL_48M_SEL = pll_out;   //����PLL���Ϊ32��48Mhz

    SCU->SCLKEN1.PLL_EN = 1;
    while(SCU->SCLKEN1.PLL_RDY == 0);


    if(sys_pll == ENABLE)
    {

        if(pll_out == SCU_PLL_32M)
        {
          SCU->SCLKEN0.CLKFLT_BY = 0;
        }
        else
        {
          SCU->SCLKEN0.CLKFLT_BY = 0x55;  //48M ʱ���˲���·
        }
        SCU->SCLKEN1.PLL_BYLOCK = 1;
        SCU->SCLKEN0.PLL_MUX = 1;
    }
    else
    {
        SCU->SCLKEN0.PLL_MUX = 0;
        SCU->SCLKEN1.PLL_BYLOCK = 0;
        SCU->SCLKEN0.CLKFLT_BY = 0x00;
    }

    SCU_RegLock(); 
}

/*************************END OF FILE**********************/



