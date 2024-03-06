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
* �ļ�����          zf_driver_csi
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

#ifndef _zf_driver_csi_h_
#define _zf_driver_csi_h_

#include "zf_common_typedef.h"
#include "fsl_csi.h"

extern csi_handle_t csi_handle;        //csi����ṹ��


//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ�������
{
    CSI_VSYNC_B14,
    CSI_VSYNC_B22,
    CSI_VSYNC_C29,
}vsync_pin_enum;

//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ�������
{
    CSI_PIXCLK_B20,
    CSI_PIXCLK_C28,
}pixclk_pin_enum;

//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ�������
{
    CSI_PIXCLK_RISING  = kCSI_DataLatchOnRisingEdge,    // �����ش���
    CSI_PIXCLK_FALLING = kCSI_DataLatchOnFallingEdge,   // �½��ش���
}pixclk_polarity_enum;

void csi_add_empty_buffer(csi_handle_t *handle, uint8 *buff);
uint8 csi_get_full_buffer(csi_handle_t *handle, uint32 *buffaddr);
void csi_start(csi_handle_t *handle);
void csi_stop(csi_handle_t *handle);
void csi_init(uint16 width, uint16 height, csi_handle_t *handle, csi_transfer_callback_t callback, vsync_pin_enum vsync, pixclk_pin_enum pixclk, pixclk_polarity_enum pixclk_polarity);



#endif
