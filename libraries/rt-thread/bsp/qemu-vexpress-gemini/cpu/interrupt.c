/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013-2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 * 2014-04-03     Grissiom     port to VMM
 */

#include <rthw.h>
#include <rtthread.h>
#include "realview.h"
#include "gic.h"
#include "cp15.h"

#ifdef RT_USING_VMM
#include <vmm.h>
#endif

#define MAX_HANDLERS                NR_IRQS_PBA8

extern volatile rt_uint8_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

extern void rt_cpu_vector_set_base(unsigned int addr);
extern int system_vectors;

static void rt_hw_vector_init(void)
{
    int sctrl;
    unsigned int *src = (unsigned int *)&system_vectors;

    /* C12-C0 is only active when SCTLR.V = 0 */
    asm volatile ("mrc p15, #0, %0, c1, c0, #0"
                  :"=r" (sctrl));
    sctrl &= ~(1 << 13);
    asm volatile ("mcr p15, #0, %0, c1, c0, #0"
                  :
                  :"r" (sctrl));

    asm volatile ("mcr p15, #0, %0, c12, c0, #0"
                  :
                  :"r" (src));
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    rt_uint32_t gic_cpu_base;
    rt_uint32_t gic_dist_base;

    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* initialize ARM GIC */
    gic_dist_base = REALVIEW_GIC_DIST_BASE;
    gic_cpu_base = REALVIEW_GIC_CPU_BASE;
    arm_gic_dist_init(0, gic_dist_base, 0);
    arm_gic_cpu_init(0, gic_cpu_base);
    /*arm_gic_dump_type(0);*/

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    arm_gic_mask(0, vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    arm_gic_umask(0, vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < MAX_HANDLERS)
    {
        old_handler = isr_table[vector].handler;

        if (handler != RT_NULL)
        {
#ifdef RT_USING_INTERRUPT_INFO
            rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
        arm_gic_set_cpu(0, vector, 1 << rt_cpu_get_smp_id());
    }

    return old_handler;
}

/**
 * Trigger a software IRQ
 *
 * Since we are running in single core, the target CPU are always CPU0.
 */
void rt_hw_interrupt_trigger(int vector)
{
    arm_gic_trigger(0, 1, vector);
}

void rt_hw_interrupt_clear(int vector)
{
    arm_gic_clear_sgi(0, 1, vector);
}
