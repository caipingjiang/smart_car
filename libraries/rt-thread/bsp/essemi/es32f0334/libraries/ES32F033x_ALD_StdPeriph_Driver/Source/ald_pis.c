/**
  *********************************************************************************
  *
  * @file    ald_pis.c
  * @brief   PIS module driver.
  *
  * @version V1.0
  * @date    27 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_pis.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup PIS PIS
  * @brief PIS module driver
  * @{
  */
#ifdef ALD_PIS

/** @defgroup PIS_Public_Functions PIS Public Functions
  * @{
  */

/** @defgroup PIS_Public_Functions_Group1 Initialization functions
  * @brief Initialization and Configuration functions
  * @{
  */

/**
  * @brief  Create the PIS mode according to the specified parameters in
  *         the pis_handle_t and create the associated handle.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_create(pis_handle_t *hperh)
{
    pis_divide_t temp;
    uint8_t clock_menu = 0;

    if (hperh == NULL)
        return ERROR;

    assert_param(IS_PIS_SRC(hperh->init.producer_src));
    assert_param(IS_PIS_TRIG(hperh->init.consumer_trig));
    assert_param(IS_PIS_CLOCK(hperh->init.producer_clk));
    assert_param(IS_PIS_CLOCK(hperh->init.consumer_clk));
    assert_param(IS_PIS_EDGE(hperh->init.producer_edge));

    __LOCK(hperh);
    hperh->perh = PIS;

    /* get location of consumer in channel and position of con0/con1
     * accord to comsumer_trig information */
    temp.HalfWord       = (hperh->init.consumer_trig);
    hperh->consumer_ch  = (pis_ch_t)(temp.ch);
    hperh->consumer_con = (pis_con_t)(temp.con);
    hperh->consumer_pos = (1 << temp.shift);

    /* union producer clock and consumer clock */
    clock_menu = (hperh->init.producer_clk << 4) | (hperh->init.consumer_clk);

    if (hperh->perh->CH_CON[hperh->consumer_ch] != 0)
    {
        __UNLOCK(hperh);
        return BUSY;
    }

    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SRCS_MSK, ((hperh->init.producer_src) >> 4) << PIS_CH0_CON_SRCS_POSS);
    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_MSIGS_MSK, ((hperh->init.producer_src) & 0xf) << PIS_CH0_CON_MSIGS_POSS);

    /* configure sync clock, judging by producer clock with consumer clock */
    switch (clock_menu)
    {
        case 0x00:
        case 0x11:
        case 0x22:
        case 0x33:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 0 << PIS_CH0_CON_SYNCSEL_POSS);
            break;

        case 0x01:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 5 << PIS_CH0_CON_SYNCSEL_POSS);
            break;

        case 0x02:
        case 0x12:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 6 << PIS_CH0_CON_SYNCSEL_POSS);
            break;

        case 0x21:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 4 << PIS_CH0_CON_SYNCSEL_POSS);
            break;

        case 0x30:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 1 << PIS_CH0_CON_SYNCSEL_POSS);
            break;

        case 0x31:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 2 << PIS_CH0_CON_SYNCSEL_POSS);
            break;

        case 0x32:
            MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_SYNCSEL_MSK, 3 << PIS_CH0_CON_SYNCSEL_POSS);

        default:
            break;
    }

    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_PULCK_MSK, hperh->init.consumer_clk << PIS_CH0_CON_PULCK_POSS);
    MODIFY_REG(hperh->perh->CH_CON[hperh->consumer_ch], PIS_CH0_CON_EDGS_MSK, hperh->init.producer_edge << PIS_CH0_CON_EDGS_POSS);
    hperh->check_info = hperh->perh->CH_CON[hperh->consumer_ch];

    /* enable consumer bit, switch pin of consumer */
    switch (hperh->consumer_con)
    {
        case PIS_CON_0:
            PIS->TAR_CON0 |= hperh->consumer_pos;
            break;

        case PIS_CON_1:
            PIS->TAR_CON1 |= hperh->consumer_pos;
            break;

        default:
            break;
    }

    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Destroy the PIS mode according to the specified parameters in
  *         the pis_init_t and create the associated handle.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_destroy(pis_handle_t *hperh)
{
    assert_param(IS_PIS(hperh->perh));

    if (hperh->check_info != hperh->perh->CH_CON[hperh->consumer_ch])
        return ERROR;

    __LOCK(hperh);

    CLEAR_BIT(PIS->CH_OER, (1 << hperh->consumer_ch));
    WRITE_REG(hperh->perh->CH_CON[hperh->consumer_ch], 0x0);

    switch (hperh->consumer_con)
    {
        case PIS_CON_0:
            PIS->TAR_CON0 &= ~(hperh->consumer_pos);
            break;

        case PIS_CON_1:
            PIS->TAR_CON1 &= ~(hperh->consumer_pos);
            break;

        default:
            break;
    }

    hperh->state = PIS_STATE_RESET;
    __UNLOCK(hperh);

    return OK;
}
/**
  * @}
  */

/** @defgroup PIS_Public_Functions_Group2 Operation functions
  * @brief PIS output enable or disable functions
  * @{
  */

