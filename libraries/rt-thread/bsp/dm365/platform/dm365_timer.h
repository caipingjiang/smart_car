/*
 * File      : dm365_timer.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author		Notes
 * 2010-11-13     weety		first version
 */

#ifndef __ASM_ARCH_TIME_H
#define __ASM_ARCH_TIME_H

/* Timer register offsets */
#define PID12				0x0
#define TIM12				0x10
#define TIM34				0x14
#define PRD12				0x18
#define PRD34				0x1c
#define TCR				0x20
#define TGCR				0x24
#define WDTCR				0x28
#define CMP12(n)			(0x60 + ((n) << 2))

/* Timer register bitfields */
#define ENAMODE12_SHIFT 		6
#define ENAMODE34_SHIFT 		22
#define TCR_ENAMODE_DISABLE		0x0
#define TCR_ENAMODE_ONESHOT		0x1
#define TCR_ENAMODE_PERIODIC		0x2
#define TCR_ENAMODE_MASK		0x3

#define TGCR_TIMMODE_SHIFT		2
#define TGCR_TIMMODE_64BIT_GP		0x0
#define TGCR_TIMMODE_32BIT_UNCHAINED	0x1
#define TGCR_TIMMODE_64BIT_WDOG 	0x2
#define TGCR_TIMMODE_32BIT_CHAINED	0x3

#define TGCR_TIM12RS_SHIFT		0
#define TGCR_TIM34RS_SHIFT		1
#define TGCR_RESET			0x0
#define TGCR_UNRESET			0x1
#define TGCR_RESET_MASK 		0x3

#define WDTCR_WDEN_SHIFT		14
#define WDTCR_WDEN_DISABLE		0x0
#define WDTCR_WDEN_ENABLE		0x1
#define WDTCR_WDKEY_SHIFT		16
#define WDTCR_WDKEY_SEQ0		0xA5C6
#define WDTCR_WDKEY_SEQ1		0xDA7E

enum {
	T0_BOT,
	T0_TOP,
	T1_BOT,
	T1_TOP,
	NUM_TIMERS
};

#endif /* __ASM_ARCH_TIME_H__ */

