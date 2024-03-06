/*!
*******************************************************************************
**
** \file      gh_audio.h
**
** \brief     Audio Interface..
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_AUDIO_H
#define _GH_AUDIO_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_AUDIO_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_AUDIO_DEBUG_PRINT_FUNCTION printk
#else
#define GH_AUDIO_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_AUDIO_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_AUDIO_AHB_GENERAL0                              FIO_ADDRESS(AUDIO,0x90020E00) /* read/write */
#define REG_AUDIO_AHB_GENERAL1                              FIO_ADDRESS(AUDIO,0x90020E04) /* read/write */
#define REG_AUDIO_CKG_CTRL0                                 FIO_ADDRESS(AUDIO,0x90020C00) /* read/write */
#define REG_AUDIO_SYS_RST_CTRL0                             FIO_ADDRESS(AUDIO,0x90020C04) /* read/write */
#define REG_AUDIO_TIMING_CTRL0                              FIO_ADDRESS(AUDIO,0x90020C08) /* read/write */
#define REG_AUDIO_TIMING_CTRL1                              FIO_ADDRESS(AUDIO,0x90020C0C) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL0                           FIO_ADDRESS(AUDIO,0x90020C10) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL1                           FIO_ADDRESS(AUDIO,0x90020C14) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL2                           FIO_ADDRESS(AUDIO,0x90020C18) /* read/write */
#define REG_AUDIO_AUDIOBAND_STS                             FIO_ADDRESS(AUDIO,0x90020C1C) /* read */
#define REG_AUDIO_AUDIOBAND_STS2                            FIO_ADDRESS(AUDIO,0x90020C20) /* read */
#define REG_AUDIO_SINE_GEN_CTRL0                            FIO_ADDRESS(AUDIO,0x90020C24) /* read/write */
#define REG_AUDIO_SINE_GEN_CTRL1                            FIO_ADDRESS(AUDIO,0x90020C28) /* read/write */
#define REG_AUDIO_TEST_CTRL0                                FIO_ADDRESS(AUDIO,0x90020C30) /* read/write */
#define REG_AUDIO_SDM_CTRL0                                 FIO_ADDRESS(AUDIO,0x90020C34) /* read/write */
#define REG_AUDIO_SDM_CTRL1                                 FIO_ADDRESS(AUDIO,0x90020C38) /* read/write */
#define REG_AUDIO_NF_SYNTH_1_NF_H                           FIO_ADDRESS(AUDIO,0x90020C3C) /* read/write */
#define REG_AUDIO_NF_SYNTH_1_NF_L                           FIO_ADDRESS(AUDIO,0x90020C40) /* read/write */
#define REG_AUDIO_NF_SYNTH_2_NF_H                           FIO_ADDRESS(AUDIO,0x90020C44) /* read/write */
#define REG_AUDIO_NF_SYNTH_2_NF_L                           FIO_ADDRESS(AUDIO,0x90020C48) /* read/write */
#define REG_AUDIO_DIG_MIC_CTRL                              FIO_ADDRESS(AUDIO,0x90020C4C) /* read/write */
#define REG_AUDIO_MIX_CTRL0                                 FIO_ADDRESS(AUDIO,0x90020C50) /* read/write */
#define REG_AUDIO_SDM_DWA_DATAIN_L                          FIO_ADDRESS(AUDIO,0x90020C54) /* read */
#define REG_AUDIO_SDM_DWA_DATAIN_R                          FIO_ADDRESS(AUDIO,0x90020C58) /* read */
#define REG_AUDIO_VALID_SIGNALS                             FIO_ADDRESS(AUDIO,0x90020C5C) /* read */
#define REG_AUDIO_MMP_DPGA_CFG1                             FIO_ADDRESS(AUDIO,0x90020C60) /* read/write */
#define REG_AUDIO_MMP_DPGA_CFG2                             FIO_ADDRESS(AUDIO,0x90020C64) /* read/write */
#define REG_AUDIO_PGA_DPGA_CFG                              FIO_ADDRESS(AUDIO,0x90020C68) /* read/write */
#define REG_AUDIO_INT_DOUT                                  FIO_ADDRESS(AUDIO,0x90020C74) /* read */
#define REG_AUDIO_FIFO_TH_CTRL0                             FIO_ADDRESS(AUDIO,0x90020C7C) /* read/write */
#define REG_AUDIO_FIFO_CTRL                                 FIO_ADDRESS(AUDIO,0x90020C80) /* read/write */
#define REG_AUDIO_FIFO_STS                                  FIO_ADDRESS(AUDIO,0x90020C84) /* read */
#define REG_AUDIO_NF_SYNTH_5_NF_H                           FIO_ADDRESS(AUDIO,0x90020C88) /* read */
#define REG_AUDIO_NF_SYNTH_5_NF_L                           FIO_ADDRESS(AUDIO,0x90020C8C) /* read */
#define REG_AUDIO_INT_CTRL                                  FIO_ADDRESS(AUDIO,0x90020C90) /* read */
#define REG_AUDIO_ANALOG_CTRL00                             FIO_ADDRESS(AUDIO,0x90021C00) /* read/write */
#define REG_AUDIO_ANALOG_CTRL01                             FIO_ADDRESS(AUDIO,0x90021C04) /* read/write */
#define REG_AUDIO_ANALOG_CTRL02                             FIO_ADDRESS(AUDIO,0x90021C08) /* read/write */
#define REG_AUDIO_ANALOG_CTRL03                             FIO_ADDRESS(AUDIO,0x90021C0C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL04                             FIO_ADDRESS(AUDIO,0x90021C10) /* read/write */
#define REG_AUDIO_ANALOG_CTRL05                             FIO_ADDRESS(AUDIO,0x90021C14) /* read/write */
#define REG_AUDIO_ANALOG_CTRL06                             FIO_ADDRESS(AUDIO,0x90021C18) /* read/write */
#define REG_AUDIO_ANALOG_CTRL07                             FIO_ADDRESS(AUDIO,0x90021C1C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL08                             FIO_ADDRESS(AUDIO,0x90021C20) /* read/write */
#define REG_AUDIO_ANALOG_CTRL09                             FIO_ADDRESS(AUDIO,0x90021C24) /* read/write */
#define REG_AUDIO_ANALOG_CTRL10                             FIO_ADDRESS(AUDIO,0x90021C28) /* read/write */
#define REG_AUDIO_ANALOG_CTRL11                             FIO_ADDRESS(AUDIO,0x90021C2C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL12                             FIO_ADDRESS(AUDIO,0x90021C30) /* read/write */
#define REG_AUDIO_ANALOG_CTRL13                             FIO_ADDRESS(AUDIO,0x90021C34) /* read/write */
#define REG_AUDIO_ANALOG_CTRL14                             FIO_ADDRESS(AUDIO,0x90021C38) /* read/write */
#define REG_AUDIO_ANALOG_CTRL15                             FIO_ADDRESS(AUDIO,0x90021C3C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL16                             FIO_ADDRESS(AUDIO,0x90021C40) /* read/write */
#define REG_AUDIO_ANALOG_CTRL17                             FIO_ADDRESS(AUDIO,0x90021C44) /* read/write */
#define REG_AUDIO_ANALOG_CTRL18                             FIO_ADDRESS(AUDIO,0x90021C48) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* AUDIO_AHB_GENERAL0 */
    U16 all;
    struct {
        U16 usb_tm1                     : 1;
        U16 ahb_rmii_sel                : 1;
        U16                             : 14;
    } bitc;
} GH_AUDIO_AHB_GENERAL0_S;

typedef union { /* AUDIO_AHB_GENERAL1 */
    U16 all;
    struct {
        U16 audio_i2s_sel               : 1;
        U16                             : 15;
    } bitc;
} GH_AUDIO_AHB_GENERAL1_S;

typedef union { /* AUDIO_CKG_CTRL0 */
    U16 all;
    struct {
        U16 au_src1_mac_48m_dyng_en     : 1;
        U16                             : 15;
    } bitc;
} GH_AUDIO_CKG_CTRL0_S;

typedef union { /* AUDIO_SYS_RST_CTRL0 */
    U16 all;
    struct {
        U16                             : 13;
        U16 reset_sdm_sync              : 1;
        U16 reset_dpga_sync             : 1;
        U16 reset_au_sync               : 1;
    } bitc;
} GH_AUDIO_SYS_RST_CTRL0_S;

typedef union { /* AUDIO_TIMING_CTRL0 */
    U16 all;
    struct {
        U16 en_time_gen_p               : 1;
        U16 en_dec_1_p                  : 1;
        U16 en_dec_2_p                  : 1;
        U16 en_int_1_p                  : 1;
        U16 en_int_2_p                  : 1;
        U16 en_asrc1_p                  : 1;
        U16                             : 2;
        U16 dec_num                     : 2;
        U16 dac_sync_sel                : 1;
        U16 adc_sync_sel                : 1;
        U16 sync_clk2_sel               : 2;
        U16 sync_clk1_sel               : 2;
    } bitc;
} GH_AUDIO_TIMING_CTRL0_S;

