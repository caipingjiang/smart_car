/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_exti
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#ifndef _zf_driver_exti_h_
#define _zf_driver_exti_h_

#include "zf_common_typedef.h"
#include "zf_driver_gpio.h"



typedef enum{                                                                   // ö�� EXTI �����ź�  ��ö�ٶ��岻�����û��޸�
    EXTI_TRIGGER_LOW = 1,                                                       // �͵�ƽ����ģʽ
    EXTI_TRIGGER_HIGH,                                                          // �ߵ�ƽ����ģʽ
    EXTI_TRIGGER_RISING,                                                        // �����ش���ģʽ
    EXTI_TRIGGER_FALLING,                                                       // �½��ش���ģʽ
    EXTI_TRIGGER_BOTH,                                                          // ˫���ش���ģʽ
}exti_trigger_enum;



#define exti_flag_get(pin)      ((GPIO_GetPinsInterruptFlags(PORTPTR[pin>>5]) >> (pin&0x1f)) & 0x01)
#define exti_flag_clear(pin)    (GPIO_ClearPinsInterruptFlags(PORTPTR[pin>>5], (uint32)1<<(pin&0x1f)))

void    exti_enable             (gpio_pin_enum pin);
void    exti_disable            (gpio_pin_enum pin);
void    exti_init               (gpio_pin_enum pin, exti_trigger_enum trigger);

#endif
