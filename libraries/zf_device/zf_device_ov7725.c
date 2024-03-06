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
* �ļ�����          zf_device_ov7725
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
*                   TXD/SCL             �鿴 zf_device_ov7725.h �� OV7725_COF_UART_TX �� OV7725_COF_IIC_SCL �궨��
*                   RXD/SDA             �鿴 zf_device_ov7725.h �� OV7725_COF_UART_RX �� OV7725_COF_IIC_SDA �궨��
*                   PCLK                �鿴 zf_device_ov7725.h �� OV7725_PCLK_PIN �궨��
*                   VSY                 �鿴 zf_device_ov7725.h �� OV7725_VSYNC_PIN �궨��
*                   D0-D7               �鿴 zf_device_ov7725.h �� OV7725_DATA_PIN �궨�� �Ӹö��忪ʼ�������˸�����
*                   VCC                 3.3V��Դ
*                   GND                 ��Դ��
*                   ������������
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "fsl_cache.h"
#include "zf_driver_delay.h"
#include "zf_driver_csi.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_iic.h"
#include "zf_driver_uart.h"
#include "zf_device_camera.h"
#include "zf_device_type.h"

#include "zf_device_ov7725.h"

vuint8 ov7725_finish_flag = 0;

// ͼ�񻺳���  ����û���Ҫ����ͼ������ ���ͨ��mt9v03x_csi_image���������ݣ���ò�Ҫֱ�ӷ��ʻ�����
AT_DTCM_SECTION_ALIGN(uint8 ov7725_image_binary1[OV7725_H][OV7725_W / 8], 64);
AT_DTCM_SECTION_ALIGN(uint8 ov7725_image_binary2[OV7725_H][OV7725_W / 8], 64);

// �û�����ͼ������ֱ�ӷ������ָ������Ϳ���
// ���ʷ�ʽ�ǳ��򵥣�����ֱ��ʹ���±�ķ�ʽ����
// ������ʵ�10�� 50�еĵ㣬mt9v03x_csi_image[10][50]�Ϳ�����
uint8 (*ov7725_image_binary)[OV7725_W / 8];

// ��Ҫ���õ�����ͷ������ �����������޸Ĳ���
static uint16 ov7725_set_confing_buffer [OV7725_CONFIG_FINISH][2]=
{
    {OV7725_INIT,           0},                                                 // ��ʼ������

    {OV7725_RESERVE,        0},                                                 // ����
    {OV7725_CONTRAST,       OV7725_CONTRAST_DEF},                               // ��ֵ����
    {OV7725_FPS,            OV7725_FPS_DEF},                                    // ֡��
    {OV7725_COL,            OV7725_W},                                          // ͼ����
    {OV7725_ROW,            OV7725_H}                                           // ͼ��߶�
};

