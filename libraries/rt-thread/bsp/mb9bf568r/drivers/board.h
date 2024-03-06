/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2011-03-04     lgnq         add board.h to FM3 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__


#include <system_mb9bf56xr.h>
#include <mb9b560r.h>
#include <base_types.h>

#include "serial.h"


#define FM4_SRAM_SIZE         128
#define FM4_SRAM_END          (0x1FFF0000 + FM4_SRAM_SIZE * 1024)

/* RT_USING_UART */
#define RT_USING_UART0

#define RT_UART_RX_BUFFER_SIZE        128

void rt_hw_board_init(void);
rt_uint32_t rt_hw_tick_get_millisecond(void);
rt_uint32_t rt_hw_tick_get_microsecond(void);

#endif
