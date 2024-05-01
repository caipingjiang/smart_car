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
* �ļ�����          zf_device_wireless_uart
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
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   RX                  �鿴 zf_device_wireless_uart.h �� WIRELESS_UART_RX_PINx �궨��
*                   TX                  �鿴 zf_device_wireless_uart.h �� WIRELESS_UART_TX_PINx �궨��
*                   RTS                 �鿴 zf_device_wireless_uart.h �� WIRELESS_UART_RTS_PINx �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_device_type.h"

#include "zf_device_wireless_uart.h"
#include <stdlib.h>

static  fifo_struct         wireless_uart_fifo;
static  uint8               wireless_uart_buffer[WIRELESS_UART_BUFFER_SIZE];    // ���ݴ������

static  uint8               wireless_uart_data          = 0;
#if (1 == WIRELESS_UART_AUTO_BAUD_RATE)
static volatile wireless_uart_auto_baudrate_state_enum  wireless_auto_baud_flag     = WIRELESS_UART_AUTO_BAUD_RATE_INIT;
static volatile uint8                                   wireless_auto_baud_data[3]  = {0x00, 0x01, 0x03};
#endif

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��������
// ����˵��     data            8bit ����
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     wireless_uart_send_byte(data);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_byte (const uint8 data)
{
    uint16 time_count = WIRELESS_UART_TIMEOUT_COUNT;
    while(time_count)
    {
        if(!gpio_get_level(WIRELESS_UART_RTS_PIN))
        {
            uart_write_byte(WIRELESS_UART_INDEX, data);                         // ��������
            break;
        }
        time_count --;
        system_delay_ms(1);
    }
    return (0 == time_count);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �������ݿ�
// ����˵��     *buff           ���ͻ�����
// ����˵��     len             �������ݳ���
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     wireless_uart_send_buffer(buff, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_buffer (const uint8 *buff, uint32 len)
{
    zf_assert(NULL != buff);
    uint16 time_count = 0;
    while(0 != len)
    {
        if(!gpio_get_level(WIRELESS_UART_RTS_PIN))                              // ���RTSΪ�͵�ƽ �������������
        {
            if(30 <= len)                                                       // ���ݷ� 30byte ÿ������
            {
                uart_write_buffer(WIRELESS_UART_INDEX, buff, 30);               // ��������
                buff += 30;                                                     // ��ַƫ��
                len -= 30;                                                      // ����
                time_count = 0;
            }
            else                                                                // ���� 30byte ������һ���Է������
            {
                uart_write_buffer(WIRELESS_UART_INDEX, buff, len);              // ��������
                len = 0;
                break;
            }
        }
        else                                                                    // ���RTSΪ�ߵ�ƽ ��ģ��æ
        {
            if(WIRELESS_UART_TIMEOUT_COUNT <= (++ time_count))                  // ���������ȴ�ʱ��
            {
                break;                                                          // �˳�����
            }
            system_delay_ms(1);
        }
    }
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �����ַ���
// ����˵��     *str            Ҫ���͵��ַ�����ַ
// ���ز���     uint32          ʣ�෢�ͳ���
// ʹ��ʾ��     wireless_uart_send_string("Believe in yourself.");
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_send_string (const char *str)
{
    zf_assert(NULL != str);
    uint16 time_count = 0;
    uint32 len = strlen(str);
    while(0 != len)
    {
        if(!gpio_get_level(WIRELESS_UART_RTS_PIN))                              // ���RTSΪ�͵�ƽ �������������
        {
            if(30 <= len)                                                       // ���ݷ� 30byte ÿ������
            {
                uart_write_buffer(WIRELESS_UART_INDEX, (const uint8 *)str, 30); // ��������
                str += 30;                                                      // ��ַƫ��
                len -= 30;                                                      // ����
                time_count = 0;
            }
            else                                                                // ���� 30byte ������һ���Է������
            {
                uart_write_buffer(WIRELESS_UART_INDEX, (const uint8 *)str, len);// ��������
                len = 0;
                break;
            }
        }
        else                                                                    // ���RTSΪ�ߵ�ƽ ��ģ��æ
        {
            if(WIRELESS_UART_TIMEOUT_COUNT <= (++ time_count))                  // ���������ȴ�ʱ��
            {
                break;                                                          // �˳�����
            }
            system_delay_ms(1);
        }
    }
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��������ͷͼ������λ���鿴ͼ��
// ����˵��     *image_addr     ��Ҫ���͵�ͼ���ַ
// ����˵��     image_size      ͼ��Ĵ�С
// ���ز���     void
// ʹ��ʾ��     wireless_uart_send_image(&mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void wireless_uart_send_image (const uint8 *image_addr, uint32 image_size)
{
    zf_assert(NULL != image_addr);
    extern uint8 camera_send_image_frame_header[4];
    wireless_uart_send_buffer(camera_send_image_frame_header, 4);
    wireless_uart_send_buffer((uint8 *)image_addr, image_size);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��ȡ����
// ����˵��     *buff           ���ջ�����
// ����˵��     len             ��ȡ���ݳ���
// ���ز���     uint32          ʵ�ʶ�ȡ���ݳ���
// ʹ��ʾ��     wireless_uart_read_buffer(buff, 32);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_uart_read_buffer (uint8 *buff, uint32 len)
{
    zf_assert(NULL != buff);
    uint32 data_len = len;
    fifo_read_buffer(&wireless_uart_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� �����жϻص�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     wireless_uart_callback();
// ��ע��Ϣ     �ú����� ISR �ļ� �����жϳ��򱻵���
//              �ɴ����жϷ��������� wireless_module_uart_handler() ����
//              ���� wireless_module_uart_handler() �������ñ�����
//-------------------------------------------------------------------------------------------------------------------
int16 status = 0, control_flag = 0;
int16 temp=0;
int16 vx=0,vy=0;
void wireless_uart_callback (void)
{
	
    if(uart_query_byte(WIRELESS_UART_INDEX, &wireless_uart_data) != 0)
    {
        
        fifo_write_buffer(&wireless_uart_fifo, &wireless_uart_data,1 );
        if     (wireless_uart_data == 'a') { for(uint8 i = 0; i<4; i++){Inc_Kp[i]+=5;};    }
        else if(wireless_uart_data == 'b') { for(uint8 i = 0; i<4; i++){Inc_Kp[i]-=5;};    }
        else if(wireless_uart_data == 'c') { for(uint8 i = 0; i<4; i++){Inc_Ki[i]+=0.2;}; }
        else if(wireless_uart_data == 'd') { for(uint8 i = 0; i<4; i++){Inc_Ki[i]-=0.2;}; }
        else if(wireless_uart_data == 'e') { for(uint8 i = 0; i<4; i++){Inc_Kd[i]+=1;}; }
        else if(wireless_uart_data == 'f') { for(uint8 i = 0; i<4; i++){Inc_Kd[i]-=1;}; }
        else if(wireless_uart_data == 'g') { Ki_w+=0.005;   }
        else if(wireless_uart_data == 'h') { Ki_w-=0.005;   }
        else if(wireless_uart_data == 'i') { Kp_w+=0.05;    }
        else if(wireless_uart_data == 'j') { Kp_w-=0.05;    }
        else if(wireless_uart_data == 'k') { Kd_w+=0.01;    }
        else if(wireless_uart_data == 'l') { Kd_w-=0.01;    }
        else if(wireless_uart_data == 'm') { Kp_A+=0.5;     }
        else if(wireless_uart_data == 'n') { Kp_A-=0.5;     }
        else if(wireless_uart_data == 'o') { Kd_A+=1;       }
        else if(wireless_uart_data == 'p') { Kd_A-=1;       }
        else if(wireless_uart_data == 'r') { Ki_A+=0.02;    }
        else if(wireless_uart_data == 's') { Ki_A-=0.02;    }
        else if(wireless_uart_data == 't') { Kp_T+=0.2;     }
        else if(wireless_uart_data == 'u') { Kp_T-=0.2;     }
        else if(wireless_uart_data == 'v') { Kd_T+=0.2;     }
        else if(wireless_uart_data == 'w') { Kd_T-=0.2;     }
        else if(wireless_uart_data == 'x') { v_y+=2;        }
        else if(wireless_uart_data == 'y') { v_y-=2;        }
        else if(wireless_uart_data == '!') { v_x+=5;        }
        else if(wireless_uart_data == '$') { v_x-=5;        }
         
	    else if(wireless_uart_data == '@') {;}

        else if(wireless_uart_data == '>') {t_b += 5;}
        else if(wireless_uart_data == '<') {t_b -= 5;}
        else if(wireless_uart_data == '[') {k += 0;}
        else if(wireless_uart_data == ']') {k += 1;}
		 
		else if(wireless_uart_data == '+') {y_threshold += 1;}
        else if(wireless_uart_data == '-') {y_threshold -= 1;}
        else if(wireless_uart_data == ')') {x_threshold += 1;}
        else if(wireless_uart_data == '(') {x_threshold -= 1;}
		
        else if(wireless_uart_data == '{') {Kp_correct1 += 0.25;}
        else if(wireless_uart_data == '}') {Kp_correct1 -= 0.25;}
        else if(wireless_uart_data == ';') {Kd_correct1 += 10;}
        else if(wireless_uart_data == '\'') {Kd_correct1 -= 10;}

        else if(wireless_uart_data == '|') {Kp_correct2 += 0.01;}
        else if(wireless_uart_data == '.') {Kp_correct2 -= 0.01;}
        else if(wireless_uart_data == ':') {Kd_correct2 += 0.1;}
        else if(wireless_uart_data == '\"') {Kd_correct2 -= 0.1;}
        
		else if(wireless_uart_data == 'z') 
		{
           clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
           debug_init();
           my_motor_init();	//--->>>>>>>>>ע�������D12-D15������ips200��csi�ظ�ʹ�ã�����ͬʱʹ��
           my_encoder_init();	//����Ļ��ʾ����Ҳ��Ӱ��

           wireless_uart_init();
           imu660ra_init();

           pit_ms_init(PIT_CH1, 5);
           interrupt_set_priority(LPUART8_IRQn,0);
           interrupt_set_priority(PIT_IRQn, 1);
           interrupt_global_enable(0);
           
           gpio_init(B11, GPO, GPIO_LOW, GPO_PUSH_PULL);system_delay_ms(100); gpio_toggle_level(B11);system_delay_ms(100); gpio_toggle_level(B11);
       }
        
//        //���ն�άң�����ݵ�״̬��
//        if(status == 0 && wireless_uart_data == ':' ) {status = 1;}                  //����������vx
//        if(status == 1 && wireless_uart_data != '-' ) {status = 2;}                  //vxΪ����
//        if(status == 1 && wireless_uart_data == '-' ) {status = 3;}                  //vxΪ����
//        if((status == 2||status == 3) && wireless_uart_data == ',' ) {status = 4;}   //vx���꣬������vy
//        if(status == 4 && wireless_uart_data != '-' ) {status = 5;}                  //vyΪ����
//        if(status == 4 && wireless_uart_data == '-' ) {status = 6;}                  //vyΪ����
//        if((status == 5||status == 6) && wireless_uart_data == '\n' ) {v_x = vx; v_y = vy; status = 0;control_flag=1;}  //v����ص�״̬0

//        //atoi()����ֻ�ܽ�����С����͸��ŵ��ַ���ת��Ϊ����
//		const char *data_str = (const char *)&wireless_uart_data;  // ���޷����ַ��ͱ���ת��Ϊconst char *����ָ��
//		temp = (int16)atoi(data_str);
//        //temp = atoi((const char*)&wireless_uart_data);
//        if(status == 2){vx = vx*10 + temp;}
//        if(status == 3){vx = vx*10 - temp;}
//        if(status == 5){vy = vy*10 + temp;}
//        if(status == 6){vy = vy*10 - temp;}

        //wireless_uart_send_buffer(wireless_uart_buffer,len);
        //����������Ϊ�ֽ�����������Ϊuint8�����ݣ���ôֱ����Ϊ1���У���Ҫ�������ܻ�������
        memset(&wireless_uart_data, 0, 1);
//    
    }
#if WIRELESS_UART_AUTO_BAUD_RATE                                                // �����Զ�������
    if(WIRELESS_UART_AUTO_BAUD_RATE_START == wireless_auto_baud_flag && 3 == fifo_used(&wireless_uart_fifo))
    {
        uint32 wireless_auto_baud_count = 3;
        wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_GET_ACK;
        fifo_read_buffer(&wireless_uart_fifo, (uint8 *)wireless_auto_baud_data, (uint32 *)&wireless_auto_baud_count, FIFO_READ_AND_CLEAN);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ת����ģ�� ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     wireless_uart_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 wireless_uart_init (void)
{
    uint8 return_state = 0;
    set_wireless_type(WIRELESS_UART, wireless_uart_callback);

    fifo_init(&wireless_uart_fifo, FIFO_DATA_8BIT, wireless_uart_buffer, WIRELESS_UART_BUFFER_SIZE);
    gpio_init(WIRELESS_UART_RTS_PIN, GPI, GPIO_HIGH, GPI_PULL_UP);
#if(0 == WIRELESS_UART_AUTO_BAUD_RATE)                                          // �ر��Զ�������
    // ������ʹ�õĲ�����Ϊ115200 Ϊ����ת����ģ���Ĭ�ϲ����� ������������������������ģ�鲢�޸Ĵ��ڵĲ�����
    uart_init (WIRELESS_UART_INDEX, WIRELESS_UART_BUAD_RATE, WIRELESS_UART_RX_PIN, WIRELESS_UART_TX_PIN);   // ��ʼ������
    uart_rx_interrupt(WIRELESS_UART_INDEX, 1);
#elif(1 == WIRELESS_UART_AUTO_BAUD_RATE)                                        // �����Զ�������
    uint8 rts_init_status = 0;
    uint16 time_count = 0;

    wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_INIT;
    wireless_auto_baud_data[0] = 0;
    wireless_auto_baud_data[1] = 1;
    wireless_auto_baud_data[2] = 3;

    rts_init_status = gpio_get_level(WIRELESS_UART_RTS_PIN);
    gpio_init(WIRELESS_UART_RTS_PIN, GPO, rts_init_status, GPO_PUSH_PULL);      // ��ʼ����������

    uart_init (WIRELESS_UART_INDEX, WIRELESS_UART_BUAD_RATE, WIRELESS_UART_RX_PIN, WIRELESS_UART_TX_PIN);   // ��ʼ������
    uart_rx_interrupt(WIRELESS_UART_INDEX, 1);

    system_delay_ms(5);                                                         // ģ���ϵ�֮����Ҫ��ʱ�ȴ�
    gpio_set_level(WIRELESS_UART_RTS_PIN, !rts_init_status);                    // RTS�������ߣ������Զ�������ģʽ
    system_delay_ms(100);                                                       // RTS����֮�������ʱ20ms
    gpio_toggle_level(WIRELESS_UART_RTS_PIN);                                   // RTS����ȡ��

    do
    {
        wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_START;
        uart_write_byte(WIRELESS_UART_INDEX, wireless_auto_baud_data[0]);       // �����ض����� ����ģ���Զ��жϲ�����
        uart_write_byte(WIRELESS_UART_INDEX, wireless_auto_baud_data[1]);       // �����ض����� ����ģ���Զ��жϲ�����
        uart_write_byte(WIRELESS_UART_INDEX, wireless_auto_baud_data[2]);       // �����ض����� ����ģ���Զ��жϲ�����
        system_delay_ms(20);

        if(WIRELESS_UART_AUTO_BAUD_RATE_GET_ACK != wireless_auto_baud_flag)     // �����Զ��������Ƿ����
        {
            return_state = 1;                                                   // ���������뵽������� ˵���Զ�������ʧ����
            break;
        }

        time_count = 0;
        if( 0xa5 != wireless_auto_baud_data[0] &&                               // �����Զ��������Ƿ���ȷ
            0xff != wireless_auto_baud_data[1] &&                               // �����Զ��������Ƿ���ȷ
            0xff != wireless_auto_baud_data[2] )                                // �����Զ��������Ƿ���ȷ
        {
            return_state = 1;                                                   // ���������뵽������� ˵���Զ�������ʧ����
            break;
        }
        wireless_auto_baud_flag = WIRELESS_UART_AUTO_BAUD_RATE_SUCCESS;

        gpio_init(WIRELESS_UART_RTS_PIN, GPI, 0, GPI_PULL_UP);                  // ��ʼ����������
        system_delay_ms(10);                                                    // ��ʱ�ȴ� ģ��׼������
    }while(0);
#endif
    return return_state;
}
