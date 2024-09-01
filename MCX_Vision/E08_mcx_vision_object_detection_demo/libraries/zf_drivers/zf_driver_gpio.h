/*********************************************************************************************************************
* MCX Vision Opensourec Library ����MCX Vision ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2024 SEEKFREE ��ɿƼ�
* 
* ���ļ��� MCX Vision ��Դ���һ����
* 
* MCX Vision ��Դ�� ��������
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
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_driver_gpio
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.38a
* ����ƽ̨          MCX Vision
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#ifndef _zf_driver_gpio_h_
#define _zf_driver_gpio_h_

#include "MCXN947_cm33_core0.h"
#include "zf_common_typedef.h"
#include "fsl_port.h"
#include "fsl_gpio.h"


typedef struct gpio_pin_struct// GPIO
{
    GPIO_Type       *gpio;    
    uint32          pin;
}gpio_struct;

typedef enum
{
    PULL_UP = 0,    // ����
    PULL_DOWN,      // ����
    OPEN_DTAIN      // ��©
}gpio_mode_enum;

typedef enum // ö�ٶ˿ڷ���
{
    GPI         = 0x00, // ����ܽ����뷽��      
    GPO         = 0x01, // ����ܽ��������
}gpio_dir_enum;

typedef enum // ö�ٶ˿ڵ�ƽ
{
    GPIO_LOW    = 0x00, // ����ܽų�ʼ����ƽΪ��      
    GPIO_HIGH   = 0x01, // ����ܽų�ʼ����ƽΪ��
}gpio_level_enum;




void    gpio_set_dir        (gpio_struct gpio_t, gpio_dir_enum dir);
void    gpio_set_level      (gpio_struct gpio_t, uint8 dat);
uint8   gpio_get_level      (gpio_struct gpio_t);
void    gpio_toggle_level   (gpio_struct gpio_t);
void    gpio_init           (gpio_struct gpio_t, gpio_dir_enum dir, uint8 dat, gpio_mode_enum mode);


#define     gpio_low(gpio_t)               gpio_set_level(gpio_t, 0)
#define     gpio_high(gpio_t)              gpio_set_level(gpio_t, 1)


#endif
