/**
  *********************************************************************************
  *
  * @file    type.h
  * @brief   define type
  *
  * @version V1.0
  * @date    17 Apr 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __TYPE_H__
#define __TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#if defined (__CC_ARM)
#define __INLINE__		__inline
#define __STATIC_INLINE__	static __inline
#else
#define __INLINE__		inline
#define __STATIC_INLINE__	static inline
#endif

#define __isr__

typedef enum
{
    RESET = 0x0,
    SET   = 0x1,
} flag_status_t, it_status_t;

typedef enum
{
    BIT_RESET = 0x0,
    BIT_SET   = 0x1,
} bit_status_t;

typedef enum
{
    DISABLE = 0x0,
    ENABLE  = 0x1,
} type_func_t;
#define IS_FUNC_STATE(x)	(((x) == DISABLE) || ((x) == ENABLE))

typedef enum
{
    FALSE = 0x0,
    TRUE  = 0x1,
} type_bool_t;

typedef enum
{
    UNLOCK = 0x0,
    LOCK   = 0x1,
} lock_state_t;
#define IS_LOCK_STATE(x)	(((x) == UNLOCK) || ((x) == LOCK))


#define BIT(x)			((1U << (x)))
#define BITS(s, e)		((0xffffffff << (s)) & (0xffffffff >> (31 - (e))))
#define SET_BIT(reg, bit)	((reg) |= (bit))
#define CLEAR_BIT(reg, bit)	((reg) &= ~(bit))
#define READ_BIT(reg, bit)	((reg) & (bit))
#define READ_BITS(reg, msk, s)	(((reg) & (msk)) >> (s))
#define CLEAR_REG(reg)		((reg) = (0x0))
#define WRITE_REG(reg, val)	((reg) = (val))
#define READ_REG(reg)		((reg))
#define MODIFY_REG(reg, clearmask, setmask)	\
    WRITE_REG((reg), (((READ_REG(reg)) & (~(clearmask))) | (setmask)))
#define UNUSED(x)	((void)(x))

#ifdef USE_ASSERT
#define assert_param(x)			\
    do {					\
        if (!(x)) {			\
            __disable_irq();	\
            while (1)		\
                ;		\
        }				\
    } while (0)
#else
#define assert_param(x)
#endif


#define PER_MEM_BASE         ((uint32_t) 0x40000000UL)	/* PER base address  */
#define RAM_MEM_BASE         ((uint32_t) 0x20000000UL)	/* RAM base address  */
#define BITBAND_PER_BASE     ((uint32_t) 0x42000000UL)	/* Peripheral Address Space bit-band area */
#define BITBAND_RAM_BASE     ((uint32_t) 0x22000000UL)	/* SRAM Address Space bit-band area */

__STATIC_INLINE__ void BITBAND_PER(volatile uint32_t *addr, uint32_t bit, uint32_t val)
{
    uint32_t tmp = BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) << 5) + (bit << 2);
    *((volatile uint32_t *)tmp) = (uint32_t)val;
}

__STATIC_INLINE__ void BITBAND_SRAM(uint32_t *addr, uint32_t bit, uint32_t val)
{
    uint32_t tmp = BITBAND_RAM_BASE + (((uint32_t)addr - RAM_MEM_BASE) << 5) + (bit << 2);
    *((volatile uint32_t *)tmp) = (uint32_t)val;
}

#if defined ( __GNUC__ )
#ifndef __weak
#define __weak   __attribute__((weak))
#endif	/* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif	/* __packed */
#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TYPE_H__ */
