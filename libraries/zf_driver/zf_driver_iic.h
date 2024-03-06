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
* 文件名称          zf_driver_iic
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

#ifndef _zf_driver_iic_h_
#define _zf_driver_iic_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // IIC 1 引脚 SCL
    IIC1_SCL_B16 = 16 * 1,  IIC1_SCL_D4 ,

    // IIC 2 引脚 SCL
    IIC2_SCL_C4  = 16 * 2,
    
    // IIC 3 引脚 SCL
    IIC3_SCL_B23 = 16 * 3,  IIC3_SCL_D12,
    
    // IIC 4 引脚 SCL
    IIC4_SCL_B12 = 16 * 4,
}iic_scl_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{

    // IIC 1 引脚 SDA
    IIC1_SDA_B17 = 16 * 1,

    // IIC 2 引脚 SDA
    IIC2_SDA_C5  = 16 * 2,

    // IIC 3 引脚 SDA
    IIC3_SDA_B22 = 16 * 3,  IIC3_SDA_D13,

    // IIC 4 引脚 SDA
    IIC4_SDA_B13 = 16 * 4,
}iic_sda_pin_enum;


typedef enum                                                                    // 枚举 IIC 工作状态 此枚举定义不允许用户修改
{
    IIC_SUCCESS,
    IIC_WRITE_TIMEOUT,
    IIC_READ_TIMEOUT,
}iic_state_enum;

typedef enum                                                                    // 枚举 IIC 编号 此枚举定义不允许用户修改
{
    IIC_1 = 1,
    IIC_2,
    IIC_3,
    IIC_4,
}iic_index_enum;

void        iic_write_8bit              (iic_index_enum iic_n, uint8 target_addr, const uint8 data);
void        iic_write_8bit_array        (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len);

void        iic_write_16bit             (iic_index_enum iic_n, uint8 target_addr, const uint16 data);
void        iic_write_16bit_array       (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len);

void        iic_write_8bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data);
void        iic_write_8bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len);

void        iic_write_16bit_register    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data);
void        iic_write_16bit_registers   (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len);

uint8       iic_read_8bit               (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_8bit_array         (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len);

uint16      iic_read_16bit              (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_16bit_array        (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len);

uint8       iic_read_8bit_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);
void        iic_read_8bit_registers     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len);

uint16      iic_read_16bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name);
void        iic_read_16bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len);

void        iic_transfer_8bit_array     (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len);
void        iic_transfer_16bit_array    (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len);

void        iic_sccb_write_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data);
uint8       iic_sccb_read_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);

void        iic_init                    (iic_index_enum iic_n, uint8 addr, uint32 baud, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称

#endif

#endif
