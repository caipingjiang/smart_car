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
* �ļ�����          zf_device_tsl1401
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
/*********************************************************************************************************************
* ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�            ��Ƭ���ܽ�
*                   CLK                 �鿴 zf_device_tsl1401.h �� TSL1401_CLK_PIN �궨��
*                   SI                  �鿴 zf_device_tsl1401.h �� TSL1401_SI_PIN �궨��
*                   AO[x]               �鿴 zf_device_tsl1401.h �� TSL1401_AO_PINx �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_tsl1401_h_
#define _zf_device_tsl1401_h_

#include "zf_common_typedef.h"
#include "zf_driver_uart.h"

#define TSL1401_AO_PIN          (ADC1_CH0_B27)                                  // ��Ӧ��һ�� TSL1401 �� AO ����
#define TSL1401_AO_PIN2         (ADC1_CH1_B12)                                  // ��Ӧ�ڶ��� TSL1401 �� AO ����

// TSL1401 �Ŀ������Ŷ��� ��� TSL1401 ���齫��������ֱ�Ӳ���
#define TSL1401_CLK_PIN         (B2)                                            // TSL1401 �� CLK ���Ŷ���
#define TSL1401_SI_PIN          (B3)                                            // TSL1401 �� SI ���Ŷ���
#define TSL1401_CLK(x)          ((x) ? (gpio_high(TSL1401_CLK_PIN)) : (gpio_low(TSL1401_CLK_PIN)))
#define TSL1401_SI(x)           ((x) ? (gpio_high(TSL1401_SI_PIN)) : (gpio_low(TSL1401_SI_PIN)))

// TSL1401 �����ڲɼ����ֶ��� ʹ�õ��ĸ� PIT ��Ҫ��  �����ĸ� PIT ���жϷ�������
#define TSL1401_EXPOSURE_TIME   (10 )                                           // ���� TSL1401 �ع�ʱ�� ��λ MS
#define TSL1401_PIT_INDEX       (PIT_CH3)                                       // ʹ�������ж�
#define TSL1401_AD_RESOLUTION   (ADC_8BIT)                                      // ADC ���� 8bit
#define TSL1401_DATA_LEN        (128 )                                          // TSL1401 ���ݳ���

extern uint16 tsl1401_data[2][TSL1401_DATA_LEN];                                // TSL1401 ���ݴ������
extern uint8 tsl1401_finish_flag;                                               // TSL1401 ���ݲɼ���ɱ�־

void tsl1401_collect_pit_handler    (void);
void tsl1401_send_data              (uart_index_enum uart_n, uint8 index);
void tsl1401_init                   (void);

#endif
