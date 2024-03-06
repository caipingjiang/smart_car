/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     ��Ϊ��       first version
 */

// ���Ź���(��ͨgpio��pwm�����õ�)��ؽӿ�

#ifndef __OPENLOONGSON_PIN_H
#define __OPENLOONGSON_PIN_H


// ������;
typedef enum
{
    PIN_PURPOSE_GPIO = 0,               // ����������ͨgpio
    PIN_PURPOSE_OTHER,                  // ����������������(��gpio)
}pin_purpose_t;


// ���Ÿ���
typedef enum
{
    PIN_REMAP_FIRST = 0,                // ��һ����
    PIN_REMAP_SECOND,                   // �ڶ�����
    PIN_REMAP_THIRD,                    // ��������
    PIN_REMAP_FOURTH,                   // ���ĸ���
    PIN_REMAP_FIFTH,                    // ���帴��
    PIN_REMAP_DEFAULT,                //ȱʡ����
}pin_remap_t;


/*
 * ��ָ��pin����Ϊָ����;(��ͨgpio����gpio)
 * @gpio gpio���ű��
 * @purpose ��;
 */
void pin_set_purpose(unsigned int gpio, pin_purpose_t purpose);


/*
 * ����ָ��pinΪ��n����
 * @gpio gpio���
 * @remap ��n����
 */
void pin_set_remap(unsigned int gpio, pin_remap_t remap);


#endif

