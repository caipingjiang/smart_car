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
* 文件名称          zf_driver_csi
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

#include "fsl_iomuxc.h"
#include "zf_driver_gpio.h"

#include "zf_driver_csi.h"

#define CSI_PIN_CONF    SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //配置CSI引脚默认配置   

csi_handle_t            csi_handle;                         //csi事务结构体


void csi_iomuxc(vsync_pin_enum vsync, pixclk_pin_enum pixclk)
{
    //数据端口引脚复用设置
    afio_init(IOMUXC_GPIO_AD_B1_08_CSI_DATA09, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_09_CSI_DATA08, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_10_CSI_DATA07, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_11_CSI_DATA06, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_12_CSI_DATA05, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_13_CSI_DATA04, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_14_CSI_DATA03, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_15_CSI_DATA02, 0, CSI_PIN_CONF);
    
    if      (CSI_VSYNC_B14 == vsync)    afio_init(IOMUXC_GPIO_AD_B0_14_CSI_VSYNC,   0, CSI_PIN_CONF);
    else if (CSI_VSYNC_B22 == vsync)    afio_init(IOMUXC_GPIO_AD_B1_06_CSI_VSYNC,   0, CSI_PIN_CONF);
    else if (CSI_VSYNC_C29 == vsync)    afio_init(IOMUXC_GPIO_B1_13_CSI_VSYNC,      0, CSI_PIN_CONF);
                                                       
    if      (CSI_PIXCLK_B20 == pixclk)  afio_init(IOMUXC_GPIO_AD_B1_04_CSI_PIXCLK,  0, CSI_PIN_CONF);
    else if (CSI_PIXCLK_C28 == pixclk)  afio_init(IOMUXC_GPIO_B1_12_CSI_PIXCLK,     0, CSI_PIN_CONF);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI添加空缓冲区地址
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @param      *buff       缓冲区的首地址
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_add_empty_buffer(csi_handle_t *handle, uint8 *buff)
{
    CSI_TransferSubmitEmptyBuffer(CSI,handle,(uint32_t)buff);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI获取采集完成的缓冲区地址
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @param      buffaddr    获取到的地址
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
uint8 csi_get_full_buffer(csi_handle_t *handle, uint32 *buffaddr)
{
    if(kStatus_Success == CSI_TransferGetFullBuffer(CSI,handle,(uint32_t *)buffaddr))
    {
        return 1;//获取到采集完成的BUFFER
    }
    return 0;    //未采集完成
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI启动
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_start(csi_handle_t *handle)
{
    CSI_TransferStart(CSI,handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI停止
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_stop(csi_handle_t *handle)
{
    CSI_TransferStop(CSI,handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI初始化
//  @param      width       图像的列
//  @param      height      图像的行
//  @param      handle      CSI的handle结构体 在MT9V032_CSI已经定义好了
//  @param      callback    中断的时候的回调函数
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_init(uint16 width, uint16 height, csi_handle_t *handle, csi_transfer_callback_t callback, vsync_pin_enum vsync, pixclk_pin_enum pixclk, pixclk_polarity_enum pixclk_polarity)
{
    uint16 i;
    uint32 pixel_num;
    uint16 temp_width;
    uint16 temp_height=0;
    csi_config_t csi_config;

    csi_iomuxc(vsync,pixclk);
    
    //CSI 采集初始化
    CLOCK_SetMux(kCLOCK_CsiMux, 2);
    CLOCK_SetDiv(kCLOCK_CsiDiv, 0);
        
    //摄像头采集初始化
    pixel_num = width*height;
    if(pixel_num%8) assert(0);//像素点不是8的倍数 无法采集
    if(width%8)
    {
        temp_width = width - width%8;//储存临时宽度
        i=1;
        while(pixel_num>(temp_width+(i*8)))
        {
            if(!(pixel_num%((temp_width+(i*8))))) 
            {
                temp_width += (i*8);//储存临时宽度
                temp_height = pixel_num/temp_width;
                break;
            }
            i++;
        }
        if(!temp_height)
        {
            //如果没有找到则从临时宽度往下找
            i=1;
            while((temp_width-(i*8)))
            {
                if(!(pixel_num%((temp_width-(i*8))))) 
                {
                    temp_width -= (i*8);//储存临时宽度
                    temp_height = pixel_num/temp_width;
                    break;
                }
                i++;
            }
        }
        if(!temp_height)
        {
            //如果还是没有找到
            temp_width = pixel_num;
            temp_height = 1;
        }
    }
    else
    {
        temp_width = width;
        temp_height = height;
    }
    
    CSI_GetDefaultConfig(&csi_config);
    csi_config.width = temp_width;
    csi_config.height = temp_height;
    csi_config.polarityFlags = pixclk_polarity;
    csi_config.bytesPerPixel = 1U;
    csi_config.linePitch_Bytes = temp_width;
    csi_config.workMode = kCSI_NonGatedClockMode;
    csi_config.dataBus = kCSI_DataBus8Bit;
    csi_config.useExtVsync = true;
    CSI_Init(CSI, &csi_config);
    CSI_TransferCreateHandle(CSI,handle, callback, NULL);
}