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
* 文件名称          zf_driver_flash
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

#include "fsl_cache.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_romapi.h"
#include "zf_driver_flash.h"


flexspi_nor_config_t config;

uint32 flash_instance = 1;

flash_data_union flash_union_buffer[FLASH_DATA_BUFFER_SIZE];               // FLASH 操作的数据缓冲区



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     校验 FLASH 是否有数据
// 参数说明     sector_num      需要写入的扇区编号 参数范围 <0 - 127>
// 参数说明     page_num        当前扇区页的编号   参数范围 <FLASH_PAGE_0-FLASH_PAGE_7>
// 返回参数     uint8           1-有数据 0-没有数据 如果需要对有数据的区域写入新的数据则应该对所在扇区进行擦除操作
// 使用示例     flash_check(FLASH_SECTION_127, FLASH_PAGE_3);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check (uint32 sector_num, flash_page_enum page_num)
{
    uint16 i;
    
    status_t state = kStatus_Success;
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);//读取flash前，最好先清空缓存
    
    for(i=0; i<FLASH_PAGE_SIZE/4; i++)
    {
        if(0xFFFFFFFF != flash_read(sector_num, page_num, i, uint32))
        {
            state =  kStatus_Fail;//flash需要擦除
            break;
        }
    }
    
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     擦除扇区
// 参数说明     sector_num      需要擦除的扇区编号 参数范围 <0 - 127>
// 参数说明     page_num        当前扇区页的编号   参数范围 <FLASH_PAGE_0-FLASH_PAGE_7>
// 返回参数     uint8           1-表示失败 0-表示成功
// 使用示例     flash_erase_page(FLASH_SECTION_127, FLASH_PAGE_3);
// 备注信息     函数名称虽然是擦除页，实际上是擦除的一个删除，在这个驱动中是将扇区当做页来使用的
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_erase_page (uint32 sector_num, flash_page_enum page_num)
{
    uint32 primask;
    status_t state = kStatus_Success;
    primask = interrupt_global_disable();
    state = rom_api_flexspi_nor_flash_erase(flash_instance, &config, sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
    interrupt_global_enable(primask);
    if(state != kStatus_Success)
    {
        state = kStatus_Fail;
    }
    
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     读取一页
// 参数说明     sector_num      需要读取的扇区编号 参数范围 <0 - 127>
// 参数说明     page_num        当前扇区页的编号   参数范围 <FLASH_PAGE_0-FLASH_PAGE_7>
// 参数说明     buf             需要读取的数据地址   传入的数组类型必须为uint32
// 参数说明     len             需要写入的数据长度   参数范围 1-1024
// 返回参数     void
// 使用示例     flash_read_page(FLASH_SECTION_127, FLASH_PAGE_3, data_buffer, 256);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page (uint32 sector_num, flash_page_enum page_num, uint32 *buf, uint16 len)
{
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE, len * 4);//读取flash前，最好先清空缓存
    
    rom_api_flexspi_nor_flash_read(flash_instance, &config, buf, sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, len * 4);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     编程一页
// 参数说明     sector_num      需要写入的扇区编号 参数范围 <0 - 127>
// 参数说明     page_num        当前扇区页的编号   参数范围 <FLASH_PAGE_0-FLASH_PAGE_7>
// 参数说明     buf             需要写入的数据地址   传入的数组类型必须为uint32
// 参数说明     len             需要写入的数据长度   参数范围 1-1024
// 返回参数     uint8           1-表示失败 0-表示成功
// 使用示例     flash_write_page(FLASH_SECTION_127, FLASH_PAGE_3, data_buffer, 256);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_write_page (uint32 sector_num, flash_page_enum page_num, const uint32 *buf, uint16 len)
{
    uint8 i;
    uint32 primask;
    status_t state = kStatus_Success;
    
    zf_assert(len <= FLASH_PAGE_SIZE);                                                      
    
    if(flash_check(sector_num, page_num))                                       // 判断是否有数据 这里是冗余的保护 防止有人没擦除就写入
    {
        flash_erase_page(sector_num, page_num);                                 // 擦除这一页
    }
    
    for(i=0; i<FLASH_PAGE_NUM_DRIVER; i++)
    {
        primask = interrupt_global_disable();
        state = rom_api_flexspi_nor_flash_page_program(flash_instance, &config, sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE + (i * (FLASH_PAGE_SIZE/FLASH_PAGE_NUM_DRIVER)),(uint32 *)&flash_union_buffer[i*64]);
        interrupt_global_enable(primask);
        if(state != kStatus_Success)
        {
            state = kStatus_Fail;
            break;
        }
    }
    
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     从指定 FLASH 的扇区的指定页码读取数据到缓冲区
// 参数说明     sector_num      需要读取的扇区编号 参数范围 <0 - 127>
// 参数说明     page_num        当前扇区页的编号   参数范围 <FLASH_PAGE_0-FLASH_PAGE_7>
// 返回参数     void
// 使用示例     flash_read_page_to_buffer(FLASH_SECTION_127, FLASH_PAGE_3);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page_to_buffer (uint32 sector_num, flash_page_enum page_num)
{
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE, FLASH_PAGE_SIZE);//读取flash前，最好先清空缓存
    
    rom_api_flexspi_nor_flash_read(flash_instance, &config, (uint32 *)&flash_union_buffer[0], sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     向指定 FLASH 的扇区的指定页码写入缓冲区的数据
// 参数说明     sector_num      需要写入的扇区编号 参数范围 <0 - 127>
// 参数说明     page_num        当前扇区页的编号   参数范围 <FLASH_PAGE_0-FLASH_PAGE_7>
// 返回参数     uint8           1-表示失败 0-表示成功
// 使用示例     flash_write_page_from_buffer(FLASH_SECTION_127, FLASH_PAGE_3);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_write_page_from_buffer (uint32 sector_num, flash_page_enum page_num)
{
    uint32 primask;
    status_t state = kStatus_Success;
    primask = interrupt_global_disable();
    flash_write_page(sector_num, page_num, (const uint32 *)&flash_union_buffer[0], FLASH_PAGE_SIZE);
    interrupt_global_enable(primask);
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     清空数据缓冲区
// 参数说明     void
// 返回参数     void
// 使用示例     flash_buffer_clear();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void flash_buffer_clear (void)
{
    memset(flash_union_buffer, 0xFF, FLASH_PAGE_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     flash初始化
// 参数说明     void
// 返回参数     void
// 使用示例     flash_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_init (void)
{
    serial_nor_config_option_t option;
    
    option.option0.U = 0xC0000008; // QuadSPI NOR, Frequency: 133MHz
    
    rom_api_init();
    if(rom_api_flexspi_nor_get_config(flash_instance, &config, &option) !=  kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}
