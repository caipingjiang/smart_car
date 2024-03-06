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
* 文件名称          zf_device_imu660ra
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
*                   // 硬件 SPI 引脚
*                   SCL/SPC           查看 zf_device_imu660ra.h 中 IMU660RA_SPC_PIN 宏定义
*                   SDA/DSI           查看 zf_device_imu660ra.h 中 IMU660RA_SDI_PIN 宏定义
*                   SA0/SDO           查看 zf_device_imu660ra.h 中 IMU660RA_SDO_PIN 宏定义
*                   CS                查看 zf_device_imu660ra.h 中 IMU660RA_CS_PIN 宏定义
*                   VCC               3.3V电源
*                   GND               电源地
*                   其余引脚悬空
*
*                   // 软件 IIC 引脚
*                   SCL/SPC           查看 zf_device_imu660ra.h 中 IMU660RA_SCL_PIN 宏定义
*                   SDA/DSI           查看 zf_device_imu660ra.h 中 IMU660RA_SDA_PIN 宏定义
*                   VCC               3.3V电源
*                   GND               电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_debug.h"
#include "zf_driver_delay.h"
#include "zf_driver_spi.h"
#include "zf_driver_gpio.h"
#include "zf_driver_soft_iic.h"
#include "zf_device_config.h"
#include "zf_device_imu660ra.h"

int16 imu660ra_gyro_x = 0, imu660ra_gyro_y = 0, imu660ra_gyro_z = 0;            // 三轴陀螺仪数据   gyro (陀螺仪)
int16 imu660ra_acc_x = 0, imu660ra_acc_y = 0, imu660ra_acc_z = 0;               // 三轴加速度计数据 acc  (accelerometer 加速度计)
float imu660ra_transition_factor[2] = {4096, 16.4};

#if IMU660RA_USE_SOFT_IIC
static soft_iic_info_struct imu660ra_iic_struct;