// ������ͷ�ڲ���ȡ������������ �����������޸Ĳ���
static uint16 ov7725_get_confing_buffer [OV7725_CONFIG_FINISH - 1][2]=
{
    {OV7725_RESERVE,        0},                                                 // ����
    {OV7725_CONTRAST,       0},                                                 // ��ֵ����
    {OV7725_FPS,            0},                                                 // ֡��
    {OV7725_COL,            0},                                                 // ͼ����
    {OV7725_ROW,            0}                                                  // ͼ��߶�
};

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͷ�ڲ�������Ϣ
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(ov7725_set_config(ov7725_set_confing_buffer)){}
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 ov7725_set_config (uint16 buff[OV7725_CONFIG_FINISH][2])
{
    uint8 return_state = 1;
    uint8  uart_buffer[4];
    uint16 temp = 0;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    for(loop_count = OV7725_ROW; OV7725_SET_DATA > loop_count; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = buff[loop_count][0];
        temp           = buff[loop_count][1];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;

        uart_write_buffer(OV7725_COF_UART, uart_buffer, 4);
        system_delay_ms(10);
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
    }while(OV7725_INIT_TIMEOUT > timeout_count ++);

    // ���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
    // ����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�ڲ�������Ϣ
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(ov7725_get_config(ov7725_get_confing_buffer)){}
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8 ov7725_get_config (uint16 buff[OV7725_CONFIG_FINISH - 1][2])
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp = 0;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    for(loop_count = OV7725_ROW - 1; 1 <= loop_count; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = OV7725_GET_STATUS;
        temp           = buff[loop_count][0];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;

        uart_write_buffer(OV7725_COF_UART, uart_buffer, 4);

        system_delay_ms(10);

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
        }while(OV7725_INIT_TIMEOUT > timeout_count ++);
        if(OV7725_INIT_TIMEOUT < timeout_count)                                 // ��ʱ
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     С�������ͷ�ڲ��Ĵ�����ʼ��
// ����˵��     void
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     if(ov7725_iic_init()){}
// ��ע��Ϣ     �ڲ�ʹ�� �û��������
//-------------------------------------------------------------------------------------------------------------------
static uint8 ov7725_iic_init (void)
{
    soft_iic_info_struct ov7725_iic_struct;
    uint8 ov7725_idcode = 0;
    uint8 return_state = 0;

    uart_rx_interrupt(OV7725_COF_UART, 0);

    soft_iic_init(&ov7725_iic_struct, OV7725_DEV_ADD, OV7725_COF_IIC_DELAY, OV7725_COF_IIC_SCL, OV7725_COF_IIC_SDA);

    soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM7, 0x80);        // ��λ����ͷ
    system_delay_ms(50);

    do
    {
        ov7725_idcode = soft_iic_sccb_read_register(&ov7725_iic_struct, OV7725_VER);
        if(OV7725_ID != ov7725_idcode)
        {
            return_state = 1;                                                   // У������ͷID��
            break;
        }

        // ID��ȷ������   Ȼ�����üĴ���
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM4         , 0xC1);  
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_CLKRC        , 0x01);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM2         , 0x03);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM3         , 0xD0);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM7         , 0x40);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM8         , 0xCE);   // 0xCE:�ر��Զ��ع�  0xCF�������Զ��ع�
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HSTART       , 0x3F);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HSIZE        , 0x50);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_VSTRT        , 0x03);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_VSIZE        , 0x78);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HREF         , 0x00);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_SCAL0        , 0x0A);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_AWB_Ctrl0    , 0xE0);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_DSPAuto      , 0xff);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_DSP_Ctrl2    , 0x0C);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_DSP_Ctrl3    , 0x00);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_DSP_Ctrl4    , 0x00);

        if(OV7725_W == 80)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HOutSize, 0x14);
        }
        else if(OV7725_W == 160)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HOutSize, 0x28);
        }
        else if(OV7725_W == 240)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HOutSize, 0x3c);
        }
        else if(OV7725_W == 320)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_HOutSize, 0x50);
        }

        if(OV7725_H == 60)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_VOutSize, 0x1E);
        }
        else if(OV7725_H == 120)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_VOutSize, 0x3c);
        }
        else if(OV7725_H == 180)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_VOutSize, 0x5a);
        }
        else if(OV7725_H == 240)
        {
            soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_VOutSize, 0x78);
        }

        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_REG28        , 0x01);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_EXHCH        , 0x10);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_EXHCL        , 0x1F);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM1         , 0x0c);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM2         , 0x16);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM3         , 0x2a);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM4         , 0x4e);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM5         , 0x61);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM6         , 0x6f);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM7         , 0x7b);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM8         , 0x86);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM9         , 0x8e);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM10        , 0x97);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM11        , 0xa4);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM12        , 0xaf);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM13        , 0xc5);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM14        , 0xd7);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_GAM15        , 0xe8);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_SLOP         , 0x20);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_LC_RADI      , 0x00);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_LC_COEF      , 0x13);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_LC_XC        , 0x08);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_LC_COEFB     , 0x14);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_LC_COEFR     , 0x17);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_LC_CTR       , 0x05);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_BDBase       , 0x99);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_BDMStep      , 0x03);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_SDE          , 0x04);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_BRIGHT       , 0x00);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_CNST         , 0x40);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_SIGN         , 0x06);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_UVADJ0       , 0x11);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_UVADJ1       , 0x02);
    }while(0);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�̼� ID
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ov7725_uart_get_id();                           // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 ov7725_uart_get_id (void)
{
    uint16 temp = 0;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = OV7725_GET_WHO_AM_I;
    temp           = 0;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;

    uart_write_buffer(OV7725_COF_UART, uart_buffer, 4);

    temp = 0;

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
    }while(OV7725_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�̼��汾
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     ov7725_get_version();                           // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint16 ov7725_get_version (void)
{
    uint16 temp = 0;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = OV7725_GET_STATUS;
    temp           = OV7725_GET_VERSION;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;

    uart_write_buffer(OV7725_COF_UART, uart_buffer, 4);

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
    }while(OV7725_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X����ͷ�����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �ú�����ISR�ļ� ����5�жϳ��򱻵���
//-------------------------------------------------------------------------------------------------------------------
void ov7725_uart_callback(void)
{
    uint8 data = 0;
    uart_query_byte(OV7725_COF_UART, &data);
    
    if(0xA5 == data)
    {
        fifo_clear(&camera_receiver_fifo);
    }
    
    fifo_write_element(&camera_receiver_fifo, data);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X����ͷ�ɼ�����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �ú�����isr.c�е�CSI_IRQHandler��������
//-------------------------------------------------------------------------------------------------------------------
void ov7725_finished_callback(CSI_Type *base, csi_handle_t *handle, status_t status, void *userData)
{
    uint32 full_buffer_addr;
    if(csi_get_full_buffer(&csi_handle, &full_buffer_addr))
    {
        if(full_buffer_addr == (uint32)ov7725_image_binary1[0])
        {
            ov7725_image_binary = ov7725_image_binary1; // image_csi1�ɼ����
        csi_add_empty_buffer(&csi_handle, ov7725_image_binary2[0]);
        }
        else if(full_buffer_addr == (uint32)ov7725_image_binary2[0])
        {
            ov7725_image_binary = ov7725_image_binary2; // image_csi2�ɼ����
        csi_add_empty_buffer(&csi_handle, ov7725_image_binary1[0]);
        }
        ov7725_finish_flag = 1;                         // �ɼ���ɱ�־λ��һ
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     OV7725 ����ͷ��ʼ��
// ����˵��     NULL
// ���ز���     void
// ʹ��ʾ��     ov7725_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 ov7725_init (void)
{
    uint8 return_state = 0;

    do
    {
        set_camera_type(CAMERA_BIN_UART, NULL, NULL, &ov7725_uart_callback);       // ������������ͷ����
        camera_fifo_init();

        uart_init(OV7725_COF_UART, OV7725_COF_BAUR, OV7725_COF_UART_RX, OV7725_COF_UART_TX);
        uart_rx_interrupt(OV7725_COF_UART, 1);
        system_delay_ms(200);
        
        fifo_clear(&camera_receiver_fifo);

        // ��ȡ���в���
        if(ov7725_get_config(ov7725_get_confing_buffer))
        {
            system_delay_ms(200);
            set_camera_type(CAMERA_BIN_IIC, NULL, NULL, NULL);
            if(ov7725_iic_init())
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���� IIC ������ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���
                zf_log(0, "OV7725 IIC error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
        }
        else
        {
            // �������в���
            if(ov7725_set_config(ov7725_set_confing_buffer))
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���
                zf_log(0, "OV7725 set confing error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
            // ��ȡ���в���
            if(ov7725_get_config(ov7725_get_confing_buffer))
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���
                zf_log(0, "OV7725 get confing error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
        }

        csi_init(OV7725_W / 8, OV7725_H, &csi_handle, ov7725_finished_callback, OV7725_VSYNC_PIN, OV7725_PCLK_PIN, CSI_PIXCLK_FALLING);
        csi_add_empty_buffer(&csi_handle, ov7725_image_binary1[0]);
        csi_add_empty_buffer(&csi_handle, ov7725_image_binary2[0]);

        
        
        csi_start(&csi_handle);
        ov7725_image_binary = ov7725_image_binary1;// ���ó�ֵ
        
        interrupt_enable(CSI_IRQn);
    }while(0);

    return return_state;
}
