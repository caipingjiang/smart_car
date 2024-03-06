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


#include "fsl_flexio_camera.h"
#include "fsl_flexio.h"
#include "fsl_iomuxc.h"
#include "fsl_dmamux.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"

#include "zf_driver_flexio_csi.h"

#define FLEXIO_PIN_CONF         SPEED_100MHZ | KEEPER_EN | DSE_R0_6             // ����FLEXIO����Ĭ������


#define DMA_CHN                 0u
#define DMA_MUX_SRC             kDmaRequestMuxFlexIO2Request2Request3

static uint8 flexio_shift_count;
static FLEXIO_CAMERA_Type s_FlexioCameraDevice;
static flexio_camera_config_t s_FlexioCameraConfig;

edma_transfer_config_t transferConfig;
edma_config_t edma_config;
edma_handle_t g_EDMA_Handle;

void flexio_iomuxc(flexio_pin_enum dat_pin_start, flexio_pin_enum pclk_pin, flexio_pin_enum href_pin)
{
    uint8 i;
    uint32 temp_config[5] = {IOMUXC_GPIO_B0_00_FLEXIO2_FLEXIO00};
    zf_assert(FLEXIO2_D24_C24 >= dat_pin_start);                                // �������Ų�������  ��ʼ���Ų��ô���24
    zf_assert((pclk_pin < dat_pin_start) || (pclk_pin > (dat_pin_start + 7)));  // ����ʱ�����Ų�Ӧ�����������ŷ�Χ��
    zf_assert((href_pin < dat_pin_start) || (href_pin > (dat_pin_start + 7)));  // ���ź����Ų�Ӧ�����������ŷ�Χ��
    zf_assert(href_pin != pclk_pin);                                            // ���ź����Ų�Ӧ��������ʱ������һ��
    
    afio_init(temp_config[0] + pclk_pin * 4, temp_config[1], temp_config[2], temp_config[3], temp_config[4] + pclk_pin * 4, 0, FLEXIO_PIN_CONF);
    afio_init(temp_config[0] + href_pin * 4, temp_config[1], temp_config[2], temp_config[3], temp_config[4] + href_pin * 4, 0, FLEXIO_PIN_CONF);
    
    for(i=0; i<8; i++)
    {
        afio_init(temp_config[0] + (dat_pin_start + i) * 4, temp_config[1], temp_config[2], temp_config[3], temp_config[4] + (dat_pin_start + i) * 4, 0, FLEXIO_PIN_CONF);
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO ʹ��
//  @param      enable          1��ʹ��FLEXIO   0���ر�FLEXIO
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_enable(uint8 enable)
{
    if(enable)
    {
        s_FlexioCameraDevice.flexioBase->CTRL |= FLEXIO_CTRL_FLEXEN_MASK;
    }
    else
    {
        s_FlexioCameraDevice.flexioBase->CTRL &= ~FLEXIO_CTRL_FLEXEN_MASK;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO ��־λ���
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_flag_clear(void)
{
    FLEXIO_CAMERA_ClearStatusFlags(&s_FlexioCameraDevice, kFLEXIO_CAMERA_RxDataRegFullFlag | kFLEXIO_CAMERA_RxErrorFlag);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA����
//  @param      dest_addr       Ŀ�ĵ�ַ
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_dma_restart(uint8 *dest_addr)
{
    DMA0->TCD[DMA_CHN].DADDR = (uint32_t)(dest_addr);
    flexio_csi_flag_clear();
    DMA0->SERQ = DMA_SERQ_SERQ(DMA_CHN);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO RX����DMA����
//  @param      void
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_enable_rxdma(void)
{
    FLEXIO_CAMERA_EnableRxDMA(&s_FlexioCameraDevice, true);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA��ʼ��
//  @param      dest_addr       Ŀ�ĵ�ַ
//  @param      count           DMA�������
//  @param      callback        DMA�жϻص�����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_dma_init(uint8 *dest_addr, uint32 count, edma_callback callback)
{
    edma_modulo_t s_addr_modulo;
    
    DMAMUX_Deinit(DMAMUX);
    DMAMUX_Init(DMAMUX);
    DMAMUX_SetSource(DMAMUX, DMA_CHN, DMA_MUX_SRC);
    DMAMUX_EnableChannel(DMAMUX, DMA_CHN);
    
    EDMA_GetDefaultConfig(&edma_config);
    EDMA_Deinit(DMA0);
    EDMA_Init(DMA0, &edma_config);
    DMA0->CERR = DMA_CERR_CERR_MASK | DMA_CERR_CAEI_MASK;
    
    EDMA_CreateHandle(&g_EDMA_Handle, DMA0, DMA_CHN);
    EDMA_SetCallback(&g_EDMA_Handle, callback, NULL);
    EDMA_PrepareTransfer(&transferConfig, 
                        (void *)FLEXIO_CAMERA_GetRxBufferAddress(&s_FlexioCameraDevice), 
                        4,
                        (void *)(dest_addr), 
                        4,
                        4*flexio_shift_count,
                        count,
                        kEDMA_MemoryToMemory);
    
    
    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);
    
    switch(4*flexio_shift_count)
    {
        case 4:     s_addr_modulo = kEDMA_Modulo4bytes;break;
        case 8:     s_addr_modulo = kEDMA_Modulo8bytes;break;
        case 16:    s_addr_modulo = kEDMA_Modulo16bytes;break;
        case 32:    s_addr_modulo = kEDMA_Modulo32bytes;break;
        default:assert(0);  //��������
    }
    
    
    EDMA_SetModulo(DMA0,DMA_CHN,s_addr_modulo,kEDMA_ModuloDisable);
    EDMA_StartTransfer(&g_EDMA_Handle);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLEXIO��ʼ��ΪCSI(����ͷ)�ӿ�
//  @param      dat_pin_start   ����ͷ���ݽӿڵ���ʼλ
//  @param      pclk_pin        ����ʱ�ӵ�����
//  @param      href_pin        ���źŵ�����
//  @return     void
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void flexio_csi_init(flexio_pin_enum dat_pin_start, flexio_pin_enum pclk_pin, flexio_pin_enum href_pin, uint16 width, uint16 height, uint8 *dest_addr, edma_callback callback)
{
    flexio_iomuxc(dat_pin_start,pclk_pin,href_pin);
    
    if(width * height>=(376*240))   flexio_shift_count = 2;
    else                            flexio_shift_count = 1;
    
    s_FlexioCameraDevice.flexioBase = FLEXIO2;                  // ���û���ַ
    s_FlexioCameraDevice.datPinStartIdx = dat_pin_start;        // ��������������ʼλ
    s_FlexioCameraDevice.pclkPinIdx = pclk_pin;                 // ��������ʱ������
    s_FlexioCameraDevice.hrefPinIdx = href_pin;                 // �������ź�����
    s_FlexioCameraDevice.shifterStartIdx = 4-flexio_shift_count;// ���û�������ʼ���  ����1064�Ļ�����ֻ���ĸ��������д����4-
    s_FlexioCameraDevice.shifterCount = flexio_shift_count;     // ���û���������
    s_FlexioCameraDevice.timerIdx = 3;                          // ���ö�ʱ�����
    
    CLOCK_EnableClock(kCLOCK_Flexio2);
    FLEXIO_Reset(FLEXIO2);
    FLEXIO_CAMERA_GetDefaultConfig(&s_FlexioCameraConfig);
    FLEXIO_CAMERA_Init(&s_FlexioCameraDevice, &s_FlexioCameraConfig);
    FLEXIO_CAMERA_ClearStatusFlags(&s_FlexioCameraDevice, kFLEXIO_CAMERA_RxDataRegFullFlag | kFLEXIO_CAMERA_RxErrorFlag);
    FLEXIO_CAMERA_Enable(&s_FlexioCameraDevice, true);
    
    flexio_csi_dma_init(dest_addr, width * height, callback);
}
