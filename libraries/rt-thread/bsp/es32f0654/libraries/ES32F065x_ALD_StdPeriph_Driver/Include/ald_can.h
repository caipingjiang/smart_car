/**
  ******************************************************************************
  * @file    ald_can.h
  * @brief   Header file of CAN Module driver.
  *
  * @version V1.0
  * @date    16 Apr 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ******************************************************************************
  */

#ifndef __ALD_CAN_H
#define __ALD_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup CAN
  * @{
  */

/** @defgroup CAN_Public_Types CAN Public Types
  * @{
  */
/**
  * @brief  ALD State structures definition
  */
typedef enum
{
    CAN_STATE_RESET      = 0x00,    /**< CAN not yet initialized or disabled */
    CAN_STATE_READY      = 0x01,    /**< CAN initialized and ready for use */
    CAN_STATE_BUSY       = 0x02,    /**< CAN process is ongoing */
    CAN_STATE_BUSY_TX    = 0x11,    /**< CAN process is ongoing */
    CAN_STATE_BUSY_RX    = 0x21,    /**< CAN process is ongoing */
    CAN_STATE_BUSY_TX_RX = 0x31,    /**< CAN process is ongoing */
    CAN_STATE_TIMEOUT    = 0x03,    /**< CAN in Timeout state */
    CAN_STATE_ERROR      = 0x04,    /**< CAN error state */
} can_state_t;

/**
  * @brief CAN Error Code
  */
typedef enum
{
    CAN_ERROR_NONE = 0x00,      /**< No error */
    CAN_ERROR_EWG  = 0x01,      /**< EWG error */
    CAN_ERROR_EPV  = 0x02,      /**< EPV error */
    CAN_ERROR_BOF  = 0x04,      /**< BOF error */
    CAN_ERROR_STF  = 0x08,      /**< Stuff error */
    CAN_ERROR_FOR  = 0x10,      /**< Form error */
    CAN_ERROR_ACK  = 0x20,      /**< Acknowledgment error */
    CAN_ERROR_BR   = 0x40,      /**< Bit recessive */
    CAN_ERROR_BD   = 0x80,      /**< LEC dominant */
    CAN_ERROR_CRC  = 0x100,     /**< LEC transfer error */
} can_error_t;

/**
  * @brief CAN Operating Mode
  */
typedef enum
{
    CAN_MODE_NORMAL          =  0x00,   /**< Normal mode */
    CAN_MODE_LOOPBACK        =  0x01,   /**< Loopback mode */
    CAN_MODE_SILENT          =  0x02,   /**< Silent mode */
    CAN_MODE_SILENT_LOOPBACK =  0x03,   /**< Loopback combined with silent mode */
} can_operate_mode_t;

/**
  * @brief CAN Synchronization Jump Width
  */
typedef enum
{
    CAN_SJW_1 = 0x0,    /**< 1 time quantum */
    CAN_SJW_2 = 0x1,    /**< 2 time quantum */
    CAN_SJW_3 = 0x2,    /**< 3 time quantum */
    CAN_SJW_4 = 0x3,    /**< 4 time quantum */
} can_sjw_t;

/**
  * @brief CAN Time Quantum in Bit Segment 1
  */
typedef enum
{
    CAN_SEG1_1  = 0x0,  /**< 1 time quantum */
    CAN_SEG1_2  = 0x1,  /**< 2 time quantum */
    CAN_SEG1_3  = 0x2,  /**< 3 time quantum */
    CAN_SEG1_4  = 0x3,  /**< 4 time quantum */
    CAN_SEG1_5  = 0x4,  /**< 5 time quantum */
    CAN_SEG1_6  = 0x5,  /**< 6 time quantum */
    CAN_SEG1_7  = 0x6,  /**< 7 time quantum */
    CAN_SEG1_8  = 0x7,  /**< 8 time quantum */
    CAN_SEG1_9  = 0x8,  /**< 9 time quantum */
    CAN_SEG1_10 = 0x9,  /**< 10 time quantum */
    CAN_SEG1_11 = 0xA,  /**< 11 time quantum */
    CAN_SEG1_12 = 0xB,  /**< 12 time quantum */
    CAN_SEG1_13 = 0xC,  /**< 13 time quantum */
    CAN_SEG1_14 = 0xD,  /**< 14 time quantum */
    CAN_SEG1_15 = 0xE,  /**< 15 time quantum */
    CAN_SEG1_16 = 0xF,  /**< 16 time quantum */
} can_seg1_t;

/**
  * @brief CAN Time Quantum in Bit Segment 2
  */
typedef enum
{
    CAN_SEG2_1 = 0x0,   /**< 1 time quantum */
    CAN_SEG2_2 = 0x1,       /**< 2 time quantum */
    CAN_SEG2_3 = 0x2,       /**< 3 time quantum */
    CAN_SEG2_4 = 0x3,       /**< 4 time quantum */
    CAN_SEG2_5 = 0x4,       /**< 5 time quantum */
    CAN_SEG2_6 = 0x5,       /**< 6 time quantum */
    CAN_SEG2_7 = 0x6,       /**< 7 time quantum */
    CAN_SEG2_8 = 0x7,       /**< 8 time quantum */
} can_seg2_t;

/**
  * @brief CAN Filter Mode
  */
typedef enum
{
    CAN_FILTER_MODE_MASK = 0x0, /**< Identifier mask mode */
    CAN_FILTER_MODE_LIST = 0x1, /**< Identifier list mode */
} can_filter_mode_t;

/**
  * @brief CAN Filter Scale
  */
typedef enum
{
    CAN_FILTER_SCALE_16 = 0x0,  /**< Two 16-bit filters */
    CAN_FILTER_SCALE_32 = 0x1,  /**< One 32-bit filter */
} can_filter_scale_t;

/**
  * @brief CAN Filter fifo
  */
typedef enum
{
    CAN_FILTER_FIFO0 = 0x0, /**< FIFO 0 assignment for filter */
    CAN_FILTER_FIFO1 = 0x1, /**< FIFO 1 assignment for filter */
} can_filter_fifo_t;

/**
  * @brief CAN Identifier Type
  */
typedef enum
{
    CAN_ID_STD = 0x0,   /**< Standard Id */
    CAN_ID_EXT = 0x1,   /**< Extended Id */
} can_id_type_t;

/**
  * @brief CAN Remote Transmission Request
  */
typedef enum
{
    CAN_RTR_DATA   = 0x0,   /**< Data frame */
    CAN_RTR_REMOTE = 0x1,   /**< Remote frame */
} can_remote_req_t;

/**
  * @brief CAN Transmit Constants
  */
typedef enum
{
    CAN_TX_MAILBOX_0    = 0x0,  /**< TX mailbox index 0 */
    CAN_TX_MAILBOX_1    = 0x1,  /**< TX mailbox index 1 */
    CAN_TX_MAILBOX_2    = 0x2,  /**< TX mailbox index 2 */
    CAN_TX_MAILBOX_NONE = 0x3,  /**< MailBox can't be used */
} can_tx_mailbox_t;

/**
  * @brief  CAN Receive fifo Number
  */
typedef enum
{
    CAN_RX_FIFO0 = 0x0, /**< CAN fifo 0 used to receive */
    CAN_RX_FIFO1 = 0x1, /**< CAN fifo 1 used to receive */
} can_rx_fifo_t;

/**
  * @brief  CAN Flags
  */
typedef enum
{
    CAN_FLAG_SLAK  = (1U << 1),         /**< Sleep acknowledge flag */
    CAN_FLAG_WKU   = (1U << 3),         /**< Wake up flag */
    CAN_FLAG_SLAKI = (1U << 4),         /**< Sleep acknowledge flag */
    CAN_FLAG_RQCP0 = (1U << 20) | (1U << 0),    /**< Request MailBox0 flag */
    CAN_FLAG_TXOK0 = (1U << 20) | (1U << 1),    /**< Transmission OK MailBox0 flag */
    CAN_FLAG_RQCP1 = (1U << 20) | (1U << 8),    /**< Request MailBox1 flag */
    CAN_FLAG_TXOK1 = (1U << 20) | (1U << 9),    /**< Transmission OK MailBox1 flag */
    CAN_FLAG_RQCP2 = (1U << 20) | (1U << 16),   /**< Request MailBox2 flag */
    CAN_FLAG_TXOK2 = (1U << 20) | (1U << 17),   /**< Transmission OK MailBox2 flag */
    CAN_FLAG_TME0  = (1U << 20) | (1U << 26),   /**< Transmit mailbox 0 empty flag */
    CAN_FLAG_TME1  = (1U << 20) | (1U << 27),   /**< Transmit mailbox 1 empty flag */
    CAN_FLAG_TME2  = (1U << 20) | (1U << 28),   /**< Transmit mailbox 2 empty flag */
    CAN_FLAG_FF0   = (2U << 20) | (1U << 3),    /**< FIFO 0 Full flag */
    CAN_FLAG_FOV0  = (2U << 20) | (1U << 4),    /**< FIFO 0 Overrun flag */
    CAN_FLAG_FF1   = (3U << 20) | (1U << 3),    /**< FIFO 1 Full flag */
    CAN_FLAG_FOV1  = (3U << 20) | (1U << 4),    /**< FIFO 1 Overrun flag */
    CAN_FLAG_EWG   = (4U << 20) | (1U << 0),    /**< Error warning flag */
    CAN_FLAG_EPV   = (4U << 20) | (1U << 1),    /**< Error passive flag */
    CAN_FLAG_BOF   = (4U << 20) | (1U << 2),    /**< Bus-Off flag */
} can_flag_t;

/**
  * @brief CAN Interrupts
  */
typedef enum
{
    CAN_IT_TME  = (1U << 0),    /**< Transmit mailbox empty interrupt bit */
    CAN_IT_FMP0 = (1U << 1),    /**< FIFO0 message pending interrupt bit */
    CAN_IT_FF0  = (1U << 2),    /**< FIFO0 full interrupt bit */
    CAN_IT_FOV0 = (1U << 3),    /**< FIFO0 overrun interrupt bit */
    CAN_IT_FMP1 = (1U << 4),    /**< FIFO1 message pending interrupt bit */
    CAN_IT_FF1  = (1U << 5),    /**< FIFO1 full interrupt bit */
    CAN_IT_FOV1 = (1U << 6),    /**< FIFO1 overrun interrupt bit */
    CAN_IT_EWG  = (1U << 8),    /**< Error warning interrupt bit */
    CAN_IT_EPV  = (1U << 9),    /**< Error passive interrupt bit */
    CAN_IT_BOF  = (1U << 10),   /**< Bus-off interrupt bit */
    CAN_IT_LEC  = (1U << 11),   /**< Last error code interrupt bit */
    CAN_IT_ERR  = (1U << 15),   /**< Error interrupt bit */
    CAN_IT_WKU  = (1U << 16),   /**< wake-up interrupt bit */
    CAN_IT_SLK  = (1U << 17),   /**< sleep interrupt bit */
} can_it_t;

/**
  * @brief CAN filter configuration structure definition
  */
typedef struct
{
    uint32_t id_high;       /**< Specifies the filter identification number */
    uint32_t id_low;        /**< Specifies the filter identification number */
    uint32_t mask_id_high;      /**< Specifies the filter mask number or identification number */
    uint32_t mask_id_low;       /**< Specifies the filter mask number or identification number */
    can_filter_fifo_t fifo;     /**< Specifies the fifo (0 or 1) which will be assigned to the filter. */
    uint32_t number;        /**< Specifies the filter which will be initialized. */
    can_filter_mode_t mode;     /**< Specifies the filter mode to be initialized. */
    can_filter_scale_t scale;   /**< Specifies the filter scale. */
    type_func_t active;     /**< Enable or disable the filter. */
    uint32_t bank_number;       /**< Select the start slave bank filter. */
} can_filter_t;

/**
  * @brief CAN init structure definition
  */
typedef struct
{
    uint32_t psc;           /**< Specifies the length of a time quantum. */
    can_operate_mode_t mode;    /**< Specifies the CAN operating mode. */
    can_sjw_t sjw;          /**< Specifies the maximum number of time quanta the CAN hardware is
                                           allowed to lengthen or shorten a bit to perform resynchronization. */
    can_seg1_t seg1;            /**< Specifies the number of time quanta in Bit Segment 1. */
    can_seg2_t seg2;            /**< Specifies the number of time quanta in Bit Segment 2. */
    type_func_t ttcm;       /**< Enable or disable the time triggered communication mode. */
    type_func_t abom;       /**< Enable or disable the automatic bus-off management. */
    type_func_t awk;        /**< Enable or disable the automatic wake-up mode. */
    type_func_t artx;       /**< Enable or disable the non-automatic retransmission mode. */
    type_func_t rfom;       /**< Enable or disable the Receive fifo Locked mode. */
    type_func_t txmp;       /**< Enable or disable the transmit fifo priority. */
} can_init_t;

/**
  * @brief CAN Tx message structure definition
  */
typedef struct
{
    uint32_t std;       /**< Specifies the standard identifier. */
    uint32_t ext;       /**< Specifies the extended identifier. */
    can_id_type_t type; /**< Specifies the type of identifier for the message that will be transmitted. */
    can_remote_req_t rtr;   /**< Specifies the type of frame for the message that will be transmitted. */
    uint32_t len;       /**< Specifies the length of the frame that will be transmitted. */
    uint8_t data[8];    /**< Contains the data to be transmitted. */
} can_tx_msg_t;

/**
  * @brief CAN Rx message structure definition
  */
typedef struct
{
    uint32_t std;       /**< Specifies the standard identifier. */
    uint32_t ext;       /**< Specifies the extended identifier. */
    can_id_type_t type; /**< Specifies the type of identifier for the message that will be received. */
    can_remote_req_t rtr;   /**< Specifies the type of frame for the received message. */
    uint32_t len;       /**< Specifies the length of the frame that will be received. */
    uint8_t data[8];    /**< Contains the data to be received. */
    uint32_t fmi;       /**< Specifies the index of the filter the message stored in the mailbox passes through. */
    can_rx_fifo_t num;  /**< Specifies the receive fifo number. */
} can_rx_msg_t;

/**
  * @brief CAN handle Structure definition
  */
typedef struct can_handle_s
{
    CAN_TypeDef *perh;  /**< Register base address */
    can_init_t init;    /**< CAN required parameters */
    can_rx_msg_t *rx_msg;   /**< Pointer to receive message */
    lock_state_t lock;  /**< CAN locking object */
    can_state_t state;  /**< CAN communication state */
    can_error_t err;    /**< CAN Error code */

    void (*tx_cplt_cbk)(struct can_handle_s *arg);  /**< Tx completed callback */
    void (*rx_cplt_cbk)(struct can_handle_s *arg);  /**< Rx completed callback */
    void (*error_cbk)(struct can_handle_s *arg);    /**< error callback */
} can_handle_t;
/**
  * @}
  */

/** @defgroup CAN_Public_Macro CAN Public Macros
  * @{
  */
#define CAN_RESET_HANDLE_STATE(x)   ((x)->state = CAN_STATE_RESET)
#define CAN_RX_MSG_PENDING(x, y)    (((y) == CAN_RX_FIFO0) ? \
    (READ_BIT((x)->perh->RXF0, CAN_RXF0_PEND_MSK)) : (READ_BIT((x)->perh->RXF1, CAN_RXF1_PEND_MSK)))
