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


#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "fsl_lpi2c.h"
#include "fsl_iomuxc.h"

#include "zf_driver_iic.h"

static  LPI2C_Type *iic_index[]      = LPI2C_BASE_PTRS;


#define LPI2C_CLOCK_SOURCE_DIVIDER (0x05)
#define LPI2C_CLOCK_FREQUENCY ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (LPI2C_CLOCK_SOURCE_DIVIDER + 1))
#define IIC_PIN_CONF  SPEED_100MHZ | KEEPER_EN | PULLUP_22K | DSE_R0_6 | OD_EN  //����IIC����Ĭ������

void iic_iomuxc(iic_index_enum iic_n, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin)
{
    switch(iic_n)
    {
        case IIC_1:
        {
            if      (IIC1_SDA_B17 == sda_pin) afio_init(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 1, IIC_PIN_CONF);                            
                                                             
            if      (IIC1_SCL_B16 == scl_pin) afio_init(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, 1, IIC_PIN_CONF);
            else if (IIC1_SCL_D4  == scl_pin) afio_init(IOMUXC_GPIO_SD_B1_04_LPI2C1_SCL, 1, IIC_PIN_CONF);                             
        }break;                                              
                                                             
        case IIC_2:                                          
        {                                                    
            if      (IIC2_SDA_C5  == sda_pin) afio_init(IOMUXC_GPIO_B0_05_LPI2C2_SDA,    1, IIC_PIN_CONF);
                                                                
            if      (IIC2_SCL_C4  == scl_pin) afio_init(IOMUXC_GPIO_B0_04_LPI2C2_SCL,    1, IIC_PIN_CONF);                          
        }break;                                              
                                                             
        case IIC_3:                                          
        {                                                    
            if      (IIC3_SDA_B22 == sda_pin) afio_init(IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA, 1, IIC_PIN_CONF);
            else if (IIC3_SDA_D13 == sda_pin) afio_init(IOMUXC_GPIO_SD_B0_01_LPI2C3_SDA, 1, IIC_PIN_CONF);
                                                       
            if      (IIC3_SCL_B23 == scl_pin) afio_init(IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL, 1, IIC_PIN_CONF);
            else if (IIC3_SCL_D12 == scl_pin) afio_init(IOMUXC_GPIO_SD_B0_00_LPI2C3_SCL, 1, IIC_PIN_CONF);
        }break;                                              
                                                             
        case IIC_4:                                          
        {                                                    
            if      (IIC4_SDA_B13 == sda_pin) afio_init(IOMUXC_GPIO_AD_B0_13_LPI2C4_SDA, 1, IIC_PIN_CONF);                               
                                                                
            if      (IIC4_SCL_B12 == scl_pin) afio_init(IOMUXC_GPIO_AD_B0_12_LPI2C4_SCL, 1, IIC_PIN_CONF);
        }break;
        
        default:zf_assert(0);break;
    }
}
//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ�д 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     iic_write_8bit(IIC_1, 0x7A, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit (iic_index_enum iic_n, uint8 target_addr, const uint8 data)
{
    status_t state = kStatus_Fail;

    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&data, 1);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ�д 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_write_8bit_array(IIC_1, 0x7A, data, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_array (iic_index_enum iic_n, uint8 target_addr, const uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;

    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterSend(iic_index[iic_n], (void *)data, len);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ�д 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     iic_write_16bit(IIC_1, 0x7A, 0x0101);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit (iic_index_enum iic_n, uint8 target_addr, const uint16 data)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        temp_data[0] = data>>8;
        temp_data[1] = data;
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ�д 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_write_16bit_array(IIC_1, 0x7A, data, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_array (iic_index_enum iic_n, uint8 target_addr, const uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        while(len--)
        {
            temp_data[0] = *data >> 8;
            temp_data[1] = *data;
            state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
            data++;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ��򴫸����Ĵ���д 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     iic_write_8bit_register(IIC_1, 0x7A, 0x01, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 data)
{
    status_t state = kStatus_Fail;
    
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&data, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ��򴫸����Ĵ���д 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_write_8bit_registers(IIC_1, 0x7A, 0x01, data, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_8bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, const uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&data, len);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ��򴫸����Ĵ���д 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     iic_write_16bit_register(IIC_1, 0x7A, 0x0101, 0x0101);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_register (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 data)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        temp_data[0] = data>>8;
        temp_data[1] = data;
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ��򴫸����Ĵ���д 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_write_16bit_registers(IIC_1, 0x7A, 0x0101, data, 6);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_write_16bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, const uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        while(len--)
        {
            temp_data[0] = *data>>8;
            temp_data[1] = *data;
            state = LPI2C_MasterSend(iic_index[iic_n], (void *)temp_data, 2);
            data++;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڶ�ȡ 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ���ز���     uint8           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     iic_read_8bit(IIC_1, 0x7A);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_8bit (iic_index_enum iic_n, uint8 target_addr)
{
    status_t state = kStatus_Fail;
    uint8 return_data = 0;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)&return_data, 1);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڶ�ȡ 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_read_8bit_array(IIC_1, 0x7A, data, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_8bit_array (iic_index_enum iic_n, uint8 target_addr, uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)data, len);
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڶ�ȡ 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ���ز���     uint16          ���ض�ȡ�� 16bit ����
// ʹ��ʾ��     iic_read_16bit(IIC_1, 0x7A);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 iic_read_16bit (iic_index_enum iic_n, uint8 target_addr)
{
    status_t state = kStatus_Fail;
    uint16 return_data = 0;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
        return_data = ((uint16)temp_data[0]<<8) | temp_data[1];
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڶ�ȡ 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_read_16bit_array(IIC_1, 0x7A, data, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_16bit_array (iic_index_enum iic_n, uint8 target_addr, uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);

        while(len --)
        {
            state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
            *data = ((uint16)temp_data[0]<<8) | temp_data[1];
            data++;
        }
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint8           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     iic_read_8bit_register(IIC_1, 0x7A, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_8bit_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name)
{
    status_t state = kStatus_Fail;
    uint8 return_data = 0;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)&return_data, 1);

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڴӴ������Ĵ�����ȡ 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_read_8bit_registers(IIC_1, 0x7A, 0x01, data, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_8bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)data, len);

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڴӴ������Ĵ�����ȡ 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint16          ���ض�ȡ�� 16bit ����
// ʹ��ʾ��     iic_read_16bit_register(IIC_1, 0x7A, 0x0101);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 iic_read_16bit_register (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name)
{
    status_t state = kStatus_Fail;
    uint16 return_data = 0;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        
        temp_data[0] = (register_name)>>8;
        temp_data[1] = (register_name);
        state = LPI2C_MasterSend(iic_index[iic_n], temp_data, 2);
        
        
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        

        state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
        return_data = ((uint16)temp_data[0]<<8) | temp_data[1];


        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
    return return_data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڴӴ������Ĵ�����ȡ 16bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     *data           ���ݴ�Ż�����
// ����˵��     len             ����������
// ���ز���     void            
// ʹ��ʾ��     iic_read_16bit_registers(IIC_1, 0x7A, 0x0101, data, 8);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_read_16bit_registers (iic_index_enum iic_n, uint8 target_addr, const uint16 register_name, uint16 *data, uint32 len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        
        temp_data[0] = (register_name)>>8;
        temp_data[1] = (register_name);
        state = LPI2C_MasterSend(iic_index[iic_n], temp_data, 2);
        
        
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        
        while(len --)
        {
            state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
            *data = ((uint16)temp_data[0]<<8) | temp_data[1];
            data++;
        }

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڴ��� 8bit ���� ��д���ȡ
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ��������ַ
// ����˵��     *write_data     �������ݴ�Ż�����
// ����˵��     write_len       ���ͻ���������
// ����˵��     *read_data      ��ȡ���ݴ�Ż�����
// ����˵��     read_len        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_8bit_array(IIC_1, addr, data, 64, data, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer_8bit_array (iic_index_enum iic_n, uint8 target_addr, const uint8 *write_data, uint32 write_len, uint8 *read_data, uint32 read_len)
{
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)write_data, write_len);
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        state = LPI2C_MasterReceive(iic_index[iic_n], (void *)read_data, read_len);

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڴ��� 16bit ���� ��д���ȡ
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ��������ַ
// ����˵��     *write_data     �������ݴ�Ż�����
// ����˵��     write_len       ���ͻ���������
// ����˵��     *read_data      ��ȡ���ݴ�Ż�����
// ����˵��     read_len        ��ȡ����������
// ���ز���     void            
// ʹ��ʾ��     iic_transfer_16bit_array(IIC_1, addr, data, 64, data, 64);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_transfer_16bit_array (iic_index_enum iic_n, uint8 target_addr, const uint16 *write_data, uint32 write_len, uint16 *read_data, uint32 read_len)
{
    status_t state = kStatus_Fail;
    uint8 temp_data[2];
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        while(write_len --)
        {
            temp_data[0] = (*write_data)>>8;
            temp_data[1] = (*write_data);
            state = LPI2C_MasterSend(iic_index[iic_n], temp_data, 2);
            write_data++;
        }
        
        state = LPI2C_MasterRepeatedStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        
        while(read_len --)
        {
            state = LPI2C_MasterReceive(iic_index[iic_n], temp_data, 2);
            *read_data = ((uint16)temp_data[0]<<8) | temp_data[1];
            read_data++;
        }

        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ� SCCB ģʽ�򴫸����Ĵ���д 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ����˵��     data            Ҫд�������
// ���ز���     void            
// ʹ��ʾ��     iic_sccb_write_register(IIC_1, 0x7A, 0x01, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_sccb_write_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name, uint8 data)
{
    status_t state = kStatus_Fail;
    
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterSend(iic_index[iic_n], &data, 1);
        if (state != kStatus_Success)
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿ� SCCB ģʽ�Ӵ������Ĵ�����ȡ 8bit ����
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     target_addr     Ŀ���ַ
// ����˵��     register_name   �������ļĴ�����ַ
// ���ز���     uint8           ���ض�ȡ�� 8bit ����
// ʹ��ʾ��     iic_sccb_read_register(IIC_1, 0x7A, 0x01);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_sccb_read_register (iic_index_enum iic_n, uint8 target_addr, const uint8 register_name)
{
    uint8 data = 0;
    
    status_t state = kStatus_Fail;
    do
    {
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Write);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterSend(iic_index[iic_n], (void *)&register_name, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStart(iic_index[iic_n], target_addr, kLPI2C_Read);
        if (state != kStatus_Success)   
        {
            break;
        }
        while (LPI2C_MasterGetStatusFlags(iic_index[iic_n]) & kLPI2C_MasterNackDetectFlag);
        
        state = LPI2C_MasterReceive(iic_index[iic_n], &data, 1);
        if (state != kStatus_Success)   
        {
            break;
        }
        
        state = LPI2C_MasterStop(iic_index[iic_n]);
        if (state != kStatus_Success)   
        {
            break;
        }
    }while(0);
    
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IIC �ӿڳ�ʼ�� Ĭ�� MASTER ģʽ ���ṩ SLAVE ģʽ
// ����˵��     iic_n           IIC ģ��� ���� zf_driver_iic.h �� iic_index_enum ö���嶨��
// ����˵��     addr            IIC ��ַ ������Ҫע�� ��׼��λ��ַ ���λ���� д��ʱ�����ȷ������
// ����˵��     baud            IIC ������ ������ 1000Khz ������ 1KHz 
// ����˵��     scl_pin         IIC ʱ������ ���� zf_driver_iic.h �� iic_scl_pin_enum ö���嶨��
// ����˵��     sda_pin         IIC �������� ���� zf_driver_iic.h �� iic_sda_pin_enum ö���嶨��
// ���ز���     void            
// ʹ��ʾ��     iic_init(IIC_1, 0x7A, 100000, IIC1_SCL_D10, IIC1_SDA_D11);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void iic_init(iic_index_enum iic_n, uint8 addr, uint32 baud, iic_scl_pin_enum scl_pin, iic_sda_pin_enum sda_pin)
{
    zf_assert((baud >= 1000)&&(baud <= 1000000));                             // ���� 1KHz ���� 400KHz ����
    zf_assert((scl_pin / 16) == (sda_pin / 16));                                // scl_pin �� sda_pin ������ iic_n ƥ��

    lpi2c_master_config_t masterConfig;
    
    iic_iomuxc(iic_n, scl_pin, sda_pin);

    CLOCK_SetMux(kCLOCK_Lpi2cMux, 0);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, LPI2C_CLOCK_SOURCE_DIVIDER);
    
    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = baud;
    LPI2C_MasterInit(iic_index[iic_n], &masterConfig, LPI2C_CLOCK_FREQUENCY);   // ��һ�γ�ʼ�����ڴ�ʱ��
    LPI2C_MasterReset(iic_index[iic_n]);                                        // ��λ����
    LPI2C_MasterInit(iic_index[iic_n], &masterConfig, LPI2C_CLOCK_FREQUENCY);   // ���³�ʼ��������ȷ�Ĳ���
}
