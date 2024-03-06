/**
  *********************************************************************************
  *
  * @file    ald_tsense.c
  * @brief   TSENSE module driver.
  *
  * @version V1.0
  * @date    15 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_tsense.h"
#include "ald_bkpc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup TSENSE TSENSE
  * @brief TSENSE module driver
  * @{
  */
#ifdef ALD_TSENSE


/** @defgroup TSENSE_Private_Variables TSENSE Private Variables
  * @{
  */
tsense_cbk __tsense_cbk;
/**
  * @}
  */

/** @defgroup TSENSE_Public_Functions TSENSE Public Functions
  * @{
  */

/** @addtogroup TSENSE_Public_Functions_Group1 Initialization functions
  * @brief Initialization functions
  *
  * @verbatim
  ==============================================================================
              ##### Initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to initialize the TSENSE:
      (+) This parameters can be configured:
        (++) Update Cycle
        (++) Output Mode
        (++) Perscaler
      (+) Select TSENSE source clock(default LOSC)

    @endverbatim
  * @{
  */

/**
  * @brief  Initializes the TSENSE according to the specified
  *         parameters in the tsense_init_t.
  * @param  init: Pointer to a tsense_init_t structure that contains
  *         the configuration information.
  * @retval None
  */
void ald_tsense_init(tsense_init_t *init)
{
    assert_param(IS_TSENSE_UPDATE_CYCLE(init->cycle));
    assert_param(IS_TSENSE_OUTPUT_MODE(init->mode));

    TSENSE_UNLOCK();
    TSENSE->CR = 0;

    MODIFY_REG(TSENSE->CR, TSENSE_CR_TSU_MSK, init->cycle << TSENSE_CR_TSU_POSS);
    MODIFY_REG(TSENSE->CR, TSENSE_CR_TOM_MSK, init->mode << TSENSE_CR_TOM_POSS);
    MODIFY_REG(TSENSE->CR, TSENSE_CR_CTN_MSK, init->ctn << TSENSE_CR_CTN_POS);
    MODIFY_REG(TSENSE->PSR, TSENSE_PSR_PRS_MSK, init->psc << TSENSE_PSR_PRS_POSS);
    TSENSE_LOCK();

    return;
}

/**
  * @brief  Configure the TSENSE source.
  * @param  sel: TSENSE source type.
  * @retval None
  */
void ald_tsense_source_select(tsense_source_sel_t sel)
{
    assert_param(IS_TSENSE_SOURCE_SEL(sel));

    BKPC_UNLOCK();
    MODIFY_REG(BKPC->PCCR, BKPC_PCCR_TSENSECS_MSK, sel << BKPC_PCCR_TSENSECS_POSS);

    if (sel == TSENSE_SOURCE_LOSC)
    {
        SET_BIT(BKPC->CR, BKPC_CR_LOSCEN_MSK);
    }
    else if (sel == TSENSE_SOURCE_LRC)
    {
        SET_BIT(BKPC->CR, BKPC_CR_LRCEN_MSK);
    }
    else
    {
        ; /* do nothing */
    }

    BKPC_LOCK();
    return;
}
/**
  * @}
  */

/** @addtogroup TSENSE_Public_Functions_Group2 Peripheral Control functions
  * @brief Peripheral Control functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral Control functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) ald_tsense_get_value() API can get the current temperature.
    (+) ald_tsense_get_value_by_it() API can get the current temperature by interrupt.
    (+) ald_tsense_irq_handler() API can handle the interrupt request.

    @endverbatim
  * @{
  */

/**
  * @brief  Get the current temperature
  * @param  tsense: The value of current temperature.
  * @retval ALD status:
  *         @arg @ref OK    The value is valid
  *         @arg @ref ERROR The value is invalid
  */
ald_status_t ald_tsense_get_value(uint16_t *tsense)
{
    uint32_t tmp = 0;

    TSENSE_UNLOCK();
    SET_BIT(TSENSE->IFCR, TSENSE_IFCR_TSENSE_MSK);
    SET_BIT(TSENSE->CR, TSENSE_CR_EN_MSK);
    TSENSE_LOCK();

    while ((!(READ_BIT(TSENSE->IF, TSENSE_IF_TSENSE_MSK))) && (tmp++ < 1000000));

    if (tmp >= 1000000)
        return TIMEOUT;

    TSENSE_UNLOCK();
    SET_BIT(TSENSE->IFCR, TSENSE_IFCR_TSENSE_MSK);
    TSENSE_LOCK();

    if (READ_BIT(TSENSE->DR, TSENSE_DR_ERR_MSK))
        return ERROR;

    *tsense = READ_BITS(TSENSE->DR, TSENSE_DR_DATA_MSK, TSENSE_DR_DATA_POSS);
    return OK;
}

/**
  * @brief  Get the current temperature by interrupt
  * @param  cbk: The callback function
  * @retval None
  */
void ald_tsense_get_value_by_it(tsense_cbk cbk)
{
    __tsense_cbk = cbk;

    TSENSE_UNLOCK();
    SET_BIT(TSENSE->IFCR, TSENSE_IFCR_TSENSE_MSK);
    SET_BIT(TSENSE->IE, TSENSE_IE_TSENSE_MSK);
    SET_BIT(TSENSE->CR, TSENSE_CR_EN_MSK);
    TSENSE_LOCK();

    return;
}

/**
  * @brief  This function handles TSENSE interrupt request.
  * @retval None
  */
void ald_tsense_irq_handler(void)
{
    TSENSE_UNLOCK();
    SET_BIT(TSENSE->IFCR, TSENSE_IFCR_TSENSE_MSK);
    TSENSE_LOCK();

    if (__tsense_cbk == NULL)
        return;

    if (READ_BIT(TSENSE->DR, TSENSE_DR_ERR_MSK))
    {
        __tsense_cbk(0, ERROR);
        return;
    }

    __tsense_cbk(READ_BITS(TSENSE->DR, TSENSE_DR_DATA_MSK, TSENSE_DR_DATA_POSS), OK);

    TSENSE_UNLOCK();
    SET_BIT(TSENSE->IFCR, TSENSE_IFCR_TSENSE_MSK);
    TSENSE_LOCK();
    return;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_TSENSE */
/**
  * @}
  */

/**
  * @}
  */
