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

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_driver_delay.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"

#include "zf_device_ips114.h"

static uint16                   ips114_pencolor     = IPS114_DEFAULT_PENCOLOR;
static uint16                   ips114_bgcolor      = IPS114_DEFAULT_BGCOLOR;

static ips114_dir_enum          ips114_display_dir  = IPS114_DEFAULT_DISPLAY_DIR;
static ips114_font_size_enum    ips114_display_font = IPS114_DEFAULT_DISPLAY_FONT;
static uint8                    ips114_x_max        = 240;
static uint8                    ips114_y_max        = 135;

#if IPS114_USE_SOFT_SPI
static soft_spi_info_struct             ips114_spi;
//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_8bit_data(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_8bit_data(data)    (soft_spi_write_8bit(&ips114_spi, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_16bit_data(x1 + 52);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_16bit_data(data)   (soft_spi_write_16bit(&ips114_spi, (data)))
#else
//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 SPI д 8bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_8bit_data(dat);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_8bit_data(data)    (spi_write_8bit(IPS114_SPI, (data)))

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 SPI д 16bit ����
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_16bit_data(x1 + 52);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
#define ips114_write_16bit_data(data)   (spi_write_16bit(IPS114_SPI, (data)))
#endif

//-------------------------------------------------------------------------------------------------------------------
// �������     д����
// ����˵��     dat             ����
// ���ز���     void
// ʹ��ʾ��     ips114_write_index(0x2a);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void ips114_write_index (const uint8 dat)
{
    IPS114_DC(0);
    ips114_write_8bit_data(dat);
    IPS114_DC(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     x1              ��ʼx������
// ����˵��     y1              ��ʼy������
// ����˵��     x2              ����x������
// ����˵��     y2              ����y������
// ���ز���     void
// ʹ��ʾ��     ips114_set_region(0, 0, ips114_x_max - 1, ips114_y_max - 1);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void ips114_set_region (const uint16 x1, const uint16 y1, const uint16 x2, const uint16 y2)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    // ���һ�������ʾ���õĺ��� �Լ�����һ�����ﳬ������Ļ��ʾ��Χ
    zf_assert(x1 < ips114_x_max);
    zf_assert(y1 < ips114_y_max);
    zf_assert(x2 < ips114_x_max);
    zf_assert(y2 < ips114_y_max);

    switch(ips114_display_dir)
    {
        case IPS114_PORTAIT:
        {
            ips114_write_index(0x2a);                                           // �е�ַ����
            ips114_write_16bit_data(x1 + 52);
            ips114_write_16bit_data(x2 + 52);
            ips114_write_index(0x2b);                                           // �е�ַ����
            ips114_write_16bit_data(y1 + 40);
            ips114_write_16bit_data(y2 + 40);
            ips114_write_index(0x2c);                                           // ������д
        }break;
        case IPS114_PORTAIT_180:
        {
            ips114_write_index(0x2a);                                           // �е�ַ����
            ips114_write_16bit_data(x1 + 53);
            ips114_write_16bit_data(x2 + 53);
            ips114_write_index(0x2b);                                           // �е�ַ����
            ips114_write_16bit_data(y1 + 40);
            ips114_write_16bit_data(y2 + 40);
            ips114_write_index(0x2c);                                           // ������д
        }break;
        case IPS114_CROSSWISE:
        {
            ips114_write_index(0x2a);                                           // �е�ַ����
            ips114_write_16bit_data(x1 + 40);
            ips114_write_16bit_data(x2 + 40);
            ips114_write_index(0x2b);                                           // �е�ַ����
            ips114_write_16bit_data(y1 + 53);
            ips114_write_16bit_data(y2 + 53);
            ips114_write_index(0x2c);                                           // ������д
        }break;
        case IPS114_CROSSWISE_180:
        {
            ips114_write_index(0x2a);                                           // �е�ַ����
            ips114_write_16bit_data(x1 + 40);
            ips114_write_16bit_data(x2 + 40);
            ips114_write_index(0x2b);                                           // �е�ַ����
            ips114_write_16bit_data(y1 + 52);
            ips114_write_16bit_data(y2 + 52);
            ips114_write_index(0x2c);                                           // ������д
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     1.14�� IPS Һ����ʾDEBUG��Ϣ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ips114_debug_init();
// ��ע��Ϣ     �ڲ�ʹ��
//-------------------------------------------------------------------------------------------------------------------
static void ips114_debug_init (void)
{
    debug_output_struct info;
    debug_output_struct_init(&info);

    info.type_index = 1;
    info.display_x_max = ips114_x_max;
    info.display_y_max = ips114_y_max;

    switch(ips114_display_font)
    {
        case IPS114_6X8_FONT:
        {
            info.font_x_size = 6;
            info.font_y_size = 8;
        }break;
        case IPS114_8X16_FONT:
        {
            info.font_x_size = 8;
            info.font_y_size = 16;
        }break;
        case IPS114_16X16_FONT:
        {
            // �ݲ�֧��
        }break;
    }
    info.output_screen = ips114_show_string;
    info.output_screen_clear = ips114_clear;
        
    debug_output_init(&info);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ips114_clear();
// ��ע��Ϣ     ����Ļ��ճɱ�����ɫ
//-------------------------------------------------------------------------------------------------------------------
void ips114_clear (void)
{
    uint32 i = ips114_x_max * ips114_y_max;

    IPS114_CS(0);
    ips114_set_region(0, 0, ips114_x_max - 1, ips114_y_max - 1);
    for( ; 0 < i; i --)
    {
        ips114_write_16bit_data(ips114_bgcolor);
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��Ļ��亯��
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_full(RGB565_BLACK);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_full (const uint16 color)
{
    uint32 i = ips114_x_max * ips114_y_max;

    IPS114_CS(0);
    ips114_set_region(0, 0, ips114_x_max - 1, ips114_y_max - 1);
    for( ; 0 < i; i --)
    {
        ips114_write_16bit_data(color);
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_ips114.h �� ips114_dir_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     ips114_set_dir(IPS114_CROSSWISE);
// ��ע��Ϣ     �������ֻ���ڳ�ʼ����Ļ֮ǰ���ò���Ч
//-------------------------------------------------------------------------------------------------------------------
void ips114_set_dir (ips114_dir_enum dir)
{
    ips114_display_dir = dir;
    switch(ips114_display_dir)
    {
        case IPS114_PORTAIT:
        case IPS114_PORTAIT_180:
        {
            ips114_x_max = 135;
            ips114_y_max = 240;
        }break;
        case IPS114_CROSSWISE:
        case IPS114_CROSSWISE_180:
        {
            ips114_x_max = 240;
            ips114_y_max = 135;
        }break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ����
// ����˵��     dir             ��ʾ����  ���� zf_device_ips114.h �� ips114_font_size_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     ips114_set_font(IPS114_8x16_FONT);
// ��ע��Ϣ     ���������ʱ�������� ���ú���Ч ������ʾ�����µ������С
//-------------------------------------------------------------------------------------------------------------------
void ips114_set_font (ips114_font_size_enum font)
{
    ips114_display_font = font;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ��ɫ
// ����˵��     pen             ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ����˵��     bgcolor         ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_set_color(RGB565_WHITE, RGB565_BLACK);
// ��ע��Ϣ     ������ɫ�ͱ�����ɫҲ������ʱ�������� ���ú���Ч
//-------------------------------------------------------------------------------------------------------------------
void ips114_set_color (const uint16 pen, const uint16 bgcolor)
{
    ips114_pencolor = pen;
    ips114_bgcolor = bgcolor;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ����
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_draw_point(0, 0, RGB565_RED);            // ���� 0,0 ��һ����ɫ�ĵ�
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_draw_point (uint16 x, uint16 y, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);

    IPS114_CS(0);
    ips114_set_region(x, y, x, y);
    ips114_write_16bit_data(color);
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ����
// ����˵��     x_start         ����x��������
// ����˵��     y_start         ����y��������
// ����˵��     x_end           ����x������յ�
// ����˵��     y_end           ����y������յ�
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_draw_line(0, 0, 10, 10, RGB565_RED);     // ���� 0,0 �� 10,10 ��һ����ɫ����
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x_start < ips114_x_max);
    zf_assert(y_start < ips114_y_max);
    zf_assert(x_end < ips114_x_max);
    zf_assert(y_end < ips114_y_max);

    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if(x_start != x_end)
        {
            temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
            temp_b = (float)y_start - (float)x_start * temp_rate;
        }
        else
        {
            while(y_start != y_end)
            {
                ips114_draw_point(x_start, y_start, color);
                y_start += y_dir;
            }
            break;
        }
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                ips114_draw_point(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
        }
        else
        {
            while(x_start != x_end)
            {
                ips114_draw_point(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ�ַ�
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ�
// ���ز���     void
// ʹ��ʾ��     ips114_show_char(0, 0, 'x');                    // ���� 0,0 дһ���ַ� x
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_char (uint16 x, uint16 y, const char dat)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);

    uint8 i = 0, j = 0;

    IPS114_CS(0);
    switch(ips114_display_font)
    {
        case IPS114_6X8_FONT:
        {
            for(i = 0; 6 > i; i ++)
            {
                ips114_set_region(x + i, y, x + i, y + 8);
                // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
                uint8 temp_top = ascii_font_6x8[dat - 32][i];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips114_write_16bit_data(ips114_pencolor);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                    temp_top >>= 1;
                }
            }
        }break;
        case IPS114_8X16_FONT:
        {
            for(i = 0; 8 > i; i ++)
            {
                ips114_set_region(x + i, y, x + i, y + 15);
                // �� 32 ��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո��� ascii ������� 32
                uint8 temp_top = ascii_font_8x16[dat - 32][i];
                uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        ips114_write_16bit_data(ips114_pencolor);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; 8 > j; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        ips114_write_16bit_data(ips114_pencolor);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
        }break;
        case IPS114_16X16_FONT:
        {
            // �ݲ�֧��
        }break;
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ�ַ���
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ���ַ���
// ���ز���     void
// ʹ��ʾ��     ips114_show_string(0, 0, "seekfree");
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_string (uint16 x, uint16 y, const char dat[])
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    
    uint16 j = 0;
    while('\0' != dat[j])
    {
        switch(ips114_display_font)
        {
            case IPS114_6X8_FONT:   ips114_show_char(x + 6 * j, y, dat[j]); break;
            case IPS114_8X16_FONT:  ips114_show_char(x + 8 * j, y, dat[j]); break;
            case IPS114_16X16_FONT: break;                                      // �ݲ�֧��
        }
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ32λ�з��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� int32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips114_show_int(0, 0, x, 3);                    // x ����Ϊ int32 int16 int8 ����
// ��ע��Ϣ     ��������ʾһ�� ��-����
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_int (uint16 x, uint16 y, const int32 dat, uint8 num)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    int32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];

    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num + 1);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_int_to_str(data_buffer, dat_temp);
    ips114_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ32λ�޷��� (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� uint32
// ����˵��     num             ��Ҫ��ʾ��λ�� ���10λ  ������������
// ���ز���     void
// ʹ��ʾ��     ips114_show_uint(0, 0, x, 3);                   // x ����Ϊ uint32 uint16 uint8 ����
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_uint (uint16 x, uint16 y, const uint32 dat, uint8 num)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(0 < num);
    zf_assert(10 >= num);

    uint32 dat_temp = dat;
    int32 offset = 1;
    char data_buffer[12];
    memset(data_buffer, 0, 12);
    memset(data_buffer, ' ', num);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    if(10 > num)
    {
        for(; 0 < num; num --)
        {
            offset *= 10;
        }
        dat_temp %= offset;
    }
    func_uint_to_str(data_buffer, dat_temp);
    ips114_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ������ (ȥ������������Ч��0)
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     dat             ��Ҫ��ʾ�ı��� �������� float
// ����˵��     num             ����λ��ʾ����   ���8λ  
// ����˵��     pointnum        С��λ��ʾ����   ���6λ
// ���ز���     void
// ʹ��ʾ��     ips114_show_float(0, 0, x, 2, 3);               // ��ʾ������ ������ʾ 2 λ С����ʾ 3 λ
// ��ע��Ϣ     �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//              ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//              �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//              ��������ʾһ�� ��-����
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_float (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(0 < num);
    zf_assert(8 >= num);
    zf_assert(0 < pointnum);
    zf_assert(6 >= pointnum);

    double dat_temp = dat;
    double offset = 1.0;
    char data_buffer[17];
    memset(data_buffer, 0, 17);
    memset(data_buffer, ' ', num + pointnum + 2);

    // ��������������ʾ 123 ��ʾ 2 λ��Ӧ����ʾ 23
    for(; 0 < num; num --)
    {
        offset *= 10;
    }
    dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    func_double_to_str(data_buffer, dat_temp, pointnum);
    ips114_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ��ֵͼ�� ����ÿ�˸������һ���ֽ�����
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, ips114_x_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, ips114_y_max]
// ���ز���     void
// ʹ��ʾ��     ips114_show_binary_image(0, 0, ov7725_image_binary[0], OV7725_W, OV7725_H, OV7725_W, OV7725_H);
// ��ע��Ϣ     ������ʾС����δ��ѹ��ѹ����ֵ��ͼ��
//              �����������������ֱ����ʾ������δѹ���Ķ�ֵ��ͼ��
//              �����������������ֱ����ʾ������δѹ���Ķ�ֵ��ͼ��
//              �����������������ֱ����ʾ������δѹ���Ķ�ֵ��ͼ��
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_binary_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint8 temp = 0;
    uint32 width_index = 0, height_index = 0;

    IPS114_CS(0);
    ips114_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width / 8 + width_index / 8);       // ��ȡ���ص�
            if(0x80 & (temp << (width_index % 8)))
            {
                ips114_write_16bit_data(RGB565_WHITE);
            }
            else
            {
                ips114_write_16bit_data(RGB565_BLACK);
            }
        }
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ 8bit �Ҷ�ͼ�� ����ֵ����ֵ
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, ips114_x_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, ips114_y_max]
// ����˵��     threshold       ��ֵ����ʾ��ֵ 0-��������ֵ��
// ���ز���     void
// ʹ��ʾ��     ips114_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
// ��ע��Ϣ     ������ʾ������ͼ��
//              ���Ҫ��ʾ��ֵ��ͼ�� ֱ���޸����һ������Ϊ��Ҫ�Ķ�ֵ����ֵ����
//              ���Ҫ��ʾ��ֵ��ͼ�� ֱ���޸����һ������Ϊ��Ҫ�Ķ�ֵ����ֵ����
//              ���Ҫ��ʾ��ֵ��ͼ�� ֱ���޸����һ������Ϊ��Ҫ�Ķ�ֵ����ֵ����
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_gray_image (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 threshold)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0,temp = 0;
    uint32 width_index = 0, height_index = 0;

    IPS114_CS(0);
    ips114_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            temp = *(image + height_index * width + width_index);               // ��ȡ���ص�
            if(threshold == 0)
            {
                color = (0x001f & ((temp) >> 3)) << 11;
                color = color | (((0x003f) & ((temp) >> 2)) << 5);
                color = color | (0x001f & ((temp) >> 3));
                ips114_write_16bit_data(color);
            }
            else if(temp < threshold)
            {
                ips114_write_16bit_data(RGB565_BLACK);
            }
            else
            {
                ips114_write_16bit_data(RGB565_WHITE);
            }
        }
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ RGB565 ��ɫͼ��
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     *image          ͼ������ָ��
// ����˵��     width           ͼ��ʵ�ʿ��
// ����˵��     height          ͼ��ʵ�ʸ߶�
// ����˵��     dis_width       ͼ����ʾ��� ������Χ [0, ips114_x_max]
// ����˵��     dis_height      ͼ����ʾ�߶� ������Χ [0, ips114_y_max]
// ����˵��     color_mode      ɫ��ģʽ 0-��λ��ǰ 1-��λ��ǰ
// ���ز���     void
// ʹ��ʾ��     ips114_show_rgb565_image(0, 0, scc8660_image[0], SCC8660_W, SCC8660_H, SCC8660_W, SCC8660_H, 1);
// ��ע��Ϣ     ������ʾ��ͫ�� RGB565 ��ͼ��
//              ���Ҫ��ʾ��λ��ǰ������ RGB565 ͼ�� �޸����һ����������
//              ���Ҫ��ʾ��λ��ǰ������ RGB565 ͼ�� �޸����һ����������
//              ���Ҫ��ʾ��λ��ǰ������ RGB565 ͼ�� �޸����һ����������
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_rgb565_image (uint16 x, uint16 y, const uint16 *image, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height, uint8 color_mode)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(NULL != image);

    uint32 i = 0, j = 0;
    uint16 color = 0;
    uint32 width_index = 0, height_index = 0;

    IPS114_CS(0);
    ips114_set_region(x, y, x + dis_width - 1, y + dis_height - 1);             // ������ʾ����

    for(j = 0; j < dis_height; j ++)
    {
        height_index = j * height / dis_height;
        for(i = 0; i < dis_width; i ++)
        {
            width_index = i * width / dis_width;
            color = *(image + height_index * width + width_index);              // ��ȡ���ص�
            if(color_mode)
            {
                color = ((color & 0xff) << 8) | (color >> 8);
            }
            ips114_write_16bit_data(color);
        }
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IPS114 ��ʾ����
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     *wave           ��������ָ��
// ����˵��     width           ����ʵ�ʿ��
// ����˵��     value_max       ����ʵ�����ֵ
// ����˵��     dis_width       ������ʾ��� ������Χ [0, ips114_x_max]
// ����˵��     dis_value_max   ������ʾ���ֵ ������Χ [0, ips114_y_max]
// ���ز���     void
// ʹ��ʾ��     ips114_show_wave(56,35,data,128,64,128,64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_wave (uint16 x, uint16 y, const uint16 *wave, uint16 width, uint16 value_max, uint16 dis_width, uint16 dis_value_max)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(NULL != wave);

    uint32 i = 0, j = 0;
    uint32 width_index = 0, value_max_index = 0;

    IPS114_CS(0);
    ips114_set_region(x, y, x + dis_width - 1, y + dis_value_max - 1);          // ������ʾ����
    for(i = 0; i < dis_value_max; i ++)
    {
        for(j = 0; j < dis_width; j ++)
        {
            ips114_write_16bit_data(ips114_bgcolor); 
        }
    }
    IPS114_CS(1);

    for(i = 0; i < dis_width; i ++)
    {
        width_index = i * width / dis_width;
        value_max_index = *(wave + width_index) * (dis_value_max - 1) / value_max;
        ips114_draw_point(i + x, (dis_value_max - 1) - value_max_index + y, ips114_pencolor);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ʾ
// ����˵��     x               ����x�������� ������Χ [0, ips114_x_max-1]
// ����˵��     y               ����y�������� ������Χ [0, ips114_y_max-1]
// ����˵��     size            ȡģ��ʱ�����õĺ��������С Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��� ȡģ��ʱ����Ҫ������һ����
// ����˵��     *chinese_buffer ��Ҫ��ʾ�ĺ�������
// ����˵��     number          ��Ҫ��ʾ����λ
// ����˵��     color           ��ɫ��ʽ RGB565 ���߿���ʹ�� zf_common_font.h �� rgb565_color_enum ö��ֵ��������д��
// ���ز���     void
// ʹ��ʾ��     ips114_show_chinese(0, 0, 16, chinese_test[0], 4, RGB565_RED);// ��ʾfont�ļ������ ʾ��
// ��ע��Ϣ     ʹ��PCtoLCD2002���ȡģ           ���롢����ʽ��˳��   16*16
//-------------------------------------------------------------------------------------------------------------------
void ips114_show_chinese (uint16 x, uint16 y, uint8 size, const uint8 *chinese_buffer, uint8 number, const uint16 color)
{
    // �������������˶�����Ϣ ������ʾ����λ��������
    // ��ôһ������Ļ��ʾ��ʱ�򳬹���Ļ�ֱ��ʷ�Χ��
    zf_assert(x < ips114_x_max);
    zf_assert(y < ips114_y_max);
    zf_assert(NULL != chinese_buffer);

    int i = 0, j = 0, k = 0; 
    uint8 temp = 0, temp1 = 0, temp2 = 0;
    const uint8 *p_data = chinese_buffer;
    
    temp2 = size / 8;

    IPS114_CS(0);
    ips114_set_region(x, y, number * size - 1 + x, y + size - 1);
    
    for(i = 0; i < size; i ++)
    {
        temp1 = number;
        p_data = chinese_buffer + i * temp2;
        while(temp1 --)
        {
            for(k = 0; k < temp2; k ++)
            {
                for(j = 8; 0 < j; j --)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if(temp)
                    {
                        ips114_write_16bit_data(color);
                    }
                    else
                    {
                        ips114_write_16bit_data(ips114_bgcolor);
                    }
                }
                p_data ++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }   
    }
    IPS114_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     1.14�� IPSҺ����ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ips114_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void ips114_init (void)
{
#if IPS114_USE_SOFT_SPI
    soft_spi_init(&ips114_spi, 0, IPS114_SOFT_SPI_DELAY, IPS114_SCL_PIN, IPS114_SDA_PIN, SOFT_SPI_PIN_NULL, SOFT_SPI_PIN_NULL);
#else
    spi_init(IPS114_SPI, SPI_MODE0, IPS114_SPI_SPEED, IPS114_SCL_PIN, IPS114_SDA_PIN, SPI_MISO_NULL, SPI_CS_NULL);
#endif

    gpio_init(IPS114_DC_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(IPS114_RST_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(IPS114_CS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(IPS114_BLK_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    ips114_set_dir(ips114_display_dir);
    ips114_set_color(ips114_pencolor, ips114_bgcolor);

    IPS114_RST(0);
    system_delay_ms(200);

    IPS114_RST(1);
    system_delay_ms(100);

    IPS114_CS(0);
    ips114_write_index(0x36);
    system_delay_ms(100);
    switch(ips114_display_dir)
    {
        case IPS114_PORTAIT:        ips114_write_8bit_data(0x00);   break;
        case IPS114_PORTAIT_180:    ips114_write_8bit_data(0xC0);   break;
        case IPS114_CROSSWISE:      ips114_write_8bit_data(0x70);   break;
        case IPS114_CROSSWISE_180:  ips114_write_8bit_data(0xA0);   break;
    }

    ips114_write_index(0x3A);
    ips114_write_8bit_data(0x05);

    ips114_write_index(0xB2);
    ips114_write_8bit_data(0x0C);
    ips114_write_8bit_data(0x0C);
    ips114_write_8bit_data(0x00);
    ips114_write_8bit_data(0x33);
    ips114_write_8bit_data(0x33);

    ips114_write_index(0xB7);
    ips114_write_8bit_data(0x35);

    ips114_write_index(0xBB);
    ips114_write_8bit_data(0x37);

    ips114_write_index(0xC0);
    ips114_write_8bit_data(0x2C);

    ips114_write_index(0xC2);
    ips114_write_8bit_data(0x01);

    ips114_write_index(0xC3);
    ips114_write_8bit_data(0x12);

    ips114_write_index(0xC4);
    ips114_write_8bit_data(0x20);

    ips114_write_index(0xC6);
    ips114_write_8bit_data(0x0F);

    ips114_write_index(0xD0);
    ips114_write_8bit_data(0xA4);
    ips114_write_8bit_data(0xA1);

    ips114_write_index(0xE0);
    ips114_write_8bit_data(0xD0);
    ips114_write_8bit_data(0x04);
    ips114_write_8bit_data(0x0D);
    ips114_write_8bit_data(0x11);
    ips114_write_8bit_data(0x13);
    ips114_write_8bit_data(0x2B);
    ips114_write_8bit_data(0x3F);
    ips114_write_8bit_data(0x54);
    ips114_write_8bit_data(0x4C);
    ips114_write_8bit_data(0x18);
    ips114_write_8bit_data(0x0D);
    ips114_write_8bit_data(0x0B);
    ips114_write_8bit_data(0x1F);
    ips114_write_8bit_data(0x23);

    ips114_write_index(0xE1);
    ips114_write_8bit_data(0xD0);
    ips114_write_8bit_data(0x04);
    ips114_write_8bit_data(0x0C);
    ips114_write_8bit_data(0x11);
    ips114_write_8bit_data(0x13);
    ips114_write_8bit_data(0x2C);
    ips114_write_8bit_data(0x3F);
    ips114_write_8bit_data(0x44);
    ips114_write_8bit_data(0x51);
    ips114_write_8bit_data(0x2F);
    ips114_write_8bit_data(0x1F);
    ips114_write_8bit_data(0x1F);
    ips114_write_8bit_data(0x20);
    ips114_write_8bit_data(0x23);

    ips114_write_index(0x21);

    ips114_write_index(0x11);
    system_delay_ms(120);

    ips114_write_index(0x29);
    IPS114_CS(1);

    ips114_clear();
    ips114_debug_init();
}
