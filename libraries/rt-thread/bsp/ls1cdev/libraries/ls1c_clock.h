/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     ��Ϊ��       first version
 */


#ifndef __OPENLOONGSON_CLOCK_H
#define __OPENLOONGSON_CLOCK_H



/*
 * ��ȡPLLƵ��
 * @ret PLLƵ��
 */
unsigned long clk_get_pll_rate(void);


/*
 * ��ȡCPUƵ��
 * @ret CPUƵ��
 */
unsigned long clk_get_cpu_rate(void);



/*
 * ��ȡDDRƵ��
 * @ret DDRƵ��
 */
unsigned long clk_get_ddr_rate(void);


/*
 * ��ȡAPBƵ��
 * @ret APBƵ��
 */
unsigned long clk_get_apb_rate(void);


/*
 * ��ȡDCƵ��
 * @ret DCƵ��
 */
unsigned long clk_get_dc_rate(void);



#endif

