/*********************************************************************************************************************
* MCX Vision Opensourec Library ����MCX Vision ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2024 SEEKFREE ��ɿƼ�
* 
* ���ļ��� MCX Vision ��Դ���һ����
* 
* MCX Vision ��Դ�� ��������
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
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_uart
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.38a
* ����ƽ̨          MCX Vision
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_driver_uart.h"

// �û����ڻص�����
void LP_FLEXCOMM5_IRQHandler(void)
{
    uint8_t data;

    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(USER_USART))
    {
        // ���յ�������
        data = LPUART_ReadByte(USER_USART);
    }
    LPUART_ClearStatusFlags(USER_USART, kLPUART_RxOverrunFlag);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �û������ֽ����
// ����˵��     c             ��Ҫ���͵��ֽ�
// ���ز���     void        
// ʹ��ʾ��     uart_write_byte(0xA5);                                  // ����1����0xA5
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_putchar(char c)
{
    while(!(USER_USART->STAT & LPUART_STAT_TDRE_MASK));                 // �ȴ��������
    LPUART_WriteBlocking(USER_USART, (const uint8_t *)&c, 1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ�������
// ����˵��     *buff           Ҫ���͵������ַ
// ����˵��     len             ���ͳ���
// ���ز���     void
// ʹ��ʾ��     user_uart_write_buffer(&a[0], 5);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_write_buffer (const uint8 *buff, uint32 len)
{
    while(!(USER_USART->STAT & LPUART_STAT_TDRE_MASK));                 // �ȴ��������
    LPUART_WriteBlocking(USER_USART, buff, len);                        // д�뷢������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ڷ����ַ���
// ����˵��     *str            Ҫ���͵��ַ�����ַ
// ���ز���     void
// ʹ��ʾ��     user_uart_write_string("seekfree"); 
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void user_uart_write_string (const char *str)
{
    while(*str)                                                                 // һֱѭ������β
    {
        user_uart_putchar(*str ++);                                             // ��������
    }
}
//-------------------------------------------------------------------------------------------------------------------
// �������     �Զ���user_printf����
// ����˵��     ��printf�÷���ͬ
// ���ز���     void        
// ʹ��ʾ��     zf_user_printf("seekfree%d\r\n", 0xA5);                                  // ����1����0xA5
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void zf_user_printf(const char *format, ...) 
{
    va_list args;
    va_start(args, format);

    char buffer[64]; // �������ת������ַ�������Ϊ64
    int written = 0;
    while (*format && written < 63) 
    {
        if (*format == '%') 
        {
            format++; // ����%
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
                char char_value = va_arg(args, int); // char������va_arg�лᱻ����Ϊint
                user_uart_putchar(char_value);
                written++;
            } 
            else if (*format == 'f') 
            {
                float float_value = va_arg(args, double); // ��������va_arg�лᱻ����Ϊdouble
                float_to_str(float_value, buffer);
                for (int i = 0; buffer[i] != '\0' && written < 63; i++) 
                {
                    user_uart_putchar(buffer[i]);
                    written++;
                }
            }
            else
            {
                format++; // �ƶ�����һ���ַ�
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
// �������     �û����ڳ�ʼ��
// ���ز���     void            
// ʹ��ʾ��     uart_init();          
// ��ע��Ϣ     
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

