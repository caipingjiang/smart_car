/*!
*******************************************************************************
**
** \file      gh_vo_display0.h
**
** \brief     VO Display A access function.
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
#ifndef _GH_VO_DISPLAY0_H
#define _GH_VO_DISPLAY0_H

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

#define GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
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
#define REG_VO_DISPLAY0_CONTROL                             FIO_ADDRESS(VO_DISPLAY0,0x90004300) /* read/write */
#define REG_VO_DISPLAY0_STATUS                              FIO_ADDRESS(VO_DISPLAY0,0x90004304) /* read/write */
#define REG_VO_DISPLAY0_FRAME_SIZE_FIELD0                   FIO_ADDRESS(VO_DISPLAY0,0x90004308) /* read/write */
#define REG_VO_DISPLAY0_FRAME_SIZE_FIELD1                   FIO_ADDRESS(VO_DISPLAY0,0x9000430C) /* read/write */
#define REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0          FIO_ADDRESS(VO_DISPLAY0,0x90004310) /* read/write */
#define REG_VO_DISPLAY0_ACTIVE_REGION_END_0                 FIO_ADDRESS(VO_DISPLAY0,0x90004314) /* read/write */
#define REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1          FIO_ADDRESS(VO_DISPLAY0,0x90004318) /* read/write */
#define REG_VO_DISPLAY0_ACTIVE_REGION_END_1                 FIO_ADDRESS(VO_DISPLAY0,0x9000431C) /* read/write */
#define REG_VO_DISPLAY0_BACKGROUND                          FIO_ADDRESS(VO_DISPLAY0,0x90004320) /* write */
#define REG_VO_DISPLAY0_DIGITAL_OUTPUT                      FIO_ADDRESS(VO_DISPLAY0,0x90004324) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL               FIO_ADDRESS(VO_DISPLAY0,0x90004328) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0               FIO_ADDRESS(VO_DISPLAY0,0x9000432C) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0                 FIO_ADDRESS(VO_DISPLAY0,0x90004330) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1               FIO_ADDRESS(VO_DISPLAY0,0x90004334) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1                 FIO_ADDRESS(VO_DISPLAY0,0x90004338) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_656_VBIT                    FIO_ADDRESS(VO_DISPLAY0,0x9000433C) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_656_SAV_START               FIO_ADDRESS(VO_DISPLAY0,0x90004340) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0              FIO_ADDRESS(VO_DISPLAY0,0x90004344) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1              FIO_ADDRESS(VO_DISPLAY0,0x90004348) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2              FIO_ADDRESS(VO_DISPLAY0,0x9000434C) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3              FIO_ADDRESS(VO_DISPLAY0,0x90004350) /* read/write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0                 FIO_ADDRESS(VO_DISPLAY0,0x90004354) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1                 FIO_ADDRESS(VO_DISPLAY0,0x90004358) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2                 FIO_ADDRESS(VO_DISPLAY0,0x9000435C) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3                 FIO_ADDRESS(VO_DISPLAY0,0x90004360) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4                 FIO_ADDRESS(VO_DISPLAY0,0x90004364) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5                 FIO_ADDRESS(VO_DISPLAY0,0x90004368) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6                 FIO_ADDRESS(VO_DISPLAY0,0x9000436C) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7                 FIO_ADDRESS(VO_DISPLAY0,0x90004370) /* write */
#define REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8                 FIO_ADDRESS(VO_DISPLAY0,0x90004374) /* write */
#define REG_VO_DISPLAY0_VOUT_VOUT_SYNC                      FIO_ADDRESS(VO_DISPLAY0,0x9000445C) /* read/write */
#define REG_VO_DISPLAY0_INPUT_STREAM_ENABLES                FIO_ADDRESS(VO_DISPLAY0,0x90004460) /* read/write */
#define REG_VO_DISPLAY0_INPUT_SYNC_CONTROL                  FIO_ADDRESS(VO_DISPLAY0,0x90004464) /* read/write */
#define REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL                 FIO_ADDRESS(VO_DISPLAY0,0x90004468) /* read/write */
#define REG_VO_DISPLAY0_STREAM_CONTROL                      FIO_ADDRESS(VO_DISPLAY0,0x9000446C) /* read/write */
#define REG_VO_DISPLAY0_FRAME_ENABLE                        FIO_ADDRESS(VO_DISPLAY0,0x90004470) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DISPLAY0_CONTROL */
    U32 all;
    struct {
        U32 fixed_format                : 5;
        U32 interlace_enable            : 1;
        U32 reverse_mode_enable         : 1;
        U32                             : 18;
        U32 vout_vout_sync_enable       : 1;
        U32 vin_vout_sync_enable        : 1;
        U32 digital_output_enable       : 1;
        U32 i80_output_enable           : 1;
        U32                             : 2;
        U32 reset                       : 1;
    } bitc;
} GH_VO_DISPLAY0_CONTROL_S;

