#include "zf_common_headfile.h"
#include "my_moter.h"
#include "imu660ra.h"
#include "my_image.h"
#include <math.h>

#define r_x                 0.089//8.9 //左右两轮轴间距的一半(cm)
#define r_y                  0.1//10  //前后两轮轴间距的一半(cm)

float angle_now = 0;    //进入环岛十字时的角度
float angle_turn = 0;   //需要转的角度
uint8 turn_flag = 0;    //转向完成标志位（用于环岛十字的转向）
uint8 Control_Mode = 0;     //0-正常循迹， 1-边界矫正
float Inc_Kp[4]={45, 45, 45, 45};//10//6.5/100
float Inc_Ki[4]={5.5, 5.5, 5.5, 5.5};//0/64/4.8
float Inc_Kd[4]={0, 0, 0, 0};//1.1
int16 v_w[4]={0};       //四个轮子的转速
int16 v_x=0, v_y=30, w=0;  //x、 y轴分速度,车绕几何中心的角速度
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
	duty = func_limit(duty, 8000);
    if(duty >= 0)   //正转
    {
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_HIGH); pwm_set_duty(MOTOR1_PWM, (uint32_t)duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_HIGH); pwm_set_duty(MOTOR2_PWM, (uint32_t)duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_LOW); pwm_set_duty(MOTOR3_PWM, (uint32_t)duty);} //gpio_set_level(MOTOR3_DIR, GPIO_LOW); pwm_set_duty(MOTOR3_PWM, (uint32_t)duty);
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_LOW); pwm_set_duty(MOTOR4_PWM, (uint32_t)duty);} //gpio_set_level(MOTOR4_DIR, GPIO_LOW); pwm_set_duty(MOTOR4_PWM, (uint32_t)duty);
    }
    else           //反转
    {
		int16 abs_duty = -duty;
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_LOW); pwm_set_duty(MOTOR1_PWM, (uint32_t)abs_duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_LOW); pwm_set_duty(MOTOR2_PWM, (uint32_t)abs_duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)abs_duty);}//gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)abs_duty);
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)abs_duty);}//gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)abs_duty);
    }   
}

//增量式PI速度环
int16 Incremental_PI (uint8 motor_num, int16 Encoder, int16 Target)
{ 		
    int16 bias = Target - Encoder ;
	Pwm[motor_num-1] += ( Inc_Kp[motor_num-1]*(bias-motor_bias_last[motor_num-1]) 
                        + Inc_Ki[motor_num-1]*bias
                        + Inc_Kd[motor_num-1]*(bias-2*motor_bias_last[motor_num-1] + motor_bias_last2[motor_num-1] ));
    motor_bias_last2[motor_num-1] = motor_bias_last[motor_num-1];
    motor_bias_last[motor_num-1] = bias;
    
    //积分限幅
    if(Pwm[motor_num-1]> 8000)Pwm[motor_num-1]= 8000;
    if(Pwm[motor_num-1]<-8000)Pwm[motor_num-1]=-8000;
	
    return (int16)Pwm[motor_num-1];
}

//-----------------------------------------------------------------------------------------------
// 函数简介  麦克纳姆轮解算
// 参数说明  v_x: x方向的速度
// 参数说明  v_y: y方向的速度
// 参数说明  w:   车身角速度
// 返回参数  void
// 使用示例  
// 备注信息  将v_x, v_y,w这三个参数传入即可解算出四个轮子的转速
//-----------------------------------------------------------------------------------------------		                                  
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
    v_y = 0;
    w = 20;
	car_omni(v_x, v_y, w);
}

//-----------------------------------------------------------------------------------------------
// 函数简介  循迹转向函数
// 参数说明  Target_slope：目标斜率
// 参数说明  actual_slope：实际斜率
// 返回参数  void
// 使用示例  
// 备注信息  通过总钻风计算的斜率传入此函数来计算转向值，从而循迹
//-----------------------------------------------------------------------------------------------
float Kp_T=2.0, Kd_T=15; //2.6， 1.5
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

