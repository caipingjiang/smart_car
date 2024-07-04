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
* 文件名称          zf_board_init
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
#include "zf_board_init.h"


// DEBUG串口回调函数
void LP_FLEXCOMM4_IRQHandler(void)
{
    uint8_t data;
    
    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(DEBUG_USART))
    {
        // 接收到的数据
        data = LPUART_ReadByte(DEBUG_USART);
    }
    LPUART_ClearStatusFlags(DEBUG_USART, kLPUART_RxOverrunFlag);
}


void debug_uart_putchar(char c)
{
    while(!(DEBUG_USART->STAT & LPUART_STAT_TDRE_MASK));                 // 等待发送完成
    LPUART_WriteBlocking(DEBUG_USART, (const uint8_t *)&c, 1);
}

//int32_t fputc (int32_t ch, FILE* f)
//{
//    debug_uart_putchar((ch & 0xFF));
//    return ch;
//}

void int_to_str(int num, char *str) 
{
    volatile 
    int i = 0;
    volatile int temp = num;
    if (num < 0) 
    {
        temp = -num;
    }
    do 
    {
        str[i++] = temp % 10 + '0';
        temp /= 10;
    } while (temp != 0);
    if (num < 0) 
    {
        str[i++] = '-';
    }
    str[i] = '\0';
    // 反转字符串
    int len = i;
    for (int j = 0; j < len / 2; j++) 
    {
        char tmp = str[j];
        str[j] = str[len - j - 1];
        str[len - j - 1] = tmp;
    }
}

void float_to_str(float num, char *str) 
{
    int int_part = (int)num;
    float float_part = func_abs(num - int_part);

    int_to_str(int_part, str);

    // 添加小数点
    int len = strlen(str);
    str[len] = '.';
    str[len + 1] = '\0';

    // 处理小数部分
    int decimal_part = float_part * 100000; // 保留五位小数
    int_to_str(decimal_part, str + len + 1);
}

// 自定义debug_printf函数
void zf_debug_printf(const char *format, ...) 
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
                    debug_uart_putchar(buffer[i]);
                    written++;
                }
            } 
            else if (*format == 's') 
            {
                const char *str_value = va_arg(args, const char *);
                while (*str_value && written < 63) 
                {
                    debug_uart_putchar(*str_value);
                    str_value++;
                    written++;
                }
            } 
            else if (*format == 'c') 
            {
                char char_value = va_arg(args, int); // char类型在va_arg中会被提升为int
                debug_uart_putchar(char_value);
                written++;
            } 
            else if (*format == 'f') 
            {
                float float_value = va_arg(args, double); // 浮点数在va_arg中会被提升为double
                float_to_str(float_value, buffer);
                for (int i = 0; buffer[i] != '\0' && written < 63; i++) 
                {
                    debug_uart_putchar(buffer[i]);
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
            debug_uart_putchar(*format);
            written++;
        }
        format++;
    }

    va_end(args);
}
void debug_uart_init(void)
{
    lpuart_config_t config;
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1u);
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
    
    CLOCK_EnableClock(kCLOCK_Port1);
    const port_pin_config_t port1_8_pinA1_config = {/* Internal pull-up/down resistor is disabled */
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
    /* PORT1_8 (pin A1) is configured as FC4_P0 */
    PORT_SetPinConfig(PORT1, 8U, &port1_8_pinA1_config);

    const port_pin_config_t port1_9_pinB1_config = {/* Internal pull-up/down resistor is disabled */
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
    /* PORT1_9 (pin B1) is configured as FC4_P1 */
    PORT_SetPinConfig(PORT1, 9U, &port1_9_pinB1_config);
                       
    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = DEBUG_USART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;
    LPUART_Init(DEBUG_USART, &config, CLOCK_GetLPFlexCommClkFreq(DEBUG_USART_NUM));
    LPUART_Deinit(DEBUG_USART);                                                
    LPUART_Init(DEBUG_USART, &config, CLOCK_GetLPFlexCommClkFreq(DEBUG_USART_NUM));
    LPUART_EnableInterrupts(DEBUG_USART, kLPUART_RxDataRegFullInterruptEnable);
                                                    
    NVIC_SetPriority(LP_FLEXCOMM4_IRQn, 6);
    EnableIRQ(LP_FLEXCOMM4_IRQn);
}

gpio_struct led_core = {GPIO4, 7u};
void zf_board_init(void)
{
    BOARD_InitBootClocks();
    BOARD_PowerMode_OD();
    gpio_init(led_core, GPO, GPIO_LOW, PULL_UP);
    
    NVIC_SetPriorityGrouping(3);
    debug_uart_init();
    system_delay_init();
    /* Enable caching of flash memory */
    SYSCON->LPCAC_CTRL = SYSCON->LPCAC_CTRL & ~SYSCON_LPCAC_CTRL_DIS_LPCAC_MASK;
    SYSCON->NVM_CTRL = SYSCON->NVM_CTRL & ~SYSCON_NVM_CTRL_DIS_FLASH_DATA_MASK;
}

void HardFault_Handler(void)
{
	//硬件上访  可能是数组越界或者使用了未初始化的设备
	//这里提示大家一个问题，经常有人说我的外设初始化了怎么就是要进HardFault呢
	//很多是因为自己开了中断，然后在中断里面使用了外设，然后他的初始化顺序是先初始化中断然后再初始化外设
	//那么问题就来了，中断初始化完成之后会部分中断直接进入中断函数或者满足调节也会进入中断函数，那么就会造成中断里面使用到的外设还没被初始化
	//所以大家需要注意这个问题
	while(1)
    {
        gpio_toggle_level(led_core);
        system_delay_ms(100);
    }
}