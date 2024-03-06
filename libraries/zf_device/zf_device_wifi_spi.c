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
* 文件名称          zf_device_wifi_spi
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
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   RST                 查看 zf_device_wifi_spi.h 中 WIFI_SPI_RST_PIN 宏定义
*                   INT                 查看 zf_device_wifi_spi.h 中 WIFI_SPI_INT_PIN 宏定义
*                   CS                  查看 zf_device_wifi_spi.h 中 WIFI_SPI_CS_PIN 宏定义
*                   MISO                查看 zf_device_wifi_spi.h 中 WIFI_SPI_MISO_PIN 宏定义
*                   SCK                 查看 zf_device_wifi_spi.h 中 WIFI_SPI_SCK_PIN 宏定义
*                   MOSI                查看 zf_device_wifi_spi.h 中 WIFI_SPI_MOSI_PIN 宏定义
*                   5V                  5V 电源
*                   GND                 电源地
*                   其余引脚悬空
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

#define     WAIT_TIME_OUT               (10000)             // 单指令等待时间  单位：ms

#define     WIFI_SPI_WRITE_MAX          4092                // 定义一次SPI通讯最大发送的数据长度
    
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
static      uint8 wifi_spi_buffer[WIFI_SPI_BUFFER_SIZE];    // 数据存放数组

vuint8      wifi_spi_ack_flag = 0;                          // 0：模块未应答 1：模块已应答
uint8       wifi_spi_init_flag;                             // 0：模块未初始化成功或者未连接 1：模块已连接并成功初始化
vuint8      wifi_spi_packet_num;                            // 发送的数据包ID
vuint32     wifi_spi_send_remain_length;                    // 剩余的发送长度
                        
uint8       wifi_spi_receive_buffer[WIFI_SPI_WRITE_MAX];

