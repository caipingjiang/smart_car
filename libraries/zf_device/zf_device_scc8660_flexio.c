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

#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_delay.h"
#include "zf_driver_exti.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_driver_soft_iic.h"
#include "zf_device_camera.h"
#include "zf_device_type.h"
#include "zf_driver_flexio_csi.h"
#include "zf_device_config.h"

#include "zf_device_scc8660_flexio.h"

vuint8 scc8660_flexio_finish_flag = 0;                                                  // һ��ͼ��ɼ���ɱ�־λ

AT_DTCM_SECTION_ALIGN(uint16 scc8660_flexio_image[SCC8660_FLEXIO_H][SCC8660_FLEXIO_W], 4);

static scc8660_flexio_type_enum scc8660_flexio_type;

// ��Ҫ���õ�����ͷ������ �����������޸Ĳ���
static int16 scc8660_flexio_set_confing_buffer[SCC8660_FLEXIO_CONFIG_FINISH][2]=
{
    {SCC8660_FLEXIO_INIT,              0},                                              // ����ͷ��ʼ��ʼ��

    {SCC8660_FLEXIO_AUTO_EXP,          SCC8660_FLEXIO_AUTO_EXP_DEF},                    // �Զ��ع�
    {SCC8660_FLEXIO_BRIGHT,            SCC8660_FLEXIO_BRIGHT_DEF},                      // ��������
    {SCC8660_FLEXIO_FPS,               SCC8660_FLEXIO_FPS_DEF},                         // ͼ��֡��
    {SCC8660_FLEXIO_SET_COL,           SCC8660_FLEXIO_W},                               // ͼ������
    {SCC8660_FLEXIO_SET_ROW,           SCC8660_FLEXIO_H},                               // ͼ������
    {SCC8660_FLEXIO_PCLK_DIV,          SCC8660_FLEXIO_PCLK_DIV_DEF},                    // PCLK��Ƶϵ��
    {SCC8660_FLEXIO_PCLK_MODE,         SCC8660_FLEXIO_PCLK_MODE_DEF},                   // PCLKģʽ
    {SCC8660_FLEXIO_COLOR_MODE,        SCC8660_FLEXIO_COLOR_MODE_DEF},                  // ͼ��ɫ��ģʽ
    {SCC8660_FLEXIO_DATA_FORMAT,       SCC8660_FLEXIO_DATA_FORMAT_DEF},                 // ������ݸ�ʽ
    {SCC8660_FLEXIO_MANUAL_WB,         SCC8660_FLEXIO_MANUAL_WB_DEF}                    // �ֶ���ƽ��
};

