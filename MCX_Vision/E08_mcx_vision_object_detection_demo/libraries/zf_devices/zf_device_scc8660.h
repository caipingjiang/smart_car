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
* �ļ�����          zf_device_scc8660
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
#ifndef _zf_device_scc8660_h_
#define _zf_device_scc8660_h_

#include "zf_common_headfile.h"
#include "zf_device_config.h"

#define SCC8660_COF_IIC_DELAY   (2)                                             // ��ͫ IIC ��ʱ
#define SCC8660_INIT_TIMEOUT    (0x0080)                                        // Ĭ�ϵ�����ͷ��ʼ����ʱʱ�� ����Ϊ��λ

//--------------------------------------------------------------------------------------------------
// ����ͷĬ�ϲ������� �ڴ��޸�����ͷ����
//--------------------------------------------------------------------------------------------------
// ����ͷͼ��ߴ�
#define SCC8660_QVGA            (320240) 
#define SCC8660_QQVGA           (160120)

// ����ͷ�ĳߴ�ֻ֧��QVGA��QQVGA��ͼ���С����ֻ��Ҫ�޸�����궨��
#define FRAME_SIZE              SCC8660_QVGA

// �������޸�Ϊ��������
#if (FRAME_SIZE == SCC8660_QVGA)
#define SCC8660_W               (320)                                           
#define SCC8660_H               (240)                                           
#elif (FRAME_SIZE == SCC8660_QQVGA)
#define SCC8660_W               (160)                                           
#define SCC8660_H               (120)                                           
#endif

#define SCC8660_IMAGE_SIZE      (SCC8660_W * 2 * SCC8660_H)                     // ����ͼ���С SCC8660_W*2*SCC8660_H ���ܳ��� 65535

#define SCC8660_AUTO_EXP_DEF    (0  )                                           // �Զ��ع�     Ĭ�ϲ������Զ��ع�����  ��Χ [0-1] 0Ϊ�ر�
#define SCC8660_BRIGHT_DEF      (800)                                           // ��������     �ֶ��ع�Ĭ�ϣ�300   �ֶ��ع�ʱ��������Χ0-65535   �Զ��ع��Ƽ�ֵ��100 �Զ��ع�ʱ�������÷�Χ0-255
#define SCC8660_FPS_DEF         (60 )                                           // ͼ��֡��     Ĭ�ϣ�50        ��ѡ����Ϊ��60 50 30 25�� ʵ��֡�ʻ���Ҫ��SCC8660_PCLK_DIV����������
#define SCC8660_PCLK_DIV_DEF    (2  )                                           // PCLK��Ƶϵ�� Ĭ�ϣ�0         ��ѡ����Ϊ��<0:1/1> <1:2/3> <2:1/2> <3:1/3> <4:1/4> <5:1/8>
                                                                                //              ��Ƶϵ��Խ��PCLKƵ��Խ�ͣ�����PCLK���Լ���DVP�ӿڵĸ��ţ�������PCLKƵ�����Ӱ��֡�ʡ��������������뱣��Ĭ�ϡ�
                                                                                //              ��������FPSΪ50֡������pclk��Ƶϵ��ѡ���Ϊ5��������ͷ�����֡��Ϊ50*��1/8��=6.25֡
                                                                                //              �����������������£�SCC8660_PCLK_DIV����Խ��ͼ���Խ��
#define SCC8660_PCLK_MODE_DEF   (0  )                                           // PCLKģʽ     Ĭ�ϣ�0         ��ѡ����Ϊ��[0,1] 0������������ź� 1����������ź� <ͨ��������Ϊ0�����ʹ��STM32��DCMI�ӿڲɼ���Ҫ����Ϊ1>
#define SCC8660_COLOR_MODE_DEF  (1  )                                           // ͼ��ɫ��ģʽ Ĭ�ϣ�0         ��ѡ����Ϊ��[0,1] 0��������ɫģʽ   1������ģʽ��ɫ�ʱ��Ͷ���ߣ�
#define SCC8660_DATA_FORMAT_DEF (0  )                                           // ������ݸ�ʽ Ĭ�ϣ�0         ��ѡ����Ϊ��[0-3] 0��RGB565 1��RGB565(�ֽڽ���) 2��YUV422(YUYV) 3��YUV422(UYVY)
#define SCC8660_MANUAL_WB_DEF   (0  )                                           // �ֶ���ƽ��   Ĭ�ϣ�0         ��ѡ����Ϊ��[0,0x65-0xa0] 0���ر��ֶ���ƽ�⣬�����Զ���ƽ��    �������ֶ���ƽ�� �ֶ���ƽ��ʱ ������Χ0x65-0xa0

// ����ͷ����ö��
typedef enum
{
    SCC8660_INIT                = 0x00,                                         // ����ͷ��ʼ������
    SCC8660_AUTO_EXP,                                                           // �Զ��ع�����
    SCC8660_BRIGHT,                                                             // ��������
    SCC8660_FPS,                                                                // ����ͷ֡������
    SCC8660_SET_COL,                                                            // ͼ��������
    SCC8660_SET_ROW,                                                            // ͼ��������
    SCC8660_PCLK_DIV,                                                           // ����ʱ�ӷ�Ƶ����
    SCC8660_PCLK_MODE,                                                          // ����ʱ��ģʽ����
    SCC8660_COLOR_MODE,                                                         // ɫ��ģʽ����
    SCC8660_DATA_FORMAT,                                                        // ���ݸ�ʽ����
    SCC8660_MANUAL_WB,                                                          // �ֶ���ƽ������
    SCC8660_CONFIG_FINISH,                                                      // ������λ����Ҫ����ռλ����
        
    SCC8660_GET_WHO_AM_I        = 0xEF,                                         // ����˭��������ж�����ͷ�ͺ�
    SCC8660_SET_BRIGHT          = 0xF0,                                         // ������������
    SCC8660_GET_STATUS          = 0XF1,                                         // ��ȡ����ͷ��������
    SCC8660_GET_VERSION         = 0xF2,                                         // �̼��汾��
    SCC8660_SET_MANUAL_WB       = 0xF3,                                         // ���������ֶ���ƽ��
        
    SCC8660_SET_REG_ADDR        = 0xFE, 
    SCC8660_SET_REG_DATA        = 0xFF, 
}scc8660_cmd_enum;

#if (FRAME_SIZE == SCC8660_QVGA)
extern volatile uint32_t g_camera_buffer[320*240/2];
#elif (FRAME_SIZE == SCC8660_QQVGA)
extern volatile uint32_t g_camera_buffer[120*160/2];
#endif

extern uint16_t     *scc8660_image;
extern vuint8       scc8660_finish_flag;                                        // һ��ͼ��ɼ���ɱ�־λ
extern uint32       scc8660_frame_size;

uint8       scc8660_set_brightness      (uint16 data);
uint8       scc8660_set_white_balance   (uint16 data);
uint8       scc8660_set_reg             (uint8 addr, uint16 data);

uint8       scc8660_init                (void);

#endif
