#include "zf_common_headfile.h"
#include "my_motor.h"
#include "imu660ra.h"
#include "my_image.h"
#include <math.h>


#define r_x                 0.089//8.9 //�������������һ��(cm)
#define r_y                  0.1//10  //ǰ�����������һ��(cm)

uint32 set_time_ms = 0; //�趨�ļ�ʱ��ʱ��
bool CHECK_TIMER_ENABLE = false;    //����ʱ������ֵ�Ƿ�ʹ��neg
bool SPEED_ENABLE = false;  //�ٶ�ʹ��,Ĭ�Ϲرգ��ʸ�����ʱ��Ҫ�ֶ������Ż�ʹ���˶�
float angle_now = 0;    //���뻷��ʮ��ʱ�ĽǶ�
float angle_turn = 0;   //��Ҫת�ĽǶ�
float target_angle = 0; //�趨�ĽǶ�ֵ
float target_slope  = 0;  //Ŀ��б��
int16 tracking_speed = 40;//60;  //ѭ���ٶ�
int16 last_speed_y = 40;    //�ϴε�v_y
int16 speed_offset = 10;    //�ٶ�ƫ����
uint8 Control_Mode = 0;     //0-����ѭ���� 1-�߽����,2��Ƭ����ģʽ,3������ת��4�ȴ�ģʽ�� 5�������ߵı߽������6�Ƕȱջ�ģʽ
uint8 Correct_Mode = 0;     //��Ƭ����ģʽ��0-ʰȡ��Ƭ������1-�ſ�Ƭ����
uint8 turn_flag = 0;    //ת����ɱ�־λ�����ڻ���ʮ�ֵ�ת��

float Inc_Kp[4]={45, 45, 45, 45};//10//6.5/100
float Inc_Ki[4]={5.5, 5.5, 5.5, 5.5};//0/64/4.8
float Inc_Kd[4]={0, 0, 0, 0};//1.1
int16 v_w[4]={0};       //�ĸ����ӵ�ת��
int16 v_x = 0, v_y = 40, w = 0;  //x�� y����ٶ�,���Ƽ������ĵĽ��ٶ�
int16 Pwm[4]={0};
int16 bias;
int16 motor_bias_last[4];
int16 motor_bias_last2[4];

void my_motor_init()
{
    gpio_init(MOTOR1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR1_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0
    
    gpio_init(MOTOR2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR2_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

    gpio_init(MOTOR3_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR3_PWM, 17000, 0);                                                  // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0

    gpio_init(MOTOR4_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);                            // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(MOTOR4_PWM, 17000, 0); 
}

void motor_set_duty(uint8 motor_num, int16 duty)
{
	//ips114_show_int(40,40,duty,5);
	duty = func_limit(duty, 8000);
    if(duty >= 0)   //��ת
    {
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_HIGH); pwm_set_duty(MOTOR1_PWM, (uint32_t)duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_HIGH); pwm_set_duty(MOTOR2_PWM, (uint32_t)duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_LOW); pwm_set_duty(MOTOR3_PWM, (uint32_t)duty);} //gpio_set_level(MOTOR3_DIR, GPIO_LOW); pwm_set_duty(MOTOR3_PWM, (uint32_t)duty);
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_LOW); pwm_set_duty(MOTOR4_PWM, (uint32_t)duty);} //gpio_set_level(MOTOR4_DIR, GPIO_LOW); pwm_set_duty(MOTOR4_PWM, (uint32_t)duty);
    }
    else           //��ת
    {
        if(motor_num == 1) { gpio_set_level(MOTOR1_DIR, GPIO_LOW); pwm_set_duty(MOTOR1_PWM, (uint32_t)-duty);}
        if(motor_num == 2) { gpio_set_level(MOTOR2_DIR, GPIO_LOW); pwm_set_duty(MOTOR2_PWM, (uint32_t)-duty);}

        if(motor_num == 3) { gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)-duty);}//gpio_set_level(MOTOR3_DIR, GPIO_HIGH); pwm_set_duty(MOTOR3_PWM, (uint32_t)abs_duty);
        if(motor_num == 4) { gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)-duty);}//gpio_set_level(MOTOR4_DIR, GPIO_HIGH); pwm_set_duty(MOTOR4_PWM, (uint32_t)abs_duty);
    }   
}

//����ʽPI�ٶȻ�
int16 Incremental_PI (uint8 motor_num, int16 Encoder, int16 Target)
{ 		
    int16 bias = Target - Encoder ;
	Pwm[motor_num-1] += ( Inc_Kp[motor_num-1]*(bias-motor_bias_last[motor_num-1]) 
                        + Inc_Ki[motor_num-1]*bias
                        + Inc_Kd[motor_num-1]*(bias-2*motor_bias_last[motor_num-1] + motor_bias_last2[motor_num-1] ));
    motor_bias_last2[motor_num-1] = motor_bias_last[motor_num-1];
    motor_bias_last[motor_num-1] = bias;
    
    //�����޷�
    if(Pwm[motor_num-1]> 8000)Pwm[motor_num-1]= 8000;
    if(Pwm[motor_num-1]<-8000)Pwm[motor_num-1]=-8000;
	
    return (int16)Pwm[motor_num-1];
}

