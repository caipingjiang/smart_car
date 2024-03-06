/*
*******************************************************************************
**
** \file      gd_gpio.h
**
** \brief     General purpose input output driver.
**
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
*******************************************************************************
*/
#ifndef _GD_GPIO_H_
#define _GD_GPIO_H_

#include <gtypes.h>
#include <gmodids.h>
//#include "gd_int.h"

/*!
*******************************************************************************
**
** \brief GPIO driver error codes.
**
*******************************************************************************
*/
#define GD_GPIO_ERR_BASE (GD_GPIO_MODULE_ID<<16) //!< The GPIO base error code.

enum
{
    /*!
    ** The GPIO is not of the right mode to to perform
    ** a requested function, e.g. writing to a GPIO which was
    ** configured as input.
    */
    GD_ERR_GPIO_INVALID_TYPE = GD_GPIO_ERR_BASE,
    GD_ERR_GPIO_OPEN_FAILED,
};

/*!
*******************************************************************************
**
** \brief All available GPIO pins named by number.
**
** \sa GD_GPIO_Open()
** \sa GD_GPIO_OpenFunctionMode()
** \sa GD_GPIO_SetType()
**
*******************************************************************************
*/
typedef enum
{
    GD_GPIO_0  =  0, //!< Value representing GPIO  0.
    GD_GPIO_1  =  1, //!< Value representing GPIO  1.
    GD_GPIO_2  =  2, //!< Value representing GPIO  2.
    GD_GPIO_3  =  3, //!< Value representing GPIO  3.
    GD_GPIO_4  =  4, //!< Value representing GPIO  4.
    GD_GPIO_5  =  5, //!< Value representing GPIO  5.
    GD_GPIO_6  =  6, //!< Value representing GPIO  6.
    GD_GPIO_7  =  7, //!< Value representing GPIO  7.
    GD_GPIO_8  =  8, //!< Value representing GPIO  8.
    GD_GPIO_9  =  9, //!< Value representing GPIO  9.
    GD_GPIO_10 = 10, //!< Value representing GPIO 10.
    GD_GPIO_11 = 11, //!< Value representing GPIO 11.
    GD_GPIO_12 = 12, //!< Value representing GPIO 12.
    GD_GPIO_13 = 13, //!< Value representing GPIO 13.
    GD_GPIO_14 = 14, //!< Value representing GPIO 14.
    GD_GPIO_15 = 15, //!< Value representing GPIO 15.
    GD_GPIO_16 = 16, //!< Value representing GPIO 16.
    GD_GPIO_17 = 17, //!< Value representing GPIO 17.
    GD_GPIO_18 = 18, //!< Value representing GPIO 18.
    GD_GPIO_19 = 19, //!< Value representing GPIO 19.
    GD_GPIO_20 = 20, //!< Value representing GPIO 20.
    GD_GPIO_21 = 21, //!< Value representing GPIO 21.
    GD_GPIO_22 = 22, //!< Value representing GPIO 22.
    GD_GPIO_23 = 23, //!< Value representing GPIO 23.
    GD_GPIO_24 = 24, //!< Value representing GPIO 24.
    GD_GPIO_25 = 25, //!< Value representing GPIO 25.
    GD_GPIO_26 = 26, //!< Value representing GPIO 26.
    GD_GPIO_27 = 27, //!< Value representing GPIO 27.
    GD_GPIO_28 = 28, //!< Value representing GPIO 28.
    GD_GPIO_29 = 29, //!< Value representing GPIO 29.
    GD_GPIO_30 = 30, //!< Value representing GPIO 30.
    GD_GPIO_31 = 31, //!< Value representing GPIO 31.
    GD_GPIO_32 = 32, //!< Value representing GPIO 32.
    GD_GPIO_33 = 33, //!< Value representing GPIO 33.
    GD_GPIO_34 = 34, //!< Value representing GPIO 34.
    GD_GPIO_35 = 35, //!< Value representing GPIO 35.
    GD_GPIO_36 = 36, //!< Value representing GPIO 36.
    GD_GPIO_37 = 37, //!< Value representing GPIO 37.
    GD_GPIO_38 = 38, //!< Value representing GPIO 38.
    GD_GPIO_39 = 39, //!< Value representing GPIO 39.
    GD_GPIO_40 = 40, //!< Value representing GPIO 40.
    GD_GPIO_41 = 41, //!< Value representing GPIO 41.
    GD_GPIO_42 = 42, //!< Value representing GPIO 42.
    GD_GPIO_43 = 43, //!< Value representing GPIO 43.
    GD_GPIO_44 = 44, //!< Value representing GPIO 44.
    GD_GPIO_45 = 45, //!< Value representing GPIO 45.
    GD_GPIO_46 = 46, //!< Value representing GPIO 46.
    GD_GPIO_47 = 47, //!< Value representing GPIO 47.
    GD_GPIO_48 = 48, //!< Value representing GPIO 48.
    GD_GPIO_49 = 49, //!< Value representing GPIO 49.
    GD_GPIO_50 = 50, //!< Value representing GPIO 50.
    GD_GPIO_51 = 51, //!< Value representing GPIO 51.
    GD_GPIO_52 = 52, //!< Value representing GPIO 52.
    GD_GPIO_53 = 53, //!< Value representing GPIO 53.
    GD_GPIO_54 = 54, //!< Value representing GPIO 54.
    GD_GPIO_55 = 55, //!< Value representing GPIO 55.
    GD_GPIO_NUM,
}GD_GPIO_PIN_E;;

