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
* 文件名称          zf_device_scc8660_flexio
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
*                   TXD                 查看 zf_device_scc8660_flexio.h 中 SCC8660_FLEXIO_COF_UART_TX 宏定义
*                   RXD                 查看 zf_device_scc8660_flexio.h 中 SCC8660_FLEXIO_COF_UART_RX 宏定义
*                   PCLK                查看 zf_device_scc8660_flexio.h 中 SCC8660_FLEXIO_PCLK_PIN 宏定义
*                   VSY                 查看 zf_device_scc8660_flexio.h 中 SCC8660_FLEXIO_VSYNC_PIN 宏定义
*                   D0-D7               查看 zf_device_scc8660_flexio.h 中 SCC8660_FLEXIO_DATA_PIN 宏定义 从该定义开始的连续八个引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
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

vuint8 scc8660_flexio_finish_flag = 0;                                                  // 一场图像采集完成标志位

AT_DTCM_SECTION_ALIGN(uint16 scc8660_flexio_image[SCC8660_FLEXIO_H][SCC8660_FLEXIO_W], 4);

static scc8660_flexio_type_enum scc8660_flexio_type;

// 需要配置到摄像头的数据 不允许在这修改参数
static int16 scc8660_flexio_set_confing_buffer[SCC8660_FLEXIO_CONFIG_FINISH][2]=
{
    {SCC8660_FLEXIO_INIT,              0},                                              // 摄像头开始初始化

    {SCC8660_FLEXIO_AUTO_EXP,          SCC8660_FLEXIO_AUTO_EXP_DEF},                    // 自动曝光
    {SCC8660_FLEXIO_BRIGHT,            SCC8660_FLEXIO_BRIGHT_DEF},                      // 亮度设置
    {SCC8660_FLEXIO_FPS,               SCC8660_FLEXIO_FPS_DEF},                         // 图像帧率
    {SCC8660_FLEXIO_SET_COL,           SCC8660_FLEXIO_W},                               // 图像列数
    {SCC8660_FLEXIO_SET_ROW,           SCC8660_FLEXIO_H},                               // 图像行数
    {SCC8660_FLEXIO_PCLK_DIV,          SCC8660_FLEXIO_PCLK_DIV_DEF},                    // PCLK分频系数
    {SCC8660_FLEXIO_PCLK_MODE,         SCC8660_FLEXIO_PCLK_MODE_DEF},                   // PCLK模式
    {SCC8660_FLEXIO_COLOR_MODE,        SCC8660_FLEXIO_COLOR_MODE_DEF},                  // 图像色彩模式
    {SCC8660_FLEXIO_DATA_FORMAT,       SCC8660_FLEXIO_DATA_FORMAT_DEF},                 // 输出数据格式
    {SCC8660_FLEXIO_MANUAL_WB,         SCC8660_FLEXIO_MANUAL_WB_DEF}                    // 手动白平衡
};

