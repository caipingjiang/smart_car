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
* �ļ�����          zf_driver_flexio_csi
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

#ifndef _zf_driver_flexio_csi_h_
#define _zf_driver_flexio_csi_h_


#include "zf_common_typedef.h"
#include "fsl_edma.h"


//��ö�ٶ��岻�����û��޸�
typedef enum    //FLEXIO ���Ŷ���
{
    FLEXIO2_D00_C0,
    FLEXIO2_D01_C1,
    FLEXIO2_D02_C2,
    FLEXIO2_D03_C3,
    FLEXIO2_D04_C4,
    FLEXIO2_D05_C5,
    FLEXIO2_D06_C6,
    FLEXIO2_D07_C7,
    FLEXIO2_D08_C8,
    FLEXIO2_D09_C9,
    FLEXIO2_D10_C10,
    FLEXIO2_D11_C11,
    FLEXIO2_D12_C12,
    FLEXIO2_D13_C13,
    FLEXIO2_D14_C14,
    FLEXIO2_D15_C15,
    FLEXIO2_D16_C16,
    FLEXIO2_D17_C17,
    FLEXIO2_D18_C18,
    FLEXIO2_D19_C19,
    FLEXIO2_D20_C20,
    FLEXIO2_D21_C21,
    FLEXIO2_D22_C22,
    FLEXIO2_D23_C23,
    FLEXIO2_D24_C24,
    FLEXIO2_D25_C25,
    FLEXIO2_D26_C26,
    FLEXIO2_D27_C27,
    FLEXIO2_D28_C28,
    FLEXIO2_D29_C29,
    FLEXIO2_D30_C30,
    FLEXIO2_D31_C31,
}flexio_pin_enum;






void flexio_csi_enable(uint8 enable);
void flexio_csi_flag_clear(void);
void flexio_csi_dma_restart(uint8 *dest_addr);
void flexio_csi_enable_rxdma(void);
void flexio_csi_init(flexio_pin_enum dat_pin_start, flexio_pin_enum pclk_pin, flexio_pin_enum href_pin, uint16 width, uint16 height, uint8 *dest_addr, edma_callback callback);

















#endif
