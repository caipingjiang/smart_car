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
* 文件名称          zf_device_mt9v03x
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
*                   TXD                 查看 zf_device_mt9v03x.h 中 MT9V03X_COF_UART_TX 宏定义
*                   RXD                 查看 zf_device_mt9v03x.h 中 MT9V03X_COF_UART_RX 宏定义
*                   PCLK                查看 zf_device_mt9v03x.h 中 MT9V03X_PCLK_PIN 宏定义
*                   VSY                 查看 zf_device_mt9v03x.h 中 MT9V03X_VSYNC_PIN 宏定义
*                   D0-D7               查看 zf_device_mt9v03x.h 中 MT9V03X_DATA_PIN 宏定义 从该定义开始的连续八个引脚
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_debug.h"
#include "zf_common_interrupt.h"
#include "zf_driver_delay.h"
#include "zf_driver_csi.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"
#include "zf_driver_soft_iic.h"
#include "zf_device_camera.h"
#include "zf_device_type.h"
#include "zf_device_config.h"

#include "zf_device_mt9v03x.h"

vuint8 mt9v03x_finish_flag = 0;                                                  // 一场图像采集完成标志位
// 图像缓冲区  如果用户需要访问图像数据 最好通过mt9v03x_csi_image来访问数据，最好不要直接访问缓冲区
AT_DTCM_SECTION_ALIGN(uint8 mt9v03x_image1[MT9V03X_H][MT9V03X_W], 64);
AT_DTCM_SECTION_ALIGN(uint8 mt9v03x_image2[MT9V03X_H][MT9V03X_W], 64);

// 用户访问图像数据直接访问这个指针变量就可以
// 访问方式非常简单，可以直接使用下标的方式访问
// 例如访问第10行 50列的点，mt9v03x_csi_image[10][50]就可以了
uint8 (*mt9v03x_image)[MT9V03X_W];

static m9v03x_type_enum     mt9v03x_type = MT9V03X_SCCB;
static uint16               mt9v03x_version = 0x00;

// 需要配置到摄像头的数据 不允许在这修改参数
static int16 mt9v03x_set_confing_buffer[MT9V03X_CONFIG_FINISH][2]=
{
    {MT9V03X_INIT,              0},                                             // 摄像头开始初始化

    {MT9V03X_AUTO_EXP,          MT9V03X_AUTO_EXP_DEF},                          // 自动曝光设置
    {MT9V03X_EXP_TIME,          MT9V03X_EXP_TIME_DEF},                          // 曝光时间
    {MT9V03X_FPS,               MT9V03X_FPS_DEF},                               // 图像帧率
    {MT9V03X_SET_COL,           MT9V03X_W},                                     // 图像列数量
    {MT9V03X_SET_ROW,           MT9V03X_H},                                     // 图像行数量
    {MT9V03X_LR_OFFSET,         MT9V03X_LR_OFFSET_DEF},                         // 图像左右偏移量
    {MT9V03X_UD_OFFSET,         MT9V03X_UD_OFFSET_DEF},                         // 图像上下偏移量
    {MT9V03X_GAIN,              MT9V03X_GAIN_DEF},                              // 图像增益
    {MT9V03X_PCLK_MODE,         MT9V03X_PCLK_MODE_DEF},                         // 像素时钟模式
};

