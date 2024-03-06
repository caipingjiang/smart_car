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
* �ļ�����          zf_device_mt9v03x_flexio
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
*                   TXD                 �鿴 zf_device_mt9v03x_flexio.h �� MT9V03X_FLEXIO_COF_UART_TX �궨��
*                   RXD                 �鿴 zf_device_mt9v03x_flexio.h �� MT9V03X_FLEXIO_COF_UART_RX �궨��
*                   PCLK                �鿴 zf_device_mt9v03x_flexio.h �� MT9V03X_FLEXIO_PCLK_PIN �궨��
*                   VSY                 �鿴 zf_device_mt9v03x_flexio.h �� MT9V03X_FLEXIO_VSYNC_PIN �궨��
*                   D0-D7               �鿴 zf_device_mt9v03x_flexio.h �� MT9V03X_FLEXIO_DATA_PIN �궨�� �Ӹö��忪ʼ�������˸�����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_mt9v03x_flexio_h_
#define _zf_device_mt9v03x_flexio_h_

#include "zf_common_typedef.h"

//--------------------------------------------------------------------------------------------------
// ��������
//--------------------------------------------------------------------------------------------------
#define MT9V03X_FLEXIO_COF_UART        (UART_4     )                            // ��������ͷ��ʹ�õ��Ĵ���
#define MT9V03X_FLEXIO_COF_BAUR        (9600       )                            // ��������ô��ڲ�����
#define MT9V03X_FLEXIO_COF_UART_TX     (UART4_RX_C17)                           // ����� UART-TX ���� Ҫ���ڵ�Ƭ�� RX ��
#define MT9V03X_FLEXIO_COF_UART_RX     (UART4_TX_C16)                           // ����� UART-RX ���� Ҫ���ڵ�Ƭ�� TX ��

#define MT9V03X_FLEXIO_COF_IIC_DELAY   (800)                                    // ����� IIC ��ʱ
#define MT9V03X_FLEXIO_COF_IIC_SCL     (C17)                                    // ����� IIC-SCL ����
#define MT9V03X_FLEXIO_COF_IIC_SDA     (C16)                                    // ����� IIC-SDA ����

#define MT9V03X_FLEXIO_DMA_CH           (DMA_CH0)                               // ��������ͷ��DMA�ɼ�ͨ��

#define MT9V03X_FLEXIO_VSYNC_PIN        C7                                      // ���ж�����
#define MT9V03X_FLEXIO_VSYNC_IRQN       GPIO2_Combined_0_15_IRQn                // �жϺ�
    
    
#define MT9V03X_FLEXIO_DATA_PIN         FLEXIO2_D08_C8                          // ����D0��������  ����D0����ΪFLEXIO2_D08_C8 ��ôD1��ʹ�õ�������ΪFLEXIO2_D09_C9����������
#define MT9V03X_FLEXIO_PCLK_PIN         FLEXIO2_D05_C5                          // ��������ʱ������
#define MT9V03X_FLEXIO_HREF_PIN         FLEXIO2_D06_C6                          // �������ź�����


#define MT9V03X_FLEXIO_INIT_TIMEOUT    (0x0080)                                 // Ĭ�ϵ�����ͷ��ʼ����ʱʱ�� ����Ϊ��λ

//--------------------------------------------------------------------------------------------------
// ����ͷĬ�ϲ������� �ڴ��޸�����ͷ����
//--------------------------------------------------------------------------------------------------
#define MT9V03X_FLEXIO_W               (188)                                    // ͼ����     ��Χ [1-752] 	ֻ����4�ı���
#define MT9V03X_FLEXIO_H               (120)                                    // ͼ��߶�     ��Χ [1-480]	ֻ����4�ı���
#define MT9V03X_FLEXIO_IMAGE_SIZE      (MT9V03X_W * MT9V03X_H)                  // 
    
#define MT9V03X_FLEXIO_AUTO_EXP_DEF    (0  )                                    // �Զ��ع�����     Ĭ�ϲ������Զ��ع�����  ��Χ [0-63] 0Ϊ�ر�
                                                                                //                  ����Զ��ع⿪��  EXP_TIME���������Զ��ع�ʱ�������
                                                                                //                  һ������ǲ���Ҫ�����Զ��ع����� ����������߷ǳ������ȵ�������Գ��������Զ��ع⣬����ͼ���ȶ���
