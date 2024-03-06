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
* �ļ�����          zf_device_scc8660_flexio
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
*                   TXD                 �鿴 zf_device_scc8660_flexio.h �� SCC8660_FLEXIO_COF_UART_TX �궨��
*                   RXD                 �鿴 zf_device_scc8660_flexio.h �� SCC8660_FLEXIO_COF_UART_RX �궨��
*                   PCLK                �鿴 zf_device_scc8660_flexio.h �� SCC8660_FLEXIO_PCLK_PIN �궨��
*                   VSY                 �鿴 zf_device_scc8660_flexio.h �� SCC8660_FLEXIO_VSYNC_PIN �궨��
*                   D0-D7               �鿴 zf_device_scc8660_flexio.h �� SCC8660_FLEXIO_DATA_PIN �궨�� �Ӹö��忪ʼ�������˸�����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/

#ifndef _zf_device_scc8660_flexio_h_
#define _zf_device_scc8660_flexio_h_

#include "zf_common_typedef.h"

//--------------------------------------------------------------------------------------------------
// ��������
//--------------------------------------------------------------------------------------------------
#define SCC8660_FLEXIO_COF_UART         (UART_4     )                           // ��������ͷ��ʹ�õ��Ĵ���
#define SCC8660_FLEXIO_COF_BAUR         (9600       )                           // ��ͫ���ô��ڲ�����
#define SCC8660_FLEXIO_COF_UART_TX      (UART4_RX_C17)                          // ��ͫ UART-TX ���� Ҫ���ڵ�Ƭ�� RX ��
#define SCC8660_FLEXIO_COF_UART_RX      (UART4_TX_C16)                          // ��ͫ UART-RX ���� Ҫ���ڵ�Ƭ�� TX ��

#define SCC8660_FLEXIO_COF_IIC_DELAY    (800)                                   // ��ͫ IIC ��ʱ
#define SCC8660_FLEXIO_COF_IIC_SCL      (C17)                                   // ��ͫ IIC-SCL ����
#define SCC8660_FLEXIO_COF_IIC_SDA      (C16)                                   // ��ͫ IIC-SDA ����

#define SCC8660_FLEXIO_DMA_CH           (DMA_CH0)                               // ��������ͷ��DMA�ɼ�ͨ��

#define SCC8660_FLEXIO_VSYNC_PIN        C7                                      // ���ж�����
#define SCC8660_FLEXIO_VSYNC_IRQN       GPIO2_Combined_0_15_IRQn                // �жϺ�
    
    
#define SCC8660_FLEXIO_DATA_PIN         FLEXIO2_D08_C8                          // ����D0��������  ����D0����ΪFLEXIO2_D08_C8 ��ôD1��ʹ�õ�������ΪFLEXIO2_D09_C9����������
#define SCC8660_FLEXIO_PCLK_PIN         FLEXIO2_D05_C5                          // ��������ʱ������
#define SCC8660_FLEXIO_HREF_PIN         FLEXIO2_D06_C6                          // �������ź�����


#define SCC8660_FLEXIO_INIT_TIMEOUT    (0x0080)                                 // Ĭ�ϵ�����ͷ��ʼ����ʱʱ�� ����Ϊ��λ

//--------------------------------------------------------------------------------------------------
// ����ͷĬ�ϲ������� �ڴ��޸�����ͷ����
//--------------------------------------------------------------------------------------------------
#define SCC8660_FLEXIO_W               (160)                                    // ʵ��ͼ��ֱ��ʿ�� ��ѡ����Ϊ��160 180
#define SCC8660_FLEXIO_H               (120)                                    // ʵ��ͼ��ֱ��ʸ߶� ��ѡ����Ϊ��120 160
#define SCC8660_FLEXIO_IMAGE_SIZE      (SCC8660_FLEXIO_W * 2 * SCC8660_FLEXIO_H)// ����ͼ���С SCC8660_W*2*SCC8660_H ���ܳ��� 65535

#define SCC8660_FLEXIO_AUTO_EXP_DEF    (0  )                                    // �Զ��ع�     Ĭ�ϲ������Զ��ع�����  ��Χ [0-1] 0Ϊ�ر�
#define SCC8660_FLEXIO_BRIGHT_DEF      (800)                                    // ��������     �ֶ��ع�Ĭ�ϣ�300   �ֶ��ع�ʱ��������Χ0-65535   �Զ��ع��Ƽ�ֵ��100 �Զ��ع�ʱ�������÷�Χ0-255
#define SCC8660_FLEXIO_FPS_DEF         (50 )                                    // ͼ��֡��     Ĭ�ϣ�50        ��ѡ����Ϊ��60 50 30 25�� ʵ��֡�ʻ���Ҫ��SCC8660_PCLK_DIV����������
#define SCC8660_FLEXIO_PCLK_DIV_DEF    (2  )                                    // PCLK��Ƶϵ�� Ĭ�ϣ�2         ��ѡ����Ϊ��<0:1/1> <1:2/3> <2:1/2> <3:1/3> <4:1/4> <5:1/8>
                                                                                //              ��Ƶϵ��Խ��PCLKƵ��Խ�ͣ�����PCLK���Լ���DVP�ӿڵĸ��ţ�������PCLKƵ�����Ӱ��֡�ʡ��������������뱣��Ĭ�ϡ�
                                                                                //              ��������FPSΪ50֡������pclk��Ƶϵ��ѡ���Ϊ5��������ͷ�����֡��Ϊ50*��1/8��=6.25֡
                                                                                //              �����������������£�SCC8660_PCLK_DIV����Խ��ͼ���Խ��
