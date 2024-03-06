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
* 文件名称          zf_device_imu963ra
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
*                   SCL/SPC             查看 zf_device_imu963ra.h 中 IMU963RA_SPC_PIN 宏定义
*                   SDA/DSI             查看 zf_device_imu963ra.h 中 IMU963RA_SDI_PIN 宏定义
*                   SA0/SDO             查看 zf_device_imu963ra.h 中 IMU963RA_SDO_PIN 宏定义
*                   CS                  查看 zf_device_imu963ra.h 中 IMU963RA_CS_PIN  宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*
*                   // 软件 IIC 引脚
*                   SCL/SPC             查看 zf_device_imu963ra.h 中 IMU963RA_SCL_PIN 宏定义
*                   SDA/DSI             查看 zf_device_imu963ra.h 中 IMU963RA_SDA_PIN 宏定义
*                   VCC                 3.3V电源
*                   GND                 电源地
*                   其余引脚悬空
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_delay.h"
#include "zf_driver_spi.h"
#include "zf_driver_soft_iic.h"

#include "zf_device_imu963ra.h"

int16 imu963ra_gyro_x = 0, imu963ra_gyro_y = 0, imu963ra_gyro_z = 0;
int16 imu963ra_acc_x = 0,  imu963ra_acc_y = 0,  imu963ra_acc_z = 0;
int16 imu963ra_mag_x = 0,  imu963ra_mag_y = 0,  imu963ra_mag_z = 0;
float imu963ra_transition_factor[3] = {4098, 14.3, 3000};

#if IMU963RA_USE_SOFT_IIC
static soft_iic_info_struct imu963ra_iic_struct;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 写寄存器
// 参数说明     reg             寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define imu963ra_write_acc_gyro_register(reg,data)       (soft_iic_write_8bit_register(&imu963ra_iic_struct,reg,data))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 读寄存器
// 参数说明     reg             寄存器地址
// 返回参数     uint8           数据
// 使用示例     imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define imu963ra_read_acc_gyro_register(reg)             (soft_iic_sccb_read_register(&imu963ra_iic_struct,reg))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 读数据 内部调用
// 参数说明     reg             寄存器地址
// 参数说明     data            数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, dat, 6);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
#define imu963ra_read_acc_gyro_registers(reg,data,len)   (soft_iic_read_8bit_registers(&imu963ra_iic_struct,reg,data,len))
#else
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 写寄存器
// 参数说明     reg             寄存器地址
// 参数说明     data            数据
// 返回参数     void
// 使用示例     imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_write_acc_gyro_register (uint8 reg, uint8 data)
{
    IMU963RA_CS(0);
    spi_write_8bit_register(IMU963RA_SPI, reg | IMU963RA_SPI_W, data);

    IMU963RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 读寄存器
// 参数说明     reg             寄存器地址
// 返回参数     uint8           数据
// 使用示例     imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_read_acc_gyro_register (uint8 reg)
{
    uint8 data = 0;
    IMU963RA_CS(0);
    data = spi_read_8bit_register(IMU963RA_SPI, reg | IMU963RA_SPI_R);

    IMU963RA_CS(1);
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 读数据 内部调用
// 参数说明     reg             寄存器地址
// 参数说明     data            数据缓冲区
// 参数说明     len             数据长度
// 返回参数     void
// 使用示例     imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, dat, 6);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_read_acc_gyro_registers (uint8 reg, uint8 *data, uint32 len)
{
    IMU963RA_CS(0);
    spi_read_8bit_registers(IMU963RA_SPI, reg | IMU963RA_SPI_R, data, len);

    IMU963RA_CS(1);
}
#endif

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 作为 IIC 主机向磁力计写数据
// 参数说明     addr            目标地址
// 参数说明     reg             目标寄存器
// 参数说明     data            数据
// 返回参数     uint8           1-失败 0-成功
// 使用示例     imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x80);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_write_mag_register (uint8 addr, uint8 reg, uint8 data)
{
    uint8 return_state = 0;
    uint16 timeout_count = 0;

    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);               // 从机0配置清除
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 0);              // 设置地磁计地址（注意这里需要设置8位的I2C地址） 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);                // 需要写入的寄存器地址
    imu963ra_write_acc_gyro_register(IMU963RA_DATAWRITE_SLV0, data);            // 需要写入的数据
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);             // 仅在第一个周期启用通讯 开启上拉 I2C主机使能
    
    // 等待通讯成功
    while(0 == (0x80 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state = 1;
            break;
        }
        system_delay_ms(2);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 作为 IIC 主机向磁力计读数据
// 参数说明     addr            目标地址
// 参数说明     reg             目标寄存器
// 返回参数     uint8           读取的数据
// 使用示例     imu963ra_read_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CHIP_ID);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_read_mag_register (uint8 addr, uint8 reg)
{
    uint16 timeout_count = 0;

    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);              // 设置地磁计地址（注意这里需要设置8位的I2C地址） 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);                // 需要读取的寄存器地址
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x01);    
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);             // 仅在第一个周期启用通讯 开启上拉 I2C主机使能
    
    // 等待通讯成功
    while(0 == (0x01 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            break;
        }
        system_delay_ms(2);
    }
    
    return (imu963ra_read_acc_gyro_register(IMU963RA_SENSOR_HUB_1));            // 返回读取到的数据
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 作为 IIC 主机向磁力计自动写数据
// 参数说明     addr            目标地址
// 参数说明     reg             目标寄存器
// 返回参数     void
// 使用示例     imu963ra_connect_mag(IMU963RA_MAG_ADDR, IMU963RA_MAG_OUTX_L);
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_connect_mag (uint8 addr, uint8 reg)
{
    addr = addr << 1;
    
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);              // 设置地磁计地址（注意这里需要设置8位的I2C地址） 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);                // 需要读取的寄存器地址
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x06);    
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x6C);             // 仅在第一个周期启用通讯 开启上拉 I2C主机使能
}   


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 六轴自检 内部调用
// 参数说明     void
// 返回参数     uint8           1-自检失败 0-自检成功
// 使用示例     imu963ra_acc_gyro_self_check();
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_acc_gyro_self_check (void)
{
    uint8 return_state = 0;
    uint8 dat = 0;
    uint16 timeout_count = 0;

    while(0x6B != dat)                                                          // 判断 ID 是否正确
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state = 1;
            break;
        }
        dat = imu963ra_read_acc_gyro_register(IMU963RA_WHO_AM_I);
        system_delay_ms(10);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     IMU963RA 磁力计自检 内部调用
