#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM1             (PWM4_MODULE2_CHA_C30)  //��е�۶��1                     // ���������϶����Ӧ����
#define SERVO_MOTOR_PWM2             (PWM2_MODULE1_CHA_C8)   //��е�۶��2
#define SERVO_MOTOR_PWM3             (PWM2_MODULE0_CHB_C7)   //����ն��
#define magnet_PWM             		  (PWM1_MODULE3_CHA_B10)  //PWM2_MODULE3_CHA_B9 //(PWM1_MODULE3_CHA_B10)  //�����


#define SERVO_MOTOR_FREQ            (150)                   // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
#define SERVO_MOTOR_MaxRange1       (360)   //180               //180�ȶ��
#define SERVO_MOTOR_MaxRange2       (360)                   //360�ȶ��  (����յĶ��)
#define SERVO_MOTOR_MaxRange3       (360)                   //360�ȶ��(�ɿ��ƽǶ�)  (��е������Ķ��)

#if (SERVO_MOTOR_FREQ<50 || SERVO_MOTOR_FREQ>330)
    #error "SERVO_MOTOR_FREQ ERROE!"
#endif
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
// 
// �����Ӧ�� 0-180 ��Ƕȶ�Ӧ ��������� 0.5ms-2.5ms �ߵ�ƽ
// 
// ��ô��ͬƵ���µ�ռ�ձȼ��㷽ʽ����
// PWM_DUTY_MAX/(1000/freq)*(0.5+Angle*2/180) �� 50hz ʱ���� PWM_DUTY_MAX/(1000/50)*(0.5+Angle*2/180)
// 
// ��ô 100hz �� 90�ȵĴ�� ���ߵ�ƽʱ��1.5ms ��������Ϊ
// PWM_DUTY_MAX/(1000/100)*(1+90*2/SERVO_MOTOR_MaxRange) = PWM_DUTY_MAX/10*1.5
// 
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
#define Arm_Servo1_Angle(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)*2/SERVO_MOTOR_MaxRange1))
#define Arm_Servo2_Angle(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)*2/SERVO_MOTOR_MaxRange3))
#define Box_Servo_Angle(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)*2/SERVO_MOTOR_MaxRange2))

#define BOX_OFFSET	83
#define ARM1_OFFSET	-165
#define ARM2_OFFSET	3
#define SERVO_SPEED	1		//�������ٶȣ�0Ϊ����ģʽ��1Ϊslowģʽ
#define is_IR   true        //�Ƿ���IR����⿨Ƭʰȡ�Ƿ�λ

//������Servo_SetAngle_Slow���¼�Ƕ�	
static uint32 current_angle[3] = {100, 80, 0};    //��ʼ��Ϊ�����ϵ���������ĽǶȣ���Ӧpwm��ʼ���õĲ���

void my_servo_init(void)
{  
    pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(360-95+ARM1_OFFSET)); //100
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(80+ARM2_OFFSET));
    system_delay_ms(200);
    pwm_init(SERVO_MOTOR_PWM3, SERVO_MOTOR_FREQ, (uint32)Box_Servo_Angle(0+BOX_OFFSET));
	
	//�������ʼ��
	pwm_init(magnet_PWM, 10000, 0);

    //pwm_init(PWM2_MODULE3_CHA_B9, 1000, 9000);
    gpio_init(B9, GPO, 1, GPO_PUSH_PULL);
	current_angle[0] = 360-95+ARM1_OFFSET;
	current_angle[1] = 80+ARM2_OFFSET;
	current_angle[2] = 0+BOX_OFFSET;
	
}

//������� state:0�رգ� 1����
uint8 magnet_scale = 1; //����ǿ�ȣ�1����һ�㣬2������ǿ
void magnet_set(uint8 state)
{
	if(state == 0){ pwm_set_duty(magnet_PWM, 0); }
	else if(state == 1)
    {
        if(magnet_scale == 1)pwm_set_duty(magnet_PWM, 7142);//7142
        else if(magnet_scale == 2)pwm_set_duty(magnet_PWM, 10000);
        
    }
}

