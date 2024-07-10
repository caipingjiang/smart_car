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
* �ļ�����          zf_board_init
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
#include "zf_board_init.h"


// DEBUG���ڻص�����
void LP_FLEXCOMM4_IRQHandler(void)
{
    uint8_t data;
    
    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(DEBUG_USART))
    {
        // ���յ�������
        data = LPUART_ReadByte(DEBUG_USART);
    }
    LPUART_ClearStatusFlags(DEBUG_USART, kLPUART_RxOverrunFlag);
}


void debug_uart_putchar(char c)
{
    while(!(DEBUG_USART->STAT & LPUART_STAT_TDRE_MASK));                 // �ȴ��������
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
    // ��ת�ַ���
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

    // ���С����
    int len = strlen(str);
    str[len] = '.';
    str[len + 1] = '\0';

    // ����С������
    int decimal_part = float_part * 100000; // ������λС��
    int_to_str(decimal_part, str + len + 1);
}

// �Զ���debug_printf����
void zf_debug_printf(const char *format, ...) 
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
                char char_value = va_arg(args, int); // char������va_arg�лᱻ����Ϊint
                debug_uart_putchar(char_value);
                written++;
            } 
            else if (*format == 'f') 
            {
                float float_value = va_arg(args, double); // ��������va_arg�лᱻ����Ϊdouble
                float_to_str(float_value, buffer);
                for (int i = 0; buffer[i] != '\0' && written < 63; i++) 
                {
                    debug_uart_putchar(buffer[i]);
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
	//Ӳ���Ϸ�  ����������Խ�����ʹ����δ��ʼ�����豸
	//������ʾ���һ�����⣬��������˵�ҵ������ʼ������ô����Ҫ��HardFault��
	//�ܶ�����Ϊ�Լ������жϣ�Ȼ�����ж�����ʹ�������裬Ȼ�����ĳ�ʼ��˳�����ȳ�ʼ���ж�Ȼ���ٳ�ʼ������
	//��ô��������ˣ��жϳ�ʼ�����֮��Ჿ���ж�ֱ�ӽ����жϺ��������������Ҳ������жϺ�������ô�ͻ�����ж�����ʹ�õ������軹û����ʼ��
	//���Դ����Ҫע���������
	while(1)
    {
        gpio_toggle_level(led_core);
        system_delay_ms(100);
    }
}