typedef union { /* VO_DISPLAY0_STATUS */
    U32 all;
    struct {
        U32 hdmi_field                  : 1;
        U32 analog_fied                 : 1;
        U32 digital_field               : 1;
        U32                             : 24;
        U32 hdmi_underflow              : 1;
        U32 analog_underflow            : 1;
        U32 digital_underflow           : 1;
        U32 sdtv_configuration_ready    : 1;
        U32 reset                       : 1;
    } bitc;
} GH_VO_DISPLAY0_STATUS_S;

typedef union { /* VO_DISPLAY0_FRAME_SIZE_FIELD0 */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 2;
        U32 width                       : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S;

typedef union { /* VO_DISPLAY0_FRAME_SIZE_FIELD1 */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 18;
    } bitc;
} GH_VO_DISPLAY0_FRAME_SIZE_FIELD1_S;

typedef union { /* VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S;

typedef union { /* VO_DISPLAY0_ACTIVE_REGION_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S;

typedef union { /* VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S;

typedef union { /* VO_DISPLAY0_ACTIVE_REGION_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S;

typedef union { /* VO_DISPLAY0_BACKGROUND */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32                             : 8;
    } bitc;
} GH_VO_DISPLAY0_BACKGROUND_S;

typedef union { /* VO_DISPLAY0_DIGITAL_OUTPUT */
    U32 all;
    struct {
        U32 digital_hsync_polarity      : 1;
        U32 digital_vsync_polarity      : 1;
        U32 digital_clock_output_divider: 1;
        U32 digital_clock_divider_enable: 1;
        U32 digital_clock_edge          : 1;
        U32 digital_clock_disable       : 1;
        U32 digital_clock_divider_pattern_width: 7;
        U32 mipi_configuration          : 6;
        U32                             : 2;
        U32 color_sequence_even_lines   : 3;
        U32 color_sequence_odd_lines    : 3;
        U32 mode                        : 5;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_OUTPUT_S;

typedef union { /* VO_DISPLAY0_DIGITAL_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S;

typedef union { /* VO_DISPLAY0_DIGITAL_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S;

typedef union { /* VO_DISPLAY0_DIGITAL_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S;

typedef union { /* VO_DISPLAY0_DIGITAL_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S;

typedef union { /* VO_DISPLAY0_DIGITAL_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S;

typedef union { /* VO_DISPLAY0_DIGITAL_656_VBIT */
    U32 all;
    struct {
        U32 end_row                     : 14;
        U32                             : 2;
        U32 start_row                   : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_656_VBIT_S;

typedef union { /* VO_DISPLAY0_DIGITAL_656_SAV_START */
    U32 all;
    struct {
        U32 code_location               : 14;
        U32                             : 18;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_656_SAV_START_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_0_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_1_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_2_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_3_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_4_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_5_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_6 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_6_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_7 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_7_S;

typedef union { /* VO_DISPLAY0_DIGITAL_CSC_PARAM_8 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_8_S;

typedef union { /* VO_DISPLAY0_VOUT_VOUT_SYNC */
    U32 all;
    struct {
        U32 start_row                   : 14;
        U32                             : 2;
        U32 field_select                : 1;
        U32                             : 15;
    } bitc;
} GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_VO_DISPLAY0_BACKGROUND_S             m_vo_display0_background;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_0_S    m_vo_display0_digital_csc_param_0;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_1_S    m_vo_display0_digital_csc_param_1;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_2_S    m_vo_display0_digital_csc_param_2;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_3_S    m_vo_display0_digital_csc_param_3;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_4_S    m_vo_display0_digital_csc_param_4;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_5_S    m_vo_display0_digital_csc_param_5;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_6_S    m_vo_display0_digital_csc_param_6;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_7_S    m_vo_display0_digital_csc_param_7;
extern GH_VO_DISPLAY0_DIGITAL_CSC_PARAM_8_S    m_vo_display0_digital_csc_param_8;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_CONTROL (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_CONTROL'. */
U32  GH_VO_DISPLAY0_get_CONTROL(void);
/*! \brief Writes the bit group 'Fixed_Format' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_Fixed_Format(U8 data);
/*! \brief Reads the bit group 'Fixed_Format' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_Fixed_Format(void);
/*! \brief Writes the bit group 'Interlace_Enable' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_Interlace_Enable(U8 data);
/*! \brief Reads the bit group 'Interlace_Enable' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_Interlace_Enable(void);
/*! \brief Writes the bit group 'Reverse_Mode_Enable' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_Reverse_Mode_Enable(U8 data);
/*! \brief Reads the bit group 'Reverse_Mode_Enable' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_Reverse_Mode_Enable(void);
/*! \brief Writes the bit group 'VOUT_VOUT_Sync_Enable' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_VOUT_VOUT_Sync_Enable(U8 data);
/*! \brief Reads the bit group 'VOUT_VOUT_Sync_Enable' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_VOUT_VOUT_Sync_Enable(void);
/*! \brief Writes the bit group 'VIN_VOUT_Sync_Enable' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_VIN_VOUT_Sync_Enable(U8 data);
/*! \brief Reads the bit group 'VIN_VOUT_Sync_Enable' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_VIN_VOUT_Sync_Enable(void);
/*! \brief Writes the bit group 'Digital_Output_Enable' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_Digital_Output_Enable(U8 data);
/*! \brief Reads the bit group 'Digital_Output_Enable' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_Digital_Output_Enable(void);
/*! \brief Writes the bit group 'I80_Output_Enable' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_I80_Output_Enable(U8 data);
/*! \brief Reads the bit group 'I80_Output_Enable' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_I80_Output_Enable(void);
/*! \brief Writes the bit group 'Reset' of register 'VO_DISPLAY0_CONTROL'. */
void GH_VO_DISPLAY0_set_CONTROL_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' of register 'VO_DISPLAY0_CONTROL'. */
U8   GH_VO_DISPLAY0_get_CONTROL_Reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_Fixed_Format(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.fixed_format = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Fixed_Format] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_Fixed_Format(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Fixed_Format] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.fixed_format;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_Interlace_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.interlace_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Interlace_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_Interlace_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Interlace_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.interlace_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_Reverse_Mode_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.reverse_mode_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Reverse_Mode_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_Reverse_Mode_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Reverse_Mode_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.reverse_mode_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_VOUT_VOUT_Sync_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.vout_vout_sync_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_VOUT_VOUT_Sync_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_VOUT_VOUT_Sync_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_VOUT_VOUT_Sync_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.vout_vout_sync_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_VIN_VOUT_Sync_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.vin_vout_sync_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_VIN_VOUT_Sync_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_VIN_VOUT_Sync_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_VIN_VOUT_Sync_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.vin_vout_sync_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_Digital_Output_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.digital_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Digital_Output_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_Digital_Output_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Digital_Output_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.digital_output_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_I80_Output_Enable(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.i80_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_I80_Output_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_I80_Output_Enable(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_I80_Output_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.i80_output_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_CONTROL_Reset(U8 data)
{
    GH_VO_DISPLAY0_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_CONTROL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_DISPLAY0_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_CONTROL_Reset] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_CONTROL_Reset(void)
{
    GH_VO_DISPLAY0_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_CONTROL_Reset] --> 0x%08x\n",
                        REG_VO_DISPLAY0_CONTROL,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_STATUS (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_STATUS'. */
U32  GH_VO_DISPLAY0_get_STATUS(void);
/*! \brief Writes the bit group 'HDMI_Field' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_HDMI_Field(U8 data);
/*! \brief Reads the bit group 'HDMI_Field' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_HDMI_Field(void);
/*! \brief Writes the bit group 'Analog_Fied' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_Analog_Fied(U8 data);
/*! \brief Reads the bit group 'Analog_Fied' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_Analog_Fied(void);
/*! \brief Writes the bit group 'Digital_Field' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_Digital_Field(U8 data);
/*! \brief Reads the bit group 'Digital_Field' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_Digital_Field(void);
/*! \brief Writes the bit group 'HDMI_Underflow' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_HDMI_Underflow(U8 data);
/*! \brief Reads the bit group 'HDMI_Underflow' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_HDMI_Underflow(void);
/*! \brief Writes the bit group 'Analog_Underflow' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_Analog_Underflow(U8 data);
/*! \brief Reads the bit group 'Analog_Underflow' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_Analog_Underflow(void);
/*! \brief Writes the bit group 'Digital_Underflow' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_Digital_Underflow(U8 data);
/*! \brief Reads the bit group 'Digital_Underflow' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_Digital_Underflow(void);
/*! \brief Writes the bit group 'SDTV_Configuration_Ready' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_SDTV_Configuration_Ready(U8 data);
/*! \brief Reads the bit group 'SDTV_Configuration_Ready' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_SDTV_Configuration_Ready(void);
/*! \brief Writes the bit group 'Reset' of register 'VO_DISPLAY0_STATUS'. */
void GH_VO_DISPLAY0_set_STATUS_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' of register 'VO_DISPLAY0_STATUS'. */
U8   GH_VO_DISPLAY0_get_STATUS_Reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_STATUS(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_HDMI_Field(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.hdmi_field = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_HDMI_Field] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_HDMI_Field(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_HDMI_Field] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.hdmi_field;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_Analog_Fied(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.analog_fied = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Analog_Fied] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_Analog_Fied(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Analog_Fied] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.analog_fied;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_Digital_Field(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.digital_field = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Digital_Field] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_Digital_Field(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Digital_Field] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.digital_field;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_HDMI_Underflow(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.hdmi_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_HDMI_Underflow] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_HDMI_Underflow(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_HDMI_Underflow] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.hdmi_underflow;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_Analog_Underflow(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.analog_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Analog_Underflow] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_Analog_Underflow(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Analog_Underflow] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.analog_underflow;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_Digital_Underflow(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.digital_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Digital_Underflow] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_Digital_Underflow(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Digital_Underflow] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.digital_underflow;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_SDTV_Configuration_Ready(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.sdtv_configuration_ready = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_SDTV_Configuration_Ready] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_SDTV_Configuration_Ready(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_SDTV_Configuration_Ready] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.sdtv_configuration_ready;
}
GH_INLINE void GH_VO_DISPLAY0_set_STATUS_Reset(U8 data)
{
    GH_VO_DISPLAY0_STATUS_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_STATUS;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_DISPLAY0_STATUS = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STATUS_Reset] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_STATUS_Reset(void)
{
    GH_VO_DISPLAY0_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STATUS);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STATUS_Reset] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STATUS,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_FRAME_SIZE_FIELD0 (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_FRAME_SIZE_FIELD0'. */
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_FRAME_SIZE_FIELD0'. */
U32  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0(void);
/*! \brief Writes the bit group 'Height' of register 'VO_DISPLAY0_FRAME_SIZE_FIELD0'. */
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Height(U16 data);
/*! \brief Reads the bit group 'Height' of register 'VO_DISPLAY0_FRAME_SIZE_FIELD0'. */
U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Height(void);
/*! \brief Writes the bit group 'Width' of register 'VO_DISPLAY0_FRAME_SIZE_FIELD0'. */
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Width(U16 data);
/*! \brief Reads the bit group 'Width' of register 'VO_DISPLAY0_FRAME_SIZE_FIELD0'. */
U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Width(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Height(U16 data)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Height] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Height(void)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Height] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,value);
    #endif
    return tmp_value.bitc.height;
}
GH_INLINE void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Width(U16 data)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0;
    d.bitc.width = data;
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD0_Width] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Width(void)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD0_Width] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD0,value);
    #endif
    return tmp_value.bitc.width;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_FRAME_SIZE_FIELD1 (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_FRAME_SIZE_FIELD1'. */
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_FRAME_SIZE_FIELD1'. */
U32  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1(void);
/*! \brief Writes the bit group 'Height' of register 'VO_DISPLAY0_FRAME_SIZE_FIELD1'. */
void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1_Height(U16 data);
/*! \brief Reads the bit group 'Height' of register 'VO_DISPLAY0_FRAME_SIZE_FIELD1'. */
U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1_Height(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1_Height(U16 data)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_SIZE_FIELD1_Height] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1_Height(void)
{
    GH_VO_DISPLAY0_FRAME_SIZE_FIELD1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_SIZE_FIELD1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_SIZE_FIELD1_Height] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_SIZE_FIELD1,value);
    #endif
    return tmp_value.bitc.height;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD0'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD0'. */
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD0'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD0'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD0'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD0'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_END_0 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_ACTIVE_REGION_END_0'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_ACTIVE_REGION_END_0'. */
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_END_0'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_END_0'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_END_0'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_END_0'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD1'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD1'. */
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD1'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD1'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD1'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_START_FIELD1'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_START_FIELD1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_START_FIELD1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_START_FIELD1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_ACTIVE_REGION_END_1 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_ACTIVE_REGION_END_1'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_ACTIVE_REGION_END_1'. */
U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_END_1'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_ACTIVE_REGION_END_1'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_END_1'. */
void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_ACTIVE_REGION_END_1'. */
U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_row(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_row(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_column(U16 data)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_ACTIVE_REGION_END_1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_column(void)
{
    GH_VO_DISPLAY0_ACTIVE_REGION_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_ACTIVE_REGION_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_ACTIVE_REGION_END_1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_ACTIVE_REGION_END_1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_BACKGROUND (write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_BACKGROUND'. */
void GH_VO_DISPLAY0_set_BACKGROUND(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_BACKGROUND'. */
U32  GH_VO_DISPLAY0_getm_BACKGROUND(void);
/*! \brief Writes the bit group 'v' of register 'VO_DISPLAY0_BACKGROUND'. */
void GH_VO_DISPLAY0_set_BACKGROUND_v(U8 data);
/*! \brief Reads the bit group 'v' from the mirror variable of register 'VO_DISPLAY0_BACKGROUND'. */
U8   GH_VO_DISPLAY0_getm_BACKGROUND_v(void);
/*! \brief Writes the bit group 'u' of register 'VO_DISPLAY0_BACKGROUND'. */
void GH_VO_DISPLAY0_set_BACKGROUND_u(U8 data);
/*! \brief Reads the bit group 'u' from the mirror variable of register 'VO_DISPLAY0_BACKGROUND'. */
U8   GH_VO_DISPLAY0_getm_BACKGROUND_u(void);
/*! \brief Writes the bit group 'y' of register 'VO_DISPLAY0_BACKGROUND'. */
void GH_VO_DISPLAY0_set_BACKGROUND_y(U8 data);
/*! \brief Reads the bit group 'y' from the mirror variable of register 'VO_DISPLAY0_BACKGROUND'. */
U8   GH_VO_DISPLAY0_getm_BACKGROUND_y(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_BACKGROUND(U32 data)
{
    m_vo_display0_background.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_BACKGROUND(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND] --> 0x%08x\n",
                        m_vo_display0_background.all);
    #endif
    return m_vo_display0_background.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_BACKGROUND_v(U8 data)
{
    m_vo_display0_background.bitc.v = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = m_vo_display0_background.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND_v] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,m_vo_display0_background.all,m_vo_display0_background.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_getm_BACKGROUND_v(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND_v] --> 0x%08x\n",
                        m_vo_display0_background.bitc.v);
    #endif
    return m_vo_display0_background.bitc.v;
}
GH_INLINE void GH_VO_DISPLAY0_set_BACKGROUND_u(U8 data)
{
    m_vo_display0_background.bitc.u = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = m_vo_display0_background.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND_u] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,m_vo_display0_background.all,m_vo_display0_background.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_getm_BACKGROUND_u(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND_u] --> 0x%08x\n",
                        m_vo_display0_background.bitc.u);
    #endif
    return m_vo_display0_background.bitc.u;
}
GH_INLINE void GH_VO_DISPLAY0_set_BACKGROUND_y(U8 data)
{
    m_vo_display0_background.bitc.y = data;
    *(volatile U32 *)REG_VO_DISPLAY0_BACKGROUND = m_vo_display0_background.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_BACKGROUND_y] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_BACKGROUND,m_vo_display0_background.all,m_vo_display0_background.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_getm_BACKGROUND_y(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_BACKGROUND_y] --> 0x%08x\n",
                        m_vo_display0_background.bitc.y);
    #endif
    return m_vo_display0_background.bitc.y;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_OUTPUT (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_OUTPUT(void);
/*! \brief Writes the bit group 'Digital_Hsync_Polarity' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Digital_Hsync_Polarity' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity(void);
/*! \brief Writes the bit group 'Digital_Vsync_Polarity' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Digital_Vsync_Polarity' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity(void);
/*! \brief Writes the bit group 'Digital_Clock_Output_Divider' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Output_Divider' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(void);
/*! \brief Writes the bit group 'Digital_Clock_Divider_Enable' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Divider_Enable' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(void);
/*! \brief Writes the bit group 'Digital_Clock_Edge' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Edge(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Edge' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Edge(void);
/*! \brief Writes the bit group 'Digital_Clock_Disable' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Disable(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Disable' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Disable(void);
/*! \brief Writes the bit group 'Digital_Clock_Divider_Pattern_Width' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Divider_Pattern_Width' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(void);
/*! \brief Writes the bit group 'MIPI_Configuration' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_MIPI_Configuration(U8 data);
/*! \brief Reads the bit group 'MIPI_Configuration' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_MIPI_Configuration(void);
/*! \brief Writes the bit group 'Color_Sequence_Even_Lines' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(U8 data);
/*! \brief Reads the bit group 'Color_Sequence_Even_Lines' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(void);
/*! \brief Writes the bit group 'Color_Sequence_Odd_Lines' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(U8 data);
/*! \brief Reads the bit group 'Color_Sequence_Odd_Lines' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(void);
/*! \brief Writes the bit group 'Mode' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'VO_DISPLAY0_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_OUTPUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_hsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_hsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_vsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_vsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_output_divider = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_output_divider;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_divider_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_divider_enable;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Edge(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_edge = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Edge] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Edge(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Edge] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_edge;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Disable(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_disable = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Disable] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Disable(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Disable] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_disable;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.digital_clock_divider_pattern_width = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.digital_clock_divider_pattern_width;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_MIPI_Configuration(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.mipi_configuration = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_MIPI_Configuration] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_MIPI_Configuration(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_MIPI_Configuration] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.mipi_configuration;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.color_sequence_even_lines = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.color_sequence_even_lines;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.color_sequence_odd_lines = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.color_sequence_odd_lines;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Mode(U8 data)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_OUTPUT_Mode] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Mode(void)
{
    GH_VO_DISPLAY0_DIGITAL_OUTPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_OUTPUT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_OUTPUT_Mode] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_OUTPUT,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_HSYNC_CONTROL (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_HSYNC_CONTROL'. */
void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_HSYNC_CONTROL'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL(void);
/*! \brief Writes the bit group 'end_column' of register 'VO_DISPLAY0_DIGITAL_HSYNC_CONTROL'. */
void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_end_column(U16 data);
/*! \brief Reads the bit group 'end_column' of register 'VO_DISPLAY0_DIGITAL_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_end_column(void);
/*! \brief Writes the bit group 'start_column' of register 'VO_DISPLAY0_DIGITAL_HSYNC_CONTROL'. */
void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_start_column(U16 data);
/*! \brief Reads the bit group 'start_column' of register 'VO_DISPLAY0_DIGITAL_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_start_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_end_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL;
    d.bitc.end_column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_end_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_end_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_end_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,value);
    #endif
    return tmp_value.bitc.end_column;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_start_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL;
    d.bitc.start_column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_HSYNC_CONTROL_start_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_start_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_HSYNC_CONTROL_start_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_HSYNC_CONTROL,value);
    #endif
    return tmp_value.bitc.start_column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_START_0 (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_VSYNC_START_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_VSYNC_START_0'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_0'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_0'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_END_0 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_VSYNC_END_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_VSYNC_END_0'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_0'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_0'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_0_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_0_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_0,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_START_1 (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_VSYNC_START_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_VSYNC_START_1'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_1'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_START_1'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_START_1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_START_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_START_1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_START_1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_VSYNC_END_1 (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_VSYNC_END_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_VSYNC_END_1'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_1'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY0_DIGITAL_VSYNC_END_1'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_column(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,value);
    #endif
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_column(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1 = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_VSYNC_END_1_column] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_column(void)
{
    GH_VO_DISPLAY0_DIGITAL_VSYNC_END_1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_VSYNC_END_1_column] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_VSYNC_END_1,value);
    #endif
    return tmp_value.bitc.column;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_656_VBIT (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_656_VBIT'. */
void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_656_VBIT'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT(void);
/*! \brief Writes the bit group 'end_row' of register 'VO_DISPLAY0_DIGITAL_656_VBIT'. */
void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_end_row(U16 data);
/*! \brief Reads the bit group 'end_row' of register 'VO_DISPLAY0_DIGITAL_656_VBIT'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_end_row(void);
/*! \brief Writes the bit group 'start_row' of register 'VO_DISPLAY0_DIGITAL_656_VBIT'. */
void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_start_row(U16 data);
/*! \brief Reads the bit group 'start_row' of register 'VO_DISPLAY0_DIGITAL_656_VBIT'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_start_row(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_VBIT] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_VBIT] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_end_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT;
    d.bitc.end_row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_end_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_end_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_end_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,value);
    #endif
    return tmp_value.bitc.end_row;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_start_row(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT;
    d.bitc.start_row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_VBIT_start_row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_start_row(void)
{
    GH_VO_DISPLAY0_DIGITAL_656_VBIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_VBIT);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_VBIT_start_row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_VBIT,value);
    #endif
    return tmp_value.bitc.start_row;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_656_SAV_START (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_656_SAV_START'. */
void GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_656_SAV_START'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START(void);
/*! \brief Writes the bit group 'Code_Location' of register 'VO_DISPLAY0_DIGITAL_656_SAV_START'. */
void GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START_Code_Location(U16 data);
/*! \brief Reads the bit group 'Code_Location' of register 'VO_DISPLAY0_DIGITAL_656_SAV_START'. */
U16  GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START_Code_Location(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START_Code_Location(U16 data)
{
    GH_VO_DISPLAY0_DIGITAL_656_SAV_START_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START;
    d.bitc.code_location = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_656_SAV_START_Code_Location] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START_Code_Location(void)
{
    GH_VO_DISPLAY0_DIGITAL_656_SAV_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_656_SAV_START);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_656_SAV_START_Code_Location] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_656_SAV_START,value);
    #endif
    return tmp_value.bitc.code_location;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0'. */
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN0] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1'. */
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN1] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2'. */
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN2(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN2(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN2] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN2(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN2] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3 (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3'. */
void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN3(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3'. */
U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN3(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CLOCK_PATTERN3] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN3(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_DIGITAL_CLOCK_PATTERN3] --> 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CLOCK_PATTERN3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_0 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_0'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_0'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0(U32 data)
{
    m_vo_display0_digital_csc_param_0.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_0.all);
    #endif
    return m_vo_display0_digital_csc_param_0.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_0.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0 = m_vo_display0_digital_csc_param_0.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0,m_vo_display0_digital_csc_param_0.all,m_vo_display0_digital_csc_param_0.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_0.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_0.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_0.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0 = m_vo_display0_digital_csc_param_0.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_0,m_vo_display0_digital_csc_param_0.all,m_vo_display0_digital_csc_param_0.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_0.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_0.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_1 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_1'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_1'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1(U32 data)
{
    m_vo_display0_digital_csc_param_1.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_1.all);
    #endif
    return m_vo_display0_digital_csc_param_1.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_1.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1 = m_vo_display0_digital_csc_param_1.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1,m_vo_display0_digital_csc_param_1.all,m_vo_display0_digital_csc_param_1.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_1.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_1.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_1.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1 = m_vo_display0_digital_csc_param_1.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_1,m_vo_display0_digital_csc_param_1.all,m_vo_display0_digital_csc_param_1.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_1.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_1.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_2 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_2'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_2'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_2'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_2'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2(U32 data)
{
    m_vo_display0_digital_csc_param_2.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_2.all);
    #endif
    return m_vo_display0_digital_csc_param_2.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_2.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2 = m_vo_display0_digital_csc_param_2.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2,m_vo_display0_digital_csc_param_2.all,m_vo_display0_digital_csc_param_2.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_2.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_2.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_2.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2 = m_vo_display0_digital_csc_param_2.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_2,m_vo_display0_digital_csc_param_2.all,m_vo_display0_digital_csc_param_2.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_2.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_2.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_3 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_3'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_3'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_3'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_3'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3(U32 data)
{
    m_vo_display0_digital_csc_param_3.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_3.all);
    #endif
    return m_vo_display0_digital_csc_param_3.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246(U16 data)
{
    m_vo_display0_digital_csc_param_3.bitc.coefficient_a0246 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3 = m_vo_display0_digital_csc_param_3.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3,m_vo_display0_digital_csc_param_3.all,m_vo_display0_digital_csc_param_3.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_3.bitc.coefficient_a0246);
    #endif
    return m_vo_display0_digital_csc_param_3.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357(U16 data)
{
    m_vo_display0_digital_csc_param_3.bitc.coefficient_a1357 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3 = m_vo_display0_digital_csc_param_3.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_3,m_vo_display0_digital_csc_param_3.all,m_vo_display0_digital_csc_param_3.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_3.bitc.coefficient_a1357);
    #endif
    return m_vo_display0_digital_csc_param_3.bitc.coefficient_a1357;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_4 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_4'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_4'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4(void);
/*! \brief Writes the bit group 'Coefficient_a8' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_4'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Coefficient_a8(U16 data);
/*! \brief Reads the bit group 'Coefficient_a8' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8(void);
/*! \brief Writes the bit group 'Constant_b0' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_4'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Constant_b0(U16 data);
/*! \brief Reads the bit group 'Constant_b0' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Constant_b0(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4(U32 data)
{
    m_vo_display0_digital_csc_param_4.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_4.all);
    #endif
    return m_vo_display0_digital_csc_param_4.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Coefficient_a8(U16 data)
{
    m_vo_display0_digital_csc_param_4.bitc.coefficient_a8 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4 = m_vo_display0_digital_csc_param_4.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Coefficient_a8] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4,m_vo_display0_digital_csc_param_4.all,m_vo_display0_digital_csc_param_4.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_4.bitc.coefficient_a8);
    #endif
    return m_vo_display0_digital_csc_param_4.bitc.coefficient_a8;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Constant_b0(U16 data)
{
    m_vo_display0_digital_csc_param_4.bitc.constant_b0 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4 = m_vo_display0_digital_csc_param_4.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_4_Constant_b0] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_4,m_vo_display0_digital_csc_param_4.all,m_vo_display0_digital_csc_param_4.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Constant_b0(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_4_Constant_b0] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_4.bitc.constant_b0);
    #endif
    return m_vo_display0_digital_csc_param_4.bitc.constant_b0;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_5 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_5'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_5'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5(void);
/*! \brief Writes the bit group 'Constant_b1' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_5'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b1(U16 data);
/*! \brief Reads the bit group 'Constant_b1' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b1(void);
/*! \brief Writes the bit group 'Constant_b2' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_5'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b2(U16 data);
/*! \brief Reads the bit group 'Constant_b2' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b2(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5(U32 data)
{
    m_vo_display0_digital_csc_param_5.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_5.all);
    #endif
    return m_vo_display0_digital_csc_param_5.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b1(U16 data)
{
    m_vo_display0_digital_csc_param_5.bitc.constant_b1 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5 = m_vo_display0_digital_csc_param_5.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b1] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5,m_vo_display0_digital_csc_param_5.all,m_vo_display0_digital_csc_param_5.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b1(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b1] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_5.bitc.constant_b1);
    #endif
    return m_vo_display0_digital_csc_param_5.bitc.constant_b1;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b2(U16 data)
{
    m_vo_display0_digital_csc_param_5.bitc.constant_b2 = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5 = m_vo_display0_digital_csc_param_5.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_5_Constant_b2] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_5,m_vo_display0_digital_csc_param_5.all,m_vo_display0_digital_csc_param_5.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b2(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_5_Constant_b2] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_5.bitc.constant_b2);
    #endif
    return m_vo_display0_digital_csc_param_5.bitc.constant_b2;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_6 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_6'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_6'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_6'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_6'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_6'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_6'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6(U32 data)
{
    m_vo_display0_digital_csc_param_6.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_6.all);
    #endif
    return m_vo_display0_digital_csc_param_6.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(U16 data)
{
    m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_low = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6 = m_vo_display0_digital_csc_param_6.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6,m_vo_display0_digital_csc_param_6.all,m_vo_display0_digital_csc_param_6.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_low);
    #endif
    return m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(U16 data)
{
    m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_high = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6 = m_vo_display0_digital_csc_param_6.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_6,m_vo_display0_digital_csc_param_6.all,m_vo_display0_digital_csc_param_6.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_high);
    #endif
    return m_vo_display0_digital_csc_param_6.bitc.output_012_clamp_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_7 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_7'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_7'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_7'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_7'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_7'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_7'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7(U32 data)
{
    m_vo_display0_digital_csc_param_7.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_7.all);
    #endif
    return m_vo_display0_digital_csc_param_7.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(U16 data)
{
    m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_low = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7 = m_vo_display0_digital_csc_param_7.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7,m_vo_display0_digital_csc_param_7.all,m_vo_display0_digital_csc_param_7.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_low);
    #endif
    return m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(U16 data)
{
    m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_high = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7 = m_vo_display0_digital_csc_param_7.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_7,m_vo_display0_digital_csc_param_7.all,m_vo_display0_digital_csc_param_7.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_high);
    #endif
    return m_vo_display0_digital_csc_param_7.bitc.output_012_clamp_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_DIGITAL_CSC_PARAM_8 (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_8'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_8'. */
U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_8'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_8'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_8'. */
void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY0_DIGITAL_CSC_PARAM_8'. */
U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8(U32 data)
{
    m_vo_display0_digital_csc_param_8.all = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8 = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_8.all);
    #endif
    return m_vo_display0_digital_csc_param_8.all;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(U16 data)
{
    m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_low = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8 = m_vo_display0_digital_csc_param_8.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8,m_vo_display0_digital_csc_param_8.all,m_vo_display0_digital_csc_param_8.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_low);
    #endif
    return m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(U16 data)
{
    m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_high = data;
    *(volatile U32 *)REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8 = m_vo_display0_digital_csc_param_8.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_DIGITAL_CSC_PARAM_8,m_vo_display0_digital_csc_param_8.all,m_vo_display0_digital_csc_param_8.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY0_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_high);
    #endif
    return m_vo_display0_digital_csc_param_8.bitc.output_012_clamp_high;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_VOUT_VOUT_SYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_VOUT_VOUT_SYNC'. */
void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_VOUT_VOUT_SYNC'. */
U32  GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC(void);
/*! \brief Writes the bit group 'Start_Row' of register 'VO_DISPLAY0_VOUT_VOUT_SYNC'. */
void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Start_Row(U16 data);
/*! \brief Reads the bit group 'Start_Row' of register 'VO_DISPLAY0_VOUT_VOUT_SYNC'. */
U16  GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Start_Row(void);
/*! \brief Writes the bit group 'Field_Select' of register 'VO_DISPLAY0_VOUT_VOUT_SYNC'. */
void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Field_Select(U8 data);
/*! \brief Reads the bit group 'Field_Select' of register 'VO_DISPLAY0_VOUT_VOUT_SYNC'. */
U8   GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Field_Select(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC] --> 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Start_Row(U16 data)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC;
    d.bitc.start_row = data;
    *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Start_Row] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Start_Row(void)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Start_Row] --> 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,value);
    #endif
    return tmp_value.bitc.start_row;
}
GH_INLINE void GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Field_Select(U8 data)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC;
    d.bitc.field_select = data;
    *(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC = d.all;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_VOUT_VOUT_SYNC_Field_Select] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Field_Select(void)
{
    GH_VO_DISPLAY0_VOUT_VOUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_VOUT_VOUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_VOUT_VOUT_SYNC_Field_Select] --> 0x%08x\n",
                        REG_VO_DISPLAY0_VOUT_VOUT_SYNC,value);
    #endif
    return tmp_value.bitc.field_select;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_INPUT_STREAM_ENABLES (read/write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_INPUT_STREAM_ENABLES'. */
void GH_VO_DISPLAY0_set_INPUT_STREAM_ENABLES(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_INPUT_STREAM_ENABLES'. */
U32  GH_VO_DISPLAY0_get_INPUT_STREAM_ENABLES(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_INPUT_STREAM_ENABLES(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_INPUT_STREAM_ENABLES = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_INPUT_STREAM_ENABLES] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_STREAM_ENABLES,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_INPUT_STREAM_ENABLES(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_INPUT_STREAM_ENABLES);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_INPUT_STREAM_ENABLES] --> 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_STREAM_ENABLES,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_INPUT_SYNC_CONTROL (read/write)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_INPUT_SYNC_CONTROL'. */
void GH_VO_DISPLAY0_set_INPUT_SYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_INPUT_SYNC_CONTROL'. */
U32  GH_VO_DISPLAY0_get_INPUT_SYNC_CONTROL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_INPUT_SYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_INPUT_SYNC_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_INPUT_SYNC_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_SYNC_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_INPUT_SYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_INPUT_SYNC_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_INPUT_SYNC_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_INPUT_SYNC_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_OUTPUT_SYNC_CONTROL (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_OUTPUT_SYNC_CONTROL'. */
void GH_VO_DISPLAY0_set_OUTPUT_SYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_OUTPUT_SYNC_CONTROL'. */
U32  GH_VO_DISPLAY0_get_OUTPUT_SYNC_CONTROL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_OUTPUT_SYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_OUTPUT_SYNC_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_OUTPUT_SYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_OUTPUT_SYNC_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_OUTPUT_SYNC_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_STREAM_CONTROL (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_STREAM_CONTROL'. */
void GH_VO_DISPLAY0_set_STREAM_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_STREAM_CONTROL'. */
U32  GH_VO_DISPLAY0_get_STREAM_CONTROL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_STREAM_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_STREAM_CONTROL = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_STREAM_CONTROL] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_STREAM_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_STREAM_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_STREAM_CONTROL);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_STREAM_CONTROL] --> 0x%08x\n",
                        REG_VO_DISPLAY0_STREAM_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY0_FRAME_ENABLE (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DISPLAY0_FRAME_ENABLE'. */
void GH_VO_DISPLAY0_set_FRAME_ENABLE(U32 data);
/*! \brief Reads the register 'VO_DISPLAY0_FRAME_ENABLE'. */
U32  GH_VO_DISPLAY0_get_FRAME_ENABLE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DISPLAY0_set_FRAME_ENABLE(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY0_FRAME_ENABLE = data;
    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DISPLAY0_set_FRAME_ENABLE] <-- 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_ENABLE,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DISPLAY0_get_FRAME_ENABLE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY0_FRAME_ENABLE);

    #if GH_VO_DISPLAY0_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DISPLAY0_get_FRAME_ENABLE] --> 0x%08x\n",
                        REG_VO_DISPLAY0_FRAME_ENABLE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_DISPLAY0_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_DISPLAY0_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

