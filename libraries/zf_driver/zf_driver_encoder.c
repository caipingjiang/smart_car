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
* �ļ�����          zf_driver_encoder
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

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "fsl_qtmr.h"
#include "fsl_iomuxc.h"
#include "zf_driver_gpio.h"

#include "zf_driver_encoder.h"

#define QTMR_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_IpgClk)
#define QTIMER_PIN_CONF  SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //����QTIMER����Ĭ������

TMR_Type * qtimer_index[] = TMR_BASE_PTRS;

void qtimer_iomuxc(encoder_index_enum qtimern, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    switch(qtimern)
    {
        case QTIMER1_ENCODER1:
        {
            if      (QTIMER1_ENCODER1_CH1_C0  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_00_QTIMER1_TIMER0,     0, QTIMER_PIN_CONF);
            if      (QTIMER1_ENCODER1_CH2_C1  == ch2_pin)  afio_init(IOMUXC_GPIO_B0_01_QTIMER1_TIMER1,     0, QTIMER_PIN_CONF);
        }break; 
            
        case QTIMER1_ENCODER2: 
        {   
            if      (QTIMER1_ENCODER2_CH1_C2  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_02_QTIMER1_TIMER2,     0, QTIMER_PIN_CONF);
            if      (QTIMER1_ENCODER2_CH2_C24 == ch2_pin)  afio_init(IOMUXC_GPIO_B1_08_QTIMER1_TIMER3,     0, QTIMER_PIN_CONF);
        }break; 
            
        case QTIMER2_ENCODER1: 
        {   
            if      (QTIMER2_ENCODER1_CH1_C3  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_03_QTIMER2_TIMER0,     0, QTIMER_PIN_CONF);
            if      (QTIMER2_ENCODER1_CH2_C4  == ch2_pin)  afio_init(IOMUXC_GPIO_B0_04_QTIMER2_TIMER1,     0, QTIMER_PIN_CONF);
            else if (QTIMER2_ENCODER1_CH2_C25 == ch2_pin)  afio_init(IOMUXC_GPIO_B1_09_QTIMER2_TIMER3,     0, QTIMER_PIN_CONF);
        }break; 
            
        case QTIMER2_ENCODER2: 
        {   
            if      (QTIMER2_ENCODER2_CH1_C5  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_05_QTIMER2_TIMER2,     0, QTIMER_PIN_CONF);
            if      (QTIMER2_ENCODER2_CH2_C25 == ch2_pin)  afio_init(IOMUXC_GPIO_B1_09_QTIMER2_TIMER3,     0, QTIMER_PIN_CONF);
        }break;

        case QTIMER3_ENCODER1:
        {
            if      (QTIMER3_ENCODER1_CH1_B16 == ch1_pin)  afio_init(IOMUXC_GPIO_AD_B1_00_QTIMER3_TIMER0,  0, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCODER1_CH1_C6  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_06_QTIMER3_TIMER0,     0, QTIMER_PIN_CONF);
            
            if (QTIMER3_ENCODER1_CH2_B17 == ch2_pin)  afio_init(IOMUXC_GPIO_AD_B1_01_QTIMER3_TIMER1,  0, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCODER1_CH2_C7  == ch2_pin)  afio_init(IOMUXC_GPIO_B0_07_QTIMER3_TIMER1,     0, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER3_ENCODER2:
        {
            if      (QTIMER3_ENCODER2_CH1_B18 == ch1_pin)  afio_init(IOMUXC_GPIO_AD_B1_02_QTIMER3_TIMER2,  0, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCODER2_CH1_C8  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_08_QTIMER3_TIMER2,     0, QTIMER_PIN_CONF);
            
            if      (QTIMER3_ENCODER2_CH2_B19 == ch2_pin)  afio_init(IOMUXC_GPIO_AD_B1_03_QTIMER3_TIMER3,  0, QTIMER_PIN_CONF);
            else if (QTIMER3_ENCODER2_CH2_C26 == ch2_pin)  afio_init(IOMUXC_GPIO_B1_10_QTIMER3_TIMER3,     0, QTIMER_PIN_CONF);
        }break;
        
        case QTIMER4_ENCODER1:
        {
            if      (QTIMER4_ENCODER1_CH1_C9  == ch1_pin)  afio_init(IOMUXC_GPIO_B0_09_QTIMER4_TIMER0,     0, QTIMER_PIN_CONF);
            if      (QTIMER4_ENCODER1_CH2_C10 == ch2_pin)  afio_init(IOMUXC_GPIO_B0_10_QTIMER4_TIMER1,     0, QTIMER_PIN_CONF);
        }break;     
                
        case QTIMER4_ENCODER2:    
        {       
            if      (QTIMER4_ENCODER2_CH1_C11 == ch1_pin)  afio_init(IOMUXC_GPIO_B0_11_QTIMER4_TIMER2,     0, QTIMER_PIN_CONF);
            if      (QTIMER4_ENCODER2_CH2_C27 == ch2_pin)  afio_init(IOMUXC_GPIO_B1_11_QTIMER4_TIMER3,     0, QTIMER_PIN_CONF);
        }break;
        
        default: zf_assert(0);break;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER �ӿڻ�ȡ����������
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ���ز���     int16           ��������ֵ
// ʹ��ʾ��     encoder_get_count(QTIMER1_ENCOEDER1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
int16 encoder_get_count (encoder_index_enum encoder_n)
{
    uint8 qtimer_cha;
    qtimer_cha = (encoder_n % 2) * 2;                                                           // ����Aͨ��
    return QTMR_GetCurrentTimerCount(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER ��ձ���������
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     encoder_clear_count(QTIMER1_ENCOEDER1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void encoder_clear_count (encoder_index_enum encoder_n)
{
    uint8 qtimer_cha;
    qtimer_cha = (encoder_n % 2) * 2;                                                           // ����Aͨ��
    qtimer_index[encoder_n / 2]->CHANNEL[qtimer_cha].CNTR = 0;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER �ӿڳ�ʼ�� ����������ʹ��
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ����˵��     ch1_pin         ENCODER ͨ�� 1 ���� zf_driver_encoder.h �� encoder_channel1_enum ö���嶨��
// ����˵��     ch2_pin         ENCODER ͨ�� 2 ���� zf_driver_encoder.h �� encoder_channel2_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     encoder_quad_init(QTIMER1_ENCOEDER1, QTIMER1_ENCOEDER1_CH1_C0, QTIMER1_ENCOEDER1_CH2_C1);
// ��ע��Ϣ     ʹ�õı������������������ſ���ʹ�ô˺����ӿ�
//              �������ν�� ������������������ �ı����� �鷳��ȷ���������ǲ������������������
//              ����ӿ�ֻ�ܸ�������������źŵı�������
//-------------------------------------------------------------------------------------------------------------------
void encoder_quad_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    uint8 qtimer_cha;
    uint8 qtimer_chb;
    qtmr_config_t qtmrConfig;
    
    zf_assert(encoder_n == (ch1_pin / 2));                                                      // ch1_pin ������ encoder_n ƥ��
    zf_assert(encoder_n == (ch2_pin / 2));                                                      // ch2_pin ������ encoder_n ƥ��
    
    qtimer_iomuxc(encoder_n, ch1_pin, ch2_pin);

    qtimer_cha = (encoder_n % 2) * 2;                                                           // ����Aͨ��
    if(QTIMER2_ENCODER1_CH2_C25 == ch2_pin)
    {
        qtimer_chb = 3;
    }
    else
    {
        qtimer_chb = qtimer_cha + 1;
    }
    
    QTMR_GetDefaultConfig(&qtmrConfig);
    qtmrConfig.primarySource = (qtmr_primary_count_source_t)(qtimer_cha);
    qtmrConfig.secondarySource = (qtmr_input_source_t)(qtimer_chb);
    QTMR_Init(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), &qtmrConfig);// ��һ�γ�ʼ�����ڴ�ʱ��
    QTMR_Deinit(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha));           // ��λ����
    QTMR_Init(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), &qtmrConfig);// ���³�ʼ��������ȷ�Ĳ���
    
    QTMR_StartTimer(qtimer_index[encoder_n / 2], (qtmr_channel_selection_t)(qtimer_cha), kQTMR_PriSrcRiseEdgeSecDir);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ENCODER �ӿڳ�ʼ�� �����������ʹ��
// ����˵��     encoder_n       ENCODER ģ��� ���� zf_driver_encoder.h �� encoder_index_enum ö���嶨��
// ����˵��     ch1_pin         ENCODER ͨ�� 1 ���� zf_driver_encoder.h �� encoder_channel1_enum ö���嶨��
// ����˵��     ch2_pin         ENCODER ͨ�� 2 ���� zf_driver_encoder.h �� encoder_channel2_enum ö���嶨��
// ���ز���     void
// ʹ��ʾ��     encoder_dir_init(QTIMER1_ENCOEDER1, QTIMER1_ENCOEDER1_CH1_C0, QTIMER1_ENCOEDER1_CH2_C1);
// ��ע��Ϣ     ʹ�õı������Ǵ��������������ʽ�������ſ���ʹ�ô˺����ӿ�
//              ch1_pin ����Ϊ����������� ch2_pin ����Ϊ���������������
//              �˷�ʽ�� �ڳ��ַ�������ת������� �������򽫲�����ȫ�ɿ���
//              ֻ�ж�ȡʱ�̵� ch2_pin �ĵ�ƽ������������ֵ����������
//              ͬʱ ch1_pin ֻ��ѡ�� CH1 ͨ��������
//-------------------------------------------------------------------------------------------------------------------
void encoder_dir_init (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin)
{
    // RT1064��Ƭ�������������뷽����������ֱ��붼֧�֣����ʹ��ͬһ�������ӿڽ��вɼ�
    encoder_quad_init(encoder_n, ch1_pin, ch2_pin);
}