// ������ͷ�ڲ���ȡ������������ �����������޸Ĳ���
static int16 scc8660_flexio_get_confing_buffer[SCC8660_FLEXIO_CONFIG_FINISH - 1][2]=
{
    {SCC8660_FLEXIO_AUTO_EXP,          0},
    {SCC8660_FLEXIO_BRIGHT,            0},                                              // ��������          
    {SCC8660_FLEXIO_FPS,               0},                                              // ͼ��֡��           
    {SCC8660_FLEXIO_SET_COL,           0},                                              // ͼ������           
    {SCC8660_FLEXIO_SET_ROW,           0},                                              // ͼ������          
    {SCC8660_FLEXIO_PCLK_DIV,          0},                                              // PCLK��Ƶϵ��      
    {SCC8660_FLEXIO_PCLK_MODE,         0},                                              // PCLKģʽ      
    {SCC8660_FLEXIO_COLOR_MODE,        0},                                              // ͼ��ɫ��ģʽ
    {SCC8660_FLEXIO_DATA_FORMAT,       0},                                              // ������ݸ�ʽ    
    {SCC8660_FLEXIO_MANUAL_WB,         0},                                              // ��ƽ������
};

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͷ�ڲ�������Ϣ �ڲ�����
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(scc8660_flexio_set_config(scc8660_flexio_set_confing_buffer)){}
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_flexio_set_config (int16 buff[SCC8660_FLEXIO_CONFIG_FINISH][2])
{
    uint8 return_state = 1;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    // ���ò���  ������ο���������ֲ�
    // ��ʼ��������ͷ�����³�ʼ��
    for(loop_count = SCC8660_FLEXIO_MANUAL_WB; loop_count < SCC8660_FLEXIO_SET_REG_DATA; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = buff[loop_count][0];
        temp = buff[loop_count][1];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

        system_delay_ms(2);
    }

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            if((0xff == uart_buffer[1]) || (0xff == uart_buffer[2]))
            {
                return_state = 0;
                break;
            }
        }
        system_delay_ms(1);
    }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);

    // ���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
    // ����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�ڲ�������Ϣ �ڲ�����
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(scc8660_flexio_get_config(scc8660_flexio_get_confing_buffer)){}
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_flexio_get_config (int16 buff[SCC8660_FLEXIO_CONFIG_FINISH-1][2])
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    for(loop_count = SCC8660_FLEXIO_MANUAL_WB - 1; loop_count >= 1; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_FLEXIO_GET_STATUS;
        temp = buff[loop_count][0];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

        timeout_count = 0;    
        do
        {
            if(3 <= fifo_used(&camera_receiver_fifo))
            {
                uart_buffer_index = 3;
                fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
                buff[loop_count][1] = uart_buffer[1] << 8 | uart_buffer[2];
                break;
            }
            system_delay_ms(1);
        }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
        if(timeout_count > SCC8660_FLEXIO_INIT_TIMEOUT)                                // ��ʱ
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ ID
// ����˵��     void
// ���ز���     uint16          0-��ȡ���� N-�汾��
// ʹ��ʾ��     scc8660_flexio_flexio_get_id();                               // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_flexio_get_id (void)
{
    uint16 temp;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_FLEXIO_GET_WHO_AM_I;
    temp = 0;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;
    uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������������ͷ�ع�ʱ��
// ����˵��     light           �����ع�ʱ��Խ��ͼ��Խ��������ͷ�յ������ݷֱ��ʼ�FPS��������ع�ʱ��������õ����ݹ�����ô����ͷ��������������ֵ
// ���ز���     uint16          ����
// ʹ��ʾ��     scc8660_flexio_get_parameter();                                        // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_flexio_get_parameter (uint16 config)
{
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_FLEXIO_GET_WHO_AM_I;
    uart_buffer[2] = 0x00;
    uart_buffer[3] = config;
    uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ��ɫ����ͷ�̼��汾
// ����˵��     void
// ���ز���     uint16          �汾��
// ʹ��ʾ��     scc8660_flexio_get_version();                                          // ���øú���ǰ���ȳ�ʼ������ͷ���ô���
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 scc8660_flexio_get_version (void)
{
    uint16 temp;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = SCC8660_FLEXIO_GET_STATUS;
    temp           = SCC8660_FLEXIO_GET_VERSION;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;

    uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

    do
    {
        if(3 <= fifo_used(&camera_receiver_fifo))
        {
            uart_buffer_index = 3;
            fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
            return_value = uart_buffer[1] << 8 | uart_buffer[2];
            break;
        }
        system_delay_ms(1);
    }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͼ������
// ����˵��     data            ��Ҫ���õ�����ֵ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_flexio_set_bright(data);                                       // ͨ���ú������õĲ��������ᱻ51��Ƭ������
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������ͷ���ô���
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_flexio_set_brightness (uint16 data)
{
    uint8 return_state = 0;
    
    if(SCC8660_FLEXIO_UART == scc8660_flexio_type)
    {
        uint8  uart_buffer[4];
        uint16 temp;
        uint16 timeout_count = 0;
        uint32 uart_buffer_index = 0;

        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_FLEXIO_SET_BRIGHT;
        uart_buffer[2] = data >> 8;
        uart_buffer[3] = (uint8)data;

        uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

        do
        {
            if(3 <= fifo_used(&camera_receiver_fifo))
            {
                uart_buffer_index = 3;
                fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
                temp = uart_buffer[1] << 8 | uart_buffer[2];
                break;
            }
            system_delay_ms(1);
        }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
        if((temp != data) || (SCC8660_FLEXIO_INIT_TIMEOUT <= timeout_count))
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = scc8660_set_brightness_sccb(data);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �������ð�ƽ��
// ����˵��     data            ��Ҫ���õ�����ֵ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_flexio_set_white_balance(data);                // ���øú���ǰ���ȳ�ʼ������ͷ���ô���
// ��ע��Ϣ     ͨ���ú������õĲ��������ᱻ51��Ƭ������
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_flexio_set_white_balance (uint16 data)
{
    uint8 return_state = 0;
    
    if(SCC8660_FLEXIO_UART == scc8660_flexio_type)
    {
        uint8  uart_buffer[4];
        uint16 temp;
        uint16 timeout_count = 0;
        uint32 uart_buffer_index = 0;

        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_FLEXIO_SET_MANUAL_WB;
        uart_buffer[2] = data >> 8;
        uart_buffer[3] = (uint8)data;

        uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

        do
        {
            if(3 <= fifo_used(&camera_receiver_fifo))
            {
                uart_buffer_index = 3;
                fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
                temp = uart_buffer[1] << 8 | uart_buffer[2];
                break;
            }
            system_delay_ms(1);
        }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
        if((temp != data) || (SCC8660_FLEXIO_INIT_TIMEOUT <= timeout_count))
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = scc8660_set_manual_wb_sccb(data);
    }    
    
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ͷ�ڲ��Ĵ�������д����
// ����˵��     addr            ����ͷ�ڲ��Ĵ�����ַ
// ����˵��     data            ��Ҫд�������
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_flexio_set_reg(addr, data);                    // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_flexio_set_reg (uint8 addr, uint16 data)
{
    uint8 return_state = 0;
    
    if(SCC8660_FLEXIO_UART == scc8660_flexio_type)
    {
        uint8  uart_buffer[4];
        uint16 temp;
        uint16 timeout_count = 0;
        uint32 uart_buffer_index = 0;

        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_FLEXIO_SET_REG_ADDR;
        uart_buffer[2] = 0x00;
        uart_buffer[3] = (uint8)addr;
        uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

        system_delay_ms(10);
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = SCC8660_FLEXIO_SET_REG_DATA;
        temp           = data;
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(SCC8660_FLEXIO_COF_UART, uart_buffer, 4);

        do
        {
            if(3 <= fifo_used(&camera_receiver_fifo))
            {
                uart_buffer_index = 3;
                fifo_read_buffer(&camera_receiver_fifo, uart_buffer, &uart_buffer_index, FIFO_READ_AND_CLEAN);
                temp = uart_buffer[1] << 8 | uart_buffer[2];
                break;
            }
            system_delay_ms(1);
        }while(SCC8660_FLEXIO_INIT_TIMEOUT > timeout_count ++);
        if((temp != data) || (SCC8660_FLEXIO_INIT_TIMEOUT <= timeout_count))
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = scc8660_set_reg_sccb(addr, data);
    }

    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660 ����ͷ�����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �ú�����ISR�ļ� ����5�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_flexio_uart_callback(void)
{
    uint8 data = 0;
    uart_query_byte(SCC8660_FLEXIO_COF_UART, &data);
    
    if(0xA5 == data)
    {
        fifo_clear(&camera_receiver_fifo);
    }
    
    fifo_write_element(&camera_receiver_fifo, data);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660 ����ͷ�ɼ�����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �ú�����isr.c�е�CSI_IRQHandler��������
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_flexio_vsync_callback(void)
{
    if(exti_flag_get(SCC8660_FLEXIO_VSYNC_PIN))
    {
        exti_flag_clear(SCC8660_FLEXIO_VSYNC_PIN);
        flexio_csi_dma_restart((uint8 *)scc8660_flexio_image[0]);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      SCC8660 ����ͷDMA����ж�
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
static void scc8660_flexio_dma_callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
	scc8660_flexio_finish_flag = 1; 
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SCC8660 ����ͷ��ʼ��
// ����˵��     void
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_flexio_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_flexio_init (void)
{
    uint8 return_state = 0;
    soft_iic_info_struct scc8660_flexio_iic_struct;
    do
    {
        // ������ͷ��ʼ��֮ǰ�����߳��ź�
        gpio_init(SCC8660_FLEXIO_VSYNC_PIN, GPO, 1, GPO_PUSH_PULL);
        
        system_delay_ms(200);
        set_flexio_camera_type(CAMERA_COLOR, &scc8660_flexio_vsync_callback, NULL, NULL);                                           // ������������ͷ����
        // ���ȳ���SCCBͨѶ
        scc8660_flexio_type = SCC8660_FLEXIO_SCCB;
        soft_iic_init(&scc8660_flexio_iic_struct, 0, SCC8660_FLEXIO_COF_IIC_DELAY, SCC8660_FLEXIO_COF_IIC_SCL, SCC8660_FLEXIO_COF_IIC_SDA);
        if(scc8660_set_config_sccb(&scc8660_flexio_iic_struct, scc8660_flexio_set_confing_buffer))
        {
            // SCCBͨѶʧ�ܣ����Դ���ͨѶ
            scc8660_flexio_type = SCC8660_FLEXIO_UART;
            camera_fifo_init();
            set_flexio_camera_type(CAMERA_COLOR, &scc8660_flexio_vsync_callback, NULL, &scc8660_flexio_uart_callback);              // ������������ͷ����
            uart_init (SCC8660_FLEXIO_COF_UART, SCC8660_FLEXIO_COF_BAUR, SCC8660_FLEXIO_COF_UART_RX, SCC8660_FLEXIO_COF_UART_TX);	//��ʼ������ ��������ͷ    
            uart_rx_interrupt(SCC8660_FLEXIO_COF_UART, 1);
            fifo_clear(&camera_receiver_fifo);
            
            scc8660_flexio_get_version();                                                      // ��ȡ���õķ�ʽ
            
            if(scc8660_flexio_set_config(scc8660_flexio_set_confing_buffer))
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���
                zf_log(0, "SCC8660 set config error.");
                set_flexio_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }

            // ��ȡ���ñ��ڲ鿴�����Ƿ���ȷ
            if(scc8660_flexio_get_config(scc8660_flexio_get_confing_buffer))
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���
                zf_log(0, "SCC8660 get config error.");
                set_flexio_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
        }

        flexio_csi_init(SCC8660_FLEXIO_DATA_PIN, SCC8660_FLEXIO_PCLK_PIN, SCC8660_FLEXIO_HREF_PIN, SCC8660_FLEXIO_W * 2, SCC8660_FLEXIO_H, (uint8 *)scc8660_flexio_image[0], scc8660_flexio_dma_callback);
        flexio_csi_enable_rxdma();
        NVIC_SetPriority(DMA0_DMA16_IRQn, 1);                   // ����DMA�ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
        interrupt_enable(DMA0_DMA16_IRQn);
        
        //���ó��ж�
        exti_init(SCC8660_FLEXIO_VSYNC_PIN, EXTI_TRIGGER_FALLING);
        NVIC_SetPriority(SCC8660_FLEXIO_VSYNC_IRQN, 0);         // ���ó��ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
    }while(0);

    return return_state;
}
