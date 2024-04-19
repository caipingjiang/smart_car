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
* 文件名称          zf_common_headfile
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

#ifndef _zf_common_headfile_h_
#define _zf_common_headfile_h_

#include "stdio.h"
#include "stdint.h"
#include "string.h"

//===================================================芯片 SDK 底层===================================================
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_iomuxc.h"
#include "fsl_cache.h"
#include "fsl_csi.h"


//===================================================芯片 SDK 底层===================================================

//====================================================开源库公共层====================================================
#include "zf_common_typedef.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_common_interrupt.h"
#include "zf_common_vector.h"
//====================================================开源库公共层====================================================

//===================================================芯片外设驱动层===================================================
#include "zf_driver_adc.h"
#include "zf_driver_delay.h"
#include "zf_driver_encoder.h"
#include "zf_driver_exti.h"
#include "zf_driver_flash.h"
#include "zf_driver_gpio.h"
#include "zf_driver_iic.h"
#include "zf_driver_pit.h"
#include "zf_driver_pwm.h"
#include "zf_driver_sdio.h"
#include "zf_driver_soft_iic.h"
#include "zf_driver_soft_spi.h"
#include "zf_driver_spi.h"
#include "zf_driver_timer.h"
#include "zf_driver_uart.h"
#include "zf_driver_csi.h"
#include "zf_driver_romapi.h"
#include "zf_driver_flexio_csi.h"
#include "zf_driver_usb_cdc.h"
//===================================================芯片外设驱动层===================================================

//===================================================外接设备驱动层===================================================
#include "zf_device_absolute_encoder.h"
#include "zf_device_bluetooth_ch9141.h"
#include "zf_device_camera.h"
#include "zf_device_gps_tau1201.h"
#include "zf_device_icm20602.h"
#include "zf_device_imu963ra.h"
#include "zf_device_ips114.h"
#include "zf_device_ips200.h"
#include "zf_device_key.h"
#include "zf_device_mpu6050.h"
#include "zf_device_oled.h"
#include "zf_device_mt9v03x.h"
#include "zf_device_mt9v03x_flexio.h"
#include "zf_device_ov7725.h"
#include "zf_device_scc8660.h"
#include "zf_device_scc8660_flexio.h"
#include "zf_device_tft180.h"
#include "zf_device_tsl1401.h"
#include "zf_device_type.h"
#include "zf_device_virtual_oscilloscope.h"
#include "zf_device_wifi_uart.h"
#include "zf_device_wireless_uart.h"
#include "zf_device_imu660ra.h"
#include "zf_device_dl1a.h"
#include "zf_device_dl1b.h"
#include "zf_device_wifi_spi.h"
#include "zf_device_detector.h"
//===================================================外接设备驱动层===================================================

//===================================================应用组件层===================================================
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"
//===================================================应用组件层===================================================



//===================================================用户自定义文件===================================================
//RT-Thread headfile
#include "rtthread.h"

#include "my_moter.h"
#include "my_encoder.h"
#include "vofa.h"

//编码器相关
extern int16 encoder_data[4];
extern int16 encoder_data_last[4];

//电机&运动 相关
extern int16 bias;
extern int16 motor_bias_last[4];
extern int16 motor_bias_last2[4];
extern int16 Pwm[4];
extern float Inc_Kp[4];
extern float Inc_Ki[4];
extern float Inc_Kd[4];

//全向运动
extern int16 v_x, v_y;
extern int16 Target_Speed;
extern float Kp_correct1, Kd_correct1, Kp_correct2, Kd_correct2; 

//图像相关
extern int16 Slope;
extern float Kp_T, Kd_T;
extern uint8 t_b, k;
extern uint8 image_changed[MT9V03X_H - 2][MT9V03X_W - 2];
extern uint8 y_threshold, x_threshold;
extern int16 sideline_err, sideline_distance;

//陀螺仪相关
extern float angle;
extern float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;
extern int16 w;
extern float Kp_w,Kd_w,Ki_w;
extern float out_w, err_w,last_err_w, last_err_w2;
void imu660_zeroBias(void);
extern float Kp_A,Kd_A,Ki_A;



//===================================================用户自定义文件===================================================

#endif