// 从摄像头内部获取到的配置数据 不允许在这修改参数
static int16 scc8660_flexio_get_confing_buffer[SCC8660_FLEXIO_CONFIG_FINISH - 1][2]=
{
    {SCC8660_FLEXIO_AUTO_EXP,          0},
    {SCC8660_FLEXIO_BRIGHT,            0},                                              // 亮度设置          
    {SCC8660_FLEXIO_FPS,               0},                                              // 图像帧率           
    {SCC8660_FLEXIO_SET_COL,           0},                                              // 图像列数           
    {SCC8660_FLEXIO_SET_ROW,           0},                                              // 图像行数          
    {SCC8660_FLEXIO_PCLK_DIV,          0},                                              // PCLK分频系数      
    {SCC8660_FLEXIO_PCLK_MODE,         0},                                              // PCLK模式      
    {SCC8660_FLEXIO_COLOR_MODE,        0},                                              // 图像色彩模式
    {SCC8660_FLEXIO_DATA_FORMAT,       0},                                              // 输出数据格式    
    {SCC8660_FLEXIO_MANUAL_WB,         0},                                              // 白平衡设置
};

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     配置摄像头内部配置信息 内部调用
// 参数说明     buff            发送配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(scc8660_flexio_set_config(scc8660_flexio_set_confing_buffer)){}
// 备注信息     调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
static uint8 scc8660_flexio_set_config (int16 buff[SCC8660_FLEXIO_CONFIG_FINISH][2])
{
    uint8 return_state = 1;
    uint8  uart_buffer[4];
    uint16 temp;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    // 设置参数  具体请参看问题锦集手册
    // 开始配置摄像头并重新初始化
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

    // 以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    // 利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头内部配置信息 内部调用
// 参数说明     buff            接收配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     if(scc8660_flexio_get_config(scc8660_flexio_get_confing_buffer)){}
// 备注信息     调用该函数前请先初始化串口
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
        if(timeout_count > SCC8660_FLEXIO_INIT_TIMEOUT)                                // 超时
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头 ID
// 参数说明     void
// 返回参数     uint16          0-获取错误 N-版本号
// 使用示例     scc8660_flexio_flexio_get_id();                               // 调用该函数前请先初始化串口
// 备注信息     
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
// 函数简介     单独设置摄像头曝光时间
// 参数说明     light           设置曝光时间越大图像越亮，摄像头收到后会根据分辨率及FPS计算最大曝光时间如果设置的数据过大，那么摄像头将会设置这个最大值
// 返回参数     uint16          数据
// 使用示例     scc8660_flexio_get_parameter();                                        // 调用该函数前请先初始化串口
// 备注信息     
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
// 函数简介     获取彩色摄像头固件版本
// 参数说明     void
// 返回参数     uint16          版本号
// 使用示例     scc8660_flexio_get_version();                                          // 调用该函数前请先初始化摄像头配置串口
// 备注信息     
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
// 函数简介     单独设置图像亮度
// 参数说明     data            需要设置的亮度值
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_flexio_set_bright(data);                                       // 通过该函数设置的参数，不会被51单片机保存
// 备注信息     调用该函数前请先初始化摄像头配置串口
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
// 函数简介     单独设置白平衡
// 参数说明     data            需要设置的亮度值
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_flexio_set_white_balance(data);                // 调用该函数前请先初始化摄像头配置串口
// 备注信息     通过该函数设置的参数，不会被51单片机保存
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
// 函数简介     对摄像头内部寄存器进行写操作
// 参数说明     addr            摄像头内部寄存器地址
// 参数说明     data            需要写入的数据
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_flexio_set_reg(addr, data);                    // 调用该函数前请先初始化串口
// 备注信息     
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
//  @brief      SCC8660 摄像头串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口5中断程序被调用
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
//  @brief      SCC8660 摄像头采集完成中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数由isr.c中的CSI_IRQHandler函数调用
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
//  @brief      SCC8660 摄像头DMA完成中断
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
// 函数简介     SCC8660 摄像头初始化
// 参数说明     void
// 返回参数     uint8           1-失败 0-成功
// 使用示例     scc8660_flexio_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 scc8660_flexio_init (void)
{
    uint8 return_state = 0;
    soft_iic_info_struct scc8660_flexio_iic_struct;
    do
    {
        // 对摄像头初始化之前先拉高场信号
        gpio_init(SCC8660_FLEXIO_VSYNC_PIN, GPO, 1, GPO_PUSH_PULL);
        
        system_delay_ms(200);
        set_flexio_camera_type(CAMERA_COLOR, &scc8660_flexio_vsync_callback, NULL, NULL);                                           // 设置连接摄像头类型
        // 首先尝试SCCB通讯
        scc8660_flexio_type = SCC8660_FLEXIO_SCCB;
        soft_iic_init(&scc8660_flexio_iic_struct, 0, SCC8660_FLEXIO_COF_IIC_DELAY, SCC8660_FLEXIO_COF_IIC_SCL, SCC8660_FLEXIO_COF_IIC_SDA);
        if(scc8660_set_config_sccb(&scc8660_flexio_iic_struct, scc8660_flexio_set_confing_buffer))
        {
            // SCCB通讯失败，尝试串口通讯
            scc8660_flexio_type = SCC8660_FLEXIO_UART;
            camera_fifo_init();
            set_flexio_camera_type(CAMERA_COLOR, &scc8660_flexio_vsync_callback, NULL, &scc8660_flexio_uart_callback);              // 设置连接摄像头类型
            uart_init (SCC8660_FLEXIO_COF_UART, SCC8660_FLEXIO_COF_BAUR, SCC8660_FLEXIO_COF_UART_RX, SCC8660_FLEXIO_COF_UART_TX);	//初始换串口 配置摄像头    
            uart_rx_interrupt(SCC8660_FLEXIO_COF_UART, 1);
            fifo_clear(&camera_receiver_fifo);
            
            scc8660_flexio_get_version();                                                      // 获取配置的方式
            
            if(scc8660_flexio_set_config(scc8660_flexio_set_confing_buffer))
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是串口通信出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
                zf_log(0, "SCC8660 set config error.");
                set_flexio_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }

            // 获取配置便于查看配置是否正确
            if(scc8660_flexio_get_config(scc8660_flexio_get_confing_buffer))
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是串口通信出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
                zf_log(0, "SCC8660 get config error.");
                set_flexio_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
        }

        flexio_csi_init(SCC8660_FLEXIO_DATA_PIN, SCC8660_FLEXIO_PCLK_PIN, SCC8660_FLEXIO_HREF_PIN, SCC8660_FLEXIO_W * 2, SCC8660_FLEXIO_H, (uint8 *)scc8660_flexio_image[0], scc8660_flexio_dma_callback);
        flexio_csi_enable_rxdma();
        NVIC_SetPriority(DMA0_DMA16_IRQn, 1);                   // 设置DMA中断优先级 范围0-15 越小优先级越高
        interrupt_enable(DMA0_DMA16_IRQn);
        
        //设置场中断
        exti_init(SCC8660_FLEXIO_VSYNC_PIN, EXTI_TRIGGER_FALLING);
        NVIC_SetPriority(SCC8660_FLEXIO_VSYNC_IRQN, 0);         // 设置场中断优先级 范围0-15 越小优先级越高
    }while(0);

    return return_state;
}
