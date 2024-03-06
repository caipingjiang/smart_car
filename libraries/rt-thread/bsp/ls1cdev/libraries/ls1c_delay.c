/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     ��Ϊ��       first version
 */


#include "ls1c_clock.h"




/*
 * ��ʱָ��ʱ�䣬��λms
 * @j ��ʱʱ�䣬��λms
 */
void delay_ms(int j)
{
    int k_max = clk_get_cpu_rate()/1000/92;  // ����1000��ʾms������һ������Ϊʵ���õľ���ֵ
    int k = k_max;

    for ( ; j > 0; j--)
    {
        for (k = k_max; k > 0; k--)
        {
            __asm__ ("nop");        // ע�⣬���������������࣬����ᱻ�Ż���
        }
    }

    return ;
}


/*
 * ��ʱָ��ʱ�䣬��λus
 * @n ��ʱʱ�䣬��λus
 */
void delay_us(int n)
{
    int count_1us = 252000000 / 1000000 / 84;           // ��ʱ1us��ѭ������
                    // 252000000ΪcpuƵ�ʣ�����1000000��ʾ��ʱ��λΪus��92Ϊʵ���õľ���ֵ
    int count_max;                                      // ��ʱn΢���ѭ������
    int tmp;

    // ΢��
    count_max = n * count_1us;
    if (10 >= n)                // <=10us
    {
        count_max = count_max / 3;
    }
    else if (100 >= n)          // <= 100us
    {
        count_max = count_max - count_max / 5;
    }
    else                        // > 100us
    {
        count_max = count_max - count_max / 10;
    }

    // ��ʱ
    for (tmp = count_max; tmp > 0; tmp--)
    {
        __asm__ ("nop");        // ע�⣬���������������࣬����ᱻ�Ż���            
    }

    return ;
}


/*
 * ��ʱָ��ʱ�䣬��λs
 * @i ��ʱʱ�䣬��λs
 */
void delay_s(int i)
{
    for ( ; i > 0; i--)
    {
        delay_ms(1000);
    }

    return ;
}