// 参数说明     void
// 返回参数     uint8           1-自检失败 0-自检成功
// 使用示例     imu963ra_mag_self_check();
// 备注信息     内部调用
//-------------------------------------------------------------------------------------------------------------------
static uint8 imu963ra_mag_self_check (void)
{
    uint8 return_state = 0;
    uint8 dat = 0;
    uint16 timeout_count = 0;

    while(0xff != dat)                                                          // 判断 ID 是否正确
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state = 1;
            break;
        }
        dat = imu963ra_read_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CHIP_ID);
        system_delay_ms(10);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取 IMU963RA 加速度计数据
// 参数说明     void
// 返回参数     void
// 使用示例     imu963ra_get_acc();
// 备注信息     执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_acc (void)
{
    uint8 dat[6];

    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, dat, 6);
    imu963ra_acc_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
    imu963ra_acc_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
    imu963ra_acc_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取IMU963RA陀螺仪数据
// 参数说明     void
// 返回参数     void
// 使用示例     imu963ra_get_gyro();
// 备注信息     执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_gyro (void)
{
    uint8 dat[6];

    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_G, dat, 6);
    imu963ra_gyro_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
    imu963ra_gyro_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
    imu963ra_gyro_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     获取 IMU963RA 磁力计数据
// 参数说明     void
// 返回参数     void
// 使用示例     imu963ra_get_mag();
// 备注信息     执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_mag (void)
{
    uint8 temp_status;
    uint8 dat[6];

    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);
    temp_status = imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
    if(0x01 & temp_status)
    {
        imu963ra_read_acc_gyro_registers(IMU963RA_SENSOR_HUB_1, dat, 6);
        imu963ra_mag_x = (int16)(((uint16)dat[1] << 8 | dat[0]));
        imu963ra_mag_y = (int16)(((uint16)dat[3] << 8 | dat[2]));
        imu963ra_mag_z = (int16)(((uint16)dat[5] << 8 | dat[4]));
    }
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     初始化 IMU963RA
// 参数说明     void
// 返回参数     uint8           1-初始化失败 0-初始化成功
// 使用示例     imu963ra_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
uint8 imu963ra_init (void)
{
    uint8 return_state = 0;
    system_delay_ms(10);                                                        // 上电延时

#if IMU963RA_USE_SOFT_IIC
    soft_iic_init(&imu963ra_iic_struct, IMU963RA_DEV_ADDR, IMU963RA_SOFT_IIC_DELAY, IMU963RA_SCL_PIN, IMU963RA_SDA_PIN);
#else
    spi_init(IMU963RA_SPI, SPI_MODE0, IMU963RA_SPI_SPEED, IMU963RA_SPC_PIN, IMU963RA_SDI_PIN, IMU963RA_SDO_PIN, SPI_CS_NULL);
    gpio_init(IMU963RA_CS_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);
#endif

    do
    {
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);       // 关闭HUB寄存器访问
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x01);               // 复位设备
        system_delay_ms(2);                             
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);       // 关闭HUB寄存器访问
        if(imu963ra_acc_gyro_self_check())                   
        {                   
            zf_log(0, "IMU963RA acc and gyro self check error.");                    
            return_state = 1;
            break;            
        }                   
                            
        imu963ra_write_acc_gyro_register(IMU963RA_INT1_CTRL, 0x03);             // 开启陀螺仪 加速度数据就绪中断

        // IMU963RA_CTRL1_XL 寄存器
        // 设置为 0x30 加速度量程为 ±2  g    获取到的加速度计数据除以 16393  可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        // 设置为 0x38 加速度量程为 ±4  g    获取到的加速度计数据除以 8197   可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        // 设置为 0x3C 加速度量程为 ±8  g    获取到的加速度计数据除以 4098   可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        // 设置为 0x34 加速度量程为 ±16 g    获取到的加速度计数据除以 2049   可以转化为带物理单位的数据 (g 代表重力加速度 物理学名词 一般情况下 g 取 9.8 m/s^2 为标准值)
        switch(IMU963RA_ACC_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU963RA_ACC_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_2G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x30);
                imu963ra_transition_factor[0] = 16393;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_4G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x38);
                imu963ra_transition_factor[0] = 8197;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_8G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x3C);
                imu963ra_transition_factor[0] = 4098;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_16G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x34);
                imu963ra_transition_factor[0] = 2049;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        // IMU963RA_CTRL2_G 寄存器
        // 设置为 0x52 陀螺仪量程为 ±125  dps    获取到的陀螺仪数据除以 228.6   可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x50 陀螺仪量程为 ±250  dps    获取到的陀螺仪数据除以 114.3   可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x54 陀螺仪量程为 ±500  dps    获取到的陀螺仪数据除以 57.1    可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x58 陀螺仪量程为 ±1000 dps    获取到的陀螺仪数据除以 28.6    可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x5C 陀螺仪量程为 ±2000 dps    获取到的陀螺仪数据除以 14.3    可以转化为带物理单位的数据 单位为 °/s
        // 设置为 0x51 陀螺仪量程为 ±4000 dps    获取到的陀螺仪数据除以 7.1     可以转化为带物理单位的数据 单位为 °/s
        switch(IMU963RA_GYRO_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU963RA_GYRO_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_125DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x52);
                imu963ra_transition_factor[1] = 228.6;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_250DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x50);
                imu963ra_transition_factor[1] = 114.3;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_500DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x54);
                imu963ra_transition_factor[1] = 57.1;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_1000DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x58);
                imu963ra_transition_factor[1] = 28.6;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_2000DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x5C);
                imu963ra_transition_factor[1] = 14.3;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_4000DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x51);
                imu963ra_transition_factor[1] = 7.1;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x44);               // 使能陀螺仪数字低通滤波器
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL4_C, 0x02);               // 使能数字低通滤波器
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL5_C, 0x00);               // 加速度计与陀螺仪四舍五入
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL6_C, 0x00);               // 开启加速度计高性能模式 陀螺仪低通滤波 133hz
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL7_G, 0x00);               // 开启陀螺仪高性能模式 关闭高通滤波
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL9_XL, 0x01);              // 关闭I3C接口

        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);       // 开启HUB寄存器访问 用于配置地磁计
        imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x80);         // 复位I2C主机
        system_delay_ms(2);                             
        imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x00);         // 清除复位标志
        system_delay_ms(2);
        
        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x80);// 复位连接的外设
        system_delay_ms(2);
        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x00);
        system_delay_ms(2);

        if(imu963ra_mag_self_check())
        {
            zf_log(0, "IMU963RA mag self check error.");
            return_state = 1;
            break;            
        }

        // IMU963RA_MAG_ADDR 寄存器
        // 设置为 0x09 磁力计量程为 2G   获取到的磁力计数据除以 12000   可以转化为带物理单位的数据 单位 G(高斯)
        // 设置为 0x19 磁力计量程为 8G   获取到的磁力计数据除以 3000    可以转化为带物理单位的数据 单位 G(高斯)
        switch(IMU963RA_MAG_SAMPLE_DEFAULT)
        {
            default:
            {
                zf_log(0, "IMU963RA_MAG_SAMPLE_DEFAULT set error.");
                return_state = 1;
            }break;
            case IMU963RA_MAG_SAMPLE_2G:
            {
                imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x09);
                imu963ra_transition_factor[2] = 12000;
            }break;
            case IMU963RA_MAG_SAMPLE_8G:
            {
                imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x19);
                imu963ra_transition_factor[2] = 3000;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_FBR, 0x01);
        imu963ra_connect_mag(IMU963RA_MAG_ADDR, IMU963RA_MAG_OUTX_L);
        
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);       // 关闭HUB寄存器访问

        system_delay_ms(20);                                                    // 等待磁力计获取数据
    }while(0);
    return return_state;
}
