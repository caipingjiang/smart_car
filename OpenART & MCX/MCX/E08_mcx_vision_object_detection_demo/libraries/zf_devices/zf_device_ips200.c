/*********************************************************************************************************************
* MCX Vision Opensourec Library 即（MCX Vision 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2024 SEEKFREE 逐飞科技
* 
* 本文件是 MCX Vision 开源库的一部分
* 
* MCX Vision 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_device_ips200
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK 5.38a
* 适用平台          MCX Vision
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2024-04-21        ZSY            first version
********************************************************************************************************************/
#include "zf_device_ips200.h"

const gpio_struct ips200_rst_pin = IPS200_RST_PIN;
const gpio_struct ips200_dc_pin = IPS200_DC_PIN;
const gpio_struct ips200_blk_pin = IPS200_BLK_PIN;
lpspi_master_config_t masterConfig;
lpspi_transfer_t spi_masterfer = {  .rxData = NULL, \
                                    .configFlags = kLPSPI_MasterPcs0 | kLPSPI_MasterPcsContinuous | kLPSPI_MasterByteSwap};
lpspi_master_edma_handle_t g_m_edma_handle = {0};
volatile bool isTransferCompleted  = false;

void LPSPI_MasterUserCallback(LPSPI_Type *base, lpspi_master_edma_handle_t *handle, status_t status, void *userData)
{
    isTransferCompleted = true;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 写命令
// 参数说明     command         命令
// 返回参数     void
// 使用示例     ips200_write_command(0x2a);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_command (const uint8_t command)
{
    IPS200_DC(0);
    spi_masterfer.txData   = (uint8*)&command;
    spi_masterfer.dataSize = 1;
    isTransferCompleted = false;
    LPSPI_MasterTransferEDMA(IPS200_SPI, &g_m_edma_handle, &spi_masterfer);
    while (!isTransferCompleted);
    IPS200_DC(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 向液晶屏写 8bit 数据
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips200_write_8bit_data(0x0C);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_8bit_data (const uint8_t dat)
{    
    spi_masterfer.txData   = (uint8*)&dat;
    spi_masterfer.dataSize = 1;
    isTransferCompleted = false;
    LPSPI_MasterTransferEDMA(IPS200_SPI, &g_m_edma_handle, &spi_masterfer);
    while (!isTransferCompleted);
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 向液晶屏写 8bit 数据
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips200_write_8bit_data(0x0C);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_8bit_data_array (const uint8_t *dat, uint32_t len)
{
    spi_masterfer.txData   = (uint8*)dat;
    spi_masterfer.dataSize = len;
    isTransferCompleted = false;
    LPSPI_MasterTransferEDMA(IPS200_SPI, &g_m_edma_handle, &spi_masterfer);
    while (!isTransferCompleted);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 向液晶屏写 16bit 数据
// 参数说明     dat             数据
// 返回参数     void
// 使用示例     ips200_write_8bit_data(0x0C);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_write_16bit_data (const uint16_t dat)
{
    uint8_t temp_data[2];
    temp_data[0] = dat >> 8;
    temp_data[1] = dat;
    isTransferCompleted = false;
    ips200_write_8bit_data_array(temp_data, 2);
    while (!isTransferCompleted);
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     设置显示区域
// 参数说明     x1              起始x轴坐标
// 参数说明     y1              起始y轴坐标
// 参数说明     x2              结束x轴坐标
// 参数说明     y2              结束y轴坐标
// 返回参数     void
// 使用示例     ips200_set_region(0, 0, ips200_x_max - 1, ips200_y_max - 1);
// 备注信息     内部调用 用户无需关心
//-------------------------------------------------------------------------------------------------------------------
static void ips200_set_region (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ips200_write_command(0x2a);
    ips200_write_16bit_data(x1);
    ips200_write_16bit_data(x2);

    ips200_write_command(0x2b);
    ips200_write_16bit_data(y1);
    ips200_write_16bit_data(y2);

    ips200_write_command(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 画点
// 参数说明     x               坐标x方向的起点 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 [0, ips200_y_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_draw_point(0, 0, RGB565_RED);            //坐标0,0画一个红色的点
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_draw_point (uint16 x, uint16 y, const uint16 color)
{
    ips200_set_region(x, y, x, y);
    ips200_write_16bit_data(color);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 画线
// 参数说明     x_start         坐标x方向的起点 [0, ips200_x_max-1]
// 参数说明     y_start         坐标y方向的起点 [0, ips200_y_max-1]
// 参数说明     x_end           坐标x方向的终点 [0, ips200_x_max-1]
// 参数说明     y_end           坐标y方向的终点 [0, ips200_y_max-1]
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_draw_line(0, 0, 10, 10, RGB565_RED);     // 坐标 0,0 到 10,10 画一条红色的线
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_draw_line (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color)
{
    int16 x_dir = (x_start < x_end ? 1 : -1);
    int16 y_dir = (y_start < y_end ? 1 : -1);
    float temp_rate = 0;
    float temp_b = 0;

    do
    {
        if(x_start != x_end)
        {
            temp_rate = (float)(y_start - y_end) / (float)(x_start - x_end);
            temp_b = (float)y_start - (float)x_start * temp_rate;
        }
        else
        {
            while(y_start != y_end)
            {
                ips200_draw_point(x_start, y_start, color);
                y_start += y_dir;
            }
            break;
        }
        if(func_abs(y_start - y_end) > func_abs(x_start - x_end))
        {
            while(y_start != y_end)
            {
                ips200_draw_point(x_start, y_start, color);
                y_start += y_dir;
                x_start = (int16)(((float)y_start - temp_b) / temp_rate);
            }
        }
        else
        {
            while(x_start != x_end)
            {
                ips200_draw_point(x_start, y_start, color);
                x_start += x_dir;
                y_start = (int16)((float)x_start * temp_rate + temp_b);
            }
        }
    }while(0);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 屏幕填充函数
// 参数说明     color           颜色格式 RGB565 或者可以使用 zf_common_font.h 内 rgb565_color_enum 枚举值或者自行写入
// 返回参数     void
// 使用示例     ips200_full(0);
// 备注信息     将屏幕填充成指定颜色
//-------------------------------------------------------------------------------------------------------------------
void ips200_full (const uint16_t color)
{
    uint8_t color_buffer[320*2];
    uint16_t i = 0, j = 0;

    for(i = 0; i < 320; i ++)
    {
        color_buffer[i * 2] = (uint8_t)(color >> 8);
        color_buffer[i * 2 + 1] = (color);
    }
    ips200_set_region(0, 0, 320 - 1, 240 - 1);
    for (j = 0; j < 240; j ++)
    {
        ips200_write_8bit_data_array(color_buffer, 640);
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示字符
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的字符
// 返回参数     void
// 使用示例     ips200_show_char(0, 0, 'x');                     // 坐标0,0写一个字符x
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_char (uint16 x, uint16 y, const char dat)
{

    uint8 i = 0, j = 0;
    uint16 display_buffer[8*16];
    ips200_set_region(x, y, x + 7, y + 15);
    for(i = 0; 8 > i; i ++)
    {
        uint8 temp_top = ascii_font_8x16[dat - 32][i];
        uint8 temp_bottom = ascii_font_8x16[dat - 32][i + 8];
        for(j = 0; 8 > j; j ++)
        {
            if(temp_top & 0x01)
            {
                display_buffer[i + j * 8] = (RGB565_BLACK);
            }
            else
            {
                display_buffer[i + j * 8] = (RGB565_WHITE);
            }
            temp_top >>= 1;
        }
        for(j = 0; 8 > j; j ++)
        {
            if(temp_bottom & 0x01)
            {
                display_buffer[i + j * 8 + 4 * 16] = (RGB565_BLACK);
            }
            else
            {
                display_buffer[i + j * 8 + 4 * 16] = (RGB565_WHITE);
            }
            temp_bottom >>= 1;
        }
    }
    ips200_write_8bit_data_array((uint8*)display_buffer, 8 * 16 * 2);

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示字符串
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的字符串
// 返回参数     void
// 使用示例     ips200_show_string(0, 0, "seekfree");
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_string (uint16 x, uint16 y, const char dat[])
{
    uint16 j = 0;
    while('\0' != dat[j])
    {
        ips200_show_char(x + 8 * j, y, dat[j]);
        j ++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示32位有符号 (去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 int32
// 返回参数     void
// 使用示例     ips200_show_int(0, 0, x, 3);                    // x 可以为 int32 int16 int8 类型
// 备注信息     负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_int (uint16 x, uint16 y, const int32 dat)
{
    char data_buffer[12];
    memset(data_buffer, ' ', 12);

    int_to_str(dat, data_buffer);
    ips200_show_string(x, y, (const char *)&data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 显示浮点数(去除整数部分无效的0)
// 参数说明     x               坐标x方向的起点 参数范围 [0, ips200_x_max-1]
// 参数说明     y               坐标y方向的起点 参数范围 [0, ips200_y_max-1]
// 参数说明     dat             需要显示的变量 数据类型 float
// 返回参数     void
// 使用示例     ips200_show_float(0, 0, x);               // 显示浮点数   整数显示2位   小数显示三位
// 备注信息     特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//              负数会显示一个 ‘-’号
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_float (uint16 x, uint16 y, const float dat)
{
    char data_buffer[17];
    memset(data_buffer, ' ', 17);
    float_to_str(dat, data_buffer);
    ips200_show_string(x, y, data_buffer);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IPS200 屏幕显示摄像头图像函数
// 参数说明     data           摄像头数据
// 返回参数     void
// 使用示例     ips200_show_scc8660(scc8660_image);
//-------------------------------------------------------------------------------------------------------------------
void ips200_show_scc8660 (uint16_t* data)
{
    uint16_t i = 0, j = 0;

#if (FRAME_SIZE == SCC8660_QVGA)
    ips200_set_region(0, 0, 320 - 1, 240 - 1);
    for (j = 0; j < 8; j ++)
    {
        ips200_write_8bit_data_array((uint8_t*)(&data[j * 3200 * 3]), 6400 * 3);
    }
#elif (FRAME_SIZE == SCC8660_QQVGA)
    ips200_set_region(0, 0, 160 - 1, 120 - 1);
    for (j = 0; j < 4; j ++)
    {
        ips200_write_8bit_data_array((uint8_t*)(&data[j * 1600 * 3]), 3200 * 3);
    }
#endif
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     2寸 IPS液晶初始化
// 返回参数     void
// 使用示例     ips200_init();
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void ips200_init (void)
{
    edma_config_t userConfig = {0};
    static edma_handle_t ips200_dma_rxhandle;
    static edma_handle_t ips200_dma_txhandle;
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom1Clk, 1u);
    CLOCK_AttachClk(kFRO_HF_DIV_to_FLEXCOMM1);
    
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Port0);
    CLOCK_EnableClock(kCLOCK_Dma0);

    PORT0->PCR[24] = (2<<8) |(1<<12);
    PORT0->PCR[25] = (2<<8) |(1<<12);
    PORT0->PCR[26] = (2<<8) |(1<<12);
    PORT0->PCR[27] = (2<<8) |(1<<12);
    
    NVIC_SetPriority(EDMA_0_CH0_IRQn, 0);
    NVIC_SetPriority(EDMA_0_CH1_IRQn, 0);
    NVIC_SetPriority(LP_FLEXCOMM1_IRQn, 0);
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DMA0, &userConfig);

    /*Master config*/
    LPSPI_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate = IPS200_SPI_BAUDRATE;
    masterConfig.whichPcs = kLPSPI_Pcs0;
    masterConfig.betweenTransferDelayInNanoSec = 14;
    masterConfig.lastSckToPcsDelayInNanoSec = 0;
    masterConfig.pcsToSckDelayInNanoSec = 7;                                                    
                                             
    LPSPI_MasterInit(IPS200_SPI, &masterConfig, CLOCK_GetLPFlexCommClkFreq(1u));

    /*Set up lpspi master*/
    memset(&(ips200_dma_rxhandle), 0, sizeof(ips200_dma_rxhandle));
    memset(&(ips200_dma_txhandle), 0, sizeof(ips200_dma_txhandle));

    EDMA_CreateHandle(&(ips200_dma_rxhandle), DMA0, 0u);
    EDMA_CreateHandle(&(ips200_dma_txhandle), DMA0, 1u);    

    EDMA_SetChannelMux(DMA0, 0u, 71u);
    EDMA_SetChannelMux(DMA0, 1u, 72u);
    
    LPSPI_MasterTransferCreateHandleEDMA(IPS200_SPI, &g_m_edma_handle, 
                                            LPSPI_MasterUserCallback,
                                            NULL, 
                                            &ips200_dma_rxhandle,
                                            &ips200_dma_txhandle);
    gpio_init(ips200_rst_pin, GPO, GPIO_HIGH, PULL_UP);
    gpio_init(ips200_dc_pin, GPO, GPIO_HIGH, PULL_UP);
    gpio_init(ips200_blk_pin, GPO, GPIO_HIGH, PULL_UP);
    
    NVIC_SetPriority(EDMA_0_CH0_IRQn, 0);
    NVIC_SetPriority(EDMA_0_CH1_IRQn, 0);
    NVIC_SetPriority(LP_FLEXCOMM1_IRQn, 0);
    EnableIRQ(EDMA_0_CH0_IRQn);
    EnableIRQ(EDMA_0_CH1_IRQn);
    EnableIRQ(LP_FLEXCOMM1_IRQn);
    IPS200_BLK(1);
    IPS200_RST(0);
	system_delay_ms(5);
    IPS200_RST(1);
	system_delay_ms(20);

    ips200_write_command(0x11);
    ips200_write_command(0x36);
    switch(IPS200_DEFAULT_DISPLAY_DIR)
    {
        case IPS200_CROSSWISE:      ips200_write_8bit_data(0xA0);   break;
        case IPS200_CROSSWISE_180:  ips200_write_8bit_data(0x70);   break;
    }
    ips200_write_command(0x3A);
    ips200_write_8bit_data(0x05);

    ips200_write_command(0xB2);
    ips200_write_8bit_data(0x0C);
    ips200_write_8bit_data(0x0C);
    ips200_write_8bit_data(0x00);
    ips200_write_8bit_data(0x33);
    ips200_write_8bit_data(0x33);

    ips200_write_command(0xB7);
    ips200_write_8bit_data(0x35);

    ips200_write_command(0xBB);
    ips200_write_8bit_data(0x29);                                              

    ips200_write_command(0xC2);
    ips200_write_8bit_data(0x01);

    ips200_write_command(0xC3);
    ips200_write_8bit_data(0x19);                                              

    ips200_write_command(0xC4);
    ips200_write_8bit_data(0x20);                                              

    ips200_write_command(0xC5);
    ips200_write_8bit_data(0x1A);                                              

    ips200_write_command(0xC6);
    ips200_write_8bit_data(0x1F);                                              

    ips200_write_command(0xD0);
    ips200_write_8bit_data(0xA4);
    ips200_write_8bit_data(0xA1);

    ips200_write_command(0xE0);
    ips200_write_8bit_data(0xD0);
    ips200_write_8bit_data(0x08);
    ips200_write_8bit_data(0x0E);
    ips200_write_8bit_data(0x09);
    ips200_write_8bit_data(0x09);
    ips200_write_8bit_data(0x05);
    ips200_write_8bit_data(0x31);
    ips200_write_8bit_data(0x33);
    ips200_write_8bit_data(0x48);
    ips200_write_8bit_data(0x17);
    ips200_write_8bit_data(0x14);
    ips200_write_8bit_data(0x15);
    ips200_write_8bit_data(0x31);
    ips200_write_8bit_data(0x34);

    ips200_write_command(0xE1);
    ips200_write_8bit_data(0xD0);
    ips200_write_8bit_data(0x08);
    ips200_write_8bit_data(0x0E);
    ips200_write_8bit_data(0x09);
    ips200_write_8bit_data(0x09);
    ips200_write_8bit_data(0x15);
    ips200_write_8bit_data(0x31);
    ips200_write_8bit_data(0x33);
    ips200_write_8bit_data(0x48);
    ips200_write_8bit_data(0x17);
    ips200_write_8bit_data(0x14);
    ips200_write_8bit_data(0x15);
    ips200_write_8bit_data(0x31);
    ips200_write_8bit_data(0x34);

    ips200_write_command(0x21);

    ips200_write_command(0x29);
    
    ips200_full(0xffff);
}