#define MT9V03X_FLEXIO_EXP_TIME_DEF    (512)                                    // �ع�ʱ��         ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
#define MT9V03X_FLEXIO_FPS_DEF         (50 )                                    // ͼ��֡��         ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
#define MT9V03X_FLEXIO_LR_OFFSET_DEF   (0  )                                    // ͼ������ƫ����   ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��
                                                                                //                  ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
#define MT9V03X_FLEXIO_UD_OFFSET_DEF   (0  )                                    // ͼ������ƫ����   ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��
                                                                                //                  ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
#define MT9V03X_FLEXIO_GAIN_DEF        (32 )                                    // ͼ������         ��Χ [16-64]  ����������ع�ʱ��̶�������¸ı�ͼ�������̶�
#define MT9V03X_FLEXIO_PCLK_MODE_DEF   (0  )                                    // ����ʱ��ģʽ     ��Χ [0-1]    Ĭ�ϣ�0 ��ѡ����Ϊ��[0������������ź�,1����������ź�]
                                                                                //                  ͨ��������Ϊ0�����ʹ��CH32V307��DVP�ӿڻ�STM32��DCMI�ӿڲɼ���Ҫ����Ϊ1
                                                                                //                  ������� MT9V034 V1.5 �Լ����ϰ汾֧�ָ�����

// ����ͷ����ö��
typedef enum
{
    MT9V03X_FLEXIO_INIT = 0,                                                    // ����ͷ��ʼ������
    MT9V03X_FLEXIO_AUTO_EXP,                                                    // �Զ��ع�����
    MT9V03X_FLEXIO_EXP_TIME,                                                    // �ع�ʱ������
    MT9V03X_FLEXIO_FPS,                                                         // ����ͷ֡������
    MT9V03X_FLEXIO_SET_COL,                                                     // ͼ��������
    MT9V03X_FLEXIO_SET_ROW,                                                     // ͼ��������
    MT9V03X_FLEXIO_LR_OFFSET,                                                   // ͼ������ƫ������
    MT9V03X_FLEXIO_UD_OFFSET,                                                   // ͼ������ƫ������
    MT9V03X_FLEXIO_GAIN,                                                        // ͼ��ƫ������
    MT9V03X_FLEXIO_PCLK_MODE,                                                   // ����ʱ��ģʽ����(�������MT9V034 V1.5�Լ����ϰ汾֧�ָ�����)
    MT9V03X_FLEXIO_CONFIG_FINISH,                                               // ������λ����Ҫ����ռλ����
    
    MT9V03X_FLEXIO_COLOR_GET_WHO_AM_I = 0xEF,   
    MT9V03X_FLEXIO_SET_EXP_TIME = 0XF0,                                         // ���������ع�ʱ������
    MT9V03X_FLEXIO_GET_STATUS,                                                  // ��ȡ����ͷ��������
    MT9V03X_FLEXIO_GET_VERSION,                                                 // �̼��汾������
    
    MT9V03X_FLEXIO_SET_ADDR = 0XFE,                                             // �Ĵ�����ַ����
    MT9V03X_FLEXIO_SET_DATA                                                     // �Ĵ�����������
}m9v03x_flexio_cmd_enum;

// ����ͷ�ӿ�����ö��
typedef enum
{
    MT9V03X_FLEXIO_UART,
    MT9V03X_FLEXIO_SCCB,
}m9v03x_flexio_type_enum;

extern vuint8   mt9v03x_flexio_finish_flag;                                     // һ��ͼ��ɼ���ɱ�־λ
extern uint8    mt9v03x_flexio_image[MT9V03X_FLEXIO_H][MT9V03X_FLEXIO_W];

uint16      mt9v03x_flexio_get_version         (void);
uint8       mt9v03x_flexio_set_exposure_time   (uint16 light);
uint8       mt9v03x_flexio_set_reg             (uint8 addr, uint16 data);

// ����RT1064��˵���������ӿڶ����Բɼ�����ͷһ����CSI�ӿ� һ����FLEXIO�ӿ�
// ��ֻ��Ҫʹ��һ������ͷ��ʱ���Ƽ�ʹ��CSI�ӿڲɼ�����ͷ��Ҳ���ǵ���mt9v03x_init��ʼ������ͷ����
// ����Ҫ�ɼ���������ͷ��ʱ����Էֱ����mt9v03x_init �� mt9v03x_flexio_init��ʼ����������ͷ
uint8       mt9v03x_flexio_init                (void);

#endif
