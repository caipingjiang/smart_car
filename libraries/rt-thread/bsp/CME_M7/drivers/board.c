/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2014, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-03     aozima       first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

/**
 * @addtogroup CME_M7
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

static void idle_hook(void)
{
    __WFI();
}

/**
 * This function will initial board.
 */
void rt_hw_board_init()
{
    //rt_thread_idle_sethook(idle_hook);

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    SysTick_Config(SYSTEM_CLOCK_FREQ / RT_TICK_PER_SECOND);

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

/*@}*/
