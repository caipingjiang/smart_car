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
* 文件名称          zf_driver_sdio
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


#include "fsl_debug_console.h"
#include "fsl_sd_disk.h"
#include "fsl_sd.h"
#include "fsl_iomuxc.h"
#include "sdmmc_config.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_delay.h"

#include "zf_driver_sdio.h"

#define SDHC_PIN_CONF   SPEED_200MHZ | PULL_EN | PULLUP_47K | DSE_R0 | SRE_FAST

void sdhc_iomuxc(void)
{
    
    gpio_iomuxc(B23, SPEED_200MHZ | KEEPER_EN | PULLDOWN_100K | DSE_R0_6);  // 电源使能引脚
    gpio_iomuxc(D4 , SDHC_PIN_CONF);                                        // 插入检测引脚
    
    afio_init(IOMUXC_GPIO_B1_14_USDHC1_VSELECT,  0, SDHC_PIN_CONF);         // 电压切换引脚
    afio_init(IOMUXC_GPIO_SD_B0_00_USDHC1_CMD,   0, SDHC_PIN_CONF);         // CMD
    afio_init(IOMUXC_GPIO_SD_B0_01_USDHC1_CLK,   0, SDHC_PIN_CONF);         // CLK
    afio_init(IOMUXC_GPIO_SD_B0_02_USDHC1_DATA0, 0, SDHC_PIN_CONF);         // DATA0
    afio_init(IOMUXC_GPIO_SD_B0_03_USDHC1_DATA1, 0, SDHC_PIN_CONF);         // DATA1
    afio_init(IOMUXC_GPIO_SD_B0_04_USDHC1_DATA2, 0, SDHC_PIN_CONF);         // DATA2
    afio_init(IOMUXC_GPIO_SD_B0_05_USDHC1_DATA3, 0, SDHC_PIN_CONF);         // DATA3
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     sdio 初始化SDHC时钟并等待SD卡插入
// 参数说明     void
// 返回参数     void
// 使用示例                     sdio_init();
//-------------------------------------------------------------------------------------------------------------------
void sdio_init (void)
{
    
    sdhc_iomuxc();
    
    BOARD_SD_Config(&g_sd, NULL, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    if (SD_HostInit(&g_sd) != kStatus_Success)
    {
        zf_assert(0);
    }

    if (SD_PollingCardInsert(&g_sd, kSD_Inserted) == kStatus_Success)
    {
        SD_SetCardPower(&g_sd, false);
        SD_SetCardPower(&g_sd, true);
    }
    else
    {
        zf_assert(0);
    }
}