#define CAN_DBG_FREEZE(x, y)    (MODIFY_REG((x)->perh->CON, CAN_CON_DBGSTP_MSK, (y) << CAN_CON_DBGSTP_POS))
/**
  * @}
  */

/** @defgroup CAN_Private_Macros CAN Private Macros
  * @{
  */
#define IS_CAN_ALL(x)   ((x) == CAN0)
#define IS_CAN_FILTER_NUMBER(x) ((x) <= 13)
#define IS_CAN_MODE(x)  (((x) == CAN_MODE_NORMAL)   || \
                         ((x) == CAN_MODE_LOOPBACK) || \
                         ((x) == CAN_MODE_SILENT)   || \
                         ((x) == CAN_MODE_SILENT_LOOPBACK))
#define IS_CAN_SJW(x)   (((x) == CAN_SJW_1) || \
                         ((x) == CAN_SJW_2) || \
                         ((x) == CAN_SJW_3) || \
                         ((x) == CAN_SJW_4))
#define IS_CAN_BS1(x)   ((x) <= CAN_SEG1_16)
#define IS_CAN_BS2(x)   ((x) <= CAN_SEG2_8)
#define IS_CAN_FILTER_MODE(x)   (((x) == CAN_FILTER_MODE_MASK) || \
                                 ((x) == CAN_FILTER_MODE_LIST))
