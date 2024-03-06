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
* �ļ�����          zf_device_absolute_encoder
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
*                   // Ӳ�� SPI ����
*                   SCLK                �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_SCLK_PIN �궨��
*                   MOSI                �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_MOSI_PIN �궨��
*                   MISO                �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_MISO_PIN �궨��
*                   CS                  �鿴 zf_device_absolute_encoder.h �� ABSOLUTE_ENCODER_CS_PIN �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_absolute_encoder_h_
#define _zf_device_absolute_encoder_h_

#include "zf_common_typedef.h"

#define ABSOLUTE_ENCODER_USE_SOFT_SPI       (0)                                 // Ĭ��ʹ��Ӳ�� SPI ��ʽ����
#if ABSOLUTE_ENCODER_USE_SOFT_SPI                                               // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
#define ABSOLUTE_ENCODER_SOFT_SPI_DELAY     (1)                                 // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define ABSOLUTE_ENCODER_SCLK_PIN           (C23)                               // Ӳ�� SPI SCK ����
#define ABSOLUTE_ENCODER_MOSI_PIN           (C22)                               // Ӳ�� SPI MOSI ����
#define ABSOLUTE_ENCODER_MISO_PIN           (C21)                               // Ӳ�� SPI MISO ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define ABSOLUTE_ENCODER_SPI_SPEED          (10 * 1000 * 1000)                  // Ӳ�� SPI ����
#define ABSOLUTE_ENCODER_SPI                (SPI_4)                             // Ӳ�� SPI ��
#define ABSOLUTE_ENCODER_SCLK_PIN           (SPI4_SCK_C23)                      // Ӳ�� SPI SCK ����
#define ABSOLUTE_ENCODER_MOSI_PIN           (SPI4_MOSI_C22)                     // Ӳ�� SPI MOSI ����
#define ABSOLUTE_ENCODER_MISO_PIN           (SPI4_MISO_C21)                     // Ӳ�� SPI MISO ����
//====================================================Ӳ�� SPI ����====================================================
#endif

#define ABSOLUTE_ENCODER_CS_PIN             (C20)
#define ABSOLUTE_ENCODER_CSN(x)             ((x) ? (gpio_high(ABSOLUTE_ENCODER_CS_PIN)): (gpio_low(ABSOLUTE_ENCODER_CS_PIN)))

#define ABSOLUTE_ENCODER_TIMEOUT_COUNT      (100)
#define ABSOLUTE_ENCODER_DEFAULT_ZERO       (0)

//====================================================�Ƕȴ���������====================================================
#define ABSOLUTE_ENCODER_SPI_W              (0x80)
#define ABSOLUTE_ENCODER_SPI_R              (0x40)

#define ABSOLUTE_ENCODER_ZERO_L_REG         (0x00)
#define ABSOLUTE_ENCODER_ZERO_H_REG         (0x01)
#define ABSOLUTE_ENCODER_DIR_REG            (0X09)
//====================================================�Ƕȴ���������====================================================

int16       absolute_encoder_get_location   (void);
int16       absolute_encoder_get_offset     (void);
uint8       absolute_encoder_init           (void);

#endif
