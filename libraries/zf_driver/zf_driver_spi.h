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
* �ļ�����          zf_driver_spi
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

#ifndef _zf_driver_spi_h_
#define _zf_driver_spi_h_

#include "zf_common_typedef.h"

#define SPI_SPEED_PRIORITY                                                      // SPI ͨ���ٶ�����

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    // SPI1 ���� SCK
    SPI1_SCK_D12    = 1 * 16, 
    
    // SPI3 ���� SCK
    SPI3_SCK_B0     = 3 * 16, SPI3_SCK_B31, 
    
    // SPI4 ���� SCK
    SPI4_SCK_C3     = 4 * 16, SPI4_SCK_C23 ,
}spi_sck_pin_enum;

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    // SPI1 ���� MOSI
    SPI1_MOSI_D14   = 1 * 16,
   
    // SPI3 ���� MOSI
    SPI3_MOSI_B1    = 3 * 16, SPI3_MOSI_B30,
    
    // SPI4 ���� MOSI
    SPI4_MOSI_C2    = 4 * 16, SPI4_MOSI_C22,
}spi_mosi_pin_enum;

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    SPI_MISO_NULL   = 0xFFFF,                                                   // ��ʹ��Ӳ�� MISO ���ž������
    
    // SPI1 ���� MISO
    SPI1_MISO_D15   = 1 * 16, 
    
    // SPI3 ���� MISO
    SPI3_MISO_B2    = 3 * 16, SPI3_MISO_B29,
    
    // SPI4 ���� MISO
    SPI4_MISO_C1    = 4 * 16, SPI4_MISO_C21,
}spi_miso_pin_enum;

typedef enum                                                                    // ö�ٴ������� ��ö�ٶ��岻�����û��޸�
{
    SPI_CS_NULL     = 0xFFFF,                                                   // ��ʹ��Ӳ�� CS ���ž������
    
    SPI1_CS0_D13    = 1 * 16 + 2 * 0,
    SPI1_CS2_D26    = 1 * 16 + 2 * 2,
    SPI1_CS3_D27    = 1 * 16 + 2 * 3,
        
    SPI3_CS0_B3     = 3 * 16 + 2 * 0, SPI3_CS0_B28,
        
    SPI4_CS0_C0     = 4 * 16 + 2 * 0, SPI4_CS0_C20 ,
    SPI4_CS1_C19    = 4 * 16 + 2 * 1,
    SPI4_CS2_C18    = 4 * 16 + 2 * 2,
    SPI4_CS3_C27    = 4 * 16 + 2 * 3,
}spi_cs_pin_enum;

typedef enum                                                                    // ö�� SPI ģʽ ��ö�ٶ��岻�����û��޸�
{
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3,
}spi_mode_enum;

typedef enum                                                                    // ö�� SPI ��� ��ö�ٶ��岻�����û��޸�
{
    SPI_1 = 1,
    SPI_3 = 3,
    SPI_4,
    SPI_MAX,
}spi_index_enum;

void        spi_write_8bit                  (spi_index_enum spi_n, const uint8 data);
void        spi_write_8bit_array            (spi_index_enum spi_n, const uint8 *data, uint32 len);

void        spi_write_16bit                 (spi_index_enum spi_n, const uint16 data);
void        spi_write_16bit_array           (spi_index_enum spi_n, const uint16 *data, uint32 len);

void        spi_write_8bit_register         (spi_index_enum spi_n, const uint8 register_name, const uint8 data);
void        spi_write_8bit_registers        (spi_index_enum spi_n, const uint8 register_name, const uint8 *data, uint32 len);

void        spi_write_16bit_register        (spi_index_enum spi_n, const uint16 register_name, const uint16 data);
void        spi_write_16bit_registers       (spi_index_enum spi_n, const uint16 register_name, const uint16 *data, uint32 len);

uint8       spi_read_8bit                   (spi_index_enum spi_n);
void        spi_read_8bit_array             (spi_index_enum spi_n, uint8 *data, uint32 len);

uint16      spi_read_16bit                  (spi_index_enum spi_n);
void        spi_read_16bit_array            (spi_index_enum spi_n, uint16 *data, uint32 len);

uint8       spi_read_8bit_register          (spi_index_enum spi_n, const uint8 register_name);
void        spi_read_8bit_registers         (spi_index_enum spi_n, const uint8 register_name, uint8 *data, uint32 len);

uint16      spi_read_16bit_register         (spi_index_enum spi_n, const uint16 register_name);
void        spi_read_16bit_registers        (spi_index_enum spi_n, const uint16 register_name, uint16 *data, uint32 len);

void        spi_transfer_8bit               (spi_index_enum spi_n, const uint8 *write_buffer, uint8 *read_buffer, uint32 len);
void        spi_transfer_16bit              (spi_index_enum spi_n, const uint16 *write_buffer, uint16 *read_buffer, uint32 len);

void        spi_init                        (spi_index_enum spi_n, spi_mode_enum mode, uint32 baud, spi_sck_pin_enum sck_pin, spi_mosi_pin_enum mosi_pin, spi_miso_pin_enum miso_pin, spi_cs_pin_enum cs_pin);

#ifdef COMPATIBLE_WITH_OLDER_VERSIONS                                           // ���ݾɰ汾��Դ��ӿ�����
#define spi_mosi(spi_n, mosi, miso, len)    (spi_transfer_8bit((spi_n), (mosi), (miso), (len)))
#endif

#endif
