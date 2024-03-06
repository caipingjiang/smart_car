/***************************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ�����  system_ES8P508x.c
*��  �ߣ�  Liut
*��  ����  V1.00
*��  �ڣ�  2017/07/14
*��  ����  �⺯�������ļ�
*��  ע��  ������ ES8P508xоƬ
           ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
***************************************************************/
#include "system_ES8P508x.h"
#include "lib_config.h"

uint32_t SystemCoreClock = 48000000;


/***************************************************************
��������SystemCoreClockUpdate
��  ����ϵͳʱ������Ϊ�ڲ�ʱ��20MHZ��ͬʱ����SystemCoreClock
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t Prot_Temp;
    uint16_t Count=0;
    SystemClockSelect(SCU_SysClk_HRC , CLK_SEL_HRC);        //ѡ��ϵͳʱ��ΪHRCʱ��
    PLLClock_Config(DISABLE, SCU_PLL_HRC, SCU_PLL_48M,ENABLE);    //PLL��ֹ
    Prot_Temp = SCU->PROT.PROT;
    if(Prot_Temp != 0)                                      //д������
        {SCU->PROT.Word = 0x55AA6996;}                      //����

    SCU->SCLKEN1.HRC_EN = 1;                                //ʹ���ڲ�20MHZ
    do
    {
        Count++;
    }
    while((SCU->SCLKEN1.HRC_RDY == 0)&&(Count != 0xFFF));   //�ȴ�ʱ�ӿ���

    if(Count == 0xFFF)
    {
        return ;
    }

    SCU->SCLKEN0.SYSCLK_DIV = 0;                            //ϵͳʱ�Ӻ��Ƶ1:1

    switch(SCU->SCLKEN0.CLK_SEL)
    {
        case 0:
            SystemCoreClock = 20000000;                     //HRC
            break;
        case 1:
            SystemCoreClock = 32000;                        //LRC
            break;
        default:
            break;
    }

    if(Prot_Temp != 0)                                      //д������
        {SCU->PROT.Word = 0x00000000;}                      //��д����
}

/***************************************************************
��������SystemInit
��  ����ϵͳ��ʼ��������ʱ��
����ֵ����
���ֵ����
����ֵ����
***************************************************************/
void SystemInit (void)
{
    SystemCoreClockUpdate();
}

/*************************END OF FILE**********************/
