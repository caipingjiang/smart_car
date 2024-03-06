/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     ��Ϊ��       first version
 */


#ifndef __OPENLOONGSON_PWM_H
#define __OPENLOONGSON_PWM_H


// pwm���Ŷ���
#define LS1C_PWM0_GPIO06                    (6)         // gpio06����pwm0
#define LS1C_PWM0_GPIO04                    (4)         // gpio04����Ϊpwm0
#define LS1C_PWM1_GPIO92                    (92)        // gpio92����pwm1
#define LS1C_PWM1_GPIO05                    (5)         // gpio05����Ϊpwm1
#define LS1C_PWM2_GPIO52                    (52)        // gpio52����Ϊpwm2
#define LS1C_PWM2_GPIO46                    (46)        // gpio46����Ϊpwm2
#define LS1C_PWM3_GPIO47                    (47)        // gpio47����Ϊpwm3
#define LS1C_PWM3_GPIO53                    (53)        // gpio53����Ϊpwm3
// ...����һЩgpio���Ը���Ϊgpio�ģ�����Ҫ�����Լ����



// pwm���ƼĴ�����ÿ��bit
#define LS1C_PWM_INT_LRC_EN                 (11)        // ������������ж�ʹ��
#define LS1C_PWM_INT_HRC_EN                 (10)        // ������������ж�ʹ��
#define LS1C_PWM_CNTR_RST                   (7)         // ʹ��CNTR����������
#define LS1C_PWM_INT_SR                     (6)         // �ж�״̬λ
#define LS1C_PWM_INTEN                      (5)         // �ж�ʹ��λ
#define LS1C_PWM_SINGLE                     (4)         // ���������λ
#define LS1C_PWM_OE                         (3)         // �������ʹ��
#define LS1C_PWM_CNT_EN                     (0)         // ��������ʹ��


// Ӳ��pwm����ģʽ
enum
{
    // ����ģʽ--�������pwm����
    PWM_MODE_NORMAL = 0,
    
    // ������ģʽ��ÿ�ε���ֻ����һ�����壬���ü���������pwm����
    PWM_MODE_PULSE
};


// Ӳ��pwm��Ϣ
typedef struct
{
    unsigned int gpio;                      // PWMn���ڵ�gpio
    unsigned int mode;                      // ����ģʽ(�����塢��������)
    float duty;                             // pwm��ռ�ձ�
    unsigned long period_ns;                // pwm����(��λns)
}pwm_info_t;




/*
 * ��ʼ��PWMn
 * @pwm_info PWMn����ϸ��Ϣ
 */
void pwm_init(pwm_info_t *pwm_info);


/*
 * ��ֹpwm
 * @pwm_info PWMn����ϸ��Ϣ
 */
void pwm_disable(pwm_info_t *pwm_info);



/*
 * ʹ��PWM
 * @pwm_info PWMn����ϸ��Ϣ
 */
void pwm_enable(pwm_info_t *pwm_info);


#endif

