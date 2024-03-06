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
* �ļ�����          zf_common_debug
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

#include "fsl_pwm.h"
#include "zf_common_fifo.h"
#include "zf_common_interrupt.h"
#include "zf_driver_gpio.h"
#include "zf_driver_pwm.h"
#include "zf_driver_uart.h"

#include "zf_common_debug.h"

#if DEBUG_UART_USE_INTERRUPT                                                    // ������� debug uart �����ж�
uint8                       debug_uart_buffer[DEBUG_RING_BUFFER_LEN];           // ���ݴ������
uint8                       debug_uart_data = 0;
#endif

fifo_struct                 debug_uart_fifo;
static debug_output_struct  debug_output_info;
static volatile uint8       zf_debug_init_flag = 0;
static volatile uint8       zf_debug_assert_enable = 1;

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ����ʱ���� �� 120MHz ����һ����ʱ�� ����Ƭ����Ҫ���ݸ���ʱ������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_delay();
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_delay (void)
{
    vuint32 loop_1 = 0, loop_2 = 0;
    for(loop_1 = 0; 0xFF >= loop_1; loop_1 ++)
    {
        for(loop_2 = 0; 0xFFFF >= loop_2; loop_2 ++)
        {
            __NOP();
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug �������� ��Ҫ�Ƿ�ֹ���Ժ�����ź�ά�ֶ�����Ӳ��ʧ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_protective_handler();
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_protective_handler (void)
{
    pwm_set_duty(PWM1_MODULE0_CHB_D13, 0);
    pwm_set_duty(PWM1_MODULE0_CHA_D12, 0);
    pwm_set_duty(PWM1_MODULE1_CHB_D15, 0);
    pwm_set_duty(PWM1_MODULE1_CHA_D14, 0);
    pwm_set_duty(PWM1_MODULE2_CHB_D17, 0);
    pwm_set_duty(PWM1_MODULE2_CHA_D16, 0);
    pwm_set_duty(PWM1_MODULE3_CHB_B11, 0);
    pwm_set_duty(PWM1_MODULE3_CHA_B10, 0);
    
    
    pwm_set_duty(PWM2_MODULE0_CHB_C7, 0);
    pwm_set_duty(PWM2_MODULE0_CHA_C6, 0);
    pwm_set_duty(PWM2_MODULE1_CHB_C9, 0);
    pwm_set_duty(PWM2_MODULE1_CHA_C8, 0);
    pwm_set_duty(PWM2_MODULE2_CHB_C11, 0);
    pwm_set_duty(PWM2_MODULE2_CHA_C10, 0);
    pwm_set_duty(PWM2_MODULE3_CHB_B1, 0);
    pwm_set_duty(PWM2_MODULE3_CHA_B0, 0);
    
    pwm_set_duty(PWM4_MODULE0_CHA_B24, 0);
    pwm_set_duty(PWM4_MODULE1_CHA_B25, 0);
    pwm_set_duty(PWM4_MODULE2_CHA_C30, 0);
    pwm_set_duty(PWM4_MODULE3_CHA_C31, 0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ��������ӿ�
// ����˵��     *str        ��Ҫ������ַ���
// ���ز���     void
// ʹ��ʾ��     debug_uart_str_output("Log message");
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_uart_str_output (const char *str)
{
    uart_write_string(DEBUG_UART_INDEX, str);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ����ӿ�
// ����˵��     *type       log ����
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ����˵��     *str        ��Ϣ
// ���ز���     void
// ʹ��ʾ��     debug_output("Log message", file, line, str);
// ��ע��Ϣ     ���������ļ��ڲ����� �û����ù�ע Ҳ�����޸�
//-------------------------------------------------------------------------------------------------------------------
static void debug_output (char *type, char *file, int line, char *str)
{
    char *file_str;
    vuint16 i = 0, j = 0;
    vint16 len_origin = 0;
    vint16 show_len = 0;
    vint16 show_line_index = 0;
    len_origin = strlen(file);

    char output_buffer[256];
    char file_path_buffer[64];

    if(debug_output_info.type_index)
    {
        debug_output_info.output_screen_clear();
    }

    if(zf_debug_init_flag)
    {
        if(debug_output_info.type_index)
        {
            // ��Ҫ���н��ļ���·�����������
            // <���������·�� ֻ���һ��Ŀ¼ ���� src/main.c>
            // ��� line : xxxx
            debug_output_info.output_screen(0, show_line_index ++, type);

            file_str = file;
            len_origin = strlen(file);
            show_len = (debug_output_info.display_x_max / debug_output_info.font_x_size);

            while('\0' != *file_str ++);

            // ֻȡһ��Ŀ¼ ����ļ������̷���Ŀ¼ ���� MDK �Ĺ��̸�Ŀ¼ �ͻ�ֱ�������ǰĿ¼
            for(j = 0; (2 > j) && (0 <= len_origin); len_origin --)             // �������� '/'
            {
                file_str --;
                if(('/' == *file_str) || (0x5C == *file_str))
                {
                    j ++;
                }
            }

            // �ļ�·�����浽������
            if(0 <= len_origin)
            {
                file_str ++;
                sprintf(output_buffer, "file: %s", file_str);
            }
            else
            {
                if(0 == j)
                {
                    sprintf(output_buffer, "file: mdk/%s", file_str);
                }
                else
                {
                    sprintf(output_buffer, "file: %s", file_str);
                }
            }

            // ��Ļ��ʾ·��
            for(i = 0; i < ((strlen(output_buffer) / show_len) + 1); i ++)
            {
                for(j = 0; j < show_len; j ++)
                {
                    if(strlen(output_buffer) < (j + i * show_len))
                    {
                        break;
                    }
                    file_path_buffer[j] = output_buffer[j + i * show_len];
                }
                
                file_path_buffer[j] = '\0';                                     // ĩβ���\0
                
                debug_output_info.output_screen(0, debug_output_info.font_y_size * show_line_index ++, file_path_buffer);
            }

            // ��Ļ��ʾ�к�
            sprintf(output_buffer, "line: %d", line);
            debug_output_info.output_screen(0, debug_output_info.font_y_size * show_line_index ++, output_buffer);

            // ��Ļ��ʾ Log ����еĻ�
            if(NULL != str)
            {
                for(i = 0; i < ((strlen(str) / show_len) + 1); i ++)
                {
                    for(j = 0; j < show_len; j ++)
                    {
                        if(strlen(str) < (j + i * show_len))
                        {
                            break;
                        }
                        file_path_buffer[j] = str[j + i * show_len];
                    }
                    
                    file_path_buffer[j] = '\0';                                 // ĩβ���\0
                    
                    debug_output_info.output_screen(0, debug_output_info.font_y_size * show_line_index ++, file_path_buffer);
                }
            }
        }
        else
        {
            char output_buffer[256];
            memset(output_buffer, 0, 256);
            debug_output_info.output_uart(type);
            if(NULL != str)
            {
                sprintf(output_buffer, "\r\nfile %s line %d: %s.\r\n", file, line, str);
            }
            else
            {
                sprintf(output_buffer, "\r\nfile %s line %d.\r\n", file, line);
            }
            debug_output_info.output_uart(output_buffer);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���Դ��ڷ��ͻ�����
// ����˵��     *buff       �������ݴ�ŵ�����ָ��
// ����˵��     len         ��Ҫ���͵ĳ���
// ���ز���     uint32      ʣ��δ���͵ĳ���
// ʹ��ʾ��     
// ��ע��Ϣ     ��������Ҫ���� DEBUG_UART_USE_INTERRUPT �궨��ſ�ʹ��
//-------------------------------------------------------------------------------------------------------------------
uint32 debug_send_buffer(const uint8 *buff, uint32 len)
{
    uart_write_buffer(DEBUG_UART_INDEX, buff, len);
    return 0;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ debug ���λ���������
// ����˵��     *buff       �������ݴ�ŵ�����ָ��
// ����˵��     len         ��Ҫ��ȡ�ĳ���
// ���ز���     uint32      �������ݵ�ʵ�ʳ���
// ʹ��ʾ��     
// ��ע��Ϣ     ��������Ҫ���� DEBUG_UART_USE_INTERRUPT �궨��ſ�ʹ��
//-------------------------------------------------------------------------------------------------------------------
uint32 debug_read_ring_buffer (uint8 *buff, uint32 len)
{
    fifo_read_buffer(&debug_uart_fifo, buff, &len, FIFO_READ_AND_CLEAN);
    return len;
}

#if DEBUG_UART_USE_INTERRUPT                                                    // �������� ֻ�������ô����жϲű���
//-------------------------------------------------------------------------------------------------------------------
// �������     debug �����жϴ����� isr.c �ж�Ӧ�����жϷ���������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_interrupr_handler();
// ��ע��Ϣ     ��������Ҫ���� DEBUG_UART_USE_INTERRUPT �궨��ſ�ʹ��
//              ���ұ�����Ĭ�Ϸ����� UART1 �Ĵ��ڽ����жϴ���
//-------------------------------------------------------------------------------------------------------------------
void debug_interrupr_handler (void)
{
    if(zf_debug_init_flag)
    {
        uart_query_byte(DEBUG_UART_INDEX, &debug_uart_data);                    // ��ȡ��������
        fifo_write_buffer(&debug_uart_fifo, &debug_uart_data, 1);               // ���� FIFO
    }
}

#endif

//-------------------------------------------------------------------------     // printf �ض��� �˲��ֲ������û�����
#if defined(__ICCARM__)
#define PUTCHAR_PROTOTYPE int32_t fputc (int32_t ch, FILE *f)
#define GETCHAR_PROTOTYPE int32_t fgetc (FILE *f)
#elif defined(__GNUC__)
#define PUTCHAR_PROTOTYPE int32_t __io_putchar (int32_t ch)
#define GETCHAR_PROTOTYPE int32_t __io_getchar ()
#endif

#if defined(__ICCARM__)
PUTCHAR_PROTOTYPE
{
    if(zf_debug_init_flag)
    {
        uart_write_byte(DEBUG_UART_INDEX, (ch & 0xFF));
    }
    return ch;
}

GETCHAR_PROTOTYPE
{
    int data = 0;
    if(zf_debug_init_flag)
    {
        data = uart_read_byte(DEBUG_UART_INDEX);
    }
    return data;
}
#else
int32_t fputc (int32_t ch, FILE* f)
{
    if(zf_debug_init_flag)
    {
        uart_write_byte(DEBUG_UART_INDEX, (ch & 0xFF));
    }
    return ch;
}

int fgetc(FILE *f)
{
    int data = 0;
    if(zf_debug_init_flag)
    {
        data = uart_read_byte(DEBUG_UART_INDEX);
    }
    return data;
}
#endif
//-------------------------------------------------------------------------     // printf �ض��� �˲��ֲ������û�����

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ö���
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_assert_enable();
// ��ע��Ϣ     ����Ĭ�Ͽ��� ���鿪������
//-------------------------------------------------------------------------------------------------------------------
void debug_assert_enable (void)
{
    zf_debug_assert_enable = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���ö���
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_assert_disable();
// ��ע��Ϣ     ����Ĭ�Ͽ��� ��������ö���
//-------------------------------------------------------------------------------------------------------------------
void debug_assert_disable (void)
{
    zf_debug_assert_enable = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ���Դ�����
// ����˵��     pass        �ж��Ƿ񴥷�����
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ���ز���     void
// ʹ��ʾ��     zf_assert(0);
// ��ע��Ϣ     �����������ֱ�ӵ��õ� �˲��ֲ������û�����
//              ʹ�� zf_commmon_debug.h �е� zf_assert(x) �ӿ�
//-------------------------------------------------------------------------------------------------------------------
void debug_assert_handler (uint8 pass, char *file, int line)
{
    do
    {
        if(pass || !zf_debug_assert_enable)
        {
            break;
        }

        static uint8 assert_nest_index = 0;

        if(0 != assert_nest_index)
        {
            while(1);
        }
        assert_nest_index ++;

        interrupt_global_disable();
        debug_protective_handler();

        while(1)
        {
            // ���������ת������ͣס��
            // һ����ĺ����������ݳ�����
            // �������Լ����õ� zf_assert(x) �ӿڴ�������

            // ��������� debug_init ��ʼ���� log ���
            // ���ڶ�Ӧ�������ȥ�鿴���ĸ��ļ�����һ�б���

            // ���û�г�ʼ�� debug
            // �ǾͿ������ file ���ַ���ֵ�� line ������
            // �Ǵ�������ļ�·�����ƺͶ�Ӧ��������

            // ��ȥ���Կ�����Ϊʲô��������

            debug_output("Assert error", file, line, NULL);
            debug_delay();
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ������Ϣ������
// ����˵��     pass        �ж��Ƿ񴥷�����
// ����˵��     *str        �������Ϣ
// ����˵��     *file       �ļ���
// ����˵��     line        Ŀ������
// ���ز���     void
// ʹ��ʾ��     zf_log(0, "Log Message");
// ��ע��Ϣ     �����������ֱ�ӵ��õ� �˲��ֲ������û�����
//              ʹ�� zf_commmon_debug.h �е� zf_log(x, str) �ӿ�
//-------------------------------------------------------------------------------------------------------------------
void debug_log_handler (uint8 pass, char *str, char *file, int line)
{
    do
    {
        if(pass)
        {
            break;
        }
        if(zf_debug_init_flag)
        {
            debug_output("Log message", file, line, str);
            //printf("Log message from %s line %d :\"%s\".\r\n", file, line, str);
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug �������Ϣ��ʼ��
// ����˵��     *info       debug �������Ϣ�ṹ��
// ���ز���     void
// ʹ��ʾ��     debug_output_struct_init(info);
// ��ע��Ϣ     �������һ�㲻���û�����
//-------------------------------------------------------------------------------------------------------------------
void debug_output_struct_init (debug_output_struct *info)
{
    info->type_index            = 0;

    info->display_x_max         = 0xFFFF;
    info->display_y_max         = 0xFFFF;

    info->font_x_size           = 0xFF;
    info->font_y_size           = 0xFF;

    info->output_uart           = NULL;
    info->output_screen         = NULL;
    info->output_screen_clear   = NULL;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ����󶨳�ʼ��
// ����˵��     *info       debug �������Ϣ�ṹ��
// ���ز���     void
// ʹ��ʾ��     debug_output_init(info);
// ��ע��Ϣ     �������һ�㲻���û�����
//-------------------------------------------------------------------------------------------------------------------
void debug_output_init (debug_output_struct *info)
{
    debug_output_info.type_index            = info->type_index;

    debug_output_info.display_x_max         = info->display_x_max;
    debug_output_info.display_y_max         = info->display_y_max;

    debug_output_info.font_x_size           = info->font_x_size;
    debug_output_info.font_y_size           = info->font_y_size;
    
    debug_output_info.output_uart           = info->output_uart;
    debug_output_info.output_screen         = info->output_screen;
    debug_output_info.output_screen_clear   = info->output_screen_clear;

    zf_debug_init_flag = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     debug ���ڳ�ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     debug_init();
// ��ע��Ϣ     ��Դ��ʾ��Ĭ�ϵ��� ��Ĭ�Ͻ����жϽ���
//-------------------------------------------------------------------------------------------------------------------
void debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);
    info.output_uart = debug_uart_str_output;
    debug_output_init(&info);

    uart_init(
        DEBUG_UART_INDEX,                                                       // �� zf_common_debug.h �в鿴��Ӧֵ
        DEBUG_UART_BAUDRATE,                                                    // �� zf_common_debug.h �в鿴��Ӧֵ
        DEBUG_UART_TX_PIN,                                                      // �� zf_common_debug.h �в鿴��Ӧֵ
        DEBUG_UART_RX_PIN);                                                     // �� zf_common_debug.h �в鿴��Ӧֵ

#if DEBUG_UART_USE_INTERRUPT                                                    // �������� ֻ�������ô����жϲű���
    fifo_init(&debug_uart_fifo, FIFO_DATA_8BIT, debug_uart_buffer, DEBUG_RING_BUFFER_LEN);
    uart_rx_interrupt(DEBUG_UART_INDEX, 1);                                     // ʹ�ܶ�Ӧ���ڽ����ж�
#endif
}