// 从摄像头内部获取到的配置数据 不允许在这修改参数
static int16 mt9v03x_get_confing_buffer[MT9V03X_CONFIG_FINISH - 1][2]=
{
    {MT9V03X_AUTO_EXP,          0},                                             // 自动曝光设置
    {MT9V03X_EXP_TIME,          0},                                             // 曝光时间
    {MT9V03X_FPS,               0},                                             // 图像帧率
    {MT9V03X_SET_COL,           0},                                             // 图像列数量
    {MT9V03X_SET_ROW,           0},                                             // 图像行数量
    {MT9V03X_LR_OFFSET,         0},                                             // 图像左右偏移量
    {MT9V03X_UD_OFFSET,         0},                                             // 图像上下偏移量
    {MT9V03X_GAIN,              0},                                             // 图像增益
    {MT9V03X_PCLK_MODE,         0},                                             // 像素时钟模式命令 PCLK模式 < 仅总钻风 MT9V034 V1.5 以及以上版本支持该命令 >
};



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     配置摄像头内部配置信息
// 参数说明     buff            发送配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     mt9v03x_set_config(mt9v03x_set_confing_buffer);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 mt9v03x_set_config (int16 buff[MT9V03X_CONFIG_FINISH][2])
{
    uint8 return_state = 1;
    uint8  uart_buffer[4];
    uint16 temp = 0;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    switch(mt9v03x_version)
    {
        case 0x0230:    loop_count = MT9V03X_PCLK_MODE;  break;
        default:        loop_count = MT9V03X_GAIN;       break;
    }
    // 设置参数  具体请参看问题锦集手册
    // 开始配置摄像头并重新初始化
    for(; MT9V03X_SET_DATA > loop_count; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = buff[loop_count][0];
        temp = buff[loop_count][1];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

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
    }while(MT9V03X_INIT_TIMEOUT > timeout_count ++);
    // 以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    // 利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头内部配置信息
// 参数说明     buff            接收配置信息的地址
// 返回参数     uint8           1-失败 0-成功
// 使用示例     mt9v03x_get_config(mt9v03x_get_confing_buffer);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 mt9v03x_get_config (int16 buff[MT9V03X_CONFIG_FINISH - 1][2])
{
    uint8 return_state = 0;
    uint8  uart_buffer[4];
    uint16 temp = 0;
    uint16 timeout_count = 0;
    uint32 loop_count = 0;
    uint32 uart_buffer_index = 0;

    switch(mt9v03x_version)
    {
        case 0x0230:    loop_count = MT9V03X_PCLK_MODE;  break;
        default:        loop_count = MT9V03X_GAIN;       break;
    }

    for(loop_count = loop_count - 1; 1 <= loop_count; loop_count --)
    {
        if((0x0230 > mt9v03x_version) && (MT9V03X_PCLK_MODE == buff[loop_count][0]))
        {
            continue;
        }
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = MT9V03X_GET_STATUS;
        temp = buff[loop_count][0];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

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
        }while(MT9V03X_INIT_TIMEOUT > timeout_count ++);
        if(MT9V03X_INIT_TIMEOUT < timeout_count)                                // 超时
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取摄像头固件版本
// 参数说明     void
// 返回参数     uint16          0-获取错误 N-版本号
// 使用示例     mt9v03x_get_version();                          // 调用该函数前请先初始化串口
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint16 mt9v03x_get_version (void)
{
    uint16 temp = 0;
    uint8  uart_buffer[4];
    uint16 timeout_count = 0;
    uint16 return_value = 0;
    uint32 uart_buffer_index = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = MT9V03X_GET_STATUS;
    temp = MT9V03X_GET_VERSION;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8)temp;
    uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

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
    }while(MT9V03X_INIT_TIMEOUT > timeout_count ++);
    return return_value;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     单独设置摄像头曝光时间
// 参数说明     light           设定曝光时间
// 返回参数     uint8           1-失败 0-成功
// 使用示例     mt9v03x_set_exposure_time(100);                 // 调用该函数前请先初始化串口
// 备注信息     设置曝光时间越大图像越亮
//              摄像头收到后会根据分辨率及FPS计算最大曝光时间如果设置的数据过大
//              那么摄像头将会设置这个最大值
//-------------------------------------------------------------------------------------------------------------------
uint8 mt9v03x_set_exposure_time (uint16 light)
{
    uint8 return_state = 0;
    if(MT9V03X_UART == mt9v03x_type)
    {
        uint8  uart_buffer[4];
        uint16 temp = 0;
        uint16 timeout_count = 0;
        uint32 uart_buffer_index = 0;

        uart_buffer[0] = 0xA5;
        uart_buffer[1] = MT9V03X_SET_EXP_TIME;
        temp = light;
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

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
        }while(MT9V03X_INIT_TIMEOUT > timeout_count ++);
        if((temp != light) || (MT9V03X_INIT_TIMEOUT <= timeout_count))
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = mt9v03x_set_exposure_time_sccb(light);
    }    
    
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     对摄像头内部寄存器进行写操作
// 参数说明     addr            摄像头内部寄存器地址
// 参数说明     data            需要写入的数据
// 返回参数     uint8           1-失败 0-成功
// 使用示例     mt9v03x_set_reg(addr, data);                    // 调用该函数前请先初始化串口
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 mt9v03x_set_reg (uint8 addr, uint16 data)
{
    uint8 return_state = 0;
    if(MT9V03X_UART == mt9v03x_type)
    {
        uint8  uart_buffer[4];
        uint16 temp = 0;
        uint16 timeout_count = 0;
        uint32 uart_buffer_index = 0;

        uart_buffer[0] = 0xA5;
        uart_buffer[1] = MT9V03X_SET_ADDR;
        temp = addr;
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

        system_delay_ms(10);
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = MT9V03X_SET_DATA;
        temp = data;
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

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
        }while(MT9V03X_INIT_TIMEOUT > timeout_count ++);
        if((temp != data) || (MT9V03X_INIT_TIMEOUT <= timeout_count))
        {
            return_state = 1;
        }
    }
    else
    {
        return_state = mt9v03x_set_reg_sccb(addr, data);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X摄像头串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口5中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
static void mt9v03x_uart_callback(void)
{
    uint8 data = 0;
    uart_query_byte(MT9V03X_COF_UART, &data);
    
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
void mt9v03x_finished_callback(CSI_Type *base, csi_handle_t *handle, status_t status, void *userData)
{
    uint32 full_buffer_addr;
    if(csi_get_full_buffer(&csi_handle, &full_buffer_addr))
    {
        if(full_buffer_addr == (uint32)mt9v03x_image1[0])
        {
            mt9v03x_image = mt9v03x_image1; // image_csi1采集完成
            csi_add_empty_buffer(&csi_handle, mt9v03x_image2[0]);
        }
        else if(full_buffer_addr == (uint32)mt9v03x_image2[0])
        {
            mt9v03x_image = mt9v03x_image2; // image_csi2采集完成
            csi_add_empty_buffer(&csi_handle, mt9v03x_image1[0]);
        }
        mt9v03x_finish_flag = 1;            // 采集完成标志位置一
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     MT9V03X 摄像头初始化
// 参数说明     void
// 返回参数     uint8           1-失败 0-成功
// 使用示例     zf_log(mt9v03x_init(), "mt9v03x init error");
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 mt9v03x_init (void)
{
    uint8 return_state = 0;
    soft_iic_info_struct mt9v03x_iic_struct;
    do
    {
        system_delay_ms(200);
        set_camera_type(CAMERA_GRAYSCALE, NULL, NULL, NULL);                        // 设置连接摄像头类型
        // 首先尝试SCCB通讯
        mt9v03x_type = MT9V03X_SCCB;
        soft_iic_init(&mt9v03x_iic_struct, 0, MT9V03X_COF_IIC_DELAY, MT9V03X_COF_IIC_SCL, MT9V03X_COF_IIC_SDA);
        if(mt9v03x_set_config_sccb(&mt9v03x_iic_struct, mt9v03x_set_confing_buffer))
        {
            // SCCB通讯失败，尝试串口通讯
            mt9v03x_type = MT9V03X_UART;
            camera_fifo_init();
            set_camera_type(CAMERA_GRAYSCALE, NULL, NULL, &mt9v03x_uart_callback);  // 设置连接摄像头类型
            uart_init (MT9V03X_COF_UART, MT9V03X_COF_BAUR, MT9V03X_COF_UART_RX, MT9V03X_COF_UART_TX);	//初始换串口 配置摄像头    
            uart_rx_interrupt(MT9V03X_COF_UART, 1);
            fifo_clear(&camera_receiver_fifo);
            mt9v03x_version = mt9v03x_get_version();                                // 获取配置的方式
            
            if(mt9v03x_set_config(mt9v03x_set_confing_buffer))
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是通信出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
                zf_log(0, "MT9V03X set config error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
            
            // 获取配置便于查看配置是否正确
            if(mt9v03x_get_config(mt9v03x_get_confing_buffer))
            {
                // 如果程序在输出了断言信息 并且提示出错位置在这里
                // 那么就是串口通信出错并超时退出了
                // 检查一下接线有没有问题 如果没问题可能就是坏了
                zf_log(0, "MT9V03X get config error.");
                set_camera_type(NO_CAMERE, NULL, NULL, NULL);
                return_state = 1;
                break;
            }
        }

        csi_init(MT9V03X_W, MT9V03X_H, &csi_handle, mt9v03x_finished_callback, MT9V03X_VSYNC_PIN, MT9V03X_PCLK_PIN, CSI_PIXCLK_RISING);
        csi_add_empty_buffer(&csi_handle, mt9v03x_image1[0]);
        csi_add_empty_buffer(&csi_handle, mt9v03x_image2[0]);
        csi_start(&csi_handle);
        mt9v03x_image = mt9v03x_image1;// 设置初值
        
        interrupt_enable(CSI_IRQn);
    }while(0);

    return return_state;
}
