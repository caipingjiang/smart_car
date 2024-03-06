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

#include "fsl_cache.h"
#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_romapi.h"
#include "zf_driver_flash.h"


flexspi_nor_config_t config;

uint32 flash_instance = 1;

flash_data_union flash_union_buffer[FLASH_DATA_BUFFER_SIZE];               // FLASH ���������ݻ�����



//-------------------------------------------------------------------------------------------------------------------
// �������     У�� FLASH �Ƿ�������
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 127>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <FLASH_PAGE_0-FLASH_PAGE_7>
// ���ز���     uint8           1-������ 0-û������ �����Ҫ�������ݵ�����д���µ�������Ӧ�ö������������в�������
// ʹ��ʾ��     flash_check(FLASH_SECTION_127, FLASH_PAGE_3);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_check (uint32 sector_num, flash_page_enum page_num)
{
    uint16 i;
    
    status_t state = kStatus_Success;
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);//��ȡflashǰ���������ջ���
    
    for(i=0; i<FLASH_PAGE_SIZE/4; i++)
    {
        if(0xFFFFFFFF != flash_read(sector_num, page_num, i, uint32))
        {
            state =  kStatus_Fail;//flash��Ҫ����
            break;
        }
    }
    
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������
// ����˵��     sector_num      ��Ҫ������������� ������Χ <0 - 127>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <FLASH_PAGE_0-FLASH_PAGE_7>
// ���ز���     uint8           1-��ʾʧ�� 0-��ʾ�ɹ�
// ʹ��ʾ��     flash_erase_page(FLASH_SECTION_127, FLASH_PAGE_3);
// ��ע��Ϣ     ����������Ȼ�ǲ���ҳ��ʵ�����ǲ�����һ��ɾ����������������ǽ���������ҳ��ʹ�õ�
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_erase_page (uint32 sector_num, flash_page_enum page_num)
{
    uint32 primask;
    status_t state = kStatus_Success;
    primask = interrupt_global_disable();
    state = rom_api_flexspi_nor_flash_erase(flash_instance, &config, sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
    interrupt_global_enable(primask);
    if(state != kStatus_Success)
    {
        state = kStatus_Fail;
    }
    
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡһҳ
// ����˵��     sector_num      ��Ҫ��ȡ��������� ������Χ <0 - 127>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <FLASH_PAGE_0-FLASH_PAGE_7>
// ����˵��     buf             ��Ҫ��ȡ�����ݵ�ַ   ������������ͱ���Ϊuint32
// ����˵��     len             ��Ҫд������ݳ���   ������Χ 1-1024
// ���ز���     void
// ʹ��ʾ��     flash_read_page(FLASH_SECTION_127, FLASH_PAGE_3, data_buffer, 256);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page (uint32 sector_num, flash_page_enum page_num, uint32 *buf, uint16 len)
{
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE, len * 4);//��ȡflashǰ���������ջ���
    
    rom_api_flexspi_nor_flash_read(flash_instance, &config, buf, sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, len * 4);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���һҳ
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 127>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <FLASH_PAGE_0-FLASH_PAGE_7>
// ����˵��     buf             ��Ҫд������ݵ�ַ   ������������ͱ���Ϊuint32
// ����˵��     len             ��Ҫд������ݳ���   ������Χ 1-1024
// ���ز���     uint8           1-��ʾʧ�� 0-��ʾ�ɹ�
// ʹ��ʾ��     flash_write_page(FLASH_SECTION_127, FLASH_PAGE_3, data_buffer, 256);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_write_page (uint32 sector_num, flash_page_enum page_num, const uint32 *buf, uint16 len)
{
    uint8 i;
    uint32 primask;
    status_t state = kStatus_Success;
    
    zf_assert(len <= FLASH_PAGE_SIZE);                                                      
    
    if(flash_check(sector_num, page_num))                                       // �ж��Ƿ������� ����������ı��� ��ֹ����û������д��
    {
        flash_erase_page(sector_num, page_num);                                 // ������һҳ
    }
    
    for(i=0; i<FLASH_PAGE_NUM_DRIVER; i++)
    {
        primask = interrupt_global_disable();
        state = rom_api_flexspi_nor_flash_page_program(flash_instance, &config, sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE + (i * (FLASH_PAGE_SIZE/FLASH_PAGE_NUM_DRIVER)),(uint32 *)&flash_union_buffer[i*64]);
        interrupt_global_enable(primask);
        if(state != kStatus_Success)
        {
            state = kStatus_Fail;
            break;
        }
    }
    
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ָ�� FLASH ��������ָ��ҳ���ȡ���ݵ�������
// ����˵��     sector_num      ��Ҫ��ȡ��������� ������Χ <0 - 127>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <FLASH_PAGE_0-FLASH_PAGE_7>
// ���ز���     void
// ʹ��ʾ��     flash_read_page_to_buffer(FLASH_SECTION_127, FLASH_PAGE_3);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void flash_read_page_to_buffer (uint32 sector_num, flash_page_enum page_num)
{
    DCACHE_CleanInvalidateByRange(FLASH_BASE_ADDR + sector_num * FLASH_SECTOR_SIZE, FLASH_PAGE_SIZE);//��ȡflashǰ���������ջ���
    
    rom_api_flexspi_nor_flash_read(flash_instance, &config, (uint32 *)&flash_union_buffer[0], sector_num * FLASH_SECTOR_SIZE + page_num * FLASH_PAGE_SIZE, FLASH_PAGE_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ָ�� FLASH ��������ָ��ҳ��д�뻺����������
// ����˵��     sector_num      ��Ҫд���������� ������Χ <0 - 127>
// ����˵��     page_num        ��ǰ����ҳ�ı��   ������Χ <FLASH_PAGE_0-FLASH_PAGE_7>
// ���ز���     uint8           1-��ʾʧ�� 0-��ʾ�ɹ�
// ʹ��ʾ��     flash_write_page_from_buffer(FLASH_SECTION_127, FLASH_PAGE_3);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_write_page_from_buffer (uint32 sector_num, flash_page_enum page_num)
{
    uint32 primask;
    status_t state = kStatus_Success;
    primask = interrupt_global_disable();
    flash_write_page(sector_num, page_num, (const uint32 *)&flash_union_buffer[0], FLASH_PAGE_SIZE);
    interrupt_global_enable(primask);
    return state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ݻ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     flash_buffer_clear();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void flash_buffer_clear (void)
{
    memset(flash_union_buffer, 0xFF, FLASH_PAGE_SIZE);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     flash��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     flash_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 flash_init (void)
{
    serial_nor_config_option_t option;
    
    option.option0.U = 0xC0000008; // QuadSPI NOR, Frequency: 133MHz
    
    rom_api_init();
    if(rom_api_flexspi_nor_get_config(flash_instance, &config, &option) !=  kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}
