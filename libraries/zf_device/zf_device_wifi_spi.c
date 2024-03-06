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
* �ļ�����          zf_device_wifi_spi
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
*                   RST                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_RST_PIN �궨��
*                   INT                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_INT_PIN �궨��
*                   CS                  �鿴 zf_device_wifi_spi.h �� WIFI_SPI_CS_PIN �궨��
*                   MISO                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MISO_PIN �궨��
*                   SCK                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_SCK_PIN �궨��
*                   MOSI                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MOSI_PIN �궨��
*                   5V                  5V ��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
*********************************************************************************************************************/

#include "stdio.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_common_interrupt.h"
#include "zf_driver_exti.h"
#include "zf_driver_spi.h"
#include "zf_device_type.h"

#include "zf_device_wifi_spi.h"

#define     WAIT_TIME_OUT               (10000)             // ��ָ��ȴ�ʱ��  ��λ��ms

#define     WIFI_SPI_WRITE_MAX          4092                // ����һ��SPIͨѶ����͵����ݳ���
    
#define     WIFI_SPI_WRITE_REQUEST      0x01
#define     WIFI_SPI_CHECK_STATE        0x02
#define     WIFI_SPI_WRITE_DATA         0x03
#define     WIFI_SPI_READ_DATA          0x04
#define     WIFI_SPI_WRITE_END          0x07
#define     WIFI_SPI_READ_END           0x08
    
#define     WIFI_SPI_WRITE_ADDR         0x00
#define     WIFI_SPI_STATE_ADDR         0x04

volatile    wifi_spi_buffer_state_enum   wifi_buffer_state;
volatile    wifi_spi_transmit_state_enum wifi_transmit_state;

static      fifo_struct wifi_spi_fifo;
static      uint8 wifi_spi_buffer[WIFI_SPI_BUFFER_SIZE];    // ���ݴ������

vuint8      wifi_spi_ack_flag = 0;                          // 0��ģ��δӦ�� 1��ģ����Ӧ��
uint8       wifi_spi_init_flag;                             // 0��ģ��δ��ʼ���ɹ�����δ���� 1��ģ�������Ӳ��ɹ���ʼ��
vuint8      wifi_spi_packet_num;                            // ���͵����ݰ�ID
vuint32     wifi_spi_send_remain_length;                    // ʣ��ķ��ͳ���
                        
uint8       wifi_spi_receive_buffer[WIFI_SPI_WRITE_MAX];

