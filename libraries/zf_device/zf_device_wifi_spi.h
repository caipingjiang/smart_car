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

#ifndef _zf_device_wifi_spi_h
#define _zf_device_wifi_spi_h

#include "zf_common_typedef.h"

#define WIFI_SPI_INDEX              (SPI_1)                     // 定义使用的SPI号
#define WIFI_SPI_SPEED              (20 * 1000 * 1000)          // 硬件 SPI 速率
#define WIFI_SPI_SCK_PIN            (SPI1_SCK_D12)              // 定义SPI_SCK引脚
#define WIFI_SPI_MOSI_PIN           (SPI1_MOSI_D14)             // 定义SPI_MOSI引脚
#define WIFI_SPI_MISO_PIN           (SPI1_MISO_D15)             // 定义SPI_MISO引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#define WIFI_SPI_CS_PIN             (D13)                       // 定义SPI_CS引脚 采用软件CS引脚
#define WIFI_SPI_INT_PIN            (B17)                       // 定义中断引脚
#define WIFI_SPI_RST_PIN            (B16)                       // 定义复位引脚
                                
                                
#define WIFI_SPI_BUFFER_SIZE        (1024)                      // 定义SPI接收的缓冲区大小

#define WIFI_SPI_AUTO_CONNECT       (0)                         // 定义是否初始化时建立TCP或者UDP连接    0-不连接  1-自动连接TCP服务器并进入透传模式  2-自动连接UDP服务器并进入透传模式
    
#if     (WIFI_SPI_AUTO_CONNECT > 2)    
#error "WIFI_SPI_AUTO_CONNECT 的值只能为 [0,1,2]" 
#else   
#define WIFI_SPI_TARGET_IP          "192.168.137.1"             // 连接目标的 IP
#define WIFI_SPI_TARGET_PORT        "8080"                      // 连接目标的端口
#define WIFI_SPI_LOCAL_PORT         "8080"                      // 本机端口
#endif

#define WIFI_SPI_MAX_MULTI          (17)                        // 多地址发送，最大8个地址

typedef enum    
{   
    BUFFER_IDLE,                                                // 模块的缓冲区是空闲的
    BUFFER_READ,                                                // 模块的缓冲区有数据需要读取
    BUFFER_WRITE,                                               // 模块的缓冲区是可写的
}wifi_spi_buffer_state_enum;            

typedef enum
{       
    TRANSMIT_IDLE,                                              // 当前没有传输
    TRANSMIT_WRITE_REQUEST,                                     // 给模块发送了一个传输请求
    TRANSMIT_READ_STATE,                                        // 读取模块状态
    TRANSMIT_READ,                                              // 正在读取模块内部数据
    TRANSMIT_WRITE,                                             // 正在往模块写入数据
}wifi_spi_transmit_state_enum;

typedef enum    
{   
    WIFI_SPI_STATION,                                           // 设备模式
    WIFI_SPI_SOFTAP,                                            // AP模式
}wifi_spi_mode_enum;        
        
typedef enum        
{       
    WIFI_SPI_COMMAND,                                           // 使用命令的方式发送数据
    WIFI_SPI_SERIANET,                                          // 使用透传的方式发送数据
}wifi_spi_transfer_mode_enum;       
        
typedef enum        
{       
    WIFI_SPI_TCP_CLIENT,                                        // 模块连接TCP服务器
    WIFI_SPI_TCP_SERVER,                                        // 模块作为TCP服务器
    WIFI_SPI_UDP_CLIENT,                                        // 模块启用UDP连接
}wifi_spi_connect_mode_enum;        
        
typedef enum        
{       
    WIFI_SPI_SERVER_OFF,                                        // 模块未连接服务器
    WIFI_SPI_SERVER_ON,                                         // 模块已经连接服务器
}wifi_spi_connect_state_enum;       
        
typedef struct
{
    uint8 reserve;
    uint8 cmd;
    uint8 addr;
    uint8 dummy;
    uint8 magic;
    uint8 sequence;
    uint16 length;
}wifi_spi_buffer_struct;

typedef struct      
{       
    uint8                           version[12];                // 固件版本         字符串形式
    uint8                           mac[20];                    // 本机 MAC 地址    字符串形式
    uint8                           local_ip[17];               // 本机 IP 地址     字符串形式
    uint8                           local_port[10];             // 本机端口号       字符串形式
    uint8                           remote_ip[5][17];           // 远端 IP 地址     字符串形式
    wifi_spi_mode_enum              mode;                       // WIFI 模式
    wifi_spi_transfer_mode_enum     transfer_mode;              // 当前传输模式
    wifi_spi_connect_mode_enum      connect_mode;               // 网络连接模式
    wifi_spi_connect_state_enum     connect_state;              // 服务器连接情况
}wifi_spi_information_struct;

typedef struct
{
    uint8  *source[WIFI_SPI_MAX_MULTI];
    uint16 length[WIFI_SPI_MAX_MULTI];
}wifi_spi_send_multi_struct;

extern wifi_spi_information_struct wifi_spi_information;


uint8   wifi_spi_disconnected_wifi         (void);                                                                      // 断开 WIFI 连接
uint8   wifi_spi_entry_serianet            (void);                                                                      // 打开透传模式
uint8   wifi_spi_exit_serianet             (void);                                                                      // 关闭透传模式
    
uint8   wifi_spi_connect_tcp_servers       (char *ip, char *port, wifi_spi_transfer_mode_enum mode);                    // 连接 TCP Server
uint8   wifi_spi_connect_udp_client        (char *ip, char *port, char *local_port, wifi_spi_transfer_mode_enum mode);  // 建立 UDP 传输
uint8   wifi_spi_disconnect_link           (void);                                                                      // 断开连接 TCP Server 使用本接口将会断开所有连接

uint32  wifi_spi_send_byte                 (uint8 data);                                                                // WIFI 模块发送字节函数
uint32  wifi_spi_send_buffer               (const uint8 *buff, uint32 length);                                          // WIFI 模块发送缓冲区函数
uint32  wifi_spi_send_buffer_multi         (wifi_spi_send_multi_struct *multi_buffer);                                  // WIFI 模块发送多缓冲区函数
uint32  wifi_spi_send_string               (const char *str);                                                           // WIFI 模块发送字符串函数

uint32  wifi_spi_read_buffer               (uint8 *buff, uint32 len);                                                   // WIFI 模块数据接收函数
    
uint8   wifi_spi_init                      (char *wifi_ssid, char *pass_word, wifi_spi_mode_enum wifi_mode);            // WIFI 模块初始化函数

#endif