//-----------------------------------------------------------------------------------------------
// �������  �����ķ�ֽ���
// ����˵��  v_x: x������ٶ�
// ����˵��  v_y: y������ٶ�
// ����˵��  w:   ������ٶ�
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  ��v_x, v_y,w�������������뼴�ɽ�����ĸ����ӵ�ת��
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
// �������  ѭ��ת����
// ����˵��  Target_slope��Ŀ��б��
// ����˵��  actual_slope��ʵ��б��
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  ͨ�����������б�ʴ���˺���������ת��ֵ���Ӷ�ѭ��
//-----------------------------------------------------------------------------------------------
float Kp_T=2.5, Kd_T=15; //2.6�� 1.5
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
// �������  ��������ʮ��ʱ�ĺ����ƶ�
// ����˵��  sideline_angle:����������
// ����˵��  sideline_distance:���߾������
// ���ز���  void
// ʹ��ʾ��  roundabout_move(&sideline_angle, &sideline_distance);
// ��ע��Ϣ  ע�����Ϊ������ݱ����ĵ�ַ���ڵ���ʱ������my_iamge.c�е�ȫ�ֱ���int16 sideline_angle,sideline_distance�ĵ�ַ����
//-----------------------------------------------------------------------------------------------
float Kp_correct1=1.0, Kd_correct1=10; //0.5 0.2 //1 10
float Kp_correct2=0.12, Kd_correct2=0.4;    //Kp = 0.07 kd = 0.4
static int16 out1, out2;
int16 target_y = 430;   //���߾��������Ŀ��ֵ
void roundabout_move(int16* sideline_angle,  int16* sideline_distance)
{

    //ʹ����������PID����һ����������б�Ƕ������� �ڶ�������������ǰ�������߽��������
    static int16 err1=0, err_last1=0, err2 = 0, err_last2=0;
    
    //������ǽ���pid
    err1 = *sideline_angle;
    out1 =Kp_correct1*err1 + Kd_correct1*(err1-err_last1);
	err_last1 = err1;
    out1 = func_limit(out1, 200); //�޷�

    //�������߾������pid
    err2 = (target_y-*sideline_distance); //Ŀ�����Ϊ500�����ص㣨ʹ���˶����֮�ͣ�//450 400   430
    out2 =Kp_correct2*err2 + Kd_correct2*(err2-err_last2);
    err_last2 = err2;
    out2 = func_limit(out2, 400); //�޷�

}

//-----------------------------------------------------------------------------------------------
// �������  �ǶȻ����⻷pid��
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  ����������ֵ��ֱ�Ӵ���w, Ҳ���Դ����ڻ����ٶȻ�����һ��ĿǰЧ�����Ǻܺã���������Ϊ���⻷����һ����ԭ��Ŀǰֱ���õ��⻷
// ��ע��Ϣ  ����PID�⻷һ��һ��P����(��i�ή����Ӧ�ٶ�,��d��Ŵ�����)
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
	integral = func_limit(integral,100); //�����޷�
	//return (out>=0) ? (8*sqrt(out)) : (-8*sqrt(func_abs(out)));
	out = func_limit(out,100);   //70
    return 2*out;

}

//-----------------------------------------------------------------------------------------------
// �������  ���ٶȻ����ڻ���
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  Ŀǰ����û���ã������Ͽ�����Ϊ����pid,���ǶȻ������ֵ��Ϊ���ٶȻ�������ֵ
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
	out_w = func_limit(out_w,400); //�޷�
    return out_w;
}

//-----------------------------------------------------------------------------------------------
// �������  ����MCX���͵�������г���λ�ý���
// ����˵��  correct_mode:����ģʽ�� 0--��Ƭʱ�Ľ����� 1--�ſ�Ƭʱ�Ľ���
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  {120, 125}������λ��; {160, 170}��Ƭλ��	
//-----------------------------------------------------------------------------------------------
int16 finial_point_1[2]  = {160, 170+10};
int16 finial_point_2[2] = {140, 135+10}; //120,125
float Kp_cor = 0.25;
float Kd_cor = 0; 
void position_correct(uint8 correct_mode)
{
    if(correct_mode == 0)       //��Ƭ����
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
	else if (correct_mode == 1)  //�ſ�Ƭ���� 
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
    else if(correct_mode == 2)  //��pid�Ľ���(����)
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
// �������  ������������������룬v_y = 0
// ����˵��  middle_line ������
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
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
// �������  ������ƺ��������ڱ������ɼ��ж��б�����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  �������жϺ����������Ե��ô˺���
//-----------------------------------------------------------------------------------------------
void motor_control()
{
	static uint8 cnt = 0;

    switch(Control_Mode)
    {
        case 0:                         //����ѭ��ģʽ
            Turn(target_slope,Slope);               
            break;
        case 1:                         //�߽����ģʽ
            roundabout_move(&sideline_angle, &sideline_distance);
            v_y = out2;
            //v_x = 20;
            w = out1;
            //w = Angle_PID(Target_Speed, angle);
            break;
        case 2:                         //��Ƭ����ģʽ
            position_correct(Correct_Mode);          
            break;
        case 3:                         //������ת��ģʽ
            //w = (int16)w_PID(Angle_PID(angle_now, Gyro_Angle.Zdata), tra_gyro_z);
            //w = (int16)w_PID(20, tra_gyro_z);
            // if(angle_now>360)angle_now -= 360;
            // else if (angle_now<-360)angle_now += 360;
            w = Angle_PID(angle_now + angle_turn, Gyro_Angle.Zdata);
            break;
	    case 4:                         //�ȴ�ģʽ
            break;
        case 5:   //��������ʶ�𵽿�Ƭ����ת���δ�ҵ���Ƭ�������߽����ֱ���ҵ���Ƭ
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
        case 6://   �Ƕȱջ�ģʽ����ģʽ�ǶȻᱣ�ֽǶ�ΪĿ��Ƕ�
            w = Angle_PID(target_angle, Gyro_Angle.Zdata);
            break;
        case 7: //�̶��ٶ�ѭ��
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

