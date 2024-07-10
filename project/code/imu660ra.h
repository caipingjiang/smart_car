#include "zf_common_headfile.h"
#ifndef _icm660ra_h_
#define _icm660ra_h_

//陀螺仪参数结构体
typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
} gyro_param_t;

extern gyro_param_t Gyro_Bias, Gyro_Angle, Acc_Angle, Fusion_Angle;
void imu660_zeroBias(void);
void my_imu660ra_init();

#endif
