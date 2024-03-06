/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *�ļ�����  lib_printf.h
 *��  �ߣ�  Liut
 *��  ����  V1.00
 *��  �ڣ�  2017/07/14
 *��  ����  ���ڴ�ӡ�⺯��ͷ�ļ�
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#ifndef __LIBPRINTF_H__
#define __LIBPRINTF_H__

#include "lib_uart.h"
#include <stdio.h>
#include "type.h"

int fputc(int ch, FILE *f);
static char *itoa(int value, char *string, int radix);
ErrorStatus UART_printf(uint8_t *Data,...);

#ifdef __clang__ 
ErrorStatus UART_printf(uint8_t *Data, ...);

#elif defined __CC_ARM

#define UART_printf  printf

#endif

#endif

/*************************END OF FILE**********************/
