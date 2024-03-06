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
* �ļ�����          zf_driver_flash
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

#ifndef _zf_driver_flash_h_
#define _zf_driver_flash_h_

#include "zf_common_typedef.h"

#define FLASH_BASE_ADDR             (0x70000000)
#define FLASH_PAGE_SIZE             (0x00001000)                                // 4K (ʵ����оƬ��Sector��С)
#define FLASH_PAGE_NUM              (8)                                         // һ����8������
#define FLASH_SECTOR_SIZE           (FLASH_PAGE_SIZE * FLASH_PAGE_NUM)          // 32K (ʵ����оƬBlock��С)
#define FLASH_OPERATION_TIME_OUT    (0x0FFF)

#define FLASH_PAGE_NUM_DRIVER       (16)

#define FLASH_DATA_BUFFER_SIZE      (FLASH_PAGE_SIZE / sizeof(flash_data_union))// �Զ�����ÿ��ҳ�ܹ����¶��ٸ�����

typedef union                                                                   // �̶������ݻ��嵥Ԫ��ʽ
{
    float   float_type;                                                         // float  ����
    uint32  uint32_type;                                                        // uint32 ����
    int32   int32_type;                                                         // int32  ����
    uint16  uint16_type;                                                        // uint16 ����
    int16   int16_type;                                                         // int16  ����
    uint8   uint8_type;                                                         // uint8  ����
    int8    int8_type;                                                          // int8   ����
}flash_data_union;                                                              // �����������ݹ���ͬһ�� 32bit ��ַ



typedef enum                                                                    // ö�� Flash ҳ���� ��ö�ٶ��岻�����û��޸�
{
    FLASH_PAGE_0,
    FLASH_PAGE_1,
    FLASH_PAGE_2,
    FLASH_PAGE_3,
    FLASH_PAGE_4,
    FLASH_PAGE_5,
    FLASH_PAGE_6,
    FLASH_PAGE_7,

}flash_page_enum;

extern flash_data_union flash_union_buffer[FLASH_DATA_BUFFER_SIZE];

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ�ú궨���flash�������ݶ�ȡ
//  @param      sector_num 		��Ҫд����������
//  @param      offset	 		��ַƫ�� ƫ��1���� Ϊ�ĸ��ֽ� ��Χ0-1023
//  @param      type		 	��ȡ����������
//  @return     				���ظ�����ַ������
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//��ȡ20������ƫ��0��������Ϊuint32
//  @note       ��Ҫ�ر�ע����� RTϵ����cache�������ÿ�ζ�ȡflash֮ǰ����SCB_InvalidateDCache();ִ�и�������cache
//              ������˵û��һ���������һ�£�
//-------------------------------------------------------------------------------------------------------------------
#define     flash_read(sector_num, page_num, offset, type)    (*(type *)((uint32)((FLASH_BASE_ADDR + sector_num*FLASH_SECTOR_SIZE + page_num*FLASH_PAGE_SIZE) + (offset*4))))

uint8       flash_check                     (uint32 sector_num, flash_page_enum page_num);
uint8       flash_erase_page                (uint32 sector_num, flash_page_enum page_num);
void        flash_read_page                 (uint32 sector_num, flash_page_enum page_num, uint32 *buf, uint16 len);
uint8       flash_write_page                (uint32 sector_num, flash_page_enum page_num, const uint32 *buf, uint16 len);

void        flash_read_page_to_buffer       (uint32 sector_num, flash_page_enum page_num);
uint8       flash_write_page_from_buffer    (uint32 sector_num, flash_page_enum page_num);
void        flash_buffer_clear              (void);

uint8       flash_init                      (void);
#endif
