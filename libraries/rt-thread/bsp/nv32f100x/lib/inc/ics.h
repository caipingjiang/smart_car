/******************************************************************************
*
* @brief  ICS ����ͷ�ļ�.  
*
******************************************************************************/
#ifndef ICS_H_
#define ICS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
/****************************************************************************!
 * @brief ʱ��ģʽ��������
 *
 ***************************************************************************/
enum
{
    ICS_CLK_MODE_FEI = 1,       /*!< FEI ģʽ */
    ICS_CLK_MODE_FEE,           /*!< FEE ģʽ */
    ICS_CLK_MODE_FEE_OSC,       /*!< FEE ģʽ OSC���ʱ��Դѡ������EXTAL���ŵ��ⲿʱ��Դ */    
    ICS_CLK_MODE_FBE,           /*!< FBE ģʽ */
    ICS_CLK_MODE_FBE_OSC,       /*!< FBE ģʽ OSC���ʱ��Դѡ������EXTAL���ŵ��ⲿʱ��Դ  */    
    ICS_CLK_MODE_FBI,           /*!< FBI ģʽ */
    ICS_CLK_MODE_FBILP,         /*!< FBILP ģʽ */    
    ICS_CLK_MODE_FBELP,         /*!< FBELP ģʽ */        
};			
  
/*****************************************************************************//*!
   *
   * @brief ��ʱ��ģʽ�ӵ�ǰģʽ�л�����һ��ʱ��ģʽ.
   *
   *  ʱ��ģʽ��۶�������:
   *      FEI, FBI, FEE, FBE, FBILP, FBELP, FEE_OSC, FBE_OSC
   *   ע��FEE_OSC, FBE_OSC ����������ǰʱ��ģʽ. ��ǰʱ��ģʽ��Ҫ�л�����ʱ��ģʽ������£� 
   *    < ��ǰʱ��ģʽ��Ҫ�л�����ʱ��ģʽ>     
   *    <FEI,FEE>, <FEI,FBI>, <FEI,FBE>, <FEI,FBE_OSC>, <FEI,FEE_OSC>, <FEE,FEI>,
   *    <FEE,FBI>, <FEE,FBE>, <FBI,FBE>, <FBI,FEE>, <FBI,FBILP>, <FBI,FEI>,
   *    <FBE,FBI>, <FBE,FEE>, <FBE,FEI>, <FBE,FBELP>, <FBELP,FBE>, <FBILP,FBI>.
   *    
   * @param[in] CurMode   ��ǰʱ��ģʽ
   * @param[in] NewMode   Ҫ�л�����ʱ��ģʽ
   * @param[in] clkFreq     �ο�ʱ��Ƶ��
   *       
   * @return none
   * @warning   FEE_OSC, FBE_OSC ����������ǰʱ��ģʽ. 
   *
   *****************************************************************************/

#define ICS_SwitchMode(CurMode, NewMode, clkFreq)   CurMode##_to_##NewMode(clkFreq)
       
 
/******************************************************************************
* ���� OSC ���ýṹ��
*
*******************************************************************************/
typedef struct
{
	uint8_t bRange      : 1;        /*!< 1: ��Ƶ��Χ, 0: ��Ƶ��Χ */
	uint8_t bGain       : 1;        /*!< 1: ������, 0:������ */
	uint8_t bEnable     : 1;        /*!< 1: ʹ��OSC, 0: ����OSC */
	uint8_t bStopEnable : 1;        /*!< 1: ֹͣģʽ��OSCʹ��, 0: ֹͣģʽ��OSC���� */
	uint8_t bIsCryst    : 1;        /*!< 1: OSC���ѡ������ʱ��, 0: OSC���ѡ������extal���ŵ��ⲿʱ�� */
	uint8_t bWaitInit   : 1;        /*!< 1: �ȴ�������ʼ�����, 0: ���ȴ� */
} OSC_ConfigType, *OSC_ConfigPtr;



/******************************************************************************
* 
* ICS���ýṹ��
*
*******************************************************************************/
typedef struct
{
   uint8_t    u8ClkMode;        /*!< ѡ��ʱ��ģʽ*/
   uint8_t    bLPEnable;        /*!< �͹���ģʽ��ʹ�� */
   uint32_t   u32ClkFreq;       /*!< �ο�ʱ��Ƶ�� */  
   OSC_ConfigType  oscConfig;   /*!< OSC ���� */
} ICS_ConfigType ;

/*****************************************************************************//*!
*
* @brief ʹ���ж�.
*        
* @param   none
*
* @return none
* 
* @see    ICS_DisableInt
*****************************************************************************/
__STATIC_INLINE void ICS_EnableInt(void)
{
    ICS->C4 |= (ICS_C4_LOLIE_MASK);    
}

/*****************************************************************************//*!
*
* @brief �����ж�
*        
* @param   none
*
* @return none
*
* @see    ICS_EnableInt
*****************************************************************************/
__STATIC_INLINE void ICS_DisableInt(void)
{
    ICS->C4 &= ~(ICS_C4_LOLIE_MASK);    
}

/*****************************************************************************//*!
*
* @brief ʹ��ʱ�Ӽ��
*        
* @param   none
*
* @return none
*
* @see    ICS_DisableClockMonitor
*****************************************************************************/
__STATIC_INLINE void ICS_EnableClockMonitor(void)
{
    ICS->C4 |= (ICS_C4_CME_MASK);    
}