/*!
*******************************************************************************
**
** \brief GPIO types.
** \high 30-31:00:unused; 01: in; 10:out; 11:in & out.
** \[ 7: 0]: OUTPUT_CFG out_sel
** \    0x00: tied to 1��b0, always output 0
** \    0x01: tied to 1��b1, always output 1
** \    0x02~0x3f: data inputs from internal modules
** \[15: 8]: INPUT_CFG  in_sel
** \    0x00: tied to 1��b0, module��s input is always 0
** \    0x01: tied to 1��b1, module��s input is always 1
** \    0x02~0x3f: mux selection(gpio_input[61:0])
** \[21:16]: OUTPUT_CFG oen_sel
** \    0x00: tied to 1��b0, always output
** \    0x01: tied to 1��b1, always input
** \    0x02~0x3f: oen inputs from internal modules
** \[22:22]: out_invert
** \[23:23]: oen_invert
** \[29:24]: IOCTRL
** \    [25:24]: 0=2mA,1=4mA,2=8mA,3=12mA
** \    [29:28]: tied to 1��b0, always output
**
** \sa GD_GPIO_SetType()
** \sa GD_GPIO_Open()
**
*******************************************************************************
*/
#define GD_GPIO_OUT_SEL(n)      ((n))
#define GD_GPIO_IN_SEL(n)       ((n)<<8)
#define GD_GPIO_OEN_SEL(n)      ((n)<<16)
#define GD_GPIO_OUT_INVERT(n)   ((n)<<22)
#define GD_GPIO_OEN_INVERT(n)   ((n)<<23)
#define GD_GPIO_IOCTRL(n)       ((n)<<24)
#define GD_GPIO_FUNC(n)         ((n)<<30)

#define GD_GPIO_GET_OUT_SEL(n)      (((n)&0x000000FF))
#define GD_GPIO_GET_IN_SEL(n)       (((n)&0x0000FF00)>>8)
#define GD_GPIO_GET_OEN_SEL(n)      (((n)&0x003F0000)>>16)
#define GD_GPIO_GET_OUT_INVERT(n)   (((n)&0x00400000)>>22)
#define GD_GPIO_GET_OEN_INVERT(n)   (((n)&0x00800000)>>23)
#define GD_GPIO_GET_IOCTRL(n)       (((n)&0x3F000000)>>24)
#define GD_GPIO_GET_FUNC(n)         (((n)&0xC0000000)>>30)

#define GD_GPIO_FUNC_IN     1
#define GD_GPIO_FUNC_OUT    2
#define GD_GPIO_FUNC_INOUT  3


#define IOCTRL_NORMAL       0x00    //!< Hi-z
#define IOCTRL_PULL_UP      0x10    //!< PULL_UP
#define IOCTRL_PULL_DOWN    0x20    //!< PULL_DOWN
#define IOCTRL_REPEAT       0x30    //!< REPEAT