wifi_spi_information_struct wifi_spi_information;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����д�����ݵ�ģ��
//  @param      length      ��Ҫд��ĳ���
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_write_request(uint16 length)
{
    wifi_spi_buffer_struct head;

    head.cmd = WIFI_SPI_WRITE_REQUEST;
    head.addr = WIFI_SPI_WRITE_ADDR;
    head.dummy = 0x00;
    head.magic = 0xFE;
    head.sequence = wifi_spi_packet_num++;
    head.length = length;
    
    wifi_transmit_state = TRANSMIT_WRITE_REQUEST;
    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_write_8bit_array(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, 7);
    gpio_set_level(WIFI_SPI_CS_PIN, 1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡģ��״̬
//  @param      *length     ��Ҫ��ȡ����д��ĳ���
//  @return     WIFI_SPI_BUFFER_STATE_enum  ģ��״̬
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static wifi_spi_buffer_state_enum wifi_spi_read_state(uint16 *length)
{
    wifi_spi_buffer_struct head;
    
    head.cmd = WIFI_SPI_CHECK_STATE;
    head.addr = WIFI_SPI_STATE_ADDR;
    head.dummy = 0x00;

    wifi_spi_ack_flag = 0;
    wifi_transmit_state = TRANSMIT_READ_STATE;
    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_transfer_8bit(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, &head.cmd, 7);
    gpio_set_level(WIFI_SPI_CS_PIN, 1);

    if(BUFFER_WRITE == head.magic)
    {
        wifi_spi_packet_num = head.sequence;
    }
    *length = head.length;
    
    return (wifi_spi_buffer_state_enum)head.magic;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ݷ������
//  @param      void      
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_send_done(void)
{
    wifi_spi_buffer_struct head;
    
    head.cmd = WIFI_SPI_WRITE_END;
    head.addr = WIFI_SPI_WRITE_ADDR;
    head.dummy = 0x00;
    
    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_write_8bit_array(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, 3);
    gpio_set_level(WIFI_SPI_CS_PIN, 1);
    wifi_transmit_state = TRANSMIT_IDLE;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ݽ������
//  @param      void      
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_receive_done(void)
{
    wifi_spi_buffer_struct head;
    
    head.cmd = WIFI_SPI_READ_END;
    head.addr = WIFI_SPI_WRITE_ADDR;
    head.dummy = 0x00;

    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_write_8bit_array(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, 3);
    gpio_set_level(WIFI_SPI_CS_PIN, 1);
    wifi_transmit_state = TRANSMIT_IDLE;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ݵ�ģ��
//  @param      *buff        ��Ҫд�����ݵ��׵�ַ
//  @param      length       ��Ҫд�����ݵĳ���
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_send_data(const uint8 *buff, uint16 length)
{
    wifi_spi_buffer_struct head;
    
    head.cmd = WIFI_SPI_WRITE_DATA;
    head.addr = WIFI_SPI_WRITE_ADDR;
    head.dummy = 0x00;

    wifi_transmit_state = TRANSMIT_WRITE;
    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_write_8bit_array(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, 3);
    spi_write_8bit_array(WIFI_SPI_INDEX, buff, length);
    gpio_set_level(WIFI_SPI_CS_PIN, 1);
    wifi_spi_send_done();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ݵ�ģ�飨���Դ��ַ��
//  @param      *multi_buffer   ���Դ��ַ�Լ�ÿ��Դ��ַ��Ҫ���͵ĳ���
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_send_data_multi(wifi_spi_send_multi_struct *multi_buffer)
{
    uint8 i;
    wifi_spi_buffer_struct head;
    
    head.cmd = WIFI_SPI_WRITE_DATA;
    head.addr = WIFI_SPI_WRITE_ADDR;
    head.dummy = 0x00;

    wifi_transmit_state = TRANSMIT_WRITE;
    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_write_8bit_array(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, 3);
    
    for(i = 0; i < WIFI_SPI_MAX_MULTI; i++)
    {
        if(NULL != multi_buffer->source[i])   spi_write_8bit_array(WIFI_SPI_INDEX, multi_buffer->source[i], multi_buffer->length[i]);
    }
    gpio_set_level(WIFI_SPI_CS_PIN, 1);
    wifi_spi_send_done();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ģ�鷢�͵�����
//  @param      *buff        ��������Ļ������׵�ַ
//  @param      length       ��Ҫ���յĳ���
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_receive_data(uint8 *buff, uint16 length)
{
    wifi_spi_buffer_struct head;
    
    head.cmd = WIFI_SPI_READ_DATA;
    head.addr = WIFI_SPI_WRITE_ADDR;
    head.dummy = 0x00;
    
    wifi_transmit_state = TRANSMIT_READ;
    gpio_set_level(WIFI_SPI_CS_PIN, 0);
    spi_transfer_8bit(WIFI_SPI_INDEX, (const uint8 *)&head.cmd, &head.cmd, 3);
    spi_transfer_8bit(WIFI_SPI_INDEX, (const uint8 *)buff, buff, length);
    gpio_set_level(WIFI_SPI_CS_PIN, 1);
    wifi_spi_receive_done();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ģ��
//  @param      *str        �����ַ����׵�ַ
//  @return     void       		
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_send_command(const char *str)
{
    uint8  state = 0;
    uint16 send_length;
    uint16 wait_time = 0;
    
    // ����������
    send_length = (uint16)strlen(str);

    // �ȴ�����������
    while(TRANSMIT_IDLE != wifi_transmit_state);

    // ���û�н��뷢��״̬����������������
    while(BUFFER_WRITE != wifi_buffer_state)
    {
        wifi_spi_ack_flag = 0;
        wifi_spi_write_request(send_length);
        while(!wifi_spi_ack_flag)
        {
            wait_time++;
            if((WAIT_TIME_OUT / 4) <= wait_time)
            {
                state = 1;
                wifi_spi_init_flag = 0; // ģ���ѶϿ�
                break;
            }
            system_delay_ms(1);
        }
        
        if(1 == state)
        {
            break;
        }
    }
    
    wifi_buffer_state = BUFFER_IDLE;
    
    if(0 == state) // ͨѶδ��ʱ
    {
        wifi_spi_send_remain_length = send_length;
        // ������Ϣ
        wifi_spi_send_data((const uint8 *)str, send_length);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ģ��״̬����ȡģ�鷢�͵�����
//  @param      void        
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
void wifi_spi_check_state_read_buffer(void)
{
    uint16 wifi_spi_receive_length; // ���ν��յ�����������
    
    // ��ѯWIFIģ���״̬
    wifi_buffer_state = wifi_spi_read_state(&wifi_spi_receive_length);
    
    // �����Ҫ��ȡWIFIģ�����ݣ��򱣴���Ҫ��ȡ�ĳ���
    if(BUFFER_READ == wifi_buffer_state)
    {
        wifi_spi_receive_data((uint8 *)wifi_spi_receive_buffer, wifi_spi_receive_length);
        fifo_write_buffer(&wifi_spi_fifo, wifi_spi_receive_buffer, wifi_spi_receive_length);  // ���� FIFO
    }
    else if(BUFFER_IDLE == wifi_buffer_state)
    {
        // ���ģ���ڲ�������״̬Ϊ���У�����״̬Ҳ����Ϊ����
        wifi_transmit_state = TRANSMIT_IDLE;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ݵ�ģ��
//  @param      *buff       ��Ҫ���͵������׵�ַ     
//  @param      length      ��Ҫ���͵ĳ���
//  @return     uint32      ʣ��δ���ͳ���					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_write_data(const uint8 *buff, uint32 length)
{
    uint16 send_length;
    uint32 wait_time;
    
    // ��¼��Ҫ���͵ĳ���
    wifi_spi_send_remain_length = length;

    while(wifi_spi_send_remain_length)
    {
        send_length = (uint16)func_limit_ab(wifi_spi_send_remain_length, 1, WIFI_SPI_WRITE_MAX);
        
        // ����������
        wifi_spi_ack_flag = 0;
        wifi_spi_write_request(send_length);
        
        // ��ȴ�5��
        wait_time = 5000;
        while(!wifi_spi_ack_flag)
        {
            wait_time--;
            if(0 == wait_time)  break;
            system_delay_ms(1);
        }
        
        if(BUFFER_WRITE == wifi_buffer_state)
        {
            // ������Ϣ
            wifi_spi_send_data(buff, send_length);
            buff += send_length;
            wifi_spi_send_remain_length -= send_length;
            wifi_buffer_state = BUFFER_IDLE;
        }
        else
        {
            break;
        }
    }

    return wifi_spi_send_remain_length;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �������ݵ�ģ��(���Դ��ַ)
//  @param      *multi_buffer   ���Դ��ַ�Լ�ÿ��Դ��ַ��Ҫ���͵ĳ���
//  @return     uint32          ʣ��δ���ͳ���					
//  Sample usage:		        ���������ܳ��Ȳ��ܳ���4092��
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_write_data_multi(wifi_spi_send_multi_struct *multi_buffer)
{
    uint16 send_length;
    uint32 wait_time;
    
    // ��¼��Ҫ���͵ĳ���
    send_length = multi_buffer->length[0] + multi_buffer->length[1] + multi_buffer->length[2] + multi_buffer->length[3] + multi_buffer->length[4] + multi_buffer->length[5] + multi_buffer->length[6] + multi_buffer->length[7];
    
    if(WIFI_SPI_WRITE_MAX >= send_length)
    {
        // ����������
        wifi_spi_ack_flag = 0;
        wifi_spi_write_request(send_length);
        
        // ��ȴ�5��
        wait_time = 5000;
        while(!wifi_spi_ack_flag)
        {
            wait_time--;
            if(0 == wait_time)  break;
            system_delay_ms(1);
        }
        
        if(BUFFER_WRITE == wifi_buffer_state)
        {
            // ������Ϣ
            wifi_spi_send_data_multi(multi_buffer);
            send_length = 0;
            wifi_buffer_state = BUFFER_IDLE;
        }
    }

    return send_length;
}

//--------------------------------------------------------------------------------------------------
// �������     �ȴ�ģ����Ӧ
// ����˵��     *wait_buffer    �ȴ�����Ӧ���ַ���
// ����˵��     timeout         ��ʱʱ��
// ���ز���     uint8           0��ģ����Ӧָ������   1��ģ��δ��Ӧָ�����ݻ�ʱ
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_wait_ack (char *wait_buffer, uint32 timeout)
{
    uint8 return_state = 1;
    char receiver_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint32 receiver_len = 8;
    
    do
    {
        system_delay_ms(1);
        // �жϽ��ջ��������Ƿ�����Ҫ��Ӧ��ָ������ ����� ������ѭ�����ҷ���0
        receiver_len = 8;
        fifo_read_tail_buffer(&wifi_spi_fifo, (uint8 *)receiver_buffer, &receiver_len, FIFO_READ_ONLY);

        if(strstr(receiver_buffer, wait_buffer))
        {
            return_state = 0;
            break;
        }
        else if(strstr(receiver_buffer, "ERROR") || strstr(receiver_buffer, "busy"))
        {
        // ������յ��������ģ��æ ������ѭ�����ҷ���1
            return_state = 1;
            break;
        }
    }while(timeout --);
    
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���WiFi���ջ���������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     wifi_spi_clear_receive_buffer();
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static void wifi_spi_clear_receive_buffer (void)
{
    // ���WiFi���ջ�����
    fifo_clear(&wifi_spi_fifo);
}

//--------------------------------------------------------------------------------------------------
// �������     ģ�����ݽ���
// ����˵��     *target_buffer  Ŀ���ŵ�ַָ�� �ַ�������
// ����˵��     *origin_buffer  ������Դ��ַָ�� �ַ�������
// ����˵��     start_char      ��ʼ��ȡ�ֽ� ����� "1234" �д� '2' ��ʼ��ȡ ��Ӧ������ '2'
// ����˵��     end_char        ������ȡ�ֽ� ����� "1234" ���� '4' ������ȡ ��Ӧ������ '\0'(0x00 ���ַ� һ�����ַ�����β)
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_data_parse(wifi_spi_information.mac, wifi_spi_receive_buffer, '"', '"'); // ���û�ȡ����mac��ַ�󣬵��ô˺�����ȡmac��ַ
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_data_parse (uint8 *target_buffer, uint8 *origin_buffer, char start_char, char end_char)
{
    uint8 return_state = 0;
    char *location1;
    char *location2;
    location1 = strchr((char *)origin_buffer, start_char);
    if(location1)
    {
        location1 ++;
        location2 = strchr(location1, end_char);
        if(location2)
        {
            memcpy(target_buffer, location1, location2-location1);
        }
        else
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = 1;
    }
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �鿴ģ��汾��Ϣ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_get_version();
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_version (void)
{
    char *location1;
    uint8 return_state = 0;
    uint8 receiver_buffer[256];
    uint32 receiver_len = 256;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    wifi_spi_send_command("AT+GMR\r\n");
    do
    {

        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }

        fifo_read_buffer(&wifi_spi_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        location1 = strrchr((char *)receiver_buffer, ':');
        if(wifi_spi_data_parse(wifi_spi_information.version, (uint8 *)location1, ':', '('))
        {
            return_state = 1;
            break;
        }
    }while(0);
    wifi_spi_clear_receive_buffer();                                           // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ģ���������
// ����˵��     model           0:�ر�ģ��Ļ�д����  ����������ģ���д
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_echo_set("1");//����ģ���д����
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_echo_set (char *model)
{
    uint8 return_state = 0;
    
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    
    if('1' == *model)
    {
        wifi_spi_send_command("ATE1\r\n");
    }
    else
    {
        wifi_spi_send_command("ATE0\r\n");
    }

    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��ѯģ������ �� MAC ��ַ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     if(wifi_spi_get_mac()){}
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_mac (void)
{
    uint8 return_state = 0;
    uint8 receiver_buffer[64];
    uint32 receiver_len = 64;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    wifi_spi_send_command("AT+CIPAPMAC?\r\n");
    do
    {
        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }

        fifo_read_buffer(&wifi_spi_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        if(wifi_spi_data_parse(wifi_spi_information.mac, receiver_buffer, '"', '"'))
        {
            return_state = 1;
            break;
        }
    }while(0);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����


    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��ѯģ�����Ŀ��WIFI �� IP ��ַ(ȡ����ģ�鵱ǰ�Ĺ���ģʽ)
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     if(wifi_spi_get_ip()){}
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_ip (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    if(WIFI_SPI_STATION == wifi_spi_information.mode)
    {
        wifi_spi_send_command("AT+CIPSTA?\r\n");
    }
    else if(WIFI_SPI_SOFTAP == wifi_spi_information.mode)
    {
        wifi_spi_send_command("AT+CIPAP?\r\n");
    }

    do
    {
        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }
        uint8 receiver_buffer[128];
        uint32 receiver_len = 128;
        fifo_read_buffer(&wifi_spi_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
        if(wifi_spi_data_parse(wifi_spi_information.local_ip, receiver_buffer, '"', '"'))
        {
            return_state = 1;
            break;
        }
    }while(0);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��ѯģ��������Ϣ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     if(wifi_spi_get_information()){}
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_information (void)
{
    uint8 return_state = 0;
    do
    {
        // ��ȡģ��汾��
        if(wifi_spi_get_version())
        {
            return_state = 1;
            break;
        }
        // ��ȡģ��IP��ַ
        if(wifi_spi_get_ip())
        {
            return_state = 1;
            break;
        }
        // ��ȡģ��MAC��Ϣ
        if(wifi_spi_get_mac())
        {
            return_state = 1;
            break;
        }
        memcpy(wifi_spi_information.local_port, "no port", 7);
    }while(0);
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���� WiFi
// ����˵��     wifi_ssid       WiFi����
// ����˵��     pass_word       WiFi����
// ����˵��     model           0:��ѯWiFi�������   ����������WiFi
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_get_or_connect_wifi("WiFi_name", "Pass_word", 1);
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_set_wifi (char *wifi_ssid, char *pass_word)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    if(WIFI_SPI_SOFTAP == wifi_spi_information.mode)
    {
        sprintf(temp, "AT+CWSAP=\"%s\",\"%s\",5,3\r\n", wifi_ssid, pass_word);
        wifi_spi_send_command(temp);
    }
    else
    {
        sprintf(temp, "AT+CWJAP=\"%s\",\"%s\"\r\n", wifi_ssid, pass_word);
        wifi_spi_send_command(temp);
    }
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �ϵ��Ƿ��Զ�����WiFi
// ����˵��     model           0:�ϵ粻�Զ�����wifi   �������ϵ��Զ�����wifi
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_auto_connect_wifi(0); //�ϵ粻�Զ�����wifi
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_auto_connect_wifi (char *model)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    sprintf(temp, "AT+CWAUTOCONN=%s\r\n", model);
    wifi_spi_send_command(temp);
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ��������ģʽ
// ����˵��     model           0: ������ģʽ     1��������ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_set_connect_model("1");
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_set_connect_model (char *model)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    sprintf(temp, "AT+CIPMUX=%s\r\n", model);
    wifi_spi_send_command(temp);
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ���ô���ģʽ
// ����˵��     model           �C 0: ��ͨ����ģʽ     IP�Ͽ�����������
//                              �C 1: Wi-Fi ͸������ģʽ����֧�� TCP �����ӡ�UDP �̶�ͨ�ŶԶˡ�SSL �����ӵ����     IP�Ͽ���᲻�ϳ�����������
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_set_transfer_model("1");
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_set_transfer_model (char *model)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    sprintf(temp, "AT+CIPMODE=%s\r\n", model);
    wifi_spi_send_command(temp);
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ����ģ��ģʽ (Station/SoftAP/Station+SoftAP)
// ����˵��     state           0:�� Wi-Fi ģʽ�����ҹر� Wi-Fi RF----1: Station ģʽ----2: SoftAP ģʽ----3: SoftAP+Station ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_set_model("1");
// ��ע��Ϣ     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_set_model (wifi_spi_mode_enum  mode)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    if(WIFI_SPI_SOFTAP == mode)
    {
        wifi_spi_send_command("AT+CWMODE=2\r\n");
    }
    else
    {
        wifi_spi_send_command("AT+CWMODE=1\r\n");
    }
    // ����ģ�鹤��ģʽ
    wifi_spi_information.mode = mode;
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �ر�˯��ģʽ
// ����˵��     mode            
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ�� 
// ��ע��Ϣ     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_close_sleep_model (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    wifi_spi_send_command("AT+SLEEP=0\r\n");
    // ����ģ�鹤��ģʽ
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �Ͽ���wifi������
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_disconnected_wifi();
// ��ע��Ϣ     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_disconnected_wifi (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    wifi_spi_send_command("AT+CWQAP\r\n");
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �����͸��ģʽ
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_entry_serianet();
// ��ע��Ϣ     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_entry_serianet (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����
    wifi_spi_send_command("AT+CIPSEND\r\n");
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �˳�͸��ģʽ
// ����˵��     model           0:�ر�͸��ģʽ   ����������͸��ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_exit_serianet(1);
// ��ע��Ϣ     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_exit_serianet (void)
{
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    system_delay_ms(20);
    wifi_spi_send_command("+++");
    system_delay_ms(1000);

    return 0;
}

//--------------------------------------------------------------------------------------------------
// �������     ����TCP����
// ����˵��     ip              Զ�� IPv4 ��ַ��IPv6 ��ַ��������
// ����˵��     port            Զ�˶˿�ֵ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_connect_tcp_servers("192.168.101.110", "8080");
// ��ע��Ϣ     ����������Ӳ��ϵ��Ե�TCP������ ���Գ���ʹ���������ӵ���
//              �����ʹ��WiFi���� ���ܻᵼ��ģ������TCP�������ȴ��ϳ�ʱ��
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_connect_tcp_servers (char *ip, char *port, wifi_spi_transfer_mode_enum mode)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer();        // ���WiFi���ջ�����
    do
    {
        if(wifi_spi_set_connect_model("0"))
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();    // ���WiFi���ջ�����
        sprintf(temp, "AT+CIPSTARTEX=\"TCP\",\"%s\",%s\r\n", ip, port);
        wifi_spi_send_command(temp);

        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_spi_information.connect_state = WIFI_SPI_SERVER_OFF;
            break;
        }

        wifi_spi_clear_receive_buffer();    // ���WiFi���ջ�����

        // ���ô���ģʽ
        if(wifi_spi_set_transfer_model(WIFI_SPI_COMMAND == mode ? "0" : "1"))
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();    // ���WiFi���ջ�����
        wifi_spi_send_command("AT+CIPSTATE?\r\n");
        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            break;
        }
        else
        {
            uint8 receiver_buffer[128];
            uint32 receiver_len = 128;
            fifo_read_buffer(&wifi_spi_fifo, receiver_buffer, &receiver_len, FIFO_READ_ONLY);
            char* buffer_index = (char *)receiver_buffer;
            char* end_index;

            buffer_index += 22;
            buffer_index += strlen(ip);
            buffer_index += strlen(port);
            end_index = strchr(buffer_index, ',');

            memcpy(wifi_spi_information.local_port, "       ", 7);
            memcpy(wifi_spi_information.local_port, buffer_index, (end_index - buffer_index));
        }

        wifi_spi_information.connect_state = WIFI_SPI_SERVER_ON;
        wifi_spi_information.connect_mode = WIFI_SPI_TCP_CLIENT;
        wifi_spi_information.transfer_mode = mode;

        wifi_spi_clear_receive_buffer();    // ���WiFi���ջ�����
        if(WIFI_SPI_SERIANET == mode)       // ͸��ģʽ��ֱ�ӿ���͸��
        {
            if(wifi_spi_entry_serianet())
            {
                return_state = 1;
                break;
            }
        }

    }while(0);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     ����UDP����
// ����˵��     *ip             Զ�� IPv4 ��ַ��IPv6 ��ַ ������ �ַ�����ʽ
// ����˵��     *port           Զ�˶˿�ֵ �ַ�����ʽ
// ����˵��     *local_port     Զ�� IPv4 ��ַ��IPv6 ��ַ ������ �ַ�����ʽ
// ����˵��     mode            ģ������ͨ��ģʽ
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_connect_udp_client("192.168.101.110", "8080", "8080", WIFI_SPI_COMMAND);
// ��ע��Ϣ     �Զ�����ID
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_connect_udp_client (char *ip, char *port, char *local_port, wifi_spi_transfer_mode_enum mode)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer();                                            // ���WiFi���ջ�����
    do
    {
        if(wifi_spi_set_connect_model("0"))
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();                                        // ���WiFi���ջ�����
        
        sprintf(temp, "AT+CIPSTARTEX=\"UDP\",\"%s\",%s,%s\r\n", ip, port, local_port);
        wifi_spi_send_command(temp);

        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_spi_information.connect_state = WIFI_SPI_SERVER_OFF;
            break;
        }

        wifi_spi_clear_receive_buffer();                                       // ���WiFi���ջ�����
        if(wifi_spi_set_transfer_model(WIFI_SPI_COMMAND == mode ? "0" : "1"))  // ���ô���ģʽ
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();                                        // ���WiFi���ջ�����
        if(WIFI_SPI_SERIANET == mode)                                           // ͸��ģʽ��ֱ�ӿ���͸��
        {
            if(wifi_spi_entry_serianet())
            {
                return_state = 1;
                break;
            }
        }
        memcpy(wifi_spi_information.local_port, "       ", 7);
        memcpy(wifi_spi_information.local_port, local_port, strlen(local_port));
        wifi_spi_information.connect_state = WIFI_SPI_SERVER_ON;
        wifi_spi_information.connect_mode  = WIFI_SPI_UDP_CLIENT;
        wifi_spi_information.transfer_mode = mode;
    }while(0);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// �������     �Ͽ����� TCP Server ʹ�ñ��ӿڽ���Ͽ���������
// ����˵��     void
// ���ز���     uint8           0���ɹ�   1��ʧ��
// ʹ��ʾ��     wifi_spi_disconnect_link();
// ��ע��Ϣ     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_disconnect_link (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer();                                           // ���WiFi���ջ�����
    do
    {
        if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
        {
            wifi_spi_send_command("AT+CIPCLOSE=5\r\n");
        }
        else
        {
            wifi_spi_send_command("AT+CIPCLOSE\r\n");
        }

        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_spi_information.connect_state = WIFI_SPI_SERVER_OFF;
            break;
        }
    }while(0);
    wifi_spi_clear_receive_buffer(); // ���WiFi���ջ�����

    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFiģ�� �����ֽں���
// ����˵��     data            ��Ҫ���͵�����
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��     wifi_spi_send_byte(0xa5);
// ��ע��Ϣ     ��ģ����ΪTCP������ʱ���������ݺ���Ĭ�Ͻ����ݷ�������һ������ģ��Ŀͻ���
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_send_byte (uint8 data)
{
    char temp[64];
    uint8 temp_length;
    uint16 send_length;
    
    send_length = 1;
    if(wifi_spi_init_flag)
    {
        if(WIFI_SPI_SERVER_ON == wifi_spi_information.connect_state)
        {
            if(WIFI_SPI_COMMAND == wifi_spi_information.transfer_mode)
            {
                wifi_spi_clear_receive_buffer();                                   // ���WiFi���ջ�����
                temp_length = (uint8)sprintf(temp, "AT+CIPSEND=");

                if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
                {
                    temp_length += sprintf(&temp[temp_length], "0,");
                }
                
                temp_length += sprintf(&temp[temp_length], "%u\r\n", send_length);

                wifi_spi_send_command(temp);
                if(0 == wifi_spi_wait_ack("OK", WAIT_TIME_OUT))                    // �ȴ�ģ����Ӧ
                {
                    wifi_spi_clear_receive_buffer();                               // ���WiFi���ջ�����
                    wifi_spi_write_data(&data, send_length);
                    wifi_spi_wait_ack("bytes", 50);
                    wifi_spi_clear_receive_buffer();                               // ���WiFi���ջ�����
                    wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
                }
            
                wifi_spi_clear_receive_buffer();                                           // ���WiFi���ջ�����
            }
            else
            {
                send_length = (uint16)wifi_spi_write_data(&data, send_length);
            }
        }
    }
    
    return send_length;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFiģ�� ���ͻ���������
// ����˵��     buff            ��Ҫ���͵����ݵ�ַ
// ����˵��     len             ���ͳ���
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��     wifi_spi_send_buffer("123", 3);
// ��ע��Ϣ     ��ģ����ΪTCP������ʱ���������ݺ���Ĭ�Ͻ����ݷ�������һ������ģ��Ŀͻ���
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_send_buffer (const uint8 *buff, uint32 len)
{
    char temp[64];
    uint8 temp_length;
    uint16 send_length;
    
    if(wifi_spi_init_flag)
    {
        if(WIFI_SPI_SERVER_ON == wifi_spi_information.connect_state)
        {
            if(WIFI_SPI_COMMAND == wifi_spi_information.transfer_mode)
            {
                while(len)
                {
                    if((WIFI_SPI_WRITE_MAX * 2) < len) send_length = WIFI_SPI_WRITE_MAX * 2;
                    else
                    {
                        send_length = (uint16)len;
                    }
                    len -= send_length;

                    wifi_spi_clear_receive_buffer();                                   // ���WiFi���ջ�����
                    temp_length = (uint8)sprintf(temp, "AT+CIPSEND=");

                    if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
                    {
                        temp_length += sprintf(&temp[temp_length], "0,");
                    }
                    
                    temp_length += sprintf(&temp[temp_length], "%u\r\n", send_length);

                    wifi_spi_send_command(temp);
                    if(0 == wifi_spi_wait_ack("OK", WAIT_TIME_OUT))                    // �ȴ�ģ����Ӧ
                    {
                        wifi_spi_clear_receive_buffer();                               // ���WiFi���ջ�����
                        wifi_spi_write_data(buff, send_length);
                        wifi_spi_wait_ack("bytes", 50);
                        wifi_spi_clear_receive_buffer();                               // ���WiFi���ջ�����
                        wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
                    }
                    buff += send_length;
                }
                
                wifi_spi_clear_receive_buffer();                                           // ���WiFi���ջ�����
            }
            else
            {
                len = wifi_spi_write_data(buff, len);
            }
        }
    }
    
    return len;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFiģ�� ���ͻ���������(���Դ��ַ)
//  @param      *multi_buffer   ���Դ��ַ�Լ�ÿ��Դ��ַ��Ҫ���͵ĳ���
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��     
// ��ע��Ϣ     ��Ҫ���Ͷ������ʱ�����ô˺������Լ���Ľ���ͨѶʱ�䣬���������ܳ��Ȳ��ܳ���4092
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_send_buffer_multi (wifi_spi_send_multi_struct *multi_buffer)
{
    uint8 i;
    uint16 remain_length;
    
    if(wifi_spi_init_flag)
    {
        if(WIFI_SPI_SERVER_ON == wifi_spi_information.connect_state)
        {
            if(WIFI_SPI_COMMAND == wifi_spi_information.transfer_mode)
            {
                for(i = 0; i < WIFI_SPI_MAX_MULTI; i++)
                {
                    if(multi_buffer->source[i])    wifi_spi_send_buffer(multi_buffer->source[i], multi_buffer->length[i]);
                }
            }
            else
            {
                remain_length = (uint16)wifi_spi_write_data_multi(multi_buffer);
            }
        }
    }
    
    return remain_length;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFiģ�� �����ַ�������
// ����˵��     *str            ��Ҫ���͵�����
// ���ز���     uint32          ʣ��δ�������ݳ���
// ʹ��ʾ��     wifi_spi_send_string("123");
// ��ע��Ϣ     ��ģ����ΪTCP������ʱ���������ݺ���Ĭ�Ͻ����ݷ�������һ������ģ��Ŀͻ���
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_send_string (const char *str)
{
    char temp[64];
    uint8 temp_length;
    uint16 send_length;
    
    send_length = (uint16)strlen(str);
    if(wifi_spi_init_flag)
    {
        if(WIFI_SPI_SERVER_ON == wifi_spi_information.connect_state)
        {
            if(WIFI_SPI_COMMAND == wifi_spi_information.transfer_mode)
            {
                wifi_spi_clear_receive_buffer();                                   // ���WiFi���ջ�����
                temp_length = (uint8)sprintf(temp, "AT+CIPSEND=");

                if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
                {
                    temp_length += sprintf(&temp[temp_length], "0,");
                }
                
                temp_length += sprintf(&temp[temp_length], "%u\r\n", send_length);

                wifi_spi_send_command(temp);
                if(0 == wifi_spi_wait_ack("OK", WAIT_TIME_OUT))                    // �ȴ�ģ����Ӧ
                {
                    wifi_spi_clear_receive_buffer();                               // ���WiFi���ջ�����
                    wifi_spi_write_data((uint8 *)str, send_length);
                    wifi_spi_wait_ack("bytes", 50);
                    wifi_spi_clear_receive_buffer();                               // ���WiFi���ջ�����
                    wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
                }
            
                wifi_spi_clear_receive_buffer();                                           // ���WiFi���ջ�����
            }
            else
            {
                send_length = (uint16)wifi_spi_write_data((uint8 *)str, send_length);
            }
        }
    }
    
    return send_length;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     WiFi ģ�����ݽ��պ���
// ����˵��     buffer          �������ݵĴ�ŵ�ַ
// ����˵��     len             ���鳤�ȣ���ֱ����д����ʹ��sizeof���
// ���ز���     uint32          ����ʵ�ʽ��յ������ݳ���
// ʹ��ʾ��     uint8 test_buffer[256]; wifi_spi_read_buffer(&test_buffer[0], sizeof(test_buffer));
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_read_buffer (uint8 *buffer, uint32 len)
{
    fifo_read_buffer(&wifi_spi_fifo, buffer, &len, FIFO_READ_AND_CLEAN);
    return len;
}

//--------------------------------------------------------------------------------------------------
// �������     wifi spi handshake�жϻص�����
// ����˵��     void
// ���ز���     void          
// ��ע��Ϣ     �ڲ�����
//--------------------------------------------------------------------------------------------------
void wifi_spi_callback (void)
{
    if(exti_flag_get(WIFI_SPI_INT_PIN))
    {
        exti_flag_clear(WIFI_SPI_INT_PIN);  // ����жϱ�־λ
        
        wifi_spi_check_state_read_buffer();
        wifi_spi_ack_flag = 1;              // ACK��־λ��1
    }
}


//-------------------------------------------------------------------------------------------------------------------
// �������     WiFi ģ���ʼ��
// ����˵��     *wifi_ssid      Ŀ�����ӵ� WiFi ������ �ַ�����ʽ
// ����˵��     *pass_word      Ŀ�����ӵ� WiFi ������ �ַ�����ʽ
// ����˵��     wifi_mode       ģ��Ĺ���ģʽ ���� zf_device_wireless_spi.h �� wifi_spi_mode_enum ö��
// ���ز���     uint8           ģ���ʼ��״̬ 0-�ɹ� 1-����
// ʹ��ʾ��     wifi_spi_init("SEEKFREE_2.4G", "SEEKFREEV2", WIFI_UART_STATION);
// ��ע��Ϣ     ��ʼ�����������ô������ã�֮����ģ����л�����������
//              �����������Ϣ������ zf_device_wireless_spi.h �ļ����޸�
//-------------------------------------------------------------------------------------------------------------------
uint8 wifi_spi_init (char *wifi_ssid, char *pass_word, wifi_spi_mode_enum wifi_mode)
{
    uint8 return_state = 0;
    uint32 temp_isr;
    
    spi_init(WIFI_SPI_INDEX, SPI_MODE0, WIFI_SPI_SPEED, WIFI_SPI_SCK_PIN, WIFI_SPI_MOSI_PIN, WIFI_SPI_MISO_PIN, SPI_CS_NULL);//Ӳ��SPI��ʼ��
    set_wireless_type(WIFI_SPI, wifi_spi_callback);
    fifo_init(&wifi_spi_fifo, FIFO_DATA_8BIT, wifi_spi_buffer, WIFI_SPI_BUFFER_SIZE);
    
    gpio_init(WIFI_SPI_CS_PIN,  GPO, 1, GPO_PUSH_PULL);
    gpio_init(WIFI_SPI_RST_PIN, GPO, 1, GPO_PUSH_PULL);

    temp_isr = interrupt_global_disable();
    exti_init(WIFI_SPI_INT_PIN, EXTI_TRIGGER_RISING);
    interrupt_set_priority(GPIO1_Combined_16_31_IRQn, 15);
    
    gpio_set_level(WIFI_SPI_RST_PIN, 0);
    system_delay_ms(50);
    gpio_set_level(WIFI_SPI_RST_PIN, 1);
    system_delay_ms(1000);
    
    exti_flag_clear(WIFI_SPI_INT_PIN);
    NVIC_ClearPendingIRQ(GPIO1_Combined_16_31_IRQn);
    interrupt_global_enable(temp_isr);

    do
    {
        if(wifi_spi_echo_set("0"))                                             // �ر�ģ���д
        {
            zf_log(0, "exit echo failed");
            return_state = 1;
            break;
        }
        
        if(wifi_spi_auto_connect_wifi("0"))                                    // �ر��Զ�����
        {
            zf_log(0, "close auto connect failed");
            return_state = 1;
            break;
        }

        if(wifi_spi_set_model(wifi_mode))                                      // ��������ģʽ
        {
            zf_log(0, "set run mode failed");
            return_state = 1;
            break;
        }
        
        if(wifi_spi_close_sleep_model())                                        // �ر�˯��ģʽ
        {
            zf_log(0, "set sleep mode failed");
            return_state = 1;
            break;
        }

        if(wifi_spi_set_wifi((char *)wifi_ssid, (char *)pass_word))            // ���� wifi ���߿����ȵ�
        {
            zf_log(0, "wifi set failed");
            return_state = 1;
            break;
        }

        if(wifi_spi_get_information())                                         // ģ�����������ȡ
        {
            zf_log(0, "get module information failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "seekfree wifi spi init succeed");
#if WIFI_SPI_AUTO_CONNECT == 1
        if(wifi_spi_connect_tcp_servers(WIFI_SPI_TARGET_IP, WIFI_SPI_TARGET_PORT, WIFI_SPI_SERIANET))                       // ����TCP������
        {
            zf_log(0, "connect TCP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "connect TCP client succeed");
#endif
#if WIFI_SPI_AUTO_CONNECT == 2
        if(wifi_spi_connect_udp_client(WIFI_SPI_TARGET_IP, WIFI_SPI_TARGET_PORT, WIFI_SPI_LOCAL_PORT, WIFI_SPI_SERIANET))  // ����UDP����
        {
            zf_log(0, "connect UDP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "connect UDP server succeed");
#endif
        // ģ���ʼ���ɹ�
        wifi_spi_init_flag = 1;
    }while(0);
    
    return return_state;
}
