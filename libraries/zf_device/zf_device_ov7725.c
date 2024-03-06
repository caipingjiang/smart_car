/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
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
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          zf_device_ov7725
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/
/*********************************************************************************************************************
* 接线定义：
*                   ------------------------------------
*                   模块管脚            单片机管脚
*                   TXD/SCL             查看 zf_device_ov7725.h 中 OV7725_COF_UART_TX 或 OV7725_COF_IIC_SCL 宏定义
*                   RXD/SDA             查看 zf_device_ov7725.h 中 OV7725_COF_UART_RX 或 OV7725_COF_IIC_SDA 宏定义
*                   PCLK                查看 zf_device_ov7725.h 中 OV7725_PCLK_PIN 宏定义
*                   VSY                 查看 zf_device_ov7725.h 中 OV7725_VSYNC_PIN 宏定义
*                   D0-D7               查看 zf_device_ov7725.h 中 OV7725_DATA_PIN 宏定义 从该定义开始的连续八个引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
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

// 图像缓冲区  如果用户需要访问图像数据 最好通过mt9v03x_csi_image来访问数据，最好不要直接访问缓冲区
AT_DTCM_SECTION_ALIGN(uint8 ov7725_image_binary1[OV7725_H][OV7725_W / 8], 64);
AT_DTCM_SECTION_ALIGN(uint8 ov7725_image_binary2[OV7725_H][OV7725_W / 8], 64);

// 用户访问图像数据直接访问这个指针变量就可以
// 访问方式非常简单，可以直接使用下标的方式访问
// 例如访问第10行 50列的点，mt9v03x_csi_image[10][50]就可以了
uint8 (*ov7725_image_binary)[OV7725_W / 8];

// 需要配置到摄像头的数据 不允许在这修改参数
static uint16 ov7725_set_confing_buffer [OV7725_CONFIG_FINISH][2]=
{
    {OV7725_INIT,           0},                                                 // 初始化命令

    {OV7725_RESERVE,        0},                                                 // 保留
    {OV7725_CONTRAST,       OV7725_CONTRAST_DEF},                               // 阈值设置
    {OV7725_FPS,            OV7725_FPS_DEF},                                    // 帧率
    {OV7725_COL,            OV7725_W},                                          // 图像宽度
    {OV7725_ROW,            OV7725_H}                                           // 图像高度
};

// 从摄像头内部获取到的配置数据 不允许在这修改参数
static uint16 ov7725_get_confing_buffer [OV7725_CONFIG_FINISH - 1][2]=
{
    {OV7725_RESERVE,        0},                                                 // 保留
    {OV7725_CONTRAST,       0},                                                 // 阈值设置
    {OV7725_FPS,            0},                                                 // 帧率
    {OV7725_COL,            0},                                                 // 图像宽度
    {OV7725_ROW,            0}                                                  // 图像高度
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     配置摄像头内部配置信息
// 参数说明     buff            发送配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(ov7725_set_config(ov7725_set_confing_buffer)){}
// 备注信息     内部调用
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

    // 以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    // 利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头内部配置信息
// 参数说明     buff            接收配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(ov7725_get_config(ov7725_get_confing_buffer)){}
// 备注信息     内部调用
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
        if(OV7725_INIT_TIMEOUT < timeout_count)                                 // 超时
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     小钻风摄像头内部寄存器初始化
// 参数说明     void
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(ov7725_iic_init()){}
// 备注信息     内部使用 用户无需调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 ov7725_iic_init (void)
{
    soft_iic_info_struct ov7725_iic_struct;
    uint8 ov7725_idcode = 0;
    uint8 return_state = 0;

    uart_rx_interrupt(OV7725_COF_UART, 0);

    soft_iic_init(&ov7725_iic_struct, OV7725_DEV_ADD, OV7725_COF_IIC_DELAY, OV7725_COF_IIC_SCL, OV7725_COF_IIC_SDA);

    soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM7, 0x80);        // 复位摄像头
    system_delay_ms(50);

    do
    {
        ov7725_idcode = soft_iic_sccb_read_register(&ov7725_iic_struct, OV7725_VER);
        if(OV7725_ID != ov7725_idcode)
        {
            return_state = 1;                                                   // 校验摄像头ID号
            break;
        }

        // ID号确认无误   然后配置寄存器
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM4         , 0xC1);  
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_CLKRC        , 0x01);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM2         , 0x03);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM3         , 0xD0);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM7         , 0x40);
        soft_iic_sccb_write_register(&ov7725_iic_struct, OV7725_COM8         , 0xCE);   // 0xCE:关闭自动曝光  0xCF：开启自动曝光
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
// 函数简介     获取摄像头固件 ID
// 参数说明     void
// 返回参数     void
// 使用示例     ov7725_uart_get_id();                           // 调用该函数前请先初始化串口
// 备注信息     
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
// 函数简介     获取摄像头固件版本
// 参数说明     void
// 返回参数     void
// 使用示例     ov7725_get_version();                           // 调用该函数前请先初始化串口
// 备注信息     
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
//  @brief      MT9V03X摄像头串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口5中断程序被调用
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
//  @brief      MT9V03X摄像头采集完成中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数由isr.c中的CSI_IRQHandler函数调用
//-------------------------------------------------------------------------------------------------------------------
void ov7725_finished_callback(CSI_Type *base, csi_handle_t *handle, status_t status, void *userData)
{
    uint32 full_buffer_addr;
    if(csi_get_full_buffer(&csi_handle, &full_buffer_addr))
    {
        if(full_buffer_addr == (uint32)ov7725_image_binary1[0])
        {
            ov7725_image_binary = ov7725_image_binary1; // image_csi1采集完成
        csi_add_empty_buffer(&csi_handle, ov7725_image_binary2[0]);
        }
        else if(full_buffer_addr == (uint32)ov7725_image_binary2[0])
        {
            ov7725_image_binary = ov7725_image_binary2; // image_csi2采集完成
        csi_add_empty_buffer(&csi_handle, ov7725_image_binary1[0]);
        }
        ov7725_finish_flag = 1;                         // 采集完成标志位置一
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     OV7725 摄像头初始化
// 参数说明     NULL
// 返回参数     void
// 使用示例     ov7725_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 ov7725_init (void)
{
    uint8 return_state = 0;

    do
    {
        set_camera_type(CAMERA_BIN_UART, NULL, NULL, &ov7725_uart_callback);       // 设置连接摄像头类型
        camera_fifo_init();

        uart_init(OV7725_COF_UART, OV7725_COF_BAUR, OV7725_COF_UART_RX, OV7725_COF_UART_TX);
        uart_rx_interrupt(OV7725_COF_UART, 1);
        system_delay_ms(200);
        
        fifo_clear(&camera_receiver_fifo);

        // 获取所有参数
        if(ov7725_get_config(ov7725_get_confing_buffer))
        {
            system_delay_ms(200);
            set_camera_type(CAMERA_BIN_IIC, NULL, NULL, NULL);
            if(ov7725_iic_init())
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是 IIC 出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
                zf_log(0, "OV7725 IIC error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
        }
        else
        {
            // 设置所有参数
            if(ov7725_set_config(ov7725_set_confing_buffer))
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是串口通信出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
                zf_log(0, "OV7725 set confing error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
            // 获取所有参数
            if(ov7725_get_config(ov7725_get_confing_buffer))
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是串口通信出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
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
        ov7725_image_binary = ov7725_image_binary1;// 设置初值
        
        interrupt_enable(CSI_IRQn);
    }while(0);

    return return_state;
}