#define IS_CAN_FILTER_SCALE(x)  (((x) == CAN_FILTER_SCALE_16) || \
                                 ((x) == CAN_FILTER_SCALE_32))
#define IS_CAN_FILTER_FIFO(x)   (((x) == CAN_FILTER_FIFO0) || \
                                 ((x) == CAN_FILTER_FIFO1))
#define IS_CAN_IDTYPE(x)    (((x) == CAN_ID_STD) || \
                                 ((x) == CAN_ID_EXT))
#define IS_CAN_RTR(x)   (((x) == CAN_RTR_DATA) || ((x) == CAN_RTR_REMOTE))
#define IS_CAN_FIFO(x)  (((x) == CAN_RX_FIFO0) || ((x) == CAN_RX_FIFO1))
#define IS_CAN_BANKNUMBER(x)    ((x) <= 28)
#define IS_CAN_TX_MAILBOX(x)    ((x) <= CAN_TX_MAILBOX_NONE)
#define IS_CAN_STDID(x)     ((x) <= ((uint32_t)0x7FF))
#define IS_CAN_EXTID(x)     ((x) <= ((uint32_t)0x1FFFFFFF))
#define IS_CAN_DATA_LEN(x)  ((x) <= ((uint8_t)0x08))
#define IS_CAN_PRESCALER(x) (((x) >= 1) && ((x) <= 1024))
#define IS_CAN_GET_FLAG(x)  (((x)  == CAN_FLAG_SLAK)  || \
                                  ((x) == CAN_FLAG_WKU)   || \
                                  ((x) == CAN_FLAG_SLAKI) || \
                                  ((x) == CAN_FLAG_RQCP0) || \
                                  ((x) == CAN_FLAG_TXOK0) || \
                                  ((x) == CAN_FLAG_RQCP1) || \
                                  ((x) == CAN_FLAG_TXOK1) || \
                                  ((x) == CAN_FLAG_RQCP2) || \
                                  ((x) == CAN_FLAG_TXOK2) || \
                                  ((x) == CAN_FLAG_TME0)  || \
                                  ((x) == CAN_FLAG_TME1)  || \
                                  ((x) == CAN_FLAG_TME2)  || \
                                  ((x) == CAN_FLAG_FF0)   || \
                                  ((x) == CAN_FLAG_FOV0)  || \
                                  ((x) == CAN_FLAG_FF1)   || \
                                  ((x) == CAN_FLAG_FOV1)  || \
                                  ((x) == CAN_FLAG_EWG)   || \
                                  ((x) == CAN_FLAG_EPV)   || \
                                  ((x) == CAN_FLAG_BOF))
