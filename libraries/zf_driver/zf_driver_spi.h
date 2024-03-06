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
* 文件名称          zf_driver_spi
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

#ifndef _zf_driver_spi_h_
#define _zf_driver_spi_h_

#include "zf_common_typedef.h"

#define SPI_SPEED_PRIORITY                                                      // SPI 通信速度优先

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // SPI1 引脚 SCK
    SPI1_SCK_D12    = 1 * 16, 
    
    // SPI3 引脚 SCK
    SPI3_SCK_B0     = 3 * 16, SPI3_SCK_B31, 
    
    // SPI4 引脚 SCK
    SPI4_SCK_C3     = 4 * 16, SPI4_SCK_C23 ,
}spi_sck_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    // SPI1 引脚 MOSI
    SPI1_MOSI_D14   = 1 * 16,
   
    // SPI3 引脚 MOSI
    SPI3_MOSI_B1    = 3 * 16, SPI3_MOSI_B30,
    
    // SPI4 引脚 MOSI
    SPI4_MOSI_C2    = 4 * 16, SPI4_MOSI_C22,
}spi_mosi_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    SPI_MISO_NULL   = 0xFFFF,                                                   // 不使用硬件 MISO 引脚就填这个
    
    // SPI1 引脚 MISO
    SPI1_MISO_D15   = 1 * 16, 
    
    // SPI3 引脚 MISO
    SPI3_MISO_B2    = 3 * 16, SPI3_MISO_B29,
    
    // SPI4 引脚 MISO
    SPI4_MISO_C1    = 4 * 16, SPI4_MISO_C21,
}spi_miso_pin_enum;

typedef enum                                                                    // 枚举串口引脚 此枚举定义不允许用户修改
{
    SPI_CS_NULL     = 0xFFFF,                                                   // 不使用硬件 CS 引脚就填这个
    
    SPI1_CS0_D13    = 1 * 16 + 2 * 0,
    SPI1_CS2_D26    = 1 * 16 + 2 * 2,
    SPI1_CS3_D27    = 1 * 16 + 2 * 3,
        
    SPI3_CS0_B3     = 3 * 16 + 2 * 0, SPI3_CS0_B28,
        
    SPI4_CS0_C0     = 4 * 16 + 2 * 0, SPI4_CS0_C20 ,
    SPI4_CS1_C19    = 4 * 16 + 2 * 1,
    SPI4_CS2_C18    = 4 * 16 + 2 * 2,
    SPI4_CS3_C27    = 4 * 16 + 2 * 3,
}spi_cs_pin_enum;

typedef enum                                                                    // 枚举 SPI 模式 此枚举定义不允许用户修改
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}spi_mode_enum;

typedef enum                                                                    // 枚举 SPI 编号 此枚举定义不允许用户修改
{
    SPI_1 = 1,
    SPI_3 = 3,
    SPI_4,
    SPI_MAX,
}spi_index_enum;

void        spi_write_8bit                  (spi_index_enum spi_n, const uint8 data);
void        spi_write_8bit_array            (spi_index_enum spi_n, const uint8 *data, uint32 len);

void        spi_write_16bit                 (spi_index_enum spi_n, const uint16 data);
void        spi_write_16bit_array           (spi_index_enum spi_n, const uint16 *data, uint32 len);

void        spi_write_8bit_register         (spi_index_enum spi_n, const uint8 register_name, const uint8 data);
void        spi_write_8bit_registers        (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 len);

void        spi_write_16bit_register        (spi_index_enum spi_n, const uint16 register_name, const uint16 data);
void        spi_write_16bit_registers       (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 len);

uint8       spi_read_8bit                   (spi_index_enum spi_n);
void        spi_read_8bit_array             (spi_index_enum spi_n, uint8 *data, uint32 len);

uint16      spi_read_16bit                  (spi_index_enum spi_n);
void        spi_read_16bit_array            (spi_index_enum spi_n, uint16 *data, uint32 len);

uint8       spi_read_8bit_register          (spi_index_enum spi_n, const uint8 register_name);
void        spi_read_8bit_registers         (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 len);

uint16      spi_read_16bit_register         (spi_index_enum spi_n, const uint16 register_name);
void        spi_read_16bit_registers        (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 len);

void        spi_transfer_8bit               (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len);
void        spi_transfer_16bit              (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len);

void        spi_init                        (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // 兼容旧版本开源库接口名称
#define spi_mosi(spi_n, mosi, miso, len)    (spi_transfer_8bit((spi_n), (mosi), (miso), (len)))
#endif

#endif
