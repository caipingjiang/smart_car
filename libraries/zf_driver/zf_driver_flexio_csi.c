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
* 文件名称          zf_driver_flexio_csi
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


#include "fsl_flexio_camera.h"
#include "fsl_flexio.h"
#include "fsl_iomuxc.h"
#include "fsl_dmamux.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_flexio_csi.h"

#define FLEXIO_PIN_CONF         SPEED_100MHZ | KEEPER_EN | DSE_R0_6             // 配置FLEXIO引脚默认配置


#define DMA_CHN                 0u
#define DMA_MUX_SRC             kDmaRequestMuxFlexIO2Request2Request3

static uint8 flexio_shift_count;
static FLEXIO_CAMERA_Type s_FlexioCameraDevice;
static flexio_camera_config_t s_FlexioCameraConfig;

edma_transfer_config_t transferConfig;
edma_config_t edma_config;
edma_handle_t g_EDMA_Handle;

void flexio_iomuxc(flexio_pin_enum dat_pin_start, flexio_pin_enum pclk_pin, flexio_pin_enum href_pin)
{
    uint8 i;
    uint32 temp_config[5] = {IOMUXC_GPIO_B0_00_FLEXIO2_FLEXIO00};
    zf_assert(FLEXIO2_D24_C24 >= dat_pin_start);                                // 数据引脚参数错误  起始引脚不得大于24
    zf_assert((pclk_pin < dat_pin_start) || (pclk_pin > (dat_pin_start + 7)));  // 像素时钟引脚不应该在数据引脚范围内
    zf_assert((href_pin < dat_pin_start) || (href_pin > (dat_pin_start + 7)));  // 行信号引脚不应该在数据引脚范围内
    zf_assert(href_pin != pclk_pin);                                            // 行信号引脚不应该与像素时钟引脚一样
    
    afio_init(temp_config[0] + pclk_pin * 4, temp_config[1], temp_config[2], temp_config[3], temp_config[4] + pclk_pin * 4, 0, FLEXIO_PIN_CONF);
    afio_init(temp_config[0] + href_pin * 4, temp_config[1], temp_config[2], temp_config[3], temp_config[4] + href_pin * 4, 0, FLEXIO_PIN_CONF);
    
    for(i=0; i<8; i++)
    {
        afio_init(temp_config[0] + (dat_pin_start + i) * 4, temp_config[1], temp_config[2], temp_config[3], temp_config[4] + (dat_pin_start + i) * 4, 0, FLEXIO_PIN_CONF);
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO 使能
//  @param      enable          1：使能FLEXIO   0：关闭FLEXIO
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_enable(uint8 enable)
{
    if(enable)
    {
        s_FlexioCameraDevice.flexioBase->CTRL |= FLEXIO_CTRL_FLEXEN_MASK;
    }
    else
    {
        s_FlexioCameraDevice.flexioBase->CTRL &= ~FLEXIO_CTRL_FLEXEN_MASK;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO 标志位清除
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_flag_clear(void)
{
    FLEXIO_CAMERA_ClearStatusFlags(&s_FlexioCameraDevice, kFLEXIO_CAMERA_RxDataRegFullFlag | kFLEXIO_CAMERA_RxErrorFlag);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA开启
//  @param      dest_addr       目的地址
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_dma_restart(uint8 *dest_addr)
{
    DMA0->TCD[DMA_CHN].DADDR = (uint32_t)(dest_addr);
    flexio_csi_flag_clear();
    DMA0->SERQ = DMA_SERQ_SERQ(DMA_CHN);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO RX启用DMA触发
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_enable_rxdma(void)
{
    FLEXIO_CAMERA_EnableRxDMA(&s_FlexioCameraDevice, true);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA初始化
//  @param      dest_addr       目的地址
//  @param      count           DMA传输次数
//  @param      callback        DMA中断回调函数
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_dma_init(uint8 *dest_addr, uint32 count, edma_callback callback)
{
    edma_modulo_t s_addr_modulo;
    
    DMAMUX_Deinit(DMAMUX);
    DMAMUX_Init(DMAMUX);
    DMAMUX_SetSource(DMAMUX, DMA_CHN, DMA_MUX_SRC);
    DMAMUX_EnableChannel(DMAMUX, DMA_CHN);
    
    EDMA_GetDefaultConfig(&edma_config);
    EDMA_Deinit(DMA0);
    EDMA_Init(DMA0, &edma_config);
    DMA0->CERR = DMA_CERR_CERR_MASK | DMA_CERR_CAEI_MASK;
    
    EDMA_CreateHandle(&g_EDMA_Handle, DMA0, DMA_CHN);
    EDMA_SetCallback(&g_EDMA_Handle, callback, NULL);
    EDMA_PrepareTransfer(&transferConfig, 
                        (void *)FLEXIO_CAMERA_GetRxBufferAddress(&s_FlexioCameraDevice), 
                        4,
                        (void *)(dest_addr), 
                        4,
                        4*flexio_shift_count,
                        count,
                        kEDMA_MemoryToMemory);
    
    
    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);
    
    switch(4*flexio_shift_count)
    {
        case 4:     s_addr_modulo = kEDMA_Modulo4bytes;break;
        case 8:     s_addr_modulo = kEDMA_Modulo8bytes;break;
        case 16:    s_addr_modulo = kEDMA_Modulo16bytes;break;
        case 32:    s_addr_modulo = kEDMA_Modulo32bytes;break;
        default:assert(0);  //参数有误
    }
    
    
    EDMA_SetModulo(DMA0,DMA_CHN,s_addr_modulo,kEDMA_ModuloDisable);
    EDMA_StartTransfer(&g_EDMA_Handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO初始化为CSI(摄像头)接口
//  @param      dat_pin_start   摄像头数据接口的起始位
//  @param      pclk_pin        像素时钟的引脚
//  @param      href_pin        行信号的引脚
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_init(flexio_pin_enum dat_pin_start, flexio_pin_enum pclk_pin, flexio_pin_enum href_pin, uint16 width, uint16 height, uint8 *dest_addr, edma_callback callback)
{
    flexio_iomuxc(dat_pin_start,pclk_pin,href_pin);
    
    if(width * height>=(376*240))   flexio_shift_count = 2;
    else                            flexio_shift_count = 1;
    
    s_FlexioCameraDevice.flexioBase = FLEXIO2;                  // 设置基地址
    s_FlexioCameraDevice.datPinStartIdx = dat_pin_start;        // 设置数据引脚起始位
    s_FlexioCameraDevice.pclkPinIdx = pclk_pin;                 // 设置像素时钟引脚
    s_FlexioCameraDevice.hrefPinIdx = href_pin;                 // 设置行信号引脚
    s_FlexioCameraDevice.shifterStartIdx = 4-flexio_shift_count;// 设置环移器起始编号  由于1064的缓冲区只有四个因此这里写的是4-
    s_FlexioCameraDevice.shifterCount = flexio_shift_count;     // 设置缓冲区数量
    s_FlexioCameraDevice.timerIdx = 3;                          // 设置定时器编号
    
    CLOCK_EnableClock(kCLOCK_Flexio2);
    FLEXIO_Reset(FLEXIO2);
    FLEXIO_CAMERA_GetDefaultConfig(&s_FlexioCameraConfig);
    FLEXIO_CAMERA_Init(&s_FlexioCameraDevice, &s_FlexioCameraConfig);
    FLEXIO_CAMERA_ClearStatusFlags(&s_FlexioCameraDevice, kFLEXIO_CAMERA_RxDataRegFullFlag | kFLEXIO_CAMERA_RxErrorFlag);
    FLEXIO_CAMERA_Enable(&s_FlexioCameraDevice, true);
    
    flexio_csi_dma_init(dest_addr, width * height, callback);
}