#define SCC8660_FLEXIO_PCLK_MODE_DEF   (0  )                                    // PCLKģʽ     Ĭ�ϣ�0         ��ѡ����Ϊ��[0,1] 0������������ź� 1����������ź� <ͨ��������Ϊ0�����ʹ��STM32��DCMI�ӿڲɼ���Ҫ����Ϊ1>
#define SCC8660_FLEXIO_COLOR_MODE_DEF  (0  )                                    // ͼ��ɫ��ģʽ Ĭ�ϣ�0         ��ѡ����Ϊ��[0,1] 0��������ɫģʽ   1������ģʽ��ɫ�ʱ��Ͷ���ߣ�
#define SCC8660_FLEXIO_DATA_FORMAT_DEF (0  )                                    // ������ݸ�ʽ Ĭ�ϣ�0         ��ѡ����Ϊ��[0-3] 0��RGB565 1��RGB565(�ֽڽ���) 2��YUV422(YUYV) 3��YUV422(UYVY)
#define SCC8660_FLEXIO_MANUAL_WB_DEF   (0  )                                    // �ֶ���ƽ��   Ĭ�ϣ�0         ��ѡ����Ϊ��[0,0x65-0xa0] 0���ر��ֶ���ƽ�⣬�����Զ���ƽ��    �������ֶ���ƽ�� �ֶ���ƽ��ʱ ������Χ0x65-0xa0

// ����ͷ����ö��
typedef enum
{
    SCC8660_FLEXIO_INIT                = 0x00,                                  // ����ͷ��ʼ������
    SCC8660_FLEXIO_AUTO_EXP,                                                    // �Զ��ع�����
    SCC8660_FLEXIO_BRIGHT,                                                      // ��������
    SCC8660_FLEXIO_FPS,                                                         // ����ͷ֡������
    SCC8660_FLEXIO_SET_COL,                                                     // ͼ��������
    SCC8660_FLEXIO_SET_ROW,                                                     // ͼ��������
    SCC8660_FLEXIO_PCLK_DIV,                                                    // ����ʱ�ӷ�Ƶ����
    SCC8660_FLEXIO_PCLK_MODE,                                                   // ����ʱ��ģʽ����
    SCC8660_FLEXIO_COLOR_MODE,                                                  // ɫ��ģʽ����
    SCC8660_FLEXIO_DATA_FORMAT,                                                 // ���ݸ�ʽ����
    SCC8660_FLEXIO_MANUAL_WB,                                                   // �ֶ���ƽ������
    SCC8660_FLEXIO_CONFIG_FINISH,                                               // ������λ����Ҫ����ռλ����
            
    SCC8660_FLEXIO_GET_WHO_AM_I        = 0xEF,                                  // ����˭��������ж�����ͷ�ͺ�
    SCC8660_FLEXIO_SET_BRIGHT          = 0xF0,                                  // ������������
    SCC8660_FLEXIO_GET_STATUS          = 0XF1,                                  // ��ȡ����ͷ��������
    SCC8660_FLEXIO_GET_VERSION         = 0xF2,                                  // �̼��汾��
    SCC8660_FLEXIO_SET_MANUAL_WB       = 0xF3,                                  // ���������ֶ���ƽ��
        
    SCC8660_FLEXIO_SET_REG_ADDR        = 0xFE, 
    SCC8660_FLEXIO_SET_REG_DATA        = 0xFF, 
}scc8660_flexio_cmd_enum;

// ����ͷ�ӿ�����ö��
typedef enum
{
    SCC8660_FLEXIO_UART,
    SCC8660_FLEXIO_SCCB,
}scc8660_flexio_type_enum;

extern vuint8       scc8660_flexio_finish_flag;                                 // һ��ͼ��ɼ���ɱ�־λ
extern uint16       scc8660_flexio_image[SCC8660_FLEXIO_H][SCC8660_FLEXIO_W];


uint16      scc8660_flexio_get_id              (void);
uint16      scc8660_flexio_get_parameter       (uint16 config);
uint16      scc8660_flexio_get_version         (void);
uint8       scc8660_flexio_set_brightness      (uint16 data);
uint8       scc8660_flexio_set_white_balance   (uint16 data);
uint8       scc8660_flexio_set_reg             (uint8 addr, uint16 data);

// ����RT1064��˵���������ӿڶ����Բɼ�����ͷһ����CSI�ӿ� һ����FLEXIO�ӿ�
// ��ֻ��Ҫʹ��һ������ͷ��ʱ���Ƽ�ʹ��CSI�ӿڲɼ�����ͷ��Ҳ���ǵ���scc8660_init��ʼ������ͷ����
// ����Ҫ�ɼ���������ͷ��ʱ����Էֱ����scc8660_init �� scc8660_flexio_init��ʼ����������ͷ
uint8       scc8660_flexio_init                 (void);

#endif
