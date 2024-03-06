#include "zf_common_headfile.h"
#ifndef _icm660ra_h_
#define _icm660ra_h_

typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
} gyro_zero_param_t;


extern gyro_zero_param_t Gyro_Bias;


void imu660_zeroBias(void);
float slidingFilter(float newData);


#endif
