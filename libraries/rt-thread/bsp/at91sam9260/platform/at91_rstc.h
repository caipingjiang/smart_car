/*
 * File      : at91_rstc.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
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
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef AT91_RSTC_H
#define AT91_RSTC_H

#ifdef __cplusplus
extern "C" {
#endif

#define AT91_RSTC_CR		(AT91_RSTC + 0x00)	/* Reset Controller Control Register */
#define		AT91_RSTC_PROCRST	(1 << 0)		/* Processor Reset */
#define		AT91_RSTC_PERRST	(1 << 2)		/* Peripheral Reset */
#define		AT91_RSTC_EXTRST	(1 << 3)		/* External Reset */
#define		AT91_RSTC_KEY		(0xa5 << 24)		/* KEY Password */

#define AT91_RSTC_SR		(AT91_RSTC + 0x04)	/* Reset Controller Status Register */
#define		AT91_RSTC_URSTS		(1 << 0)		/* User Reset Status */
#define		AT91_RSTC_RSTTYP	(7 << 8)		/* Reset Type */
#define			AT91_RSTC_RSTTYP_GENERAL	(0 << 8)
#define			AT91_RSTC_RSTTYP_WAKEUP		(1 << 8)
#define			AT91_RSTC_RSTTYP_WATCHDOG	(2 << 8)
#define			AT91_RSTC_RSTTYP_SOFTWARE	(3 << 8)
#define			AT91_RSTC_RSTTYP_USER	(4 << 8)
#define		AT91_RSTC_NRSTL		(1 << 16)		/* NRST Pin Level */
#define		AT91_RSTC_SRCMP		(1 << 17)		/* Software Reset Command in Progress */

#define AT91_RSTC_MR		(AT91_RSTC + 0x08)	/* Reset Controller Mode Register */
#define		AT91_RSTC_URSTEN	(1 << 0)		/* User Reset Enable */
#define		AT91_RSTC_URSTIEN	(1 << 4)		/* User Reset Interrupt Enable */
#define		AT91_RSTC_ERSTL		(0xf << 8)		/* External Reset Length */

#ifdef __cplusplus
}
#endif

#endif