/*****************************************************************************//*!
*
* @brief ����ʱ�Ӽ��
*        
* @param   none
*
* @return none
*
* @see    ICS_EnableClockMonitor
*****************************************************************************/
__STATIC_INLINE void ICS_DisableClockMonitor(void)
{
    ICS->C4 &= ~(ICS_C4_CME_MASK);    
}

/*****************************************************************************//*!
   *
   * @brief ����ICS���ʱ��Դ��Ƶ
   *        
   * @param[in] busDivide   -- ��Ƶֵ
   *
   * @return  depends on commands
   *****************************************************************************/
__STATIC_INLINE void ICS_SetBusDivider(uint8_t u8BusDivide)
{
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(u8BusDivide);
}


/*****************************************************************************//*!
*
* @brief ʹ��OSC
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_Enable(void)
{
    OSC->CR |= (OSC_CR_OSCEN_MASK);    
}

/*****************************************************************************//*!
*
* @brief ����OSC
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_Disable(void)
{
    OSC->CR &= ~(OSC_CR_OSCEN_MASK);    
}

/*****************************************************************************//*!
*
* @brief ����OSCģ���Ƶ�ʷ�ΧΪ��Ƶ��Χ
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetLowRange(void)
{
    OSC->CR &= ~(OSC_CR_RANGE_MASK);    
}

/*!***************************************************************************//*!
+FUNCTION----------------------------------------------------------------
*
* @brief ����OSCģ���Ƶ�ʷ�ΧΪ��Ƶ��Χ
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetHighRange(void)
{
    OSC->CR |= (OSC_CR_RANGE_MASK);    
}


/*****************************************************************************//*!
*
* @brief ����OSC�Ĺ���ģʽΪ������ģʽ
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetHighGain(void)
{
    OSC->CR |= (OSC_CR_HGO_MASK);    
}

/*****************************************************************************//*!
*
* @brief ����OSC�Ĺ���ģʽΪ�͹���ģʽ
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SetLowGain(void)
{
    OSC->CR &= ~(OSC_CR_HGO_MASK);    
}

/*****************************************************************************//*!
*
* @brief ѡ��OSCģ������ʱ��ԴΪ����ʱ��Դ
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SelectCrystal(void)
{
    OSC->CR |= (OSC_CR_OSCOS_MASK);    
}


/*****************************************************************************//*!
*
* @brief OSC���ѡ������extal���ŵ��ⲿʱ�� 
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_SelectClock(void)
{
    OSC->CR &= ~(OSC_CR_OSCOS_MASK);    
}

/*****************************************************************************//*!
*
* @brief ��ֹͣģʽ��OSCģ��ʹ��
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_ActiveInStop(void)
{
    OSC->CR |= (OSC_CR_OSCSTEN_MASK);    
}

/*****************************************************************************//*!
*
* @brief ��ֹͣģʽ��OSCģ�����
*        
* @param   none
*
* @return none
*
*****************************************************************************/
__STATIC_INLINE void OSC_InactiveInStop(void)
{
    OSC->CR &= ~(OSC_CR_OSCSTEN_MASK);    
}

/******************************************************************************/

void ICS_Init(ICS_ConfigType *pConfig);
void ICS_DeInit(void);
void ICS_SetClkDivider(uint32_t u32ClkFreqKHz);
void ICS_Trim(uint16 u16TrimValue);
void OSC_Init(OSC_ConfigType *pConfig);
void OSC_DeInit(void);

/************** �������� ******************/
void ICS_DisableClockMonitor(void);
void ICS_DisableInt(void);
void ICS_EnableClockMonitor(void);
void ICS_EnableInt(void);
void ICS_SetBusDivider(uint8_t u8BusDivide);
void OSC_ActiveInStop(void);
void OSC_Enable(void);
void OSC_Disable(void);
void OSC_InactiveInStop(void);
void OSC_SelectClock(void);
void OSC_SelectCrystal(void);
void OSC_SetHighGain(void);
void OSC_SetHighRange(void);
void OSC_SetLowGain(void);
void OSC_SetLowRange(void);

/* do not touch the following functions */
void FEI_to_FEE(ICS_ConfigType *pConfig);
void FEI_to_FBI(ICS_ConfigType *pConfig);
void FEI_to_FBE(ICS_ConfigType *pConfig);
void FEE_to_FBI(ICS_ConfigType *pConfig);
void FEE_to_FEI(ICS_ConfigType *pConfig);
void FEE_to_FBE(ICS_ConfigType *pConfig);
void FBE_to_FEE(ICS_ConfigType *pConfig);
void FBE_to_FEI(ICS_ConfigType *pConfig);
void FBE_to_FBI(ICS_ConfigType *pConfig);
void FBE_to_FBELP(ICS_ConfigType *pConfig);
void FBI_to_FEI(ICS_ConfigType *pConfig);
void FBI_to_FBE(ICS_ConfigType *pConfig);
void FBI_to_FEE(ICS_ConfigType *pConfig);
void FBI_to_FBILP(ICS_ConfigType *pConfig);
void FBILP_to_FBI(ICS_ConfigType *pConfig);
void FBELP_to_FBE(ICS_ConfigType *pConfig);
void FEI_to_FBE_OSC(ICS_ConfigType *pConfig);
void FEI_to_FEE_OSC(ICS_ConfigType *pConfig);
#ifdef __cplusplus
}
#endif
#endif 