#define imu660ra_write_register(reg, data)        (soft_iic_write_8bit_register (&imu660ra_iic_struct, (reg), (data)))
#define imu660ra_write_registers(reg, data, len)  (soft_iic_write_8bit_registers(&imu660ra_iic_struct, (reg), (data), (len)))
#define imu660ra_read_register(reg)               (soft_iic_read_8bit_register  (&imu660ra_iic_struct, (reg)))
#define imu660ra_read_registers(reg, data, len)   (soft_iic_read_8bit_registers (&imu660ra_iic_struct, (reg), (data), (len)))
#else
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU660RA 写寄存器
// 参数说明     reg             寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                   // 关闭高级省电模式
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_write_register (uint8 reg, uint8 data)
{
    IMU660RA_CS(0);
    spi_write_8bit_register(IMU660RA_SPI, reg | IMU660RA_SPI_W, data);
    IMU660RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU660RA 写数据
// 参数说明     reg             寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_write_registers (uint8 reg, const uint8 *data, uint32 len)
{
    IMU660RA_CS(0);
    spi_write_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_W, data, len);
    IMU660RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU660RA 读寄存器
// 参数说明     reg             寄存器地址
// 返回参数     uint8           数据
// 使用示例     imu660ra_read_register(IMU660RA_CHIP_ID);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu660ra_read_register (uint8 reg)
{
    uint8 data[2];
    IMU660RA_CS(0);
    spi_read_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_R, data, 2);
    IMU660RA_CS(1);
    return data[1];
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU660RA 读数据
// 参数说明     reg             寄存器地址
// 参数说明     data            数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_read_registers (uint8 reg, uint8 *data, uint32 len)
{
    uint8 temp_data[8];
    IMU660RA_CS(0);
    spi_read_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_R, temp_data, len + 1);
    IMU660RA_CS(1);
    for(int i = 0; i < len; i ++)
    {
        *(data ++) = temp_data[i + 1];
    }
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU660RA 自检
// 参数说明     void
// 返回参数     uint8           1-自检失败 0-自检成功
// 使用示例     imu660ra_self_check();
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu660ra_self_check (void)
{
    uint8 dat = 0, return_state = 0;
    uint16 timeout_count = 0;
    do
    {
        if(IMU660RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state =  1;
            break;
        }
        dat = imu660ra_read_register(IMU660RA_CHIP_ID);
        system_delay_ms(1);
    }while(0x24 != dat);                                                        // 读取设备ID是否等于0X24，如果不是0X24则认为没检测到设备
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取 IMU660RA 加速度计数据
// 参数说明     void
// 返回参数     void
// 使用示例     imu660ra_get_acc();                                             // 执行该函数后，直接查看对应的变量即可
// 备注信息     使用 SPI 的采集时间为69us
//             使用 IIC 的采集时间为126us        采集加速度计的时间与采集陀螺仪的时间一致的原因是都只是读取寄存器数据
//-------------------------------------------------------------------------------------------------------------------
void imu660ra_get_acc (void)
{
    uint8 dat[6];

    imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
    imu660ra_acc_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
    imu660ra_acc_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
    imu660ra_acc_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
}
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取 IMU660RA 陀螺仪数据
// 参数说明     void
// 返回参数     void
// 使用示例     imu660ra_get_gyro();                                            // 执行该函数后，直接查看对应的变量即可
// 备注信息     使用 SPI 的采集时间为69us
//             使用 IIC 的采集时间为126us
//-------------------------------------------------------------------------------------------------------------------
void imu660ra_get_gyro (void)
{
    uint8 dat[6];

    imu660ra_read_registers(IMU660RA_GYRO_ADDRESS, dat, 6);
    imu660ra_gyro_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
    imu660ra_gyro_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
    imu660ra_gyro_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     初始化 IMU660RA
// 参数说明     void
// 返回参数     uint8           1-初始化失败 0-初始化成功
// 使用示例     imu660ra_init();
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint8 imu660ra_init (void)
{
    uint8 return_state = 0;
    system_delay_ms(20);                                                        // 等待设备上电成功
#if IMU660RA_USE_IIC
#if IMU660RA_USE_SOFT_IIC
    soft_iic_init(&imu660ra_iic_struct, IMU660RA_DEV_ADDR, IMU660RA_SOFT_IIC_DELAY, IMU660RA_SCL_PIN, IMU660RA_SDA_PIN);        // 配置 IMU660RA 的 IIC 端口
#else
    iic_init(IMU660RA_IIC_INDEX, IMU660RA_DEV_ADDR, IMU660RA_IIC_SPEED, IMU660RA_SCL_PIN, IMU660RA_SDA_PIN);        // 配置 IMU660RA 的 IIC 端口
#endif
#else
    spi_init(IMU660RA_SPI, SPI_MODE0, IMU660RA_SPI_SPEED, IMU660RA_SPC_PIN, IMU660RA_SDI_PIN, IMU660RA_SDO_PIN, SPI_CS_NULL);   // 配置 IMU660RA 的 SPI 端口
    gpio_init(IMU660RA_CS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);                  // 配置 IMU660RA 的CS端口
    imu660ra_read_register(IMU660RA_CHIP_ID);                                   // 读取一下设备ID 将设备设置为SPI模式
#endif
    do{
        if(imu660ra_self_check())                                               // IMU660RA 自检
        {
            // 如果程序在输出了断言信息 并且提示出错位置在这里
            // 那么就是 IMU660RA 自检出错并超时退出了
            // 检查一下接线有没有问题 如果没问题可能就是坏了
            zf_log(0, "imu660ra self check error.");
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                       // 关闭高级省电模式
        system_delay_ms(1);
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x00);                      // 开始对模块进行初始化配置
        imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));   // 输出配置文件
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x01);                      // 初始化配置结束
        system_delay_ms(20);
        if(1 != imu660ra_read_register(IMU660RA_INT_STA))                       // 检查是否配置完成
        {
            // 如果程序在输出了断言信息 并且提示出错位置在这里
            // 那么就是 IMU660RA 配置初始化文件出错了
            // 检查一下接线有没有问题 如果没问题可能就是坏了
            zf_log(0, "imu660ra init error.");
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CTRL, 0x0E);                       // 开启性能模式  使能陀螺仪、加速度、温度传感器
        imu660ra_write_register(IMU660RA_ACC_CONF, 0xA7);                       // 加速度采集配置 性能模式 正常采集 50Hz  采样频率
        imu660ra_write_register(IMU660RA_GYR_CONF, 0xA9);                       // 陀螺仪采集配置 性能模式 正常采集 200Hz 采样频率

        // IMU660RA_ACC_SAMPLE 寄存器
        // 设置为 0x00 加速度计量程为 ±2  g   获取到的加速度计数据除以 16384  可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        // 设置为 0x01 加速度计量程为 ±4  g   获取到的加速度计数据除以 8192   可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        // 设置为 0x02 加速度计量程为 ±8  g   获取到的加速度计数据除以 4096   可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        // 设置为 0x03 加速度计量程为 ±16 g   获取到的加速度计数据除以 2048   可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        switch(IMU660RA_ACC_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU660RA_ACC_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_2G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x00);
                imu660ra_transition_factor[0] = 16384;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_4G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x01);
                imu660ra_transition_factor[0] = 8192;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_8G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x02);
                imu660ra_transition_factor[0] = 4096;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_16G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x03);
                imu660ra_transition_factor[0] = 2048;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        // IMU660RA_GYR_RANGE 寄存器
        // 设置为 0x04 陀螺仪量程为 ±125  dps    获取到的陀螺仪数据除以 262.4   可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x03 陀螺仪量程为 ±250  dps    获取到的陀螺仪数据除以 131.2   可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x02 陀螺仪量程为 ±500  dps    获取到的陀螺仪数据除以 65.6    可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x01 陀螺仪量程为 ±1000 dps    获取到的陀螺仪数据除以 32.8    可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x00 陀螺仪量程为 ±2000 dps    获取到的陀螺仪数据除以 16.4    可以转化为带物理单位的数据 单位为 °/s
        switch(IMU660RA_GYRO_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU660RA_GYRO_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_125DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x04);
                imu660ra_transition_factor[1] = 262.4;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_250DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x03);
                imu660ra_transition_factor[1] = 131.2;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_500DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x02);
                imu660ra_transition_factor[1] = 65.6;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_1000DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x01);
                imu660ra_transition_factor[1] = 32.8;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_2000DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x00);
                imu660ra_transition_factor[1] = 16.4;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }
    }while(0);
    return return_state;
}


