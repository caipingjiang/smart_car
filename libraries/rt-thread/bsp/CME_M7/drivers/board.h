/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-03     aozima       first implementation
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "cmem7_includes.h"
//#include "cmem7_retarget.h"

#define SRAM_SIZE         64	// KB
#define SRAM_END          (0x20000000 + SRAM_SIZE * 1024)

//#define RT_USING_UART0
//#define RT_USING_UART1
#define RT_USING_UART2

void rt_hw_board_init(void);

#endif

