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
* �ļ�����          zf_driver_iic
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

#ifndef _zf_driver_iic_h_
#define _zf_driver_iic_h_

#include "zf_common_typedef.h"

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    // IIC 1 ���� SCL
    IIC1_SCL_B16 = 16 * 1,  IIC1_SCL_D4 ,

    // IIC 2 ���� SCL
    IIC2_SCL_C4  = 16 * 2,
    
    // IIC 3 ���� SCL
    IIC3_SCL_B23 = 16 * 3,  IIC3_SCL_D12,
    
    // IIC 4 ���� SCL
    IIC4_SCL_B12 = 16 * 4,
}iic_scl_pin_enum;

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{

    // IIC 1 ���� SDA
    IIC1_SDA_B17 = 16 * 1,

    // IIC 2 ���� SDA
    IIC2_SDA_C5  = 16 * 2,

    // IIC 3 ���� SDA
    IIC3_SDA_B22 = 16 * 3,  IIC3_SDA_D13,

    // IIC 4 ���� SDA
    IIC4_SDA_B13 = 16 * 4,
}iic_sda_pin_enum;


typedef enum                                                                    // ö�� IIC ����״̬ ��ö�ٶ��岻�����û��޸�
{
    IIC_SUCCESS,
    IIC_WRITE_TIMEOUT,
    IIC_READ_TIMEOUT,
}iic_state_enum;

typedef enum                                                                    // ö�� IIC ��� ��ö�ٶ��岻�����û��޸�
{
    IIC_1 = 1,
    IIC_2,
    IIC_3,
    IIC_4,
}iic_index_enum;

void        iic_write_8bit              (iic_index_enum iic_n, uint8 target_addr, const uint8 data);
void        iic_write_8bit_array        (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len);

void        iic_write_16bit             (iic_index_enum iic_n, uint8 target_addr, const uint16 data);
void        iic_write_16bit_array       (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len);

void        iic_write_8bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data);
void        iic_write_8bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len);

void        iic_write_16bit_register    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data);
void        iic_write_16bit_registers   (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len);

uint8       iic_read_8bit               (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_8bit_array         (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len);

uint16      iic_read_16bit              (iic_index_enum iic_n, uint8 target_addr);
void        iic_read_16bit_array        (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len);

uint8       iic_read_8bit_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);
void        iic_read_8bit_registers     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len);

uint16      iic_read_16bit_register     (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name);
void        iic_read_16bit_registers    (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len);

void        iic_transfer_8bit_array     (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len);
void        iic_transfer_16bit_array    (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len);

void        iic_sccb_write_register     (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data);
uint8       iic_sccb_read_register      (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name);

void        iic_init                    (iic_index_enum iic_n, uint8 addr, uint32 baud, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // ���ݾɰ汾��Դ��ӿ�����

#endif

#endif
