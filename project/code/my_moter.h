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
void forward();
void move(int16 angle, int8 speed);
float w_PID(float Target_w, float w);
void position_correct(uint8 correct_mode);

extern uint8 Control_Mode;   //0-正常循迹， 1-边界矫正,2卡片矫正模式,3陀螺仪转向，4等待模式
extern uint8 Correct_Mode;  //卡片矫正模式
extern int16 tracking_speed;
extern int16 last_speed_y;
extern float angle_now;
extern float angle_turn;
extern float target_angle;
extern float target_slope;
extern uint8 turn_flag;
extern int16 finial_point_1[2];
extern int16 finial_point_2[2];

#endif 
