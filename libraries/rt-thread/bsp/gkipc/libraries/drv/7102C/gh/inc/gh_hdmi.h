/*!
*******************************************************************************
**
** \file      gh_hdmi.h
**
** \brief     Video/Sensor Input.
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
#ifndef _GH_HDMI_H
#define _GH_HDMI_H

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

#define GH_HDMI_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_HDMI_DEBUG_PRINT_FUNCTION printk
#else
#define GH_HDMI_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_HDMI_ENABLE_DEBUG_PRINT
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
#define REG_HDMI_INT_ENABLE                                 FIO_ADDRESS(HDMI,0x60013000) /* read/write */
#define REG_HDMI_INT_STS                                    FIO_ADDRESS(HDMI,0x60013004) /* read */
#define REG_HDMI_OP_MODE                                    FIO_ADDRESS(HDMI,0x60013008) /* read/write */
#define REG_HDMI_CLOCK_GATED                                FIO_ADDRESS(HDMI,0x6001300C) /* read/write */
#define REG_HDMI_HDMISE_SOFT_RESETN                         FIO_ADDRESS(HDMI,0x60013010) /* read/write */
#define REG_HDMI_STS                                        FIO_ADDRESS(HDMI,0x60013104) /* read/write */
#define REG_HDMI_AUNIT_MCLK                                 FIO_ADDRESS(HDMI,0x60013100) /* read/write */
#define REG_HDMI_AUNIT_NCTS_CTRL                            FIO_ADDRESS(HDMI,0x60013104) /* read/write */
#define REG_HDMI_AUNIT_N                                    FIO_ADDRESS(HDMI,0x60013108) /* read/write */
#define REG_HDMI_AUNIT_CTS                                  FIO_ADDRESS(HDMI,0x6001310C) /* read/write */
#define REG_HDMI_AUNIT_SRC                                  FIO_ADDRESS(HDMI,0x60013110) /* read/write */
#define REG_HDMI_AUNIT_CS0                                  FIO_ADDRESS(HDMI,0x60013114) /* read/write */
#define REG_HDMI_AUNIT_CS1                                  FIO_ADDRESS(HDMI,0x60013118) /* read/write */
#define REG_HDMI_AUNIT_CS2                                  FIO_ADDRESS(HDMI,0x6001311C) /* read/write */
#define REG_HDMI_AUNIT_CS3                                  FIO_ADDRESS(HDMI,0x60013120) /* read/write */
#define REG_HDMI_AUNIT_CS4                                  FIO_ADDRESS(HDMI,0x60013124) /* read/write */
#define REG_HDMI_AUNIT_CS5                                  FIO_ADDRESS(HDMI,0x60013128) /* read/write */
#define REG_HDMI_AUNIT_LAYOUT                               FIO_ADDRESS(HDMI,0x6001312C) /* read/write */
#define REG_HDMI_PACKET_TX_CTRL                             FIO_ADDRESS(HDMI,0x60013130) /* read/write */
#define REG_HDMI_PACKET_GENERAL_CTRL                        FIO_ADDRESS(HDMI,0x60013134) /* read/write */
#define REG_HDMI_PACKET0                                    FIO_ADDRESS(HDMI,0x60013138) /* read/write */
#define REG_HDMI_PACKET1                                    FIO_ADDRESS(HDMI,0x6001313C) /* read/write */
#define REG_HDMI_PACKET2                                    FIO_ADDRESS(HDMI,0x60013140) /* read/write */
#define REG_HDMI_PACKET3                                    FIO_ADDRESS(HDMI,0x60013144) /* read/write */
#define REG_HDMI_PACKET4                                    FIO_ADDRESS(HDMI,0x60013148) /* read/write */
#define REG_HDMI_PACKET5                                    FIO_ADDRESS(HDMI,0x6001314C) /* read/write */
#define REG_HDMI_PACKET6                                    FIO_ADDRESS(HDMI,0x60013150) /* read/write */
#define REG_HDMI_PACKET7                                    FIO_ADDRESS(HDMI,0x60013154) /* read/write */
#define REG_HDMI_PACKET8                                    FIO_ADDRESS(HDMI,0x60013158) /* read/write */
#define REG_HDMI_I2S_MODE                                   FIO_ADDRESS(HDMI,0x60013258) /* read/write */
#define REG_HDMI_I2S_RX_CTRL                                FIO_ADDRESS(HDMI,0x6001325C) /* read/write */
#define REG_HDMI_I2S_WLEN                                   FIO_ADDRESS(HDMI,0x60013260) /* read/write */
#define REG_HDMI_I2S_WPOS                                   FIO_ADDRESS(HDMI,0x60013264) /* read/write */
#define REG_HDMI_I2S_SLOT                                   FIO_ADDRESS(HDMI,0x60013268) /* read/write */
#define REG_HDMI_I2S_RX_FIFO_GTH                            FIO_ADDRESS(HDMI,0x6001326C) /* read/write */
#define REG_HDMI_I2S_CLOCK                                  FIO_ADDRESS(HDMI,0x60013270) /* read/write */
#define REG_HDMI_I2S_INIT                                   FIO_ADDRESS(HDMI,0x60013274) /* read/write */
#define REG_HDMI_I2S_RX_DATA                                FIO_ADDRESS(HDMI,0x60013278) /* read/write */
#define REG_HDMI_I2S_FIFO_CNTR                              FIO_ADDRESS(HDMI,0x60013284) /* read/write */
#define REG_HDMI_I2S_GATE_OFF                               FIO_ADDRESS(HDMI,0x60013288) /* read/write */
#define REG_HDMI_PACKET_MISC                                FIO_ADDRESS(HDMI,0x6001328C) /* read/write */
#define REG_HDMI_VUNIT_VBLANK                               FIO_ADDRESS(HDMI,0x60013290) /* read/write */
#define REG_HDMI_VUNIT_HBLANK                               FIO_ADDRESS(HDMI,0x60013294) /* read/write */
#define REG_HDMI_VUNIT_VACTIVE                              FIO_ADDRESS(HDMI,0x60013298) /* read/write */
#define REG_HDMI_VUNIT_HACTIVE                              FIO_ADDRESS(HDMI,0x6001329C) /* read/write */
#define REG_HDMI_VUNIT_CTRL                                 FIO_ADDRESS(HDMI,0x600132A0) /* read/write */
#define REG_HDMI_VUNIT_VSYNC_DETECT                         FIO_ADDRESS(HDMI,0x600132A4) /* read/write */
#define REG_HDMI_HDMISE_TM                                  FIO_ADDRESS(HDMI,0x600132A8) /* read/write */
#define REG_HDMI_P2P_AFIFO_LEVEL                            FIO_ADDRESS(HDMI,0x600132AC) /* read/write */
#define REG_HDMI_P2P_AFIFO_CTRL                             FIO_ADDRESS(HDMI,0x600132B0) /* read/write */
#define REG_HDMI_HDMISE_DBG                                 FIO_ADDRESS(HDMI,0x600132B4) /* read/write */
#define REG_HDMI_HDMI_PHY_CTRL                              FIO_ADDRESS(HDMI,0x60013600) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* HDMI_INT_ENABLE */
    U32 all;
    struct {
        U32 vsync_active_detect_en      : 1;
        U32 hot_plug_detect_en          : 1;
        U32 hot_plug_loss_en            : 1;
        U32 cec_rx_interrupt_en         : 1;
        U32 cec_tx_interrupt_fail_en    : 1;
        U32 cec_tx_interrupt_ok_en      : 1;
        U32                             : 7;
        U32 phy_rx_sense_en             : 1;
        U32 i2s_rx_fifo_empty_en        : 1;
        U32 i2s_rx_fifo_full_en         : 1;
        U32 i2s_rx_fifo_over_en         : 1;
        U32 i2s_rx_gth_valid_en         : 1;
        U32 i2s_rx_idle_en              : 1;
        U32 cts_change_en               : 1;
        U32 p2p_wfull_en                : 1;
        U32 p2p_rempty_en               : 1;
        U32 p2p_below_lb_en             : 1;
        U32 p2p_exceed_ub_en            : 1;
        U32 hdmise_idle_en              : 1;
        U32 phy_rx_sense_remove_en      : 1;
        U32                             : 6;
    } bitc;
} GH_HDMI_INT_ENABLE_S;

typedef union { /* HDMI_INT_STS */
    U32 all;
    struct {
        U32 vsync_active_detect         : 1;
        U32 hot_plug_detect             : 1;
        U32 hot_plug_loss               : 1;
        U32 cec_rx_interrupt            : 1;
        U32 cec_tx_interrupt_fail       : 1;
        U32 cec_tx_interrupt_ok         : 1;
        U32                             : 7;
        U32 phy_rx_sense                : 1;
        U32 i2s_rx_fifo_empty           : 1;
        U32 i2s_rx_fifo_full            : 1;
        U32 i2s_rx_fifo_over            : 1;
        U32 i2s_rx_gth_valid            : 1;
        U32 i2s_rx_idle                 : 1;
        U32 cts_change                  : 1;
        U32 p2p_wfull                   : 1;
        U32 p2p_rempty                  : 1;
        U32 p2p_below_lb                : 1;
        U32 p2p_exceed_ub               : 1;
        U32 hdmise_idle                 : 1;
        U32 phy_rx_sense_remove         : 1;
        U32                             : 6;
    } bitc;
} GH_HDMI_INT_STS_S;

