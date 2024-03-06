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


#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "fsl_lpspi.h"
#include "fsl_iomuxc.h"

#include "zf_driver_spi.h"


#define LPSPI_PIN_CONF              SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置SPI引脚默认配置
#define LPSPI_CLK_DIV               3
#define LPSPI_CLK_SRC               2


static LPSPI_Type   *spi_index[] = LPSPI_BASE_PTRS;
static uint16       spi_cs_index[SPI_MAX];

void spi_iomuxc(spi_index_enum spi_n, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin)
{
    switch(spi_n)
    {
        case SPI_1:
        {
            if      (SPI1_SCK_D12  == sck_pin)  afio_init(IOMUXC_GPIO_SD_B0_00_LPSPI1_SCK,  0, LPSPI_PIN_CONF);
                                                                    
            if      (SPI1_MOSI_D14 == mosi_pin) afio_init(IOMUXC_GPIO_SD_B0_02_LPSPI1_SDO,  0, LPSPI_PIN_CONF);
                                                                    
            if      (SPI1_MISO_D15 == miso_pin) afio_init(IOMUXC_GPIO_SD_B0_03_LPSPI1_SDI,  0, LPSPI_PIN_CONF);
                                                                  
            if      (SPI1_CS0_D13  == cs_pin)   afio_init(IOMUXC_GPIO_SD_B0_01_LPSPI1_PCS0, 0, LPSPI_PIN_CONF);
            else if (SPI1_CS2_D26  == cs_pin)   afio_init(IOMUXC_GPIO_EMC_40_LPSPI1_PCS2,   0, LPSPI_PIN_CONF);
            else if (SPI1_CS3_D27  == cs_pin)   afio_init(IOMUXC_GPIO_EMC_41_LPSPI1_PCS3,   0, LPSPI_PIN_CONF);
        }break;                                                   
                                                                  
        case SPI_3:                                               
        {                                                         
            if      (SPI3_SCK_B0   == sck_pin)  afio_init(IOMUXC_GPIO_AD_B0_00_LPSPI3_SCK,  0, LPSPI_PIN_CONF);
            else if (SPI3_SCK_B31  == sck_pin)  afio_init(IOMUXC_GPIO_AD_B1_15_LPSPI3_SCK,  0, LPSPI_PIN_CONF);
                                                                    
            if      (SPI3_MOSI_B1  == mosi_pin) afio_init(IOMUXC_GPIO_AD_B0_01_LPSPI3_SDO,  0, LPSPI_PIN_CONF);
            else if (SPI3_MOSI_B30 == mosi_pin) afio_init(IOMUXC_GPIO_AD_B1_14_LPSPI3_SDO,  0, LPSPI_PIN_CONF);
                                                                  
            if      (SPI3_MISO_B2  == miso_pin) afio_init(IOMUXC_GPIO_AD_B0_02_LPSPI3_SDI,  0, LPSPI_PIN_CONF);
            else if (SPI3_MISO_B29 == miso_pin) afio_init(IOMUXC_GPIO_AD_B1_13_LPSPI3_SDI,  0, LPSPI_PIN_CONF);
                                                                  
            if      (SPI3_CS0_B3   == cs_pin)   afio_init(IOMUXC_GPIO_AD_B0_03_LPSPI3_PCS0, 0, LPSPI_PIN_CONF);
            else if (SPI3_CS0_B28  == cs_pin)   afio_init(IOMUXC_GPIO_AD_B1_12_LPSPI3_PCS0, 0, LPSPI_PIN_CONF);
        }break;                                                   
                                                                  
        case SPI_4:                                               
        {                                                         
            if      (SPI4_SCK_C3   == sck_pin)  afio_init(IOMUXC_GPIO_B0_03_LPSPI4_SCK,     0, LPSPI_PIN_CONF);
            else if (SPI4_SCK_C23  == sck_pin)  afio_init(IOMUXC_GPIO_B1_07_LPSPI4_SCK,     0, LPSPI_PIN_CONF);
                                                                    
            if      (SPI4_MOSI_C2  == mosi_pin) afio_init(IOMUXC_GPIO_B0_02_LPSPI4_SDO,     0, LPSPI_PIN_CONF);
            else if (SPI4_MOSI_C22 == mosi_pin) afio_init(IOMUXC_GPIO_B1_06_LPSPI4_SDO,     0, LPSPI_PIN_CONF);
                                                                    
            if      (SPI4_MISO_C1  == miso_pin) afio_init(IOMUXC_GPIO_B0_01_LPSPI4_SDI,     0, LPSPI_PIN_CONF);
            else if (SPI4_MISO_C21 == miso_pin) afio_init(IOMUXC_GPIO_B1_05_LPSPI4_SDI,     0, LPSPI_PIN_CONF);
                                                                  
            if      (SPI4_CS0_C0   == cs_pin)   afio_init(IOMUXC_GPIO_B0_00_LPSPI4_PCS0,    0, LPSPI_PIN_CONF);
            else if (SPI4_CS0_C20  == cs_pin)   afio_init(IOMUXC_GPIO_B1_04_LPSPI4_PCS0,    0, LPSPI_PIN_CONF);
            else if (SPI4_CS1_C19  == cs_pin)   afio_init(IOMUXC_GPIO_B1_03_LPSPI4_PCS1,    0, LPSPI_PIN_CONF);
            else if (SPI4_CS2_C18  == cs_pin)   afio_init(IOMUXC_GPIO_B1_02_LPSPI4_PCS2,    0, LPSPI_PIN_CONF);
            else if (SPI4_CS3_C27  == cs_pin)   afio_init(IOMUXC_GPIO_B1_11_LPSPI4_PCS3,    0, LPSPI_PIN_CONF);
        }break;
        
        default:
        {
            zf_assert(0); 
        }break;
    }
}


