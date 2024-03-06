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

#include "fsl_iomuxc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_gpio.h"
#include "board.h"

#include "zf_driver_uart.h"

static  LPUART_Type *uart_index[]            = LPUART_BASE_PTRS;


#define LPUART_PIN_CONF SPEED_100MHZ | KEEPER_EN | DSE_R0_6 // ����UART����Ĭ������

void uart_iomuxc(uart_index_enum uartn, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin)
{
    switch(uartn)
    {
        case UART_1:
        {
            if      (UART1_TX_B12 == tx_pin)    afio_init(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,  0, LPUART_PIN_CONF); 
            if      (UART1_RX_B13 == rx_pin)    afio_init(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,  0, LPUART_PIN_CONF); 
        }break;                                                 
        case UART_2:                                            
        {                                                       
            if      (UART2_TX_B18 == tx_pin)    afio_init(IOMUXC_GPIO_AD_B1_02_LPUART2_TX,  0, LPUART_PIN_CONF); 
                                                                
            if      (UART2_RX_B19 == rx_pin)    afio_init(IOMUXC_GPIO_AD_B1_03_LPUART2_RX,  0, LPUART_PIN_CONF); 
        }break;                                                
        case UART_3:                                          
        {                                                      
            if      (UART3_TX_B22 == tx_pin)    afio_init(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,  0, LPUART_PIN_CONF); 
            else if (UART3_TX_C8  == tx_pin)    afio_init(IOMUXC_GPIO_B0_08_LPUART3_TX,     0, LPUART_PIN_CONF); 
                                                                  
            if      (UART3_RX_B23 == rx_pin)    afio_init(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,  0, LPUART_PIN_CONF); 
            else if (UART3_RX_C9  == rx_pin)    afio_init(IOMUXC_GPIO_B0_09_LPUART3_RX,     0, LPUART_PIN_CONF); 
        }break;                                                
        case UART_4:                                          
        {                                                      
            if      (UART4_TX_C16 == tx_pin)    afio_init(IOMUXC_GPIO_B1_00_LPUART4_TX,     0, LPUART_PIN_CONF); 
            else if (UART4_TX_D0  == tx_pin)    afio_init(IOMUXC_GPIO_SD_B1_00_LPUART4_TX,  0, LPUART_PIN_CONF); 
                                                                  
            if      (UART4_RX_C17 == rx_pin)    afio_init(IOMUXC_GPIO_B1_01_LPUART4_RX,     0, LPUART_PIN_CONF); 
            else if (UART4_RX_D1  == rx_pin)    afio_init(IOMUXC_GPIO_SD_B1_01_LPUART4_RX,  0, LPUART_PIN_CONF); 
        }break;                                                
        case UART_5:                                          
        {                                                      
            if      (UART5_TX_C28 == tx_pin)    afio_init(IOMUXC_GPIO_B1_12_LPUART5_TX,     0, LPUART_PIN_CONF); 
                                                                  
            if      (UART5_RX_C29 == rx_pin)    afio_init(IOMUXC_GPIO_B1_13_LPUART5_RX,     0, LPUART_PIN_CONF); 
        }break;                                                
        case UART_6:                                          
        {                                                      
            if      (UART6_TX_B2  == tx_pin)    afio_init(IOMUXC_GPIO_AD_B0_02_LPUART6_TX,  0, LPUART_PIN_CONF); 
                                                                  
            if      (UART6_RX_B3  == rx_pin)    afio_init(IOMUXC_GPIO_AD_B0_03_LPUART6_RX,  0, LPUART_PIN_CONF); 
        }break;                                                
                                         
        case UART_8:                                          
        {                                                      
            if      (UART8_TX_B26 == tx_pin)    afio_init(IOMUXC_GPIO_AD_B1_10_LPUART8_TX,  0, LPUART_PIN_CONF); 
            else if (UART8_TX_D16 == tx_pin)    afio_init(IOMUXC_GPIO_SD_B0_04_LPUART8_TX,  0, LPUART_PIN_CONF); 
                                                                    
            if      (UART8_RX_B27 == rx_pin)    afio_init(IOMUXC_GPIO_AD_B1_11_LPUART8_RX,  0, LPUART_PIN_CONF); 
            else if (UART8_RX_D17 == rx_pin)    afio_init(IOMUXC_GPIO_SD_B0_05_LPUART8_RX,  0, LPUART_PIN_CONF); 
        }break;
        
        default: zf_assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �����ֽ����
// ����˵��     uart_n          ����ģ��� ���� zf_driver_uart.h �� uart_index_enum ö���嶨��
// ����˵��     dat             ��Ҫ���͵��ֽ�
// ���ز���     void        
// ʹ��ʾ��     uart_write_byte(UART_1, 0xA5);                                  // ����1����0xA5
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte (uart_index_enum uart_n, const uint8 dat)
{
    while(!(uart_index[uart_n]->STAT & LPUART_STAT_TDRE_MASK));                 // �ȴ��������
    LPUART_WriteByte(uart_index[uart_n], dat);                                  // д�뷢������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ�������
// ����˵��     uart_n          ����ģ��� ���� zf_driver_uart.h �� uart_index_enum ö���嶨��
// ����˵��     *buff           Ҫ���͵������ַ
// ����˵��     len             ���ͳ���
// ���ز���     void
// ʹ��ʾ��     uart_write_buffer(UART_1, &a[0], 5);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer (uart_index_enum uart_n, const uint8 *buff, uint32 len)
{
    while(!(uart_index[uart_n]->STAT & LPUART_STAT_TDRE_MASK));                 // �ȴ��������
    LPUART_WriteBlocking(uart_index[uart_n], buff, len);                        // д�뷢������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ����ַ���
// ����˵��     uart_n          ����ģ��� ���� zf_driver_uart.h �� uart_index_enum ö���嶨��
// ����˵��     *str            Ҫ���͵��ַ�����ַ
// ���ز���     void
// ʹ��ʾ��     uart_write_string(UART_1, "seekfree"); 
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string (uart_index_enum uart_n, const char *str)
{
    while(*str)                                                                 // һֱѭ������β
    {
        uart_write_byte(uart_n, *str ++);                                       // ��������
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ�whlie�ȴ���
// ����˵��     uart_n          ����ģ��� ���� zf_driver_uart.h �� uart_index_enum ö���嶨��
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     uint8           ���յ�����
// ʹ��ʾ��     uint8 dat = uart_read_byte(UART_1);                             // ���� UART_1 ����  ������ dat ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_read_byte (uart_index_enum uart_n)
{
    while (!((uart_index[uart_n]->WATER & LPUART_WATER_RXCOUNT_MASK) >> LPUART_WATER_RXCOUNT_SHIFT));
    return LPUART_ReadByte(uart_index[uart_n]);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ���ڽ��յ����ݣ���ѯ���գ�
// ����˵��     uart_n          ����ģ��� ���� zf_driver_uart.h �� uart_index_enum ö���嶨��
// ����˵��     *dat            �������ݵĵ�ַ
// ���ز���     uint8           1�����ճɹ�   0��δ���յ�����
// ʹ��ʾ��     uint8 dat; uart_query_byte(UART_1, &dat);                       // ���� UART_1 ����  ������ dat ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query_byte (uart_index_enum uart_n, uint8 *dat)
{
    uint8 return_state = 0;
    
    if((uart_index[uart_n]->WATER & LPUART_WATER_RXCOUNT_MASK) >> LPUART_WATER_RXCOUNT_SHIFT)
    {
        *dat = LPUART_ReadByte(uart_index[uart_n]);
        return_state = 1;
    }
    
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ����ж�����
// ����˵��     uart_n           ����ģ���
// ����˵��     status          1�����ж�   0���ر��ж�
// ���ز���     void        
// ʹ��ʾ��     uart_tx_interrupt(UART_1, 1);                                   // �򿪴���1��������ж�
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void uart_tx_interrupt (uart_index_enum uart_n, uint32 status)
{
    if(status)
    {
        LPUART_EnableInterrupts(uart_index[uart_n], kLPUART_TxDataRegEmptyInterruptEnable);
        interrupt_enable((IRQn_Type)(LPUART1_IRQn + (IRQn_Type)(uart_n - 1)));
    }
    else
    {
        LPUART_DisableInterrupts(uart_index[uart_n], kLPUART_TxDataRegEmptyInterruptEnable);
    }
    
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)(uartn) + LPUART1_IRQn),0);//���ȼ����� ��Χ0-15 ԽС���ȼ�Խ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڽ����ж�����
// ����˵��     uart_n           ����ģ���
// ����˵��     status          1�����ж�   0���ر��ж�
// ���ز���     void        
// ʹ��ʾ��     uart_rx_interrupt(UART_1, 1);                                   // �򿪴���1��������ж�
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt (uart_index_enum uart_n, uint32 status)
{
    if(status)  
    {
        LPUART_EnableInterrupts(uart_index[uart_n], kLPUART_RxDataRegFullInterruptEnable);
        interrupt_enable((IRQn_Type)(LPUART1_IRQn + (IRQn_Type)(uart_n - 1)));
    }
    else
    {
        LPUART_DisableInterrupts(uart_index[uart_n], kLPUART_RxDataRegFullInterruptEnable);
    }
    NVIC_SetPriority((IRQn_Type)((IRQn_Type)(uart_n) + LPUART1_IRQn),0);       // ���ȼ����� ��Χ0-15 ԽС���ȼ�Խ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڳ�ʼ��
// ����˵��     uart_n          ����ģ��� ���� zf_driver_uart.h �� uart_index_enum ö���嶨��
// ����˵��     baud            ���ڲ�����
// ����˵��     tx_pin          ���ڷ������� ���� zf_driver_uart.h �� uart_tx_pin_enum ö���嶨��
// ����˵��     rx_pin          ���ڽ������� ���� zf_driver_uart.h �� uart_rx_pin_enum ö���嶨��
// ���ز���     void            
// ʹ��ʾ��     uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);          // ��ʼ������1 ������115200 ��������ʹ��PA09 ��������ʹ��PA10
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin)
{
    uint32_t uartClkSrcFreq;
    lpuart_config_t lpuartConfig;
    
    zf_assert((tx_pin / 16) == (rx_pin / 16));                                  // tx_pin �� rx_pin ������ uart_n ƥ��
            
    uart_iomuxc(uart_n,tx_pin,rx_pin);
    uartClkSrcFreq = BOARD_DebugConsoleSrcFreq();
    LPUART_GetDefaultConfig(&lpuartConfig);
    lpuartConfig.baudRate_Bps = baud;
    lpuartConfig.enableTx = true;
    lpuartConfig.enableRx = true;
    
    LPUART_Init(uart_index[uart_n], &lpuartConfig, uartClkSrcFreq);             // ��һ�γ�ʼ�����ڴ�ʱ��
    LPUART_Deinit(uart_index[uart_n]);                                          // ��λ����
    LPUART_Init(uart_index[uart_n], &lpuartConfig, uartClkSrcFreq);             // ���³�ʼ��������ȷ�Ĳ���
}
