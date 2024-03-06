#ifndef __MY_MOTOR_H__
#define __MY_MOTOR_H__

#include "zf_common_headfile.h"
//#define MAX_DUTY                 (100 )                                               // ÊúÄÂ§? MAX_DUTY% Âç†Á©∫ÊØ?
#define MOTOR1_DIR               C7//(D0 )
#define MOTOR1_PWM               PWM2_MODULE0_CHA_C6//(PWM2_MODULE3_CHA_D2)

#define MOTOR2_DIR               C9//(D1 )
#define MOTOR2_PWM               PWM2_MODULE1_CHA_C8//(PWM2_MODULE3_CHB_D3)

#define MOTOR3_DIR               D2//(D15 )
#define MOTOR3_PWM               PWM2_MODULE3_CHB_D3//(PWM1_MODULE0_CHB_D13)

#define MOTOR4_DIR               C10//(D14 )
#define MOTOR4_PWM               PWM2_MODULE2_CHB_C11//(PWM1_MODULE0_CHA_D12)


void my_motor_init();
void motor_set_duty(uint8 motor_num, int32 duty);
void motor_control();
int16 Incremental_PI (uint8 motor_num, int16 Encoder, int16 Target);
void Turn_Left();

float w_PID(float Target_w, float w);

#endif 
