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
* �ļ�����          zf_device_ips114
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
*                   SCL                  �鿴 zf_device_ips114.h �� IPS114_SCL_PIN �궨��
*                   SDA                  �鿴 zf_device_ips114.h �� IPS114_SDA_PIN �궨��
*                   RST                  �鿴 zf_device_ips114.h �� IPS114_RST_PIN �궨��
*                   DC                   �鿴 zf_device_ips114.h �� IPS114_DC_PIN �궨��
*                   CS                   �鿴 zf_device_ips114.h �� IPS114_CS_PIN �궨��
*                   BLK                  �鿴 zf_device_ips114.h �� IPS114_BLK_PIN �궨��
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ���ֱ��� 135 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips114_h_
#define _zf_device_ips114_h_

#include "zf_common_typedef.h"

#define IPS114_USE_SOFT_SPI             (0)                                     // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if IPS114_USE_SOFT_SPI                                                         // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
#define IPS114_SOFT_SPI_DELAY           (1 )                                    // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define IPS114_SCL_PIN                  (B0)                                    // ��� SPI SCK ����
#define IPS114_SDA_PIN                  (B1)                                    // ��� SPI MOSI ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
#define IPS114_SPI_SPEED                (60 * 1000 * 1000)                      // Ӳ�� SPI ���� ��������Ϊϵͳʱ�Ӷ���Ƶ
#define IPS114_SPI                      (SPI_3)                                 // Ӳ�� SPI ��
#define IPS114_SCL_PIN                  (SPI3_SCK_B0 )                          // Ӳ�� SPI SCK ����
#define IPS114_SDA_PIN                  (SPI3_MOSI_B1)                          // Ӳ�� SPI MOSI ����
//====================================================Ӳ�� SPI ����====================================================
#endif

#define IPS114_RST_PIN                  (B2 )                                   // Һ����λ���Ŷ���
#define IPS114_DC_PIN                   (C19)                                   // Һ������λ���Ŷ���
#define IPS114_CS_PIN                   (B3 )                                   // CS Ƭѡ����
#define IPS114_BLK_PIN                  (C18)                                   // Һ���������Ŷ���

#define IPS114_DEFAULT_DISPLAY_DIR      ( IPS114_CROSSWISE_180  )               // Ĭ�ϵ���ʾ����
#define IPS114_DEFAULT_PENCOLOR         ( RGB565_RED            )               // Ĭ�ϵĻ�����ɫ
#define IPS114_DEFAULT_BGCOLOR          ( RGB565_WHITE          )               // Ĭ�ϵı�����ɫ
#define IPS114_DEFAULT_DISPLAY_FONT     ( IPS114_8X16_FONT      )               // Ĭ�ϵ�����ģʽ

#define IPS114_DC(x)                    ((x) ? (gpio_high(IPS114_DC_PIN)) : (gpio_low(IPS114_DC_PIN)))
#define IPS114_RST(x)                   ((x) ? (gpio_high(IPS114_RST_PIN)) : (gpio_low(IPS114_RST_PIN)))
#define IPS114_CS(x)                    ((x) ? (gpio_high(IPS114_CS_PIN)) : (gpio_low(IPS114_CS_PIN)))
#define IPS114_BLK(x)                   ((x) ? (gpio_high(IPS114_BLK_PIN)) : (gpio_low(IPS114_BLK_PIN)))

typedef enum
{
    IPS114_PORTAIT                      = 0,                                    // ����ģʽ
    IPS114_PORTAIT_180                  = 1,                                    // ����ģʽ  ��ת180
    IPS114_CROSSWISE                    = 2,                                    // ����ģʽ
    IPS114_CROSSWISE_180                = 3,                                    // ����ģʽ  ��ת180
}ips114_dir_enum;

typedef enum
{
    IPS114_6X8_FONT                     = 0,                                    // 6x8      ����
    IPS114_8X16_FONT                    = 1,                                    // 8x16     ����
    IPS114_16X16_FONT                   = 2,                                    // 16x16    ���� Ŀǰ��֧��
}ips114_font_size_enum;

void    ips114_clear                    (void);
void    ips114_full                     (const uint16 color);
void    ips114_set_dir                  (ips114_dir_enum dir);
void    ips114_set_font                 (ips114_font_size_enum font);
void    ips114_set_color                (const uint16 pen, const  uint16 bgcolor);
void    ips114_draw_point               (uint16 x, uint16 y, const uint16 color);
void    ips114_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips114_show_char                (uint16 x, uint16 y, const char dat);
void    ips114_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips114_show_int                 (uint16 x,uint16 y, const int32 dat, uint8 num);
void    ips114_show_uint                (uint16 x,uint16 y, const uint32 dat, uint8 num);
void    ips114_show_float               (uint16 x,uint16 y, const double dat, uint8 num, uint8 pointnum);

void    ips114_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    ips114_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);
void    ips114_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);

void    ips114_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    ips114_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾС���ͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips114_displayimage7725(ov7725_image_binary[0], 80, 60);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define ips114_displayimage7725(p, width, height)       (ips114_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ�����ͼ�� ������ֵ�� ��ʾ�Ҷ�ͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips114_displayimage03x(mt9v03x_image[0], 94, 60);
// ��ע��Ϣ     ���Ҫ��ʾ��ֵ��ͼ���ȥ���� ips114_show_gray_image ����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_displayimage03x(p, width, height)        (ips114_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ��ͫͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips114_displayimage8660(scc8660_image[0], 80, 60);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define ips114_displayimage8660(p, width, height)       (ips114_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

void    ips114_init                     (void);

#endif