void Servo_SetAngle( uint8 servo_num, uint32 angle )
{
    current_angle[servo_num-1] = angle;   //���µ�ǰ�Ƕ�
    switch (servo_num)
    {
        case 1:
            pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(360-angle+ARM1_OFFSET));
			current_angle[0] = 360-angle+ARM1_OFFSET;
            // system_delay_ms(50);
            // pwm_set_duty(SERVO_MOTOR_PWM1,0);
            break;
        case 2:
            pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(angle+ARM2_OFFSET));
            // system_delay_ms(50);
            // pwm_set_duty(SERVO_MOTOR_PWM2,0);
            current_angle[1] = angle+ARM2_OFFSET;
            break;
        case 3:
            pwm_set_duty(SERVO_MOTOR_PWM3,(uint32)Box_Servo_Angle(angle+BOX_OFFSET));
            // system_delay_ms(50);
            // pwm_set_duty(SERVO_MOTOR_PWM3,0);
            current_angle[2] = angle+BOX_OFFSET;   //���¼�¼�ĵ�ǰ�Ƕ�,��Ҫ������ƫ�ƽǶ�
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------------------------
// �������  ���ö���Ƕȣ�����ʱ��ת������
// ����˵��  servo_num�������ţ� angle��Ҫ���õĽǶ�
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  ����my_servo_init���ʼ��pwmʱ���˳�ʼ���õĽǶȣ�������ҲӦ���ľ�̬����current_angle�ĳ�ʼֵ
//-----------------------------------------------------------------------------------------------
void Servo_SetAngle_Slow(uint8 servo_num, uint32 angle)
{
    if(servo_num == 3)
    {
        angle += BOX_OFFSET;
    }
	if(servo_num == 1)
    {
        angle = 360-angle+ARM1_OFFSET;
    }
    if(servo_num == 2)
    {
        angle = angle+ARM2_OFFSET;
    }
    while(current_angle[servo_num-1]!=angle)
    {
        if     (current_angle[servo_num-1]<angle)current_angle[servo_num-1]+=1;
        else if(current_angle[servo_num-1]>angle)current_angle[servo_num-1]-=1;

        switch (servo_num)
        {
            case 1:
                pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(current_angle[servo_num-1]));
				system_delay_ms(4);
                break;
            case 2:
                pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(current_angle[servo_num-1]));
				system_delay_us(2000);
                break;
            case 3:
                pwm_set_duty(SERVO_MOTOR_PWM3,(uint32)Box_Servo_Angle(current_angle[servo_num-1]));
                system_delay_ms(3);
            default:
                break;
        }
        //system_delay_ms(5);       //���õ���ʱʱ��
    }
}   

bool arm_down()
{
    bool state;

#if SERVO_SPEED == 1
	
    Servo_SetAngle(2, 29);
    system_delay_ms(200+100);
    Servo_SetAngle(1, 100);
    system_delay_ms(150+100); 
    Servo_SetAngle(1, 78);
	magnet_set(1); 
    system_delay_ms(250);   
	Servo_SetAngle(1, 90);
	system_delay_ms(50);
	Servo_SetAngle(1, 95);
	Servo_SetAngle(2, 35);
	system_delay_ms(50);
    Servo_SetAngle(1, 100);
	Servo_SetAngle(2, 40);
    system_delay_ms(50);
    Servo_SetAngle(2, 240);
    system_delay_ms(300);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(100);
    }
    else
    {
        state = false;
    }
    Servo_SetAngle(1, 130);
    system_delay_ms(300);
    magnet_set(0);
	
#elif SERVO_SPEED == 0
   
	Servo_SetAngle_Slow(2, 29);
    Servo_SetAngle_Slow(1, 80);
	magnet_set(1); 
    system_delay_ms(100);
	Servo_SetAngle_Slow(1, 95);
	Servo_SetAngle_Slow(2, 35);
    Servo_SetAngle_Slow(2, 240);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(100);
    }
    else
    {
        state = false;
    }
    Servo_SetAngle_Slow(1, 150);
    magnet_set(0);

#endif

    return state;
}

//����ֵ:�Ƿ�ʰȡ������false-û��ʰȡ������true-�ɹ�ʰȡ����
bool arm_up()
{
    bool state;     //��¼����ʰȡ�Ƿ�ɹ�

#if SERVO_SPEED == 1

	Servo_SetAngle(2, 234+2);
    system_delay_ms(300);
    magnet_set(1);
    //Servo_SetAngle(1, 135);
    //system_delay_ms(300-100);
    
	// Servo_SetAngle(1, 155);
    // system_delay_ms(300);
	// system_delay_ms(200-100);
    
	Servo_SetAngle(1, 163);
	system_delay_ms(350);

    Servo_SetAngle(1, 153);
    system_delay_ms(100);

	Servo_SetAngle(1, 130);
	system_delay_ms(100);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(50);
    }
    else
    {
        state = false;
    }
    Servo_SetAngle(2, 60);
	system_delay_ms(400);
	Servo_SetAngle(1, 115);
    system_delay_ms(150);
	Servo_SetAngle(1, 90);
	system_delay_ms(50);
    Servo_SetAngle(2, 28);
    system_delay_ms(200);
    magnet_set(0);
	
