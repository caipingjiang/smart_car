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
* �ļ�����          zf_common_headfile
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

#ifndef _zf_common_headfile_h_
#define _zf_common_headfile_h_

#include "stdio.h"
#include "stdint.h"
#include "string.h"

//===================================================оƬ SDK �ײ�===================================================
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_iomuxc.h"
#include "fsl_cache.h"
#include "fsl_csi.h"


//===================================================оƬ SDK �ײ�===================================================

//====================================================��Դ�⹫����====================================================
#include "zf_common_typedef.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"
#include "zf_common_font.h"
#include "zf_common_function.h"
#include "zf_common_interrupt.h"
#include "zf_common_vector.h"
//====================================================��Դ�⹫����====================================================

//===================================================оƬ����������===================================================
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
//===================================================оƬ����������===================================================

//===================================================����豸������===================================================
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
//===================================================����豸������===================================================

//===================================================Ӧ�������===================================================
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"
//===================================================Ӧ�������===================================================



//===================================================�û��Զ����ļ�===================================================
//RT-Thread headfile
#include "rtthread.h"

#include "my_moter.h"
#include "my_encoder.h"
#include "vofa.h"

//���������
extern int16 encoder_data[4];
extern int16 encoder_data_last[4];

//���&�˶� ���
extern int16 bias;
extern int16 motor_bias_last[4];
extern int16 motor_bias_last2[4];
extern int16 Pwm[4];
extern float Inc_Kp[4];
extern float Inc_Ki[4];
extern float Inc_Kd[4];

//ȫ���˶�
extern int16 v_x, v_y;
extern int16 Target_Speed;
extern float Kp_correct1, Kd_correct1, Kp_correct2, Kd_correct2; 

//ͼ�����
extern int16 Slope;
extern float Kp_T, Kd_T;
extern uint8 t_b, k;
extern uint8 image_changed[MT9V03X_H - 2][MT9V03X_W - 2];
extern uint8 y_threshold, x_threshold;
extern int16 sideline_err, sideline_distance;

//���������
extern float angle;
extern float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;
extern int16 w;
extern float Kp_w,Kd_w,Ki_w;
extern float out_w, err_w,last_err_w, last_err_w2;
void imu660_zeroBias(void);
extern float Kp_A,Kd_A,Ki_A;



//===================================================�û��Զ����ļ�===================================================

#endif
