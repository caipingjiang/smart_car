 /*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *                             first version
 */
// Ӳ����ʱ��Դ��

#include <ls1c.h>  
#include "ls1c_public.h"
#include "ls1c_pin.h"
#include "ls1c_clock.h"
#include "ls1c_regs.h"
#include "ls1c_pwm.h"
#include "ls1c_timer.h"


// ��ʱ���м�����(CNTR��HRC��LRC)�����ֵ
#define TIMER_COUNTER_MAX               (0xffffff)



/*
 * ��ȡָ����ʱ���ļĴ�������ַ
 * @timer Ӳ����ʱ��
 * @ret ����ַ
 */
unsigned int timer_get_reg_base(ls1c_timer_t timer)
{
    unsigned int reg_base = 0;

    switch (timer)
    {
        case TIMER_PWM0:
            reg_base = LS1C_REG_BASE_PWM0;
            break;

        case TIMER_PWM1:
            reg_base = LS1C_REG_BASE_PWM1;
            break;

        case TIMER_PWM2:
            reg_base = LS1C_REG_BASE_PWM2;
            break;

        case TIMER_PWM3:
            reg_base = LS1C_REG_BASE_PWM3;
            break;
    }

    return reg_base;
}


/*
 * ��ʼ����ʱ��������ʼ��ʱ
 * @timer_info ��ʱ���Ͷ�ʱʱ����Ϣ
 */
void timer_init(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // �Ĵ�������ַ
    unsigned long timer_clk = 0;            // Ӳ����ʱ����ʱ��
    unsigned long tmp;
    unsigned int ctrl = 0;                  // ���ƼĴ����еĿ�����Ϣ
    
    // �ж����
    if (NULL == timer_info)
    {
        return ;
    }

    /*
     * �Ѷ�ʱʱ�任��Ϊ��������ֵ
     * ������ֵ = ��ʱ����ʱ�� * ��ʱʱ��(��λns) / 1000000000
     * ��о1c�Ķ�ʱ��ʱ��ΪAPBʱ�ӣ��ﵽ126Mhz��
     * Ϊ���������̷����������������ֶ��Ż�����ļ���ʽ��Ҳ���Բ��ø�������
     */
    timer_clk = clk_get_apb_rate();
    tmp = (timer_clk / 1000000) * (timer_info->time_ns / 1000);     // ��1000000000���Ϊ1000000��1000
    tmp = MIN(tmp, TIMER_COUNTER_MAX);

    // ���ƼĴ�����Ϣ
    ctrl = (1 << LS1C_PWM_INT_LRC_EN)
           | (0 << LS1C_PWM_INT_HRC_EN)
           | (0 << LS1C_PWM_CNTR_RST)
           | (0 << LS1C_PWM_INT_SR)
           | (1 << LS1C_PWM_INTEN)
           | (1 << LS1C_PWM_SINGLE)
           | (1 << LS1C_PWM_OE)
           | (1 << LS1C_PWM_CNT_EN);

    // ���ø����Ĵ���
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // ��ȡ�Ĵ�������ַ
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC));
    reg_write_32(tmp--,                 (volatile unsigned int *)(timer_reg_base + LS1C_PWM_LRC));
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR));
    reg_write_32(ctrl,                  (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}


/*
 * �ж�ָ����ʱ���Ƿ�ʱ(ʵ�ֶ�ʱ)
 * @timer_info ��ʱ��
 * @ret TRUE or FALSE
 */
BOOL timer_is_time_out(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // �Ĵ�������ַ
    unsigned int ctrl;                      // ���ƼĴ�����ֵ
    
    // �ж����
    if (NULL == timer_info)
    {
        return FALSE;
    }

    // ��ȡ���ƼĴ���
    timer_reg_base = timer_get_reg_base(timer_info->timer);
    ctrl = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    // �ж��ж�״̬λ
    if (ctrl & (1 << LS1C_PWM_INT_SR))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}



/*
 * ֹͣ��ʱ��
 * @timer_info ��ʱ��
 */
void timer_stop(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;
    
    // �ж����
    if (NULL == timer_info)
    {
        return ;
    }

    timer_reg_base = timer_get_reg_base(timer_info->timer);
    reg_write_32(0, (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}

/*
 * ��ȡ��ʱ���ӳ�ʼ�������ڵ�ʱ��(ʵ�ּ�ʱ����)����λns
 * @timer_info Ӳ����ʱ��
 * @ret ʱ�䣬��λns
 */
unsigned long timer_get_time_ns(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;
    unsigned int cntr = 0;                  // �Ĵ���CNTR��ֵ
    unsigned long time_ns = 0;              // ʱ�䣬��λns
    unsigned long timer_clk = 0;            // ��ʱ��ʱ��

    // ��ȡ�Ĵ���CNTR��ֵ
    timer_reg_base = timer_get_reg_base(timer_info->timer);
    cntr = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR));

    /*
     * ��CNTRֵ����Ϊʱ�䣬��λus
     * ʱ�� = (������ֵCNTR * 1000000000) / ��ʱ��ʱ��Ƶ��
     * Ϊ�������������ֶ��Ż���ʽΪ ʱ�� = (������ֵCNTR * 1000) / (��ʱ��ʱ��Ƶ�� / 1000000)
     */
    timer_clk = clk_get_apb_rate();
    time_ns = (cntr * 1000 ) / (timer_clk /1000000);
//    printf("[%s] time_us=%lu, cntr=%d, timer_clk=%d\n", __FUNCTION__, time_ns, cntr, timer_clk);

    return time_ns;
}

/*
 * ��ӡtimer��ؼĴ�����ֵ
 * @timer_info Ӳ����ʱ��
 */
void timer_print_regs(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;

    timer_reg_base = timer_get_reg_base(timer_info->timer);
    printf("CNTR=0x%x, HRC=0x%x, LRC=0x%x, CTRL=0x%x\n",
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR)),
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC)),
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_LRC)),
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL)));

    return ;
}