void spi_write(spi_index_enum spi_n, const uint8 *txdata, uint8 *rxdata, uint32 length, uint8 continuous)
{
    uint32 transfer_status;
    lpspi_transfer_t transfer;

    zf_assert(0 < length);               // 断言字节数不为0
    
    if(continuous)  transfer.configFlags = ((spi_cs_index[spi_n]%16/2)<<LPSPI_MASTER_PCS_SHIFT) | kLPSPI_MasterPcsContinuous;
    else            transfer.configFlags = ((spi_cs_index[spi_n]%16/2)<<LPSPI_MASTER_PCS_SHIFT);
    transfer.txData = (uint8 *)txdata;
    transfer.rxData = rxdata;
    transfer.dataSize = length;
    do
    {
        transfer_status = LPSPI_MasterTransferBlocking(spi_index[spi_n], &transfer);
    }while(transfer_status == kStatus_LPSPI_Busy);
}


#ifndef SPI_SPEED_PRIORITY
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 8bit 数据读写
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     uint8           读取的数据
// 使用示例     spi_8bit_data_handler(spi_n, 5);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 spi_8bit_data_handler (spi_index_enum spi_n, const uint8 data)
{
    uint8 read_data = 0;
    spi_write(spi_n, &data, &read_data, 1, 1);
    return read_data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 16bit 数据读写
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     uint16          读取的数据
// 使用示例     spi_16bit_data_handler(spi_n, 5);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint16 spi_16bit_data_handler (spi_index_enum spi_n, const uint16 data)
{
    uint16 read_data = 0;
    spi_write(spi_n, (const uint8 *)&data, (uint8 *)&read_data, 2, 1);
    return read_data;
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     length          缓冲区长度
// 返回参数     void
// 使用示例     spi_write_8bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_array (spi_index_enum spi_n, const uint8 *data, uint32 length)
{
#ifdef SPI_SPEED_PRIORITY
    lpspi_transfer_t transfer;
    
    spi_write(spi_n, data, NULL, length, 1);
#else
    while(length --)
    {
        spi_8bit_data_handler(spi_n, *data ++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_8bit(SPI_1, 0x11);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit (spi_index_enum spi_n, const uint8 data)
{
#ifdef SPI_SPEED_PRIORITY
    spi_write_8bit_array(spi_n, &data, 1);
#else
    spi_8bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_16bit(SPI_1, 0x1101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit (spi_index_enum spi_n, const uint16 data)
{
#ifdef SPI_SPEED_PRIORITY
    uint8 temp_data[2];
    temp_data[0] = data >> 8;
    temp_data[1] = data;
    spi_write_8bit_array(spi_n, temp_data, 2);
#else
    spi_16bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口写 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_16bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_array (spi_index_enum spi_n, const uint16 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    uint8 temp_data[2];
    uint32 temp_length = 0;
    
    if(1 == length)
    {
        spi_write_16bit(spi_n, *data);
    }
    else
    {
        temp_data[0] = data[temp_length] >> 8;
        temp_data[1] = data[temp_length];
        temp_length++;
        spi_write(spi_n, temp_data, NULL, 2, 1);
        
        while(temp_length < length)
        {
            temp_data[0] = data[temp_length] >> 8;
            temp_data[1] = data[temp_length];
            spi_write(spi_n, temp_data, NULL, 2, (temp_length == (length - 1)));
            temp_length++;
        }
    }
#else
    while(length --)
    {
        spi_16bit_data_handler(spi_n, *data ++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_8bit_register(SPI_1, 0x11, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_register (spi_index_enum spi_n, const uint8 register_name, const uint8 data)
{
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, &register_name, NULL, 1, 0);
    spi_write(spi_n, &data, NULL, 1, 1);
#else
    spi_8bit_data_handler(spi_n, register_name);
    spi_8bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_8bit_registers(SPI_1, 0x11, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_8bit_registers (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, &register_name, NULL, 1, 1);
    spi_write(spi_n, data, NULL, length, 1);
#else
    spi_8bit_data_handler(spi_n, register_name);
    while(length --)
    {
        spi_8bit_data_handler(spi_n, *data ++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     spi_write_16bit_register(SPI_1, 0x1011, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_register (spi_index_enum spi_n, const uint16 register_name, const uint16 data)
{
#ifdef SPI_SPEED_PRIORITY
    uint8 temp_data[2];

    temp_data[0] = register_name >> 8;
    temp_data[1] = register_name;
    spi_write(spi_n, temp_data, NULL, 2, 1);
    
    temp_data[0] = data >> 8;
    temp_data[1] = data;
    spi_write(spi_n, temp_data, NULL, 2, 1);
#else
    spi_16bit_data_handler(spi_n, register_name);
    spi_16bit_data_handler(spi_n, data);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口向传感器的寄存器写 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             缓冲区长度
// 返回参数     void
// 使用示例     spi_write_16bit_registers(SPI_1, 0x1011, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_write_16bit_registers (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, (const uint8 *)&register_name, NULL, 2, 1);
    spi_write(spi_n, (const uint8 *)&data, NULL, 2 * length, 1);
#else
    spi_16bit_data_handler(spi_n, register_name);
    while(length--)
    {
        spi_16bit_data_handler(spi_n, *data++);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint8           数据
// 使用示例     spi_read_8bit(SPI_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit (spi_index_enum spi_n)
{
#ifdef SPI_SPEED_PRIORITY
    uint8 data = 0;
    spi_write(spi_n, NULL, &data, 1, 1);
    return data;
#else
    return spi_8bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_8bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_array (spi_index_enum spi_n, uint8 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, NULL, data, length, 1);
#else
    while(length --)
    {
        *data ++ = spi_8bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint16          数据
// 使用示例     spi_read_16bit(SPI_1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit (spi_index_enum spi_n)
{
#ifdef SPI_SPEED_PRIORITY
    uint16 data = 0;
    spi_write(spi_n, NULL, (uint8 *)&data, 2, 1);
    return data;
#else
    return spi_16bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口读 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_16bit_array(SPI_1, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_array (spi_index_enum spi_n, uint16 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, NULL, (uint8 *)data, 2 * length, 1);
#else
    while(length --)
    {
        *data ++ = spi_16bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 8bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint8           数据
// 使用示例     spi_read_8bit_register(SPI_1, 0x11);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_read_8bit_register (spi_index_enum spi_n, const uint8 register_name)
{
#ifdef SPI_SPEED_PRIORITY
    uint8 data = 0;
    
    spi_write(spi_n, (const uint8 *)&register_name, NULL, 1, 1);
    spi_write(spi_n, NULL, (uint8 *)&data, 1, 1);
    return data;
#else
    spi_8bit_data_handler(spi_n, register_name);
    return spi_8bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 8bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_8bit_registers(SPI_1, 0x11, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_8bit_registers (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, (const uint8 *)&register_name, NULL, 1, 1);
    spi_write(spi_n, NULL, (uint8 *)data, length, 1);
#else
    spi_8bit_data_handler(spi_n, register_name);
    while(length --)
    {
        *data ++ = spi_8bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 16bit 数据
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 返回参数     uint16          数据
// 使用示例     spi_read_16bit_register(SPI_1, 0x1011);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 spi_read_16bit_register (spi_index_enum spi_n, const uint16 register_name)
{
#ifdef SPI_SPEED_PRIORITY
    uint16 data = 0;
    spi_write(spi_n, (const uint8 *)&register_name, NULL, 2, 1);
    spi_write(spi_n, NULL, (uint8 *)&data, 2, 1);
    return data;
#else
    spi_16bit_data_handler(spi_n, register_name);
    return spi_16bit_data_handler(spi_n, 0);
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口从传感器的寄存器读 16bit 数组
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     register_name   寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     length             发送缓冲区长度
// 返回参数     void
// 使用示例     spi_read_16bit_registers(SPI_1, 0x1101, data, 32);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_read_16bit_registers (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 length)
{
    zf_assert(data != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, (const uint8 *)&register_name, NULL, 2, 1);
    spi_write(spi_n, NULL, (uint8 *)data, 2 * length, 1);
#else
    spi_16bit_data_handler(spi_n, register_name);
    while(length --)
    {
        *data ++ = spi_16bit_data_handler(spi_n, 0);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 8bit 数据传输 发送与接收数据是同时进行的
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     write_buffer    发送的数据缓冲区地址
// 参数说明     read_buffer     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// 参数说明     length             缓冲区长度
// 返回参数     void
// 使用示例     spi_transfer_8bit(SPI_1, buf, buf, 1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_8bit (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 length)
{
    zf_assert(write_buffer != NULL);
#ifdef SPI_SPEED_PRIORITY
    spi_write(spi_n, write_buffer, read_buffer, length, 1);
#else
    while(length --)
    {
        *read_buffer = spi_8bit_data_handler(spi_n, *write_buffer);
        write_buffer ++;
        read_buffer ++;
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 16bit 数据传输 发送与接收数据是同时进行的
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     write_buffer    发送的数据缓冲区地址
// 参数说明     read_buffer     发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
// 参数说明     length             缓冲区长度
// 返回参数     void
// 使用示例     spi_transfer_16bit(SPI_1, buf, buf, 1);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_transfer_16bit (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 length)
{
    zf_assert(write_buffer != NULL);
#ifdef SPI_SPEED_PRIORITY
    uint16 temp;
    while(length --)
    {
        temp = *write_buffer;
        temp = (temp << 8) | (temp >> 8);
        spi_write(spi_n, (const uint8 *)&temp, (uint8 *)read_buffer, 2, 1);
        write_buffer ++;
        read_buffer ++;
    }
    
#else
    while(length --)
    {
        *read_buffer = spi_16bit_data_handler(spi_n, *write_buffer);
        write_buffer ++;
        read_buffer ++;
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     SPI 接口初始化
// 参数说明     spi_n           SPI 模块号 参照 zf_driver_spi.h 内 spi_index_enum 枚举体定义
// 参数说明     mode            SPI 模式 参照 zf_driver_spi.h 内 spi_mode_enum 枚举体定义
// 参数说明     baud            设置 SPI 的波特率 不超过系统时钟的一半 部分速率会被适配成相近的速率
// 参数说明     sck_pin         选择 SCK 引脚 参照 zf_driver_spi.h 内 spi_sck_pin_enum 枚举体定义
// 参数说明     mosi_pin        选择 MOSI 引脚 参照 zf_driver_spi.h 内 spi_mosi_pin_enum 枚举体定义
// 参数说明     miso_pin        选择 MISO 引脚 参照 zf_driver_spi.h 内 spi_miso_pin_enum 枚举体定义
// 参数说明     cs_pin          选择 CS 引脚 参照 zf_driver_spi.h 内 spi_cs_pin_enum 枚举体定义
// 返回参数     void
// 使用示例     spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_D12, SPI1_MOSI_D14, SPI1_MISO_D15, SPI1_CS0_D13);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void spi_init (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin)
{
    zf_assert(spi_n == (sck_pin / 16));                                         // sck_pin  与 spi_n 匹配
    zf_assert(spi_n == (mosi_pin / 16));                                        // mosi_pin 与 spi_n 匹配
    zf_assert(spi_n == (miso_pin / 16) || (miso_pin == SPI_MISO_NULL));         // miso_pin 与 spi_n 匹配
    zf_assert(spi_n == (cs_pin / 16) || (cs_pin == SPI_CS_NULL));               // cs_pin   与 spi_n 匹配
    
    if(SPI_CS_NULL == cs_pin)
    {
        spi_cs_index[spi_n] = 0;
    }
    else
    {
        spi_cs_index[spi_n] = cs_pin;
    }
    
    
    lpspi_master_config_t masterConfig;
    uint32 src_clock;
    
    spi_iomuxc(spi_n, sck_pin, mosi_pin, miso_pin, cs_pin);

    CLOCK_SetMux(kCLOCK_LpspiMux, LPSPI_CLK_SRC);    //选择PLL2作为LPSPI时钟源
    CLOCK_SetDiv(kCLOCK_LpspiDiv, LPSPI_CLK_DIV);
    
    LPSPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate = baud;
    masterConfig.bitsPerFrame = 8;
    masterConfig.whichPcs = (lpspi_which_pcs_t)(cs_pin%14/2-3);
    
    switch(mode)
    {
        case SPI_MODE0:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh; 
            masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge; 
        }break;
        
        case SPI_MODE1:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveHigh; 
            masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge; 
        }break;
        
        case SPI_MODE2:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveLow; 
            masterConfig.cpha = kLPSPI_ClockPhaseFirstEdge; 
        }break;
        
        case SPI_MODE3:
        {
            masterConfig.cpol = kLPSPI_ClockPolarityActiveLow; 
            masterConfig.cpha = kLPSPI_ClockPhaseSecondEdge; 
        }break;
    }

    masterConfig.pcsToSckDelayInNanoSec = 1000000000 / masterConfig.baudRate;
    masterConfig.lastSckToPcsDelayInNanoSec = 1000000000 / masterConfig.baudRate;
    masterConfig.betweenTransferDelayInNanoSec = 1000000000 / masterConfig.baudRate;
    src_clock = (CLOCK_GetFreq(kCLOCK_SysPllClk) / (LPSPI_CLK_DIV + 1U));
    
    LPSPI_MasterInit(spi_index[spi_n], &masterConfig, src_clock);//第一次初始化便于打开时钟
    LPSPI_Reset(spi_index[spi_n]);                               //复位外设
    LPSPI_MasterInit(spi_index[spi_n], &masterConfig, src_clock);//重新初始化设置正确的参数
    
    LPSPI_Enable(spi_index[spi_n], false);
    spi_index[spi_n]->CFGR1 &= (~LPSPI_CFGR1_NOSTALL_MASK);
    LPSPI_Enable(spi_index[spi_n], true);

    LPSPI_FlushFifo(spi_index[spi_n], true, true);                       //刷新FIFO
    LPSPI_ClearStatusFlags(spi_index[spi_n], kLPSPI_AllStatusFlag);      //清除状态标志
    LPSPI_DisableInterrupts(spi_index[spi_n], kLPSPI_AllInterruptEnable);//关闭中断
}
