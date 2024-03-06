/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_uart
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
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


#define LPUART_PIN_CONF SPEED_100MHZ | KEEPER_EN | DSE_R0_6 // 配置UART引脚默认配置

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
// 函数简介     串口字节输出
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     dat             需要发送的字节
// 返回参数     void        
// 使用示例     uart_write_byte(UART_1, 0xA5);                                  // 串口1发送0xA5
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_byte (uart_index_enum uart_n, const uint8 dat)
{
    while(!(uart_index[uart_n]->STAT & LPUART_STAT_TDRE_MASK));                 // 等待发送完成
    LPUART_WriteByte(uart_index[uart_n], dat);                                  // 写入发送数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送数组
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *buff           要发送的数组地址
// 参数说明     len             发送长度
// 返回参数     void
// 使用示例     uart_write_buffer(UART_1, &a[0], 5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer (uart_index_enum uart_n, const uint8 *buff, uint32 len)
{
    while(!(uart_index[uart_n]->STAT & LPUART_STAT_TDRE_MASK));                 // 等待发送完成
    LPUART_WriteBlocking(uart_index[uart_n], buff, len);                        // 写入发送数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送字符串
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *str            要发送的字符串地址
// 返回参数     void
// 使用示例     uart_write_string(UART_1, "seekfree"); 
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_write_string (uart_index_enum uart_n, const char *str)
{
    while(*str)                                                                 // 一直循环到结尾
    {
        uart_write_byte(uart_n, *str ++);                                       // 发送数据
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（whlie等待）
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           接收的数据
// 使用示例     uint8 dat = uart_read_byte(UART_1);                             // 接收 UART_1 数据  存在在 dat 变量里
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_read_byte (uart_index_enum uart_n)
{
    while (!((uart_index[uart_n]->WATER & LPUART_WATER_RXCOUNT_MASK) >> LPUART_WATER_RXCOUNT_SHIFT));
    return LPUART_ReadByte(uart_index[uart_n]);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取串口接收的数据（查询接收）
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     *dat            接收数据的地址
// 返回参数     uint8           1：接收成功   0：未接收到数据
// 使用示例     uint8 dat; uart_query_byte(UART_1, &dat);                       // 接收 UART_1 数据  存在在 dat 变量里
// 备注信息     
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
// 函数简介     串口发送中断设置
// 参数说明     uart_n           串口模块号
// 参数说明     status          1：打开中断   0：关闭中断
// 返回参数     void        
// 使用示例     uart_tx_interrupt(UART_1, 1);                                   // 打开串口1发送完成中断
// 备注信息     
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
    
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)(uartn) + LPUART1_IRQn),0);//优先级设置 范围0-15 越小优先级越高
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口接收中断设置
// 参数说明     uart_n           串口模块号
// 参数说明     status          1：打开中断   0：关闭中断
// 返回参数     void        
// 使用示例     uart_rx_interrupt(UART_1, 1);                                   // 打开串口1接收完成中断
// 备注信息     
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
    NVIC_SetPriority((IRQn_Type)((IRQn_Type)(uart_n) + LPUART1_IRQn),0);       // 优先级设置 范围0-15 越小优先级越高
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口初始化
// 参数说明     uart_n          串口模块号 参照 zf_driver_uart.h 内 uart_index_enum 枚举体定义
// 参数说明     baud            串口波特率
// 参数说明     tx_pin          串口发送引脚 参照 zf_driver_uart.h 内 uart_tx_pin_enum 枚举体定义
// 参数说明     rx_pin          串口接收引脚 参照 zf_driver_uart.h 内 uart_rx_pin_enum 枚举体定义
// 返回参数     void            
// 使用示例     uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);          // 初始化串口1 波特率115200 发送引脚使用PA09 接收引脚使用PA10
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void uart_init(uart_index_enum uart_n, uint32 baud, uart_tx_pin_enum tx_pin, uart_rx_pin_enum rx_pin)
{
    uint32_t uartClkSrcFreq;
    lpuart_config_t lpuartConfig;
    
    zf_assert((tx_pin / 16) == (rx_pin / 16));                                  // tx_pin 与 rx_pin 必须与 uart_n 匹配
            
    uart_iomuxc(uart_n,tx_pin,rx_pin);
    uartClkSrcFreq = BOARD_DebugConsoleSrcFreq();
    LPUART_GetDefaultConfig(&lpuartConfig);
    lpuartConfig.baudRate_Bps = baud;
    lpuartConfig.enableTx = true;
    lpuartConfig.enableRx = true;
    
    LPUART_Init(uart_index[uart_n], &lpuartConfig, uartClkSrcFreq);             // 第一次初始化便于打开时钟
    LPUART_Deinit(uart_index[uart_n]);                                          // 复位外设
    LPUART_Init(uart_index[uart_n], &lpuartConfig, uartClkSrcFreq);             // 重新初始化设置正确的参数
}
