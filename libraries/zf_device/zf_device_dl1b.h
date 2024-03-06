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
* 文件名称          zf_device_dl1b
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-08-10        Teternal            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   SCL                 查看 zf_device_dl1b.h 中 DL1B_SCL_PIN  宏定义
*                   SDA                 查看 zf_device_dl1b.h 中 DL1B_SDA_PIN  宏定义
*                   XS                  查看 zf_device_dl1b.h 中 DL1B_XS_PIN  宏定义
*                   VCC                 5V 电源
*                   GND                 电源地
*                   ------------------------------------
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _ZF_DEVICE_DL1B_H_
#define _ZF_DEVICE_DL1B_H_

#include "zf_common_typedef.h"

// 需要注意的是 DL1B 最高支持 400KHz 的 IIC 通信速率
// 需要注意的是 DL1B 最高支持 400KHz 的 IIC 通信速率
// 需要注意的是 DL1B 最高支持 400KHz 的 IIC 通信速率

#define DL1B_USE_SOFT_IIC           ( 1 )                                       // 默认使用软件 IIC 方式驱动 建议使用软件 IIC 方式
#if DL1B_USE_SOFT_IIC                                                           // 这两段 颜色正常的才是正确的 颜色灰的就是没有用的
//====================================================软件 IIC 驱动====================================================
#define DL1B_SOFT_IIC_DELAY         ( 100 )                                      // 软件 IIC 的时钟延时周期 数值越小 IIC 通信速率越快
#define DL1B_SCL_PIN                ( B9 )                                      // 软件 IIC SCL 引脚 连接 DL1B 的 SCL 引脚
#define DL1B_SDA_PIN                ( B10 )                                      // 软件 IIC SDA 引脚 连接 DL1B 的 SDA 引脚
//====================================================软件 IIC 驱动====================================================
#else
//====================================================硬件 IIC 驱动====================================================
#define DL1B_IIC_SPEED              ( 400 * 1000  )                             // 硬件 IIC 通信速率 最高 400KHz 不建议低于 40KHz
#define DL1B_IIC                    ( IIC_1       )                             // 硬件 IIC SCL 引脚 连接 DL1B 的 SCL 引脚
#define DL1B_SCL_PIN                ( IIC1_SCL_B9 )                             // 硬件 IIC SCL 引脚 连接 DL1B 的 SCL 引脚
#define DL1B_SDA_PIN                ( IIC1_SDA_B10 )                             // 硬件 IIC SDA 引脚 连接 DL1B 的 SDA 引脚
//====================================================硬件 IIC 驱动====================================================
#endif

#define DL1B_XS_PIN                 ( D4 )

#define DL1B_INT_ENABLE             ( 1 )                                       // 是否启用 INT 引脚 启用则会自动更新数据
#if DL1B_INT_ENABLE
#define DL1B_INT_PIN                ( C20 )
#endif

#define DL1B_TIMEOUT_COUNT          ( 1000 )                                    // DL1B 超时计数

//================================================定义 DL1B 内部地址================================================

#define DL1B_DEV_ADDR                                           ( 0x52 >> 1 )   // 0b0101001

#define DL1B_I2C_SLAVE__DEVICE_ADDRESS                          ( 0x0001 )
#define DL1B_GPIO__TIO_HV_STATUS                                ( 0x0031 )
#define DL1B_SYSTEM__INTERRUPT_CLEAR                            ( 0x0086 )
#define DL1B_RESULT__RANGE_STATUS                               ( 0x0089 )
#define DL1B_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0     ( 0x0096 )
#define DL1B_FIRMWARE__SYSTEM_STATUS                            ( 0x00E5 )

//================================================定义 DL1B 内部地址================================================

extern uint8 dl1b_finsh_flag;
extern uint16 dl1b_distance_mm;

void   dl1b_get_distance (void);

void   dl1b_int_handler  (void);
uint8  dl1b_init         (void);

#endif

