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

#ifndef _zf_driver_encoder_h_
#define _zf_driver_encoder_h_

#include "zf_common_typedef.h"

typedef enum
{
    QTIMER1_ENCODER1_CH1_C0  = 2 * 2, 
    QTIMER1_ENCODER2_CH1_C2  = 3 * 2,
                                    
    QTIMER2_ENCODER1_CH1_C3  = 4 * 2,                                            
    QTIMER2_ENCODER2_CH1_C5  = 5 * 2, 
                                    
    QTIMER3_ENCODER1_CH1_B16 = 6 * 2, QTIMER3_ENCODER1_CH1_C6,                        
    QTIMER3_ENCODER2_CH1_B18 = 7 * 2, QTIMER3_ENCODER2_CH1_C8,                         
                                    
    QTIMER4_ENCODER1_CH1_C9  = 8 * 2,
    QTIMER4_ENCODER2_CH1_C11 = 9 * 2,
}encoder_channel1_enum;             
                                    
typedef enum                        
{                                   
    QTIMER1_ENCODER1_CH2_C1  = 2 * 2,
    QTIMER1_ENCODER2_CH2_C24 = 3 * 2,
                                            
    QTIMER2_ENCODER1_CH2_C4  = 4 * 2, QTIMER2_ENCODER1_CH2_C25,
    QTIMER2_ENCODER2_CH2_C25 = 5 * 2,
                                   
    QTIMER3_ENCODER1_CH2_B17 = 6 * 2, QTIMER3_ENCODER1_CH2_C7,                         
    QTIMER3_ENCODER2_CH2_B19 = 7 * 2, QTIMER3_ENCODER2_CH2_C26,  
                                            
    QTIMER4_ENCODER1_CH2_C10 = 8 * 2,
    QTIMER4_ENCODER2_CH2_C27 = 9 * 2,
}encoder_channel2_enum;

typedef enum
{
    QTIMER1_ENCODER1 = 2,
    QTIMER1_ENCODER2,
    
    QTIMER2_ENCODER1,
    QTIMER2_ENCODER2,
    
    QTIMER3_ENCODER1,
    QTIMER3_ENCODER2,
    
    QTIMER4_ENCODER1,
    QTIMER4_ENCODER2,
}encoder_index_enum;

int16   encoder_get_count       (encoder_index_enum encoder_n);
void    encoder_clear_count     (encoder_index_enum encoder_n);

void    encoder_quad_init       (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);
void    encoder_dir_init        (encoder_index_enum encoder_n, encoder_channel1_enum ch1_pin, encoder_channel2_enum ch2_pin);

#endif
