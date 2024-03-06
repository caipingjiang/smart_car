/*
 * File      : lcdc.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef LCD_GENERAL_H_INCLUDED
#define LCD_GENERAL_H_INCLUDED

#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>


#define LCDWIDTH 320
#define LCDHEIGHT 240

//Macro for SIZE register setting
#define XMAX   ((LCDWIDTH/16) << 20)
#define YMAX   (LCDHEIGHT)

//Macro for PCR register setting
#define TFT   ((U32)1 << 31)
#define COLOR   (1 << 30)   //1Ϊɫ��.
#define PBSIZE   (0 << 28)
#define BPIX     (4 << 25)   //�洢����һ�����ض�Ӧ16bit
#define PIXPOL   (0 << 24)   //���ؼ��ԡ��������صļ���,����Ч	   //0<<24
#define FLMPOL   (1 << 23)   //���б�־���ԡ��������б�־�ļ���,����Ч.
#define LPPOL   (1 << 22)   //�����弫�ԡ������������źŵļ���,����Ч.
#define CLKPOL   (0 << 21)   //LCD ��λʱ�Ӽ��ԡ�����LCD ��λʱ�ӵ���Ч�صļ���,�½�����Ч.
#define OEPOL   (1 << 20)   //���ʹ�ܼ��ԡ��������ʹ���źŵļ���,����Ч.
#define END_SEL (0 << 18)   //ӡ�ڰ���ʽѡ��,Сӡ�ڰ�.
#define ACD_SEL (0 << 15)   //ACDʱ��Դѡ��ѡ����任��������ʱ��,ʹ��FLM ��ΪACD ����ʱ��
#define ACD   (0 << 8 )   //����ģʽ.
#define PCD   (10)

//Macro for HCR regiter setting //ˮƽ���üĴ���.
#define H_WIDTH ((U32)46 << 26)
#define H_WAIT_1 (20 << 8)
#define H_WAIT_2 (20)

//Macro for VCR register setting //��ֱ���üĴ���.
#define V_WIDTH ((U32)10 << 26)
#define PASS_FRAME_WAIT (0 <<16)
#define V_WAIT_1 (3 << 8)
#define V_WAIT_2 (3)

//Macro for LGPR register setting
#define GRAY   (4)    //�Ҷȵȼ�.

//Macro for PWMR register setting
#define SCR   (0 << 9)   //ʱ��Դѡ��.������.
#define CC_EN (0 << 8)   //�Աȶȿ���ʹ��,��.
#define PW   (64)    //���������Ŀ,

//Macro for DMACR register setting
#define BL   ((U32)1 << 31)   //�̶�����.
#define HM   (7 << 16)
#define TM   (3)

void lcd_set_pixel(rtgui_color_t *c, int x, int y);
void lcd_get_pixel(rtgui_color_t *c, int x, int y);
void lcd_draw_hline(rtgui_color_t *c, int x1, int x2, int y) ;
void lcd_draw_vline(rtgui_color_t *c, int x, int y1, int y2) ;
void lcd_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)  ;
void lcd_update(rtgui_rect_t *rect);
rt_uint8_t * lcd_get_framebuffer(void);
rt_err_t sep4020_lcd_init(void);


#endif


