/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *�ļ�����  lib_printf.c
 *��  �ߣ�  Liut
 *��  ����  V1.00
 *��  �ڣ�  2017/07/14
 *��  ����  ���ڴ�ӡ�⺯��
 *��  ע��  ������ ES8P508xоƬ
 ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
 ***************************************************************/
#include "lib_printf.h"
#include <stdarg.h>

/***************************************************************
  ��������fputc
  ��  �����ض���c�⺯��printf��UART
  ����ֵ��������
  ���ֵ��������
  ����ֵ��������
 ***************************************************************/
/*ʹ��printf()������Ҫ����΢�⣺Use MicroLIB*/
int fputc(int ch, FILE *f)
{
    FlagStatus Status = RESET;
    uint32_t Count=0;

#if defined  __PRINTF_USE_UART3__
    UART_SendByte(UART3, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART3,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#elif defined __PRINTF_USE_UART2__
    UART_SendByte(UART2, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART2,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#elif defined __PRINTF_USE_UART1__
    UART_SendByte(UART1, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART1,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#else
    UART_SendByte(UART0, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART0,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#endif
    return (ch);
}

#ifdef __clang__     //��ʹ�õ���idesigner������ʱ���򲻵���΢��
/***************************************************************
  ��  ��������������ת�����ַ���
  ����ֵ��   -radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 ����ֵ����
 ***************************************************************/
static char *itoa(int value, char *string, int radix)
{
    int i, d;
    int flag = 0;
    char *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;
}
/***************************************************************
  ��  ������ʽ�������������C���е�printf��������û���õ�C��
  ����ֵ��   -UARTx ����ͨ����
 *         -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *         -...    ��������
 ����ֵ����
 ����Ӧ�ã� UART_printf("\r\n this is a demo \r\n" );
 *         UART1_printf("\r\n %d \r\n", i );
 *         UART1_printf("\r\n %s \r\n", j );
 ***************************************************************/
/* δ����C���ʱ�����ʹ�ô˺�������C���е�printf����������printfȫ��
   ֻ֧��\r  \n  %d   %s */
ErrorStatus UART_printf(uint8_t *Data,...)
{
		UART_TypeDef *UARTx;
    const char *s;
    int d;   
    char buf[16];
    ErrorStatus RET = SUCCESS;
    FlagStatus Status = RESET;
    uint32_t Count=0;
    va_list ap;
	
/**
	**
	**ʹ�ú궨��ѡ��ʹ����һ������
	**
***/
#if defined  __PRINTF_USE_UART3__
	
	UARTx = UART3;
	
#elif defined __PRINTF_USE_UART2__
	
	UARTx = UART2;
	
#elif defined __PRINTF_USE_UART1__

	UARTx = UART1;
	
#else

	UARTx = UART0;
	
#endif		
		
    va_start(ap, Data);

    while ( *Data != 0)                           // �ж��Ƿ񵽴��ַ���������
    {
        if ( *Data == 0x5c )                      //'\'
        {
            switch ( *++Data )
            {
                case 'r':                         //�س���
                    Count=0;
                    UART_SendByte(UARTx, 0x0d);
                    do
                    {
                        Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                        Count++;
                    }while((Status == RESET)&&(Count != 0x1CE2));

                    if(Count == 0x1CE2)
                        RET = ERROR;

                    Data ++;
                    break;

                case 'n':                         //���з�
                    Count=0;
                    UART_SendByte(UARTx, 0x0a);    
                    do
                    {
                        Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                        Count++;
                    }while((Status == RESET)&&(Count != 0x1CE2));

                    if(Count == 0x1CE2)
                        RET = ERROR;

                    Data ++;
                    break;

                default:
                    Data ++;
                    break;
            }             
        }
        else if ( *Data == '%')
        {
            switch ( *++Data )
            {                
                case 's':                         //�ַ���
                    s = va_arg(ap, const char *);
                    for ( ; *s; s++) 
                    {
                        Count=0;
                        UART_SendByte(UARTx,*s);
                        do
                        {
                            Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                            Count++;
                        }while((Status == RESET)&&(Count != 0x1CE2));

                        if(Count == 0x1CE2)
                            RET = ERROR;
                    }
                    Data++;
                    break;

                case 'd':                         //ʮ����
                    d = va_arg(ap, int);
                    itoa(d, buf, 10);
                    for (s = buf; *s; s++)  
                    {
                        Count=0;
                        UART_SendByte(UARTx,*s);
                        do
                        {
                            Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                            Count++;
                        }while((Status == RESET)&&(Count != 0x1CE2));

                        if(Count == 0x1CE2)
                            RET = ERROR;
                    }
                    Data++;
                    break;
                default:
                    Data++;
                    break;
            }
        } /* end of else if */
        else 
        {
            Count=0;
            UART_SendByte(UARTx, *Data++);
            do
            {
                Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                Count++;
            }while((Status == RESET)&&(Count != 0x1CE2));

            if(Count == 0x1CE2)
                RET = ERROR;
        }
    }
    return RET;
}

#endif
/*************************END OF FILE**********************/