#define IOCTRL_2MA          0x00    //!< 2mA
#define IOCTRL_4MA          0x01    //!< 4mA
#define IOCTRL_8MA          0x02    //!< 8mA
#define IOCTRL_12MA         0x03    //!< 12mA
typedef enum
{

    /* ----------------------------------- GPIO output function define ----------------------------------- */
    GD_GPIO_TYPE_OUTPUT_0               = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 0),    //!< Output type: value = 0
    GD_GPIO_TYPE_OUTPUT_1               = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 1),    //!< Output type: value = 1
    GD_GPIO_TYPE_OUTPUT_SPI1_SO         = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 2) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 2),    //!< Output type: tssi_txd
    GD_GPIO_TYPE_OUTPUT_SPI1_CS0        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 3),    //!< Output type: tssi_cs0_n
    GD_GPIO_TYPE_OUTPUT_SPI1_SCLK       = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 4),    //!< Output type: tssi_sclk_out
    GD_GPIO_TYPE_OUTPUT_UART2_RTS_N     = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 5),    //!< Output type: uart2_rts_n
    GD_GPIO_TYPE_OUTPUT_UART2_DTR_N     = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 6),    //!< Output type: uart2_dtr_n
    GD_GPIO_TYPE_OUTPUT_UART2_TX        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 7),    //!< Output type: uart2_tx
    GD_GPIO_TYPE_OUTPUT_UART1_TX        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 8),    //!< Output type: uart1_tx
    GD_GPIO_TYPE_OUTPUT_UART0_TX        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL( 9),    //!< Output type: uart0_tx
    GD_GPIO_TYPE_OUTPUT_PWM3_OUT        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(10),    //!< Output type: pwm3_out
    GD_GPIO_TYPE_OUTPUT_PWM2_OUT        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(11),    //!< Output type: pwm2_out
    GD_GPIO_TYPE_OUTPUT_PWM1_OUT        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(12),    //!< Output type: pwm1_out
    GD_GPIO_TYPE_OUTPUT_PWM0_OUT        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(13),    //!< Output type: pwm0_out
    GD_GPIO_TYPE_OUTPUT_SPI0_SO         = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 7) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(14),    //!< Output type: ssi_txd
    GD_GPIO_TYPE_OUTPUT_SPI0_CS7        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(15),    //!< Output type: ssi_cs7_n
    GD_GPIO_TYPE_OUTPUT_SPI0_CS6        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(16),    //!< Output type: ssi_cs6_n
    GD_GPIO_TYPE_OUTPUT_SPI0_CS5        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(17),    //!< Output type: ssi_cs5_n
    GD_GPIO_TYPE_OUTPUT_SPI0_CS4        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(18),    //!< Output type: ssi_cs4_n
    GD_GPIO_TYPE_OUTPUT_SPI0_CS1        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(19),    //!< Output type: ssi_cs1_n
    GD_GPIO_TYPE_OUTPUT_SPI0_CS0        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(20),    //!< Output type: ssi_cs0_n
    GD_GPIO_TYPE_OUTPUT_SPI0_SCLK       = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(21),    //!< Output type: ssi_sclk_out
    //GD_GPIO_TYPE_INOUT_SD_DATA_0                                                                                                                                         GD_GPIO_OEN_SEL( 8)                          GD_GPIO_OUT_SEL(22)
    //GD_GPIO_TYPE_INOUT_SD_DATA_1                                                                                                                                         GD_GPIO_OEN_SEL( 9)                          GD_GPIO_OUT_SEL(23)
    //GD_GPIO_TYPE_INOUT_SD_DATA_2                                                                                                                                         GD_GPIO_OEN_SEL(10)                          GD_GPIO_OUT_SEL(24)
    //GD_GPIO_TYPE_INOUT_SD_DATA_3                                                                                                                                         GD_GPIO_OEN_SEL(11)                          GD_GPIO_OUT_SEL(25)
    //GD_GPIO_TYPE_INOUT_SD_DATA_4                                                                                                                                         GD_GPIO_OEN_SEL(12)                          GD_GPIO_OUT_SEL(26)
    //GD_GPIO_TYPE_INOUT_SD_DATA_5                                                                                                                                         GD_GPIO_OEN_SEL(13)                          GD_GPIO_OUT_SEL(27)
    //GD_GPIO_TYPE_INOUT_SD_DATA_6                                                                                                                                         GD_GPIO_OEN_SEL(14)                          GD_GPIO_OUT_SEL(28)
    //GD_GPIO_TYPE_INOUT_SD_DATA_7                                                                                                                                         GD_GPIO_OEN_SEL(15)                          GD_GPIO_OUT_SEL(29)
    //GD_GPIO_TYPE_INOUT_SDIO_CMD                                                                                                                                          GD_GPIO_OEN_SEL(16)                          GD_GPIO_OUT_SEL(30)
    GD_GPIO_TYPE_OUTPUT_SDIO_CLK        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)     | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(31),    //!< Output type: sd_clk_sdcard
    GD_GPIO_TYPE_OUTPUT_AOMCLK          = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(32),    //!< Output type: i2s_au_clk
    GD_GPIO_TYPE_OUTPUT_AOBCLK          = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(17) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(33),    //!< Output type: i2s_clk_o
    GD_GPIO_TYPE_OUTPUT_AOLRCLK         = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(18) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(34),    //!< Output type: i2s_ws_o
    GD_GPIO_TYPE_OUTPUT_AO_DATA0        = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(35),    //!< Output type: i2s_so
    GD_GPIO_TYPE_OUTPUT_SF_CS0          = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(36),    //!< Output type: sf_cs0_n
    GD_GPIO_TYPE_OUTPUT_SF_CS1          = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(37),    //!< Output type: sf_cs1_n
    GD_GPIO_TYPE_OUTPUT_EPHY_LED_0      = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(38),    //!< Output type: ephy_led[0] hcd ok
    GD_GPIO_TYPE_OUTPUT_EPHY_LED_1      = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(39),    //!< Output type: ephy_led[1] duplex
    GD_GPIO_TYPE_OUTPUT_EPHY_LED_2      = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(40),    //!< Output type: ephy_led[2] 10M CRS out
    GD_GPIO_TYPE_OUTPUT_EPHY_LED_3      = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(41),    //!< Output type: ephy_led[3] 100M CRS out
    GD_GPIO_TYPE_OUTPUT_EPHY_LED_4      = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(42),    //!< Output type: ephy_led[4] clo gs
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_0  = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(43),    //!< Output type: enet_phy_txd[0]
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_1  = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(44),    //!< Output type: enet_phy_txd[1]
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_2  = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(45),    //!< Output type: enet_phy_txd[2]
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_TXD_3  = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(46),    //!< Output type: enet_phy_txd[3]
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_TXER   = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(47),    //!< Output type: enet_phy_txer
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_TXEN   = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(48),    //!< Output type: enet_phy_txen
    // GD_GPIO_TYPE_INOUT_ETH_MDIO                                                                                                                                                                                      GD_GPIO_OUT_SEL(49)
    GD_GPIO_TYPE_OUTPUT_ENET_PHY_RESET  = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(61),    //!< Output type: enet_phy_reset
    GD_GPIO_TYPE_OUTPUT_ENET_GMII_MDC_O = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(50),    //!< Output type: enet_gmii_mdc_o
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_0    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(51),    //!< Output type: ahb_dac_dr[0]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_1    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(52),    //!< Output type: ahb_dac_dr[1]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_2    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(53),    //!< Output type: ahb_dac_dr[2]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_3    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(54),    //!< Output type: ahb_dac_dr[3]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_4    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(55),    //!< Output type: ahb_dac_dr[4]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_5    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(56),    //!< Output type: ahb_dac_dr[5]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_6    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(57),    //!< Output type: ahb_dac_dr[6]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_7    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(58),    //!< Output type: ahb_dac_dr[7]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_8    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(59),    //!< Output type: ahb_dac_dr[8]
    GD_GPIO_TYPE_OUTPUT_AHB_DAC_DR_9    = GD_GPIO_FUNC(GD_GPIO_FUNC_OUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 0) | GD_GPIO_IN_SEL( 0)   | GD_GPIO_OUT_SEL(60),    //!< Output type: ahb_dac_dr[9]

    /* ----------------------------------- GPIO input function define ----------------------------------- */

    GD_GPIO_TYPE_INPUT_0                = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(   0) | GD_GPIO_OUT_SEL( 0),    //!< Input type: normal input
    GD_GPIO_TYPE_INPUT_1                = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)      | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(   1) | GD_GPIO_OUT_SEL( 0),    //!< Input type: normal input
    GD_GPIO_TYPE_INPUT_SPI1_SI          = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+ 0) | GD_GPIO_OUT_SEL( 0),    //!< Input type: tssi_rxd
    //GD_GPIO_TYPE_INOUT_I2C_DATA                                                                                                                                                                GD_GPIO_IN_SEL(2+ 1)
    //GD_GPIO_TYPE_INOUT_I2C_CLK                                                                                                                                                                 GD_GPIO_IN_SEL(2+ 2)
    //GD_GPIO_TYPE_INOUT_I2C_DATA2                                                                                                                                                               GD_GPIO_IN_SEL(2+ 3)
    //GD_GPIO_TYPE_INOUT_I2C_CLK2                                                                                                                                                                GD_GPIO_IN_SEL(2+ 4)
    GD_GPIO_TYPE_INPUT_UART2_RX         = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+ 5) | GD_GPIO_OUT_SEL( 0),    //!< Input type: uart2_rx
    GD_GPIO_TYPE_INPUT_UART1_RX         = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+ 6) | GD_GPIO_OUT_SEL( 0),    //!< Input type: uart1_rx
    GD_GPIO_TYPE_INPUT_UART0_RX         = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+ 7) | GD_GPIO_OUT_SEL( 0),    //!< Input type: uart0_rx
    GD_GPIO_TYPE_INPUT_TIMER1_CLK       = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+ 8) | GD_GPIO_OUT_SEL( 0),    //!< Input type: timer1_clk
    GD_GPIO_TYPE_INPUT_TIMER2_CLK       = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+ 9) | GD_GPIO_OUT_SEL( 0),    //!< Input type: timer2_clk
    GD_GPIO_TYPE_INPUT_TIMER3_CLK       = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+10) | GD_GPIO_OUT_SEL( 0),    //!< Input type: timer3_clk
    GD_GPIO_TYPE_INPUT_SPI0_SI          = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+11) | GD_GPIO_OUT_SEL( 0),    //!< Input type: ssi_rxd
    GD_GPIO_TYPE_INPUT_SD_WP_N          = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)      | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+12) | GD_GPIO_OUT_SEL( 0),    //!< Input type: sd_wp_n
    GD_GPIO_TYPE_INPUT_SD_CD_N          = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)      | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+13) | GD_GPIO_OUT_SEL( 0),    //!< Input type: sd_cd_n
    //GD_GPIO_TYPE_INOUT_SD_DATA_0                                                                                                                                                               GD_GPIO_IN_SEL(2+14)
    //GD_GPIO_TYPE_INOUT_SD_DATA_1                                                                                                                                                               GD_GPIO_IN_SEL(2+15)
    //GD_GPIO_TYPE_INOUT_SD_DATA_2                                                                                                                                                               GD_GPIO_IN_SEL(2+16)
    //GD_GPIO_TYPE_INOUT_SD_DATA_3                                                                                                                                                               GD_GPIO_IN_SEL(2+17)
    //GD_GPIO_TYPE_INOUT_SD_DATA_4                                                                                                                                                               GD_GPIO_IN_SEL(2+18)
    //GD_GPIO_TYPE_INOUT_SD_DATA_5                                                                                                                                                               GD_GPIO_IN_SEL(2+19)
    //GD_GPIO_TYPE_INOUT_SD_DATA_6                                                                                                                                                               GD_GPIO_IN_SEL(2+20)
    //GD_GPIO_TYPE_INOUT_SD_DATA_7                                                                                                                                                               GD_GPIO_IN_SEL(2+21)
    //GD_GPIO_TYPE_INOUT_SDIO_CMD                                                                                                                                                                GD_GPIO_IN_SEL(2+22)
    GD_GPIO_TYPE_INPUT_I2S_CLK          = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+23) | GD_GPIO_OUT_SEL( 0),    //!< Input type: i2s_clk
    GD_GPIO_TYPE_INPUT_I2S_WS           = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+24) | GD_GPIO_OUT_SEL( 0),    //!< Input type: i2s_ws
    GD_GPIO_TYPE_INPUT_I2S_SI           = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+25) | GD_GPIO_OUT_SEL( 0),    //!< Input type: i2s_si
    GD_GPIO_TYPE_INPUT_CLK_AU           = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+26) | GD_GPIO_OUT_SEL( 0),    //!< Input type: clk_au
    GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_0   = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+27) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_rxd[0]
    GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_1   = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+28) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_rxd[1]
    GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_2   = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+29) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_rxd[2]
    GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_3   = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+30) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_rxd[3]
    GD_GPIO_TYPE_INPUT_ENET_PHY_COL     = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+31) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_col
    GD_GPIO_TYPE_INPUT_ENET_PHY_CRS     = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+32) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_crs
    GD_GPIO_TYPE_INPUT_ENET_PHY_RXER    = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+33) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_rxer
    GD_GPIO_TYPE_INPUT_ENET_PHY_RXDV    = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+34) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_phy_rxdv
    // GD_GPIO_TYPE_INOUT_ETH_MDIO                                                                                                                                                               GD_GPIO_IN_SEL(2+35)
    GD_GPIO_TYPE_INPUT_ENET_CLK_RX      = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+36) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_clk_rx
    GD_GPIO_TYPE_INPUT_ENET_CLK_TX      = GD_GPIO_FUNC(GD_GPIO_FUNC_IN) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA)    | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 1) | GD_GPIO_IN_SEL(2+37) | GD_GPIO_OUT_SEL( 0),    //!< Input type: enet_clk_tx

    /* ----------------------------------- GPIO input&&output function define ----------------------------------- */
    GD_GPIO_TYPE_INOUT_I2C_DATA         = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 3) | GD_GPIO_IN_SEL(2+ 1) | GD_GPIO_OUT_SEL( 0),    //!< Input/Output type: i2c_sda
    GD_GPIO_TYPE_INOUT_I2C_CLK          = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 4) | GD_GPIO_IN_SEL(2+ 2) | GD_GPIO_OUT_SEL( 0),    //!< Input/Output type: i2c_scl
    GD_GPIO_TYPE_INOUT_I2C_DATA2        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 5) | GD_GPIO_IN_SEL(2+ 3) | GD_GPIO_OUT_SEL( 0),    //!< Input/Output type: i2c_sda2
    GD_GPIO_TYPE_INOUT_I2C_CLK2         = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(0) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 6) | GD_GPIO_IN_SEL(2+ 4) | GD_GPIO_OUT_SEL( 0),    //!< Input/Output type: i2c_scl2

    GD_GPIO_TYPE_INOUT_ETH_MDIO         = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_DOWN|IOCTRL_2MA) | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(19) | GD_GPIO_IN_SEL(2+35) | GD_GPIO_OUT_SEL(49),    //!< Input/Output type: enet_gmii_mdi/enet_gmii_mod_o

    GD_GPIO_TYPE_INOUT_SD_DATA_0        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 8) | GD_GPIO_IN_SEL(2+14) | GD_GPIO_OUT_SEL(22),    //!< Input/Output type: sd_data_out[0]
    GD_GPIO_TYPE_INOUT_SD_DATA_1        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL( 9) | GD_GPIO_IN_SEL(2+15) | GD_GPIO_OUT_SEL(23),    //!< Input/Output type: sd_data_out[1]
    GD_GPIO_TYPE_INOUT_SD_DATA_2        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(10) | GD_GPIO_IN_SEL(2+16) | GD_GPIO_OUT_SEL(24),    //!< Input/Output type: sd_data_out[2]
    GD_GPIO_TYPE_INOUT_SD_DATA_3        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(11) | GD_GPIO_IN_SEL(2+17) | GD_GPIO_OUT_SEL(25),    //!< Input/Output type: sd_data_out[3]
    GD_GPIO_TYPE_INOUT_SD_DATA_4        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(12) | GD_GPIO_IN_SEL(2+18) | GD_GPIO_OUT_SEL(26),    //!< Input/Output type: sd_data_out[4]
    GD_GPIO_TYPE_INOUT_SD_DATA_5        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(13) | GD_GPIO_IN_SEL(2+19) | GD_GPIO_OUT_SEL(27),    //!< Input/Output type: sd_data_out[5]
    GD_GPIO_TYPE_INOUT_SD_DATA_6        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(14) | GD_GPIO_IN_SEL(2+20) | GD_GPIO_OUT_SEL(28),    //!< Input/Output type: sd_data_out[6]
    GD_GPIO_TYPE_INOUT_SD_DATA_7        = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(15) | GD_GPIO_IN_SEL(2+21) | GD_GPIO_OUT_SEL(29),    //!< Input/Output type: sd_data_out[7]
    GD_GPIO_TYPE_INOUT_SD_CMD           = GD_GPIO_FUNC(GD_GPIO_FUNC_INOUT) | GD_GPIO_IOCTRL(IOCTRL_PULL_UP|IOCTRL_2MA)   | GD_GPIO_OEN_INVERT(1) | GD_GPIO_OUT_INVERT(0) | GD_GPIO_OEN_SEL(16) | GD_GPIO_IN_SEL(2+22) | GD_GPIO_OUT_SEL(30),    //!< Input/Output : sd_cmd

    GD_GPIO_TYPE_UNDEFINED              = 0,
} GD_GPIO_TYPE_E;

