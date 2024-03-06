/**
  *********************************************************************************
  *
  * @file    ald_trng.h
  * @brief   Header file of TRNG module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_TRNG_H__
#define __ALD_TRNG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup TRNG
  * @{
  */

/** @defgroup TRNG_Public_Types TRNG Public Types
  * @{
  */
/**
  * @brief Data width
  */
typedef enum
{
    TRNG_DSEL_1B  = 0x0,	/**< 1-bit */
    TRNG_DSEL_8B  = 0x1,	/**< 8-bit */
    TRNG_DSEL_16B = 0x2,	/**< 16-bit */
    TRNG_DSEL_32B = 0x3,	/**< 32-bit */
} trng_data_width_t;

/**
  * @brief seed type
  */
typedef enum
{
    TRNG_SEED_TYPE_0    = 0x0,	/**< Using 0 as seed */
    TRNG_SEED_TYPE_1    = 0x1,	/**< Using 1 as seed */
    TRNG_SEED_TYPE_LAST = 0x2,	/**< Using last seed */
    TRNG_SEED_TYPE_SEED = 0x3,	/**< Using value of register */
} trng_seed_type_t;

/**
  * @brief TRNG init structure definition
  */
typedef struct
{
    trng_data_width_t data_width;	/**< The width of data */
    trng_seed_type_t seed_type;	/**< The seed type */
    uint32_t seed;			/**< The value of seed */
    uint16_t t_start;		/**< T(start) = T(hclk) * (t_start + 1), T(start) > 1ms */
    uint8_t adjc;			/**< Adjust parameter */
    type_func_t posten;		/**< Data back handle function  */
} trng_init_t;

/**
  * @brief TRNG state structures definition
  */
typedef enum
{
    TRNG_STATE_RESET = 0x0,	/**< Peripheral is not initialized */
    TRNG_STATE_READY = 0x1,	/**< Peripheral Initialized and ready for use */
    TRNG_STATE_BUSY  = 0x2,	/**< An internal process is ongoing */
    TRNG_STATE_ERROR = 0x4,	/**< Error */
} trng_state_t;

/**
  * @brief State type
  */
typedef enum
{
    TRNG_STATUS_START = (1U << 0),	/**< Start state */
    TRNG_STATUS_DAVLD = (1U << 1),	/**< Data valid state */
    TRNG_STATUS_SERR  = (1U << 2),	/**< Error state */
} trng_status_t;

/**
  * @brief Interrupt type
  */
typedef enum
{
    TRNG_IT_START = (1U << 0),	/**< Start */
    TRNG_IT_DAVLD = (1U << 1),	/**< Data valid */
    TRNG_IT_SERR  = (1U << 2),	/**< Error */
} trng_it_t;

/**
  * @brief Interrupt flag type
  */
typedef enum
{
    TRNG_IF_START = (1U << 0),	/**< Start */
    TRNG_IF_DAVLD = (1U << 1),	/**< Data valid */
    TRNG_IF_SERR  = (1U << 2),	/**< Error */
} trng_flag_t;

/**
  * @brief  TRNG Handle Structure definition
  */
typedef struct trng_handle_s
{
    TRNG_TypeDef *perh;	/**< Register base address */
    trng_init_t init;	/**< TRNG required parameters */
    uint32_t data;		/**< result data */
    lock_state_t lock; 	/**< Locking object */
    trng_state_t state;	/**< TRNG operation state */

    void (*trng_cplt_cbk)(struct trng_handle_s *arg); /**< Trng completed callback */
    void (*err_cplt_cbk)(struct trng_handle_s *arg);  /**< Trng error callback */
    void (*init_cplt_cbk)(struct trng_handle_s *arg); /**< Trng init completed callback */
} trng_handle_t;
/**
  * @}
  */

/** @defgroup TRNG_Public_Macros TRNG Public Macros
  * @{
  */
#define TRNG_ENABLE()		(SET_BIT(TRNG->CR, TRNG_CR_TRNGEN_MSK))
#define TRNG_DISABLE()		(CLEAR_BIT(TRNG->CR, TRNG_CR_TRNGEN_MSK))
#define TRNG_ADJM_ENABLE()	(SET_BIT(TRNG->CR, TRNG_CR_ADJM_MSK))
#define TRNG_ADJM_DISABLE()	(CLEAR_BIT(TRNG->CR, TRNG_CR_ADJM_MSK))
/**
  * @}
  */

/**
  * @defgroup TRNG_Private_Macros TRNG Private Macros
  * @{
  */
#define IS_TRNG_DATA_WIDTH(x)	(((x) == TRNG_DSEL_1B)  || \
                                 ((x) == TRNG_DSEL_8B)  || \
                                 ((x) == TRNG_DSEL_16B) || \
                                 ((x) == TRNG_DSEL_32B))
#define IS_TRNG_SEED_TYPE(x)	(((x) == TRNG_SEED_TYPE_0)    || \
                                 ((x) == TRNG_SEED_TYPE_1)    || \
                                 ((x) == TRNG_SEED_TYPE_LAST) || \
                                 ((x) == TRNG_SEED_TYPE_SEED))
#define IS_TRNG_STATUS(x)	(((x) == TRNG_STATUS_START)  || \
                             ((x) == TRNG_STATUS_DAVLD)  || \
                             ((x) == TRNG_STATUS_SERR))
#define IS_TRNG_IT(x)	(((x) == TRNG_IT_START)  || \
                         ((x) == TRNG_IT_DAVLD)  || \
                         ((x) == TRNG_IT_SERR))
#define IS_TRNG_FLAG(x)	(((x) == TRNG_IF_START)  || \
                         ((x) == TRNG_IF_DAVLD)  || \
                         ((x) == TRNG_IF_SERR))
#define IS_TRNG_ADJC(x)	((x) < 4)
/**
  * @}
  */

/** @addtogroup TRNG_Public_Functions
  * @{
  */
/** @addtogroup TRNG_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
extern ald_status_t ald_trng_init(trng_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup TRNG_Public_Functions_Group2
  * @{
  */
/* Control functions */
extern uint32_t ald_trng_get_result(trng_handle_t *hperh);
extern void ald_trng_interrupt_config(trng_handle_t *hperh, trng_it_t it, type_func_t state);
extern flag_status_t ald_trng_get_status(trng_handle_t *hperh, trng_status_t status);
extern it_status_t ald_trng_get_it_status(trng_handle_t *hperh, trng_it_t it);
extern flag_status_t ald_trng_get_flag_status(trng_handle_t *hperh, trng_flag_t flag);
extern void ald_trng_clear_flag_status(trng_handle_t *hperh, trng_flag_t flag);
extern void ald_trng_irq_handler(trng_handle_t *hperh);
/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __ALD_TRNG_H__ */
