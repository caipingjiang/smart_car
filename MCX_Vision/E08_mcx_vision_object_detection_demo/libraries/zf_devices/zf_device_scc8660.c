/*********************************************************************************************************************
* MCX Vision Opensourec Library ����MCX Vision ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2024 SEEKFREE ��ɿƼ�
* 
* ���ļ��� MCX Vision ��Դ���һ����
* 
* MCX Vision ��Դ�� ��������
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
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          zf_device_scc8660
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK 5.38a
* ����ƽ̨          MCX Vision
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_device_scc8660.h"

#if (FRAME_SIZE == SCC8660_QVGA)
__attribute__((section (".camera"))) volatile uint32_t g_camera_buffer[320*240/2]; __attribute__ ((aligned (32)))
#elif (FRAME_SIZE == SCC8660_QQVGA)
__attribute__((section (".camera"))) volatile uint32_t g_camera_buffer[120*160/2]; __attribute__ ((aligned (32)))
#endif

uint16_t *scc8660_image;    // ʵ��ʹ�õ�����ͷ����ͷָ��
uint32 scc8660_frame_size = FRAME_SIZE;

gpio_struct scc8660_iic_scl_gpio = {GPIO3, 3u};
gpio_struct scc8660_iic_sda_gpio = {GPIO3, 2u};
gpio_struct scc8660_rst_gpio = {GPIO1, 18u};

// ��Ҫ���õ�����ͷ������ �����������޸Ĳ���
static int16 scc8660_set_confing_buffer[SCC8660_CONFIG_FINISH][2]=
{
    {SCC8660_INIT,              0},                                             // ����ͷ��ʼ��ʼ��

    {SCC8660_AUTO_EXP,          SCC8660_AUTO_EXP_DEF},                          // �Զ��ع�
    {SCC8660_BRIGHT,            SCC8660_BRIGHT_DEF},                            // ��������
    {SCC8660_FPS,               SCC8660_FPS_DEF},                               // ͼ��֡��
    {SCC8660_SET_COL,           SCC8660_W},                                     // ͼ������
    {SCC8660_SET_ROW,           SCC8660_H},                                     // ͼ������
    {SCC8660_PCLK_DIV,          SCC8660_PCLK_DIV_DEF},                          // PCLK��Ƶϵ��
    {SCC8660_PCLK_MODE,         SCC8660_PCLK_MODE_DEF},                         // PCLKģʽ
    {SCC8660_COLOR_MODE,        SCC8660_COLOR_MODE_DEF},                        // ͼ��ɫ��ģʽ
    {SCC8660_DATA_FORMAT,       SCC8660_DATA_FORMAT_DEF},                       // ������ݸ�ʽ
    {SCC8660_MANUAL_WB,         SCC8660_MANUAL_WB_DEF}                          // �ֶ���ƽ��
};

// ������ͷ�ڲ���ȡ������������ �����������޸Ĳ���
static int16 scc8660_get_confing_buffer[SCC8660_CONFIG_FINISH - 1][2]=
{
    {SCC8660_AUTO_EXP,          0},
    {SCC8660_BRIGHT,            0},                                             // ��������          
    {SCC8660_FPS,               0},                                             // ͼ��֡��           
    {SCC8660_SET_COL,           0},                                             // ͼ������           
    {SCC8660_SET_ROW,           0},                                             // ͼ������          
    {SCC8660_PCLK_DIV,          0},                                             // PCLK��Ƶϵ��      
    {SCC8660_PCLK_MODE,         0},                                             // PCLKģʽ      
    {SCC8660_COLOR_MODE,        0},                                             // ͼ��ɫ��ģʽ
    {SCC8660_DATA_FORMAT,       0},                                             // ������ݸ�ʽ    
    {SCC8660_MANUAL_WB,         0},                                             // ��ƽ������
};

//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͼ������
// ����˵��     data            ��Ҫ���õ�����ֵ
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_set_bright(data);                                       
// ��ע��Ϣ     ���øú���ǰ���ȳ�ʼ������ͷ���ô���
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_brightness (uint16 data)
{
    uint8 return_state = 0;
    return_state = scc8660_set_brightness_sccb(data);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �������ð�ƽ��
// ����˵��     data            ��Ҫ���õİ�ƽ�� ��ѡ����Ϊ��[0,0x65-0xa0] 0���ر��ֶ���ƽ�⣬�����Զ���ƽ��    �������ֶ���ƽ�� �ֶ���ƽ��ʱ ������Χ0x65-0xa0
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_set_white_balance(data);                // ���øú���ǰ���ȳ�ʼ������ͷ���ô���
// ��ע��Ϣ     ͨ���ú������õĲ��������ᱻ51��Ƭ������
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_white_balance (uint16 data)
{
    uint8 return_state = 0;
    return_state = scc8660_set_manual_wb_sccb(data);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ������ͷ�ڲ��Ĵ�������д����
// ����˵��     addr            ����ͷ�ڲ��Ĵ�����ַ
// ����˵��     data            ��Ҫд�������
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_set_reg(addr, data);                    // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_set_reg (uint8 addr, uint16 data)
{
    uint8 return_state = 0;
    return_state = scc8660_set_reg_sccb(addr, data);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     SCC8660 ����ͷ��ʼ��
// ����˵��     void
// ���ز���     uint8           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     scc8660_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_init (void)
{
    uint8 return_state = 0;
     
    CLOCK_EnableClock(kCLOCK_InputMux0);
    /* Enables the clock for PORT0 controller: Enables clock */
    CLOCK_EnableClock(kCLOCK_Port3);
    PORT_SetPinMux(PORT3, 6U, kPORT_MuxAsGpio);

    PORT3->PCR[6] = ((PORT3->PCR[6] &
                     /* Mask bits to zero which are setting */
                     (~(PORT_PCR_IBE_MASK)))

                    /* Input Buffer Enable: Enables. */
                    | PORT_PCR_IBE(0x01u));
    gpio_init(scc8660_rst_gpio, GPO, 1, PULL_UP);
    soft_iic_info_struct scc8660_iic_struct;
    do
    {
        system_delay_ms(200);
        soft_iic_init(&scc8660_iic_struct, 0, SCC8660_COF_IIC_DELAY, &scc8660_iic_scl_gpio, &scc8660_iic_sda_gpio);

        if(scc8660_set_config_sccb(&scc8660_iic_struct, scc8660_set_confing_buffer))
        {
            zf_debug_printf("camera_init_error\r\n");
        }
        else
        {
            zf_debug_printf("camera_init_finish\r\n");
            break;
        }
    }while(0);

    memset((uint8*)g_camera_buffer, 0xff, sizeof(g_camera_buffer));
    zf_debug_printf("SCC8660_SIZE:%d\r\n", sizeof(g_camera_buffer));
    ezh_start();
    return return_state;
}
