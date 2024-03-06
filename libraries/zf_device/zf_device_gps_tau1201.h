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
* 文件名称          zf_device_gps_tau1201
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
*                   RX                  查看 zf_device_gps_tau1201.h 中 GPS_TAU1201_RX 宏定义
*                   TX                  查看 zf_device_gps_tau1201.h 中 GPS_TAU1201_TX 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_gps_tau1201_h_
#define _zf_device_gps_tau1201_h_

#include "zf_common_typedef.h"

//--------------------------------------------------------------------------------------------------
//引脚配置
//--------------------------------------------------------------------------------------------------
#define GPS_TAU1201_UART    (UART_4)
#define GPS_TAU1201_RX      (UART4_TX_C16)                                      // GPS RX引脚连接到单片机此
#define GPS_TAU1201_TX      (UART4_RX_C17)                                      // GPS TX串口引脚

#define ANGLE_TO_RAD(x)     ( (x) * PI / 180.0 )                                // 角度转换为弧度
#define RAD_TO_ANGLE(x)     ( (x) * 180.0 / PI )                                // 弧度转换为角度
#define PI                  ( 3.1415926535898 )

typedef struct
{
    uint16      year;  
    uint8       month; 
    uint8       day;
    uint8       hour;
    uint8       minute;
    uint8       second;
}gps_time_struct;

typedef struct
{
    gps_time_struct    time;                                                    // 时间
    
    uint8       state;                                                          // 有效状态  1：定位有效  0：定位无效
    
    uint16      latitude_degree;                                                // 度
    uint16      latitude_cent;                                                  // 分
    uint16      latitude_second;                                                // 秒    这里的秒是被放大了100倍的，主要是避免使用浮点数
    uint16      longitude_degree;                                               // 度
    uint16      longitude_cent;                                                 // 分
    uint16      longitude_second;                                               // 秒    这里的秒是被放大了100倍的，主要是避免使用浮点数
    
    double      latitude;                                                       // 纬度
    double      longitude;                                                      // 经度
    
    int8        ns;                                                             // 纬度半球 N（北半球）或 S（南半球）
    int8        ew;                                                             // 经度半球 E（东经）或 W（西经）
    
    float       speed;                                                          // 速度（公里/每小时）
    float       direction;                                                      // 地面航向（000.0~359.9 度，以真北方为参考基准）
    
    // 下面两个个信息从GNGGA语句中获取
    uint8       satellite_used;                                                 // 用于定位的卫星数量
    float       height;                                                         // 高度   
}gps_info_struct;

typedef enum
{
    GPS_STATE_RECEIVING,                                                        // 正在接收数据
    GPS_STATE_RECEIVED,                                                         // 数据接收完成
    GPS_STATE_PARSING,                                                          // 正在解析
}gps_state_enum;

extern gps_info_struct  gps_tau1201;
extern uint8            gps_tau1201_flag;


double      get_two_points_distance     (double lat1, double lng1, double lat2, double lng2);
double      get_two_points_azimuth      (double lat1, double lon1, double lat2, double lon2);

uint8       gps_data_parse              (void);

void        gps_uart_callback           (void);

void        gps_init                    (void);

#endif