#elif SERVO_SPEED == 0
     
	//Servo_SetAngle_Slow(2, 236);
    Servo_SetAngle(2, 236);
    system_delay_ms(300);
    Servo_SetAngle_Slow(1, 150);
	Servo_SetAngle_Slow(1, 170);
    magnet_set(1);
    system_delay_ms(100);
	Servo_SetAngle_Slow(1, 125);
	//Servo_SetAngle_Slow(2, 70);
    Servo_SetAngle(2, 60);
    system_delay_ms(300);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(50);
    }
    else
    {
        state = false;
    }
    Servo_SetAngle(2, 50);
	system_delay_ms(100);
    Servo_SetAngle_Slow(1, 100);
//    // Servo_SetAngle_Slow(2, 50);
//	// Servo_SetAngle_Slow(2, 28);
//    Servo_SetAngle(2, 50);
    system_delay_ms(100);
//    Servo_SetAngle_Slow(1, 90);
    magnet_set(0);
//    
	
#endif

    return state;
}


bool arm_up_part1()
{
    bool state;     //��¼����ʰȡ�Ƿ�ɹ�

	Servo_SetAngle(2, 234);
    system_delay_ms(300);
    //Servo_SetAngle(1, 135);
    //system_delay_ms(300-100);

    magnet_set(1);
	Servo_SetAngle(1, 163);
	system_delay_ms(300);
	Servo_SetAngle(1, 130);
	system_delay_ms(100);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(50);
    }
    else
    {
        state = false;
    }
    return state;

}

void arm_up_part2()
{
    Servo_SetAngle(2, 60);
	system_delay_ms(400);
	Servo_SetAngle(1, 115);
    system_delay_ms(150);
	Servo_SetAngle(1, 90);
	system_delay_ms(50);
    Servo_SetAngle(2, 28);
    system_delay_ms(200);
    magnet_set(0);
}
void arm_hang()
{
#if SERVO_SPEED == 0

    magnet_set(0);
    
    Servo_SetAngle(1, 95);
    Servo_SetAngle(2, 95);
    system_delay_ms(200);
#elif SERVO_SPEED == 1

    magnet_set(0);
    Servo_SetAngle_Slow(2, 95);
    Servo_SetAngle_Slow(1, 95);

#endif
}

//���κ���ʱ��hang,����art_control���꿨Ƭʱ
void arm_hang_fast()
{
    magnet_set(0);
    Servo_SetAngle(1, 100);
    Servo_SetAngle(2, 100);
}

bool arm_exchange(uint8 a,uint8 b)//ȡ��aһ�ſ�Ƭ�Ų�b
{
#if SERVO_SPEED == 0  

    Servo_SetAngle(3, a*90);
	Servo_SetAngle(2, 29);
    system_delay_ms(500);
    Servo_SetAngle(1, 80);
    system_delay_ms(700);
    magnet_set(1);    
	Servo_SetAngle(1, 90);
	system_delay_ms(100);
	Servo_SetAngle(1, 95);
	Servo_SetAngle(2, 35);
	system_delay_ms(100);
    Servo_SetAngle(1, 100);
	Servo_SetAngle(2, 40);
    system_delay_ms(200);
	Servo_SetAngle(2, 150);
    system_delay_ms(200);
    Servo_SetAngle(1, 115);
    Servo_SetAngle(3, b*90);
    system_delay_ms(800);
	Servo_SetAngle(2, 60);
	system_delay_ms(200);
	Servo_SetAngle(1, 90);
	system_delay_ms(50);
    Servo_SetAngle(2, 28);
    system_delay_ms(500);
    magnet_set(0);
	arm_hang();

#elif SERVO_SPEED == 1

    bool state;
    arm_hang();
    Servo_SetAngle_Slow(3, a*90);
    //system_delay_ms(800);
    Servo_SetAngle_Slow(2, 25+3);
    system_delay_ms(200);
    Servo_SetAngle_Slow(1, 75);
	magnet_set(1); 
    system_delay_ms(250);
	Servo_SetAngle_Slow(1, 95-1);
	Servo_SetAngle_Slow(2, 35);
    Servo_SetAngle_Slow(2, 70);
    Servo_SetAngle_Slow(1, 120);
    Servo_SetAngle_Slow(3, b*90);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(100);
    }
    else
    {
        state = false;
    }
    Servo_SetAngle_Slow(1, 100);
    //system_delay_ms(800);
    Servo_SetAngle_Slow(2, 28);
	Servo_SetAngle_Slow(1, 90);
    magnet_set(0);
    arm_hang();

    return state;

#endif

}