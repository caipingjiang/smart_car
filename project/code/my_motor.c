#include "zf_common_headfile.h"
#include "my_motor.h"
#include "imu660ra.h"
#include "my_image.h"
#include <math.h>


#define r_x                 0.089//8.9 //左右两轮轴间距的一半(cm)
#define r_y                  0.1//10  //前后两轮轴间距的一半(cm)

uint32 set_time_ms = 0; //设定的计时器时间
bool CHECK_TIMER_ENABLE = false;    //检查计时器计数值是否使能neg
bool SPEED_ENABLE = false;  //速度使能,默认关闭，故刚启动时需要手动按键才会使能运动
float angle_now = 0;    //进入环岛十字时的角度
float angle_turn = 0;   //需要转的角度
float target_angle = 0; //设定的角度值
float target_slope  = 0;  //目标斜率
int16 tracking_speed = 40;//60;  //循迹速度
int16 last_speed_y = 40;    //上次的v_y
int16 speed_offset = 10;    //速度偏移量
uint8 Control_Mode = 0;     //0-正常循迹， 1-边界矫正,2卡片矫正模式,3陀螺仪转向，4等待模式， 5赛道两边的边界矫正，6角度闭环模式
uint8 Correct_Mode = 0;     //卡片矫正模式，0-拾取卡片矫正，1-放卡片矫正
uint8 turn_flag = 0;    //转向完成标志位（用于环岛十字的转向）

float Inc_Kp[4]={45, 45, 45, 45};//10//6.5/100
float Inc_Ki[4]={5.5, 5.5, 5.5, 5.5};//0/64/4.8
float Inc_Kd[4]={0, 0, 0, 0};//1.1
int16 v_w[4]={0};       //四个轮子的转速
int16 v_x = 0, v_y = 40, w = 0;  //x、 y轴分速度,车绕几何中心的角速度
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
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_LOW); pwm_set_duty(MOTOR1_PWM, (uint32_t)-duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_LOW); pwm_set_duty(MOTOR2_PWM, (uint32_t)-duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)-duty);}//gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)abs_duty);
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)-duty);}//gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)abs_duty);
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
float Kp_T=2.5, Kd_T=15; //2.6， 1.5
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
    w = 0;
}

//-----------------------------------------------------------------------------------------------
// 函数简介  到环岛和十字时的横向移动
// 参数说明  sideline_angle:边线倾角误差
// 参数说明  sideline_distance:边线距离误差
// 返回参数  void
// 使用示例  roundabout_move(&sideline_angle, &sideline_distance);
// 备注信息  注意参数为存放数据变量的地址，在调用时传入在my_iamge.c中的全局变量int16 sideline_angle,sideline_distance的地址即可
//-----------------------------------------------------------------------------------------------
float Kp_correct1=1.0, Kd_correct1=10; //0.5 0.2 //1 10
float Kp_correct2=0.12, Kd_correct2=0.4;    //Kp = 0.07 kd = 0.4
static int16 out1, out2;
int16 target_y = 430;   //边线距离矫正的目标值
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
    err2 = (target_y-*sideline_distance); //目标距离为500个像素点（使用了多个点之和）//450 400   430
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
float Kp_A=2-0.2,Kd_A=8,Ki_A=0; // 20/95/0  Kp_A = 1.25,Kd_A = 8
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
	out = func_limit(out,100);   //70
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
// 函数简介  利用MCX发送的坐标进行车身位置矫正
// 参数说明  correct_mode:矫正模式， 0--拣卡片时的矫正， 1--放卡片时的矫正
// 返回参数  void
// 使用示例  
// 备注信息  {120, 125}放置区位置; {160, 170}捡卡片位置	
//-----------------------------------------------------------------------------------------------
int16 finial_point_1[2]  = {160, 170+10};
int16 finial_point_2[2] = {140, 135+10}; //120,125
float Kp_cor = 0.25;
float Kd_cor = 0; 
void position_correct(uint8 correct_mode)
{
    if(correct_mode == 0)       //拣卡片矫正
    {
        if(uart1_data_arr[0] != 0 && uart1_data_arr[1] != 0)
        {
            v_x = (uart1_data_arr[0] - finial_point_1[0])*0.25;
            v_y = -(uart1_data_arr[1] - finial_point_1[1])*0.25;
            w = 0;
        }
        else
        {
            v_x = 0;
            v_y = 0;
            w = 0;
        }
        
    }
	else if (correct_mode == 1)  //放卡片矫正 
    {
        if(uart1_data_arr[0] != 0 && uart1_data_arr[1] != 0)
        {
            v_x = (uart1_data_arr[0] - finial_point_2[0])*0.25;
            v_y = -(uart1_data_arr[1] - finial_point_2[1])*0.25;
            w = 0;
        }
        else
        {
            v_x = 0;
            v_y = 0;
            w = 0;
        }
    }
    else if(correct_mode == 2)  //带pid的矫正(弃用)
    {
        static int16 err_x = 0, last_err_x = 0;
        static int16 err_y = 0, last_err_y = 0;
        if(uart1_data_arr[0] != 0 && uart1_data_arr[1] != 0)
        {
            err_x = (uart1_data_arr[0] - finial_point_1[0]);
            err_y = -(uart1_data_arr[1] - finial_point_1[1]);

            v_x = Kp_cor*err_x + Kd_cor*(err_x - last_err_x);
            v_y = Kp_cor*err_y + Kd_cor*(err_y - last_err_y);

            last_err_x = err_x;
            last_err_y = err_y;
        }
        else
        {
            v_x = 0;
            v_y = 0;
            w = 0;
        } 
        
    }
    
}

