/*************************************************************!     
 *     �������ۣ�QQȺ  123763203
 *     ����    ��www.navota.com
 *
 * @file       ics.c
 * @brief      ʱ��ģ�飨ICS)������
 * @author     Navota
 * @date       2017-1-1
 ****************************************************************/
#include "common.h"
#include "ics.h"

/* ��λ��ICS��OSCģ��Ĵ�����Ĭ��ֵ */
#define ICS_C1_DEFAULT  0x04
#define ICS_C2_DEFAULT  0x20
#define ICS_C3_DEFAULT  0x54
#define ICS_C4_DEFAULT  0x00
#define ICS_S_DEFAULT   0x50
#define OSC_CR_DEFAULT  0


/*****************************************************************************//*!
   * 
   * @ ��Ҫ  ICS�Ĺ���ģʽ�ɵ�ǰ��FEIģʽ�л�ΪFEEģʽ����ѡ�е�ʱ��Դ��1��Ƶ
   *         OSCģ������ʱ��ѡ������ʱ��Դ
   * 
   * @ ���������롿 pConfig  ָ��ICS���ýṹ��
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   *****************************************************************************/
void FEI_to_FEE(ICS_ConfigType *pConfig)
{
	/*
	 * ʹ��OSCģ��
	 */
	OSC_Init(&pConfig->oscConfig); /*OSCģ���ʼ�� */
	
	/* 
     * ���ⲿ�ο�ʱ�ӽ��з�Ƶ���ɽ��ⲿʱ�ӷ�Ƶ��31.25k~39.0625k֮��
	 */
 
    ICS_SetClkDivider(pConfig->u32ClkFreq);

        /*��FLL�Ĳο�ʱ��ѡ��Ϊ�ⲿʱ��*/
	ICS->C1 =  ICS->C1 & ~ICS_C1_IREFS_MASK;
         
        /*�ȴ�FLL�ο�ʱ�ӱ�Ϊ�ⲿʱ��*/

#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop 
};        
#endif        
	while(ICS->S & ICS_S_IREFST_MASK);
	
        /* �ȴ�FLLʱ�ӳ�ΪICS���ʱ��Դ*/
	while(!(ICS->S & ICS_S_LOCK_MASK));
		
	/*
     *����FLL���ʱ�ӱ�ʱ��Ƶ�ʵ���FLL�ο�ʱ�ӷ�Ƶ�������FLL�ı�Ƶϵ��
	 * FLL�ı�Ƶϵ����ο��ο��ֲ�
	 */
#if defined(CPU_NV32)
  /*��ѡ�е�ICS���ʱ��Դ��1��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) == 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	
	/*
	 * ��ɶ�ѡ�е�ʱ��Դ��1��Ƶ��ϵͳ/����ʱ��ʱƵ��Ϊ���õ�Ŀ��Ƶ��
	 */
    /*LOLS��0*/
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ  ICS�Ĺ���ģʽ�ɵ�ǰ��FEIģʽת���FBIģʽ����ѡ�е�ICS���ʱ��Դ
   *         ����2��Ƶ
   *        
   * @ ����  pConfig    ָ��ICS���ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBI(ICS_ConfigType *pConfig)
{

        /*ICS���ʱ��Դѡ���ڲ��ο�ʱ��*/
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
        /*�ȴ��ڲ�ʱ�ӳ�ΪICS���ʱ��Դ*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif        
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=1);
			
	/*
	 * �����ڲ��ο�ʱ��ΪICS���ʱ��Դ
	 */
#if defined(BUS_CLK_EQU_CORE_DIVIDE_BY_2)||defined(CPU_NV32) 
         /*��ѡ�е�ICS���ʱ��Դ��2��Ƶ*/       
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}

#else
	ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK));     
#endif        
	
     /*LOLS����*/
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ  ICS�Ĺ���ģʽ�ɵ�ǰ��FEIģʽת����FBEģʽ����ѡ�е�ICS���ʱ��Դ��2��Ƶ
   *         OSCģ������ʱ��ѡ������ʱ��Դ
   *
   * @ ����  pConfig   ָ��ICS�����ýṹ�� . 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/

