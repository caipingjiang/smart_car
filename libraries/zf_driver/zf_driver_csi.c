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
* �ļ�����          zf_driver_csi
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

#include "fsl_iomuxc.h"
#include "zf_driver_gpio.h"

#include "zf_driver_csi.h"

#define CSI_PIN_CONF    SPEED_100MHZ | KEEPER_EN | DSE_R0_6 //����CSI����Ĭ������   

csi_handle_t            csi_handle;                         //csi����ṹ��


void csi_iomuxc(vsync_pin_enum vsync, pixclk_pin_enum pixclk)
{
    //���ݶ˿����Ÿ�������
    afio_init(IOMUXC_GPIO_AD_B1_08_CSI_DATA09, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_09_CSI_DATA08, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_10_CSI_DATA07, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_11_CSI_DATA06, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_12_CSI_DATA05, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_13_CSI_DATA04, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_14_CSI_DATA03, 0, CSI_PIN_CONF);
    afio_init(IOMUXC_GPIO_AD_B1_15_CSI_DATA02, 0, CSI_PIN_CONF);
    
    if      (CSI_VSYNC_B14 == vsync)    afio_init(IOMUXC_GPIO_AD_B0_14_CSI_VSYNC,   0, CSI_PIN_CONF);
    else if (CSI_VSYNC_B22 == vsync)    afio_init(IOMUXC_GPIO_AD_B1_06_CSI_VSYNC,   0, CSI_PIN_CONF);
    else if (CSI_VSYNC_C29 == vsync)    afio_init(IOMUXC_GPIO_B1_13_CSI_VSYNC,      0, CSI_PIN_CONF);
                                                       
    if      (CSI_PIXCLK_B20 == pixclk)  afio_init(IOMUXC_GPIO_AD_B1_04_CSI_PIXCLK,  0, CSI_PIN_CONF);
    else if (CSI_PIXCLK_C28 == pixclk)  afio_init(IOMUXC_GPIO_B1_12_CSI_PIXCLK,     0, CSI_PIN_CONF);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI��ӿջ�������ַ
//  @param      handle      CSI��handle�ṹ�� ��MT9V032_CSI�Ѿ��������
//  @param      *buff       ���������׵�ַ
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_add_empty_buffer(csi_handle_t *handle, uint8 *buff)
{
    CSI_TransferSubmitEmptyBuffer(CSI,handle,(uint32_t)buff);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI��ȡ�ɼ���ɵĻ�������ַ
//  @param      handle      CSI��handle�ṹ�� ��MT9V032_CSI�Ѿ��������
//  @param      buffaddr    ��ȡ���ĵ�ַ
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
uint8 csi_get_full_buffer(csi_handle_t *handle, uint32 *buffaddr)
{
    if(kStatus_Success == CSI_TransferGetFullBuffer(CSI,handle,(uint32_t *)buffaddr))
    {
        return 1;//��ȡ���ɼ���ɵ�BUFFER
    }
    return 0;    //δ�ɼ����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI����
//  @param      handle      CSI��handle�ṹ�� ��MT9V032_CSI�Ѿ��������
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_start(csi_handle_t *handle)
{
    CSI_TransferStart(CSI,handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSIֹͣ
//  @param      handle      CSI��handle�ṹ�� ��MT9V032_CSI�Ѿ��������
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_stop(csi_handle_t *handle)
{
    CSI_TransferStop(CSI,handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      CSI��ʼ��
//  @param      width       ͼ�����
//  @param      height      ͼ�����
//  @param      handle      CSI��handle�ṹ�� ��MT9V032_CSI�Ѿ��������
//  @param      callback    �жϵ�ʱ��Ļص�����
//  @return     void			
//  @since      v1.0
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void csi_init(uint16 width, uint16 height, csi_handle_t *handle, csi_transfer_callback_t callback, vsync_pin_enum vsync, pixclk_pin_enum pixclk, pixclk_polarity_enum pixclk_polarity)
{
    uint16 i;
    uint32 pixel_num;
    uint16 temp_width;
    uint16 temp_height=0;
    csi_config_t csi_config;

    csi_iomuxc(vsync,pixclk);
    
    //CSI �ɼ���ʼ��
    CLOCK_SetMux(kCLOCK_CsiMux, 2);
    CLOCK_SetDiv(kCLOCK_CsiDiv, 0);
        
    //����ͷ�ɼ���ʼ��
    pixel_num = width*height;
    if(pixel_num%8) assert(0);//���ص㲻��8�ı��� �޷��ɼ�
    if(width%8)
    {
        temp_width = width - width%8;//������ʱ���
        i=1;
        while(pixel_num>(temp_width+(i*8)))
        {
            if(!(pixel_num%((temp_width+(i*8))))) 
            {
                temp_width += (i*8);//������ʱ���
                temp_height = pixel_num/temp_width;
                break;
            }
            i++;
        }
        if(!temp_height)
        {
            //���û���ҵ������ʱ���������
            i=1;
            while((temp_width-(i*8)))
            {
                if(!(pixel_num%((temp_width-(i*8))))) 
                {
                    temp_width -= (i*8);//������ʱ���
                    temp_height = pixel_num/temp_width;
                    break;
                }
                i++;
            }
        }
        if(!temp_height)
        {
            //�������û���ҵ�
            temp_width = pixel_num;
            temp_height = 1;
        }
    }
    else
    {
        temp_width = width;
        temp_height = height;
    }
    
    CSI_GetDefaultConfig(&csi_config);
    csi_config.width = temp_width;
    csi_config.height = temp_height;
    csi_config.polarityFlags = pixclk_polarity;
    csi_config.bytesPerPixel = 1U;
    csi_config.linePitch_Bytes = temp_width;
    csi_config.workMode = kCSI_NonGatedClockMode;
    csi_config.dataBus = kCSI_DataBus8Bit;
    csi_config.useExtVsync = true;
    CSI_Init(CSI, &csi_config);
    CSI_TransferCreateHandle(CSI,handle, callback, NULL);
}