/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_uart
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#ifndef _zf_driver_uart_h_
#define _zf_driver_uart_h_

#include "zf_common_typedef.h"
#include "fsl_lpuart.h"

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    // UART 1 TX ����
    UART1_TX_B12 = 16 * 1,

    // UART 2 TX ����
    UART2_TX_B18 = 16 * 2,

    // UART 3 TX ����
    UART3_TX_B22 = 16 * 3,  UART3_TX_C8,

    // UART 4 TX ����
    UART4_TX_C16 = 16 * 4,  UART4_TX_D0,

    // UART 5 TX ����
    UART5_TX_C28 = 16 * 5,

    // UART 6 TX ����
    UART6_TX_B2  = 16 * 6,

    // UART 7 TX ����
    // �����ſ���

    // UART 8 TX ����
    UART8_TX_B26 = 16 * 8,  UART8_TX_D16,
    
}uart_tx_pin_enum;

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    // UART 1 RX ����
    UART1_RX_B13 = 16 * 1, 
                
    // UART 2 RX ���� 
    UART2_RX_B19 = 16 * 2,
                
    // UART 3 RX ���� 
    UART3_RX_B23 = 16 * 3,  UART3_RX_C9,
                
    // UART 4 RX ���� 
    UART4_RX_C17 = 16 * 4,  UART4_RX_D1,
                
    // UART 5 RX ���� 
    UART5_RX_C29 = 16 * 5,
                
    // UART 6 RX ���� 
    UART6_RX_B3  = 16 * 6,
                
    // UART 7 RX ���� 
    // �����ſ���
                
    // UART 8 RX ���� 
    UART8_RX_B27 = 16 * 8,  UART8_RX_D17,
}uart_rx_pin_enum;

typedef enum                                                                    // ö�ٴ��ں� ��ö�ٶ��岻�����û��޸�
{
    UART_1 = 1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_8 = 8,
}uart_index_enum;


void    uart_write_byte                     (uart_index_enum uartn, const uint8 dat);
void    uart_write_buffer                   (uart_index_enum uartn, const uint8 *buff, uint32 len);
void    uart_write_string                   (uart_index_enum uartn, const char *str);

uint8   uart_read_byte                      (uart_index_enum uartn);
uint8   uart_query_byte                     (uart_index_enum uartn, uint8 *dat);

void    uart_tx_interrupt                   (uart_index_enum uartn, uint32 status);
void    uart_rx_interrupt                   (uart_index_enum uartn, uint32 status);

void    uart_init                           (uart_index_enum uartn, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // ���ݾɰ汾��Դ��ӿ�����
#define uart_putchar(uart_n, dat)           (uart_write_byte((uart_n), (dat)))
#define uart_putbuff(uart_n, buff, len)     (uart_write_buffer((uart_n), (buff), (len)))
#define uart_putstr(uart_n, str)            (uart_write_string((uart_n), (str)))

#define uart_getchar(uart_n, dat)           (*(dat) = uart_read_byte((uart_n)))
#define uart_query(uart_n, dat)             (uart_query_byte((uart_n), (dat)))

#define uart_tx_irq(uart_n, status)         (uart_tx_interrupt((uart_n), (status)))
#define uart_rx_irq(uart_n, status)         (uart_rx_interrupt((uart_n), (status)))
#endif

#endif
