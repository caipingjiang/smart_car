/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-01     wangyq       the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "board.h"
#include "drv_rtc.h"
#include <ald_cmu.h>
#include <ald_rtc.h>

#ifdef RT_USING_RTC

static void __rtc_init(rtc_init_t *init)
{
    assert_param(IS_RTC_HOUR_FORMAT(init->hour_format));
    assert_param(IS_RTC_OUTPUT_SEL(init->output));
    assert_param(IS_RTC_OUTPUT_POLARITY(init->output_polarity));

    ald_rtc_reset();
    RTC_UNLOCK();

    MODIFY_REG(RTC->CON, RTC_CON_HFM_MSK, init->hour_format << RTC_CON_HFM_POS);
    MODIFY_REG(RTC->CON, RTC_CON_EOS_MSK, init->output << RTC_CON_EOS_POSS);
    MODIFY_REG(RTC->CON, RTC_CON_POL_MSK, init->output_polarity << RTC_CON_POL_POS);
    MODIFY_REG(RTC->PSR, RTC_PSR_SPRS_MSK, init->synch_pre_div << RTC_PSR_SPRS_POSS);
    MODIFY_REG(RTC->PSR, RTC_PSR_APRS_MSK, init->asynch_pre_div << RTC_PSR_APRS_POSS);

    RTC_LOCK();
    return;
}

static rt_err_t es32f0_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    struct tm time_temp;
    struct tm *pNow;
    rtc_date_t date;
    rtc_time_t time;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:

        ald_rtc_get_date_time(&date, &time, RTC_FORMAT_DEC);
        time_temp.tm_sec = time.second;
        time_temp.tm_min = time.minute;
        time_temp.tm_hour = time.hour;
        time_temp.tm_mday = date.day;
        time_temp.tm_mon = date.month - 1;
        time_temp.tm_year = date.year - 1900 + 2000;
        *((time_t *)args) = mktime(&time_temp);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:

        rt_enter_critical();
        /* converts calendar time time into local time. */
        pNow = localtime((const time_t *)args);
        /* copy the statically located variable */
        memcpy(&time_temp, pNow, sizeof(struct tm));
        /* unlock scheduler. */
        rt_exit_critical();

        time.hour = time_temp.tm_hour;
        time.minute = time_temp.tm_min;
        time.second = time_temp.tm_sec;
        date.year = time_temp.tm_year + 1900 - 2000;
        date.month = time_temp.tm_mon + 1;
        date.day = time_temp.tm_mday;
        ald_rtc_set_time(&time, RTC_FORMAT_DEC);
        ald_rtc_set_date(&date, RTC_FORMAT_DEC);
        /* start RTC */
        RTC_UNLOCK();
        SET_BIT(RTC->CON, RTC_CON_GO_MSK);
        RTC_LOCK();
        break;

    case RT_DEVICE_CTRL_RTC_GET_ALARM:
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:
        break;

    default:
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops es32f0_rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    es32f0_rtc_control
};
#endif

int rt_hw_rtc_init(void)
{
    rt_err_t ret = RT_EOK;
    static struct rt_device rtc_dev;
    rtc_init_t rtc_initstruct;

    /* enable external 32.768kHz */
    CMU_LOSC_ENABLE();
    ald_cmu_losc_safe_config(ENABLE);
    /* set default time */
    RTC_UNLOCK();
    WRITE_REG(RTC->TIME, 0x134251);
    WRITE_REG(RTC->DATE, 0x1190401);
    RTC_LOCK();
    /* RTC function initialization */
    rtc_initstruct.hour_format = RTC_HOUR_FORMAT_24;
    rtc_initstruct.asynch_pre_div = 0;
    rtc_initstruct.synch_pre_div = 32767;
    rtc_initstruct.output = RTC_OUTPUT_DISABLE;
    __rtc_init(&rtc_initstruct);

    rtc_dev.type = RT_Device_Class_RTC;
    rtc_dev.rx_indicate = RT_NULL;
    rtc_dev.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    rtc_dev.ops = &es32f0_rtc_ops;
#else
    rtc_dev.init = RT_NULL;
    rtc_dev.open = RT_NULL;
    rtc_dev.close = RT_NULL;
    rtc_dev.read = RT_NULL;
    rtc_dev.write = RT_NULL;
    rtc_dev.control = es32f0_rtc_control;
#endif

    rtc_dev.user_data = RTC;

    ret = rt_device_register(&rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif
