/*
 * File      : display_controller.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-08     lgnq         first version for LS1B
 */
 
#ifndef __DISPLAY_CONTROLLER_H__
#define __DISPLAY_CONTROLLER_H__

#include <rtthread.h>
#include "ls1b.h"

#define DC_BASE					0xBC301240  //Display Controller

/* Frame Buffer registers */
#define DC_FB_CONFIG			__REG32(DC_BASE + 0x000)
#define DC_FB_BUFFER_ADDR0		__REG32(DC_BASE + 0x020)
#define DC_FB_BUFFER_STRIDE		__REG32(DC_BASE + 0x040)
#define DC_FB_BUFFER_ORIGIN		__REG32(DC_BASE + 0x060)
#define DC_DITHER_CONFIG		__REG32(DC_BASE + 0x120)
#define DC_DITHER_TABLE_LOW		__REG32(DC_BASE + 0x140)
#define DC_DITHER_TABLE_HIGH	__REG32(DC_BASE + 0x160)
#define DC_PANEL_CONFIG			__REG32(DC_BASE + 0x180)
#define DC_PANEL_TIMING			__REG32(DC_BASE + 0x1A0)
#define DC_HDISPLAY				__REG32(DC_BASE + 0x1C0)
#define DC_HSYNC				__REG32(DC_BASE + 0x1E0)
#define DC_VDISPLAY				__REG32(DC_BASE + 0x240)
#define DC_VSYNC				__REG32(DC_BASE + 0x260)
#define DC_FB_BUFFER_ADDR1		__REG32(DC_BASE + 0x340)

/* Display Controller driver for 1024x768 16bit */
#define FB_XSIZE		1024
#define FB_YSIZE		768
#define CONFIG_VIDEO_16BPP

#define APB_CLK 33333333

#define K1BASE				0xA0000000
#define KSEG1(addr)			((void *)(K1BASE | (rt_uint32_t)(addr)))
#define HW_FB_ADDR			KSEG1(_rt_framebuffer)
#define HW_FB_PIXEL(x, y)	*(volatile rt_uint16_t*)((rt_uint8_t*)HW_FB_ADDR + (y * FB_XSIZE * 2) + x * 2)

struct vga_struct
{
	long pclk;
	int hr,hss,hse,hfl;
	int vr,vss,vse,vfl;
};

#endif