#define IS_CAN_CLEAR_FLAG(x)    (((x)  == CAN_FLAG_WKU)   || \
                                  ((x) == CAN_FLAG_SLAKI) || \
                                  ((x) == CAN_FLAG_RQCP0) || \
                                  ((x) == CAN_FLAG_RQCP1) || \
                                  ((x) == CAN_FLAG_RQCP2) || \
                                  ((x) == CAN_FLAG_FF0)   || \
                                  ((x) == CAN_FLAG_FOV0)  || \
                                  ((x) == CAN_FLAG_FF1)   || \
                                  ((x) == CAN_FLAG_FOV1))
#define IS_CAN_IT(x)        (((x)  == CAN_IT_TME)   || \
                                  ((x) == CAN_IT_FMP0) || \
                                  ((x) == CAN_IT_FF0) || \
                                  ((x) == CAN_IT_FOV0) || \
                                  ((x) == CAN_IT_FMP1) || \
                                  ((x) == CAN_IT_FF1)   || \
                                  ((x) == CAN_IT_FOV1)  || \
                                  ((x) == CAN_IT_EWG)   || \
                  ((x) == CAN_IT_EPV) || \
                                  ((x) == CAN_IT_BOF) || \
                                  ((x) == CAN_IT_LEC) || \
                                  ((x) == CAN_IT_ERR)   || \
                                  ((x) == CAN_IT_WKU)  || \
                                  ((x) == CAN_IT_SLK))