/**
  * @brief  Start the PIS output function.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @param  ch: The PIS channel enable output
  *	    This parameter can be one of the following values:
  *		@arg PIS_OUT_CH_0
  *		@arg PIS_OUT_CH_1
  *		@arg PIS_OUT_CH_2
  *		@arg PIS_OUT_CH_3
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_output_start(pis_handle_t *hperh, pis_out_ch_t ch)
{
    assert_param(IS_PIS(hperh->perh));
    assert_param(IS_PIS_OUPUT_CH(ch));
    __LOCK(hperh);
    SET_BIT(PIS->CH_OER, (1 << ch));
    __UNLOCK(hperh);

    return OK;
}

/**
  * @brief  Stop the PIS output function.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @param  ch: The PIS channel disable output
  *	    This parameter can be one of the following values:
  *		@arg PIS_OUT_CH_0
  *		@arg PIS_OUT_CH_1
  *		@arg PIS_OUT_CH_2
  *		@arg PIS_OUT_CH_3
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_output_stop(pis_handle_t *hperh, pis_out_ch_t ch)
{
    assert_param(IS_PIS(hperh->perh));
    assert_param(IS_PIS_OUPUT_CH(ch));
    __LOCK(hperh);
    CLEAR_BIT(PIS->CH_OER, (1 << ch));
    __UNLOCK(hperh);

    return OK;
}
/**
  * @}
  */

/** @defgroup PIS_Public_Functions_Group3 Peripheral State and Errors functions
  *  @brief   PIS State and Errors functions
  * @{
  */

/**
  * @brief  Returns the PIS state.
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @retval ALD state
  */
pis_state_t ald_pis_get_state(pis_handle_t *hperh)
{
    assert_param(IS_PIS(hperh->perh));
    return hperh->state;
}

/**
  * @}
  */

/** @defgroup PIS_Public_Functions_Group4 modulate output functions
  *  @brief   PIS modulate output signal functions
  * @{
  */

/**
  * @brief  Config the PIS modulate signal function
  * @param  hperh: Pointer to a pis_handle_t structure that contains
  *         the configuration information for the specified PIS module.
  * @param  config: Pointer to a pis_modulate_config_t structure that
  *         contains the selected target (UART0,UART1,UART2,UART3 or
  *         LPUART0) how to modulate the target output signal.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_pis_modu_config(pis_handle_t *hperh, pis_modulate_config_t *config)
{
    assert_param(IS_PIS(hperh->perh));
    assert_param(IS_PIS_MODU_TARGET(config->target));
    assert_param(IS_PIS_MODU_LEVEL(config->level));
    assert_param(IS_PIS_MODU_SRC(config->src));
    assert_param(IS_PIS_MODU_CHANNEL(config->channel));
    __LOCK(hperh);

    switch (config->target)
    {
        case PIS_UART0_TX:
            MODIFY_REG(hperh->perh->UART0_TXMCR, PIS_TXMCR_TXMLVLS_MSK, config->level << PIS_TXMCR_TXMLVLS_POS);
            MODIFY_REG(hperh->perh->UART0_TXMCR, PIS_TXMCR_TXMSS_MSK, config->src << PIS_TXMCR_TXMSS_POSS);
            MODIFY_REG(hperh->perh->UART0_TXMCR, PIS_TXMCR_TXSIGS_MSK, config->channel << PIS_TXMCR_TXSIGS_POSS);
            break;

        case PIS_UART1_TX:
            MODIFY_REG(hperh->perh->UART1_TXMCR, PIS_TXMCR_TXMLVLS_MSK, config->level << PIS_TXMCR_TXMLVLS_POS);
            MODIFY_REG(hperh->perh->UART1_TXMCR, PIS_TXMCR_TXMSS_MSK, config->src << PIS_TXMCR_TXMSS_POSS);
            MODIFY_REG(hperh->perh->UART1_TXMCR, PIS_TXMCR_TXSIGS_MSK, config->channel << PIS_TXMCR_TXSIGS_POSS);
            break;

        case PIS_UART2_TX:
            MODIFY_REG(hperh->perh->UART2_TXMCR, PIS_TXMCR_TXMLVLS_MSK, config->level << PIS_TXMCR_TXMLVLS_POS);
            MODIFY_REG(hperh->perh->UART2_TXMCR, PIS_TXMCR_TXMSS_MSK, config->src << PIS_TXMCR_TXMSS_POSS);
            MODIFY_REG(hperh->perh->UART2_TXMCR, PIS_TXMCR_TXSIGS_MSK, config->channel << PIS_TXMCR_TXSIGS_POSS);
            break;

        case PIS_UART3_TX:
            MODIFY_REG(hperh->perh->UART3_TXMCR, PIS_TXMCR_TXMLVLS_MSK, config->level << PIS_TXMCR_TXMLVLS_POS);
            MODIFY_REG(hperh->perh->UART3_TXMCR, PIS_TXMCR_TXMSS_MSK, config->src << PIS_TXMCR_TXMSS_POSS);
            MODIFY_REG(hperh->perh->UART3_TXMCR, PIS_TXMCR_TXSIGS_MSK, config->channel << PIS_TXMCR_TXSIGS_POSS);
            break;

        case PIS_LPUART0_TX:
            MODIFY_REG(hperh->perh->LPUART0_TXMCR, PIS_TXMCR_TXMLVLS_MSK, config->level << PIS_TXMCR_TXMLVLS_POS);
            MODIFY_REG(hperh->perh->LPUART0_TXMCR, PIS_TXMCR_TXMSS_MSK, config->src << PIS_TXMCR_TXMSS_POSS);
            MODIFY_REG(hperh->perh->LPUART0_TXMCR, PIS_TXMCR_TXSIGS_MSK, config->channel << PIS_TXMCR_TXSIGS_POSS);
            break;

        default:
            break;
    }

    __UNLOCK(hperh);
    return OK;
}
/**
  * @}
  */
/**
  * @}
  */
#endif /* ALD_PIS */
/**
  * @}
  */
/**
  * @}
  */