typedef union { /* HDMI_OP_MODE */
    U32 all;
    struct {
        U32 op_mode                     : 1;
        U32 op_en                       : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_OP_MODE_S;

typedef union { /* HDMI_CLOCK_GATED */
    U32 all;
    struct {
        U32 hdmise_clock_en             : 1;
        U32                             : 1;
        U32 cec_clock_en                : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_CLOCK_GATED_S;

typedef union { /* HDMI_HDMISE_SOFT_RESETN */
    U32 all;
    struct {
        U32 hdmise_soft_resetn          : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_HDMISE_SOFT_RESETN_S;

typedef union { /* HDMI_AUNIT_MCLK */
    U32 all;
    struct {
        U32 mclk_conf                   : 3;
        U32                             : 29;
    } bitc;
} GH_HDMI_AUNIT_MCLK_S;

typedef union { /* HDMI_AUNIT_NCTS_CTRL */
    U32 all;
    struct {
        U32 cts_sel                     : 1;
        U32 ncts_en                     : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_AUNIT_NCTS_CTRL_S;

typedef union { /* HDMI_AUNIT_N */
    U32 all;
    struct {
        U32 aunit_n                     : 20;
        U32                             : 12;
    } bitc;
} GH_HDMI_AUNIT_N_S;

typedef union { /* HDMI_AUNIT_CTS */
    U32 all;
    struct {
        U32 aunit_cts                   : 20;
        U32                             : 12;
    } bitc;
} GH_HDMI_AUNIT_CTS_S;

typedef union { /* HDMI_AUNIT_SRC */
    U32 all;
    struct {
        U32 i2s0_en                     : 1;
        U32 i2s1_en                     : 1;
        U32 i2s2_en                     : 1;
        U32 flat_line0                  : 1;
        U32 flat_line1                  : 1;
        U32 flat_line2                  : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_AUNIT_SRC_S;

typedef union { /* HDMI_AUNIT_LAYOUT */
    U32 all;
    struct {
        U32 layout                      : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_AUNIT_LAYOUT_S;

typedef union { /* HDMI_PACKET_TX_CTRL */
    U32 all;
    struct {
        U32 gen_en                      : 1;
        U32 gen_rpt                     : 1;
        U32 acp_en                      : 1;
        U32 acp_rpt                     : 1;
        U32 isrc_en                     : 1;
        U32 isrc_rpt                    : 1;
        U32 avi_en                      : 1;
        U32 avi_rpt                     : 1;
        U32 spd_en                      : 1;
        U32 spd_rpt                     : 1;
        U32 aud_en                      : 1;
        U32 aud_rpt                     : 1;
        U32 mpeg_en                     : 1;
        U32 mpeg_rpt                    : 1;
        U32 gamut_en                    : 1;
        U32 gamut_rpt                   : 1;
        U32                             : 15;
        U32 buf_switch_en               : 1;
    } bitc;
} GH_HDMI_PACKET_TX_CTRL_S;

typedef union { /* HDMI_PACKET_GENERAL_CTRL */
    U32 all;
    struct {
        U32 set_avmute                  : 1;
        U32                             : 3;
        U32 clr_avmute                  : 1;
        U32                             : 3;
        U32 cd                          : 4;
        U32 pp                          : 4;
        U32 def_phase                   : 1;
        U32                             : 15;
    } bitc;
} GH_HDMI_PACKET_GENERAL_CTRL_S;

typedef union { /* HDMI_PACKET0 */
    U32 all;
    struct {
        U32 acp_hb0                     : 8;
        U32 acp_hb1                     : 8;
        U32 acp_hb2                     : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET0_S;

typedef union { /* HDMI_PACKET1 */
    U32 all;
    struct {
        U32 acp_pb0                     : 8;
        U32 acp_pb1                     : 8;
        U32 acp_pb2                     : 8;
        U32 acp_pb3                     : 8;
    } bitc;
} GH_HDMI_PACKET1_S;

typedef union { /* HDMI_PACKET2 */
    U32 all;
    struct {
        U32 acp_pb4                     : 8;
        U32 acp_pb5                     : 8;
        U32 acp_pb6                     : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET2_S;

typedef union { /* HDMI_PACKET3 */
    U32 all;
    struct {
        U32 acp_pb7                     : 8;
        U32 acp_pb8                     : 8;
        U32 acp_pb9                     : 8;
        U32 acp_pb10                    : 8;
    } bitc;
} GH_HDMI_PACKET3_S;

typedef union { /* HDMI_PACKET4 */
    U32 all;
    struct {
        U32 acp_pb11                    : 8;
        U32 acp_pb12                    : 8;
        U32 acp_pb13                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET4_S;

typedef union { /* HDMI_PACKET5 */
    U32 all;
    struct {
        U32 acp_pb14                    : 8;
        U32 acp_pb15                    : 8;
        U32 acp_pb16                    : 8;
        U32 acp_pb17                    : 8;
    } bitc;
} GH_HDMI_PACKET5_S;

typedef union { /* HDMI_PACKET6 */
    U32 all;
    struct {
        U32 acp_pb18                    : 8;
        U32 acp_pb19                    : 8;
        U32 acp_pb20                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET6_S;

typedef union { /* HDMI_PACKET7 */
    U32 all;
    struct {
        U32 acp_pb21                    : 8;
        U32 acp_pb22                    : 8;
        U32 acp_pb23                    : 8;
        U32 acp_pb24                    : 8;
    } bitc;
} GH_HDMI_PACKET7_S;

typedef union { /* HDMI_PACKET8 */
    U32 all;
    struct {
        U32 acp_pb25                    : 8;
        U32 acp_pb26                    : 8;
        U32 acp_pb27                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET8_S;

typedef union { /* HDMI_I2S_MODE */
    U32 all;
    struct {
        U32 dai_mode                    : 3;
        U32                             : 29;
    } bitc;
} GH_HDMI_I2S_MODE_S;

typedef union { /* HDMI_I2S_RX_CTRL */
    U32 all;
    struct {
        U32 rx_ws_inv                   : 1;
        U32 rx_ws_mst                   : 1;
        U32 rx_ord                      : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_I2S_RX_CTRL_S;

typedef union { /* HDMI_I2S_WLEN */
    U32 all;
    struct {
        U32 dai_wlen                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_WLEN_S;

typedef union { /* HDMI_I2S_WPOS */
    U32 all;
    struct {
        U32 dai_wpos                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_WPOS_S;

typedef union { /* HDMI_I2S_SLOT */
    U32 all;
    struct {
        U32 dai_slot                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_SLOT_S;

typedef union { /* HDMI_I2S_RX_FIFO_GTH */
    U32 all;
    struct {
        U32 rx_fifo_gth                 : 8;
        U32                             : 24;
    } bitc;
} GH_HDMI_I2S_RX_FIFO_GTH_S;

typedef union { /* HDMI_I2S_CLOCK */
    U32 all;
    struct {
        U32                             : 5;
        U32 rx_scp                      : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_I2S_CLOCK_S;

typedef union { /* HDMI_I2S_INIT */
    U32 all;
    struct {
        U32 dai_reset                   : 1;
        U32 rx_enable                   : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_I2S_INIT_S;

typedef union { /* HDMI_I2S_RX_DATA */
    U32 all;
    struct {
        U32 rx_fifo_dout                : 24;
        U32                             : 8;
    } bitc;
} GH_HDMI_I2S_RX_DATA_S;

typedef union { /* HDMI_I2S_FIFO_CNTR */
    U32 all;
    struct {
        U32 rx_fifo_cntr                : 8;
        U32                             : 24;
    } bitc;
} GH_HDMI_I2S_FIFO_CNTR_S;

typedef union { /* HDMI_I2S_GATE_OFF */
    U32 all;
    struct {
        U32 gate_off_en                 : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_I2S_GATE_OFF_S;

typedef union { /* HDMI_PACKET_MISC */
    U32 all;
    struct {
        U32 left_valid_bit              : 1;
        U32 right_valid_bit             : 1;
        U32 spd_send_ctrl               : 1;
        U32 cts_sw_mode                 : 1;
        U32 ncts_priority               : 1;
        U32 i2s_rx_mode                 : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_PACKET_MISC_S;

typedef union { /* HDMI_VUNIT_VBLANK */
    U32 all;
    struct {
        U32 vblank_right_offset         : 6;
        U32 vblank_pulse_width          : 6;
        U32 vblank_left_offset          : 6;
        U32                             : 14;
    } bitc;
} GH_HDMI_VUNIT_VBLANK_S;

typedef union { /* HDMI_VUNIT_HBLANK */
    U32 all;
    struct {
        U32 hblank_right_offset         : 10;
        U32 hblank_pulse_width          : 10;
        U32 hblank_left_offset          : 10;
        U32                             : 2;
    } bitc;
} GH_HDMI_VUNIT_HBLANK_S;

typedef union { /* HDMI_VUNIT_VACTIVE */
    U32 all;
    struct {
        U32 vunit_vactive               : 11;
        U32                             : 21;
    } bitc;
} GH_HDMI_VUNIT_VACTIVE_S;

typedef union { /* HDMI_VUNIT_HACTIVE */
    U32 all;
    struct {
        U32 vunit_hactive               : 12;
        U32                             : 20;
    } bitc;
} GH_HDMI_VUNIT_HACTIVE_S;

typedef union { /* HDMI_VUNIT_CTRL */
    U32 all;
    struct {
        U32 vsync_pol                   : 1;
        U32 hsync_pol                   : 1;
        U32 video_mode                  : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_VUNIT_CTRL_S;

typedef union { /* HDMI_VUNIT_VSYNC_DETECT */
    U32 all;
    struct {
        U32 vsync_detect_en             : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_VUNIT_VSYNC_DETECT_S;

typedef union { /* HDMI_HDMISE_TM */
    U32 all;
    struct {
        U32 i2s_dout_mode               : 1;
        U32 vdata_src_mode              : 1;
        U32 video_pattern_mode          : 1;
        U32 adata_src_mode              : 1;
        U32                             : 4;
        U32 bg_b                        : 8;
        U32 bg_g                        : 8;
        U32 bg_r                        : 8;
    } bitc;
} GH_HDMI_HDMISE_TM_S;

typedef union { /* HDMI_P2P_AFIFO_LEVEL */
    U32 all;
    struct {
        U32 p2p_afifo_level             : 5;
        U32 p2p_afifo_min_level         : 5;
        U32 p2p_afifo_max_level         : 5;
        U32 p2p_afifo_lb                : 4;
        U32 p2p_afifo_ub                : 4;
        U32                             : 9;
    } bitc;
} GH_HDMI_P2P_AFIFO_LEVEL_S;

typedef union { /* HDMI_P2P_AFIFO_CTRL */
    U32 all;
    struct {
        U32 p2p_afifo_en                : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_P2P_AFIFO_CTRL_S;

typedef union { /* HDMI_HDMISE_DBG */
    U32 all;
    struct {
        U32 dbg_p2p_afifo_bypass        : 1;
        U32 dbg_vdata_src_mode          : 1;
        U32                             : 2;
        U32 dbg_ch_b_rev                : 1;
        U32 dbg_ch_g_rev                : 1;
        U32 dbg_ch_r_rev                : 1;
        U32                             : 1;
        U32 dbg_ch_swp                  : 3;
        U32                             : 21;
    } bitc;
} GH_HDMI_HDMISE_DBG_S;

typedef union { /* HDMI_HDMI_PHY_CTRL */
    U32 all;
    struct {
        U32 rstnd_hdmi                  : 1;
        U32 pib                         : 2;
        U32 pes                         : 2;
        U32 pdb_hdmi                    : 1;
        U32 pd_bg                       : 1;
        U32                             : 25;
    } bitc;
} GH_HDMI_HDMI_PHY_CTRL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register HDMI_INT_ENABLE (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE(U32 data);
/*! \brief Reads the register 'HDMI_INT_ENABLE'. */
U32  GH_HDMI_get_INT_ENABLE(void);
/*! \brief Writes the bit group 'VSYNC_ACTIVE_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(U8 data);
/*! \brief Reads the bit group 'VSYNC_ACTIVE_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(void);
/*! \brief Writes the bit group 'HOT_PLUG_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_HOT_PLUG_DETECT_EN(U8 data);
/*! \brief Reads the bit group 'HOT_PLUG_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_DETECT_EN(void);
/*! \brief Writes the bit group 'HOT_PLUG_LOSS_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_HOT_PLUG_LOSS_EN(U8 data);
/*! \brief Reads the bit group 'HOT_PLUG_LOSS_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_LOSS_EN(void);
/*! \brief Writes the bit group 'CEC_RX_INTERRUPT_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CEC_RX_INTERRUPT_EN(U8 data);
/*! \brief Reads the bit group 'CEC_RX_INTERRUPT_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CEC_RX_INTERRUPT_EN(void);
/*! \brief Writes the bit group 'CEC_TX_INTERRUPT_FAIL_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(U8 data);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_FAIL_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(void);
/*! \brief Writes the bit group 'CEC_TX_INTERRUPT_OK_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(U8 data);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_OK_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(void);
/*! \brief Writes the bit group 'PHY_RX_SENSE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_EN(U8 data);
/*! \brief Reads the bit group 'PHY_RX_SENSE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_EN(void);
/*! \brief Writes the bit group 'I2S_RX_FIFO_EMPTY_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_FIFO_EMPTY_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(void);
/*! \brief Writes the bit group 'I2S_RX_FIFO_FULL_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_FULL_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_FIFO_FULL_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_FULL_EN(void);
/*! \brief Writes the bit group 'I2S_RX_FIFO_OVER_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_OVER_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_FIFO_OVER_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_OVER_EN(void);
/*! \brief Writes the bit group 'I2S_RX_GTH_VALID_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_GTH_VALID_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_GTH_VALID_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_GTH_VALID_EN(void);
/*! \brief Writes the bit group 'I2S_RX_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_IDLE_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_IDLE_EN(void);
/*! \brief Writes the bit group 'CTS_CHANGE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CTS_CHANGE_EN(U8 data);
/*! \brief Reads the bit group 'CTS_CHANGE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CTS_CHANGE_EN(void);
/*! \brief Writes the bit group 'P2P_WFULL_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_WFULL_EN(U8 data);
/*! \brief Reads the bit group 'P2P_WFULL_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_WFULL_EN(void);
/*! \brief Writes the bit group 'P2P_REMPTY_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_REMPTY_EN(U8 data);
/*! \brief Reads the bit group 'P2P_REMPTY_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_REMPTY_EN(void);
/*! \brief Writes the bit group 'P2P_BELOW_LB_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_BELOW_LB_EN(U8 data);
/*! \brief Reads the bit group 'P2P_BELOW_LB_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_BELOW_LB_EN(void);
/*! \brief Writes the bit group 'P2P_EXCEED_UB_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_EXCEED_UB_EN(U8 data);
/*! \brief Reads the bit group 'P2P_EXCEED_UB_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_EXCEED_UB_EN(void);
/*! \brief Writes the bit group 'HDMISE_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_HDMISE_IDLE_EN(U8 data);
/*! \brief Reads the bit group 'HDMISE_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_HDMISE_IDLE_EN(void);
/*! \brief Writes the bit group 'PHY_RX_SENSE_REMOVE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(U8 data);
/*! \brief Reads the bit group 'PHY_RX_SENSE_REMOVE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_INT_ENABLE(U32 data)
{
    *(volatile U32 *)REG_HDMI_INT_ENABLE = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_INT_ENABLE(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.vsync_active_detect_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.vsync_active_detect_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_HOT_PLUG_DETECT_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.hot_plug_detect_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_HOT_PLUG_DETECT_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_DETECT_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_HOT_PLUG_DETECT_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.hot_plug_detect_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_HOT_PLUG_LOSS_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.hot_plug_loss_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_HOT_PLUG_LOSS_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_LOSS_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_HOT_PLUG_LOSS_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.hot_plug_loss_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CEC_RX_INTERRUPT_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.cec_rx_interrupt_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_CEC_RX_INTERRUPT_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CEC_RX_INTERRUPT_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_CEC_RX_INTERRUPT_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.cec_rx_interrupt_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.cec_tx_interrupt_fail_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.cec_tx_interrupt_fail_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.cec_tx_interrupt_ok_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.cec_tx_interrupt_ok_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.phy_rx_sense_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.phy_rx_sense_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.i2s_rx_fifo_empty_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.i2s_rx_fifo_empty_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_FULL_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.i2s_rx_fifo_full_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_FULL_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_FULL_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_FULL_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.i2s_rx_fifo_full_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_OVER_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.i2s_rx_fifo_over_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_OVER_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_OVER_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_OVER_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.i2s_rx_fifo_over_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_GTH_VALID_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.i2s_rx_gth_valid_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_I2S_RX_GTH_VALID_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_GTH_VALID_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_I2S_RX_GTH_VALID_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.i2s_rx_gth_valid_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_IDLE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.i2s_rx_idle_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_I2S_RX_IDLE_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_IDLE_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_I2S_RX_IDLE_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.i2s_rx_idle_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CTS_CHANGE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.cts_change_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_CTS_CHANGE_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CTS_CHANGE_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_CTS_CHANGE_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.cts_change_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_WFULL_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.p2p_wfull_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_P2P_WFULL_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_WFULL_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_P2P_WFULL_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.p2p_wfull_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_REMPTY_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.p2p_rempty_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_P2P_REMPTY_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_REMPTY_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_P2P_REMPTY_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.p2p_rempty_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_BELOW_LB_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.p2p_below_lb_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_P2P_BELOW_LB_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_BELOW_LB_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_P2P_BELOW_LB_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.p2p_below_lb_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_EXCEED_UB_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.p2p_exceed_ub_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_P2P_EXCEED_UB_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_EXCEED_UB_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_P2P_EXCEED_UB_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.p2p_exceed_ub_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_HDMISE_IDLE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.hdmise_idle_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_HDMISE_IDLE_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_HDMISE_IDLE_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_HDMISE_IDLE_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.hdmise_idle_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE;
    d.bitc.phy_rx_sense_remove_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN] <-- 0x%08x\n",
                        REG_HDMI_INT_ENABLE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(void)
{
    GH_HDMI_INT_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN] --> 0x%08x\n",
                        REG_HDMI_INT_ENABLE,value);
    #endif
    return tmp_value.bitc.phy_rx_sense_remove_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_INT_STS (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'HDMI_INT_STS'. */
U32  GH_HDMI_get_INT_STS(void);
/*! \brief Reads the bit group 'VSYNC_ACTIVE_DETECT' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_VSYNC_ACTIVE_DETECT(void);
/*! \brief Reads the bit group 'HOT_PLUG_DETECT' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_HOT_PLUG_DETECT(void);
/*! \brief Reads the bit group 'HOT_PLUG_LOSS' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_HOT_PLUG_LOSS(void);
/*! \brief Reads the bit group 'CEC_RX_INTERRUPT' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CEC_RX_INTERRUPT(void);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_FAIL' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_FAIL(void);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_OK' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_OK(void);
/*! \brief Reads the bit group 'PHY_RX_SENSE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE(void);
/*! \brief Reads the bit group 'I2S_RX_FIFO_EMPTY' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_EMPTY(void);
/*! \brief Reads the bit group 'I2S_RX_FIFO_FULL' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_FULL(void);
/*! \brief Reads the bit group 'I2S_RX_FIFO_OVER' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_OVER(void);
/*! \brief Reads the bit group 'I2S_RX_GTH_VALID' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_GTH_VALID(void);
/*! \brief Reads the bit group 'I2S_RX_IDLE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_IDLE(void);
/*! \brief Reads the bit group 'CTS_CHANGE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CTS_CHANGE(void);
/*! \brief Reads the bit group 'P2P_WFULL' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_WFULL(void);
/*! \brief Reads the bit group 'P2P_REMPTY' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_REMPTY(void);
/*! \brief Reads the bit group 'P2P_BELOW_LB' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_BELOW_LB(void);
/*! \brief Reads the bit group 'P2P_EXCEED_UB' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_EXCEED_UB(void);
/*! \brief Reads the bit group 'HDMISE_IDLE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_HDMISE_IDLE(void);
/*! \brief Reads the bit group 'PHY_RX_SENSE_REMOVE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE_REMOVE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_HDMI_get_INT_STS(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_VSYNC_ACTIVE_DETECT(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_VSYNC_ACTIVE_DETECT] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.vsync_active_detect;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_HOT_PLUG_DETECT(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_HOT_PLUG_DETECT] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.hot_plug_detect;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_HOT_PLUG_LOSS(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_HOT_PLUG_LOSS] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.hot_plug_loss;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CEC_RX_INTERRUPT(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_CEC_RX_INTERRUPT] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.cec_rx_interrupt;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_FAIL(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_FAIL] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.cec_tx_interrupt_fail;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_OK(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_OK] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.cec_tx_interrupt_ok;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_PHY_RX_SENSE] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.phy_rx_sense;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_EMPTY(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_I2S_RX_FIFO_EMPTY] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.i2s_rx_fifo_empty;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_FULL(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_I2S_RX_FIFO_FULL] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.i2s_rx_fifo_full;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_OVER(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_I2S_RX_FIFO_OVER] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.i2s_rx_fifo_over;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_GTH_VALID(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_I2S_RX_GTH_VALID] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.i2s_rx_gth_valid;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_IDLE(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_I2S_RX_IDLE] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.i2s_rx_idle;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CTS_CHANGE(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_CTS_CHANGE] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.cts_change;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_WFULL(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_P2P_WFULL] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.p2p_wfull;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_REMPTY(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_P2P_REMPTY] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.p2p_rempty;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_BELOW_LB(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_P2P_BELOW_LB] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.p2p_below_lb;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_EXCEED_UB(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_P2P_EXCEED_UB] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.p2p_exceed_ub;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_HDMISE_IDLE(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_HDMISE_IDLE] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.hdmise_idle;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE_REMOVE(void)
{
    GH_HDMI_INT_STS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_INT_STS_PHY_RX_SENSE_REMOVE] --> 0x%08x\n",
                        REG_HDMI_INT_STS,value);
    #endif
    return tmp_value.bitc.phy_rx_sense_remove;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_OP_MODE (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_OP_MODE'. */
void GH_HDMI_set_OP_MODE(U32 data);
/*! \brief Reads the register 'HDMI_OP_MODE'. */
U32  GH_HDMI_get_OP_MODE(void);
/*! \brief Writes the bit group 'OP_MODE' of register 'HDMI_OP_MODE'. */
void GH_HDMI_set_OP_MODE_OP_MODE(U8 data);
/*! \brief Reads the bit group 'OP_MODE' of register 'HDMI_OP_MODE'. */
U8   GH_HDMI_get_OP_MODE_OP_MODE(void);
/*! \brief Writes the bit group 'OP_EN' of register 'HDMI_OP_MODE'. */
void GH_HDMI_set_OP_MODE_OP_EN(U8 data);
/*! \brief Reads the bit group 'OP_EN' of register 'HDMI_OP_MODE'. */
U8   GH_HDMI_get_OP_MODE_OP_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_OP_MODE(U32 data)
{
    *(volatile U32 *)REG_HDMI_OP_MODE = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_OP_MODE] <-- 0x%08x\n",
                        REG_HDMI_OP_MODE,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_OP_MODE(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_OP_MODE);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_OP_MODE] --> 0x%08x\n",
                        REG_HDMI_OP_MODE,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_OP_MODE_OP_MODE(U8 data)
{
    GH_HDMI_OP_MODE_S d;
    d.all = *(volatile U32 *)REG_HDMI_OP_MODE;
    d.bitc.op_mode = data;
    *(volatile U32 *)REG_HDMI_OP_MODE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_OP_MODE_OP_MODE] <-- 0x%08x\n",
                        REG_HDMI_OP_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_OP_MODE_OP_MODE(void)
{
    GH_HDMI_OP_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_OP_MODE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_OP_MODE_OP_MODE] --> 0x%08x\n",
                        REG_HDMI_OP_MODE,value);
    #endif
    return tmp_value.bitc.op_mode;
}
GH_INLINE void GH_HDMI_set_OP_MODE_OP_EN(U8 data)
{
    GH_HDMI_OP_MODE_S d;
    d.all = *(volatile U32 *)REG_HDMI_OP_MODE;
    d.bitc.op_en = data;
    *(volatile U32 *)REG_HDMI_OP_MODE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_OP_MODE_OP_EN] <-- 0x%08x\n",
                        REG_HDMI_OP_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_OP_MODE_OP_EN(void)
{
    GH_HDMI_OP_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_OP_MODE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_OP_MODE_OP_EN] --> 0x%08x\n",
                        REG_HDMI_OP_MODE,value);
    #endif
    return tmp_value.bitc.op_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_CLOCK_GATED (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_CLOCK_GATED'. */
void GH_HDMI_set_CLOCK_GATED(U32 data);
/*! \brief Reads the register 'HDMI_CLOCK_GATED'. */
U32  GH_HDMI_get_CLOCK_GATED(void);
/*! \brief Writes the bit group 'HDMISE_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
void GH_HDMI_set_CLOCK_GATED_HDMISE_CLOCK_EN(U8 data);
/*! \brief Reads the bit group 'HDMISE_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
U8   GH_HDMI_get_CLOCK_GATED_HDMISE_CLOCK_EN(void);
/*! \brief Writes the bit group 'CEC_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
void GH_HDMI_set_CLOCK_GATED_CEC_CLOCK_EN(U8 data);
/*! \brief Reads the bit group 'CEC_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
U8   GH_HDMI_get_CLOCK_GATED_CEC_CLOCK_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_CLOCK_GATED(U32 data)
{
    *(volatile U32 *)REG_HDMI_CLOCK_GATED = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_CLOCK_GATED] <-- 0x%08x\n",
                        REG_HDMI_CLOCK_GATED,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_CLOCK_GATED(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_CLOCK_GATED);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_CLOCK_GATED] --> 0x%08x\n",
                        REG_HDMI_CLOCK_GATED,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_CLOCK_GATED_HDMISE_CLOCK_EN(U8 data)
{
    GH_HDMI_CLOCK_GATED_S d;
    d.all = *(volatile U32 *)REG_HDMI_CLOCK_GATED;
    d.bitc.hdmise_clock_en = data;
    *(volatile U32 *)REG_HDMI_CLOCK_GATED = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_CLOCK_GATED_HDMISE_CLOCK_EN] <-- 0x%08x\n",
                        REG_HDMI_CLOCK_GATED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_CLOCK_GATED_HDMISE_CLOCK_EN(void)
{
    GH_HDMI_CLOCK_GATED_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_CLOCK_GATED);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_CLOCK_GATED_HDMISE_CLOCK_EN] --> 0x%08x\n",
                        REG_HDMI_CLOCK_GATED,value);
    #endif
    return tmp_value.bitc.hdmise_clock_en;
}
GH_INLINE void GH_HDMI_set_CLOCK_GATED_CEC_CLOCK_EN(U8 data)
{
    GH_HDMI_CLOCK_GATED_S d;
    d.all = *(volatile U32 *)REG_HDMI_CLOCK_GATED;
    d.bitc.cec_clock_en = data;
    *(volatile U32 *)REG_HDMI_CLOCK_GATED = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_CLOCK_GATED_CEC_CLOCK_EN] <-- 0x%08x\n",
                        REG_HDMI_CLOCK_GATED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_CLOCK_GATED_CEC_CLOCK_EN(void)
{
    GH_HDMI_CLOCK_GATED_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_CLOCK_GATED);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_CLOCK_GATED_CEC_CLOCK_EN] --> 0x%08x\n",
                        REG_HDMI_CLOCK_GATED,value);
    #endif
    return tmp_value.bitc.cec_clock_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_SOFT_RESETN (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_HDMISE_SOFT_RESETN'. */
void GH_HDMI_set_HDMISE_SOFT_RESETN(U32 data);
/*! \brief Reads the register 'HDMI_HDMISE_SOFT_RESETN'. */
U32  GH_HDMI_get_HDMISE_SOFT_RESETN(void);
/*! \brief Writes the bit group 'HDMISE_SOFT_RESETN' of register 'HDMI_HDMISE_SOFT_RESETN'. */
void GH_HDMI_set_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(U8 data);
/*! \brief Reads the bit group 'HDMISE_SOFT_RESETN' of register 'HDMI_HDMISE_SOFT_RESETN'. */
U8   GH_HDMI_get_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_HDMISE_SOFT_RESETN(U32 data)
{
    *(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_SOFT_RESETN] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_SOFT_RESETN,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_HDMISE_SOFT_RESETN(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_SOFT_RESETN] --> 0x%08x\n",
                        REG_HDMI_HDMISE_SOFT_RESETN,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(U8 data)
{
    GH_HDMI_HDMISE_SOFT_RESETN_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN;
    d.bitc.hdmise_soft_resetn = data;
    *(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_SOFT_RESETN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(void)
{
    GH_HDMI_HDMISE_SOFT_RESETN_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN] --> 0x%08x\n",
                        REG_HDMI_HDMISE_SOFT_RESETN,value);
    #endif
    return tmp_value.bitc.hdmise_soft_resetn;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_STS (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_STS'. */
void GH_HDMI_set_STS(U32 data);
/*! \brief Reads the register 'HDMI_STS'. */
U32  GH_HDMI_get_STS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_STS(U32 data)
{
    *(volatile U32 *)REG_HDMI_STS = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_STS] <-- 0x%08x\n",
                        REG_HDMI_STS,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_STS(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_STS);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_STS] --> 0x%08x\n",
                        REG_HDMI_STS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_MCLK (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_MCLK'. */
void GH_HDMI_set_AUNIT_MCLK(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_MCLK'. */
U32  GH_HDMI_get_AUNIT_MCLK(void);
/*! \brief Writes the bit group 'MCLK_CONF' of register 'HDMI_AUNIT_MCLK'. */
void GH_HDMI_set_AUNIT_MCLK_MCLK_CONF(U8 data);
/*! \brief Reads the bit group 'MCLK_CONF' of register 'HDMI_AUNIT_MCLK'. */
U8   GH_HDMI_get_AUNIT_MCLK_MCLK_CONF(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_MCLK(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_MCLK = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_MCLK] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_MCLK,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_MCLK(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_MCLK);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_MCLK] --> 0x%08x\n",
                        REG_HDMI_AUNIT_MCLK,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_AUNIT_MCLK_MCLK_CONF(U8 data)
{
    GH_HDMI_AUNIT_MCLK_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_MCLK;
    d.bitc.mclk_conf = data;
    *(volatile U32 *)REG_HDMI_AUNIT_MCLK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_MCLK_MCLK_CONF] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_MCLK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_MCLK_MCLK_CONF(void)
{
    GH_HDMI_AUNIT_MCLK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_MCLK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_MCLK_MCLK_CONF] --> 0x%08x\n",
                        REG_HDMI_AUNIT_MCLK,value);
    #endif
    return tmp_value.bitc.mclk_conf;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_NCTS_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_NCTS_CTRL'. */
void GH_HDMI_set_AUNIT_NCTS_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_NCTS_CTRL'. */
U32  GH_HDMI_get_AUNIT_NCTS_CTRL(void);
/*! \brief Writes the bit group 'CTS_SEL' of register 'HDMI_AUNIT_NCTS_CTRL'. */
void GH_HDMI_set_AUNIT_NCTS_CTRL_CTS_SEL(U8 data);
/*! \brief Reads the bit group 'CTS_SEL' of register 'HDMI_AUNIT_NCTS_CTRL'. */
U8   GH_HDMI_get_AUNIT_NCTS_CTRL_CTS_SEL(void);
/*! \brief Writes the bit group 'NCTS_EN' of register 'HDMI_AUNIT_NCTS_CTRL'. */
void GH_HDMI_set_AUNIT_NCTS_CTRL_NCTS_EN(U8 data);
/*! \brief Reads the bit group 'NCTS_EN' of register 'HDMI_AUNIT_NCTS_CTRL'. */
U8   GH_HDMI_get_AUNIT_NCTS_CTRL_NCTS_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_NCTS_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_NCTS_CTRL] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_NCTS_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_NCTS_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_NCTS_CTRL] --> 0x%08x\n",
                        REG_HDMI_AUNIT_NCTS_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_AUNIT_NCTS_CTRL_CTS_SEL(U8 data)
{
    GH_HDMI_AUNIT_NCTS_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL;
    d.bitc.cts_sel = data;
    *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_NCTS_CTRL_CTS_SEL] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_NCTS_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_NCTS_CTRL_CTS_SEL(void)
{
    GH_HDMI_AUNIT_NCTS_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_NCTS_CTRL_CTS_SEL] --> 0x%08x\n",
                        REG_HDMI_AUNIT_NCTS_CTRL,value);
    #endif
    return tmp_value.bitc.cts_sel;
}
GH_INLINE void GH_HDMI_set_AUNIT_NCTS_CTRL_NCTS_EN(U8 data)
{
    GH_HDMI_AUNIT_NCTS_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL;
    d.bitc.ncts_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_NCTS_CTRL_NCTS_EN] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_NCTS_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_NCTS_CTRL_NCTS_EN(void)
{
    GH_HDMI_AUNIT_NCTS_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_NCTS_CTRL_NCTS_EN] --> 0x%08x\n",
                        REG_HDMI_AUNIT_NCTS_CTRL,value);
    #endif
    return tmp_value.bitc.ncts_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_N (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_N'. */
void GH_HDMI_set_AUNIT_N(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_N'. */
U32  GH_HDMI_get_AUNIT_N(void);
/*! \brief Writes the bit group 'AUNIT_N' of register 'HDMI_AUNIT_N'. */
void GH_HDMI_set_AUNIT_N_AUNIT_N(U32 data);
/*! \brief Reads the bit group 'AUNIT_N' of register 'HDMI_AUNIT_N'. */
U32  GH_HDMI_get_AUNIT_N_AUNIT_N(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_N(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_N = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_N] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_N,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_N(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_N);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_N] --> 0x%08x\n",
                        REG_HDMI_AUNIT_N,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_AUNIT_N_AUNIT_N(U32 data)
{
    GH_HDMI_AUNIT_N_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_N;
    d.bitc.aunit_n = data;
    *(volatile U32 *)REG_HDMI_AUNIT_N = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_N_AUNIT_N] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_N,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_N_AUNIT_N(void)
{
    GH_HDMI_AUNIT_N_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_N);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_N_AUNIT_N] --> 0x%08x\n",
                        REG_HDMI_AUNIT_N,value);
    #endif
    return tmp_value.bitc.aunit_n;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CTS (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CTS'. */
void GH_HDMI_set_AUNIT_CTS(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CTS'. */
U32  GH_HDMI_get_AUNIT_CTS(void);
/*! \brief Writes the bit group 'AUNIT_CTS' of register 'HDMI_AUNIT_CTS'. */
void GH_HDMI_set_AUNIT_CTS_AUNIT_CTS(U32 data);
/*! \brief Reads the bit group 'AUNIT_CTS' of register 'HDMI_AUNIT_CTS'. */
U32  GH_HDMI_get_AUNIT_CTS_AUNIT_CTS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CTS(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CTS = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CTS] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CTS,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CTS(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CTS);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CTS] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CTS,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_AUNIT_CTS_AUNIT_CTS(U32 data)
{
    GH_HDMI_AUNIT_CTS_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_CTS;
    d.bitc.aunit_cts = data;
    *(volatile U32 *)REG_HDMI_AUNIT_CTS = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CTS_AUNIT_CTS] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CTS,d.all,d.all);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CTS_AUNIT_CTS(void)
{
    GH_HDMI_AUNIT_CTS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CTS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CTS_AUNIT_CTS] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CTS,value);
    #endif
    return tmp_value.bitc.aunit_cts;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_SRC (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_SRC'. */
U32  GH_HDMI_get_AUNIT_SRC(void);
/*! \brief Writes the bit group 'I2S0_EN' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_I2S0_EN(U8 data);
/*! \brief Reads the bit group 'I2S0_EN' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_I2S0_EN(void);
/*! \brief Writes the bit group 'I2S1_EN' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_I2S1_EN(U8 data);
/*! \brief Reads the bit group 'I2S1_EN' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_I2S1_EN(void);
/*! \brief Writes the bit group 'I2S2_EN' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_I2S2_EN(U8 data);
/*! \brief Reads the bit group 'I2S2_EN' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_I2S2_EN(void);
/*! \brief Writes the bit group 'FLAT_LINE0' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_FLAT_LINE0(U8 data);
/*! \brief Reads the bit group 'FLAT_LINE0' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE0(void);
/*! \brief Writes the bit group 'FLAT_LINE1' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_FLAT_LINE1(U8 data);
/*! \brief Reads the bit group 'FLAT_LINE1' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE1(void);
/*! \brief Writes the bit group 'FLAT_LINE2' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_FLAT_LINE2(U8 data);
/*! \brief Reads the bit group 'FLAT_LINE2' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_SRC(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_SRC(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_I2S0_EN(U8 data)
{
    GH_HDMI_AUNIT_SRC_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC;
    d.bitc.i2s0_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC_I2S0_EN] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_I2S0_EN(void)
{
    GH_HDMI_AUNIT_SRC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC_I2S0_EN] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return tmp_value.bitc.i2s0_en;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_I2S1_EN(U8 data)
{
    GH_HDMI_AUNIT_SRC_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC;
    d.bitc.i2s1_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC_I2S1_EN] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_I2S1_EN(void)
{
    GH_HDMI_AUNIT_SRC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC_I2S1_EN] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return tmp_value.bitc.i2s1_en;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_I2S2_EN(U8 data)
{
    GH_HDMI_AUNIT_SRC_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC;
    d.bitc.i2s2_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC_I2S2_EN] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_I2S2_EN(void)
{
    GH_HDMI_AUNIT_SRC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC_I2S2_EN] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return tmp_value.bitc.i2s2_en;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_FLAT_LINE0(U8 data)
{
    GH_HDMI_AUNIT_SRC_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC;
    d.bitc.flat_line0 = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC_FLAT_LINE0] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE0(void)
{
    GH_HDMI_AUNIT_SRC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC_FLAT_LINE0] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return tmp_value.bitc.flat_line0;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_FLAT_LINE1(U8 data)
{
    GH_HDMI_AUNIT_SRC_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC;
    d.bitc.flat_line1 = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC_FLAT_LINE1] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE1(void)
{
    GH_HDMI_AUNIT_SRC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC_FLAT_LINE1] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return tmp_value.bitc.flat_line1;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_FLAT_LINE2(U8 data)
{
    GH_HDMI_AUNIT_SRC_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC;
    d.bitc.flat_line2 = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_SRC_FLAT_LINE2] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE2(void)
{
    GH_HDMI_AUNIT_SRC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_SRC_FLAT_LINE2] --> 0x%08x\n",
                        REG_HDMI_AUNIT_SRC,value);
    #endif
    return tmp_value.bitc.flat_line2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS0 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CS0'. */
void GH_HDMI_set_AUNIT_CS0(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS0'. */
U32  GH_HDMI_get_AUNIT_CS0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CS0(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS0 = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CS0] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CS0,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS0(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS0);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CS0] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CS0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CS1'. */
void GH_HDMI_set_AUNIT_CS1(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS1'. */
U32  GH_HDMI_get_AUNIT_CS1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CS1(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS1 = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CS1] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CS1,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS1(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS1);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CS1] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CS1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CS2'. */
void GH_HDMI_set_AUNIT_CS2(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS2'. */
U32  GH_HDMI_get_AUNIT_CS2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CS2(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS2 = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CS2] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CS2,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS2(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS2);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CS2] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CS2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS3 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CS3'. */
void GH_HDMI_set_AUNIT_CS3(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS3'. */
U32  GH_HDMI_get_AUNIT_CS3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CS3(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS3 = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CS3] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CS3,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS3(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS3);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CS3] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CS3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS4 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CS4'. */
void GH_HDMI_set_AUNIT_CS4(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS4'. */
U32  GH_HDMI_get_AUNIT_CS4(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CS4(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS4 = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CS4] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CS4,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS4(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS4);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CS4] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CS4,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS5 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_CS5'. */
void GH_HDMI_set_AUNIT_CS5(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS5'. */
U32  GH_HDMI_get_AUNIT_CS5(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_CS5(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS5 = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_CS5] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_CS5,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS5(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS5);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_CS5] --> 0x%08x\n",
                        REG_HDMI_AUNIT_CS5,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_LAYOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_AUNIT_LAYOUT'. */
void GH_HDMI_set_AUNIT_LAYOUT(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_LAYOUT'. */
U32  GH_HDMI_get_AUNIT_LAYOUT(void);
/*! \brief Writes the bit group 'LAYOUT' of register 'HDMI_AUNIT_LAYOUT'. */
void GH_HDMI_set_AUNIT_LAYOUT_LAYOUT(U8 data);
/*! \brief Reads the bit group 'LAYOUT' of register 'HDMI_AUNIT_LAYOUT'. */
U8   GH_HDMI_get_AUNIT_LAYOUT_LAYOUT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_AUNIT_LAYOUT(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_LAYOUT = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_LAYOUT] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_LAYOUT,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_AUNIT_LAYOUT(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_LAYOUT);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_LAYOUT] --> 0x%08x\n",
                        REG_HDMI_AUNIT_LAYOUT,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_AUNIT_LAYOUT_LAYOUT(U8 data)
{
    GH_HDMI_AUNIT_LAYOUT_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_LAYOUT;
    d.bitc.layout = data;
    *(volatile U32 *)REG_HDMI_AUNIT_LAYOUT = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_AUNIT_LAYOUT_LAYOUT] <-- 0x%08x\n",
                        REG_HDMI_AUNIT_LAYOUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_AUNIT_LAYOUT_LAYOUT(void)
{
    GH_HDMI_AUNIT_LAYOUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_LAYOUT);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_AUNIT_LAYOUT_LAYOUT] --> 0x%08x\n",
                        REG_HDMI_AUNIT_LAYOUT,value);
    #endif
    return tmp_value.bitc.layout;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_TX_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_PACKET_TX_CTRL'. */
U32  GH_HDMI_get_PACKET_TX_CTRL(void);
/*! \brief Writes the bit group 'GEN_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GEN_EN(U8 data);
/*! \brief Reads the bit group 'GEN_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_EN(void);
/*! \brief Writes the bit group 'GEN_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GEN_RPT(U8 data);
/*! \brief Reads the bit group 'GEN_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_RPT(void);
/*! \brief Writes the bit group 'ACP_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ACP_EN(U8 data);
/*! \brief Reads the bit group 'ACP_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_EN(void);
/*! \brief Writes the bit group 'ACP_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ACP_RPT(U8 data);
/*! \brief Reads the bit group 'ACP_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_RPT(void);
/*! \brief Writes the bit group 'ISRC_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ISRC_EN(U8 data);
/*! \brief Reads the bit group 'ISRC_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_EN(void);
/*! \brief Writes the bit group 'ISRC_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ISRC_RPT(U8 data);
/*! \brief Reads the bit group 'ISRC_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_RPT(void);
/*! \brief Writes the bit group 'AVI_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AVI_EN(U8 data);
/*! \brief Reads the bit group 'AVI_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_EN(void);
/*! \brief Writes the bit group 'AVI_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AVI_RPT(U8 data);
/*! \brief Reads the bit group 'AVI_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_RPT(void);
/*! \brief Writes the bit group 'SPD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_SPD_EN(U8 data);
/*! \brief Reads the bit group 'SPD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_EN(void);
/*! \brief Writes the bit group 'SPD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_SPD_RPT(U8 data);
/*! \brief Reads the bit group 'SPD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_RPT(void);
/*! \brief Writes the bit group 'AUD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AUD_EN(U8 data);
/*! \brief Reads the bit group 'AUD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_EN(void);
/*! \brief Writes the bit group 'AUD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AUD_RPT(U8 data);
/*! \brief Reads the bit group 'AUD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_RPT(void);
/*! \brief Writes the bit group 'MPEG_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_MPEG_EN(U8 data);
/*! \brief Reads the bit group 'MPEG_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_EN(void);
/*! \brief Writes the bit group 'MPEG_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_MPEG_RPT(U8 data);
/*! \brief Reads the bit group 'MPEG_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_RPT(void);
/*! \brief Writes the bit group 'GAMUT_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_EN(U8 data);
/*! \brief Reads the bit group 'GAMUT_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_EN(void);
/*! \brief Writes the bit group 'GAMUT_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_RPT(U8 data);
/*! \brief Reads the bit group 'GAMUT_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_RPT(void);
/*! \brief Writes the bit group 'BUF_SWITCH_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_BUF_SWITCH_EN(U8 data);
/*! \brief Reads the bit group 'BUF_SWITCH_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_BUF_SWITCH_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET_TX_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GEN_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.gen_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_GEN_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_GEN_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.gen_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GEN_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.gen_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_GEN_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_GEN_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.gen_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ACP_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.acp_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_ACP_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_ACP_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.acp_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ACP_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.acp_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_ACP_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_ACP_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.acp_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ISRC_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.isrc_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_ISRC_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_ISRC_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.isrc_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ISRC_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.isrc_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_ISRC_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_ISRC_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.isrc_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AVI_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.avi_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_AVI_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_AVI_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.avi_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AVI_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.avi_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_AVI_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_AVI_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.avi_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_SPD_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.spd_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_SPD_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_SPD_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.spd_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_SPD_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.spd_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_SPD_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_SPD_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.spd_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AUD_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.aud_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_AUD_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_AUD_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.aud_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AUD_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.aud_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_AUD_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_AUD_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.aud_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_MPEG_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.mpeg_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_MPEG_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_MPEG_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.mpeg_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_MPEG_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.mpeg_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_MPEG_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_MPEG_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.mpeg_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.gamut_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_GAMUT_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_GAMUT_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.gamut_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.gamut_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_GAMUT_RPT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_GAMUT_RPT] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.gamut_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_BUF_SWITCH_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL;
    d.bitc.buf_switch_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_TX_CTRL_BUF_SWITCH_EN] <-- 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_BUF_SWITCH_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_TX_CTRL_BUF_SWITCH_EN] --> 0x%08x\n",
                        REG_HDMI_PACKET_TX_CTRL,value);
    #endif
    return tmp_value.bitc.buf_switch_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_GENERAL_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_PACKET_GENERAL_CTRL'. */
U32  GH_HDMI_get_PACKET_GENERAL_CTRL(void);
/*! \brief Writes the bit group 'SET_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_SET_AVMUTE(U8 data);
/*! \brief Reads the bit group 'SET_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_SET_AVMUTE(void);
/*! \brief Writes the bit group 'CLR_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_CLR_AVMUTE(U8 data);
/*! \brief Reads the bit group 'CLR_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CLR_AVMUTE(void);
/*! \brief Writes the bit group 'CD' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_CD(U8 data);
/*! \brief Reads the bit group 'CD' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CD(void);
/*! \brief Writes the bit group 'PP' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_PP(U8 data);
/*! \brief Reads the bit group 'PP' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_PP(void);
/*! \brief Writes the bit group 'DEF_PHASE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_DEF_PHASE(U8 data);
/*! \brief Reads the bit group 'DEF_PHASE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_DEF_PHASE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_GENERAL_CTRL] <-- 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET_GENERAL_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_GENERAL_CTRL] --> 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_SET_AVMUTE(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL;
    d.bitc.set_avmute = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_GENERAL_CTRL_SET_AVMUTE] <-- 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_SET_AVMUTE(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_GENERAL_CTRL_SET_AVMUTE] --> 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,value);
    #endif
    return tmp_value.bitc.set_avmute;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_CLR_AVMUTE(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL;
    d.bitc.clr_avmute = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_GENERAL_CTRL_CLR_AVMUTE] <-- 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CLR_AVMUTE(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_GENERAL_CTRL_CLR_AVMUTE] --> 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,value);
    #endif
    return tmp_value.bitc.clr_avmute;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_CD(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL;
    d.bitc.cd = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_GENERAL_CTRL_CD] <-- 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CD(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_GENERAL_CTRL_CD] --> 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,value);
    #endif
    return tmp_value.bitc.cd;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_PP(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL;
    d.bitc.pp = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_GENERAL_CTRL_PP] <-- 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_PP(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_GENERAL_CTRL_PP] --> 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,value);
    #endif
    return tmp_value.bitc.pp;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_DEF_PHASE(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL;
    d.bitc.def_phase = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_GENERAL_CTRL_DEF_PHASE] <-- 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_DEF_PHASE(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_GENERAL_CTRL_DEF_PHASE] --> 0x%08x\n",
                        REG_HDMI_PACKET_GENERAL_CTRL,value);
    #endif
    return tmp_value.bitc.def_phase;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET0 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET0'. */
U32  GH_HDMI_get_PACKET0(U8 index);
/*! \brief Writes the bit group 'ACP_HB0' of register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0_ACP_HB0(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_HB0' of register 'HDMI_PACKET0'. */
U8   GH_HDMI_get_PACKET0_ACP_HB0(U8 index);
/*! \brief Writes the bit group 'ACP_HB1' of register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0_ACP_HB1(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_HB1' of register 'HDMI_PACKET0'. */
U8   GH_HDMI_get_PACKET0_ACP_HB1(U8 index);
/*! \brief Writes the bit group 'ACP_HB2' of register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0_ACP_HB2(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_HB2' of register 'HDMI_PACKET0'. */
U8   GH_HDMI_get_PACKET0_ACP_HB2(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET0(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET0] <-- 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET0(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET0] --> 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET0_ACP_HB0(U8 index, U8 data)
{
    GH_HDMI_PACKET0_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_hb0 = data;
    *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET0_ACP_HB0] <-- 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET0_ACP_HB0(U8 index)
{
    GH_HDMI_PACKET0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET0_ACP_HB0] --> 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_hb0;
}
GH_INLINE void GH_HDMI_set_PACKET0_ACP_HB1(U8 index, U8 data)
{
    GH_HDMI_PACKET0_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_hb1 = data;
    *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET0_ACP_HB1] <-- 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET0_ACP_HB1(U8 index)
{
    GH_HDMI_PACKET0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET0_ACP_HB1] --> 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_hb1;
}
GH_INLINE void GH_HDMI_set_PACKET0_ACP_HB2(U8 index, U8 data)
{
    GH_HDMI_PACKET0_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_hb2 = data;
    *(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET0_ACP_HB2] <-- 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET0_ACP_HB2(U8 index)
{
    GH_HDMI_PACKET0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET0_ACP_HB2] --> 0x%08x\n",
                        (REG_HDMI_PACKET0 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_hb2;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET1'. */
U32  GH_HDMI_get_PACKET1(U8 index);
/*! \brief Writes the bit group 'ACP_PB0' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB0(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB0' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB0(U8 index);
/*! \brief Writes the bit group 'ACP_PB1' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB1(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB1' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB1(U8 index);
/*! \brief Writes the bit group 'ACP_PB2' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB2(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB2' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB2(U8 index);
/*! \brief Writes the bit group 'ACP_PB3' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB3(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB3' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB3(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET1(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET1] <-- 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET1] --> 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB0(U8 index, U8 data)
{
    GH_HDMI_PACKET1_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb0 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET1_ACP_PB0] <-- 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB0(U8 index)
{
    GH_HDMI_PACKET1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET1_ACP_PB0] --> 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb0;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB1(U8 index, U8 data)
{
    GH_HDMI_PACKET1_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb1 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET1_ACP_PB1] <-- 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB1(U8 index)
{
    GH_HDMI_PACKET1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET1_ACP_PB1] --> 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb1;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB2(U8 index, U8 data)
{
    GH_HDMI_PACKET1_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb2 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET1_ACP_PB2] <-- 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB2(U8 index)
{
    GH_HDMI_PACKET1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET1_ACP_PB2] --> 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb2;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB3(U8 index, U8 data)
{
    GH_HDMI_PACKET1_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb3 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET1_ACP_PB3] <-- 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB3(U8 index)
{
    GH_HDMI_PACKET1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET1_ACP_PB3] --> 0x%08x\n",
                        (REG_HDMI_PACKET1 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET2 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET2'. */
U32  GH_HDMI_get_PACKET2(U8 index);
/*! \brief Writes the bit group 'ACP_PB4' of register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2_ACP_PB4(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB4' of register 'HDMI_PACKET2'. */
U8   GH_HDMI_get_PACKET2_ACP_PB4(U8 index);
/*! \brief Writes the bit group 'ACP_PB5' of register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2_ACP_PB5(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB5' of register 'HDMI_PACKET2'. */
U8   GH_HDMI_get_PACKET2_ACP_PB5(U8 index);
/*! \brief Writes the bit group 'ACP_PB6' of register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2_ACP_PB6(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB6' of register 'HDMI_PACKET2'. */
U8   GH_HDMI_get_PACKET2_ACP_PB6(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET2(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET2] <-- 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET2(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET2] --> 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET2_ACP_PB4(U8 index, U8 data)
{
    GH_HDMI_PACKET2_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb4 = data;
    *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET2_ACP_PB4] <-- 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET2_ACP_PB4(U8 index)
{
    GH_HDMI_PACKET2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET2_ACP_PB4] --> 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb4;
}
GH_INLINE void GH_HDMI_set_PACKET2_ACP_PB5(U8 index, U8 data)
{
    GH_HDMI_PACKET2_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb5 = data;
    *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET2_ACP_PB5] <-- 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET2_ACP_PB5(U8 index)
{
    GH_HDMI_PACKET2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET2_ACP_PB5] --> 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb5;
}
GH_INLINE void GH_HDMI_set_PACKET2_ACP_PB6(U8 index, U8 data)
{
    GH_HDMI_PACKET2_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb6 = data;
    *(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET2_ACP_PB6] <-- 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET2_ACP_PB6(U8 index)
{
    GH_HDMI_PACKET2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET2_ACP_PB6] --> 0x%08x\n",
                        (REG_HDMI_PACKET2 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb6;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET3 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET3'. */
U32  GH_HDMI_get_PACKET3(U8 index);
/*! \brief Writes the bit group 'ACP_PB7' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB7(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB7' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB7(U8 index);
/*! \brief Writes the bit group 'ACP_PB8' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB8(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB8' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB8(U8 index);
/*! \brief Writes the bit group 'ACP_PB9' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB9(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB9' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB9(U8 index);
/*! \brief Writes the bit group 'ACP_PB10' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB10(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB10' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB10(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET3(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET3] <-- 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET3(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET3] --> 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB7(U8 index, U8 data)
{
    GH_HDMI_PACKET3_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb7 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET3_ACP_PB7] <-- 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB7(U8 index)
{
    GH_HDMI_PACKET3_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET3_ACP_PB7] --> 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb7;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB8(U8 index, U8 data)
{
    GH_HDMI_PACKET3_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb8 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET3_ACP_PB8] <-- 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB8(U8 index)
{
    GH_HDMI_PACKET3_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET3_ACP_PB8] --> 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb8;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB9(U8 index, U8 data)
{
    GH_HDMI_PACKET3_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb9 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET3_ACP_PB9] <-- 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB9(U8 index)
{
    GH_HDMI_PACKET3_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET3_ACP_PB9] --> 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb9;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB10(U8 index, U8 data)
{
    GH_HDMI_PACKET3_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb10 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET3_ACP_PB10] <-- 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB10(U8 index)
{
    GH_HDMI_PACKET3_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET3_ACP_PB10] --> 0x%08x\n",
                        (REG_HDMI_PACKET3 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb10;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET4 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET4'. */
U32  GH_HDMI_get_PACKET4(U8 index);
/*! \brief Writes the bit group 'ACP_PB11' of register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4_ACP_PB11(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB11' of register 'HDMI_PACKET4'. */
U8   GH_HDMI_get_PACKET4_ACP_PB11(U8 index);
/*! \brief Writes the bit group 'ACP_PB12' of register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4_ACP_PB12(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB12' of register 'HDMI_PACKET4'. */
U8   GH_HDMI_get_PACKET4_ACP_PB12(U8 index);
/*! \brief Writes the bit group 'ACP_PB13' of register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4_ACP_PB13(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB13' of register 'HDMI_PACKET4'. */
U8   GH_HDMI_get_PACKET4_ACP_PB13(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET4(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET4] <-- 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET4(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET4] --> 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET4_ACP_PB11(U8 index, U8 data)
{
    GH_HDMI_PACKET4_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb11 = data;
    *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET4_ACP_PB11] <-- 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET4_ACP_PB11(U8 index)
{
    GH_HDMI_PACKET4_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET4_ACP_PB11] --> 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb11;
}
GH_INLINE void GH_HDMI_set_PACKET4_ACP_PB12(U8 index, U8 data)
{
    GH_HDMI_PACKET4_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb12 = data;
    *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET4_ACP_PB12] <-- 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET4_ACP_PB12(U8 index)
{
    GH_HDMI_PACKET4_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET4_ACP_PB12] --> 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb12;
}
GH_INLINE void GH_HDMI_set_PACKET4_ACP_PB13(U8 index, U8 data)
{
    GH_HDMI_PACKET4_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb13 = data;
    *(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET4_ACP_PB13] <-- 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET4_ACP_PB13(U8 index)
{
    GH_HDMI_PACKET4_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET4_ACP_PB13] --> 0x%08x\n",
                        (REG_HDMI_PACKET4 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb13;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET5 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET5'. */
U32  GH_HDMI_get_PACKET5(U8 index);
/*! \brief Writes the bit group 'ACP_PB14' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB14(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB14' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB14(U8 index);
/*! \brief Writes the bit group 'ACP_PB15' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB15(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB15' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB15(U8 index);
/*! \brief Writes the bit group 'ACP_PB16' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB16(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB16' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB16(U8 index);
/*! \brief Writes the bit group 'ACP_PB17' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB17(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB17' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB17(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET5(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET5] <-- 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET5(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET5] --> 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB14(U8 index, U8 data)
{
    GH_HDMI_PACKET5_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb14 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET5_ACP_PB14] <-- 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB14(U8 index)
{
    GH_HDMI_PACKET5_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET5_ACP_PB14] --> 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb14;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB15(U8 index, U8 data)
{
    GH_HDMI_PACKET5_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb15 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET5_ACP_PB15] <-- 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB15(U8 index)
{
    GH_HDMI_PACKET5_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET5_ACP_PB15] --> 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb15;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB16(U8 index, U8 data)
{
    GH_HDMI_PACKET5_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb16 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET5_ACP_PB16] <-- 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB16(U8 index)
{
    GH_HDMI_PACKET5_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET5_ACP_PB16] --> 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb16;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB17(U8 index, U8 data)
{
    GH_HDMI_PACKET5_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb17 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET5_ACP_PB17] <-- 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB17(U8 index)
{
    GH_HDMI_PACKET5_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET5_ACP_PB17] --> 0x%08x\n",
                        (REG_HDMI_PACKET5 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb17;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET6 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET6'. */
U32  GH_HDMI_get_PACKET6(U8 index);
/*! \brief Writes the bit group 'ACP_PB18' of register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6_ACP_PB18(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB18' of register 'HDMI_PACKET6'. */
U8   GH_HDMI_get_PACKET6_ACP_PB18(U8 index);
/*! \brief Writes the bit group 'ACP_PB19' of register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6_ACP_PB19(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB19' of register 'HDMI_PACKET6'. */
U8   GH_HDMI_get_PACKET6_ACP_PB19(U8 index);
/*! \brief Writes the bit group 'ACP_PB20' of register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6_ACP_PB20(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB20' of register 'HDMI_PACKET6'. */
U8   GH_HDMI_get_PACKET6_ACP_PB20(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET6(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET6] <-- 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET6(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET6] --> 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET6_ACP_PB18(U8 index, U8 data)
{
    GH_HDMI_PACKET6_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb18 = data;
    *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET6_ACP_PB18] <-- 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET6_ACP_PB18(U8 index)
{
    GH_HDMI_PACKET6_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET6_ACP_PB18] --> 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb18;
}
GH_INLINE void GH_HDMI_set_PACKET6_ACP_PB19(U8 index, U8 data)
{
    GH_HDMI_PACKET6_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb19 = data;
    *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET6_ACP_PB19] <-- 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET6_ACP_PB19(U8 index)
{
    GH_HDMI_PACKET6_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET6_ACP_PB19] --> 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb19;
}
GH_INLINE void GH_HDMI_set_PACKET6_ACP_PB20(U8 index, U8 data)
{
    GH_HDMI_PACKET6_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb20 = data;
    *(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET6_ACP_PB20] <-- 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET6_ACP_PB20(U8 index)
{
    GH_HDMI_PACKET6_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET6_ACP_PB20] --> 0x%08x\n",
                        (REG_HDMI_PACKET6 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb20;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET7 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET7'. */
U32  GH_HDMI_get_PACKET7(U8 index);
/*! \brief Writes the bit group 'ACP_PB21' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB21(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB21' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB21(U8 index);
/*! \brief Writes the bit group 'ACP_PB22' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB22(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB22' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB22(U8 index);
/*! \brief Writes the bit group 'ACP_PB23' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB23(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB23' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB23(U8 index);
/*! \brief Writes the bit group 'ACP_PB24' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB24(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB24' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB24(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET7(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET7] <-- 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET7(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET7] --> 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB21(U8 index, U8 data)
{
    GH_HDMI_PACKET7_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb21 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET7_ACP_PB21] <-- 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB21(U8 index)
{
    GH_HDMI_PACKET7_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET7_ACP_PB21] --> 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb21;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB22(U8 index, U8 data)
{
    GH_HDMI_PACKET7_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb22 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET7_ACP_PB22] <-- 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB22(U8 index)
{
    GH_HDMI_PACKET7_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET7_ACP_PB22] --> 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb22;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB23(U8 index, U8 data)
{
    GH_HDMI_PACKET7_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb23 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET7_ACP_PB23] <-- 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB23(U8 index)
{
    GH_HDMI_PACKET7_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET7_ACP_PB23] --> 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb23;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB24(U8 index, U8 data)
{
    GH_HDMI_PACKET7_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb24 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET7_ACP_PB24] <-- 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB24(U8 index)
{
    GH_HDMI_PACKET7_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET7_ACP_PB24] --> 0x%08x\n",
                        (REG_HDMI_PACKET7 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb24;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET8 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET8'. */
U32  GH_HDMI_get_PACKET8(U8 index);
/*! \brief Writes the bit group 'ACP_PB25' of register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8_ACP_PB25(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB25' of register 'HDMI_PACKET8'. */
U8   GH_HDMI_get_PACKET8_ACP_PB25(U8 index);
/*! \brief Writes the bit group 'ACP_PB26' of register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8_ACP_PB26(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB26' of register 'HDMI_PACKET8'. */
U8   GH_HDMI_get_PACKET8_ACP_PB26(U8 index);
/*! \brief Writes the bit group 'ACP_PB27' of register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8_ACP_PB27(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB27' of register 'HDMI_PACKET8'. */
U8   GH_HDMI_get_PACKET8_ACP_PB27(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET8(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET8] <-- 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET8(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET8] --> 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET8_ACP_PB25(U8 index, U8 data)
{
    GH_HDMI_PACKET8_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb25 = data;
    *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET8_ACP_PB25] <-- 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET8_ACP_PB25(U8 index)
{
    GH_HDMI_PACKET8_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET8_ACP_PB25] --> 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb25;
}
GH_INLINE void GH_HDMI_set_PACKET8_ACP_PB26(U8 index, U8 data)
{
    GH_HDMI_PACKET8_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb26 = data;
    *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET8_ACP_PB26] <-- 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET8_ACP_PB26(U8 index)
{
    GH_HDMI_PACKET8_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET8_ACP_PB26] --> 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb26;
}
GH_INLINE void GH_HDMI_set_PACKET8_ACP_PB27(U8 index, U8 data)
{
    GH_HDMI_PACKET8_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb27 = data;
    *(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET8_ACP_PB27] <-- 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET8_ACP_PB27(U8 index)
{
    GH_HDMI_PACKET8_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET8_ACP_PB27] --> 0x%08x\n",
                        (REG_HDMI_PACKET8 + index * FIO_MOFFSET(HDMI,0x24)),value);
    #endif
    return tmp_value.bitc.acp_pb27;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_MODE (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_MODE'. */
void GH_HDMI_set_I2S_MODE(U32 data);
/*! \brief Reads the register 'HDMI_I2S_MODE'. */
U32  GH_HDMI_get_I2S_MODE(void);
/*! \brief Writes the bit group 'dai_mode' of register 'HDMI_I2S_MODE'. */
void GH_HDMI_set_I2S_MODE_dai_mode(U8 data);
/*! \brief Reads the bit group 'dai_mode' of register 'HDMI_I2S_MODE'. */
U8   GH_HDMI_get_I2S_MODE_dai_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_MODE(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_MODE = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_MODE] <-- 0x%08x\n",
                        REG_HDMI_I2S_MODE,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_MODE(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_MODE);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_MODE] --> 0x%08x\n",
                        REG_HDMI_I2S_MODE,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_MODE_dai_mode(U8 data)
{
    GH_HDMI_I2S_MODE_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_MODE;
    d.bitc.dai_mode = data;
    *(volatile U32 *)REG_HDMI_I2S_MODE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_MODE_dai_mode] <-- 0x%08x\n",
                        REG_HDMI_I2S_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_MODE_dai_mode(void)
{
    GH_HDMI_I2S_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_MODE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_MODE_dai_mode] --> 0x%08x\n",
                        REG_HDMI_I2S_MODE,value);
    #endif
    return tmp_value.bitc.dai_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_CTRL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_I2S_RX_CTRL'. */
U32  GH_HDMI_get_I2S_RX_CTRL(void);
/*! \brief Writes the bit group 'rx_ws_inv' of register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL_rx_ws_inv(U8 data);
/*! \brief Reads the bit group 'rx_ws_inv' of register 'HDMI_I2S_RX_CTRL'. */
U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_inv(void);
/*! \brief Writes the bit group 'rx_ws_mst' of register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL_rx_ws_mst(U8 data);
/*! \brief Reads the bit group 'rx_ws_mst' of register 'HDMI_I2S_RX_CTRL'. */
U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_mst(void);
/*! \brief Writes the bit group 'rx_ord' of register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL_rx_ord(U8 data);
/*! \brief Reads the bit group 'rx_ord' of register 'HDMI_I2S_RX_CTRL'. */
U8   GH_HDMI_get_I2S_RX_CTRL_rx_ord(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_CTRL] <-- 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_CTRL] --> 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL_rx_ws_inv(U8 data)
{
    GH_HDMI_I2S_RX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_CTRL;
    d.bitc.rx_ws_inv = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_CTRL_rx_ws_inv] <-- 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_inv(void)
{
    GH_HDMI_I2S_RX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_CTRL_rx_ws_inv] --> 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,value);
    #endif
    return tmp_value.bitc.rx_ws_inv;
}
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL_rx_ws_mst(U8 data)
{
    GH_HDMI_I2S_RX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_CTRL;
    d.bitc.rx_ws_mst = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_CTRL_rx_ws_mst] <-- 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_mst(void)
{
    GH_HDMI_I2S_RX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_CTRL_rx_ws_mst] --> 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,value);
    #endif
    return tmp_value.bitc.rx_ws_mst;
}
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL_rx_ord(U8 data)
{
    GH_HDMI_I2S_RX_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_CTRL;
    d.bitc.rx_ord = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_CTRL_rx_ord] <-- 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_CTRL_rx_ord(void)
{
    GH_HDMI_I2S_RX_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_CTRL_rx_ord] --> 0x%08x\n",
                        REG_HDMI_I2S_RX_CTRL,value);
    #endif
    return tmp_value.bitc.rx_ord;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_WLEN (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_WLEN'. */
void GH_HDMI_set_I2S_WLEN(U32 data);
/*! \brief Reads the register 'HDMI_I2S_WLEN'. */
U32  GH_HDMI_get_I2S_WLEN(void);
/*! \brief Writes the bit group 'dai_wlen' of register 'HDMI_I2S_WLEN'. */
void GH_HDMI_set_I2S_WLEN_dai_wlen(U8 data);
/*! \brief Reads the bit group 'dai_wlen' of register 'HDMI_I2S_WLEN'. */
U8   GH_HDMI_get_I2S_WLEN_dai_wlen(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_WLEN(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_WLEN = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_WLEN] <-- 0x%08x\n",
                        REG_HDMI_I2S_WLEN,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_WLEN(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_WLEN);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_WLEN] --> 0x%08x\n",
                        REG_HDMI_I2S_WLEN,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_WLEN_dai_wlen(U8 data)
{
    GH_HDMI_I2S_WLEN_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_WLEN;
    d.bitc.dai_wlen = data;
    *(volatile U32 *)REG_HDMI_I2S_WLEN = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_WLEN_dai_wlen] <-- 0x%08x\n",
                        REG_HDMI_I2S_WLEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_WLEN_dai_wlen(void)
{
    GH_HDMI_I2S_WLEN_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_WLEN);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_WLEN_dai_wlen] --> 0x%08x\n",
                        REG_HDMI_I2S_WLEN,value);
    #endif
    return tmp_value.bitc.dai_wlen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_WPOS (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_WPOS'. */
void GH_HDMI_set_I2S_WPOS(U32 data);
/*! \brief Reads the register 'HDMI_I2S_WPOS'. */
U32  GH_HDMI_get_I2S_WPOS(void);
/*! \brief Writes the bit group 'dai_wpos' of register 'HDMI_I2S_WPOS'. */
void GH_HDMI_set_I2S_WPOS_dai_wpos(U8 data);
/*! \brief Reads the bit group 'dai_wpos' of register 'HDMI_I2S_WPOS'. */
U8   GH_HDMI_get_I2S_WPOS_dai_wpos(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_WPOS(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_WPOS = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_WPOS] <-- 0x%08x\n",
                        REG_HDMI_I2S_WPOS,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_WPOS(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_WPOS);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_WPOS] --> 0x%08x\n",
                        REG_HDMI_I2S_WPOS,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_WPOS_dai_wpos(U8 data)
{
    GH_HDMI_I2S_WPOS_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_WPOS;
    d.bitc.dai_wpos = data;
    *(volatile U32 *)REG_HDMI_I2S_WPOS = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_WPOS_dai_wpos] <-- 0x%08x\n",
                        REG_HDMI_I2S_WPOS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_WPOS_dai_wpos(void)
{
    GH_HDMI_I2S_WPOS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_WPOS);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_WPOS_dai_wpos] --> 0x%08x\n",
                        REG_HDMI_I2S_WPOS,value);
    #endif
    return tmp_value.bitc.dai_wpos;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_SLOT (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_SLOT'. */
void GH_HDMI_set_I2S_SLOT(U32 data);
/*! \brief Reads the register 'HDMI_I2S_SLOT'. */
U32  GH_HDMI_get_I2S_SLOT(void);
/*! \brief Writes the bit group 'dai_slot' of register 'HDMI_I2S_SLOT'. */
void GH_HDMI_set_I2S_SLOT_dai_slot(U8 data);
/*! \brief Reads the bit group 'dai_slot' of register 'HDMI_I2S_SLOT'. */
U8   GH_HDMI_get_I2S_SLOT_dai_slot(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_SLOT(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_SLOT = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_SLOT] <-- 0x%08x\n",
                        REG_HDMI_I2S_SLOT,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_SLOT(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_SLOT);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_SLOT] --> 0x%08x\n",
                        REG_HDMI_I2S_SLOT,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_SLOT_dai_slot(U8 data)
{
    GH_HDMI_I2S_SLOT_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_SLOT;
    d.bitc.dai_slot = data;
    *(volatile U32 *)REG_HDMI_I2S_SLOT = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_SLOT_dai_slot] <-- 0x%08x\n",
                        REG_HDMI_I2S_SLOT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_SLOT_dai_slot(void)
{
    GH_HDMI_I2S_SLOT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_SLOT);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_SLOT_dai_slot] --> 0x%08x\n",
                        REG_HDMI_I2S_SLOT,value);
    #endif
    return tmp_value.bitc.dai_slot;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_FIFO_GTH (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_RX_FIFO_GTH'. */
void GH_HDMI_set_I2S_RX_FIFO_GTH(U32 data);
/*! \brief Reads the register 'HDMI_I2S_RX_FIFO_GTH'. */
U32  GH_HDMI_get_I2S_RX_FIFO_GTH(void);
/*! \brief Writes the bit group 'rx_FIFO_gth' of register 'HDMI_I2S_RX_FIFO_GTH'. */
void GH_HDMI_set_I2S_RX_FIFO_GTH_rx_FIFO_gth(U8 data);
/*! \brief Reads the bit group 'rx_FIFO_gth' of register 'HDMI_I2S_RX_FIFO_GTH'. */
U8   GH_HDMI_get_I2S_RX_FIFO_GTH_rx_FIFO_gth(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_RX_FIFO_GTH(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_FIFO_GTH] <-- 0x%08x\n",
                        REG_HDMI_I2S_RX_FIFO_GTH,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_FIFO_GTH(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_FIFO_GTH] --> 0x%08x\n",
                        REG_HDMI_I2S_RX_FIFO_GTH,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_RX_FIFO_GTH_rx_FIFO_gth(U8 data)
{
    GH_HDMI_I2S_RX_FIFO_GTH_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH;
    d.bitc.rx_fifo_gth = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_FIFO_GTH_rx_FIFO_gth] <-- 0x%08x\n",
                        REG_HDMI_I2S_RX_FIFO_GTH,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_FIFO_GTH_rx_FIFO_gth(void)
{
    GH_HDMI_I2S_RX_FIFO_GTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_FIFO_GTH_rx_FIFO_gth] --> 0x%08x\n",
                        REG_HDMI_I2S_RX_FIFO_GTH,value);
    #endif
    return tmp_value.bitc.rx_fifo_gth;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_CLOCK (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_CLOCK'. */
void GH_HDMI_set_I2S_CLOCK(U32 data);
/*! \brief Reads the register 'HDMI_I2S_CLOCK'. */
U32  GH_HDMI_get_I2S_CLOCK(void);
/*! \brief Writes the bit group 'rx_scp' of register 'HDMI_I2S_CLOCK'. */
void GH_HDMI_set_I2S_CLOCK_rx_scp(U8 data);
/*! \brief Reads the bit group 'rx_scp' of register 'HDMI_I2S_CLOCK'. */
U8   GH_HDMI_get_I2S_CLOCK_rx_scp(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_CLOCK(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_CLOCK = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_CLOCK] <-- 0x%08x\n",
                        REG_HDMI_I2S_CLOCK,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_CLOCK(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_CLOCK);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_CLOCK] --> 0x%08x\n",
                        REG_HDMI_I2S_CLOCK,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_CLOCK_rx_scp(U8 data)
{
    GH_HDMI_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_CLOCK;
    d.bitc.rx_scp = data;
    *(volatile U32 *)REG_HDMI_I2S_CLOCK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_CLOCK_rx_scp] <-- 0x%08x\n",
                        REG_HDMI_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_CLOCK_rx_scp(void)
{
    GH_HDMI_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_CLOCK_rx_scp] --> 0x%08x\n",
                        REG_HDMI_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.rx_scp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_INIT (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_INIT'. */
void GH_HDMI_set_I2S_INIT(U32 data);
/*! \brief Reads the register 'HDMI_I2S_INIT'. */
U32  GH_HDMI_get_I2S_INIT(void);
/*! \brief Writes the bit group 'dai_reset' of register 'HDMI_I2S_INIT'. */
void GH_HDMI_set_I2S_INIT_dai_reset(U8 data);
/*! \brief Reads the bit group 'dai_reset' of register 'HDMI_I2S_INIT'. */
U8   GH_HDMI_get_I2S_INIT_dai_reset(void);
/*! \brief Writes the bit group 'rx_enable' of register 'HDMI_I2S_INIT'. */
void GH_HDMI_set_I2S_INIT_rx_enable(U8 data);
/*! \brief Reads the bit group 'rx_enable' of register 'HDMI_I2S_INIT'. */
U8   GH_HDMI_get_I2S_INIT_rx_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_INIT(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_INIT = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_INIT] <-- 0x%08x\n",
                        REG_HDMI_I2S_INIT,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_INIT(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_INIT);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_INIT] --> 0x%08x\n",
                        REG_HDMI_I2S_INIT,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_INIT_dai_reset(U8 data)
{
    GH_HDMI_I2S_INIT_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_INIT;
    d.bitc.dai_reset = data;
    *(volatile U32 *)REG_HDMI_I2S_INIT = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_INIT_dai_reset] <-- 0x%08x\n",
                        REG_HDMI_I2S_INIT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_INIT_dai_reset(void)
{
    GH_HDMI_I2S_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_INIT);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_INIT_dai_reset] --> 0x%08x\n",
                        REG_HDMI_I2S_INIT,value);
    #endif
    return tmp_value.bitc.dai_reset;
}
GH_INLINE void GH_HDMI_set_I2S_INIT_rx_enable(U8 data)
{
    GH_HDMI_I2S_INIT_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_INIT;
    d.bitc.rx_enable = data;
    *(volatile U32 *)REG_HDMI_I2S_INIT = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_INIT_rx_enable] <-- 0x%08x\n",
                        REG_HDMI_I2S_INIT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_INIT_rx_enable(void)
{
    GH_HDMI_I2S_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_INIT);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_INIT_rx_enable] --> 0x%08x\n",
                        REG_HDMI_I2S_INIT,value);
    #endif
    return tmp_value.bitc.rx_enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_DATA (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_RX_DATA'. */
void GH_HDMI_set_I2S_RX_DATA(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_I2S_RX_DATA'. */
U32  GH_HDMI_get_I2S_RX_DATA(U8 index);
/*! \brief Writes the bit group 'rx_FIFO_dout' of register 'HDMI_I2S_RX_DATA'. */
void GH_HDMI_set_I2S_RX_DATA_rx_FIFO_dout(U8 index, U32 data);
/*! \brief Reads the bit group 'rx_FIFO_dout' of register 'HDMI_I2S_RX_DATA'. */
U32  GH_HDMI_get_I2S_RX_DATA_rx_FIFO_dout(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_RX_DATA(U8 index, U32 data)
{
    *(volatile U32 *)(REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)) = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_DATA] <-- 0x%08x\n",
                        (REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)),data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_DATA(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)));

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_DATA] --> 0x%08x\n",
                        (REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)),value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_RX_DATA_rx_FIFO_dout(U8 index, U32 data)
{
    GH_HDMI_I2S_RX_DATA_S d;
    d.all = *(volatile U32 *)(REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4));
    d.bitc.rx_fifo_dout = data;
    *(volatile U32 *)(REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)) = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_RX_DATA_rx_FIFO_dout] <-- 0x%08x\n",
                        (REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)),d.all,d.all);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_DATA_rx_FIFO_dout(U8 index)
{
    GH_HDMI_I2S_RX_DATA_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)));

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_RX_DATA_rx_FIFO_dout] --> 0x%08x\n",
                        (REG_HDMI_I2S_RX_DATA + index * FIO_MOFFSET(HDMI,0x4)),value);
    #endif
    return tmp_value.bitc.rx_fifo_dout;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_FIFO_CNTR (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_FIFO_CNTR'. */
void GH_HDMI_set_I2S_FIFO_CNTR(U32 data);
/*! \brief Reads the register 'HDMI_I2S_FIFO_CNTR'. */
U32  GH_HDMI_get_I2S_FIFO_CNTR(void);
/*! \brief Writes the bit group 'rx_FIFO_cntr' of register 'HDMI_I2S_FIFO_CNTR'. */
void GH_HDMI_set_I2S_FIFO_CNTR_rx_FIFO_cntr(U8 data);
/*! \brief Reads the bit group 'rx_FIFO_cntr' of register 'HDMI_I2S_FIFO_CNTR'. */
U8   GH_HDMI_get_I2S_FIFO_CNTR_rx_FIFO_cntr(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_FIFO_CNTR(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_FIFO_CNTR] <-- 0x%08x\n",
                        REG_HDMI_I2S_FIFO_CNTR,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_FIFO_CNTR(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_FIFO_CNTR] --> 0x%08x\n",
                        REG_HDMI_I2S_FIFO_CNTR,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_FIFO_CNTR_rx_FIFO_cntr(U8 data)
{
    GH_HDMI_I2S_FIFO_CNTR_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR;
    d.bitc.rx_fifo_cntr = data;
    *(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_FIFO_CNTR_rx_FIFO_cntr] <-- 0x%08x\n",
                        REG_HDMI_I2S_FIFO_CNTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_FIFO_CNTR_rx_FIFO_cntr(void)
{
    GH_HDMI_I2S_FIFO_CNTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_FIFO_CNTR_rx_FIFO_cntr] --> 0x%08x\n",
                        REG_HDMI_I2S_FIFO_CNTR,value);
    #endif
    return tmp_value.bitc.rx_fifo_cntr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_GATE_OFF (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_I2S_GATE_OFF'. */
void GH_HDMI_set_I2S_GATE_OFF(U32 data);
/*! \brief Reads the register 'HDMI_I2S_GATE_OFF'. */
U32  GH_HDMI_get_I2S_GATE_OFF(void);
/*! \brief Writes the bit group 'gate_off_en' of register 'HDMI_I2S_GATE_OFF'. */
void GH_HDMI_set_I2S_GATE_OFF_gate_off_en(U8 data);
/*! \brief Reads the bit group 'gate_off_en' of register 'HDMI_I2S_GATE_OFF'. */
U8   GH_HDMI_get_I2S_GATE_OFF_gate_off_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_I2S_GATE_OFF(U32 data)
{
    *(volatile U32 *)REG_HDMI_I2S_GATE_OFF = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_GATE_OFF] <-- 0x%08x\n",
                        REG_HDMI_I2S_GATE_OFF,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_I2S_GATE_OFF(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_GATE_OFF);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_GATE_OFF] --> 0x%08x\n",
                        REG_HDMI_I2S_GATE_OFF,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_I2S_GATE_OFF_gate_off_en(U8 data)
{
    GH_HDMI_I2S_GATE_OFF_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_GATE_OFF;
    d.bitc.gate_off_en = data;
    *(volatile U32 *)REG_HDMI_I2S_GATE_OFF = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_I2S_GATE_OFF_gate_off_en] <-- 0x%08x\n",
                        REG_HDMI_I2S_GATE_OFF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_I2S_GATE_OFF_gate_off_en(void)
{
    GH_HDMI_I2S_GATE_OFF_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_GATE_OFF);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_I2S_GATE_OFF_gate_off_en] --> 0x%08x\n",
                        REG_HDMI_I2S_GATE_OFF,value);
    #endif
    return tmp_value.bitc.gate_off_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_MISC (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC(U32 data);
/*! \brief Reads the register 'HDMI_PACKET_MISC'. */
U32  GH_HDMI_get_PACKET_MISC(void);
/*! \brief Writes the bit group 'LEFT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_LEFT_VALID_BIT(U8 data);
/*! \brief Reads the bit group 'LEFT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_LEFT_VALID_BIT(void);
/*! \brief Writes the bit group 'RIGHT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_RIGHT_VALID_BIT(U8 data);
/*! \brief Reads the bit group 'RIGHT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_RIGHT_VALID_BIT(void);
/*! \brief Writes the bit group 'SPD_SEND_CTRL' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_SPD_SEND_CTRL(U8 data);
/*! \brief Reads the bit group 'SPD_SEND_CTRL' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_SPD_SEND_CTRL(void);
/*! \brief Writes the bit group 'CTS_SW_MODE' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_CTS_SW_MODE(U8 data);
/*! \brief Reads the bit group 'CTS_SW_MODE' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_CTS_SW_MODE(void);
/*! \brief Writes the bit group 'NCTS_PRIORITY' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_NCTS_PRIORITY(U8 data);
/*! \brief Reads the bit group 'NCTS_PRIORITY' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_NCTS_PRIORITY(void);
/*! \brief Writes the bit group 'I2S_RX_MODE' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_I2S_RX_MODE(U8 data);
/*! \brief Reads the bit group 'I2S_RX_MODE' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_I2S_RX_MODE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_PACKET_MISC(U32 data)
{
    *(volatile U32 *)REG_HDMI_PACKET_MISC = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_PACKET_MISC(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_LEFT_VALID_BIT(U8 data)
{
    GH_HDMI_PACKET_MISC_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC;
    d.bitc.left_valid_bit = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC_LEFT_VALID_BIT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_LEFT_VALID_BIT(void)
{
    GH_HDMI_PACKET_MISC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC_LEFT_VALID_BIT] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return tmp_value.bitc.left_valid_bit;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_RIGHT_VALID_BIT(U8 data)
{
    GH_HDMI_PACKET_MISC_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC;
    d.bitc.right_valid_bit = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC_RIGHT_VALID_BIT] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_RIGHT_VALID_BIT(void)
{
    GH_HDMI_PACKET_MISC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC_RIGHT_VALID_BIT] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return tmp_value.bitc.right_valid_bit;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_SPD_SEND_CTRL(U8 data)
{
    GH_HDMI_PACKET_MISC_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC;
    d.bitc.spd_send_ctrl = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC_SPD_SEND_CTRL] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_SPD_SEND_CTRL(void)
{
    GH_HDMI_PACKET_MISC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC_SPD_SEND_CTRL] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return tmp_value.bitc.spd_send_ctrl;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_CTS_SW_MODE(U8 data)
{
    GH_HDMI_PACKET_MISC_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC;
    d.bitc.cts_sw_mode = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC_CTS_SW_MODE] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_CTS_SW_MODE(void)
{
    GH_HDMI_PACKET_MISC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC_CTS_SW_MODE] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return tmp_value.bitc.cts_sw_mode;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_NCTS_PRIORITY(U8 data)
{
    GH_HDMI_PACKET_MISC_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC;
    d.bitc.ncts_priority = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC_NCTS_PRIORITY] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_NCTS_PRIORITY(void)
{
    GH_HDMI_PACKET_MISC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC_NCTS_PRIORITY] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return tmp_value.bitc.ncts_priority;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_I2S_RX_MODE(U8 data)
{
    GH_HDMI_PACKET_MISC_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC;
    d.bitc.i2s_rx_mode = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_PACKET_MISC_I2S_RX_MODE] <-- 0x%08x\n",
                        REG_HDMI_PACKET_MISC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_I2S_RX_MODE(void)
{
    GH_HDMI_PACKET_MISC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_PACKET_MISC_I2S_RX_MODE] --> 0x%08x\n",
                        REG_HDMI_PACKET_MISC,value);
    #endif
    return tmp_value.bitc.i2s_rx_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VBLANK (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_VBLANK'. */
U32  GH_HDMI_get_VUNIT_VBLANK(void);
/*! \brief Writes the bit group 'VBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(U8 data);
/*! \brief Reads the bit group 'VBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(void);
/*! \brief Writes the bit group 'VBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(U8 data);
/*! \brief Reads the bit group 'VBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_VBLANK'. */
U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(void);
/*! \brief Writes the bit group 'VBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(U8 data);
/*! \brief Reads the bit group 'VBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK(U32 data)
{
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VBLANK] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_VUNIT_VBLANK(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VBLANK] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(U8 data)
{
    GH_HDMI_VUNIT_VBLANK_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VBLANK;
    d.bitc.vblank_right_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(void)
{
    GH_HDMI_VUNIT_VBLANK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,value);
    #endif
    return tmp_value.bitc.vblank_right_offset;
}
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(U8 data)
{
    GH_HDMI_VUNIT_VBLANK_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VBLANK;
    d.bitc.vblank_pulse_width = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VBLANK_VBLANK_PULSE_WIDTH] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(void)
{
    GH_HDMI_VUNIT_VBLANK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VBLANK_VBLANK_PULSE_WIDTH] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,value);
    #endif
    return tmp_value.bitc.vblank_pulse_width;
}
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(U8 data)
{
    GH_HDMI_VUNIT_VBLANK_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VBLANK;
    d.bitc.vblank_left_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VBLANK_VBLANK_LEFT_OFFSET] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(void)
{
    GH_HDMI_VUNIT_VBLANK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VBLANK_VBLANK_LEFT_OFFSET] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VBLANK,value);
    #endif
    return tmp_value.bitc.vblank_left_offset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_HBLANK (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_HBLANK'. */
U32  GH_HDMI_get_VUNIT_HBLANK(void);
/*! \brief Writes the bit group 'HBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(U16 data);
/*! \brief Reads the bit group 'HBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(void);
/*! \brief Writes the bit group 'HBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(U16 data);
/*! \brief Reads the bit group 'HBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_HBLANK'. */
U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(void);
/*! \brief Writes the bit group 'HBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(U16 data);
/*! \brief Reads the bit group 'HBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK(U32 data)
{
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_HBLANK] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_VUNIT_HBLANK(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_HBLANK] --> 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(U16 data)
{
    GH_HDMI_VUNIT_HBLANK_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HBLANK;
    d.bitc.hblank_right_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(void)
{
    GH_HDMI_VUNIT_HBLANK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET] --> 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,value);
    #endif
    return tmp_value.bitc.hblank_right_offset;
}
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(U16 data)
{
    GH_HDMI_VUNIT_HBLANK_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HBLANK;
    d.bitc.hblank_pulse_width = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_HBLANK_HBLANK_PULSE_WIDTH] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(void)
{
    GH_HDMI_VUNIT_HBLANK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_HBLANK_HBLANK_PULSE_WIDTH] --> 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,value);
    #endif
    return tmp_value.bitc.hblank_pulse_width;
}
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(U16 data)
{
    GH_HDMI_VUNIT_HBLANK_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HBLANK;
    d.bitc.hblank_left_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_HBLANK_HBLANK_LEFT_OFFSET] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(void)
{
    GH_HDMI_VUNIT_HBLANK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_HBLANK_HBLANK_LEFT_OFFSET] --> 0x%08x\n",
                        REG_HDMI_VUNIT_HBLANK,value);
    #endif
    return tmp_value.bitc.hblank_left_offset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VACTIVE (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_VUNIT_VACTIVE'. */
void GH_HDMI_set_VUNIT_VACTIVE(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_VACTIVE'. */
U32  GH_HDMI_get_VUNIT_VACTIVE(void);
/*! \brief Writes the bit group 'VUNIT_VACTIVE' of register 'HDMI_VUNIT_VACTIVE'. */
void GH_HDMI_set_VUNIT_VACTIVE_VUNIT_VACTIVE(U16 data);
/*! \brief Reads the bit group 'VUNIT_VACTIVE' of register 'HDMI_VUNIT_VACTIVE'. */
U16  GH_HDMI_get_VUNIT_VACTIVE_VUNIT_VACTIVE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_VUNIT_VACTIVE(U32 data)
{
    *(volatile U32 *)REG_HDMI_VUNIT_VACTIVE = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VACTIVE] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VACTIVE,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_VUNIT_VACTIVE(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VACTIVE);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VACTIVE] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VACTIVE,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_VUNIT_VACTIVE_VUNIT_VACTIVE(U16 data)
{
    GH_HDMI_VUNIT_VACTIVE_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VACTIVE;
    d.bitc.vunit_vactive = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VACTIVE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VACTIVE_VUNIT_VACTIVE] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VACTIVE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_HDMI_get_VUNIT_VACTIVE_VUNIT_VACTIVE(void)
{
    GH_HDMI_VUNIT_VACTIVE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VACTIVE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VACTIVE_VUNIT_VACTIVE] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VACTIVE,value);
    #endif
    return tmp_value.bitc.vunit_vactive;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_HACTIVE (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_VUNIT_HACTIVE'. */
void GH_HDMI_set_VUNIT_HACTIVE(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_HACTIVE'. */
U32  GH_HDMI_get_VUNIT_HACTIVE(void);
/*! \brief Writes the bit group 'VUNIT_HACTIVE' of register 'HDMI_VUNIT_HACTIVE'. */
void GH_HDMI_set_VUNIT_HACTIVE_VUNIT_HACTIVE(U16 data);
/*! \brief Reads the bit group 'VUNIT_HACTIVE' of register 'HDMI_VUNIT_HACTIVE'. */
U16  GH_HDMI_get_VUNIT_HACTIVE_VUNIT_HACTIVE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_VUNIT_HACTIVE(U32 data)
{
    *(volatile U32 *)REG_HDMI_VUNIT_HACTIVE = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_HACTIVE] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_HACTIVE,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_VUNIT_HACTIVE(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HACTIVE);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_HACTIVE] --> 0x%08x\n",
                        REG_HDMI_VUNIT_HACTIVE,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_VUNIT_HACTIVE_VUNIT_HACTIVE(U16 data)
{
    GH_HDMI_VUNIT_HACTIVE_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HACTIVE;
    d.bitc.vunit_hactive = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HACTIVE = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_HACTIVE_VUNIT_HACTIVE] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_HACTIVE,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HACTIVE_VUNIT_HACTIVE(void)
{
    GH_HDMI_VUNIT_HACTIVE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HACTIVE);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_HACTIVE_VUNIT_HACTIVE] --> 0x%08x\n",
                        REG_HDMI_VUNIT_HACTIVE,value);
    #endif
    return tmp_value.bitc.vunit_hactive;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_CTRL'. */
U32  GH_HDMI_get_VUNIT_CTRL(void);
/*! \brief Writes the bit group 'VSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL_VSYNC_POL(U8 data);
/*! \brief Reads the bit group 'VSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
U8   GH_HDMI_get_VUNIT_CTRL_VSYNC_POL(void);
/*! \brief Writes the bit group 'HSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL_HSYNC_POL(U8 data);
/*! \brief Reads the bit group 'HSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
U8   GH_HDMI_get_VUNIT_CTRL_HSYNC_POL(void);
/*! \brief Writes the bit group 'VIDEO_MODE' of register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL_VIDEO_MODE(U8 data);
/*! \brief Reads the bit group 'VIDEO_MODE' of register 'HDMI_VUNIT_CTRL'. */
U8   GH_HDMI_get_VUNIT_CTRL_VIDEO_MODE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_VUNIT_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_CTRL] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_VUNIT_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_CTRL] --> 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_VUNIT_CTRL_VSYNC_POL(U8 data)
{
    GH_HDMI_VUNIT_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_CTRL;
    d.bitc.vsync_pol = data;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_CTRL_VSYNC_POL] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_CTRL_VSYNC_POL(void)
{
    GH_HDMI_VUNIT_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_CTRL_VSYNC_POL] --> 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,value);
    #endif
    return tmp_value.bitc.vsync_pol;
}
GH_INLINE void GH_HDMI_set_VUNIT_CTRL_HSYNC_POL(U8 data)
{
    GH_HDMI_VUNIT_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_CTRL;
    d.bitc.hsync_pol = data;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_CTRL_HSYNC_POL] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_CTRL_HSYNC_POL(void)
{
    GH_HDMI_VUNIT_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_CTRL_HSYNC_POL] --> 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,value);
    #endif
    return tmp_value.bitc.hsync_pol;
}
GH_INLINE void GH_HDMI_set_VUNIT_CTRL_VIDEO_MODE(U8 data)
{
    GH_HDMI_VUNIT_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_CTRL;
    d.bitc.video_mode = data;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_CTRL_VIDEO_MODE] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_CTRL_VIDEO_MODE(void)
{
    GH_HDMI_VUNIT_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_CTRL_VIDEO_MODE] --> 0x%08x\n",
                        REG_HDMI_VUNIT_CTRL,value);
    #endif
    return tmp_value.bitc.video_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VSYNC_DETECT (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_VUNIT_VSYNC_DETECT'. */
void GH_HDMI_set_VUNIT_VSYNC_DETECT(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_VSYNC_DETECT'. */
U32  GH_HDMI_get_VUNIT_VSYNC_DETECT(void);
/*! \brief Writes the bit group 'VSYNC_DETECT_EN' of register 'HDMI_VUNIT_VSYNC_DETECT'. */
void GH_HDMI_set_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(U8 data);
/*! \brief Reads the bit group 'VSYNC_DETECT_EN' of register 'HDMI_VUNIT_VSYNC_DETECT'. */
U8   GH_HDMI_get_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_VUNIT_VSYNC_DETECT(U32 data)
{
    *(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VSYNC_DETECT] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VSYNC_DETECT,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_VUNIT_VSYNC_DETECT(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VSYNC_DETECT] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VSYNC_DETECT,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(U8 data)
{
    GH_HDMI_VUNIT_VSYNC_DETECT_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT;
    d.bitc.vsync_detect_en = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN] <-- 0x%08x\n",
                        REG_HDMI_VUNIT_VSYNC_DETECT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(void)
{
    GH_HDMI_VUNIT_VSYNC_DETECT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN] --> 0x%08x\n",
                        REG_HDMI_VUNIT_VSYNC_DETECT,value);
    #endif
    return tmp_value.bitc.vsync_detect_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_TM (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM(U32 data);
/*! \brief Reads the register 'HDMI_HDMISE_TM'. */
U32  GH_HDMI_get_HDMISE_TM(void);
/*! \brief Writes the bit group 'I2S_DOUT_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_I2S_DOUT_MODE(U8 data);
/*! \brief Reads the bit group 'I2S_DOUT_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_I2S_DOUT_MODE(void);
/*! \brief Writes the bit group 'VDATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_VDATA_SRC_MODE(U8 data);
/*! \brief Reads the bit group 'VDATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_VDATA_SRC_MODE(void);
/*! \brief Writes the bit group 'VIDEO_PATTERN_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_VIDEO_PATTERN_MODE(U8 data);
/*! \brief Reads the bit group 'VIDEO_PATTERN_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_VIDEO_PATTERN_MODE(void);
/*! \brief Writes the bit group 'ADATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_ADATA_SRC_MODE(U8 data);
/*! \brief Reads the bit group 'ADATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_ADATA_SRC_MODE(void);
/*! \brief Writes the bit group 'BG_B' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_BG_B(U8 data);
/*! \brief Reads the bit group 'BG_B' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_BG_B(void);
/*! \brief Writes the bit group 'BG_G' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_BG_G(U8 data);
/*! \brief Reads the bit group 'BG_G' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_BG_G(void);
/*! \brief Writes the bit group 'BG_R' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_BG_R(U8 data);
/*! \brief Reads the bit group 'BG_R' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_BG_R(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_HDMISE_TM(U32 data)
{
    *(volatile U32 *)REG_HDMI_HDMISE_TM = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_HDMISE_TM(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_I2S_DOUT_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.i2s_dout_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_I2S_DOUT_MODE] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_I2S_DOUT_MODE(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_I2S_DOUT_MODE] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.i2s_dout_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_VDATA_SRC_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.vdata_src_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_VDATA_SRC_MODE] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_VDATA_SRC_MODE(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_VDATA_SRC_MODE] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.vdata_src_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_VIDEO_PATTERN_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.video_pattern_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_VIDEO_PATTERN_MODE] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_VIDEO_PATTERN_MODE(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_VIDEO_PATTERN_MODE] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.video_pattern_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_ADATA_SRC_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.adata_src_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_ADATA_SRC_MODE] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_ADATA_SRC_MODE(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_ADATA_SRC_MODE] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.adata_src_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_BG_B(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.bg_b = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_BG_B] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_BG_B(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_BG_B] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.bg_b;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_BG_G(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.bg_g = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_BG_G] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_BG_G(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_BG_G] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.bg_g;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_BG_R(U8 data)
{
    GH_HDMI_HDMISE_TM_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM;
    d.bitc.bg_r = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_TM_BG_R] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_TM,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_BG_R(void)
{
    GH_HDMI_HDMISE_TM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_TM_BG_R] --> 0x%08x\n",
                        REG_HDMI_HDMISE_TM,value);
    #endif
    return tmp_value.bitc.bg_r;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_P2P_AFIFO_LEVEL (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL(U32 data);
/*! \brief Reads the register 'HDMI_P2P_AFIFO_LEVEL'. */
U32  GH_HDMI_get_P2P_AFIFO_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_MIN_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_MIN_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_MAX_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_MAX_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_LB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_LB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(void);
/*! \brief Writes the bit group 'P2P_AFIFO_UB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_UB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL(U32 data)
{
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_LEVEL] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_P2P_AFIFO_LEVEL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_LEVEL] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL;
    d.bitc.p2p_afifo_level = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,value);
    #endif
    return tmp_value.bitc.p2p_afifo_level;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL;
    d.bitc.p2p_afifo_min_level = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,value);
    #endif
    return tmp_value.bitc.p2p_afifo_min_level;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL;
    d.bitc.p2p_afifo_max_level = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,value);
    #endif
    return tmp_value.bitc.p2p_afifo_max_level;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL;
    d.bitc.p2p_afifo_lb = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LB] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LB] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,value);
    #endif
    return tmp_value.bitc.p2p_afifo_lb;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL;
    d.bitc.p2p_afifo_ub = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_UB] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_UB] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_LEVEL,value);
    #endif
    return tmp_value.bitc.p2p_afifo_ub;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_P2P_AFIFO_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_P2P_AFIFO_CTRL'. */
void GH_HDMI_set_P2P_AFIFO_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_P2P_AFIFO_CTRL'. */
U32  GH_HDMI_get_P2P_AFIFO_CTRL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_EN' of register 'HDMI_P2P_AFIFO_CTRL'. */
void GH_HDMI_set_P2P_AFIFO_CTRL_P2P_AFIFO_EN(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_EN' of register 'HDMI_P2P_AFIFO_CTRL'. */
U8   GH_HDMI_get_P2P_AFIFO_CTRL_P2P_AFIFO_EN(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_P2P_AFIFO_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_CTRL] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_P2P_AFIFO_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_CTRL] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_CTRL_P2P_AFIFO_EN(U8 data)
{
    GH_HDMI_P2P_AFIFO_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL;
    d.bitc.p2p_afifo_en = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_P2P_AFIFO_CTRL_P2P_AFIFO_EN] <-- 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_CTRL_P2P_AFIFO_EN(void)
{
    GH_HDMI_P2P_AFIFO_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_P2P_AFIFO_CTRL_P2P_AFIFO_EN] --> 0x%08x\n",
                        REG_HDMI_P2P_AFIFO_CTRL,value);
    #endif
    return tmp_value.bitc.p2p_afifo_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_DBG (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG(U32 data);
/*! \brief Reads the register 'HDMI_HDMISE_DBG'. */
U32  GH_HDMI_get_HDMISE_DBG(void);
/*! \brief Writes the bit group 'DBG_P2P_AFIFO_BYPASS' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(U8 data);
/*! \brief Reads the bit group 'DBG_P2P_AFIFO_BYPASS' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(void);
/*! \brief Writes the bit group 'DBG_VDATA_SRC_MODE' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_VDATA_SRC_MODE(U8 data);
/*! \brief Reads the bit group 'DBG_VDATA_SRC_MODE' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_VDATA_SRC_MODE(void);
/*! \brief Writes the bit group 'DBG_CH_B_REV' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_B_REV(U8 data);
/*! \brief Reads the bit group 'DBG_CH_B_REV' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_B_REV(void);
/*! \brief Writes the bit group 'DBG_CH_G_REV' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_G_REV(U8 data);
/*! \brief Reads the bit group 'DBG_CH_G_REV' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_G_REV(void);
/*! \brief Writes the bit group 'DBG_CH_R_REV' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_R_REV(U8 data);
/*! \brief Reads the bit group 'DBG_CH_R_REV' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_R_REV(void);
/*! \brief Writes the bit group 'DBG_CH_SWP' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_SWP(U8 data);
/*! \brief Reads the bit group 'DBG_CH_SWP' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_SWP(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_HDMISE_DBG(U32 data)
{
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_HDMISE_DBG(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(U8 data)
{
    GH_HDMI_HDMISE_DBG_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG;
    d.bitc.dbg_p2p_afifo_bypass = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(void)
{
    GH_HDMI_HDMISE_DBG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return tmp_value.bitc.dbg_p2p_afifo_bypass;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_VDATA_SRC_MODE(U8 data)
{
    GH_HDMI_HDMISE_DBG_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG;
    d.bitc.dbg_vdata_src_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG_DBG_VDATA_SRC_MODE] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_VDATA_SRC_MODE(void)
{
    GH_HDMI_HDMISE_DBG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG_DBG_VDATA_SRC_MODE] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return tmp_value.bitc.dbg_vdata_src_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_B_REV(U8 data)
{
    GH_HDMI_HDMISE_DBG_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG;
    d.bitc.dbg_ch_b_rev = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG_DBG_CH_B_REV] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_B_REV(void)
{
    GH_HDMI_HDMISE_DBG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG_DBG_CH_B_REV] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return tmp_value.bitc.dbg_ch_b_rev;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_G_REV(U8 data)
{
    GH_HDMI_HDMISE_DBG_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG;
    d.bitc.dbg_ch_g_rev = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG_DBG_CH_G_REV] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_G_REV(void)
{
    GH_HDMI_HDMISE_DBG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG_DBG_CH_G_REV] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return tmp_value.bitc.dbg_ch_g_rev;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_R_REV(U8 data)
{
    GH_HDMI_HDMISE_DBG_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG;
    d.bitc.dbg_ch_r_rev = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG_DBG_CH_R_REV] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_R_REV(void)
{
    GH_HDMI_HDMISE_DBG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG_DBG_CH_R_REV] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return tmp_value.bitc.dbg_ch_r_rev;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_SWP(U8 data)
{
    GH_HDMI_HDMISE_DBG_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG;
    d.bitc.dbg_ch_swp = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMISE_DBG_DBG_CH_SWP] <-- 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_SWP(void)
{
    GH_HDMI_HDMISE_DBG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMISE_DBG_DBG_CH_SWP] --> 0x%08x\n",
                        REG_HDMI_HDMISE_DBG,value);
    #endif
    return tmp_value.bitc.dbg_ch_swp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMI_PHY_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_HDMI_PHY_CTRL'. */
U32  GH_HDMI_get_HDMI_PHY_CTRL(void);
/*! \brief Writes the bit group 'RSTND_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_RSTND_HDMI(U8 data);
/*! \brief Reads the bit group 'RSTND_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_RSTND_HDMI(void);
/*! \brief Writes the bit group 'PIB' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PIB(U8 data);
/*! \brief Reads the bit group 'PIB' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PIB(void);
/*! \brief Writes the bit group 'PES' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PES(U8 data);
/*! \brief Reads the bit group 'PES' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PES(void);
/*! \brief Writes the bit group 'PDB_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PDB_HDMI(U8 data);
/*! \brief Reads the bit group 'PDB_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PDB_HDMI(void);
/*! \brief Writes the bit group 'PD_BG' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PD_BG(U8 data);
/*! \brief Reads the bit group 'PD_BG' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PD_BG(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL(U32 data)
{
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL = data;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMI_PHY_CTRL] <-- 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,data,data);
    #endif
}
GH_INLINE U32  GH_HDMI_get_HDMI_PHY_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL);

    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMI_PHY_CTRL] --> 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_RSTND_HDMI(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL;
    d.bitc.rstnd_hdmi = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMI_PHY_CTRL_RSTND_HDMI] <-- 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_RSTND_HDMI(void)
{
    GH_HDMI_HDMI_PHY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMI_PHY_CTRL_RSTND_HDMI] --> 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,value);
    #endif
    return tmp_value.bitc.rstnd_hdmi;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PIB(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL;
    d.bitc.pib = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMI_PHY_CTRL_PIB] <-- 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PIB(void)
{
    GH_HDMI_HDMI_PHY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMI_PHY_CTRL_PIB] --> 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,value);
    #endif
    return tmp_value.bitc.pib;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PES(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL;
    d.bitc.pes = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMI_PHY_CTRL_PES] <-- 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PES(void)
{
    GH_HDMI_HDMI_PHY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMI_PHY_CTRL_PES] --> 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,value);
    #endif
    return tmp_value.bitc.pes;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PDB_HDMI(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL;
    d.bitc.pdb_hdmi = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMI_PHY_CTRL_PDB_HDMI] <-- 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PDB_HDMI(void)
{
    GH_HDMI_HDMI_PHY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMI_PHY_CTRL_PDB_HDMI] --> 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,value);
    #endif
    return tmp_value.bitc.pdb_hdmi;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PD_BG(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL;
    d.bitc.pd_bg = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL = d.all;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_HDMI_set_HDMI_PHY_CTRL_PD_BG] <-- 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PD_BG(void)
{
    GH_HDMI_HDMI_PHY_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL);

    tmp_value.all = value;
    #if GH_HDMI_ENABLE_DEBUG_PRINT
    GH_HDMI_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_HDMI_get_HDMI_PHY_CTRL_PD_BG] --> 0x%08x\n",
                        REG_HDMI_HDMI_PHY_CTRL,value);
    #endif
    return tmp_value.bitc.pd_bg;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_HDMI_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_HDMI_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