#define CAN_TIMEOUT_VALUE   100
#define CAN_STATE_TX_MASK   (1U << 4)
#define CAN_STATE_RX_MASK   (1U << 5)
/**
  * @}
  */

/** @addtogroup CAN_Public_Functions
  * @{
  */

/** @addtogroup CAN_Public_Functions_Group1
  *  @{
  */
/* Initialization functions */
void can_reset(can_handle_t *hperh);
ald_status_t can_init(can_handle_t *hperh);
ald_status_t can_filter_config(can_handle_t *hperh, can_filter_t *config);
/**
  * @}
  */

/** @addtogroup CAN_Public_Functions_Group2
  * @{
  */
/* IO operation functions */
ald_status_t can_send(can_handle_t *hperh, can_tx_msg_t *msg, uint32_t timeout);
ald_status_t can_send_by_it(can_handle_t *hperh, can_tx_msg_t *msg);
ald_status_t can_recv(can_handle_t *hperh, can_rx_fifo_t num, can_rx_msg_t *msg, uint32_t timeout);
ald_status_t can_recv_by_it(can_handle_t *hperh, can_rx_fifo_t num, can_rx_msg_t *msg);
/**
  * @}
  */

/** @addtogroup CAN_Public_Functions_Group3
  * @{
  */
/* Control function */
ald_status_t can_sleep(can_handle_t *hperh);
ald_status_t can_wake_up(can_handle_t *hperh);
void can_cancel_send(can_handle_t *hperh, can_tx_mailbox_t box);
void can_irq_handler(can_handle_t *hperh);
type_bool_t can_get_tx_status(can_handle_t *hperh, can_tx_mailbox_t box);
void can_interrupt_config(can_handle_t *hperh, can_it_t it, type_func_t state);
it_status_t can_get_it_status(can_handle_t *hperh, can_it_t it);
flag_status_t can_get_flag_status(can_handle_t *hperh, can_flag_t flag);
void can_clear_flag_status(can_handle_t *hperh, can_flag_t flag);
/**
  * @}
  */

/** @addtogroup CAN_Public_Functions_Group4
  * @{
  */
/* State and Error functions */
can_state_t can_get_state(can_handle_t *hperh);
can_error_t can_get_error(can_handle_t *hperh);
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

#endif /* __ALD_CAN_H */
