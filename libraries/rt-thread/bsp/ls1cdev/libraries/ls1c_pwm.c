/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     ��Ϊ��       first version
 */

// ��װӲ��pwm�ӿ�

#include "ls1c_public.h"
#include "ls1c_pin.h"
#include "ls1c_pwm.h"
#include "ls1c_clock.h"
#include "ls1c_regs.h"

// pwm���������
#define PWM_MAX_PERIOD                  (0xFFFFFF)      // ��������ֵ

/*
 * ����gpio��ȡ��Ӧpwm�Ļ���ַ
 * @gpio pwm����
 * @ret pwm����ַ
 */
unsigned int pwm_get_reg_base(unsigned int gpio)
{
    unsigned int reg_base = 0;
    
    switch (gpio)
    {
        case LS1C_PWM0_GPIO06:
        case LS1C_PWM0_GPIO04:
            reg_base = LS1C_REG_BASE_PWM0;
            break;

        case LS1C_PWM1_GPIO92:
        case LS1C_PWM1_GPIO05:
            reg_base = LS1C_REG_BASE_PWM1;
            break;

        case LS1C_PWM2_GPIO52:
        case LS1C_PWM2_GPIO46:
            reg_base = LS1C_REG_BASE_PWM2;
            break;

        case LS1C_PWM3_GPIO47:
        case LS1C_PWM3_GPIO53:
            reg_base = LS1C_REG_BASE_PWM3;
            break;
    }

    return reg_base;
}


/*
 * ��ֹpwm
 * @pwm_info PWMn����ϸ��Ϣ
 */
void pwm_disable(pwm_info_t *pwm_info)
{
    unsigned int pwm_reg_base = 0;
    
    // ������
    if (NULL == pwm_info)
    {
        return ;
    }

    pwm_reg_base = pwm_get_reg_base(pwm_info->gpio);
    reg_write_32(0, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_CTRL));

    return ;
}



/*
 * ʹ��PWM
 * @pwm_info PWMn����ϸ��Ϣ
 */
void pwm_enable(pwm_info_t *pwm_info)
{
    unsigned int pwm_reg_base = 0;
    unsigned int ctrl = 0;

    // ������
    if (NULL == pwm_info)
    {
        return ;
    }

    // ��ȡ����ַ
    pwm_reg_base = pwm_get_reg_base(pwm_info->gpio);

    // ���������
    reg_write_32(0, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_CNTR));

    // ���ÿ��ƼĴ���
    ctrl = (0 << LS1C_PWM_INT_LRC_EN)
           | (0 << LS1C_PWM_INT_HRC_EN)
           | (0 << LS1C_PWM_CNTR_RST)
           | (0 << LS1C_PWM_INT_SR)
           | (0 << LS1C_PWM_INTEN)
           | (0 << LS1C_PWM_OE)
           | (1 << LS1C_PWM_CNT_EN);
    if (PWM_MODE_PULSE == pwm_info->mode)     // ������
    {
        ctrl |= (1 << LS1C_PWM_SINGLE);
    }
    else                            // ��������
    {
        ctrl &= ~(1 << LS1C_PWM_SINGLE);
    }
    reg_write_32(ctrl, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_CTRL));
    
    return ;
}



/*
 * ��ʼ��PWMn
 * @pwm_info PWMn����ϸ��Ϣ
 */
void pwm_init(pwm_info_t *pwm_info)
{
    unsigned int gpio;
    unsigned long pwm_clk = 0;          // pwmģ���ʱ��Ƶ��
    unsigned long tmp = 0;
    unsigned int pwm_reg_base = 0;
    unsigned long period = 0;
    
    // �ж����
    if (NULL == pwm_info)
    {
        // ��ηǷ�����ֱ�ӷ���
        return ;
    }
    gpio = pwm_info->gpio;

    // ������Ӧ��������pwm������gpio
    pin_set_purpose(gpio, PIN_PURPOSE_OTHER);

    // ����
    switch (gpio)
    {
        // ����Ҫ����
        case LS1C_PWM0_GPIO06:
        case LS1C_PWM1_GPIO92:
            break;

        case LS1C_PWM0_GPIO04:          // gpio04�ĵ�������
            pin_set_remap(LS1C_PWM0_GPIO04, PIN_REMAP_THIRD);
            break;

        case LS1C_PWM1_GPIO05:          // gpio05�ĵ�������
            pin_set_remap(LS1C_PWM1_GPIO05, PIN_REMAP_THIRD);
            break;

        case LS1C_PWM2_GPIO52:          // gpio52�ĵ��ĸ���
            pin_set_remap(LS1C_PWM2_GPIO52, PIN_REMAP_FOURTH);
            break;

        case LS1C_PWM2_GPIO46:          // gpio46�ĵ��ĸ���
            pin_set_remap(LS1C_PWM2_GPIO46, PIN_REMAP_FOURTH);
            break;

        case LS1C_PWM3_GPIO47:          // gpio47�ĵ��ĸ���
            pin_set_remap(LS1C_PWM3_GPIO47, PIN_REMAP_FOURTH);
            break;

        case LS1C_PWM3_GPIO53:          // gpio53�ĵ��ĸ���
            pin_set_remap(LS1C_PWM3_GPIO53, PIN_REMAP_FOURTH);
            break;

        default:
            break;
    }

    // ����ռ�ձȺ�pwm���ڼ���Ĵ���HRC��LRC��ֵ
    // ����64λ����ˣ�ֻ�ܵõ���32λ��linux��ȴ���Եõ�64λ�����
    // �ݲ����ԭ���ø����������
    pwm_clk = clk_get_apb_rate();
    period = (1.0 * pwm_clk * pwm_info->period_ns) / 1000000000;
    period = MIN(period, PWM_MAX_PERIOD);       // �������ڲ��ܳ������ֵ
    tmp = period - (period * pwm_info->duty);
    
    // д�Ĵ���HRC��LRC
    pwm_reg_base = pwm_get_reg_base(gpio);
    reg_write_32(--tmp, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_HRC));
    reg_write_32(--period, (volatile unsigned int *)(pwm_reg_base + LS1C_PWM_LRC));

    // д��������
    pwm_enable(pwm_info);
    
    return ;
}

