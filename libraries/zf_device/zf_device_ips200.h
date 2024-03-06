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
* �ļ�����          zf_device_ips200
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
*                   // ˫������ ���������� Ӳ������
*                   RD                  �鿴 zf_device_ips200.h �� IPS200_RD_PIN_PARALLEL8     �궨��
*                   WR                  �鿴 zf_device_ips200.h �� IPS200_WR_PIN_PARALLEL8     �궨��
*                   RS                  �鿴 zf_device_ips200.h �� IPS200_RS_PIN_PARALLEL8     �궨��
*                   RST                 �鿴 zf_device_ips200.h �� IPS200_RST_PIN_PARALLEL8    �궨��
*                   CS                  �鿴 zf_device_ips200.h �� IPS200_CS_PIN_PARALLEL8     �궨��
*                   BL                  �鿴 zf_device_ips200.h �� IPS200_BL_PIN_PARALLEL8     �궨��
*                   D0-D7               �鿴 zf_device_ips200.h �� IPS200_Dx_PIN_PARALLEL8     �궨��
*                   // �������� SPI ������ Ӳ������
*                   SCL                 �鿴 zf_device_ips200.h �� IPS200_SCL_PIN_SPI  �궨��
*                   SDA                 �鿴 zf_device_ips200.h �� IPS200_SDA_PIN_SPI  �궨��
*                   RST                 �鿴 zf_device_ips200.h �� IPS200_RST_PIN_SPI  �궨��
*                   DC                  �鿴 zf_device_ips200.h �� IPS200_DC_PIN_SPI   �궨��
*                   CS                  �鿴 zf_device_ips200.h �� IPS200_CS_PIN_SPI   �궨��
*                   BLk                 �鿴 zf_device_ips200.h �� IPS200_BLk_PIN_SPI  �궨��
*                   ��Դ����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ���ֱ��� 320 * 240
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_ips200_h_
#define _zf_device_ips200_h_

#include "zf_common_typedef.h"
#include "zf_driver_gpio.h"

#define IPS200_USE_SOFT_SPI             (0 )                                    // Ĭ��ʹ��Ӳ�� SPI ��ʽ���� ����ʹ��Ӳ�� SPI ��ʽ����
#if IPS200_USE_SOFT_SPI                                                         // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� SPI ����====================================================
// ���ʹ�õ��ǵ��������������Ļ SPI ������������ �����޸�
#define IPS200_SOFT_SPI_DELAY           (1 )                                    // ��� SPI ��ʱ����ʱ���� ��ֵԽС SPI ͨ������Խ��
#define IPS200_SCL_PIN                  (B0)                                    // ��� SPI SCK ����
#define IPS200_SDA_PIN                  (B1)                                    // ��� SPI MOSI ����
//====================================================��� SPI ����====================================================
#else
//====================================================Ӳ�� SPI ����====================================================
// ���ʹ�õ��ǵ��������������Ļ SPI ������������ �����޸�
#define IPS200_SPI_SPEED                (60 * 1000 * 1000)                      // Ӳ�� SPI ���� ��������Ϊϵͳʱ�Ӷ���Ƶ
#define IPS200_SPI                      (SPI_3           )                      // Ӳ�� SPI ��
#define IPS200_SCL_PIN_SPI              (SPI3_SCK_B0     )                      // Ӳ�� SPI SCK ����
#define IPS200_SDA_PIN_SPI              (SPI3_MOSI_B1    )                      // Ӳ�� SPI MOSI ����
//====================================================Ӳ�� SPI ����====================================================
#endif
// ���ʹ�õ��ǵ��������������Ļ SPI ������������ �����޸�
#define IPS200_RST_PIN_SPI              (B2 )                                   // Һ����λ���Ŷ���
#define IPS200_DC_PIN_SPI               (C19)                                   // Һ������λ���Ŷ���
#define IPS200_CS_PIN_SPI               (B3 )
#define IPS200_BLk_PIN_SPI              (C18)

// ���ʹ�õ���˫�������������Ļ ���������������� �����޸�
#define IPS200_RD_PIN_PARALLEL8         (B0 )
#define IPS200_WR_PIN_PARALLEL8         (B1 )
#define IPS200_RS_PIN_PARALLEL8         (B2 )
#define IPS200_RST_PIN_PARALLEL8        (C19 )
#define IPS200_CS_PIN_PARALLEL8         (B3 )
#define IPS200_BL_PIN_PARALLEL8         (C18)

// ���ʹ�õ���˫�������������Ļ ���������������� ���������޸�
#define IPS200_D0_PIN_PARALLEL8         (B16)
#define IPS200_D1_PIN_PARALLEL8         (B17)
#define IPS200_D2_PIN_PARALLEL8         (B18)
#define IPS200_D3_PIN_PARALLEL8         (B19)
#define IPS200_D4_PIN_PARALLEL8         (D12)
#define IPS200_D5_PIN_PARALLEL8         (D13)
#define IPS200_D6_PIN_PARALLEL8         (D14)
#define IPS200_D7_PIN_PARALLEL8         (D15)

