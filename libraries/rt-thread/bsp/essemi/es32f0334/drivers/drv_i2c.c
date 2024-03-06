/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-03-19     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_i2c.h"
#include <ald_i2c.h>
#include <ald_gpio.h>

#ifdef RT_USING_I2C

#define TIMEOUT 0x0FFF
/* I2C struct definition */
static i2c_handle_t _h_i2c0, _h_i2c1;

static void _i2c_init(void)
{
    gpio_init_t gpio_instruct;

    /* Initialize I2C Pin */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;
    gpio_instruct.odos = GPIO_PUSH_PULL;
    gpio_instruct.pupd = GPIO_PUSH_UP;
    gpio_instruct.odrv = GPIO_OUT_DRIVE_NORMAL;
    gpio_instruct.flt  = GPIO_FILTER_DISABLE;
    gpio_instruct.type = GPIO_TYPE_CMOS;
    gpio_instruct.func = GPIO_FUNC_5;

#ifdef BSP_USING_I2C0
    /* Initialize I2C Function */
    _h_i2c0.perh = I2C0;
    _h_i2c0.init.clk_speed    = 100000;
    _h_i2c0.init.duty         = I2C_DUTYCYCLE_2;
    _h_i2c0.init.own_addr1    = 0x0A;
    _h_i2c0.init.addr_mode    = I2C_ADDR_7BIT;
    _h_i2c0.init.general_call = I2C_GENERALCALL_DISABLE;
    _h_i2c0.init.no_stretch   = I2C_NOSTRETCH_ENABLE;

    ald_i2c_reset(&_h_i2c0);
    ald_i2c_init(&_h_i2c0);
    /* I2C0_SCL->PB8,  I2C0_SDA->PB9 */
    ald_gpio_init(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, &gpio_instruct);
#endif

#ifdef BSP_USING_I2C1
    /* Initialize i2c function */
    _h_i2c1.perh = I2C1;
    _h_i2c1.init.clk_speed    = 100000;
    _h_i2c1.init.duty         = I2C_DUTYCYCLE_2;
    _h_i2c1.init.own_addr1    = 0xA0;
    _h_i2c1.init.addr_mode    = I2C_ADDR_7BIT;
    _h_i2c1.init.general_call = I2C_GENERALCALL_DISABLE;
    _h_i2c1.init.no_stretch   = I2C_NOSTRETCH_ENABLE;

    ald_i2c_reset(&_h_i2c1);
    ald_i2c_init(&_h_i2c1);
    /* I2C1_SCL->PB10, I2C1_SDA->PB11 */
    ald_gpio_init(GPIOB, GPIO_PIN_10 | GPIO_PIN_11, &gpio_instruct);
#endif
}

static rt_size_t es32f0_master_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags & RT_I2C_RD)
        {
            if (ald_i2c_master_recv(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT) != 0)
            {
                i2c_dbg("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
        else
        {
            if (ald_i2c_master_send(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT) != 0)
            {
                i2c_dbg("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
    }

    ret = i;

out:
    i2c_dbg("send stop condition\n");

    return ret;
}

const struct rt_i2c_bus_device_ops es32f0_i2c_ops =
{
    es32f0_master_xfer,
    RT_NULL,
    RT_NULL,
};

int rt_hw_i2c_init(void)
{
    _i2c_init();

#ifdef BSP_USING_I2C0
    /* define i2c Instance */
    static struct rt_i2c_bus_device _i2c_device0;
    rt_memset((void *)&_i2c_device0, 0, sizeof(struct rt_i2c_bus_device));
    _i2c_device0.ops = &es32f0_i2c_ops;
    _i2c_device0.priv = &_h_i2c0;
    rt_i2c_bus_device_register(&_i2c_device0, "i2c0");
#endif

#ifdef BSP_USING_I2C1
    /* define i2c Instance */
    static struct rt_i2c_bus_device _i2c_device1;
    rt_memset((void *)&_i2c_device1, 0, sizeof(struct rt_i2c_bus_device));
    _i2c_device1.ops = &es32f0_i2c_ops;
    _i2c_device1.priv = &_h_i2c1;
    rt_i2c_bus_device_register(&_i2c_device1, "i2c1");
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
