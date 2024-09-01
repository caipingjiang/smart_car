/*********************************************************************************************************************
* MCX Vision Opensourec Library 即（MCX Vision 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2024 SEEKFREE 逐飞科技
* 
* 本文件是 MCX Vision 开源库的一部分
* 
* MCX Vision 开源库 是免费软件
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
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_driver_sd
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.38a
* 适用平台          MCX Vision
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_driver_sd.h"

/*! @brief Data block count accessed in card */
#define DATA_BLOCK_COUNT (5U)
/*! @brief Start data block number accessed in card */
#define DATA_BLOCK_START (2U)
/*! @brief Data buffer size. */
#define DATA_BUFFER_SIZE (FSL_SDMMC_DEFAULT_BLOCK_SIZE * DATA_BLOCK_COUNT)

/*! @brief Data written to the card */
SDK_ALIGN(uint8_t g_dataWrite[DATA_BUFFER_SIZE], BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
/*! @brief Data read from the card */
SDK_ALIGN(uint8_t g_dataRead[DATA_BUFFER_SIZE], BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
sd_card_t g_sd;

static void CardInformationLog(sd_card_t *card)
{
    assert(card);
    zf_debug_printf("card size %d * %d bytes\r\n", card->blockCount, card->blockSize);
    zf_debug_printf("working condition:\r\n");
    if (card->operationVoltage == kSDMMC_OperationVoltage330V)
    {
        zf_debug_printf("voltage : 3.3V\r\n");
    }
    else if (card->operationVoltage == kSDMMC_OperationVoltage180V)
    {
        zf_debug_printf("voltage : 1.8V\r\n");
    }

    if (card->currentTiming == kSD_TimingSDR12DefaultMode)
    {
        if (card->operationVoltage == kSDMMC_OperationVoltage330V)
        {
            zf_debug_printf("timing mode: default mode\r\n");
        }
        else if (card->operationVoltage == kSDMMC_OperationVoltage180V)
        {
            zf_debug_printf("timing mode: sdr12 mode\r\n");
        }
    }
    else if (card->currentTiming == kSD_TimingSDR25HighSpeedMode)
    {
        if (card->operationVoltage == kSDMMC_OperationVoltage180V)
        {
            zf_debug_printf("timing mode: sdr25\r\n");
        }
        else
        {
            zf_debug_printf("timing mode: high speed\r\n");
        }
    }
    else if (card->currentTiming == kSD_TimingSDR50Mode)
    {
        zf_debug_printf("timing mode: sdr50\r\n");
    }
    else if (card->currentTiming == kSD_TimingSDR104Mode)
    {
        zf_debug_printf("timing mode: sdr104\r\n");
    }
    else if (card->currentTiming == kSD_TimingDDR50Mode)
    {
        zf_debug_printf("timing mode: ddr50\r\n");
    }

    zf_debug_printf("freq : %d hz\r\n", card->busClock_Hz);
}

void rw_card_test()
{
    if(g_sd.usrParam.cd->cardDetected() != true)
    {
        zf_debug_printf("\r\nSD card not detected\r\n");
        return;
    }
    
    memset(g_dataWrite, 0x67U, sizeof(g_dataWrite));

    zf_debug_printf("\r\nwrite/read one data block......\r\n");
    if (kStatus_Success != SD_WriteBlocks(&g_sd, g_dataWrite, DATA_BLOCK_START, 1U))
    {
        zf_debug_printf("write one data block failed.\r\n");
        return;
    }

    memset(g_dataRead, 0U, sizeof(g_dataRead));
    if (kStatus_Success != SD_ReadBlocks(&g_sd, g_dataRead, DATA_BLOCK_START, 1U))
    {
        zf_debug_printf("read one data block failed.\r\n");
        return;
    }

    zf_debug_printf("compare the read/write content......\r\n");
    if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
    {
        zf_debug_printf("the read/write content isn't consistent.\r\n");
        return;
    }
    zf_debug_printf("the read/write content is consistent.\r\n");

    zf_debug_printf("write/read multiple data blocks......\r\n");
    if (kStatus_Success != SD_WriteBlocks(&g_sd, g_dataWrite, DATA_BLOCK_START, DATA_BLOCK_COUNT))
    {
        zf_debug_printf("Write multiple data blocks failed.\r\n");
        return;
    }

    memset(g_dataRead, 0U, sizeof(g_dataRead));

    if (kStatus_Success != SD_ReadBlocks(&g_sd, g_dataRead, DATA_BLOCK_START, DATA_BLOCK_COUNT))
    {
        zf_debug_printf("read multiple data blocks failed.\r\n");
        return;
    }

    zf_debug_printf("compare the read/write content......\r\n");
    if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE))
    {
        zf_debug_printf("the read/write content isn't consistent.\r\n");
        return;
    }
    zf_debug_printf("the read/write content is consistent.\r\n");

    zf_debug_printf("erase multiple data blocks......\r\n");
    if (kStatus_Success != SD_EraseBlocks(&g_sd, DATA_BLOCK_START, DATA_BLOCK_COUNT))
    {
        zf_debug_printf("erase multiple data blocks failed.\r\n");
        return;
    }

    zf_debug_printf("rw_card_test success!\r\n");
}