//-----------------------------------------------------------------------------------------------
// 函数简介  到环岛和十字时的横向移动
// 参数说明  sideline_angle:边线倾角误差
// 参数说明  sideline_distance:边线距离误差
// 返回参数  void
// 使用示例  roundabout_move(&sideline_angle, &sideline_distance);
// 备注信息  注意参数为存放数据变量的地址，在调用时传入在my_iamge.c中的全局变量int16 sideline_angle,sideline_distance的地址即可
//-----------------------------------------------------------------------------------------------
float Kp_correct1=1, Kd_correct1=10; //0.5 0.2 //1 10
float Kp_correct2=0.07, Kd_correct2=0.4;
static int16 out1, out2;
void roundabout_move(int16* sideline_angle,  int16* sideline_distance)
{
    //使用两个并级PID，第一个：车身倾斜角度修正， 第二个：车身与正前方赛道边界距离修正
    static int16 err1=0, err_last1=0, err2 = 0, err_last2=0;
    
    //车身倾角矫正pid
    err1 = *sideline_angle;
    out1 =Kp_correct1*err1 + Kd_correct1*(err1-err_last1);
	err_last1 = err1;
    out1 = func_limit(out1, 200); //限幅

    //赛道边线距离矫正pid
    err2 = (450-*sideline_distance); //目标距离为500个像素点（使用了多个点之和）
    out2 =Kp_correct2*err2 + Kd_correct2*(err2-err_last2);
    err_last2 = err2;
    out2 = func_limit(out2, 400); //限幅
}

//-----------------------------------------------------------------------------------------------
// 函数简介  角度环（外环pid）
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  计算出的输出值可直接传给w, 也可以传入内环角速度环，后一种目前效果不是很好，可能是因为内外环中期一样的原因；目前直接用的外环
// 备注信息  串级PID外环一般一个P就行(加i会降低响应速度,加d会放大噪音)
//-----------------------------------------------------------------------------------------------
float Kp_A=1.25,Kd_A=8,Ki_A=0; // 20/95/0
float Angle_PID(float Target_Angle, float Angle)
{	
	//Angle = slidingFilter(Angle);
	float err = Target_Angle - Angle;
	static float last_err, integral;
	float out = Kp_A*err +Kd_A*(err - last_err) + Ki_A*integral;
	last_err = err;
	integral += err;
	integral = func_limit(integral,100); //积分限幅
	//return (out>=0) ? (8*sqrt(out)) : (-8*sqrt(func_abs(out)));
	return 2*out;
}

//-----------------------------------------------------------------------------------------------
// 函数简介  角速度环（内环）
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  目前闲置没有用，理论上可以作为串级pid,将角度环的输出值作为角速度环的输入值
//-----------------------------------------------------------------------------------------------
float Kp_w=5.45,Kd_w=0,Ki_w=0.125;//0.005;
float out_w=0, err_w,last_err_w, last_err_w2;
float w_PID(float Target_w, float w)
{
	//w = slidingFilter(w);
	err_w = Target_w - w;
	out_w += (Kp_w*(err_w-last_err_w) + Kd_w*(err_w-2*last_err_w+last_err_w2) + Ki_w*err_w);
	last_err_w2 = last_err_w;
	last_err_w = err_w;
	out_w = func_limit(out_w,400); //限幅
    return out_w;
}

//-----------------------------------------------------------------------------------------------
// 函数简介  电机控制函数，放在编码器采集中断中被调用
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  编码器中断函数里周期性调用此函数
//-----------------------------------------------------------------------------------------------
void motor_control()
{
    if(Control_Mode == 0)Turn(0,Slope);     //正常循迹模式
    else if(Control_Mode == 1)              //边界矫正模式
    {
        roundabout_move(&sideline_angle, &sideline_distance);
<<<<<<< HEAD
=======
        v_y = out2;
        //v_x = 20;
        w = out1;
>>>>>>> 770f3a423882e11769e9692f6e107c6e6bc8379b
        //w = Angle_PID(Target_Speed, angle);
        //car_omni(20, out2, out1);
    }
    else if(Control_Mode == 2)              //卡片矫正模式
    {

    }
    else if(Control_Mode == 3)              //陀螺仪转向模式
    {

        
        //w = (int16)w_PID(Angle_PID(angle_now, Gyro_Angle.Zdata), tra_gyro_z);
        //w = (int16)w_PID(20, tra_gyro_z);
        w = Angle_PID(angle_now + angle_turn, Gyro_Angle.Zdata);
    }
	else if(Control_Mode == 4)              //等待模式
    {
        
    }
    car_omni(v_x, v_y, w);
    motor_set_duty(1, Incremental_PI(1,encoder_data[0],v_w[0]));
    motor_set_duty(2, Incremental_PI(2,encoder_data[1],v_w[1]));
    motor_set_duty(3, Incremental_PI(3,encoder_data[2],v_w[2]));
    motor_set_duty(4, Incremental_PI(4,encoder_data[3],v_w[3]));
}

