#include "zf_common_headfile.h"
#include "my_moter.h"
#include "imu660ra.h"
#include <math.h>
#define r_x                 0.089//8.9 //左右两轮轴间距的一半(cm)
#define r_y                  0.1//10  //前后两轮轴间距的一半(cm)

float Inc_Kp[4]={6.5, 6.5, 6.5, 6.5};//10
float Inc_Ki[4]={0.65, 0.65, 0.65, 0.65};
float Inc_Kd[4]={0, 0, 0, 0};//1.1
int16 v_w[4]={0};       //四个轮子的转速
int16 v_x=0, v_y=40, w=0;  //x、 y轴分速度,车绕几何中心的角速度
int16 Pwm[4]={0};
int16 bias;
int16 motor_bias_last[4];
int16 motor_bias_last2[4];
void my_motor_init()
{
    gpio_init(MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(MOTOR3_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR3_PWM, 17000, 0);                                                  // PWM 通道初始化频率 17KHz 占空比初始为 0

    gpio_init(MOTOR4_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO 初始化为输出 默认上拉输出高
    pwm_init(MOTOR4_PWM, 17000, 0); 
}

void motor_set_duty(uint8 motor_num, int16 duty)
{
	//ips114_show_int(40,40,duty,5);
	duty = func_limit(duty, 5000);
    if(duty >= 0)   //正转
    {
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_LOW); pwm_set_duty(MOTOR1_PWM, (uint32_t)duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_LOW); pwm_set_duty(MOTOR2_PWM, (uint32_t)duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_LOW); pwm_set_duty(MOTOR3_PWM, (uint32_t)duty);}
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_LOW); pwm_set_duty(MOTOR4_PWM, (uint32_t)duty);}
    }
    else           //反转
    {
		int16 abs_duty = -duty;
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_HIGH); pwm_set_duty(MOTOR1_PWM, (uint32_t)abs_duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_HIGH); pwm_set_duty(MOTOR2_PWM, (uint32_t)abs_duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)abs_duty);}
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)abs_duty);}
    }   
}

void car_omni(int16 v_x, int16 v_y, int16 w);

//增量式PI速度环

int16 Incremental_PI (uint8 motor_num, int16 Encoder, int16 Target)
{ 		
    int16 bias = Target - Encoder ;
	Pwm[motor_num-1] += ( Inc_Kp[motor_num-1]*(bias-motor_bias_last[motor_num-1]) 
                        + Inc_Ki[motor_num-1]*bias
                        + Inc_Kd[motor_num-1]*(bias-2*motor_bias_last[motor_num-1]) + motor_bias_last2[motor_num-1] );
    motor_bias_last2[motor_num-1] = motor_bias_last[motor_num-1];
    motor_bias_last[motor_num-1] = bias;
    
    //积分限幅
    if(Pwm[motor_num-1]> 8000)Pwm[motor_num-1]= 8000;
    if(Pwm[motor_num-1]<-8000)Pwm[motor_num-1]=-8000;
	
    return (int16)Pwm[motor_num-1];
}
		                                  
void car_omni(int16 v_x, int16 v_y, int16 w)
{
    v_w[0] = v_y - v_x + w*(r_x + r_y);
    v_w[1] = v_y + v_x - w*(r_x + r_y);
    v_w[2] = v_y - v_x - w*(r_x + r_y);
    v_w[3] = v_y + v_x + w*(r_x + r_y);
}

void Turn_Left()
{
    v_x = 0;
    v_y = 7;
    w = 20;
	car_omni(v_x, v_y, w);
}

float Kp_T=2.6, Kd_T=15;
void Turn(float Target_slope, float actual_slope)
{
	static float err, err_last;
	err = Target_slope - actual_slope;
    w = Kp_T*err + Kd_T*(err - err_last);
	err_last = err;
	car_omni(v_x, v_y, w);
}
void forward()
{
	v_x = 0;
    v_y = 20;
    w = 0;
	car_omni(v_x, v_y, w);
}
void backward()
{
	v_x = 0;
    v_y = -20;
    w = 0;
	car_omni(v_x, v_y, w);
}
void move(int16 angle, int8 speed)
{
    v_x = speed*cos(angle*3.14/180);
    v_y = speed*sin(angle*3.14/180);
}

void roundabout_move(int16 sideline_err,  int16 sideline_distance)
{
    
}

//角度环---外环    串级PID外环一般一个P就行(加i会降低响应速度,加d会放大噪音)
float Kp_A=20,Kd_A=95,Ki_A=0;
float Angle_PID(float Target_Angle, float Angle)
{	
	Angle = slidingFilter(Angle);
	float err = Target_Angle - Angle;
	static float last_err, integral;
	float out = Kp_A*err +Kd_A*(err - last_err) + Ki_A*integral;
	last_err = err;
	integral += err;
	integral = func_limit(integral,100); //积分限幅
	//return (out>=0) ? (8*sqrt(out)) : (-8*sqrt(func_abs(out)));
	return 2*out;
}

float Kp_w=5.45,Kd_w=0,Ki_w=0.125;//0.005;
float out_w=0, err_w,last_err_w, last_err_w2;

//角速度环---内环
char da[18];
float w_PID(float Target_w, float w)
{
	//w = slidingFilter(w);
	err_w = Target_w - w;
	out_w += (Kp_w*(err_w-last_err_w) + Kd_w*(err_w-2*last_err_w+last_err_w2) + Ki_w*err_w);
	last_err_w2 = last_err_w;
	last_err_w = err_w;
	
	out_w = func_limit(out_w,400); //限幅
//	sprintf(da, "%f", out_w);
//	wireless_uart_send_string(da);
//	wireless_uart_send_string("\n");
    return out_w;
}
extern int16 control_flag;
void motor_control()
{
    if(control_flag == 0)Turn(0,Slope);
	
	//w = (int16)w_PID(Angle_PID(Target_Speed, angle), tra_gyro_z);
    //w = (int16)w_PID(20, tra_gyro_z);

	car_omni(v_x, v_y, w);
    motor_set_duty(1, Incremental_PI(1,encoder_data[0],v_w[0]));
    motor_set_duty(2, Incremental_PI(2,encoder_data[1],v_w[1]));
    motor_set_duty(3, Incremental_PI(3,encoder_data[2],v_w[2]));
    motor_set_duty(4, Incremental_PI(4,encoder_data[3],v_w[3]));
	
}
