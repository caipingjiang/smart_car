/*
 * File      : spi-davinci.h
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
 * 2011-01-13     weety		first version
 */

#ifndef __DAVINCI_SPI_H
#define __DAVINCI_SPI_H

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef unsigned int   bool;

#define SPI_INTERN_CS	0xFF

enum {
	SPI_VERSION_1, /* For DM355/DM365/DM6467 */
	SPI_VERSION_2, /* For DA8xx */
};

/**
 * davinci_spi_config - Per-chip-select configuration for SPI slave devices
 *
 * @wdelay:	amount of delay between transmissions. Measured in number of
 *		SPI module clocks.
 * @odd_parity:	polarity of parity flag at the end of transmit data stream.
 *		0 - odd parity, 1 - even parity.
 * @parity_enable: enable transmission of parity at end of each transmit
 *		data stream.
 * @io_type:	type of IO transfer. Choose between polled, interrupt and DMA.
 * @timer_disable: disable chip-select timers (setup and hold)
 * @c2tdelay:	chip-select setup time. Measured in number of SPI module clocks.
 * @t2cdelay:	chip-select hold time. Measured in number of SPI module clocks.
 * @t2edelay:	transmit data finished to SPI ENAn pin inactive time. Measured
 *		in number of SPI clocks.
 * @c2edelay:	chip-select active to SPI ENAn signal active time. Measured in
 *		number of SPI clocks.
 */
struct davinci_spi_config {
	u8	wdelay;
	u8	odd_parity;
	u8	parity_enable;
#define SPI_IO_TYPE_INTR	0
#define SPI_IO_TYPE_POLL	1
#define SPI_IO_TYPE_DMA		2
	u8	io_type;
	u8	timer_disable;
	u8	c2tdelay;
	u8	t2cdelay;
	u8	t2edelay;
	u8	c2edelay;
};

extern int rt_hw_spi_init(void);

#endif	/* __DAVINCI_SPI_H */