/*
 * ��ʱ���ж���
 * @timer_info ��ʱ����Ϣ
 */
void timer_int_clr(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // �Ĵ�������ַ
    unsigned int ctrl ;  
    
    // �ж����
    if (NULL == timer_info)
    {
        return ;
    }
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // ��ȡ�Ĵ�������ַ
    ctrl = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl | (1<<LS1C_PWM_INT_SR) ;
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl & (~(1<<LS1C_PWM_INT_SR))  ;
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}
/*
 * ��ʱ��������
 * @timer_info ��ʱ����Ϣ
 */
void timer_cnt_clr(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // �Ĵ�������ַ
    unsigned int ctrl ;  
    
    // �ж����
    if (NULL == timer_info)
    {
        return ;
    }
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // ��ȡ�Ĵ�������ַ
    ctrl = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl | (1<<LS1C_PWM_CNTR_RST);
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl & (~(1<<LS1C_PWM_CNTR_RST)) ;
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}

/*
 * ��ʼ����ʱ��������ʼ�ж϶�ʱ
 * @timer_info ��ʱ���Ͷ�ʱʱ����Ϣ
 * @hrc ���ж� lrc ���ж� Ϊ1�򿪣�Ϊ0�ر�
*/
void timer_int_init(timer_info_t *timer_info, int hrc, int lrc)
{
    unsigned int timer_reg_base = 0;        // �Ĵ�������ַ
    unsigned long timer_clk = 0;            // Ӳ����ʱ����ʱ��
    unsigned long h_value, l_value;
    unsigned int ctrl = 0;                  // ���ƼĴ����еĿ�����Ϣ
    
    // �ж����
    if (NULL == timer_info)
    {
        return ;
    }

    /*
     * �Ѷ�ʱʱ�任��Ϊ��������ֵ
     * ������ֵ = ��ʱ����ʱ�� * ��ʱʱ��(��λns) / 1000000000
     * ��о1c�Ķ�ʱ��ʱ��ΪAPBʱ�ӣ��ﵽ126Mhz��
     * Ϊ���������̷����������������ֶ��Ż�����ļ���ʽ��Ҳ���Բ��ø�������
     */
    timer_clk = clk_get_apb_rate();
    l_value = (timer_clk / 1000000) * (timer_info->time_ns / 1000);     // ��1000000000���Ϊ1000000��1000
    l_value = MIN(l_value, TIMER_COUNTER_MAX);
    h_value = (timer_clk / 1000000) * (timer_info->time_h_ns / 1000);     // ��1000000000���Ϊ1000000��1000
    h_value = MIN(h_value, l_value);

    // ���ƼĴ�����Ϣ
    ctrl = (lrc << LS1C_PWM_INT_LRC_EN)
           | (hrc << LS1C_PWM_INT_HRC_EN)
           | (0 << LS1C_PWM_CNTR_RST)
           | (0 << LS1C_PWM_INT_SR)
           | (1 << LS1C_PWM_INTEN)
           | (1 << LS1C_PWM_SINGLE)
           | (1 << LS1C_PWM_OE)
           | (1 << LS1C_PWM_CNT_EN);

    // ���ø����Ĵ���
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // ��ȡ�Ĵ�������ַ
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC));
    reg_write_32(l_value--,                 (volatile unsigned int *)(timer_reg_base + LS1C_PWM_LRC));
    reg_write_32(h_value--,                 (volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC));
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR));
    reg_write_32(ctrl,                  (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}