void FEI_to_FBE(ICS_ConfigType *pConfig)
{
	OSC_Init(&pConfig->oscConfig); /*��ʼ��OSC ģ�� */

         /*����FLL�Ĳο�ʱ��Ϊ�ⲿʱ��*/

    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
       
        /*���ڲο�ʱ�ӷ����ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif        

	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);  /*�ⲿʱ�ӳ�ΪICSʱ�����Դ*/
        while(ICS->S & ICS_S_IREFST_MASK);  /*FLL�ο�ʱ�ӳ�Ϊ�ⲿʱ��*/
			
	/* 
	 * �����ⲿʱ�ӳ�ΪICS���ʱ��Դ
	 */
#if defined(CPU_NV32)
        /*��ѡ�е�ICS���ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* 
	 * ����ICS���ʱ��Ƶ��Ϊѡ�е����ʱ��Դ��2��Ƶ
	 */
        /* LOLS���� */
	ICS->S |= ICS_S_LOLS_MASK;	
}


/*****************************************************************************//*!
   *
   * @ ��Ҫ  ICS�Ĺ���ģʽ�ɵ�ǰ��FEIģʽת����FBEģʽ����ѡ�е����ʱ��Դ��2��Ƶ 
   *         OSC���ʱ��ѡ��EXTAL���ŵ��ⲿʱ��Դ 
   *
   * @ ���� pConfig  ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBE_OSC(ICS_ConfigType *pConfig)
{
    
	OSC_Init(&pConfig->oscConfig); /* ��ʼ��OSC */

	/* 
	 * �����ⲿ�ο�ʱ�ӵķ�Ƶϵ�������ο�ʱ�ӵķ�Ƶ����趨��FLL����������31.25k~39.0625k��Χ�ڣ�
	 */
    ICS_SetClkDivider(pConfig->u32ClkFreq);
    
        /*�ı�ο�ʱ��Դ����FLL�Ĳο�ʱ������Ϊ���ⲿʱ��*/
        ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);/*��FLL�Ĳο�ʱ������Ϊ���ⲿʱ��*/
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);  /*���ʱ��Դѡ���ⲿʱ��*/ 
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
        
        /* �ȴ��ο�ʱ�ӷ����ı�*/

#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);/*�ⲿʱ�ӳ�ΪICSʱ�����ʱ��Դ*/
        while(ICS->S & ICS_S_IREFST_MASK);   /*�ⲿʱ�ӳ�ΪFLL�ο�ʱ��*/
			
	/* 
	 * �����ⲿʱ�ӳ�ΪFLL�ο�ʱ�Ӻ�ICS���ʱ��Դ
	 */
#if defined(CPU_NV32)
             /*��ѡ�е�ICS���ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* 
	 * ����ICS�����ʱ��Ƶ�ʣ�Ϊ�ⲿ�ο�ʱ�ӵ�2��Ƶ
	 */
        /*LOLS ����*/
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ  ICS�Ĺ���ģʽ�ɵ�ǰ��FEIģʽת��FEEģʽ����ѡ�е�ICS���ʱ��Դ��2��Ƶ 
   *         OSC���ʱ��ѡ��EXTAL���ŵ��ⲿʱ��Դ
   *
   * @ ����  pConfig    ָ�����ýṹ��
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/

void FEI_to_FEE_OSC(ICS_ConfigType *pConfig)
{

	OSC_Init(&pConfig->oscConfig); /* ��ʼ��OSC */

	/* 
	 * �����ⲿ�ο�ʱ�ӵķ�Ƶϵ�������ο�ʱ�ӵķ�Ƶ����趨��FLL����������31.25k~39.0625k��Χ��
	 */
    ICS_SetClkDivider(pConfig->u32ClkFreq);

        /* ��FLL�Ĳο�ʱ������Ϊ�ⲿʱ�� */
        
    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);

        /*�ȴ��ο�ʱ�ӱ仯*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(ICS->S & ICS_S_IREFST_MASK); /*FLL�ο�ʱ�ӱ�Ϊ�ⲿʱ��*/
	
        /*�ȴ�FLL��ΪICS���ʱ��Դ */
	while(!(ICS->S & ICS_S_LOCK_MASK));
