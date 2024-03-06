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

#include "zf_driver_exti.h"


#define GPIO_EXTI_CONFIG         SPEED_100MHZ | HYS_EN | PULL_EN | PULLUP_100K   // GPIO�ж����Ų�������

//-------------------------------------------------------------------------------------------------------------------
// �������     EXTI �ж�ʹ��
// ����˵��     pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     exti_enable(B0);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void exti_enable (gpio_pin_enum pin)
{
    GPIO_PortEnableInterrupts(PORTPTR[pin >> 5],1 << (pin & 0x1f));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     EXTI �ж�ʧ��
// ����˵��     pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ���ز���     void
// ʹ��ʾ��     exti_disable(B0);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void exti_disable (gpio_pin_enum pin)
{
    GPIO_PortDisableInterrupts(PORTPTR[pin >> 5],1 << (pin & 0x1f)); 
}

//-------------------------------------------------------------------------------------------------------------------
// �������     EXTI �жϳ�ʼ��
// ����˵��     pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// ����˵��     trigger         ѡ�񴥷����źŷ�ʽ [EXTI_TRIGGER_RISING/EXTI_TRIGGER_FALLING/EXTI_TRIGGER_BOTH]
// ���ز���     void
// ʹ��ʾ��     exti_init(B0, EXTI_TRIGGER_RISING);
// ��ע��Ϣ     ͬһ�±�����Ų���ͬʱ��ʼ��Ϊ�ⲿ�ж����� ���� A0 �� B0 ����ͬʱ��ʼ��Ϊ�ⲿ�ж�����
//-------------------------------------------------------------------------------------------------------------------
void exti_init (gpio_pin_enum pin, exti_trigger_enum trigger)
{
    gpio_pin_config_t gpio_config;
    
    gpio_iomuxc(pin, GPIO_EXTI_CONFIG);
    
    gpio_config.direction = kGPIO_DigitalInput;         
    gpio_config.interruptMode = (gpio_interrupt_mode_t)trigger;  
    GPIO_PinInit(PORTPTR[pin >> 5], pin & 0x1f, &gpio_config);                      // ��ʼ��GPIO
    GPIO_PortEnableInterrupts(PORTPTR[pin >> 5],1 << (pin & 0x1f));                 // ��GPIO���ж�

    EnableIRQ((IRQn_Type)((IRQn_Type)((pin >> 4) - 2) + GPIO1_Combined_0_15_IRQn)); // ʹ��IRQ
    
    //NVIC_SetPriority((IRQn_Type)((IRQn_Type)((pin>>4)-2) + GPIO1_Combined_0_15_IRQn),0);// ���ȼ����� ��Χ0-15 ԽС���ȼ�Խ��
}
