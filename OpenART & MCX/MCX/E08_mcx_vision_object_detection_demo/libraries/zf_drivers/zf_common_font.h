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
* �ļ�����          zf_common_font
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
#ifndef _zf_common_font_h_
#define _zf_common_font_h_


//-------������ɫ----------
typedef enum
{
    RGB565_WHITE    = (0xFFFF),                                                     // ��ɫ
    RGB565_BLACK    = (0x0000),                                                     // ��ɫ
    RGB565_BLUE     = (0x001F),                                                     // ��ɫ
    RGB565_PURPLE   = (0xF81F),                                                     // ��ɫ
    RGB565_PINK     = (0xFE19),                                                     // ��ɫ
    RGB565_RED      = (0xF800),                                                     // ��ɫ
    RGB565_MAGENTA  = (0xF81F),                                                     // Ʒ��
    RGB565_GREEN    = (0x07E0),                                                     // ��ɫ
    RGB565_CYAN     = (0x07FF),                                                     // ��ɫ
    RGB565_YELLOW   = (0xFFE0),                                                     // ��ɫ
    RGB565_BROWN    = (0xBC40),                                                     // ��ɫ
    RGB565_GRAY     = (0x8430),                                                     // ��ɫ

    RGB565_39C5BB   = (0x3616),
    RGB565_66CCFF   = (0x665F),
}rgb565_color_enum;

extern const unsigned char      ascii_font_8x16[][16];
extern const unsigned char      gImage_seekfree_logo[38400];

#endif