#if defined(CPU_NV32)	
       /*��ѡ�е�ʱ��Դ��2��Ƶ*/	
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* 
	 * ����ICS���ʱ��Ƶ�ʣ���ΪҪ���õ�Ŀ��Ƶ��
	 */

     /* LOLS���� */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FEEģʽת����FEIģʽ.
   *        
   * @ ����  pConfig  ָ�����ýṹ�� 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FEE_to_FEI(ICS_ConfigType *pConfig)
{
       /*ѡ���ڲ�ʱ����ΪFLL�Ĳο�ʱ��*/ 
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	
        /*�ȴ��ο�ʱ�ӷ����ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(!(ICS->S & ICS_S_IREFST_MASK)); /*FLL�ο�ʱ�ӳ�Ϊ�ڲ�ʱ��*/
	
        /*FLLʱ�ӳ�ΪICS���ʱ��Դ */
	while(!(ICS->S & ICS_S_LOCK_MASK));
         /*LOLS����*/
	ICS->S |= ICS_S_LOLS_MASK;

	/* 
	 * ����FLL�����ΪICS���ʱ��Դ
	 */
#if defined(CPU_NV32)
        /*��ѡ�е�ICS���ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* 
	 * ����ϵͳ/����ʱ�Ӵ�ԼΪ 16MHz
	 */
	    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
      OSC_Disable();            /* ���� OSCģ�� */
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FEEģʽת����FBIģʽ.
   *        
   * @ ���� pConfig    ָ�����ýṹ��
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FEE_to_FBI(ICS_ConfigType *pConfig)
{
        /*LOLS����*/
	ICS->S |= ICS_S_LOLS_MASK;
	
  /* ѡ���ڲ�ʱ����ΪICS���ʱ��Դ */
	/* ѡ���ڲ�ʱ����ΪFLL�ο�ʱ�� */ 
	/* LP = 0 ��bypassģʽFLL���ᱻ��ֹ*/
        
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 

        /* �ȴ��ο�ʱ�ӷ����ı� */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(!(ICS->S & ICS_S_IREFST_MASK));  /*FLL�ο�ʱ�ӳ�Ϊ�ڲ�ʱ��*/
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=1);  /*�ڲ�ʱ��ΪICS���ʱ��Դ*/
	
#if defined(BUS_CLK_EQU_CORE_DIVIDE_BY_2)||defined(CPU_NV32)  
         /*����ѡ�е�ICS���ʱ��Դ��2��Ƶ*/      
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}

#else
	ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK));
       
#endif    
        OSC_Disable();            
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ  ��ICS�Ĺ���ģʽ�ɵ�ǰ��FEEģʽת���FBEģʽ
   *        
   * @ ����  pConfig  ָ�����ýṹ��
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/