//-----------------------------------------------------------------------------------------------
// 函数简介  将车身矫正至赛道中央，v_y = 0
// 参数说明  middle_line ：中线
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------

void middle_correct(uint8* middle_line)
{
    int16 sum = 0;
    for(uint8 i = 0; i < 20; i++)
    {
        sum += (middle_line[MT9V03X_H-6-i] - middle);
    }
    v_x = sum/15;
    w = sum/10;
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
	static uint8 cnt = 0;

    switch(Control_Mode)
    {
        case 0:                         //正常循迹模式
            Turn(target_slope,Slope);               
            break;
        case 1:                         //边界矫正模式
            roundabout_move(&sideline_angle, &sideline_distance);
            v_y = out2;
            //v_x = 20;
            w = out1;
            //w = Angle_PID(Target_Speed, angle);
            break;
        case 2:                         //卡片矫正模式
            position_correct(Correct_Mode);          
            break;
        case 3:                         //陀螺仪转向模式
            //w = (int16)w_PID(Angle_PID(angle_now, Gyro_Angle.Zdata), tra_gyro_z);
            //w = (int16)w_PID(20, tra_gyro_z);
            // if(angle_now>360)angle_now -= 360;
            // else if (angle_now<-360)angle_now += 360;
            w = Angle_PID(angle_now + angle_turn, Gyro_Angle.Zdata);
            break;
	    case 4:                         //等待模式
            break;
        case 5:   //赛道两边识别到卡片，但转弯后未找到卡片，开启边界矫正直到找到卡片
            roundabout_move(&sideline_angle, &sideline_distance);
            if(uart1_data_arr[0])
            {
                v_x = (uart1_data_arr[0] - finial_point_2[0])*0.25;
            }
            else
            {
                v_x = 0;
            }
            
            v_y = out2;
            w = out1;
            break;
        case 6://   角度闭环模式，此模式角度会保持角度为目标角度
            w = Angle_PID(target_angle, Gyro_Angle.Zdata);
            break;
        case 7: //固定速度循迹
            Turn(target_slope,Slope);
            break;
        case 8:
            middle_correct(boder_M);
            break;
    }
    
    if(Control_Mode == 0)
    {
        
        tracking_speed = 1700/(40+abs(Slope));//v_y = 2700/(50+abs(Slope));//2000/(34+abs(Slope));//2310/(45+abs(Slope));//
        v_y = 0.7*tracking_speed + 0.3*last_speed_y + speed_offset;//0.3*v_y + 0.7*last_speed_y;
        
        //last_speed_y = v_y;
        // tracking_speed = v_y;
        // v_y = tracking_speed;
    }

    car_omni(v_x, v_y, w);
    if(SPEED_ENABLE)
    {
        motor_set_duty(1, Incremental_PI(1,encoder_data[0],v_w[0]));
        motor_set_duty(2, Incremental_PI(2,encoder_data[1],v_w[1]));
        motor_set_duty(3, Incremental_PI(3,encoder_data[2],v_w[2]));
        motor_set_duty(4, Incremental_PI(4,encoder_data[3],v_w[3]));
    }
    
}