/*!
*******************************************************************************
**
** \brief Interrupt trigger types.
**
*******************************************************************************
*/
typedef enum
{
    GD_GPIO_INT_TRIGGER_LOW_LEVEL,      //!< Interrupt trigger on low level.
    GD_GPIO_INT_TRIGGER_HIGH_LEVEL,     //!< Interrupt trigger on high level.
    GD_GPIO_INT_TRIGGER_RISING_EDGE,    //!< Interrupt trigger on rising edge.
    GD_GPIO_INT_TRIGGER_FALLING_EDGE,   //!< Interrupt trigger on falling edge.
    GD_GPIO_INT_TRIGGER_BOTH_EDGE       //!< Interrupt trigger on both edge.
}GD_GPIO_INT_TRIGGER_E;

/*!
*******************************************************************************
**
** \brief Interrupt configuration.
**
** \sa    GD_GPIO_Open()
**
*******************************************************************************
*/
typedef struct
{
    /*!
    ** The interrupt trigger type.
    */
    GD_GPIO_INT_TRIGGER_E trigger;

    /*!
    ** Flag to enable/disable the interrupt.
    */
    GBOOL enable;

    /*!
    ** The notification function which shall be called when an interrupt
    ** occurs.
    */
    void (*notifyFct)();
}GD_GPIO_INT_CONFIG_S;

