#include "zf_common_headfile.h"
#ifndef _icm660ra_h_
#define _icm660ra_h_

typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
} gyro_zero_param_t;


extern gyro_zero_param_t Gyro_Bias, Gyro_Angle;

void imu660_zeroBias(void);
void my_imu660ra_init();

#endif
