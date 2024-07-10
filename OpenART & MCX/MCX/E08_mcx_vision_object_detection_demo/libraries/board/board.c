/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif /* SDK_I2C_BASED_COMPONENT_USED */
#if defined(LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER) && LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER
#include "fsl_lpflexcomm.h"
#endif /* LPFLEXCOMM_INIT_NOT_USED_IN_DRIVER */
#include "fsl_spc.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */

/* Update Active mode voltage for OverDrive mode. */
void BOARD_PowerMode_OD(void)
{
    spc_active_mode_dcdc_option_t opt = {
        .DCDCVoltage       = kSPC_DCDC_OverdriveVoltage,
        .DCDCDriveStrength = kSPC_DCDC_NormalDriveStrength,
    };
    SPC_SetActiveModeDCDCRegulatorConfig(SPC0, &opt);

    spc_sram_voltage_config_t cfg = {
        .operateVoltage       = kSPC_sramOperateAt1P2V,
        .requestVoltageUpdate = true,
    };
    SPC_SetSRAMOperateVoltage(SPC0, &cfg);
}