typedef union { /* AUDIO_TIMING_CTRL1 */
    U16 all;
    struct {
        U16                             : 8;
        U16 dec_num2                    : 2;
        U16                             : 1;
        U16 en_asrc3_p                  : 1;
        U16                             : 2;
        U16 ch2_int_cnt_sync_sel        : 1;
        U16 ch1_int_cnt_sync_sel        : 1;
    } bitc;
} GH_AUDIO_TIMING_CTRL1_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL0 */
    U16 all;
    struct {
        U16 ini_sram                    : 1;
        U16 ch12_sync_enable            : 1;
        U16                             : 10;
        U16 ch2_int_128fs_nf_sel        : 1;
        U16 ch1_int_128fs_nf_sel        : 1;
        U16                             : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL0_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL1 */
    U16 all;
    struct {
        U16                             : 10;
        U16 sdm_dwa_datain_r_sel        : 2;
        U16 sdm_dwa_datain_l_sel        : 2;
        U16                             : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL1_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL2 */
    U16 all;
    struct {
        U16                             : 2;
        U16 en_dec_4_p                  : 1;
        U16 en_dec_3_p                  : 1;
        U16                             : 4;
        U16 nt4_mix_ctrl                : 2;
        U16 nt3_mix_ctrl                : 2;
        U16                             : 2;
        U16 dec_num3                    : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL2_S;

typedef union { /* AUDIO_AUDIOBAND_STS */
    U16 all;
    struct {
        U16 quant_out_r                 : 6;
        U16 quant_out_l                 : 6;
        U16                             : 4;
    } bitc;
} GH_AUDIO_AUDIOBAND_STS_S;

typedef union { /* AUDIO_AUDIOBAND_STS2 */
    U16 all;
    struct {
        U16 pga_status                  : 2;
        U16 mmp2_mute_done              : 1;
        U16 mmp1_mute_done              : 1;
        U16 pnt_mmc_dec_err_clr         : 1;
        U16                             : 3;
        U16 dpga_status                 : 7;
        U16                             : 1;
    } bitc;
} GH_AUDIO_AUDIOBAND_STS2_S;

typedef union { /* AUDIO_SINE_GEN_CTRL0 */
    U16 all;
    struct {
        U16 ch1_sin_gen_en_p            : 1;
        U16 ch2_sin_gen_en_p            : 1;
        U16 en_dit_sine                 : 1;
        U16 en_dit_src                  : 1;
        U16                             : 2;
        U16 pga2_swap                   : 1;
        U16 pga1_swap                   : 1;
        U16                             : 4;
        U16 int2_mix_ctrl               : 2;
        U16 int1_mix_ctrl               : 2;
    } bitc;
} GH_AUDIO_SINE_GEN_CTRL0_S;

typedef union { /* AUDIO_SINE_GEN_CTRL1 */
    U16 all;
    struct {
        U16 sine_gen_ch1_freq           : 4;
        U16 sine_gen_ch1_gain           : 4;
        U16 sine_gen_ch2_freq           : 4;
        U16 sine_gen_ch2_gain           : 4;
    } bitc;
} GH_AUDIO_SINE_GEN_CTRL1_S;

typedef union { /* AUDIO_TEST_CTRL0 */
    U16 all;
    struct {
        U16 dac_test_en                 : 1;
        U16 sdm_test_en                 : 1;
        U16 sdm_sft_dis                 : 1;
        U16 sram_cg_en                  : 1;
        U16 testclk_sel                 : 6;
        U16                             : 2;
        U16 testbus_sel                 : 4;
    } bitc;
} GH_AUDIO_TEST_CTRL0_S;

typedef union { /* AUDIO_SDM_CTRL0 */
    U16 all;
    struct {
        U16 en_sdm_p                    : 1;
        U16 fs_synth_sel_p              : 1;
        U16 dac_din_l_sel               : 2;
        U16 dac_din_r_sel               : 2;
        U16 fix_msb_en                  : 1;
        U16 fix_msb_sel                 : 5;
        U16 dither_en_p                 : 1;
        U16 dither_sel                  : 3;
    } bitc;
} GH_AUDIO_SDM_CTRL0_S;

typedef union { /* AUDIO_SDM_CTRL1 */
    U16 all;
    struct {
        U16 sdm_offset                  : 16;
    } bitc;
} GH_AUDIO_SDM_CTRL1_S;

typedef union { /* AUDIO_NF_SYNTH_1_NF_H */
    U16 all;
    struct {
        U16 value                       : 14;
        U16 trig                        : 2;
    } bitc;
} GH_AUDIO_NF_SYNTH_1_NF_H_S;

typedef union { /* AUDIO_NF_SYNTH_1_NF_L */
    U16 all;
    struct {
        U16 value                       : 16;
    } bitc;
} GH_AUDIO_NF_SYNTH_1_NF_L_S;

typedef union { /* AUDIO_NF_SYNTH_2_NF_H */
    U16 all;
    struct {
        U16 value                       : 14;
        U16                             : 1;
        U16 trig                        : 1;
    } bitc;
} GH_AUDIO_NF_SYNTH_2_NF_H_S;

typedef union { /* AUDIO_NF_SYNTH_2_NF_L */
    U16 all;
    struct {
        U16 value                       : 16;
    } bitc;
} GH_AUDIO_NF_SYNTH_2_NF_L_S;

typedef union { /* AUDIO_DIG_MIC_CTRL */
    U16 all;
    struct {
        U16 pga_status_clr              : 1;
        U16 dpga_status_clr             : 1;
        U16 pnt_mmc3_dec_sync_enz       : 1;
        U16 pnt_mmc1_dec_sync_enz       : 1;
        U16                             : 1;
        U16 pnt_mmc_dec_err_clr         : 1;
        U16                             : 10;
    } bitc;
} GH_AUDIO_DIG_MIC_CTRL_S;

typedef union { /* AUDIO_MIX_CTRL0 */
    U16 all;
    struct {
        U16                             : 2;
        U16 ch2_mux_sel                 : 2;
        U16 ch1_mux_sel                 : 2;
        U16                             : 8;
        U16 sel_dec2_dout               : 1;
        U16 sel_dec1_dout               : 1;
    } bitc;
} GH_AUDIO_MIX_CTRL0_S;

typedef union { /* AUDIO_SDM_DWA_DATAIN_L */
    U16 all;
    struct {
        U16 data                        : 16;
    } bitc;
} GH_AUDIO_SDM_DWA_DATAIN_L_S;

typedef union { /* AUDIO_SDM_DWA_DATAIN_R */
    U16 all;
    struct {
        U16 data                        : 16;
    } bitc;
} GH_AUDIO_SDM_DWA_DATAIN_R_S;

typedef union { /* AUDIO_VALID_SIGNALS */
    U16 all;
    struct {
        U16 valid_signals               : 16;
    } bitc;
} GH_AUDIO_VALID_SIGNALS_S;

typedef union { /* AUDIO_MMP_DPGA_CFG1 */
    U16 all;
    struct {
        U16 dpga_en                     : 1;
        U16 fading_en                   : 1;
        U16 mute_2_zero                 : 1;
        U16 step                        : 3;
        U16 offset                      : 5;
        U16                             : 5;
    } bitc;
} GH_AUDIO_MMP_DPGA_CFG1_S;

typedef union { /* AUDIO_MMP_DPGA_CFG2 */
    U16 all;
    struct {
        U16 gain                        : 8;
        U16 gain_trig                   : 1;
        U16                             : 7;
    } bitc;
} GH_AUDIO_MMP_DPGA_CFG2_S;

typedef union { /* AUDIO_PGA_DPGA_CFG */
    U16 all;
    struct {
        U16 pga2_gain                   : 5;
        U16 pga2_gain_trig              : 1;
        U16 pga2_mute                   : 1;
        U16 pga2_en                     : 1;
        U16 pga1_gain                   : 5;
        U16 pga1_gain_trig              : 1;
        U16 pga1_mute                   : 1;
        U16 pga1_en                     : 1;
    } bitc;
} GH_AUDIO_PGA_DPGA_CFG_S;

typedef union { /* AUDIO_FIFO_TH_CTRL0 */
    U16 all;
    struct {
        U16 tx                          : 7;
        U16                             : 1;
        U16 rx                          : 7;
        U16                             : 1;
    } bitc;
} GH_AUDIO_FIFO_TH_CTRL0_S;

typedef union { /* AUDIO_FIFO_CTRL */
    U16 all;
    struct {
        U16 tx_fifo_int_en              : 4;
        U16 tx_fifo_enable              : 1;
        U16                             : 2;
        U16 tx_fifo_status_clr          : 1;
        U16 rx_fifo_int_en              : 4;
        U16 rx_fifo_enable              : 1;
        U16                             : 2;
        U16 rx_fifo_status_clr          : 1;
    } bitc;
} GH_AUDIO_FIFO_CTRL_S;

typedef union { /* AUDIO_FIFO_STS */
    U16 all;
    struct {
        U16 tx_fifo_status              : 4;
        U16 rx_fifo_status              : 4;
        U16                             : 8;
    } bitc;
} GH_AUDIO_FIFO_STS_S;

typedef union { /* AUDIO_ANALOG_CTRL00 */
    U16 all;
    struct {
        U16 dbnc_time                   : 2;
        U16 mcpls_sel                   : 2;
        U16 mcpls_prd                   : 3;
        U16                             : 5;
        U16 _rstz_au_det                : 1;
        U16 int_au_det_test_value       : 1;
        U16 int_au_det_test_mode        : 1;
        U16 mcpls_en                    : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL00_S;

typedef union { /* AUDIO_ANALOG_CTRL01 */
    U16 all;
    struct {
        U16                             : 1;
        U16 int_mask_miclp_plugin       : 1;
        U16 int_mask_miclp_unplug       : 1;
        U16 int_mask_spk_plugin         : 1;
        U16 int_mask_spk_unplug         : 1;
        U16 int_mask_hs_plugin          : 1;
        U16 int_mask_hs_unplug          : 1;
        U16 int_mask_hs_gnd             : 1;
        U16                             : 1;
        U16 int_clr_miclp_plugin        : 1;
        U16 int_clr_miclp_unplug        : 1;
        U16 int_clr_spk_plugin          : 1;
        U16 int_clr_spk_unplug          : 1;
        U16 int_clr_hs_plugin           : 1;
        U16 int_clr_hs_unplug           : 1;
        U16 int_clr_hs_gnc              : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL01_S;

typedef union { /* AUDIO_ANALOG_CTRL02 */
    U16 all;
    struct {
        U16                             : 3;
        U16 sdm_out_3_4_12_sel          : 1;
        U16 sdm_out_1_2_12_sel          : 1;
        U16 sdm_out_3_4_12_swap_sel     : 1;
        U16 sdm_out_1_2_12_swap_sel     : 1;
        U16 sdm_out_4_12_inv_sel        : 1;
        U16 sdm_out_3_12_inv_sel        : 1;
        U16 sdm_out_2_12_inv_sel        : 1;
        U16 sdm_out_1_12_inv_sel        : 1;
        U16                             : 4;
        U16 dft_sel                     : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL02_S;

typedef union { /* AUDIO_ANALOG_CTRL03 */
    U16 all;
    struct {
        U16 sel_irefdet                 : 2;
        U16 reg_en_micbias_12           : 1;
        U16 micv_sel                    : 2;
        U16 rcv_en_12                   : 1;
        U16 hst_en_12                   : 1;
        U16 en_micdet_12                : 1;
        U16 reg_control                 : 1;
        U16 reg_sel_control             : 1;
        U16 en_ref_no_bg_12             : 1;
        U16 en_polling_drv_12           : 1;
        U16 ibsel_audio                 : 2;
        U16 en_audio_ibias_12           : 1;
        U16 en_clk_tst                  : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL03_S;

typedef union { /* AUDIO_ANALOG_CTRL04 */
    U16 all;
    struct {
        U16 pga0_mica2sel               : 2;
        U16 pga0_mica2_gain             : 1;
        U16 en_pga0_mica2               : 1;
        U16 pga0_mica1_gain             : 1;
        U16 en_pga0_mica1               : 1;
        U16 ibias_pga0                  : 2;
        U16 en_ibias_pga0               : 1;
        U16 en_vcmbuf0_12               : 1;
        U16 sel_vcmref0                 : 1;
        U16 pullup_hsip                 : 1;
        U16 en_micdet_lp_12             : 1;
        U16 en_mictrim_12               : 1;
        U16 sel_irefgnd                 : 2;
    } bitc;
} GH_AUDIO_ANALOG_CTRL04_S;

typedef union { /* AUDIO_ANALOG_CTRL05 */
    U16 all;
    struct {
        U16 ibias_pga1                  : 2;
        U16 en_ibias_pga1               : 1;
        U16 en_vcmbuf1                  : 1;
        U16 sel_vcmref1                 : 1;
        U16 pga0_line_sel               : 1;
        U16 pga0_mute_r                 : 1;
        U16 pga0_mica4_sel              : 1;
        U16 pga0_mica4_gain             : 3;
        U16 en_pga0_mica4               : 1;
        U16 pga0_mica3_gain             : 1;
        U16 en_pga0_mica3               : 1;
        U16 pga0_mute_l                 : 1;
        U16 pga0_mica2sel               : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL05_S;

typedef union { /* AUDIO_ANALOG_CTRL06 */
    U16 all;
    struct {
        U16 en_dac0_r_12                : 1;
        U16 en_dac0_l_12                : 1;
        U16 en_dac0_ldo11               : 1;
        U16 ldo11_vc0                   : 1;
        U16 pos_rl0                     : 1;
        U16 pga1_line_sel               : 1;
        U16 pga1_mute_r                 : 1;
        U16 pga1_mica4_gain             : 3;
        U16 en_pga1_mica4               : 1;
        U16 pga1_mute_l                 : 1;
        U16 pga1_mica2_gain             : 3;
        U16 en_pga1_mica2               : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL06_S;

typedef union { /* AUDIO_ANALOG_CTRL07 */
    U16 all;
    struct {
        U16 en_adc1_dit                 : 1;
        U16 en_adc0_12                  : 1;
        U16 shrt_adc0_l                 : 1;
        U16 shrt_adc0_r                 : 1;
        U16 reset_adc0_l                : 1;
        U16 reset_adc0_r                : 1;
        U16 sel_ibias_adc0              : 2;
        U16 sel_dit_lvl_adc0            : 2;
        U16 en_adc0_dit                 : 1;
        U16 en_dac1_r_12                : 1;
        U16 en_dac1_l_12                : 1;
        U16 en_dac1_ldo11               : 1;
        U16 ldo11_vc1                   : 1;
        U16 pos_rl1                     : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL07_S;

typedef union { /* AUDIO_ANALOG_CTRL08 */
    U16 all;
    struct {
        U16                             : 1;
        U16 gain_ear                    : 2;
        U16 en_stg2ab_12                : 1;
        U16 en_oplp_12                  : 1;
        U16 en_earl_12                  : 1;
        U16 en_earr_12                  : 1;
        U16 en_adc1_12                  : 1;
        U16 shrt_adc1_l                 : 1;
        U16 shrt_adc1_r                 : 1;
        U16 reset_adc1_l                : 1;
        U16 reset_adc1_r                : 1;
        U16 sel_ibias_adc1              : 2;
        U16 sel_dit_lvl_adc1            : 2;
    } bitc;
} GH_AUDIO_ANALOG_CTRL08_S;

typedef union { /* AUDIO_ANALOG_CTRL09 */
    U16 all;
    struct {
        U16 mx_ear                      : 3;
        U16 isel_ocp                    : 2;
        U16 isel_drv                    : 2;
        U16 tst_drv                     : 4;
        U16 ear_mute                    : 1;
        U16 ear_popres                  : 2;
        U16 tcsel                       : 2;
    } bitc;
} GH_AUDIO_ANALOG_CTRL09_S;

typedef union { /* AUDIO_ANALOG_CTRL10 */
    U16 all;
    struct {
        U16 mute_line1                  : 1;
        U16 mx_line1                    : 2;
        U16 gain_line1                  : 3;
        U16 en_line1_r                  : 1;
        U16 en_line1_l                  : 1;
        U16 mute_line0                  : 1;
        U16 mx_line0                    : 2;
        U16 gain_line0                  : 3;
        U16 en_line0_r                  : 1;
        U16 en_line0_l                  : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL10_S;

typedef union { /* AUDIO_ANALOG_CTRL11 */
    U16 all;
    struct {
        U16                             : 3;
        U16 tst_autio                   : 4;
        U16 sel_ck_audio                : 2;
        U16 sel_phs_adcclk              : 1;
        U16 adc_clk_freq                : 1;
        U16 dac_clk_freq                : 1;
        U16 en_clk                      : 1;
        U16 v_set_ldo25                 : 2;
        U16 en_ldo25_12                 : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL11_S;

typedef union { /* AUDIO_ANALOG_CTRL12 */
    U16 all;
    struct {
        U16 audio_reg                   : 8;
        U16                             : 4;
        U16 test_bus_sel                : 4;
    } bitc;
} GH_AUDIO_ANALOG_CTRL12_S;

typedef union { /* AUDIO_ANALOG_CTRL13 */
    U16 all;
    struct {
        U16 mic_trim_sel_cfg            : 6;
        U16                             : 6;
        U16 trim_stop_sel               : 1;
        U16 rstz_trim_au                : 1;
        U16 trim_au_sel                 : 1;
        U16 trim_stop                   : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL13_S;

typedef union { /* AUDIO_ANALOG_CTRL14 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL14_S;

typedef union { /* AUDIO_ANALOG_CTRL15 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL15_S;

typedef union { /* AUDIO_ANALOG_CTRL16 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL16_S;

typedef union { /* AUDIO_ANALOG_CTRL17 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL17_S;

typedef union { /* AUDIO_ANALOG_CTRL18 */
    U16 all;
    struct {
        U16 audio_sleep_dbg_bus         : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL18_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register AUDIO_AHB_GENERAL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_AHB_GENERAL0'. */
void GH_AUDIO_set_AHB_GENERAL0(U16 data);
/*! \brief Reads the register 'AUDIO_AHB_GENERAL0'. */
U16  GH_AUDIO_get_AHB_GENERAL0(void);
/*! \brief Writes the bit group 'USB_TM1' of register 'AUDIO_AHB_GENERAL0'. */
void GH_AUDIO_set_AHB_GENERAL0_USB_TM1(U8 data);
/*! \brief Reads the bit group 'USB_TM1' of register 'AUDIO_AHB_GENERAL0'. */
U8   GH_AUDIO_get_AHB_GENERAL0_USB_TM1(void);
/*! \brief Writes the bit group 'AHB_RMII_SEL' of register 'AUDIO_AHB_GENERAL0'. */
void GH_AUDIO_set_AHB_GENERAL0_AHB_RMII_SEL(U8 data);
/*! \brief Reads the bit group 'AHB_RMII_SEL' of register 'AUDIO_AHB_GENERAL0'. */
U8   GH_AUDIO_get_AHB_GENERAL0_AHB_RMII_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_AHB_GENERAL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AHB_GENERAL0] <-- 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_AHB_GENERAL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AHB_GENERAL0] --> 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_AHB_GENERAL0_USB_TM1(U8 data)
{
    GH_AUDIO_AHB_GENERAL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AHB_GENERAL0;
    d.bitc.usb_tm1 = data;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AHB_GENERAL0_USB_TM1] <-- 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AHB_GENERAL0_USB_TM1(void)
{
    GH_AUDIO_AHB_GENERAL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AHB_GENERAL0_USB_TM1] --> 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL0,value);
    #endif
    return tmp_value.bitc.usb_tm1;
}
GH_INLINE void GH_AUDIO_set_AHB_GENERAL0_AHB_RMII_SEL(U8 data)
{
    GH_AUDIO_AHB_GENERAL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AHB_GENERAL0;
    d.bitc.ahb_rmii_sel = data;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AHB_GENERAL0_AHB_RMII_SEL] <-- 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AHB_GENERAL0_AHB_RMII_SEL(void)
{
    GH_AUDIO_AHB_GENERAL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AHB_GENERAL0_AHB_RMII_SEL] --> 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL0,value);
    #endif
    return tmp_value.bitc.ahb_rmii_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_AHB_GENERAL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_AHB_GENERAL1'. */
void GH_AUDIO_set_AHB_GENERAL1(U16 data);
/*! \brief Reads the register 'AUDIO_AHB_GENERAL1'. */
U16  GH_AUDIO_get_AHB_GENERAL1(void);
/*! \brief Writes the bit group 'AUDIO_I2S_SEL' of register 'AUDIO_AHB_GENERAL1'. */
void GH_AUDIO_set_AHB_GENERAL1_AUDIO_I2S_SEL(U8 data);
/*! \brief Reads the bit group 'AUDIO_I2S_SEL' of register 'AUDIO_AHB_GENERAL1'. */
U8   GH_AUDIO_get_AHB_GENERAL1_AUDIO_I2S_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_AHB_GENERAL1(U16 data)
{
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL1 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AHB_GENERAL1] <-- 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL1,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_AHB_GENERAL1(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL1);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AHB_GENERAL1] --> 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL1,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_AHB_GENERAL1_AUDIO_I2S_SEL(U8 data)
{
    GH_AUDIO_AHB_GENERAL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AHB_GENERAL1;
    d.bitc.audio_i2s_sel = data;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AHB_GENERAL1_AUDIO_I2S_SEL] <-- 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AHB_GENERAL1_AUDIO_I2S_SEL(void)
{
    GH_AUDIO_AHB_GENERAL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AHB_GENERAL1_AUDIO_I2S_SEL] --> 0x%08x\n",
                        REG_AUDIO_AHB_GENERAL1,value);
    #endif
    return tmp_value.bitc.audio_i2s_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_CKG_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_CKG_CTRL0'. */
void GH_AUDIO_set_CKG_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_CKG_CTRL0'. */
U16  GH_AUDIO_get_CKG_CTRL0(void);
/*! \brief Writes the bit group 'AU_SRC1_MAC_48M_DYNG_EN' of register 'AUDIO_CKG_CTRL0'. */
void GH_AUDIO_set_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(U8 data);
/*! \brief Reads the bit group 'AU_SRC1_MAC_48M_DYNG_EN' of register 'AUDIO_CKG_CTRL0'. */
U8   GH_AUDIO_get_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_CKG_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_CKG_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_CKG_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_CKG_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_CKG_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_CKG_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_CKG_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_CKG_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(U8 data)
{
    GH_AUDIO_CKG_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_CKG_CTRL0;
    d.bitc.au_src1_mac_48m_dyng_en = data;
    *(volatile U16 *)REG_AUDIO_CKG_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN] <-- 0x%08x\n",
                        REG_AUDIO_CKG_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(void)
{
    GH_AUDIO_CKG_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_CKG_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN] --> 0x%08x\n",
                        REG_AUDIO_CKG_CTRL0,value);
    #endif
    return tmp_value.bitc.au_src1_mac_48m_dyng_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SYS_RST_CTRL0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_SYS_RST_CTRL0'. */
U16  GH_AUDIO_get_SYS_RST_CTRL0(void);
/*! \brief Writes the bit group 'RESET_SDM_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0_RESET_SDM_SYNC(U8 data);
/*! \brief Reads the bit group 'RESET_SDM_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_SDM_SYNC(void);
/*! \brief Writes the bit group 'RESET_DPGA_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0_RESET_DPGA_SYNC(U8 data);
/*! \brief Reads the bit group 'RESET_DPGA_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_DPGA_SYNC(void);
/*! \brief Writes the bit group 'RESET_AU_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0_RESET_AU_SYNC(U8 data);
/*! \brief Reads the bit group 'RESET_AU_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_AU_SYNC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SYS_RST_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_SYS_RST_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SYS_RST_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0_RESET_SDM_SYNC(U8 data)
{
    GH_AUDIO_SYS_RST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0;
    d.bitc.reset_sdm_sync = data;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SYS_RST_CTRL0_RESET_SDM_SYNC] <-- 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_SDM_SYNC(void)
{
    GH_AUDIO_SYS_RST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SYS_RST_CTRL0_RESET_SDM_SYNC] --> 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,value);
    #endif
    return tmp_value.bitc.reset_sdm_sync;
}
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0_RESET_DPGA_SYNC(U8 data)
{
    GH_AUDIO_SYS_RST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0;
    d.bitc.reset_dpga_sync = data;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SYS_RST_CTRL0_RESET_DPGA_SYNC] <-- 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_DPGA_SYNC(void)
{
    GH_AUDIO_SYS_RST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SYS_RST_CTRL0_RESET_DPGA_SYNC] --> 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,value);
    #endif
    return tmp_value.bitc.reset_dpga_sync;
}
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0_RESET_AU_SYNC(U8 data)
{
    GH_AUDIO_SYS_RST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0;
    d.bitc.reset_au_sync = data;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SYS_RST_CTRL0_RESET_AU_SYNC] <-- 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_AU_SYNC(void)
{
    GH_AUDIO_SYS_RST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SYS_RST_CTRL0_RESET_AU_SYNC] --> 0x%08x\n",
                        REG_AUDIO_SYS_RST_CTRL0,value);
    #endif
    return tmp_value.bitc.reset_au_sync;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_TIMING_CTRL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_TIMING_CTRL0'. */
U16  GH_AUDIO_get_TIMING_CTRL0(void);
/*! \brief Writes the bit group 'EN_TIME_GEN_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_TIME_GEN_p(U8 data);
/*! \brief Reads the bit group 'EN_TIME_GEN_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_TIME_GEN_p(void);
/*! \brief Writes the bit group 'EN_DEC_1_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_1_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_1_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_1_p(void);
/*! \brief Writes the bit group 'EN_DEC_2_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_2_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_2_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_2_p(void);
/*! \brief Writes the bit group 'EN_INT_1_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_INT_1_p(U8 data);
/*! \brief Reads the bit group 'EN_INT_1_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_1_p(void);
/*! \brief Writes the bit group 'EN_INT_2_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_INT_2_p(U8 data);
/*! \brief Reads the bit group 'EN_INT_2_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_2_p(void);
/*! \brief Writes the bit group 'EN_ASRC1_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_ASRC1_p(U8 data);
/*! \brief Reads the bit group 'EN_ASRC1_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_ASRC1_p(void);
/*! \brief Writes the bit group 'DEC_NUM' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_DEC_NUM(U8 data);
/*! \brief Reads the bit group 'DEC_NUM' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_DEC_NUM(void);
/*! \brief Writes the bit group 'DAC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_DAC_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'DAC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_DAC_SYNC_SEL(void);
/*! \brief Writes the bit group 'ADC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_ADC_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'ADC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_ADC_SYNC_SEL(void);
/*! \brief Writes the bit group 'SYNC_CLK2_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK2_SEL(U8 data);
/*! \brief Reads the bit group 'SYNC_CLK2_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK2_SEL(void);
/*! \brief Writes the bit group 'SYNC_CLK1_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK1_SEL(U8 data);
/*! \brief Reads the bit group 'SYNC_CLK1_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK1_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_TIMING_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_TIME_GEN_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.en_time_gen_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_EN_TIME_GEN_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_TIME_GEN_p(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_EN_TIME_GEN_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.en_time_gen_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_1_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.en_dec_1_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_EN_DEC_1_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_1_p(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_EN_DEC_1_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.en_dec_1_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_2_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.en_dec_2_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_EN_DEC_2_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_2_p(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_EN_DEC_2_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.en_dec_2_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_INT_1_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.en_int_1_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_EN_INT_1_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_1_p(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_EN_INT_1_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.en_int_1_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_INT_2_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.en_int_2_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_EN_INT_2_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_2_p(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_EN_INT_2_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.en_int_2_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_ASRC1_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.en_asrc1_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_EN_ASRC1_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_ASRC1_p(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_EN_ASRC1_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.en_asrc1_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_DEC_NUM(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.dec_num = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_DEC_NUM] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_DEC_NUM(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_DEC_NUM] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.dec_num;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_DAC_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.dac_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_DAC_SYNC_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_DAC_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_DAC_SYNC_SEL] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.dac_sync_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_ADC_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.adc_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_ADC_SYNC_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_ADC_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_ADC_SYNC_SEL] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.adc_sync_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK2_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.sync_clk2_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK2_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK2_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK2_SEL] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.sync_clk2_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK1_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0;
    d.bitc.sync_clk1_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK1_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK1_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK1_SEL] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL0,value);
    #endif
    return tmp_value.bitc.sync_clk1_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_TIMING_CTRL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_TIMING_CTRL1'. */
U16  GH_AUDIO_get_TIMING_CTRL1(void);
/*! \brief Writes the bit group 'DEC_NUM2' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_DEC_NUM2(U8 data);
/*! \brief Reads the bit group 'DEC_NUM2' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_DEC_NUM2(void);
/*! \brief Writes the bit group 'EN_ASRC3_p' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_EN_ASRC3_p(U8 data);
/*! \brief Reads the bit group 'EN_ASRC3_p' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_EN_ASRC3_p(void);
/*! \brief Writes the bit group 'CH2_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'CH2_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(void);
/*! \brief Writes the bit group 'CH1_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'CH1_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1(U16 data)
{
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL1] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_TIMING_CTRL1(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL1] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_DEC_NUM2(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1;
    d.bitc.dec_num2 = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL1_DEC_NUM2] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_DEC_NUM2(void)
{
    GH_AUDIO_TIMING_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL1_DEC_NUM2] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,value);
    #endif
    return tmp_value.bitc.dec_num2;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_EN_ASRC3_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1;
    d.bitc.en_asrc3_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL1_EN_ASRC3_p] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_EN_ASRC3_p(void)
{
    GH_AUDIO_TIMING_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL1_EN_ASRC3_p] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,value);
    #endif
    return tmp_value.bitc.en_asrc3_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1;
    d.bitc.ch2_int_cnt_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,value);
    #endif
    return tmp_value.bitc.ch2_int_cnt_sync_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1;
    d.bitc.ch1_int_cnt_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL] --> 0x%08x\n",
                        REG_AUDIO_TIMING_CTRL1,value);
    #endif
    return tmp_value.bitc.ch1_int_cnt_sync_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL0 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_AUDIOBAND_CTRL0'. */
U16  GH_AUDIO_get_AUDIOBAND_CTRL0(void);
/*! \brief Writes the bit group 'INI_SRAM' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_INI_SRAM(U8 data);
/*! \brief Reads the bit group 'INI_SRAM' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_INI_SRAM(void);
/*! \brief Writes the bit group 'CH12_SYNC_ENABLE' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(U8 data);
/*! \brief Reads the bit group 'CH12_SYNC_ENABLE' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(void);
/*! \brief Writes the bit group 'CH2_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(U8 data);
/*! \brief Reads the bit group 'CH2_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(void);
/*! \brief Writes the bit group 'CH1_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(U8 data);
/*! \brief Reads the bit group 'CH1_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_INI_SRAM(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0;
    d.bitc.ini_sram = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL0_INI_SRAM] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_INI_SRAM(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL0_INI_SRAM] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,value);
    #endif
    return tmp_value.bitc.ini_sram;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0;
    d.bitc.ch12_sync_enable = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,value);
    #endif
    return tmp_value.bitc.ch12_sync_enable;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0;
    d.bitc.ch2_int_128fs_nf_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,value);
    #endif
    return tmp_value.bitc.ch2_int_128fs_nf_sel;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0;
    d.bitc.ch1_int_128fs_nf_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL0,value);
    #endif
    return tmp_value.bitc.ch1_int_128fs_nf_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL1 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_AUDIOBAND_CTRL1'. */
void GH_AUDIO_set_AUDIOBAND_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_AUDIOBAND_CTRL1'. */
U16  GH_AUDIO_get_AUDIOBAND_CTRL1(void);
/*! \brief Writes the bit group 'SDM_DWA_DATAIN_R_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(U8 data);
/*! \brief Reads the bit group 'SDM_DWA_DATAIN_R_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(void);
/*! \brief Writes the bit group 'SDM_DWA_DATAIN_L_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(U8 data);
/*! \brief Reads the bit group 'SDM_DWA_DATAIN_L_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL1(U16 data)
{
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL1] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL1,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_CTRL1(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL1] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL1,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1;
    d.bitc.sdm_dwa_datain_r_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL1,value);
    #endif
    return tmp_value.bitc.sdm_dwa_datain_r_sel;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1;
    d.bitc.sdm_dwa_datain_l_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL1,value);
    #endif
    return tmp_value.bitc.sdm_dwa_datain_l_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL2 (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2(U16 data);
/*! \brief Reads the register 'AUDIO_AUDIOBAND_CTRL2'. */
U16  GH_AUDIO_get_AUDIOBAND_CTRL2(void);
/*! \brief Writes the bit group 'EN_DEC_4_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_4_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_4_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_4_p(void);
/*! \brief Writes the bit group 'EN_DEC_3_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_3_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_3_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_3_p(void);
/*! \brief Writes the bit group 'NT4_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_NT4_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'NT4_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT4_MIX_CTRL(void);
/*! \brief Writes the bit group 'NT3_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_NT3_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'NT3_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT3_MIX_CTRL(void);
/*! \brief Writes the bit group 'DEC_NUM3' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_DEC_NUM3(U8 data);
/*! \brief Reads the bit group 'DEC_NUM3' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_DEC_NUM3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2(U16 data)
{
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL2] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_CTRL2(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL2] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_4_p(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2;
    d.bitc.en_dec_4_p = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_4_p] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_4_p(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_4_p] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,value);
    #endif
    return tmp_value.bitc.en_dec_4_p;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_3_p(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2;
    d.bitc.en_dec_3_p = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_3_p] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_3_p(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_3_p] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,value);
    #endif
    return tmp_value.bitc.en_dec_3_p;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_NT4_MIX_CTRL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2;
    d.bitc.nt4_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL2_NT4_MIX_CTRL] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT4_MIX_CTRL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL2_NT4_MIX_CTRL] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,value);
    #endif
    return tmp_value.bitc.nt4_mix_ctrl;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_NT3_MIX_CTRL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2;
    d.bitc.nt3_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL2_NT3_MIX_CTRL] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT3_MIX_CTRL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL2_NT3_MIX_CTRL] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,value);
    #endif
    return tmp_value.bitc.nt3_mix_ctrl;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_DEC_NUM3(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2;
    d.bitc.dec_num3 = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_AUDIOBAND_CTRL2_DEC_NUM3] <-- 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_DEC_NUM3(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_CTRL2_DEC_NUM3] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_CTRL2,value);
    #endif
    return tmp_value.bitc.dec_num3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_STS (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_AUDIOBAND_STS'. */
U16  GH_AUDIO_get_AUDIOBAND_STS(void);
/*! \brief Reads the bit group 'QUANT_OUT_R' of register 'AUDIO_AUDIOBAND_STS'. */
U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_R(void);
/*! \brief Reads the bit group 'QUANT_OUT_L' of register 'AUDIO_AUDIOBAND_STS'. */
U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_STS(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_R(void)
{
    GH_AUDIO_AUDIOBAND_STS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_R] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS,value);
    #endif
    return tmp_value.bitc.quant_out_r;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_L(void)
{
    GH_AUDIO_AUDIOBAND_STS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_L] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS,value);
    #endif
    return tmp_value.bitc.quant_out_l;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_STS2 (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_AUDIOBAND_STS2'. */
U16  GH_AUDIO_get_AUDIOBAND_STS2(void);
/*! \brief Reads the bit group 'PGA_STATUS' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_PGA_STATUS(void);
/*! \brief Reads the bit group 'MMP2_MUTE_DONE' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP2_MUTE_DONE(void);
/*! \brief Reads the bit group 'MMP1_MUTE_DONE' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP1_MUTE_DONE(void);
/*! \brief Reads the bit group 'PNT_MMC_DEC_ERR_CLR' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_PNT_MMC_DEC_ERR_CLR(void);
/*! \brief Reads the bit group 'DPGA_STATUS' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_DPGA_STATUS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_STS2(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS2] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS2,value);
    #endif
    return value;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_PGA_STATUS(void)
{
    GH_AUDIO_AUDIOBAND_STS2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS2_PGA_STATUS] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS2,value);
    #endif
    return tmp_value.bitc.pga_status;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP2_MUTE_DONE(void)
{
    GH_AUDIO_AUDIOBAND_STS2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS2_MMP2_MUTE_DONE] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS2,value);
    #endif
    return tmp_value.bitc.mmp2_mute_done;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP1_MUTE_DONE(void)
{
    GH_AUDIO_AUDIOBAND_STS2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS2_MMP1_MUTE_DONE] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS2,value);
    #endif
    return tmp_value.bitc.mmp1_mute_done;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_PNT_MMC_DEC_ERR_CLR(void)
{
    GH_AUDIO_AUDIOBAND_STS2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS2_PNT_MMC_DEC_ERR_CLR] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS2,value);
    #endif
    return tmp_value.bitc.pnt_mmc_dec_err_clr;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_DPGA_STATUS(void)
{
    GH_AUDIO_AUDIOBAND_STS2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_AUDIOBAND_STS2_DPGA_STATUS] --> 0x%08x\n",
                        REG_AUDIO_AUDIOBAND_STS2,value);
    #endif
    return tmp_value.bitc.dpga_status;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SINE_GEN_CTRL0 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_SINE_GEN_CTRL0'. */
U16  GH_AUDIO_get_SINE_GEN_CTRL0(void);
/*! \brief Writes the bit group 'CH1_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(U8 data);
/*! \brief Reads the bit group 'CH1_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(void);
/*! \brief Writes the bit group 'CH2_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(U8 data);
/*! \brief Reads the bit group 'CH2_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(void);
/*! \brief Writes the bit group 'EN_DIT_SINE' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SINE(U8 data);
/*! \brief Reads the bit group 'EN_DIT_SINE' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SINE(void);
/*! \brief Writes the bit group 'EN_DIT_SRC' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SRC(U8 data);
/*! \brief Reads the bit group 'EN_DIT_SRC' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SRC(void);
/*! \brief Writes the bit group 'PGA2_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_PGA2_SWAP(U8 data);
/*! \brief Reads the bit group 'PGA2_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA2_SWAP(void);
/*! \brief Writes the bit group 'PGA1_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_PGA1_SWAP(U8 data);
/*! \brief Reads the bit group 'PGA1_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA1_SWAP(void);
/*! \brief Writes the bit group 'INT2_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_INT2_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'INT2_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT2_MIX_CTRL(void);
/*! \brief Writes the bit group 'INT1_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_INT1_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'INT1_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT1_MIX_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_SINE_GEN_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.ch1_sin_gen_en_p = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.ch1_sin_gen_en_p;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.ch2_sin_gen_en_p = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.ch2_sin_gen_en_p;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SINE(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.en_dit_sine = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SINE] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SINE(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SINE] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.en_dit_sine;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SRC(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.en_dit_src = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SRC] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SRC(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SRC] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.en_dit_src;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_PGA2_SWAP(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.pga2_swap = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_PGA2_SWAP] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA2_SWAP(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_PGA2_SWAP] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.pga2_swap;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_PGA1_SWAP(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.pga1_swap = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_PGA1_SWAP] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA1_SWAP(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_PGA1_SWAP] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.pga1_swap;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_INT2_MIX_CTRL(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.int2_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_INT2_MIX_CTRL] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT2_MIX_CTRL(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_INT2_MIX_CTRL] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.int2_mix_ctrl;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_INT1_MIX_CTRL(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0;
    d.bitc.int1_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL0_INT1_MIX_CTRL] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT1_MIX_CTRL(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL0_INT1_MIX_CTRL] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL0,value);
    #endif
    return tmp_value.bitc.int1_mix_ctrl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SINE_GEN_CTRL1 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_SINE_GEN_CTRL1'. */
U16  GH_AUDIO_get_SINE_GEN_CTRL1(void);
/*! \brief Writes the bit group 'SINE_GEN_CH1_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH1_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(void);
/*! \brief Writes the bit group 'SINE_GEN_CH1_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH1_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(void);
/*! \brief Writes the bit group 'SINE_GEN_CH2_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH2_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(void);
/*! \brief Writes the bit group 'SINE_GEN_CH2_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH2_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1(U16 data)
{
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL1] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_SINE_GEN_CTRL1(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL1] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1;
    d.bitc.sine_gen_ch1_freq = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,value);
    #endif
    return tmp_value.bitc.sine_gen_ch1_freq;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1;
    d.bitc.sine_gen_ch1_gain = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,value);
    #endif
    return tmp_value.bitc.sine_gen_ch1_gain;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1;
    d.bitc.sine_gen_ch2_freq = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,value);
    #endif
    return tmp_value.bitc.sine_gen_ch2_freq;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1;
    d.bitc.sine_gen_ch2_gain = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN] --> 0x%08x\n",
                        REG_AUDIO_SINE_GEN_CTRL1,value);
    #endif
    return tmp_value.bitc.sine_gen_ch2_gain;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_TEST_CTRL0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_TEST_CTRL0'. */
U16  GH_AUDIO_get_TEST_CTRL0(void);
/*! \brief Writes the bit group 'DAC_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_DAC_TEST_EN(U8 data);
/*! \brief Reads the bit group 'DAC_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_DAC_TEST_EN(void);
/*! \brief Writes the bit group 'SDM_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_SDM_TEST_EN(U8 data);
/*! \brief Reads the bit group 'SDM_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_SDM_TEST_EN(void);
/*! \brief Writes the bit group 'SDM_SFT_DIS' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_SDM_SFT_DIS(U8 data);
/*! \brief Reads the bit group 'SDM_SFT_DIS' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_SDM_SFT_DIS(void);
/*! \brief Writes the bit group 'SRAM_CG_EN' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_SRAM_CG_EN(U8 data);
/*! \brief Reads the bit group 'SRAM_CG_EN' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_SRAM_CG_EN(void);
/*! \brief Writes the bit group 'TESTCLK_SEL' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_TESTCLK_SEL(U8 data);
/*! \brief Reads the bit group 'TESTCLK_SEL' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_TESTCLK_SEL(void);
/*! \brief Writes the bit group 'TESTBUS_SEL' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_TESTBUS_SEL(U8 data);
/*! \brief Reads the bit group 'TESTBUS_SEL' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_TESTBUS_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_TEST_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_TEST_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_DAC_TEST_EN(U8 data)
{
    GH_AUDIO_TEST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0;
    d.bitc.dac_test_en = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0_DAC_TEST_EN] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_DAC_TEST_EN(void)
{
    GH_AUDIO_TEST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0_DAC_TEST_EN] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return tmp_value.bitc.dac_test_en;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_SDM_TEST_EN(U8 data)
{
    GH_AUDIO_TEST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0;
    d.bitc.sdm_test_en = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0_SDM_TEST_EN] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_SDM_TEST_EN(void)
{
    GH_AUDIO_TEST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0_SDM_TEST_EN] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return tmp_value.bitc.sdm_test_en;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_SDM_SFT_DIS(U8 data)
{
    GH_AUDIO_TEST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0;
    d.bitc.sdm_sft_dis = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0_SDM_SFT_DIS] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_SDM_SFT_DIS(void)
{
    GH_AUDIO_TEST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0_SDM_SFT_DIS] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return tmp_value.bitc.sdm_sft_dis;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_SRAM_CG_EN(U8 data)
{
    GH_AUDIO_TEST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0;
    d.bitc.sram_cg_en = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0_SRAM_CG_EN] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_SRAM_CG_EN(void)
{
    GH_AUDIO_TEST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0_SRAM_CG_EN] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return tmp_value.bitc.sram_cg_en;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_TESTCLK_SEL(U8 data)
{
    GH_AUDIO_TEST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0;
    d.bitc.testclk_sel = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0_TESTCLK_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_TESTCLK_SEL(void)
{
    GH_AUDIO_TEST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0_TESTCLK_SEL] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return tmp_value.bitc.testclk_sel;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_TESTBUS_SEL(U8 data)
{
    GH_AUDIO_TEST_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0;
    d.bitc.testbus_sel = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_TEST_CTRL0_TESTBUS_SEL] <-- 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_TESTBUS_SEL(void)
{
    GH_AUDIO_TEST_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_TEST_CTRL0_TESTBUS_SEL] --> 0x%08x\n",
                        REG_AUDIO_TEST_CTRL0,value);
    #endif
    return tmp_value.bitc.testbus_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_SDM_CTRL0'. */
U16  GH_AUDIO_get_SDM_CTRL0(void);
/*! \brief Writes the bit group 'EN_SDM_p' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_EN_SDM_p(U8 data);
/*! \brief Reads the bit group 'EN_SDM_p' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_EN_SDM_p(void);
/*! \brief Writes the bit group 'FS_SYNTH_SEL_p' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_FS_SYNTH_SEL_p(U8 data);
/*! \brief Reads the bit group 'FS_SYNTH_SEL_p' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_FS_SYNTH_SEL_p(void);
/*! \brief Writes the bit group 'DAC_DIN_L_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_L_SEL(U8 data);
/*! \brief Reads the bit group 'DAC_DIN_L_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_L_SEL(void);
/*! \brief Writes the bit group 'DAC_DIN_R_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_R_SEL(U8 data);
/*! \brief Reads the bit group 'DAC_DIN_R_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_R_SEL(void);
/*! \brief Writes the bit group 'FIX_MSB_EN' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_EN(U8 data);
/*! \brief Reads the bit group 'FIX_MSB_EN' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_EN(void);
/*! \brief Writes the bit group 'FIX_MSB_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_SEL(U8 data);
/*! \brief Reads the bit group 'FIX_MSB_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_SEL(void);
/*! \brief Writes the bit group 'DITHER_EN_p' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DITHER_EN_p(U8 data);
/*! \brief Reads the bit group 'DITHER_EN_p' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DITHER_EN_p(void);
/*! \brief Writes the bit group 'DITHER_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DITHER_SEL(U8 data);
/*! \brief Reads the bit group 'DITHER_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DITHER_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_SDM_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_SDM_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_EN_SDM_p(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.en_sdm_p = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_EN_SDM_p] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_EN_SDM_p(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_EN_SDM_p] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.en_sdm_p;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_FS_SYNTH_SEL_p(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.fs_synth_sel_p = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_FS_SYNTH_SEL_p] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_FS_SYNTH_SEL_p(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_FS_SYNTH_SEL_p] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.fs_synth_sel_p;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_L_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.dac_din_l_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_DAC_DIN_L_SEL] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_L_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_DAC_DIN_L_SEL] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.dac_din_l_sel;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_R_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.dac_din_r_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_DAC_DIN_R_SEL] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_R_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_DAC_DIN_R_SEL] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.dac_din_r_sel;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_EN(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.fix_msb_en = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_FIX_MSB_EN] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_EN(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_FIX_MSB_EN] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.fix_msb_en;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.fix_msb_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_FIX_MSB_SEL] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_FIX_MSB_SEL] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.fix_msb_sel;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DITHER_EN_p(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.dither_en_p = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_DITHER_EN_p] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DITHER_EN_p(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_DITHER_EN_p] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.dither_en_p;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DITHER_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0;
    d.bitc.dither_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL0_DITHER_SEL] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DITHER_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL0_DITHER_SEL] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL0,value);
    #endif
    return tmp_value.bitc.dither_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_CTRL1 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_SDM_CTRL1'. */
void GH_AUDIO_set_SDM_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_SDM_CTRL1'. */
U16  GH_AUDIO_get_SDM_CTRL1(void);
/*! \brief Writes the bit group 'SDM_OFFSET' of register 'AUDIO_SDM_CTRL1'. */
void GH_AUDIO_set_SDM_CTRL1_SDM_OFFSET(U16 data);
/*! \brief Reads the bit group 'SDM_OFFSET' of register 'AUDIO_SDM_CTRL1'. */
U16  GH_AUDIO_get_SDM_CTRL1_SDM_OFFSET(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_SDM_CTRL1(U16 data)
{
    *(volatile U16 *)REG_AUDIO_SDM_CTRL1 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL1] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL1,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_SDM_CTRL1(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL1);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL1] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL1,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL1_SDM_OFFSET(U16 data)
{
    GH_AUDIO_SDM_CTRL1_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL1;
    d.bitc.sdm_offset = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL1 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_SDM_CTRL1_SDM_OFFSET] <-- 0x%08x\n",
                        REG_AUDIO_SDM_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_SDM_CTRL1_SDM_OFFSET(void)
{
    GH_AUDIO_SDM_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL1);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_CTRL1_SDM_OFFSET] --> 0x%08x\n",
                        REG_AUDIO_SDM_CTRL1,value);
    #endif
    return tmp_value.bitc.sdm_offset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_1_NF_H (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_NF_SYNTH_1_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_H(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_1_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_H(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_H_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_H_VALUE(void);
/*! \brief Writes the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_H_TRIG(U8 data);
/*! \brief Reads the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
U8   GH_AUDIO_get_NF_SYNTH_1_NF_H_TRIG(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_H(U16 data)
{
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_1_NF_H] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_H,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_H(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_1_NF_H] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_H,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_H_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_1_NF_H_VALUE] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_H,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_H_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_1_NF_H_VALUE] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_H,value);
    #endif
    return tmp_value.bitc.value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_H_TRIG(U8 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H;
    d.bitc.trig = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_1_NF_H_TRIG] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_NF_SYNTH_1_NF_H_TRIG(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_1_NF_H_TRIG] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_H,value);
    #endif
    return tmp_value.bitc.trig;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_1_NF_L (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_NF_SYNTH_1_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_L(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_1_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_L(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_L_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_L_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_L(U16 data)
{
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_1_NF_L] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_L,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_L(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_1_NF_L] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_L,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_L_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_L_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_1_NF_L_VALUE] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_L,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_L_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_L_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_1_NF_L_VALUE] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_1_NF_L,value);
    #endif
    return tmp_value.bitc.value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_2_NF_H (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_NF_SYNTH_2_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_H(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_2_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_H(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_H_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_H_VALUE(void);
/*! \brief Writes the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_H_TRIG(U8 data);
/*! \brief Reads the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
U8   GH_AUDIO_get_NF_SYNTH_2_NF_H_TRIG(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_H(U16 data)
{
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_2_NF_H] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_H,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_H(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_2_NF_H] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_H,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_H_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_2_NF_H_VALUE] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_H,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_H_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_2_NF_H_VALUE] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_H,value);
    #endif
    return tmp_value.bitc.value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_H_TRIG(U8 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H;
    d.bitc.trig = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_2_NF_H_TRIG] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_NF_SYNTH_2_NF_H_TRIG(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_2_NF_H_TRIG] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_H,value);
    #endif
    return tmp_value.bitc.trig;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_2_NF_L (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_NF_SYNTH_2_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_L(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_2_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_L(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_L_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_L_VALUE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_L(U16 data)
{
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_2_NF_L] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_L,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_L(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_2_NF_L] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_L,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_L_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_L_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_NF_SYNTH_2_NF_L_VALUE] <-- 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_L,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_L_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_L_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_2_NF_L_VALUE] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_2_NF_L,value);
    #endif
    return tmp_value.bitc.value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_DIG_MIC_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL(U16 data);
/*! \brief Reads the register 'AUDIO_DIG_MIC_CTRL'. */
U16  GH_AUDIO_get_DIG_MIC_CTRL(void);
/*! \brief Writes the bit group 'PGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PGA_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'PGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PGA_STATUS_CLR(void);
/*! \brief Writes the bit group 'DPGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_DPGA_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'DPGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_DPGA_STATUS_CLR(void);
/*! \brief Writes the bit group 'PNT_MMC3_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(U8 data);
/*! \brief Reads the bit group 'PNT_MMC3_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(void);
/*! \brief Writes the bit group 'PNT_MMC1_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(U8 data);
/*! \brief Reads the bit group 'PNT_MMC1_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(void);
/*! \brief Writes the bit group 'PNT_MMC_DEC_ERR_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(U8 data);
/*! \brief Reads the bit group 'PNT_MMC_DEC_ERR_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL(U16 data)
{
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_DIG_MIC_CTRL] <-- 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_DIG_MIC_CTRL(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_DIG_MIC_CTRL] --> 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PGA_STATUS_CLR(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL;
    d.bitc.pga_status_clr = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_DIG_MIC_CTRL_PGA_STATUS_CLR] <-- 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PGA_STATUS_CLR(void)
{
    GH_AUDIO_DIG_MIC_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_DIG_MIC_CTRL_PGA_STATUS_CLR] --> 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,value);
    #endif
    return tmp_value.bitc.pga_status_clr;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_DPGA_STATUS_CLR(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL;
    d.bitc.dpga_status_clr = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_DIG_MIC_CTRL_DPGA_STATUS_CLR] <-- 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_DPGA_STATUS_CLR(void)
{
    GH_AUDIO_DIG_MIC_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_DIG_MIC_CTRL_DPGA_STATUS_CLR] --> 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,value);
    #endif
    return tmp_value.bitc.dpga_status_clr;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL;
    d.bitc.pnt_mmc3_dec_sync_enz = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ] <-- 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(void)
{
    GH_AUDIO_DIG_MIC_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ] --> 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,value);
    #endif
    return tmp_value.bitc.pnt_mmc3_dec_sync_enz;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL;
    d.bitc.pnt_mmc1_dec_sync_enz = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ] <-- 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(void)
{
    GH_AUDIO_DIG_MIC_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ] --> 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,value);
    #endif
    return tmp_value.bitc.pnt_mmc1_dec_sync_enz;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL;
    d.bitc.pnt_mmc_dec_err_clr = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR] <-- 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(void)
{
    GH_AUDIO_DIG_MIC_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR] --> 0x%08x\n",
                        REG_AUDIO_DIG_MIC_CTRL,value);
    #endif
    return tmp_value.bitc.pnt_mmc_dec_err_clr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_MIX_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_MIX_CTRL0'. */
U16  GH_AUDIO_get_MIX_CTRL0(void);
/*! \brief Writes the bit group 'CH2_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(U8 data);
/*! \brief Reads the bit group 'CH2_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_CH2_MUX_SEL(void);
/*! \brief Writes the bit group 'CH1_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(U8 data);
/*! \brief Reads the bit group 'CH1_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_CH1_MUX_SEL(void);
/*! \brief Writes the bit group 'SEL_DEC2_DOUT' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_SEL_DEC2_DOUT(U8 data);
/*! \brief Reads the bit group 'SEL_DEC2_DOUT' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC2_DOUT(void);
/*! \brief Writes the bit group 'SEL_DEC1_DOUT' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_SEL_DEC1_DOUT(U8 data);
/*! \brief Reads the bit group 'SEL_DEC1_DOUT' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC1_DOUT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_MIX_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MIX_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_MIX_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MIX_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(U8 data)
{
    GH_AUDIO_MIX_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0;
    d.bitc.ch2_mux_sel = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL] <-- 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_CH2_MUX_SEL(void)
{
    GH_AUDIO_MIX_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MIX_CTRL0_CH2_MUX_SEL] --> 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,value);
    #endif
    return tmp_value.bitc.ch2_mux_sel;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(U8 data)
{
    GH_AUDIO_MIX_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0;
    d.bitc.ch1_mux_sel = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL] <-- 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_CH1_MUX_SEL(void)
{
    GH_AUDIO_MIX_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MIX_CTRL0_CH1_MUX_SEL] --> 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,value);
    #endif
    return tmp_value.bitc.ch1_mux_sel;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_SEL_DEC2_DOUT(U8 data)
{
    GH_AUDIO_MIX_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0;
    d.bitc.sel_dec2_dout = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MIX_CTRL0_SEL_DEC2_DOUT] <-- 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC2_DOUT(void)
{
    GH_AUDIO_MIX_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MIX_CTRL0_SEL_DEC2_DOUT] --> 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,value);
    #endif
    return tmp_value.bitc.sel_dec2_dout;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_SEL_DEC1_DOUT(U8 data)
{
    GH_AUDIO_MIX_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0;
    d.bitc.sel_dec1_dout = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MIX_CTRL0_SEL_DEC1_DOUT] <-- 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC1_DOUT(void)
{
    GH_AUDIO_MIX_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MIX_CTRL0_SEL_DEC1_DOUT] --> 0x%08x\n",
                        REG_AUDIO_MIX_CTRL0,value);
    #endif
    return tmp_value.bitc.sel_dec1_dout;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_DWA_DATAIN_L (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_SDM_DWA_DATAIN_L'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_L(void);
/*! \brief Reads the bit group 'data' of register 'AUDIO_SDM_DWA_DATAIN_L'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_L_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_L(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_L);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_DWA_DATAIN_L] --> 0x%08x\n",
                        REG_AUDIO_SDM_DWA_DATAIN_L,value);
    #endif
    return value;
}
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_L_data(void)
{
    GH_AUDIO_SDM_DWA_DATAIN_L_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_L);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_DWA_DATAIN_L_data] --> 0x%08x\n",
                        REG_AUDIO_SDM_DWA_DATAIN_L,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_DWA_DATAIN_R (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_SDM_DWA_DATAIN_R'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_R(void);
/*! \brief Reads the bit group 'data' of register 'AUDIO_SDM_DWA_DATAIN_R'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_R_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_R(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_R);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_DWA_DATAIN_R] --> 0x%08x\n",
                        REG_AUDIO_SDM_DWA_DATAIN_R,value);
    #endif
    return value;
}
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_R_data(void)
{
    GH_AUDIO_SDM_DWA_DATAIN_R_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_R);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_SDM_DWA_DATAIN_R_data] --> 0x%08x\n",
                        REG_AUDIO_SDM_DWA_DATAIN_R,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_VALID_SIGNALS (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_VALID_SIGNALS'. */
U16  GH_AUDIO_get_VALID_SIGNALS(void);
/*! \brief Reads the bit group 'VALID_SIGNALS' of register 'AUDIO_VALID_SIGNALS'. */
U16  GH_AUDIO_get_VALID_SIGNALS_VALID_SIGNALS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_VALID_SIGNALS(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_VALID_SIGNALS);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_VALID_SIGNALS] --> 0x%08x\n",
                        REG_AUDIO_VALID_SIGNALS,value);
    #endif
    return value;
}
GH_INLINE U16  GH_AUDIO_get_VALID_SIGNALS_VALID_SIGNALS(void)
{
    GH_AUDIO_VALID_SIGNALS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_VALID_SIGNALS);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_VALID_SIGNALS_VALID_SIGNALS] --> 0x%08x\n",
                        REG_AUDIO_VALID_SIGNALS,value);
    #endif
    return tmp_value.bitc.valid_signals;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_MMP_DPGA_CFG1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1(U8 index, U16 data);
/*! \brief Reads the register 'AUDIO_MMP_DPGA_CFG1'. */
U16  GH_AUDIO_get_MMP_DPGA_CFG1(U8 index);
/*! \brief Writes the bit group 'DPGA_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_DPGA_EN(U8 index, U8 data);
/*! \brief Reads the bit group 'DPGA_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_DPGA_EN(U8 index);
/*! \brief Writes the bit group 'FADING_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_FADING_EN(U8 index, U8 data);
/*! \brief Reads the bit group 'FADING_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_FADING_EN(U8 index);
/*! \brief Writes the bit group 'MUTE_2_ZERO' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index, U8 data);
/*! \brief Reads the bit group 'MUTE_2_ZERO' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index);
/*! \brief Writes the bit group 'STEP' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_STEP(U8 index, U8 data);
/*! \brief Reads the bit group 'STEP' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_STEP(U8 index);
/*! \brief Writes the bit group 'OFFSET' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_OFFSET(U8 index, U8 data);
/*! \brief Reads the bit group 'OFFSET' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_OFFSET(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1(U8 index, U16 data)
{
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)) = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG1] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_MMP_DPGA_CFG1(U8 index)
{
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG1] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_DPGA_EN(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.dpga_en = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG1_DPGA_EN] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_DPGA_EN(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG1_DPGA_EN] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.dpga_en;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_FADING_EN(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.fading_en = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG1_FADING_EN] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_FADING_EN(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG1_FADING_EN] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.fading_en;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.mute_2_zero = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG1_MUTE_2_ZERO] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG1_MUTE_2_ZERO] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.mute_2_zero;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_STEP(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.step = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG1_STEP] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_STEP(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG1_STEP] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.step;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_OFFSET(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.offset = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG1_OFFSET] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_OFFSET(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG1_OFFSET] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG1 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.offset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_MMP_DPGA_CFG2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_MMP_DPGA_CFG2'. */
void GH_AUDIO_set_MMP_DPGA_CFG2(U8 index, U16 data);
/*! \brief Reads the register 'AUDIO_MMP_DPGA_CFG2'. */
U16  GH_AUDIO_get_MMP_DPGA_CFG2(U8 index);
/*! \brief Writes the bit group 'GAIN' of register 'AUDIO_MMP_DPGA_CFG2'. */
void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN(U8 index, U8 data);
/*! \brief Reads the bit group 'GAIN' of register 'AUDIO_MMP_DPGA_CFG2'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN(U8 index);
/*! \brief Writes the bit group 'GAIN_TRIG' of register 'AUDIO_MMP_DPGA_CFG2'. */
void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN_TRIG(U8 index, U8 data);
/*! \brief Reads the bit group 'GAIN_TRIG' of register 'AUDIO_MMP_DPGA_CFG2'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN_TRIG(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG2(U8 index, U16 data)
{
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)) = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG2] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)),data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_MMP_DPGA_CFG2(U8 index)
{
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG2] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG2_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.gain = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG2_GAIN] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG2_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG2_GAIN] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.gain;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN_TRIG(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG2_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C));
    d.bitc.gain_trig = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)) = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_MMP_DPGA_CFG2_GAIN_TRIG] <-- 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN_TRIG(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG2_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)));

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_MMP_DPGA_CFG2_GAIN_TRIG] --> 0x%08x\n",
                        (REG_AUDIO_MMP_DPGA_CFG2 + index * FIO_MOFFSET(AUDIO,0x000000C)),value);
    #endif
    return tmp_value.bitc.gain_trig;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_PGA_DPGA_CFG (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG(U16 data);
/*! \brief Reads the register 'AUDIO_PGA_DPGA_CFG'. */
U16  GH_AUDIO_get_PGA_DPGA_CFG(void);
/*! \brief Writes the bit group 'PGA2_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain(U8 data);
/*! \brief Reads the bit group 'PGA2_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain(void);
/*! \brief Writes the bit group 'PGA2_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain_trig(U8 data);
/*! \brief Reads the bit group 'PGA2_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain_trig(void);
/*! \brief Writes the bit group 'PGA2_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute(U8 data);
/*! \brief Reads the bit group 'PGA2_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_mute(void);
/*! \brief Writes the bit group 'PGA2_en' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_en(U8 data);
/*! \brief Reads the bit group 'PGA2_en' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_en(void);
/*! \brief Writes the bit group 'PGA1_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain(U8 data);
/*! \brief Reads the bit group 'PGA1_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain(void);
/*! \brief Writes the bit group 'PGA1_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain_trig(U8 data);
/*! \brief Reads the bit group 'PGA1_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain_trig(void);
/*! \brief Writes the bit group 'PGA1_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute(U8 data);
/*! \brief Reads the bit group 'PGA1_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_mute(void);
/*! \brief Writes the bit group 'PGA1_en' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_en(U8 data);
/*! \brief Reads the bit group 'PGA1_en' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG(U16 data)
{
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_PGA_DPGA_CFG(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga2_gain = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga2_gain;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain_trig(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga2_gain_trig = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain_trig] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain_trig(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain_trig] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga2_gain_trig;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga2_mute = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_mute(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA2_mute] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga2_mute;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_en(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga2_en = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA2_en] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_en(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA2_en] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga2_en;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga1_gain = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga1_gain;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain_trig(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga1_gain_trig = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain_trig] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain_trig(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain_trig] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga1_gain_trig;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga1_mute = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_mute(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA1_mute] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga1_mute;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_en(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG;
    d.bitc.pga1_en = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_PGA_DPGA_CFG_PGA1_en] <-- 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_en(void)
{
    GH_AUDIO_PGA_DPGA_CFG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_PGA_DPGA_CFG_PGA1_en] --> 0x%08x\n",
                        REG_AUDIO_PGA_DPGA_CFG,value);
    #endif
    return tmp_value.bitc.pga1_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_INT_DOUT (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_INT_DOUT'. */
U16  GH_AUDIO_get_INT_DOUT(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_INT_DOUT(U8 index)
{
    U16 value = (*(volatile U16 *)(REG_AUDIO_INT_DOUT + index * FIO_MOFFSET(AUDIO,0x00000004)));

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_INT_DOUT] --> 0x%08x\n",
                        (REG_AUDIO_INT_DOUT + index * FIO_MOFFSET(AUDIO,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_TH_CTRL0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_FIFO_TH_CTRL0'. */
void GH_AUDIO_set_FIFO_TH_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_FIFO_TH_CTRL0'. */
U16  GH_AUDIO_get_FIFO_TH_CTRL0(void);
/*! \brief Writes the bit group 'TX' of register 'AUDIO_FIFO_TH_CTRL0'. */
void GH_AUDIO_set_FIFO_TH_CTRL0_TX(U8 data);
/*! \brief Reads the bit group 'TX' of register 'AUDIO_FIFO_TH_CTRL0'. */
U8   GH_AUDIO_get_FIFO_TH_CTRL0_TX(void);
/*! \brief Writes the bit group 'RX' of register 'AUDIO_FIFO_TH_CTRL0'. */
void GH_AUDIO_set_FIFO_TH_CTRL0_RX(U8 data);
/*! \brief Reads the bit group 'RX' of register 'AUDIO_FIFO_TH_CTRL0'. */
U8   GH_AUDIO_get_FIFO_TH_CTRL0_RX(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_FIFO_TH_CTRL0(U16 data)
{
    *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_TH_CTRL0] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_TH_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_FIFO_TH_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_TH_CTRL0] --> 0x%08x\n",
                        REG_AUDIO_FIFO_TH_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_FIFO_TH_CTRL0_TX(U8 data)
{
    GH_AUDIO_FIFO_TH_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0;
    d.bitc.tx = data;
    *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_TH_CTRL0_TX] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_TH_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_TH_CTRL0_TX(void)
{
    GH_AUDIO_FIFO_TH_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_TH_CTRL0_TX] --> 0x%08x\n",
                        REG_AUDIO_FIFO_TH_CTRL0,value);
    #endif
    return tmp_value.bitc.tx;
}
GH_INLINE void GH_AUDIO_set_FIFO_TH_CTRL0_RX(U8 data)
{
    GH_AUDIO_FIFO_TH_CTRL0_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0;
    d.bitc.rx = data;
    *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_TH_CTRL0_RX] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_TH_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_TH_CTRL0_RX(void)
{
    GH_AUDIO_FIFO_TH_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_TH_CTRL0_RX] --> 0x%08x\n",
                        REG_AUDIO_FIFO_TH_CTRL0,value);
    #endif
    return tmp_value.bitc.rx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL(U16 data);
/*! \brief Reads the register 'AUDIO_FIFO_CTRL'. */
U16  GH_AUDIO_get_FIFO_CTRL(void);
/*! \brief Writes the bit group 'TX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_INT_EN(U8 data);
/*! \brief Reads the bit group 'TX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_INT_EN(void);
/*! \brief Writes the bit group 'TX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(U8 data);
/*! \brief Reads the bit group 'TX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_ENABLE(void);
/*! \brief Writes the bit group 'TX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'TX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_STATUS_CLR(void);
/*! \brief Writes the bit group 'RX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_INT_EN(U8 data);
/*! \brief Reads the bit group 'RX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_INT_EN(void);
/*! \brief Writes the bit group 'RX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_ENABLE(U8 data);
/*! \brief Reads the bit group 'RX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_ENABLE(void);
/*! \brief Writes the bit group 'RX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'RX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_STATUS_CLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_FIFO_CTRL(U16 data)
{
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_FIFO_CTRL(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_INT_EN(U8 data)
{
    GH_AUDIO_FIFO_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL;
    d.bitc.tx_fifo_int_en = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL_TX_FIFO_INT_EN] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_INT_EN(void)
{
    GH_AUDIO_FIFO_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL_TX_FIFO_INT_EN] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return tmp_value.bitc.tx_fifo_int_en;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(U8 data)
{
    GH_AUDIO_FIFO_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL;
    d.bitc.tx_fifo_enable = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_ENABLE(void)
{
    GH_AUDIO_FIFO_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL_TX_FIFO_ENABLE] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return tmp_value.bitc.tx_fifo_enable;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_STATUS_CLR(U8 data)
{
    GH_AUDIO_FIFO_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL;
    d.bitc.tx_fifo_status_clr = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL_TX_FIFO_STATUS_CLR] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_STATUS_CLR(void)
{
    GH_AUDIO_FIFO_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL_TX_FIFO_STATUS_CLR] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return tmp_value.bitc.tx_fifo_status_clr;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_INT_EN(U8 data)
{
    GH_AUDIO_FIFO_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL;
    d.bitc.rx_fifo_int_en = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL_RX_FIFO_INT_EN] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_INT_EN(void)
{
    GH_AUDIO_FIFO_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL_RX_FIFO_INT_EN] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return tmp_value.bitc.rx_fifo_int_en;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_ENABLE(U8 data)
{
    GH_AUDIO_FIFO_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL;
    d.bitc.rx_fifo_enable = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL_RX_FIFO_ENABLE] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_ENABLE(void)
{
    GH_AUDIO_FIFO_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL_RX_FIFO_ENABLE] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return tmp_value.bitc.rx_fifo_enable;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_STATUS_CLR(U8 data)
{
    GH_AUDIO_FIFO_CTRL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL;
    d.bitc.rx_fifo_status_clr = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_FIFO_CTRL_RX_FIFO_STATUS_CLR] <-- 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_STATUS_CLR(void)
{
    GH_AUDIO_FIFO_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_CTRL_RX_FIFO_STATUS_CLR] --> 0x%08x\n",
                        REG_AUDIO_FIFO_CTRL,value);
    #endif
    return tmp_value.bitc.rx_fifo_status_clr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_STS (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_FIFO_STS'. */
U16  GH_AUDIO_get_FIFO_STS(void);
/*! \brief Reads the bit group 'TX_FIFO_STATUS' of register 'AUDIO_FIFO_STS'. */
U8   GH_AUDIO_get_FIFO_STS_TX_FIFO_STATUS(void);
/*! \brief Reads the bit group 'RX_FIFO_STATUS' of register 'AUDIO_FIFO_STS'. */
U8   GH_AUDIO_get_FIFO_STS_RX_FIFO_STATUS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_FIFO_STS(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_STS);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_STS] --> 0x%08x\n",
                        REG_AUDIO_FIFO_STS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_STS_TX_FIFO_STATUS(void)
{
    GH_AUDIO_FIFO_STS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_STS);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_STS_TX_FIFO_STATUS] --> 0x%08x\n",
                        REG_AUDIO_FIFO_STS,value);
    #endif
    return tmp_value.bitc.tx_fifo_status;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_STS_RX_FIFO_STATUS(void)
{
    GH_AUDIO_FIFO_STS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_STS);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_FIFO_STS_RX_FIFO_STATUS] --> 0x%08x\n",
                        REG_AUDIO_FIFO_STS,value);
    #endif
    return tmp_value.bitc.rx_fifo_status;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_5_NF_H (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_NF_SYNTH_5_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_5_NF_H(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_5_NF_H(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_5_NF_H);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_5_NF_H] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_5_NF_H,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_5_NF_L (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_NF_SYNTH_5_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_5_NF_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_5_NF_L(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_5_NF_L);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_NF_SYNTH_5_NF_L] --> 0x%08x\n",
                        REG_AUDIO_NF_SYNTH_5_NF_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_INT_CTRL (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'AUDIO_INT_CTRL'. */
U16  GH_AUDIO_get_INT_CTRL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_AUDIO_get_INT_CTRL(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_INT_CTRL);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_INT_CTRL] --> 0x%08x\n",
                        REG_AUDIO_INT_CTRL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL00 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL00'. */
U16  GH_AUDIO_get_ANALOG_CTRL00(void);
/*! \brief Writes the bit group 'DBNC_TIME' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_DBNC_TIME(U8 data);
/*! \brief Reads the bit group 'DBNC_TIME' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_DBNC_TIME(void);
/*! \brief Writes the bit group 'MCPLS_SEL' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_SEL(U8 data);
/*! \brief Reads the bit group 'MCPLS_SEL' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_SEL(void);
/*! \brief Writes the bit group 'MCPLS_PRD' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_PRD(U8 data);
/*! \brief Reads the bit group 'MCPLS_PRD' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_PRD(void);
/*! \brief Writes the bit group '_RSTZ_AU_DET' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00__RSTZ_AU_DET(U8 data);
/*! \brief Reads the bit group '_RSTZ_AU_DET' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00__RSTZ_AU_DET(void);
/*! \brief Writes the bit group 'INT_AU_DET_TEST_VALUE' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(U8 data);
/*! \brief Reads the bit group 'INT_AU_DET_TEST_VALUE' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(void);
/*! \brief Writes the bit group 'INT_AU_DET_TEST_MODE' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(U8 data);
/*! \brief Reads the bit group 'INT_AU_DET_TEST_MODE' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(void);
/*! \brief Writes the bit group 'MCPLS_EN' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_EN(U8 data);
/*! \brief Reads the bit group 'MCPLS_EN' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL00(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_DBNC_TIME(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc.dbnc_time = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00_DBNC_TIME] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_DBNC_TIME(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00_DBNC_TIME] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc.dbnc_time;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc.mcpls_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00_MCPLS_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00_MCPLS_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc.mcpls_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_PRD(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc.mcpls_prd = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00_MCPLS_PRD] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_PRD(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00_MCPLS_PRD] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc.mcpls_prd;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00__RSTZ_AU_DET(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc._rstz_au_det = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00__RSTZ_AU_DET] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00__RSTZ_AU_DET(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00__RSTZ_AU_DET] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc._rstz_au_det;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc.int_au_det_test_value = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc.int_au_det_test_value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc.int_au_det_test_mode = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_MODE] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_MODE] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc.int_au_det_test_mode;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_EN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00;
    d.bitc.mcpls_en = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL00_MCPLS_EN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_EN(void)
{
    GH_AUDIO_ANALOG_CTRL00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL00_MCPLS_EN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL00,value);
    #endif
    return tmp_value.bitc.mcpls_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL01 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL01'. */
U16  GH_AUDIO_get_ANALOG_CTRL01(void);
/*! \brief Writes the bit group 'INT_MASK_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_MASK_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(void);
/*! \brief Writes the bit group 'INT_MASK_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_MASK_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(void);
/*! \brief Writes the bit group 'INT_MASK_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_MASK_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(void);
/*! \brief Writes the bit group 'INT_MASK_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_MASK_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(void);
/*! \brief Writes the bit group 'INT_MASK_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_MASK_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(void);
/*! \brief Writes the bit group 'INT_MASK_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_MASK_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(void);
/*! \brief Writes the bit group 'INT_MASK_HS_GND' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_GND(U8 data);
/*! \brief Reads the bit group 'INT_MASK_HS_GND' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_GND(void);
/*! \brief Writes the bit group 'INT_CLR_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_CLR_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(void);
/*! \brief Writes the bit group 'INT_CLR_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_CLR_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(void);
/*! \brief Writes the bit group 'INT_CLR_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_CLR_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(void);
/*! \brief Writes the bit group 'INT_CLR_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_CLR_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(void);
/*! \brief Writes the bit group 'INT_CLR_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_CLR_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(void);
/*! \brief Writes the bit group 'INT_CLR_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_CLR_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(void);
/*! \brief Writes the bit group 'INT_CLR_HS_GNC' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_GNC(U8 data);
/*! \brief Reads the bit group 'INT_CLR_HS_GNC' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_GNC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL01(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_miclp_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_miclp_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_miclp_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_miclp_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_spk_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_spk_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_spk_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_spk_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_hs_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_PLUGIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_PLUGIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_hs_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_hs_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_UNPLUG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_UNPLUG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_hs_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_GND(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_mask_hs_gnd = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_GND] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_GND(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_GND] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_mask_hs_gnd;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_miclp_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_miclp_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_miclp_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_miclp_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_spk_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_spk_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_spk_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_spk_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_hs_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_PLUGIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_PLUGIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_hs_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_hs_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_UNPLUG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_UNPLUG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_hs_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_GNC(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01;
    d.bitc.int_clr_hs_gnc = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_GNC] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_GNC(void)
{
    GH_AUDIO_ANALOG_CTRL01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_GNC] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL01,value);
    #endif
    return tmp_value.bitc.int_clr_hs_gnc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL02 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL02'. */
U16  GH_AUDIO_get_ANALOG_CTRL02(void);
/*! \brief Writes the bit group 'sdm_out_3_4_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_3_4_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_sel(void);
/*! \brief Writes the bit group 'sdm_out_1_2_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_1_2_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_sel(void);
/*! \brief Writes the bit group 'sdm_out_3_4_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_3_4_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(void);
/*! \brief Writes the bit group 'sdm_out_1_2_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_1_2_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(void);
/*! \brief Writes the bit group 'sdm_out_4_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_4_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_4_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_4_12_inv_sel(void);
/*! \brief Writes the bit group 'sdm_out_3_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_3_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_12_inv_sel(void);
/*! \brief Writes the bit group 'sdm_out_2_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_2_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_2_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_2_12_inv_sel(void);
/*! \brief Writes the bit group 'sdm_out_1_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_1_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_12_inv_sel(void);
/*! \brief Writes the bit group 'dft_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_dft_sel(U8 data);
/*! \brief Reads the bit group 'dft_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_dft_sel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL02(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_3_4_12_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_3_4_12_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_1_2_12_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_1_2_12_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_3_4_12_swap_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_3_4_12_swap_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_1_2_12_swap_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_1_2_12_swap_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_4_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_4_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_4_12_inv_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_4_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_4_12_inv_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_4_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_3_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_12_inv_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_12_inv_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_3_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_2_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_2_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_2_12_inv_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_2_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_2_12_inv_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_2_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.sdm_out_1_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_12_inv_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_12_inv_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.sdm_out_1_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_dft_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02;
    d.bitc.dft_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL02_dft_sel] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_dft_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL02_dft_sel] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL02,value);
    #endif
    return tmp_value.bitc.dft_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL03 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL03'. */
U16  GH_AUDIO_get_ANALOG_CTRL03(void);
/*! \brief Writes the bit group 'SEL_IREFDET' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_SEL_IREFDET(U8 data);
/*! \brief Reads the bit group 'SEL_IREFDET' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_SEL_IREFDET(void);
/*! \brief Writes the bit group 'REG_EN_MICBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_REG_EN_MICBIAS_12(U8 data);
/*! \brief Reads the bit group 'REG_EN_MICBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_REG_EN_MICBIAS_12(void);
/*! \brief Writes the bit group 'MICV_SEL' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_MICV_SEL(U8 data);
/*! \brief Reads the bit group 'MICV_SEL' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_MICV_SEL(void);
/*! \brief Writes the bit group 'RCV_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_RCV_EN_12(U8 data);
/*! \brief Reads the bit group 'RCV_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_RCV_EN_12(void);
/*! \brief Writes the bit group 'HST_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_HST_EN_12(U8 data);
/*! \brief Reads the bit group 'HST_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_HST_EN_12(void);
/*! \brief Writes the bit group 'EN_MICDET_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_MICDET_12(U8 data);
/*! \brief Reads the bit group 'EN_MICDET_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_MICDET_12(void);
/*! \brief Writes the bit group 'REG_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_REG_CONTROL(U8 data);
/*! \brief Reads the bit group 'REG_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_REG_CONTROL(void);
/*! \brief Writes the bit group 'REG_SEL_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_REG_SEL_CONTROL(U8 data);
/*! \brief Reads the bit group 'REG_SEL_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_REG_SEL_CONTROL(void);
/*! \brief Writes the bit group 'EN_REF_NO_BG_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_REF_NO_BG_12(U8 data);
/*! \brief Reads the bit group 'EN_REF_NO_BG_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_REF_NO_BG_12(void);
/*! \brief Writes the bit group 'EN_POLLING_DRV_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_POLLING_DRV_12(U8 data);
/*! \brief Reads the bit group 'EN_POLLING_DRV_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_POLLING_DRV_12(void);
/*! \brief Writes the bit group 'IBSEL_AUDIO' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_IBSEL_AUDIO(U8 data);
/*! \brief Reads the bit group 'IBSEL_AUDIO' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_IBSEL_AUDIO(void);
/*! \brief Writes the bit group 'EN_AUDIO_IBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(U8 data);
/*! \brief Reads the bit group 'EN_AUDIO_IBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(void);
/*! \brief Writes the bit group 'EN_CLK_TST' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_CLK_TST(U8 data);
/*! \brief Reads the bit group 'EN_CLK_TST' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_CLK_TST(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL03(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_SEL_IREFDET(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.sel_irefdet = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_SEL_IREFDET] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_SEL_IREFDET(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_SEL_IREFDET] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.sel_irefdet;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_REG_EN_MICBIAS_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.reg_en_micbias_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_REG_EN_MICBIAS_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_REG_EN_MICBIAS_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_REG_EN_MICBIAS_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.reg_en_micbias_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_MICV_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.micv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_MICV_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_MICV_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_MICV_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.micv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_RCV_EN_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.rcv_en_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_RCV_EN_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_RCV_EN_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_RCV_EN_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.rcv_en_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_HST_EN_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.hst_en_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_HST_EN_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_HST_EN_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_HST_EN_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.hst_en_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_MICDET_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.en_micdet_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_EN_MICDET_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_MICDET_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_EN_MICDET_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.en_micdet_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_REG_CONTROL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.reg_control = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_REG_CONTROL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_REG_CONTROL(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_REG_CONTROL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.reg_control;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_REG_SEL_CONTROL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.reg_sel_control = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_REG_SEL_CONTROL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_REG_SEL_CONTROL(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_REG_SEL_CONTROL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.reg_sel_control;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_REF_NO_BG_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.en_ref_no_bg_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_EN_REF_NO_BG_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_REF_NO_BG_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_EN_REF_NO_BG_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.en_ref_no_bg_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_POLLING_DRV_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.en_polling_drv_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_EN_POLLING_DRV_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_POLLING_DRV_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_EN_POLLING_DRV_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.en_polling_drv_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_IBSEL_AUDIO(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.ibsel_audio = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_IBSEL_AUDIO] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_IBSEL_AUDIO(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_IBSEL_AUDIO] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.ibsel_audio;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.en_audio_ibias_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_EN_AUDIO_IBIAS_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_EN_AUDIO_IBIAS_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.en_audio_ibias_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_CLK_TST(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03;
    d.bitc.en_clk_tst = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL03_EN_CLK_TST] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_CLK_TST(void)
{
    GH_AUDIO_ANALOG_CTRL03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL03_EN_CLK_TST] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL03,value);
    #endif
    return tmp_value.bitc.en_clk_tst;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL04 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL04'. */
U16  GH_AUDIO_get_ANALOG_CTRL04(void);
/*! \brief Writes the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2SEL(void);
/*! \brief Writes the bit group 'PGA0_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA2' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA2(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA2' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA2(void);
/*! \brief Writes the bit group 'PGA0_MICA1_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA1_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA1_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA1_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA1' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA1(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA1' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA1(void);
/*! \brief Writes the bit group 'IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_IBIAS_PGA0(U8 data);
/*! \brief Reads the bit group 'IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_IBIAS_PGA0(void);
/*! \brief Writes the bit group 'EN_IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_IBIAS_PGA0(U8 data);
/*! \brief Reads the bit group 'EN_IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_IBIAS_PGA0(void);
/*! \brief Writes the bit group 'EN_VCMBUF0_12' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_VCMBUF0_12(U8 data);
/*! \brief Reads the bit group 'EN_VCMBUF0_12' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_VCMBUF0_12(void);
/*! \brief Writes the bit group 'SEL_VCMREF0' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_SEL_VCMREF0(U8 data);
/*! \brief Reads the bit group 'SEL_VCMREF0' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_VCMREF0(void);
/*! \brief Writes the bit group 'PULLUP_HSIP' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PULLUP_HSIP(U8 data);
/*! \brief Reads the bit group 'PULLUP_HSIP' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PULLUP_HSIP(void);
/*! \brief Writes the bit group 'EN_MICDET_LP_12' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_MICDET_LP_12(U8 data);
/*! \brief Reads the bit group 'EN_MICDET_LP_12' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICDET_LP_12(void);
/*! \brief Writes the bit group 'EN_MICTRIM_12' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_MICTRIM_12(U8 data);
/*! \brief Reads the bit group 'EN_MICTRIM_12' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICTRIM_12(void);
/*! \brief Writes the bit group 'SEL_IREFGND' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_SEL_IREFGND(U8 data);
/*! \brief Reads the bit group 'SEL_IREFGND' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_IREFGND(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL04(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.pga0_mica2sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2SEL(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.pga0_mica2sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.pga0_mica2_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2_GAIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.pga0_mica2_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA2(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.en_pga0_mica2 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA2] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA2(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA2] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.en_pga0_mica2;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA1_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.pga0_mica1_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA1_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA1_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA1_GAIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.pga0_mica1_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.en_pga0_mica1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA1(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.en_pga0_mica1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_IBIAS_PGA0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.ibias_pga0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_IBIAS_PGA0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_IBIAS_PGA0(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_IBIAS_PGA0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.ibias_pga0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_IBIAS_PGA0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.en_ibias_pga0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_EN_IBIAS_PGA0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_IBIAS_PGA0(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_EN_IBIAS_PGA0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.en_ibias_pga0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_VCMBUF0_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.en_vcmbuf0_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_EN_VCMBUF0_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_VCMBUF0_12(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_EN_VCMBUF0_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.en_vcmbuf0_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_SEL_VCMREF0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.sel_vcmref0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_SEL_VCMREF0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_VCMREF0(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_SEL_VCMREF0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.sel_vcmref0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PULLUP_HSIP(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.pullup_hsip = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_PULLUP_HSIP] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PULLUP_HSIP(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_PULLUP_HSIP] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.pullup_hsip;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_MICDET_LP_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.en_micdet_lp_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_EN_MICDET_LP_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICDET_LP_12(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_EN_MICDET_LP_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.en_micdet_lp_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_MICTRIM_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.en_mictrim_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_EN_MICTRIM_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICTRIM_12(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_EN_MICTRIM_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.en_mictrim_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_SEL_IREFGND(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04;
    d.bitc.sel_irefgnd = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL04_SEL_IREFGND] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_IREFGND(void)
{
    GH_AUDIO_ANALOG_CTRL04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL04_SEL_IREFGND] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL04,value);
    #endif
    return tmp_value.bitc.sel_irefgnd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL05 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL05'. */
U16  GH_AUDIO_get_ANALOG_CTRL05(void);
/*! \brief Writes the bit group 'IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_IBIAS_PGA1(U8 data);
/*! \brief Reads the bit group 'IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_IBIAS_PGA1(void);
/*! \brief Writes the bit group 'EN_IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_IBIAS_PGA1(U8 data);
/*! \brief Reads the bit group 'EN_IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_IBIAS_PGA1(void);
/*! \brief Writes the bit group 'EN_VCMBUF1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_VCMBUF1(U8 data);
/*! \brief Reads the bit group 'EN_VCMBUF1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_VCMBUF1(void);
/*! \brief Writes the bit group 'SEL_VCMREF1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_SEL_VCMREF1(U8 data);
/*! \brief Reads the bit group 'SEL_VCMREF1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_SEL_VCMREF1(void);
/*! \brief Writes the bit group 'PGA0_LINE_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_LINE_SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_LINE_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_LINE_SEL(void);
/*! \brief Writes the bit group 'PGA0_MUTE_R' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_R(U8 data);
/*! \brief Reads the bit group 'PGA0_MUTE_R' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_R(void);
/*! \brief Writes the bit group 'PGA0_MICA4_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA4_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_SEL(void);
/*! \brief Writes the bit group 'PGA0_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA4' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA4(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA4' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA4(void);
/*! \brief Writes the bit group 'PGA0_MICA3_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA3_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA3_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA3_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA3' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA3(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA3' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA3(void);
/*! \brief Writes the bit group 'PGA0_MUTE_L' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_L(U8 data);
/*! \brief Reads the bit group 'PGA0_MUTE_L' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_L(void);
/*! \brief Writes the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA2SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA2SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL05(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_IBIAS_PGA1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.ibias_pga1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_IBIAS_PGA1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_IBIAS_PGA1(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_IBIAS_PGA1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.ibias_pga1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_IBIAS_PGA1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.en_ibias_pga1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_EN_IBIAS_PGA1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_IBIAS_PGA1(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_EN_IBIAS_PGA1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.en_ibias_pga1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_VCMBUF1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.en_vcmbuf1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_EN_VCMBUF1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_VCMBUF1(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_EN_VCMBUF1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.en_vcmbuf1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_SEL_VCMREF1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.sel_vcmref1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_SEL_VCMREF1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_SEL_VCMREF1(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_SEL_VCMREF1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.sel_vcmref1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_LINE_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_line_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_LINE_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_LINE_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_LINE_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_line_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_mute_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_R(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_mute_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_mica4_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_mica4_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_mica4_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_GAIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_mica4_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA4(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.en_pga0_mica4 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA4] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA4(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA4] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.en_pga0_mica4;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA3_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_mica3_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA3_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA3_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA3_GAIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_mica3_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA3(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.en_pga0_mica3 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA3] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA3(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA3] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.en_pga0_mica3;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_mute_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_L(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_mute_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA2SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05;
    d.bitc.pga0_mica2sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA2SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA2SEL(void)
{
    GH_AUDIO_ANALOG_CTRL05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA2SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL05,value);
    #endif
    return tmp_value.bitc.pga0_mica2sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL06 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL06'. */
U16  GH_AUDIO_get_ANALOG_CTRL06(void);
/*! \brief Writes the bit group 'EN_DAC0_R_12' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_R_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC0_R_12' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_R_12(void);
/*! \brief Writes the bit group 'EN_DAC0_L_12' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_L_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC0_L_12' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_L_12(void);
/*! \brief Writes the bit group 'EN_DAC0_LDO11' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_LDO11(U8 data);
/*! \brief Reads the bit group 'EN_DAC0_LDO11' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_LDO11(void);
/*! \brief Writes the bit group 'LDO11_VC0' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_LDO11_VC0(U8 data);
/*! \brief Reads the bit group 'LDO11_VC0' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_LDO11_VC0(void);
/*! \brief Writes the bit group 'POS_RL0' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_POS_RL0(U8 data);
/*! \brief Reads the bit group 'POS_RL0' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_POS_RL0(void);
/*! \brief Writes the bit group 'PGA1_LINE_SEL' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_LINE_SEL(U8 data);
/*! \brief Reads the bit group 'PGA1_LINE_SEL' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_LINE_SEL(void);
/*! \brief Writes the bit group 'PGA1_MUTE_R' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_R(U8 data);
/*! \brief Reads the bit group 'PGA1_MUTE_R' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_R(void);
/*! \brief Writes the bit group 'PGA1_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA4_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA1_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA4_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA1_MICA4' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA4(U8 data);
/*! \brief Reads the bit group 'EN_PGA1_MICA4' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA4(void);
/*! \brief Writes the bit group 'PGA1_MUTE_L' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_L(U8 data);
/*! \brief Reads the bit group 'PGA1_MUTE_L' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_L(void);
/*! \brief Writes the bit group 'PGA1_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA2_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA1_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA2_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA1_MICA2' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA2(U8 data);
/*! \brief Reads the bit group 'EN_PGA1_MICA2' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL06(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_R_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.en_dac0_r_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_R_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_R_12(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_R_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.en_dac0_r_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_L_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.en_dac0_l_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_L_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_L_12(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_L_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.en_dac0_l_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_LDO11(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.en_dac0_ldo11 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_LDO11] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_LDO11(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_LDO11] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.en_dac0_ldo11;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_LDO11_VC0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.ldo11_vc0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_LDO11_VC0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_LDO11_VC0(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_LDO11_VC0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.ldo11_vc0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_POS_RL0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.pos_rl0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_POS_RL0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_POS_RL0(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_POS_RL0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.pos_rl0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_LINE_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.pga1_line_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_PGA1_LINE_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_LINE_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_PGA1_LINE_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.pga1_line_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.pga1_mute_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_R(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.pga1_mute_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA4_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.pga1_mica4_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA4_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA4_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA4_GAIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.pga1_mica4_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA4(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.en_pga1_mica4 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA4] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA4(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA4] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.en_pga1_mica4;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.pga1_mute_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_L(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.pga1_mute_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA2_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.pga1_mica2_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA2_GAIN] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA2_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA2_GAIN] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.pga1_mica2_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA2(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06;
    d.bitc.en_pga1_mica2 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA2] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA2(void)
{
    GH_AUDIO_ANALOG_CTRL06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA2] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL06,value);
    #endif
    return tmp_value.bitc.en_pga1_mica2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL07 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL07'. */
U16  GH_AUDIO_get_ANALOG_CTRL07(void);
/*! \brief Writes the bit group 'EN_ADC1_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC1_DIT(U8 data);
/*! \brief Reads the bit group 'EN_ADC1_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC1_DIT(void);
/*! \brief Writes the bit group 'EN_ADC0_12' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_12(U8 data);
/*! \brief Reads the bit group 'EN_ADC0_12' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_12(void);
/*! \brief Writes the bit group 'SHRT_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_L(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_L(void);
/*! \brief Writes the bit group 'SHRT_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_R(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_R(void);
/*! \brief Writes the bit group 'RESET_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_L(U8 data);
/*! \brief Reads the bit group 'RESET_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_L(void);
/*! \brief Writes the bit group 'RESET_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_R(U8 data);
/*! \brief Reads the bit group 'RESET_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_R(void);
/*! \brief Writes the bit group 'SEL_IBIAS_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SEL_IBIAS_ADC0(U8 data);
/*! \brief Reads the bit group 'SEL_IBIAS_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_IBIAS_ADC0(void);
/*! \brief Writes the bit group 'SEL_DIT_LVL_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(U8 data);
/*! \brief Reads the bit group 'SEL_DIT_LVL_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(void);
/*! \brief Writes the bit group 'EN_ADC0_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_DIT(U8 data);
/*! \brief Reads the bit group 'EN_ADC0_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_DIT(void);
/*! \brief Writes the bit group 'EN_DAC1_R_12' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_R_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC1_R_12' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_R_12(void);
/*! \brief Writes the bit group 'EN_DAC1_L_12' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_L_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC1_L_12' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_L_12(void);
/*! \brief Writes the bit group 'EN_DAC1_LDO11' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_LDO11(U8 data);
/*! \brief Reads the bit group 'EN_DAC1_LDO11' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_LDO11(void);
/*! \brief Writes the bit group 'LDO11_VC1' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_LDO11_VC1(U8 data);
/*! \brief Reads the bit group 'LDO11_VC1' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_LDO11_VC1(void);
/*! \brief Writes the bit group 'POS_RL1' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_POS_RL1(U8 data);
/*! \brief Reads the bit group 'POS_RL1' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_POS_RL1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL07(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC1_DIT(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.en_adc1_dit = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_EN_ADC1_DIT] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC1_DIT(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_EN_ADC1_DIT] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.en_adc1_dit;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.en_adc0_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_12(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.en_adc0_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.shrt_adc0_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_L(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.shrt_adc0_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.shrt_adc0_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_R(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.shrt_adc0_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.reset_adc0_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_L(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.reset_adc0_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.reset_adc0_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_R(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.reset_adc0_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SEL_IBIAS_ADC0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.sel_ibias_adc0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_SEL_IBIAS_ADC0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_IBIAS_ADC0(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_SEL_IBIAS_ADC0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.sel_ibias_adc0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.sel_dit_lvl_adc0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_SEL_DIT_LVL_ADC0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_SEL_DIT_LVL_ADC0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.sel_dit_lvl_adc0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_DIT(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.en_adc0_dit = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_DIT] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_DIT(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_DIT] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.en_adc0_dit;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_R_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.en_dac1_r_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_R_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_R_12(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_R_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.en_dac1_r_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_L_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.en_dac1_l_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_L_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_L_12(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_L_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.en_dac1_l_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_LDO11(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.en_dac1_ldo11 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_LDO11] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_LDO11(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_LDO11] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.en_dac1_ldo11;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_LDO11_VC1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.ldo11_vc1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_LDO11_VC1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_LDO11_VC1(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_LDO11_VC1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.ldo11_vc1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_POS_RL1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07;
    d.bitc.pos_rl1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL07_POS_RL1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_POS_RL1(void)
{
    GH_AUDIO_ANALOG_CTRL07_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL07_POS_RL1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL07,value);
    #endif
    return tmp_value.bitc.pos_rl1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL08 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL08'. */
U16  GH_AUDIO_get_ANALOG_CTRL08(void);
/*! \brief Writes the bit group 'GAIN_EAR' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_GAIN_EAR(U8 data);
/*! \brief Reads the bit group 'GAIN_EAR' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_GAIN_EAR(void);
/*! \brief Writes the bit group 'EN_STG2AB_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_STG2AB_12(U8 data);
/*! \brief Reads the bit group 'EN_STG2AB_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_STG2AB_12(void);
/*! \brief Writes the bit group 'EN_OPLP_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_OPLP_12(U8 data);
/*! \brief Reads the bit group 'EN_OPLP_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_OPLP_12(void);
/*! \brief Writes the bit group 'EN_EARL_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_EARL_12(U8 data);
/*! \brief Reads the bit group 'EN_EARL_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARL_12(void);
/*! \brief Writes the bit group 'EN_EARR_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_EARR_12(U8 data);
/*! \brief Reads the bit group 'EN_EARR_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARR_12(void);
/*! \brief Writes the bit group 'EN_ADC1_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_ADC1_12(U8 data);
/*! \brief Reads the bit group 'EN_ADC1_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_ADC1_12(void);
/*! \brief Writes the bit group 'SHRT_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_L(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_L(void);
/*! \brief Writes the bit group 'SHRT_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_R(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_R(void);
/*! \brief Writes the bit group 'RESET_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_L(U8 data);
/*! \brief Reads the bit group 'RESET_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_L(void);
/*! \brief Writes the bit group 'RESET_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_R(U8 data);
/*! \brief Reads the bit group 'RESET_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_R(void);
/*! \brief Writes the bit group 'SEL_IBIAS_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SEL_IBIAS_ADC1(U8 data);
/*! \brief Reads the bit group 'SEL_IBIAS_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_IBIAS_ADC1(void);
/*! \brief Writes the bit group 'SEL_DIT_LVL_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(U8 data);
/*! \brief Reads the bit group 'SEL_DIT_LVL_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL08(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_GAIN_EAR(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.gain_ear = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_GAIN_EAR] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_GAIN_EAR(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_GAIN_EAR] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.gain_ear;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_STG2AB_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.en_stg2ab_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_EN_STG2AB_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_STG2AB_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_EN_STG2AB_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.en_stg2ab_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_OPLP_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.en_oplp_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_EN_OPLP_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_OPLP_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_EN_OPLP_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.en_oplp_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_EARL_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.en_earl_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_EN_EARL_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARL_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_EN_EARL_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.en_earl_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_EARR_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.en_earr_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_EN_EARR_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARR_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_EN_EARR_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.en_earr_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_ADC1_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.en_adc1_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_EN_ADC1_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_ADC1_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_EN_ADC1_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.en_adc1_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.shrt_adc1_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_L(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.shrt_adc1_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.shrt_adc1_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_R(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.shrt_adc1_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.reset_adc1_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_L(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.reset_adc1_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.reset_adc1_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_R(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.reset_adc1_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SEL_IBIAS_ADC1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.sel_ibias_adc1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_SEL_IBIAS_ADC1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_IBIAS_ADC1(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_SEL_IBIAS_ADC1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.sel_ibias_adc1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08;
    d.bitc.sel_dit_lvl_adc1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL08_SEL_DIT_LVL_ADC1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(void)
{
    GH_AUDIO_ANALOG_CTRL08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL08_SEL_DIT_LVL_ADC1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL08,value);
    #endif
    return tmp_value.bitc.sel_dit_lvl_adc1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL09 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL09'. */
U16  GH_AUDIO_get_ANALOG_CTRL09(void);
/*! \brief Writes the bit group 'MX_EAR' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_MX_EAR(U8 data);
/*! \brief Reads the bit group 'MX_EAR' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_MX_EAR(void);
/*! \brief Writes the bit group 'ISEL_OCP' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_ISEL_OCP(U8 data);
/*! \brief Reads the bit group 'ISEL_OCP' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_OCP(void);
/*! \brief Writes the bit group 'ISEL_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_ISEL_DRV(U8 data);
/*! \brief Reads the bit group 'ISEL_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_DRV(void);
/*! \brief Writes the bit group 'TST_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_TST_DRV(U8 data);
/*! \brief Reads the bit group 'TST_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_TST_DRV(void);
/*! \brief Writes the bit group 'EAR_MUTE' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_EAR_MUTE(U8 data);
/*! \brief Reads the bit group 'EAR_MUTE' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_MUTE(void);
/*! \brief Writes the bit group 'EAR_POPRES' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_EAR_POPRES(U8 data);
/*! \brief Reads the bit group 'EAR_POPRES' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_POPRES(void);
/*! \brief Writes the bit group 'TCSEL' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_TCSEL(U8 data);
/*! \brief Reads the bit group 'TCSEL' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_TCSEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL09(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_MX_EAR(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.mx_ear = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_MX_EAR] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_MX_EAR(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_MX_EAR] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.mx_ear;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_ISEL_OCP(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.isel_ocp = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_ISEL_OCP] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_OCP(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_ISEL_OCP] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.isel_ocp;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_ISEL_DRV(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.isel_drv = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_ISEL_DRV] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_DRV(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_ISEL_DRV] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.isel_drv;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_TST_DRV(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.tst_drv = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_TST_DRV] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_TST_DRV(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_TST_DRV] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.tst_drv;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_EAR_MUTE(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.ear_mute = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_EAR_MUTE] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_MUTE(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_EAR_MUTE] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.ear_mute;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_EAR_POPRES(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.ear_popres = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_EAR_POPRES] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_POPRES(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_EAR_POPRES] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.ear_popres;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_TCSEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09;
    d.bitc.tcsel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL09_TCSEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_TCSEL(void)
{
    GH_AUDIO_ANALOG_CTRL09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL09_TCSEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL09,value);
    #endif
    return tmp_value.bitc.tcsel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL10 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL10'. */
U16  GH_AUDIO_get_ANALOG_CTRL10(void);
/*! \brief Writes the bit group 'MUTE_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE1(U8 data);
/*! \brief Reads the bit group 'MUTE_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE1(void);
/*! \brief Writes the bit group 'MX_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE1(U8 data);
/*! \brief Reads the bit group 'MX_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE1(void);
/*! \brief Writes the bit group 'GAIN_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE1(U8 data);
/*! \brief Reads the bit group 'GAIN_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE1(void);
/*! \brief Writes the bit group 'EN_LINE1_R' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_R(U8 data);
/*! \brief Reads the bit group 'EN_LINE1_R' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_R(void);
/*! \brief Writes the bit group 'EN_LINE1_L' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_L(U8 data);
/*! \brief Reads the bit group 'EN_LINE1_L' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_L(void);
/*! \brief Writes the bit group 'MUTE_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE0(U8 data);
/*! \brief Reads the bit group 'MUTE_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE0(void);
/*! \brief Writes the bit group 'MX_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE0(U8 data);
/*! \brief Reads the bit group 'MX_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE0(void);
/*! \brief Writes the bit group 'GAIN_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE0(U8 data);
/*! \brief Reads the bit group 'GAIN_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE0(void);
/*! \brief Writes the bit group 'EN_LINE0_R' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_R(U8 data);
/*! \brief Reads the bit group 'EN_LINE0_R' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_R(void);
/*! \brief Writes the bit group 'EN_LINE0_L' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_L(U8 data);
/*! \brief Reads the bit group 'EN_LINE0_L' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL10(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.mute_line1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE1(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.mute_line1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.mx_line1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_MX_LINE1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE1(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_MX_LINE1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.mx_line1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.gain_line1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE1] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE1(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE1] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.gain_line1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.en_line1_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_R(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.en_line1_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.en_line1_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_L(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.en_line1_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.mute_line0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE0(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.mute_line0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.mx_line0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_MX_LINE0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE0(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_MX_LINE0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.mx_line0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.gain_line0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE0] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE0(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE0] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.gain_line0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.en_line0_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_R] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_R(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_R] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.en_line0_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10;
    d.bitc.en_line0_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_L] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_L(void)
{
    GH_AUDIO_ANALOG_CTRL10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_L] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL10,value);
    #endif
    return tmp_value.bitc.en_line0_l;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL11 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL11'. */
U16  GH_AUDIO_get_ANALOG_CTRL11(void);
/*! \brief Writes the bit group 'TST_AUTIO' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_TST_AUTIO(U8 data);
/*! \brief Reads the bit group 'TST_AUTIO' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_TST_AUTIO(void);
/*! \brief Writes the bit group 'SEL_CK_AUDIO' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_SEL_CK_AUDIO(U8 data);
/*! \brief Reads the bit group 'SEL_CK_AUDIO' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_CK_AUDIO(void);
/*! \brief Writes the bit group 'SEL_PHS_ADCCLK' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_SEL_PHS_ADCCLK(U8 data);
/*! \brief Reads the bit group 'SEL_PHS_ADCCLK' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_PHS_ADCCLK(void);
/*! \brief Writes the bit group 'ADC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_ADC_CLK_FREQ(U8 data);
/*! \brief Reads the bit group 'ADC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_ADC_CLK_FREQ(void);
/*! \brief Writes the bit group 'DAC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_DAC_CLK_FREQ(U8 data);
/*! \brief Reads the bit group 'DAC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_DAC_CLK_FREQ(void);
/*! \brief Writes the bit group 'EN_CLK' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_EN_CLK(U8 data);
/*! \brief Reads the bit group 'EN_CLK' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_EN_CLK(void);
/*! \brief Writes the bit group 'V_SET_LDO25' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_V_SET_LDO25(U8 data);
/*! \brief Reads the bit group 'V_SET_LDO25' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_V_SET_LDO25(void);
/*! \brief Writes the bit group 'EN_LDO25_12' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_EN_LDO25_12(U8 data);
/*! \brief Reads the bit group 'EN_LDO25_12' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_EN_LDO25_12(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL11(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_TST_AUTIO(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.tst_autio = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_TST_AUTIO] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_TST_AUTIO(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_TST_AUTIO] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.tst_autio;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_SEL_CK_AUDIO(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.sel_ck_audio = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_SEL_CK_AUDIO] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_CK_AUDIO(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_SEL_CK_AUDIO] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.sel_ck_audio;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_SEL_PHS_ADCCLK(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.sel_phs_adcclk = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_SEL_PHS_ADCCLK] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_PHS_ADCCLK(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_SEL_PHS_ADCCLK] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.sel_phs_adcclk;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_ADC_CLK_FREQ(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.adc_clk_freq = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_ADC_CLK_FREQ] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_ADC_CLK_FREQ(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_ADC_CLK_FREQ] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.adc_clk_freq;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_DAC_CLK_FREQ(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.dac_clk_freq = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_DAC_CLK_FREQ] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_DAC_CLK_FREQ(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_DAC_CLK_FREQ] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.dac_clk_freq;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_EN_CLK(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.en_clk = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_EN_CLK] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_EN_CLK(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_EN_CLK] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.en_clk;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_V_SET_LDO25(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.v_set_ldo25 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_V_SET_LDO25] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_V_SET_LDO25(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_V_SET_LDO25] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.v_set_ldo25;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_EN_LDO25_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11;
    d.bitc.en_ldo25_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL11_EN_LDO25_12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_EN_LDO25_12(void)
{
    GH_AUDIO_ANALOG_CTRL11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL11_EN_LDO25_12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL11,value);
    #endif
    return tmp_value.bitc.en_ldo25_12;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL12 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL12'. */
void GH_AUDIO_set_ANALOG_CTRL12(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL12'. */
U16  GH_AUDIO_get_ANALOG_CTRL12(void);
/*! \brief Writes the bit group 'AUDIO_REG' of register 'AUDIO_ANALOG_CTRL12'. */
void GH_AUDIO_set_ANALOG_CTRL12_AUDIO_REG(U8 data);
/*! \brief Reads the bit group 'AUDIO_REG' of register 'AUDIO_ANALOG_CTRL12'. */
U8   GH_AUDIO_get_ANALOG_CTRL12_AUDIO_REG(void);
/*! \brief Writes the bit group 'TEST_BUS_SEL' of register 'AUDIO_ANALOG_CTRL12'. */
void GH_AUDIO_set_ANALOG_CTRL12_TEST_BUS_SEL(U8 data);
/*! \brief Reads the bit group 'TEST_BUS_SEL' of register 'AUDIO_ANALOG_CTRL12'. */
U8   GH_AUDIO_get_ANALOG_CTRL12_TEST_BUS_SEL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL12(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL12] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL12,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL12(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL12);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL12] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL12,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL12_AUDIO_REG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL12_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12;
    d.bitc.audio_reg = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL12_AUDIO_REG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL12_AUDIO_REG(void)
{
    GH_AUDIO_ANALOG_CTRL12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL12);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL12_AUDIO_REG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL12,value);
    #endif
    return tmp_value.bitc.audio_reg;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL12_TEST_BUS_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL12_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12;
    d.bitc.test_bus_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL12_TEST_BUS_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL12_TEST_BUS_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL12);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL12_TEST_BUS_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL12,value);
    #endif
    return tmp_value.bitc.test_bus_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL13 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL13'. */
U16  GH_AUDIO_get_ANALOG_CTRL13(void);
/*! \brief Writes the bit group 'MIC_TRIM_SEL_CFG' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(U8 data);
/*! \brief Reads the bit group 'MIC_TRIM_SEL_CFG' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(void);
/*! \brief Writes the bit group 'TRIM_STOP_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP_SEL(U8 data);
/*! \brief Reads the bit group 'TRIM_STOP_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP_SEL(void);
/*! \brief Writes the bit group 'RSTZ_TRIM_AU' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_RSTZ_TRIM_AU(U8 data);
/*! \brief Reads the bit group 'RSTZ_TRIM_AU' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_RSTZ_TRIM_AU(void);
/*! \brief Writes the bit group 'TRIM_AU_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_TRIM_AU_SEL(U8 data);
/*! \brief Reads the bit group 'TRIM_AU_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_AU_SEL(void);
/*! \brief Writes the bit group 'TRIM_STOP' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP(U8 data);
/*! \brief Reads the bit group 'TRIM_STOP' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL13] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL13(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL13] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13;
    d.bitc.mic_trim_sel_cfg = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL13_MIC_TRIM_SEL_CFG] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(void)
{
    GH_AUDIO_ANALOG_CTRL13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL13_MIC_TRIM_SEL_CFG] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,value);
    #endif
    return tmp_value.bitc.mic_trim_sel_cfg;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13;
    d.bitc.trim_stop_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,value);
    #endif
    return tmp_value.bitc.trim_stop_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_RSTZ_TRIM_AU(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13;
    d.bitc.rstz_trim_au = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL13_RSTZ_TRIM_AU] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_RSTZ_TRIM_AU(void)
{
    GH_AUDIO_ANALOG_CTRL13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL13_RSTZ_TRIM_AU] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,value);
    #endif
    return tmp_value.bitc.rstz_trim_au;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_TRIM_AU_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13;
    d.bitc.trim_au_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL13_TRIM_AU_SEL] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_AU_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL13_TRIM_AU_SEL] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,value);
    #endif
    return tmp_value.bitc.trim_au_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13;
    d.bitc.trim_stop = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP(void)
{
    GH_AUDIO_ANALOG_CTRL13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL13,value);
    #endif
    return tmp_value.bitc.trim_stop;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL14 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL14'. */
void GH_AUDIO_set_ANALOG_CTRL14(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL14'. */
U16  GH_AUDIO_get_ANALOG_CTRL14(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL14'. */
void GH_AUDIO_set_ANALOG_CTRL14_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL14'. */
U16  GH_AUDIO_get_ANALOG_CTRL14_READ_BACK(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL14(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL14 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL14] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL14,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL14(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL14);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL14] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL14,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL14_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL14_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL14;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL14 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL14_READ_BACK] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL14,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL14_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL14);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL14_READ_BACK] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL14,value);
    #endif
    return tmp_value.bitc.read_back;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL15 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL15'. */
void GH_AUDIO_set_ANALOG_CTRL15(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL15'. */
U16  GH_AUDIO_get_ANALOG_CTRL15(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL15'. */
void GH_AUDIO_set_ANALOG_CTRL15_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL15'. */
U16  GH_AUDIO_get_ANALOG_CTRL15_READ_BACK(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL15(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL15 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL15] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL15,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL15(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL15);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL15] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL15,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL15_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL15_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL15;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL15 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL15_READ_BACK] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL15,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL15_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL15);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL15_READ_BACK] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL15,value);
    #endif
    return tmp_value.bitc.read_back;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL16 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL16'. */
void GH_AUDIO_set_ANALOG_CTRL16(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL16'. */
U16  GH_AUDIO_get_ANALOG_CTRL16(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL16'. */
void GH_AUDIO_set_ANALOG_CTRL16_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL16'. */
U16  GH_AUDIO_get_ANALOG_CTRL16_READ_BACK(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL16(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL16 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL16] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL16,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL16(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL16);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL16] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL16,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL16_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL16_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL16;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL16 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL16_READ_BACK] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL16,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL16_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL16);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL16_READ_BACK] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL16,value);
    #endif
    return tmp_value.bitc.read_back;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL17 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL17'. */