#define IPS200_DEFAULT_DISPLAY_DIR      (IPS200_PORTAIT)                        // Ĭ�ϵ���ʾ����
#define IPS200_DEFAULT_PENCOLOR         (RGB565_RED    )                        // Ĭ�ϵĻ�����ɫ
#define IPS200_DEFAULT_BGCOLOR          (RGB565_WHITE  )                        // Ĭ�ϵı�����ɫ
#define IPS200_DEFAULT_DISPLAY_FONT     (IPS200_8X16_FONT)                      // Ĭ�ϵ�����ģʽ

// ���ݶ�Ӧ��ַ ���ɸ���
#define IPS200_DATA_ADD1                (PORTB_FAST_DR)
#define IPS200_DATA_ADD2                (PORTD_FAST_DR)

// �������
#define IPS200_RD(x)       	            fast_gpio_set_level(IPS200_RD_PIN_PARALLEL8,x)
#define IPS200_WR(x)       	            fast_gpio_set_level(IPS200_WR_PIN_PARALLEL8,x)
#define IPS200_RS(x)       	            fast_gpio_set_level(IPS200_RS_PIN_PARALLEL8,x)
#define IPS200_RST(x)      	            fast_gpio_set_level(ips_rst_pin,x)
#define IPS200_CS(x)       	            fast_gpio_set_level(ips_cs_pin,x)
#define IPS200_BL(x)		            fast_gpio_set_level(ips_bl_pin,x)
                    
#define IPS200_DC(x)                    fast_gpio_set_level(IPS200_DC_PIN_SPI,x)


typedef enum
{
    IPS200_TYPE_SPI,                                                            // SPI ����
    IPS200_TYPE_PARALLEL8,                                                      // ��������
}ips200_type_enum;

typedef enum
{
    IPS200_PORTAIT                      = 0,                                    // ����ģʽ
    IPS200_PORTAIT_180                  = 1,                                    // ����ģʽ  ��ת180
    IPS200_CROSSWISE                    = 2,                                    // ����ģʽ
    IPS200_CROSSWISE_180                = 3,                                    // ����ģʽ  ��ת180
}ips200_dir_enum;

typedef enum
{
    IPS200_6X8_FONT                     = 0,                                    // 6x8      ����
    IPS200_8X16_FONT                    = 1,                                    // 8x16     ����
    IPS200_16X16_FONT                   = 2,                                    // 16x16    ���� Ŀǰ��֧��
}ips200_font_size_enum;


extern  gpio_pin_enum                   ips_cs_pin;


void    ips200_clear                    (void);
void    ips200_full                     (const uint16 color);
void    ips200_set_dir                  (ips200_dir_enum dir);
void    ips200_set_font                 (ips200_font_size_enum font);
void    ips200_set_color                (const uint16 pen, const uint16 bgcolor);
void    ips200_draw_point               (uint16 x, uint16 y, const uint16 color);
void    ips200_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips200_show_char                (uint16 x, uint16 y, const char dat);
void    ips200_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips200_show_int                 (uint16 x, uint16 y, const int32 dat, uint8 num);
void    ips200_show_uint                (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    ips200_show_float               (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    ips200_show_binary_image        (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void    ips200_show_gray_image          (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold);
void    ips200_show_rgb565_image        (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode);

void    ips200_show_wave                (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max);
void    ips200_show_chinese             (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color);


//-------------------�Զ��庯��-----------------
void ips200_draw_square(uint16 x, uint16 y, uint8 lenth, const uint16 color);
void ips200_draw_circle(uint16 center_x, uint16 center_y, uint16 radius, const uint16 color);
//-------------------�Զ��庯��-----------------

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 ��ʾС���ͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips200_displayimage7725(ov7725_image_binary[0], 80, 60);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage7725(p, width, height)       (ips200_show_binary_image(0, 0, (p), OV7725_W, OV7725_H, (width), (height)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 ��ʾ�����ͼ�� ������ֵ�� ��ʾ�Ҷ�ͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips200_displayimage03x(mt9v03x_image[0], 94, 60);
// ��ע��Ϣ     ���Ҫ��ʾ��ֵ��ͼ���ȥ���� ips200_show_gray_image ����
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage03x(p, width, height)        (ips200_show_gray_image(0, 0, (p), MT9V03X_W, MT9V03X_H, (width), (height), 0))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS200 ��ʾ��ͫͼ��
// ����˵��     p               ͼ������
// ����˵��     width           ��ʾ���
// ����˵��     height          ��ʾ�߶�
// ���ز���     void
// ʹ��ʾ��     ips200_displayimage8660(scc8660_image[0], 80, 60);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
#define ips200_displayimage8660(p, width, height)       (ips200_show_rgb565_image(0, 0, (p), SCC8660_W, SCC8660_H, (width), (height), 1))

void    ips200_init                     (ips200_type_enum type_select);

#endif
