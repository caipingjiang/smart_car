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
* �ļ�����          zf_device_ips200
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
#ifndef _zf_device_ips200_h_
#define _zf_device_ips200_h_

#include "zf_common_headfile.h"

typedef enum
{
    IPS200_CROSSWISE                    = 0,                                    // ����ģʽ
    IPS200_CROSSWISE_180                = 1,                                    // ����ģʽ  ��ת180
}ips200_dir_enum;

#define IPS200_SPI                      (LPSPI1)
#define IPS200_SPI_BAUDRATE             (60000000U)

#define IPS200_RST_PIN                  {GPIO0, 22u}
#define IPS200_DC_PIN                   {GPIO0, 23u}
#define IPS200_BLK_PIN                  {GPIO0, 30u}

#define IPS200_RST(x)      	            gpio_set_level(ips200_rst_pin,x)
#define IPS200_BLK(x)		            gpio_set_level(ips200_blk_pin,x)
#define IPS200_DC(x)                    gpio_set_level(ips200_dc_pin,x)

#define IPS200_DEFAULT_DISPLAY_DIR      (IPS200_CROSSWISE)                        // Ĭ�ϵ���ʾ����

void    ips200_full                     (const uint16_t color);
void    ips200_draw_line                (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips200_show_char                (uint16 x, uint16 y, const char dat);
void    ips200_show_string              (uint16 x, uint16 y, const char dat[]);
void    ips200_show_int                 (uint16 x, uint16 y, const int32 dat);
void    ips200_show_float               (uint16 x, uint16 y, const float dat);

void    ips200_show_scc8660             (uint16_t* data);

void    ips200_init                     (void);

#endif
