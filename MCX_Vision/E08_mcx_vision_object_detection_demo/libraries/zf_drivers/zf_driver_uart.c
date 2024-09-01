/*********************************************************************************************************************
* MCX Vision Opensourec Library 即（MCX Vision 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2024 SEEKFREE 逐飞科技
* 
* 本文件是 MCX Vision 开源库的一部分
* 
* MCX Vision 开源库 是免费软件
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
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_uart
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.38a
* 适用平台          MCX Vision
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_driver_uart.h"

// 用户串口回调函数
void LP_FLEXCOMM5_IRQHandler(void)
{
    uint8_t data;

    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(USER_USART))
    {
        // 接收到的数据
        data = LPUART_ReadByte(USER_USART);
    }
    LPUART_ClearStatusFlags(USER_USART, kLPUART_RxOverrunFlag);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     用户串口字节输出
// 参数说明     c             需要发送的字节
// 返回参数     void        
// 使用示例     uart_write_byte(0xA5);                                  // 串口1发送0xA5
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_putchar(char c)
{
    while(!(USER_USART->STAT & LPUART_STAT_TDRE_MASK));                 // 等待发送完成
    LPUART_WriteBlocking(USER_USART, (const uint8_t *)&c, 1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送数组
// 参数说明     *buff           要发送的数组地址
// 参数说明     len             发送长度
// 返回参数     void
// 使用示例     user_uart_write_buffer(&a[0], 5);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_write_buffer (const uint8 *buff, uint32 len)
{
    while(!(USER_USART->STAT & LPUART_STAT_TDRE_MASK));                 // 等待发送完成
    LPUART_WriteBlocking(USER_USART, buff, len);                        // 写入发送数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     串口发送字符串
// 参数说明     *str            要发送的字符串地址
// 返回参数     void
// 使用示例     user_uart_write_string("seekfree"); 
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_write_string (const char *str)
{
    while(*str)                                                                 // 一直循环到结尾
    {
        user_uart_putchar(*str ++);                                             // 发送数据
    }
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     自定义user_printf函数
// 参数说明     和printf用法相同
// 返回参数     void        
// 使用示例     zf_user_printf("seekfree%d\r\n", 0xA5);                                  // 串口1发送0xA5
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void zf_user_printf(const char *format, ...) 
{
    va_list args;
    va_start(args, format);

    char buffer[64]; // 假设最大转换后的字符串长度为64
    int written = 0;
    while (*format && written < 63) 
    {
        if (*format == '%') 
        {
            format++; // 跳过%
            if (*format == 'd') 
            {
                int value = va_arg(args, int);
                int_to_str(value, buffer);
                for (int i = 0; buffer[i] != '\0' && written < 63; i++) 
                {
                    user_uart_putchar(buffer[i]);
                    written++;
                }
            } 
            else if (*format == 's') 
            {
                const char *str_value = va_arg(args, const char *);
                while (*str_value && written < 63) 
                {
                    user_uart_putchar(*str_value);
                    str_value++;
                    written++;
                }
            } 
            else if (*format == 'c') 
            {
                char char_value = va_arg(args, int); // char类型在va_arg中会被提升为int
                user_uart_putchar(char_value);
                written++;
            } 
            else if (*format == 'f') 
            {
                float float_value = va_arg(args, double); // 浮点数在va_arg中会被提升为double
                float_to_str(float_value, buffer);
                for (int i = 0; buffer[i] != '\0' && written < 63; i++) 
                {
                    user_uart_putchar(buffer[i]);
                    written++;
                }
            }
            else
            {
                format++; // 移动到下一个字符
            }
        } 
        else 
        {
            user_uart_putchar(*format);
            written++;
        }
        format++;
    }

    va_end(args);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     用户串口初始化
// 返回参数     void            
// 使用示例     uart_init();          
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_init(void)
{
    lpuart_config_t config;
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom5Clk, 1u);
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM5);
    
    CLOCK_EnableClock(kCLOCK_Port1);

    const port_pin_config_t port1_16_pinA1_config = {/* Internal pull-up/down resistor is disabled */
                                                    kPORT_PullDisable,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as FC4_P0 */
                                                    kPORT_MuxAlt2,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    PORT_SetPinConfig(PORT1, 16U, &port1_16_pinA1_config);

    const port_pin_config_t port1_17_pinB1_config = {/* Internal pull-up/down resistor is disabled */
                                                    kPORT_PullDisable,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as FC4_P1 */
                                                    kPORT_MuxAlt2,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    PORT_SetPinConfig(PORT1, 17U, &port1_17_pinB1_config);
                       
    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = USER_USART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;
    LPUART_Init(USER_USART, &config, CLOCK_GetLPFlexCommClkFreq(USER_USART_NUM));
    LPUART_Deinit(USER_USART);                                                
    LPUART_Init(USER_USART, &config, CLOCK_GetLPFlexCommClkFreq(USER_USART_NUM));
    LPUART_EnableInterrupts(USER_USART, kLPUART_RxDataRegFullInterruptEnable);  
    NVIC_SetPriority(LP_FLEXCOMM5_IRQn, 5);
    EnableIRQ(LP_FLEXCOMM5_IRQn);
}