bool sd_card_init(void)
{   
    /* attach FRO HF to USDHC */
    CLOCK_SetClkDiv(kCLOCK_DivUSdhcClk, 1u);
    CLOCK_AttachClk(kFRO_HF_to_USDHC);
    
    CLOCK_EnableClock(kCLOCK_Gpio2);
    CLOCK_EnableClock(kCLOCK_Port2);
    const port_pin_config_t port2_1_pinH1_config = {/* Internal pull-up/down resistor is disabled */
                                                kPORT_PullDisable,
                                                /* Low internal pull resistor value is selected. */
                                                kPORT_LowPullResistor,
                                                /* Fast slew rate is configured */
                                                kPORT_FastSlewRate,
                                                /* Passive input filter is disabled */
                                                kPORT_PassiveFilterDisable,
                                                /* Open drain output is disabled */
                                                kPORT_OpenDrainDisable,
                                                /* Low drive strength is configured */
                                                kPORT_LowDriveStrength,
                                                /* Pin is configured as PIO2_1 */
                                                kPORT_MuxAlt0,
                                                /* Digital input enabled */
                                                kPORT_InputBufferEnable,
                                                /* Digital input is not inverted */
                                                kPORT_InputNormal,
                                                /* Pin Control Register fields [15:0] are not locked */
                                                kPORT_UnlockRegister};
    /* PORT2_1 (pin H1) is configured as PIO2_1 */
    PORT_SetPinConfig(PORT2, 1U, &port2_1_pinH1_config);

    const port_pin_config_t port2_2_pinH3_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as SDHC0_D1 */
                                                    kPORT_MuxAlt3,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT2_2 (pin H3) is configured as SDHC0_D1 */
    PORT_SetPinConfig(PORT2, 2U, &port2_2_pinH3_config);

    const port_pin_config_t port2_3_pinJ3_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as SDHC0_D0 */
                                                    kPORT_MuxAlt3,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT2_3 (pin J3) is configured as SDHC0_D0 */
    PORT_SetPinConfig(PORT2, 3U, &port2_3_pinJ3_config);

    const port_pin_config_t port2_4_pinK3_config = {/* Internal pull-up/down resistor is disabled */
                                                    kPORT_PullDisable,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as SDHC0_CLK */
                                                    kPORT_MuxAlt3,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT2_4 (pin K3) is configured as SDHC0_CLK */
    PORT_SetPinConfig(PORT2, 4U, &port2_4_pinK3_config);

    const port_pin_config_t port2_5_pinK1_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as SDHC0_CMD */
                                                    kPORT_MuxAlt3,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT2_5 (pin K1) is configured as SDHC0_CMD */
    PORT_SetPinConfig(PORT2, 5U, &port2_5_pinK1_config);

    const port_pin_config_t port2_6_pinK2_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as SDHC0_D3 */
                                                    kPORT_MuxAlt3,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT2_6 (pin K2) is configured as SDHC0_D3 */
    PORT_SetPinConfig(PORT2, 6U, &port2_6_pinK2_config);

    const port_pin_config_t port2_7_pinL2_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Pin is configured as SDHC0_D2 */
                                                    kPORT_MuxAlt3,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT2_7 (pin L2) is configured as SDHC0_D2 */
    PORT_SetPinConfig(PORT2, 7U, &port2_7_pinL2_config);
                                        
    BOARD_SD_Config(&g_sd, NULL, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    SD_HostInit(&g_sd);
    
    if(g_sd.usrParam.cd->cardDetected() != true)
    {
        zf_debug_printf("\r\nSD card not detected\r\n");
        return false;
    }
    
    if (SD_PollingCardInsert(&g_sd, kSD_Inserted) != kStatus_Success)
    {
        zf_debug_printf("\r\nSD card init failed.\r\n");
        return false;
    }
    /* power off card */
    SD_SetCardPower(&g_sd, false);
    /* power on the card */
    SD_SetCardPower(&g_sd, true);
    
    if (SD_CardInit(&g_sd))
    {
        zf_debug_printf("\r\nSD card init failed.\r\n");
        return false;
    }
    else
    {
        zf_debug_printf("\r\nSD card init success.\r\n");
        CardInformationLog(&g_sd);    
        return true; 
    }     
    return true;                                    
}