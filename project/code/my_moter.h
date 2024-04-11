#ifndef __MY_MOTOR_H__
#define __MY_MOTOR_H__

#include "zf_common_headfile.h"
//#define MAX_DUTY                 (100 )                                               // ???? MAX_DUTY% ?????

//若更换板子，需要改的地方：1.电机信号引脚； 2编码器的引脚， 同时不要忘了编码器的模块
//另外若更换小车， 则motor.c中pwm设置高低电平
#define MOTOR1_DIR               (D0 )//C7//
#define MOTOR1_PWM               (PWM2_MODULE3_CHA_D2)//PWM2_MODULE0_CHA_C6//

#define MOTOR2_DIR               (D1 )//C9//
#define MOTOR2_PWM               (PWM2_MODULE3_CHB_D3)//PWM2_MODULE1_CHA_C8//

#define MOTOR3_DIR               (D15)//D2//
#define MOTOR3_PWM               (PWM1_MODULE0_CHB_D13)//PWM2_MODULE3_CHB_D3

#define MOTOR4_DIR              	(D14 )//C10//
#define MOTOR4_PWM               (PWM1_MODULE0_CHA_D12)//PWM2_MODULE2_CHB_C11//


void my_motor_init();
void motor_set_duty(uint8 motor_num, int16 duty);
void motor_control();
int16 Incremental_PI (uint8 motor_num, int16 Encoder, int16 Target);
void Turn_Left();
void move(int16 angle, int8 speed);

float w_PID(float Target_w, float w);

#endif 