void GH_AUDIO_set_ANALOG_CTRL17(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL17'. */
U16  GH_AUDIO_get_ANALOG_CTRL17(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL17'. */
void GH_AUDIO_set_ANALOG_CTRL17_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL17'. */
U16  GH_AUDIO_get_ANALOG_CTRL17_READ_BACK(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL17(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL17 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL17] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL17,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL17(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL17);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL17] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL17,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL17_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL17_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL17;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL17 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL17_READ_BACK] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL17,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL17_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL17);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL17_READ_BACK] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL17,value);
    #endif
    return tmp_value.bitc.read_back;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL18 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL18'. */
void GH_AUDIO_set_ANALOG_CTRL18(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL18'. */
U16  GH_AUDIO_get_ANALOG_CTRL18(void);
/*! \brief Writes the bit group 'AUDIO_SLEEP_DBG_BUS' of register 'AUDIO_ANALOG_CTRL18'. */
void GH_AUDIO_set_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(U16 data);
/*! \brief Reads the bit group 'AUDIO_SLEEP_DBG_BUS' of register 'AUDIO_ANALOG_CTRL18'. */
U16  GH_AUDIO_get_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL18(U16 data)
{
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL18 = data;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL18] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL18,data,data);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL18(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL18);

    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL18] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL18,value);
    #endif
    return value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(U16 data)
{
    GH_AUDIO_ANALOG_CTRL18_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL18;
    d.bitc.audio_sleep_dbg_bus = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL18 = d.all;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_AUDIO_set_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS] <-- 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL18,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(void)
{
    GH_AUDIO_ANALOG_CTRL18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL18);

    tmp_value.all = value;
    #if GH_AUDIO_ENABLE_DEBUG_PRINT
    GH_AUDIO_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_AUDIO_get_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS] --> 0x%08x\n",
                        REG_AUDIO_ANALOG_CTRL18,value);
    #endif
    return tmp_value.bitc.audio_sleep_dbg_bus;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_AUDIO_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_AUDIO_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

