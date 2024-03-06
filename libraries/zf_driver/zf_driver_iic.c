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


#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "fsl_lpi2c.h"
#include "fsl_iomuxc.h"

#include "zf_driver_iic.h"

static  LPI2C_Type *iic_index[]      = LPI2C_BASE_PTRS;


#define LPI2C_CLOCK_SOURCE_DIVIDER (0x05)
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1))
#define IIC_PIN_CONF  SPEED_100MHZ | KEEPER_EN | PULLUP_22K | DSE_R0_6 | OD_EN  //配置IIC引脚默认配置

void iic_iomuxc(iic_index_enum iic_n, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin)
{
    switch(iic_n)
    {
        case IIC_1:
        {
            if      (IIC1_SDA_B17 == sda_pin) afio_init(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 1, IIC_PIN_CONF);                            
                                                             
            if      (IIC1_SCL_B16 == scl_pin) afio_init(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, 1, IIC_PIN_CONF);
            else if (IIC1_SCL_D4  == scl_pin) afio_init(IOMUXC_GPIO_SD_B1_04_LPI2C1_SCL, 1, IIC_PIN_CONF);                             
        }break;                                              
                                                             
        case IIC_2:                                          
        {                                                    
            if      (IIC2_SDA_C5  == sda_pin) afio_init(IOMUXC_GPIO_B0_05_LPI2C2_SDA,    1, IIC_PIN_CONF);
                                                                
            if      (IIC2_SCL_C4  == scl_pin) afio_init(IOMUXC_GPIO_B0_04_LPI2C2_SCL,    1, IIC_PIN_CONF);                          
        }break;                                              
                                                             
        case IIC_3:                                          
        {                                                    
            if      (IIC3_SDA_B22 == sda_pin) afio_init(IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA, 1, IIC_PIN_CONF);
            else if (IIC3_SDA_D13 == sda_pin) afio_init(IOMUXC_GPIO_SD_B0_01_LPI2C3_SDA, 1, IIC_PIN_CONF);
                                                       
            if      (IIC3_SCL_B23 == scl_pin) afio_init(IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL, 1, IIC_PIN_CONF);
            else if (IIC3_SCL_D12 == scl_pin) afio_init(IOMUXC_GPIO_SD_B0_00_LPI2C3_SCL, 1, IIC_PIN_CONF);
        }break;                                              
                                                             
        case IIC_4:                                          
        {                                                    
            if      (IIC4_SDA_B13 == sda_pin) afio_init(IOMUXC_GPIO_AD_B0_13_LPI2C4_SDA, 1, IIC_PIN_CONF);                               
                                                                
            if      (IIC4_SCL_B12 == scl_pin) afio_init(IOMUXC_GPIO_AD_B0_12_LPI2C4_SCL, 1, IIC_PIN_CONF);
        }break;
        
        default:zf_assert(0);break;
    }
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_8bit(IIC_1, 0x7A, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit (iic_index_enum iic_n, uint8 target_addr, const uint8 data)
{
    status_t state = kStatus_Fail;

    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&data, 1);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_8bit_array(IIC_1, 0x7A, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_array (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;

    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterSend(iic_index[iic_n], (void *)data, len);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_16bit(IIC_1, 0x7A, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit (iic_index_enum iic_n, uint8 target_addr, const uint16 data)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        temp_data[0] = data>>8;
        temp_data[1] = data;
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口写 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_16bit_array(IIC_1, 0x7A, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_array (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        while(len--)
        {
            temp_data[0] = *data >> 8;
            temp_data[1] = *data;
            state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
            data++;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_8bit_register(IIC_1, 0x7A, 0x01, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data)
{
    status_t state = kStatus_Fail;
    
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&data, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_8bit_registers(IIC_1, 0x7A, 0x01, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&data, len);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_write_16bit_register(IIC_1, 0x7A, 0x0101, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_register (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        temp_data[0] = data>>8;
        temp_data[1] = data;
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口向传感器寄存器写 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_write_16bit_registers(IIC_1, 0x7A, 0x0101, data, 6);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        while(len--)
        {
            temp_data[0] = *data>>8;
            temp_data[1] = *data;
            state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
            data++;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 返回参数     uint8           返回读取的 8bit 数据
// 使用示例     iic_read_8bit(IIC_1, 0x7A);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_8bit (iic_index_enum iic_n, uint8 target_addr)
{
    status_t state = kStatus_Fail;
    uint8 return_data = 0;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)&return_data, 1);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_8bit_array(IIC_1, 0x7A, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_8bit_array (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)data, len);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 返回参数     uint16          返回读取的 16bit 数据
// 使用示例     iic_read_16bit(IIC_1, 0x7A);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 iic_read_16bit (iic_index_enum iic_n, uint8 target_addr)
{
    status_t state = kStatus_Fail;
    uint16 return_data = 0;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
        return_data = ((uint16)temp_data[0]<<8) | temp_data[1];
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口读取 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_16bit_array(IIC_1, 0x7A, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_16bit_array (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        while(len --)
        {
            state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
            *data = ((uint16)temp_data[0]<<8) | temp_data[1];
            data++;
        }
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 返回参数     uint8           返回读取的 8bit 数据
// 使用示例     iic_read_8bit_register(IIC_1, 0x7A, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_8bit_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name)
{
    status_t state = kStatus_Fail;
    uint8 return_data = 0;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)&return_data, 1);

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 8bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_8bit_registers(IIC_1, 0x7A, 0x01, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_8bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)data, len);

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 16bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 返回参数     uint16          返回读取的 16bit 数据
// 使用示例     iic_read_16bit_register(IIC_1, 0x7A, 0x0101);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 iic_read_16bit_register (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name)
{
    status_t state = kStatus_Fail;
    uint16 return_data = 0;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        
        temp_data[0] = (register_name)>>8;
        temp_data[1] = (register_name);
        state = LPI2C_MasterSend(iic_index[iic_n], temp_data, 2);
        
        
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        

        state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
        return_data = ((uint16)temp_data[0]<<8) | temp_data[1];


        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口从传感器寄存器读取 16bit 数组
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     *data           数据存放缓冲区
// 参数说明     len             缓冲区长度
// 返回参数     void            
// 使用示例     iic_read_16bit_registers(IIC_1, 0x7A, 0x0101, data, 8);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_16bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        
        temp_data[0] = (register_name)>>8;
        temp_data[1] = (register_name);
        state = LPI2C_MasterSend(iic_index[iic_n], temp_data, 2);
        
        
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        
        while(len --)
        {
            state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
            *data = ((uint16)temp_data[0]<<8) | temp_data[1];
            data++;
        }

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口传输 8bit 数组 先写后读取
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标器件地址
// 参数说明     *write_data     发送数据存放缓冲区
// 参数说明     write_len       发送缓冲区长度
// 参数说明     *read_data      读取数据存放缓冲区
// 参数说明     read_len        读取缓冲区长度
// 返回参数     void            
// 使用示例     iic_transfer_8bit_array(IIC_1, addr, data, 64, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer_8bit_array (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len)
{
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)write_data, write_len);
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)read_data, read_len);

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口传输 16bit 数组 先写后读取
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标器件地址
// 参数说明     *write_data     发送数据存放缓冲区
// 参数说明     write_len       发送缓冲区长度
// 参数说明     *read_data      读取数据存放缓冲区
// 参数说明     read_len        读取缓冲区长度
// 返回参数     void            
// 使用示例     iic_transfer_16bit_array(IIC_1, addr, data, 64, data, 64);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer_16bit_array (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        while(write_len --)
        {
            temp_data[0] = (*write_data)>>8;
            temp_data[1] = (*write_data);
            state = LPI2C_MasterSend(iic_index[iic_n], temp_data, 2);
            write_data++;
        }
        
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        
        while(read_len --)
        {
            state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
            *read_data = ((uint16)temp_data[0]<<8) | temp_data[1];
            read_data++;
        }

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口 SCCB 模式向传感器寄存器写 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 参数说明     data            要写入的数据
// 返回参数     void            
// 使用示例     iic_sccb_write_register(IIC_1, 0x7A, 0x01, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_sccb_write_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data)
{
    status_t state = kStatus_Fail;
    
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterSend(iic_index[iic_n], &data, 1);
        if (state != kStatus_Success)
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口 SCCB 模式从传感器寄存器读取 8bit 数据
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     target_addr     目标地址
// 参数说明     register_name   传感器的寄存器地址
// 返回参数     uint8           返回读取的 8bit 数据
// 使用示例     iic_sccb_read_register(IIC_1, 0x7A, 0x01);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_sccb_read_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name)
{
    uint8 data = 0;
    
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterReceive(iic_index[iic_n], &data, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
    
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IIC 接口初始化 默认 MASTER 模式 不提供 SLAVE 模式
// 参数说明     iic_n           IIC 模块号 参照 zf_driver_iic.h 内 iic_index_enum 枚举体定义
// 参数说明     addr            IIC 地址 这里需要注意 标准七位地址 最高位忽略 写入时请务必确认无误
// 参数说明     baud            IIC 波特率 不超过 1000Khz 不低于 1KHz 
// 参数说明     scl_pin         IIC 时钟引脚 参照 zf_driver_iic.h 内 iic_scl_pin_enum 枚举体定义
// 参数说明     sda_pin         IIC 数据引脚 参照 zf_driver_iic.h 内 iic_sda_pin_enum 枚举体定义
// 返回参数     void            
// 使用示例     iic_init(IIC_1, 0x7A, 100000, IIC1_SCL_D10, IIC1_SDA_D11);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void iic_init(iic_index_enum iic_n, uint8 addr, uint32 baud, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin)
{
    zf_assert((baud >= 1000)&&(baud <= 1000000));                             // 至少 1KHz 至多 400KHz 速率
    zf_assert((scl_pin / 16) == (sda_pin / 16));                                // scl_pin 与 sda_pin 必须与 iic_n 匹配

    lpi2c_master_config_t masterConfig;
    
    iic_iomuxc(iic_n, scl_pin, sda_pin);

    CLOCK_SetMux(kCLOCK_Lpi2cMux, 0);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    
    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = baud;
    LPI2C_MasterInit(iic_index[iic_n], &masterConfig, LPI2C_CLOCK_FREQUENCY);   // 第一次初始化便于打开时钟
    LPI2C_MasterReset(iic_index[iic_n]);                                        // 复位外设
    LPI2C_MasterInit(iic_index[iic_n], &masterConfig, LPI2C_CLOCK_FREQUENCY);   // 重新初始化设置正确的参数
}