void FEE_to_FBE(ICS_ConfigType *pConfig)
{
        /*LOLS����*/
	ICS->S |= ICS_S_LOLS_MASK;
	
	
        /* LP = 0 */
        /*ѡ���ⲿʱ����ΪICS���ʱ��Դ*/
        /* LP = 0 ��bypassģʽFLL���ᱻ��ֹ*/

	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 

        /*�ȴ����ʱ��Դ�����ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);
	
   /* ����ICS���ʱ��Դѡ���ⲿʱ��Դ
	 * ע��: ȷ���ⲿʱ��Ƶ����20MHz����
	 */
#if defined(CPU_NV32)
        /*��ѡ���ICS���ʱ��Դ��2��Ƶ*/	 
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBIģʽת����FBEģʽ
   *        
   * @ ����  pConfig   ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FBE(ICS_ConfigType *pConfig)
{
	OSC_Init(&pConfig->oscConfig); /*��ʼ��OSC*/
    
	/* ѡ���ⲿʱ����ΪFLL�Ĳο�ʱ�� */
	/*ѡ���ⲿʱ����Ϊ���ʱ��Դ*/

       ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   


	/* �ȴ����ʱ��Դ�����ı� */

#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2); /*�ⲿʱ�ӳ�ΪICS���ʱ��Դ*/
	while((ICS->S & ICS_S_IREFST_MASK));/*�ⲿʱ�ӳ�ΪFLL�Ĳο�ʱ��*/

        /* ����ϵͳʱ��Դ���ⲿ�ο�ʱ��
	 * ע��:ȷ���ⲿʱ��Դ��Ƶ����20MHz��
	 */
#if defined(CPU_NV32)
         /*��ѡ�е�ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
}

/*****************************************************************************//**
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBIģʽת����FEEģʽ
   *        
   * @ ����  pConfig    ָ�����ýṹ�� 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FEE(ICS_ConfigType *pConfig)
{
	OSC_Init(&pConfig->oscConfig); /*��ʼ��OSC*/
 
	/* ѡ���ⲿʱ����ΪFLL�Ĳο�ʱ�� */
	/* ѡ��FLL�����Ϊ��ΪICS���ʱ��Դ*/

    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   

        /*�ȴ�ʱ��Դ�ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     

	while((ICS->S & ICS_S_CLKST_MASK));   /*FLLʱ�ӳ�ΪICS���ʱ��Դ*/
	while((ICS->S & ICS_S_IREFST_MASK));  /*�ⲿʱ�ӳ�ΪFLL�ο�ʱ��*/
	
     /* ����ϵͳʱ��ԴΪ�ⲿʱ��
	 * ע��: ȷ���ⲿʱ��Դ��Ƶ����20MHz��
	 */
#if defined(CPU_NV32)
        /*��ѡ�е�ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
       /*LOLS����*/
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBIģʽת����FBIPģʽ 
   * 
   * @ ����  pConfig   ���ָ�����ýṹ�� 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ ���� ���������ڵ��Խӿ�û��û�н��ߵ�״̬��
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FBILP(ICS_ConfigType *pConfig)
{
	/*
	 * �����ⲿ����ʱ8MHz����4MHz
	 */
	ICS->C2 |= ICS_C2_LP_MASK;	/*����͹���ģʽ */
}



/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBIģʽת��ΪFEIģʽ
   * 
   * @ ���� pConfig  ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBI_to_FEI(ICS_ConfigType *pConfig)
{
     /* ѡ���ڲ�ʱ��ΪFLL�Ĳο�ʱ�� */
	/*ѡ��FLL�����ΪICS���ʱ��Դ*/
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
        /*�ȴ�ʱ��Դ�����ı�*/

#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while((ICS->S & ICS_S_CLKST_MASK));    /*FLL�����ΪICS���ʱ��Դ*/
	while(!(ICS->S & ICS_S_IREFST_MASK));  /*FLL�Ĳο�ʱ��ѡ��Ϊ�ⲿʱ��*/

        
	/* 
	 * ����ICS���ʱ��ԴΪFLL���
	 */
#if defined(CPU_NV32)
         /*��ѡ�е�ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif

        /*LOLS���� */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ  ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBEģʽת����FBIģʽ
   *        
   * @ ����  pConfig   ָ�����ýṹ�� 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FBI(ICS_ConfigType *pConfig)
{
        /*ѡ���ڲ�ʱ����ΪFLL�Ĳο�ʱ��*/
	/*ѡ���ڲ�ʱ����ΪICS���ʱ��Դ*/
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);   
	
        /*�ȴ�ʱ��Դ�����ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) != 1);/*�ڲ�ʱ�ӳ�ΪICS���ʱ��Դ*/
	while(!(ICS->S & ICS_S_IREFST_MASK)); /*�ڲ�ʱ�ӳ�ΪFLL�Ĳο�ʱ��*/
	
	/* 
	 * ����ICS���ʱ��ԴΪ�ڲ�ʱ��
	 */
	 
#if defined(CPU_NV32)
        /*��ѡ�е�ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
        
    /* 
     * ����OSCģ��
     */
    OSC_Disable();
}


/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBEģʽת����FEEģʽ
   *        
   * @ ���� pConfig   ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FEE(ICS_ConfigType *pConfig)
{
	
        /*ѡ��FLL�����Ϊ���ʱ��Դ*/
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
        /*�ȴ�ICS���ʱ��Դ�����ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(ICS->S & ICS_S_CLKST_MASK);

	
	/* 
    * ����ICS���ʱ��ԴΪFLL���
	 * ע��: �ⲿʱ��Ƶ�� <= 20MHz
	 */
#if defined(CPU_NV32)
         /*��ѡ�е�ICS���ʱ��Դ��2��Ƶ*/
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif	
         /* LOLS���� */
	ICS->S |= ICS_S_LOLS_MASK;	
}


/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBEģʽת���FEIģʽ
   *        
   * @ ���� pConfig    ָ�����ýṹ�� 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FEI(ICS_ConfigType *pConfig)
{
    /* ѡ���ڲ�ʱ����ΪFLL�Ĳο�ʱ��*/
	/*ѡ��FLL�����ΪICS���ʱ��Դ*/

    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
        /*�ȴ�ʱ��Դ�ı�*/
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while((ICS->S & ICS_S_CLKST_MASK));   /*FLL�����ΪICS���ʱ��Դ*/
	while(!(ICS->S & ICS_S_IREFST_MASK)); /*�ڲ�ʱ���г�ΪFLL�ο�ʱ��*/

  /* 
   * ����FLL�����ΪICS���ʱ��Դ
   */

#if defined(CPU_NV32)

       /*��ѡ�е�ʱ��Դ��2��Ƶ*/	
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif	
         /*LOLS����*/
	ICS->S |= ICS_S_LOLS_MASK;	
        
    /*
     *����OSCģ��
     */
    OSC_Disable();
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBEģʽת��ΪFBELPģʽ
   *
   * @ ����  pConfig   ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBE_to_FBELP(ICS_ConfigType *pConfig)
{
	/* enter low power mode */
        /*����͹���ģʽ*/
 	ICS->C2 = ICS->C2 | (ICS_C2_LP_MASK); 
}
/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBELPģʽת����FBEģʽ
   * 
   * @ ����  pConfig     ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBELP_to_FBE(ICS_ConfigType *pConfig)
{
	/* enter low power mode */
        /*���õ͹���ģʽ*/
 	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICS�Ĺ���ģʽ�ɵ�ǰ��FBILPת����FBIģʽ 
   * 
   * @ ����  pConfig  ָ�����ýṹ��. 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/
void FBILP_to_FBI(ICS_ConfigType *pConfig)
{
	/* enter low power mode */
        /*���õ͹���ģʽ*/
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ �����ڲ��ڲ�ʱ�� (IRC). 
   * 
   * @ ����  u16TrimValue   ����ֵ 
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   *****************************************************************************/

void ICS_Trim(uint16_t u16TrimValue)
{
   ICS->C3 =  (uint8_t) u16TrimValue;  /*������ֵд��Ĵ���*/
   ICS->C4 = (ICS->C4 & ~(ICS_C4_SCFTRIM_MASK)) | ((u16TrimValue>>8) & 0x01);
   while(!(ICS->S & ICS_S_LOCK_MASK));    
}
/*****************************************************************************//*!
   *
   * @ ��Ҫ ���ⲿ�ο�ʱ�ӽ��з�Ƶ��ʹ�÷�Ƶ�����FLL����������31.25k~39.0625k��
   *
   * @ ���� u32ClkFreqKHz    �ο�ʱ��Ƶ��.
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   *****************************************************************************/

void ICS_SetClkDivider(uint32_t u32ClkFreqKHz)
{
    
    switch(u32ClkFreqKHz)
    {
        case 8000L:
        case 10000L:
            /* 8MHz or 10MHz*/
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(3);	
                                                                         /*8MHz��Ƶ����� 8000/256 = 31.25K */ 
                                                                        /*10MHz��Ƶ����� 8000/256 = 31.25K*/ 
            break;
        case 4000L:
            /* 4MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(2);	
                                                                        /*4MHz��Ƶ����� 4000/128 = 31.25K*/
            break;
        case 12000L:
            /* 12MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(3);	
                                                                        /*12MHz��Ƶ�����12000/512 = 23.43K*/
            break;
        case 16000L:
            /* 16MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(4);	
                                                                        /* 16MHz��Ƶ����� 16000/512 = 31.25K */
            break;
        case 20000L:
            /* 20MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(4); 
                                                                        /*20MHz��Ƶ����� 20000/512 = 39.0625K */
            break;
        case 32L:
            /* 32KHz */
            ICS->C1  &= ~(ICS_C1_RDIV_MASK);
            break;
        default:
            break;
    }
}
/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ʼ��ICSģ����ݶ�������Ҫ������ʱ��Ƶ��.
   * 
   * @ ���� pConfig  ָ�����ýṹ��.  
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_ConfigType
   *****************************************************************************/


void ICS_Init(ICS_ConfigType *pConfig)
{
  if(pConfig->u8ClkMode == ICS_CLK_MODE_FEE)
  {    
        pConfig->oscConfig.bIsCryst = 1;   /* OSC�����ѡ��ѡ������ʱ��Դ */ 
        pConfig->oscConfig.bWaitInit = 1;  /* �ȴ�������ʼ������� */       
     
      /*ѡ��FEEģʽ��OSC���ѡ������ʱ��Դ*/
        FEI_to_FEE(pConfig);             
  }
  else if (pConfig->u8ClkMode == ICS_CLK_MODE_FEE_OSC)
  {     
        pConfig->oscConfig.bIsCryst = 0;     /*OSC���ʱ��ѡ��EEXTAL���ŵ��ⲿʱ��Դ*/ 

     /*ѡ��FEE����ģʽ��OSC���ʱ��ѡ��EEXTAL���ŵ��ⲿʱ��Դ*/
        FEI_to_FEE_OSC(pConfig);                
  }
  else if (pConfig->u8ClkMode == ICS_CLK_MODE_FBE_OSC)
  {
        pConfig->oscConfig.bIsCryst = 0;  /* is clock��OSC���ʱ��ѡ��EXTAL���ŵ��ⲿʱ��Դ */            
        /* ѡ��FBE����ģʽ��OSC���ʱ��ѡ��EXTAL���ŵ��ⲿʱ��Դ*/
        FEI_to_FBE_OSC(pConfig);               
  } 
	else if(pConfig->u8ClkMode == ICS_CLK_MODE_FBELP )
	{
	pConfig->oscConfig.bIsCryst = 1;        /* OSC�����ʱ��ѡ��ѡ������ʱ��Դ */
        pConfig->oscConfig.bWaitInit = 1;       /*�ȴ�������ʼ������� */		

        /* ѡ��FBEģʽ��OSC�����ʱ��ѡ��ѡ������ʱ��Դ*/
                    FEI_to_FBE(pConfig);    /*��ѡ��PBEģʽ*/            
		    FBE_to_FBELP(pConfig);   /*ѡ��FBELP*/
		    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
	}
		else if(pConfig->u8ClkMode == ICS_CLK_MODE_FBILP )
	{
       
            /* OSC���ʱ��ѡ��EXTAL���ŵ��ⲿʱ��Դ*/            
		    pConfig->oscConfig.bIsCryst = 0; 
     
            /* ѡ��FBEģʽ��OSC���ʱ��ѡ��EXTAL���ŵ��ⲿʱ��Դ*/
              FEI_to_FBI(pConfig);               
	      FBI_to_FBILP(pConfig); 
	      ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
	}
  else
  {
      
       /*ICSĬ�Ϲ���ģʽFEIģʽ*/
        #if defined(CPU_NV32)
        if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) == 1)
        {
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
        }
        #else
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
        #endif
  }

}
/*****************************************************************************//*!
   *
   * @ ��Ҫ ��ICSģ����Ĵ������и�λ.
   * 
   * @ �޲���   
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�  ICS_Init
   *****************************************************************************/

void ICS_DeInit(void)
{
    ICS->C1 = ICS_C1_DEFAULT;
    ICS->C2 = ICS_C2_DEFAULT;
    ICS->C3 = ICS_C3_DEFAULT;
    ICS->C4 = ICS_C4_DEFAULT;
    while(ICS->S != ICS_S_DEFAULT)
        ;       
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ͨ���趨�Ĳ�����ʼ��XOSC
   * 
   * @ ����  pConfig   ָ��osc���ýṹ��
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   *****************************************************************************/
void OSC_Init(OSC_ConfigType *pConfig)
{
	uint8   cr = 0;
	/* 
	 * 
	 */
	if(pConfig->bGain) /*����������ѡ��*/
	{
		/* high gain��ѡ�������ģʽ */
		cr |= OSC_CR_HGO_MASK ;		
	}  
	
	if(pConfig->bRange)  /*Ƶ�ʷ�Χ��ѡ��*/
	{
		cr |= OSC_CR_RANGE_MASK; /*ѡ���Ƶ��Χ */	
	}

	if(pConfig->bStopEnable) /*ֹͣģʽ�µ�OSCʹ��*/
	{
		cr |= OSC_CR_OSCSTEN_MASK; /*OSC��ֹͣģʽ�±���ʹ��*/
	}

	if(pConfig->bIsCryst)     /*OSC���ѡ��*/
	{
		cr |= OSC_CR_OSCOS_MASK; /*ѡ������ʱ��*/
	}

	if(pConfig->bEnable)  /*OSCʹ��*/
	{
		cr |= OSC_CR_OSCEN_MASK;
	}
    
    OSC->CR = cr;   /*��ֵд����ƼĴ���*/
    
	if(pConfig->bWaitInit)
	{

		/* 
     *�ȴ���ʼ�����
		 */
		while(!(OSC->CR & OSC_CR_OSCINIT_MASK));
		
	}
}

/*****************************************************************************//*!
   *
   * @ ��Ҫ ����OSCģ�飬ʹ��ָ���Ĭ��״̬.
   * 
   * @ �������      
   *
   * @ �޷���
   *
   * @ �ɹ�/ʧ�ܵı�׼ ����
   * @ �ο�   ICS_Init
   *****************************************************************************/

void OSC_DeInit(void)
{
    OSC->CR = OSC_CR_DEFAULT;
}
                                                	




