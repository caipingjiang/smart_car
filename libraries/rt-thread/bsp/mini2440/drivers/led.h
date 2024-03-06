/*
 * File      : led.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-12-27     rdghx        mini2440
 */

#ifndef __LED_H__
#define __LED_H__

#define LED1    0x01
#define LED2    0x02
#define LED3    0x04
#define LED4    0x08
#define LED_ALL 0x0f

void rt_hw_led_init(void);
void rt_hw_led_on(unsigned char value);
void rt_hw_led_off(unsigned char value);

#endif