wifi_spi_information_struct wifi_spi_information;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      请求写入数据到模块
//  @param      length      需要写入的长度
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
//  @brief      读取模块状态
//  @param      *length     需要读取或者写入的长度
//  @return     WIFI_SPI_BUFFER_STATE_enum  模块状态
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
//  @brief      数据发送完成
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
//  @brief      数据接收完成
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
//  @brief      发送数据到模块
//  @param      *buff        需要写入数据的首地址
//  @param      length       需要写入数据的长度
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
//  @brief      发送数据到模块（多个源地址）
//  @param      *multi_buffer   多个源地址以及每个源地址需要发送的长度
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
//  @brief      接收模块发送的数据
//  @param      *buff        接收数组的缓冲区首地址
//  @param      length       需要接收的长度
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
//  @brief      发送命令到模块
//  @param      *str        命令字符串首地址
//  @return     void       		
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
static void wifi_spi_send_command(const char *str)
{
    uint8  state = 0;
    uint16 send_length;
    uint16 wait_time = 0;
    
    // 请求发送数据
    send_length = (uint16)strlen(str);

    // 等待传输进入空闲
    while(TRANSMIT_IDLE != wifi_transmit_state);

    // 如果没有进入发送状态则重新请求发送数据
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
                wifi_spi_init_flag = 0; // 模块已断开
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
    
    if(0 == state) // 通讯未超时
    {
        wifi_spi_send_remain_length = send_length;
        // 发送消息
        wifi_spi_send_data((const uint8 *)str, send_length);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      检查模块状态并读取模块发送的数据
//  @param      void        
//  @return     void					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
void wifi_spi_check_state_read_buffer(void)
{
    uint16 wifi_spi_receive_length; // 本次接收到的数据数量
    
    // 查询WIFI模块的状态
    wifi_buffer_state = wifi_spi_read_state(&wifi_spi_receive_length);
    
    // 如果需要读取WIFI模块数据，则保存需要读取的长度
    if(BUFFER_READ == wifi_buffer_state)
    {
        wifi_spi_receive_data((uint8 *)wifi_spi_receive_buffer, wifi_spi_receive_length);
        fifo_write_buffer(&wifi_spi_fifo, wifi_spi_receive_buffer, wifi_spi_receive_length);  // 存入 FIFO
    }
    else if(BUFFER_IDLE == wifi_buffer_state)
    {
        // 如果模块内部缓冲区状态为空闲，则传输状态也设置为空闲
        wifi_transmit_state = TRANSMIT_IDLE;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      发送数据到模块
//  @param      *buff       需要发送的数据首地址     
//  @param      length      需要发送的长度
//  @return     uint32      剩余未发送长度					
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_write_data(const uint8 *buff, uint32 length)
{
    uint16 send_length;
    uint32 wait_time;
    
    // 记录需要发送的长度
    wifi_spi_send_remain_length = length;

    while(wifi_spi_send_remain_length)
    {
        send_length = (uint16)func_limit_ab(wifi_spi_send_remain_length, 1, WIFI_SPI_WRITE_MAX);
        
        // 请求发送数据
        wifi_spi_ack_flag = 0;
        wifi_spi_write_request(send_length);
        
        // 最长等待5秒
        wait_time = 5000;
        while(!wifi_spi_ack_flag)
        {
            wait_time--;
            if(0 == wait_time)  break;
            system_delay_ms(1);
        }
        
        if(BUFFER_WRITE == wifi_buffer_state)
        {
            // 发送消息
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
//  @brief      发送数据到模块(多个源地址)
//  @param      *multi_buffer   多个源地址以及每个源地址需要发送的长度
//  @return     uint32          剩余未发送长度					
//  Sample usage:		        发送数据总长度不能超过4092个
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_write_data_multi(wifi_spi_send_multi_struct *multi_buffer)
{
    uint16 send_length;
    uint32 wait_time;
    
    // 记录需要发送的长度
    send_length = multi_buffer->length[0] + multi_buffer->length[1] + multi_buffer->length[2] + multi_buffer->length[3] + multi_buffer->length[4] + multi_buffer->length[5] + multi_buffer->length[6] + multi_buffer->length[7];
    
    if(WIFI_SPI_WRITE_MAX >= send_length)
    {
        // 请求发送数据
        wifi_spi_ack_flag = 0;
        wifi_spi_write_request(send_length);
        
        // 最长等待5秒
        wait_time = 5000;
        while(!wifi_spi_ack_flag)
        {
            wait_time--;
            if(0 == wait_time)  break;
            system_delay_ms(1);
        }
        
        if(BUFFER_WRITE == wifi_buffer_state)
        {
            // 发送消息
            wifi_spi_send_data_multi(multi_buffer);
            send_length = 0;
            wifi_buffer_state = BUFFER_IDLE;
        }
    }

    return send_length;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     等待模块响应
// 参数说明     *wait_buffer    等待的响应的字符串
// 参数说明     timeout         超时时间
// 返回参数     uint8           0：模块响应指定数据   1：模块未响应指定数据或超时
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_wait_ack (char *wait_buffer, uint32 timeout)
{
    uint8 return_state = 1;
    char receiver_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint32 receiver_len = 8;
    
    do
    {
        system_delay_ms(1);
        // 判断接收缓冲区内是否有需要响应的指定数据 如果有 则跳出循环并且返回0
        receiver_len = 8;
        fifo_read_tail_buffer(&wifi_spi_fifo, (uint8 *)receiver_buffer, &receiver_len, FIFO_READ_ONLY);

        if(strstr(receiver_buffer, wait_buffer))
        {
            return_state = 0;
            break;
        }
        else if(strstr(receiver_buffer, "ERROR") || strstr(receiver_buffer, "busy"))
        {
        // 如果接收到报错或者模块忙 则跳出循环并且返回1
            return_state = 1;
            break;
        }
    }while(timeout --);
    
    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     清除WiFi接收缓冲区内容
// 参数说明     void
// 返回参数     void
// 使用示例     wifi_spi_clear_receive_buffer();
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static void wifi_spi_clear_receive_buffer (void)
{
    // 清空WiFi接收缓冲区
    fifo_clear(&wifi_spi_fifo);
}

//--------------------------------------------------------------------------------------------------
// 函数简介     模块数据解析
// 参数说明     *target_buffer  目标存放地址指针 字符串数组
// 参数说明     *origin_buffer  数据来源地址指针 字符串数组
// 参数说明     start_char      起始提取字节 例如从 "1234" 中从 '2' 开始提取 就应该填入 '2'
// 参数说明     end_char        结束提取字节 例如从 "1234" 中在 '4' 结束提取 就应该填入 '\0'(0x00 空字符 一般是字符串结尾)
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_data_parse(wifi_spi_information.mac, wifi_spi_receive_buffer, '"', '"'); // 调用获取本机mac地址后，调用此函数提取mac地址
// 备注信息     内部调用
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
// 函数简介     查看模块版本信息
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_get_version();
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_version (void)
{
    char *location1;
    uint8 return_state = 0;
    uint8 receiver_buffer[256];
    uint32 receiver_len = 256;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
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
    wifi_spi_clear_receive_buffer();                                           // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     模块回显设置
// 参数说明     model           0:关闭模块的回写功能  其他：开启模块回写
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_echo_set("1");//开启模块回写功能
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_echo_set (char *model)
{
    uint8 return_state = 0;
    
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    
    if('1' == *model)
    {
        wifi_spi_send_command("ATE1\r\n");
    }
    else
    {
        wifi_spi_send_command("ATE0\r\n");
    }

    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     查询模块自身 的 MAC 地址
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     if(wifi_spi_get_mac()){}
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_mac (void)
{
    uint8 return_state = 0;
    uint8 receiver_buffer[64];
    uint32 receiver_len = 64;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
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
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区


    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     查询模块或者目标WIFI 的 IP 地址(取决于模块当前的工作模式)
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     if(wifi_spi_get_ip()){}
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_ip (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
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
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     查询模块的相关信息
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     if(wifi_spi_get_information()){}
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_get_information (void)
{
    uint8 return_state = 0;
    do
    {
        // 获取模块版本号
        if(wifi_spi_get_version())
        {
            return_state = 1;
            break;
        }
        // 获取模块IP地址
        if(wifi_spi_get_ip())
        {
            return_state = 1;
            break;
        }
        // 获取模块MAC信息
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
// 函数简介     连接 WiFi
// 参数说明     wifi_ssid       WiFi名称
// 参数说明     pass_word       WiFi密码
// 参数说明     model           0:查询WiFi连接情况   其他：连接WiFi
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_get_or_connect_wifi("WiFi_name", "Pass_word", 1);
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_set_wifi (char *wifi_ssid, char *pass_word)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
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
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     上电是否自动连接WiFi
// 参数说明     model           0:上电不自动连接wifi   其他：上电自动连接wifi
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_auto_connect_wifi(0); //上电不自动连接wifi
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_auto_connect_wifi (char *model)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    sprintf(temp, "AT+CWAUTOCONN=%s\r\n", model);
    wifi_spi_send_command(temp);
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     设置连接模式
// 参数说明     model           0: 单连接模式     1：多连接模式
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_set_connect_model("1");
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_set_connect_model (char *model)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    sprintf(temp, "AT+CIPMUX=%s\r\n", model);
    wifi_spi_send_command(temp);
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     设置传输模式
// 参数说明     model           – 0: 普通传输模式     IP断开后不重新连接
//                              – 1: Wi-Fi 透传接收模式，仅支持 TCP 单连接、UDP 固定通信对端、SSL 单连接的情况     IP断开后会不断尝试重新连接
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_set_transfer_model("1");
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
static uint8 wifi_spi_set_transfer_model (char *model)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    sprintf(temp, "AT+CIPMODE=%s\r\n", model);
    wifi_spi_send_command(temp);
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     设置模块模式 (Station/SoftAP/Station+SoftAP)
// 参数说明     state           0:无 Wi-Fi 模式，并且关闭 Wi-Fi RF----1: Station 模式----2: SoftAP 模式----3: SoftAP+Station 模式
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_set_model("1");
// 备注信息     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_set_model (wifi_spi_mode_enum  mode)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    if(WIFI_SPI_SOFTAP == mode)
    {
        wifi_spi_send_command("AT+CWMODE=2\r\n");
    }
    else
    {
        wifi_spi_send_command("AT+CWMODE=1\r\n");
    }
    // 设置模块工作模式
    wifi_spi_information.mode = mode;
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     关闭睡眠模式
// 参数说明     mode            
// 返回参数     uint8           0：成功   1：失败
// 使用示例 
// 备注信息     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_close_sleep_model (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    wifi_spi_send_command("AT+SLEEP=0\r\n");
    // 设置模块工作模式
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     断开与wifi的连接
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_disconnected_wifi();
// 备注信息     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_disconnected_wifi (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    wifi_spi_send_command("AT+CWQAP\r\n");
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     进入打开透传模式
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_entry_serianet();
// 备注信息     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_entry_serianet (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区
    wifi_spi_send_command("AT+CIPSEND\r\n");
    return_state = wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     退出透传模式
// 参数说明     model           0:关闭透传模式   其他：开启透传模式
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_exit_serianet(1);
// 备注信息     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_exit_serianet (void)
{
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    system_delay_ms(20);
    wifi_spi_send_command("+++");
    system_delay_ms(1000);

    return 0;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     建立TCP连接
// 参数说明     ip              远端 IPv4 地址、IPv6 地址，或域名
// 参数说明     port            远端端口值
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_connect_tcp_servers("192.168.101.110", "8080");
// 备注信息     如果总是连接不上电脑的TCP服务器 可以尝试使用网线连接电脑
//              如果是使用WiFi连接 可能会导致模块连接TCP服务器等待较长时间
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_connect_tcp_servers (char *ip, char *port, wifi_spi_transfer_mode_enum mode)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer();        // 清空WiFi接收缓冲区
    do
    {
        if(wifi_spi_set_connect_model("0"))
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();    // 清空WiFi接收缓冲区
        sprintf(temp, "AT+CIPSTARTEX=\"TCP\",\"%s\",%s\r\n", ip, port);
        wifi_spi_send_command(temp);

        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_spi_information.connect_state = WIFI_SPI_SERVER_OFF;
            break;
        }

        wifi_spi_clear_receive_buffer();    // 清空WiFi接收缓冲区

        // 设置传输模式
        if(wifi_spi_set_transfer_model(WIFI_SPI_COMMAND == mode ? "0" : "1"))
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();    // 清空WiFi接收缓冲区
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

        wifi_spi_clear_receive_buffer();    // 清空WiFi接收缓冲区
        if(WIFI_SPI_SERIANET == mode)       // 透传模式下直接开启透传
        {
            if(wifi_spi_entry_serianet())
            {
                return_state = 1;
                break;
            }
        }

    }while(0);
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     建立UDP连接
// 参数说明     *ip             远端 IPv4 地址、IPv6 地址 或域名 字符串形式
// 参数说明     *port           远端端口值 字符串形式
// 参数说明     *local_port     远端 IPv4 地址、IPv6 地址 或域名 字符串形式
// 参数说明     mode            模块数据通信模式
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_connect_udp_client("192.168.101.110", "8080", "8080", WIFI_SPI_COMMAND);
// 备注信息     自动分配ID
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_connect_udp_client (char *ip, char *port, char *local_port, wifi_spi_transfer_mode_enum mode)
{
    char temp[64];
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer();                                            // 清空WiFi接收缓冲区
    do
    {
        if(wifi_spi_set_connect_model("0"))
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();                                        // 清空WiFi接收缓冲区
        
        sprintf(temp, "AT+CIPSTARTEX=\"UDP\",\"%s\",%s,%s\r\n", ip, port, local_port);
        wifi_spi_send_command(temp);

        if(wifi_spi_wait_ack("OK", WAIT_TIME_OUT))
        {
            return_state = 1;
            wifi_spi_information.connect_state = WIFI_SPI_SERVER_OFF;
            break;
        }

        wifi_spi_clear_receive_buffer();                                       // 清空WiFi接收缓冲区
        if(wifi_spi_set_transfer_model(WIFI_SPI_COMMAND == mode ? "0" : "1"))  // 设置传输模式
        {
            return_state = 1;
            break;
        }

        wifi_spi_clear_receive_buffer();                                        // 清空WiFi接收缓冲区
        if(WIFI_SPI_SERIANET == mode)                                           // 透传模式下直接开启透传
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
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     断开连接 TCP Server 使用本接口将会断开所有连接
// 参数说明     void
// 返回参数     uint8           0：成功   1：失败
// 使用示例     wifi_spi_disconnect_link();
// 备注信息     
//--------------------------------------------------------------------------------------------------
uint8 wifi_spi_disconnect_link (void)
{
    uint8 return_state = 0;

    wifi_spi_clear_receive_buffer();                                           // 清空WiFi接收缓冲区
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
    wifi_spi_clear_receive_buffer(); // 清空WiFi接收缓冲区

    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     WiFi模块 发送字节函数
// 参数说明     data            需要发送的数据
// 返回参数     uint32          剩余未发送数据长度
// 使用示例     wifi_spi_send_byte(0xa5);
// 备注信息     当模块作为TCP服务器时，发送数据函数默认将数据发送至第一个连接模块的客户端
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
                wifi_spi_clear_receive_buffer();                                   // 清空WiFi接收缓冲区
                temp_length = (uint8)sprintf(temp, "AT+CIPSEND=");

                if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
                {
                    temp_length += sprintf(&temp[temp_length], "0,");
                }
                
                temp_length += sprintf(&temp[temp_length], "%u\r\n", send_length);

                wifi_spi_send_command(temp);
                if(0 == wifi_spi_wait_ack("OK", WAIT_TIME_OUT))                    // 等待模块响应
                {
                    wifi_spi_clear_receive_buffer();                               // 清空WiFi接收缓冲区
                    wifi_spi_write_data(&data, send_length);
                    wifi_spi_wait_ack("bytes", 50);
                    wifi_spi_clear_receive_buffer();                               // 清空WiFi接收缓冲区
                    wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
                }
            
                wifi_spi_clear_receive_buffer();                                           // 清空WiFi接收缓冲区
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
// 函数简介     WiFi模块 发送缓冲区函数
// 参数说明     buff            需要发送的数据地址
// 参数说明     len             发送长度
// 返回参数     uint32          剩余未发送数据长度
// 使用示例     wifi_spi_send_buffer("123", 3);
// 备注信息     当模块作为TCP服务器时，发送数据函数默认将数据发送至第一个连接模块的客户端
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

                    wifi_spi_clear_receive_buffer();                                   // 清空WiFi接收缓冲区
                    temp_length = (uint8)sprintf(temp, "AT+CIPSEND=");

                    if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
                    {
                        temp_length += sprintf(&temp[temp_length], "0,");
                    }
                    
                    temp_length += sprintf(&temp[temp_length], "%u\r\n", send_length);

                    wifi_spi_send_command(temp);
                    if(0 == wifi_spi_wait_ack("OK", WAIT_TIME_OUT))                    // 等待模块响应
                    {
                        wifi_spi_clear_receive_buffer();                               // 清空WiFi接收缓冲区
                        wifi_spi_write_data(buff, send_length);
                        wifi_spi_wait_ack("bytes", 50);
                        wifi_spi_clear_receive_buffer();                               // 清空WiFi接收缓冲区
                        wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
                    }
                    buff += send_length;
                }
                
                wifi_spi_clear_receive_buffer();                                           // 清空WiFi接收缓冲区
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
// 函数简介     WiFi模块 发送缓冲区函数(多个源地址)
//  @param      *multi_buffer   多个源地址以及每个源地址需要发送的长度
// 返回参数     uint32          剩余未发送数据长度
// 使用示例     
// 备注信息     需要发送多个数组时，采用此函数可以极大的降低通讯时间，发送数据总长度不能超过4092
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
// 函数简介     WiFi模块 发送字符串函数
// 参数说明     *str            需要发送的数据
// 返回参数     uint32          剩余未发送数据长度
// 使用示例     wifi_spi_send_string("123");
// 备注信息     当模块作为TCP服务器时，发送数据函数默认将数据发送至第一个连接模块的客户端
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
                wifi_spi_clear_receive_buffer();                                   // 清空WiFi接收缓冲区
                temp_length = (uint8)sprintf(temp, "AT+CIPSEND=");

                if(WIFI_SPI_TCP_SERVER == wifi_spi_information.connect_mode)
                {
                    temp_length += sprintf(&temp[temp_length], "0,");
                }
                
                temp_length += sprintf(&temp[temp_length], "%u\r\n", send_length);

                wifi_spi_send_command(temp);
                if(0 == wifi_spi_wait_ack("OK", WAIT_TIME_OUT))                    // 等待模块响应
                {
                    wifi_spi_clear_receive_buffer();                               // 清空WiFi接收缓冲区
                    wifi_spi_write_data((uint8 *)str, send_length);
                    wifi_spi_wait_ack("bytes", 50);
                    wifi_spi_clear_receive_buffer();                               // 清空WiFi接收缓冲区
                    wifi_spi_wait_ack("OK", WAIT_TIME_OUT);
                }
            
                wifi_spi_clear_receive_buffer();                                           // 清空WiFi接收缓冲区
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
// 函数简介     WiFi 模块数据接收函数
// 参数说明     buffer          接收数据的存放地址
// 参数说明     len             数组长度，可直接填写或者使用sizeof求得
// 返回参数     uint32          返回实际接收到的数据长度
// 使用示例     uint8 test_buffer[256]; wifi_spi_read_buffer(&test_buffer[0], sizeof(test_buffer));
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint32 wifi_spi_read_buffer (uint8 *buffer, uint32 len)
{
    fifo_read_buffer(&wifi_spi_fifo, buffer, &len, FIFO_READ_AND_CLEAN);
    return len;
}

//--------------------------------------------------------------------------------------------------
// 函数简介     wifi spi handshake中断回调函数
// 参数说明     void
// 返回参数     void          
// 备注信息     内部调用
//--------------------------------------------------------------------------------------------------
void wifi_spi_callback (void)
{
    if(exti_flag_get(WIFI_SPI_INT_PIN))
    {
        exti_flag_clear(WIFI_SPI_INT_PIN);  // 清除中断标志位
        
        wifi_spi_check_state_read_buffer();
        wifi_spi_ack_flag = 1;              // ACK标志位置1
    }
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     WiFi 模块初始化
// 参数说明     *wifi_ssid      目标连接的 WiFi 的名称 字符串形式
// 参数说明     *pass_word      目标连接的 WiFi 的密码 字符串形式
// 参数说明     wifi_mode       模块的工作模式 参照 zf_device_wireless_spi.h 中 wifi_spi_mode_enum 枚举
// 返回参数     uint8           模块初始化状态 0-成功 1-错误
// 使用示例     wifi_spi_init("SEEKFREE_2.4G", "SEEKFREEV2", WIFI_UART_STATION);
// 备注信息     初始化会首先设置串口配置，之后会对模块进行基本参数配置
//              具体的配置信息可以在 zf_device_wireless_spi.h 文件中修改
//-------------------------------------------------------------------------------------------------------------------
uint8 wifi_spi_init (char *wifi_ssid, char *pass_word, wifi_spi_mode_enum wifi_mode)
{
    uint8 return_state = 0;
    uint32 temp_isr;
    
    spi_init(WIFI_SPI_INDEX, SPI_MODE0, WIFI_SPI_SPEED, WIFI_SPI_SCK_PIN, WIFI_SPI_MOSI_PIN, WIFI_SPI_MISO_PIN, SPI_CS_NULL);//硬件SPI初始化
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
        if(wifi_spi_echo_set("0"))                                             // 关闭模块回写
        {
            zf_log(0, "exit echo failed");
            return_state = 1;
            break;
        }
        
        if(wifi_spi_auto_connect_wifi("0"))                                    // 关闭自动连接
        {
            zf_log(0, "close auto connect failed");
            return_state = 1;
            break;
        }

        if(wifi_spi_set_model(wifi_mode))                                      // 设置运行模式
        {
            zf_log(0, "set run mode failed");
            return_state = 1;
            break;
        }
        
        if(wifi_spi_close_sleep_model())                                        // 关闭睡眠模式
        {
            zf_log(0, "set sleep mode failed");
            return_state = 1;
            break;
        }

        if(wifi_spi_set_wifi((char *)wifi_ssid, (char *)pass_word))            // 连接 wifi 或者开启热点
        {
            zf_log(0, "wifi set failed");
            return_state = 1;
            break;
        }

        if(wifi_spi_get_information())                                         // 模块基本参数获取
        {
            zf_log(0, "get module information failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "seekfree wifi spi init succeed");
#if WIFI_SPI_AUTO_CONNECT == 1
        if(wifi_spi_connect_tcp_servers(WIFI_SPI_TARGET_IP, WIFI_SPI_TARGET_PORT, WIFI_SPI_SERIANET))                       // 连接TCP服务器
        {
            zf_log(0, "connect TCP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "connect TCP client succeed");
#endif
#if WIFI_SPI_AUTO_CONNECT == 2
        if(wifi_spi_connect_udp_client(WIFI_SPI_TARGET_IP, WIFI_SPI_TARGET_PORT, WIFI_SPI_LOCAL_PORT, WIFI_SPI_SERIANET))  // 建立UDP连接
        {
            zf_log(0, "connect UDP server failed");
            return_state = 1;
            break;
        }
        // zf_log(0, "connect UDP server succeed");
#endif
        // 模块初始化成功
        wifi_spi_init_flag = 1;
    }while(0);
    
    return return_state;
}
