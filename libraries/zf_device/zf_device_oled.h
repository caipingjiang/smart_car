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
* �ļ�����          zf_device_oled
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
*                   ģ��ܽ�             ��Ƭ���ܽ�
*                   D0                  �鿴 zf_device_oled.h �� OLED_D0_PIN �궨��
*                   D1                  �鿴 zf_device_oled.h �� OLED_D1_PIN �궨��
*                   RES                 �鿴 zf_device_oled.h �� OLED_RES_PIN �궨��
*                   DC                  �鿴 zf_device_oled.h �� OLED_DC_PIN �궨��
*                   CS                  �鿴 zf_device_oled.h �� OLED_CS_PIN �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_oled_h_
#define _zf_device_oled_h_

#include "zf_common_typedef.h"

#define OLED_USE_SOFT_SPI               (0 )                                    // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if OLED_USE_SOFT_SPI                                                           // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
#define OLED_SOFT_SPI_DELAY             (1 )                                    // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define OLED_D0_PIN                     (B0)                                    // ��� SPI SCK ����
#define OLED_D1_PIN                     (B1)                                    // ��� SPI MOSI ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define OLED_SPI_SPEED                  (40 * 1000 * 1000)                      // Ӳ�� SPI ����
#define OLED_SPI                        (SPI_3)                                 // Ӳ�� SPI ��
#define OLED_D0_PIN                     (SPI3_SCK_B0 )                          // Ӳ�� SPI SCK ����
#define OLED_D1_PIN                     (SPI3_MOSI_B1)                          // Ӳ�� SPI MOSI ����
//====================================================Ӳ�� SPI ����====================================================
#endif

#define OLED_RES_PIN                    (B2 )                                   // Һ����λ���Ŷ���
#define OLED_DC_PIN                     (C19)                                   // Һ������λ���Ŷ���
#define OLED_CS_PIN                     (B3 )                                   // CS Ƭѡ����
                                         
#define OLED_BRIGHTNESS                 (0x7f)                                  // ����OLED���� Խ��Խ�� ��Χ0-0XFF
#define OLED_DEFAULT_DISPLAY_DIR        (OLED_CROSSWISE)                        // Ĭ�ϵ���ʾ����
#define OLED_DEFAULT_DISPLAY_FONT       (OLED_6X8_FONT )                        // Ĭ�ϵ�����ģʽ

#define OLED_RES(x)                     ((x) ? (gpio_high(OLED_RES_PIN)) : (gpio_low(OLED_RES_PIN)))
#define OLED_DC(x)                      ((x) ? (gpio_high(OLED_DC_PIN)) : (gpio_low(OLED_DC_PIN)))
#define OLED_CS(x)                      ((x) ? (gpio_high(OLED_CS_PIN)) : (gpio_low(OLED_CS_PIN)))

typedef enum
{
    OLED_CROSSWISE                      = 0,                                    // ����ģʽ
    OLED_CROSSWISE_180                  = 1,                                    // ����ģʽ  ��ת180
}oled_dir_enum;

typedef enum
{
    OLED_6X8_FONT                       = 0,                                    // 6x8      ����
    OLED_8X16_FONT                      = 1,                                    // 8x16     ����
    OLED_16X16_FONT                     = 2,                                    // 16x16    ���� Ŀǰ��֧��
}oled_font_size_enum;

#define OLED_X_MAX                      (128)
#define OLED_Y_MAX                      (64 )

void    oled_clear                      (void);
void    oled_full                       (const uint8 color);
void    oled_set_dir                    (oled_dir_enum dir);
void    oled_set_font                   (oled_font_size_enum font);
void    oled_draw_point                 (uint16 x, uint16 y, const uint8 color);

void    oled_show_string                (uint16 x, uint16 y, const char ch[]);
void    oled_show_int                   (uint16 x, uint16 y, const int32 dat, uint8 num);
void    oled_show_uint                  (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    oled_show_float                 (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    oled_show_binary_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    oled_show_gray_image            (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);

void    oled_show_wave                  (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    oled_show_chinese               (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number);

//-------------------------------------------------------------------------------------------------------------------
// �������     OLED 128*64 ��ʾС���ͼ��
// ����˵��     p               ͼ������
// ���ز���     void
// ʹ��ʾ��     oled_displayimage7725(ov7725_image_binary[0]);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define oled_displayimage7725(p)        (oled_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, 128, 64))

//-------------------------------------------------------------------------------------------------------------------
// �������     OLED 128*64 ��ʾ�����ͼ�� ����ֵ��
// ����˵��     p               ͼ������
// ����˵��     x               ��ֵ����ʾ��ֵ
// ���ز���     void
// ʹ��ʾ��     oled_displayimage03x(mt9v03x_image[0], 127);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define oled_displayimage03x(p,x)       (oled_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, 128, 64, (x)))

void    oled_init                       (void);

#endif