/*!
*******************************************************************************
**
** \brief GPIO cross reference between GPIO pins and functions.
**
** \sa GD_GPIO_Init()
**
*******************************************************************************
*/
typedef struct
{
    U8             pin;
    GD_GPIO_TYPE_E type;
}GD_GPIO_XREF_S;

/*!
*******************************************************************************
**
** \brief Parameters for initialisation.
**
** \sa GD_GPIO_Init()
**
*******************************************************************************
*/
typedef struct
{
    /*!
    ** General interrupt priority for all GPIO interrupts,
    ** either #GD_INT_LOW_PRIORITY or #GD_INT_MID_PRIORITY.
    */
    S8              irqPriority;
    U8              phyType;	
    U8              Reserve;
    U16             xrefTableCount;
    GD_GPIO_XREF_S* xrefTable;
}GD_GPIO_INIT_PARAMS_S;

/*
*******************************************************************************
**
** \brief Available API functions.
**
*******************************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif

GERR GD_GPIO_Init(GD_GPIO_INIT_PARAMS_S* pInitParams);
GERR GD_GPIO_Exit(void);
GERR GD_GPIO_Open(U8 number, GD_GPIO_TYPE_E type, GD_GPIO_INT_CONFIG_S* pIntConfig, GD_HANDLE* pHandle);
GERR GD_GPIO_Close(GD_HANDLE* pHandle);
GERR GD_GPIO_CloseWithType(U32 type);
GERR GD_GPIO_Read(GD_HANDLE handle, U8 *pBit);
GERR GD_GPIO_Write(GD_HANDLE handle, U8 bit);
GERR GD_GPIO_SetType(GD_HANDLE handle, GD_GPIO_TYPE_E type);
GERR GD_GPIO_DisableInterrupt(void);
GERR GD_GPIO_EnableInterrupt(void);
GERR GD_GPIO_OpenFunctionMode(GD_GPIO_TYPE_E type, GD_HANDLE* pHandle);
GERR GD_GPIO_ControlInvertData(GD_HANDLE handle, U8 modeValue);
GERR GD_GPIO_ControlInvertEnable(GD_HANDLE handle, U8 modeValue);

#ifdef __cplusplus
}
#endif

#endif
