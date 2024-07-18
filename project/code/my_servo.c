#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM1             (PWM4_MODULE2_CHA_C30)  //��е�۶��1                     // ���������϶����Ӧ����
#define SERVO_MOTOR_PWM2             (PWM2_MODULE1_CHA_C8)   //��е�۶��2
#define SERVO_MOTOR_PWM3             (PWM2_MODULE0_CHB_C7)   //����ն��
#define magnet_PWM             		  (PWM1_MODULE3_CHA_B10)  //PWM2_MODULE3_CHA_B9 //(PWM1_MODULE3_CHA_B10)  //�����


#define SERVO_MOTOR_FREQ            (150)                   // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
#define SERVO_MOTOR_MaxRange1       (180)                   //180�ȶ��
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

#define BOX_OFFSET	85
#define SERVO_SPEED	1		//�������ٶȣ�0Ϊ����ģʽ��1Ϊslowģʽ
#define is_IR   true        //�Ƿ���IR����⿨Ƭʰȡ�Ƿ�λ

//������Servo_SetAngle_Slow���¼�Ƕ�	
static uint32 current_angle[3] = {100, 40, 0};    //��ʼ��Ϊ�����ϵ���������ĽǶȣ���Ӧpwm��ʼ���õĲ���

void my_servo_init(void)
{  
    pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(100));
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(40));
    system_delay_ms(200);
    pwm_init(SERVO_MOTOR_PWM3, SERVO_MOTOR_FREQ, (uint32)Box_Servo_Angle(0+BOX_OFFSET));
	
	//�������ʼ��
	pwm_init(magnet_PWM, 10000, 0);

    //pwm_init(PWM2_MODULE3_CHA_B9, 1000, 9000);
    gpio_init(B9, GPO, 1, GPO_PUSH_PULL);
	current_angle[0] = 100;
	current_angle[1] = 40;
	current_angle[2] = 0+BOX_OFFSET;
	
}
//������� 0�رգ� 1����
void magnet_set(uint8 state)
{
	if(state == 0){ pwm_set_duty(magnet_PWM, 0); }
	else if(state == 1){pwm_set_duty(magnet_PWM, 7142); }//7142
}

void Servo_SetAngle( uint8 servo_num, uint32 angle )
{
    current_angle[servo_num-1] = angle;   //���µ�ǰ�Ƕ�
    switch (servo_num)
    {
        case 1:
            pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(angle));
            // system_delay_ms(50);
            // pwm_set_duty(SERVO_MOTOR_PWM1,0);
            break;
        case 2:
            pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(angle));
            // system_delay_ms(50);
            // pwm_set_duty(SERVO_MOTOR_PWM2,0);
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
    system_delay_ms(200);
    Servo_SetAngle(1, 100);
    system_delay_ms(350); 
    Servo_SetAngle(1, 80);
	magnet_set(1); 
    system_delay_ms(150);   
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

	Servo_SetAngle(2, 236);
    Servo_SetAngle(1, 135);
    system_delay_ms(300);
    
	Servo_SetAngle(1, 155);
    
	system_delay_ms(200);
    magnet_set(1);
	Servo_SetAngle(1, 163);
	system_delay_ms(300);
	Servo_SetAngle(1, 130);
	system_delay_ms(100);
	Servo_SetAngle(2, 60);
    if(IR_get_state() == 0)
    {
        state = true;
        buzzer_set_delay(50);
    }
    else
    {
        state = false;
    }
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




void arm_hang()
{
#if SERVO_SPEED == 1

    magnet_set(0);
    
    Servo_SetAngle(1, 100);
    Servo_SetAngle(2, 100);
    system_delay_ms(100);
#elif SERVO_SPEED == 0

    magnet_set(0);
    Servo_SetAngle_Slow(2, 100);
    Servo_SetAngle_Slow(1, 100);

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
    Servo_SetAngle_Slow(2, 29);
    Servo_SetAngle_Slow(1, 80);
	magnet_set(1); 
    system_delay_ms(100);
	Servo_SetAngle_Slow(1, 95);
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


// �����ȫ�ּ�¼------------------------------------------->

//�������ߴ�����Ϣ��ÿ���ֵ����һ��Ԫ�ؼ�¼���ֵĿ�Ƭ����
static char store_list[4][10] = { {0} };

//����ʮ�ִ�����Ϣ��4���֣� >>>������������<<< ����ÿ���ִ���������Ϣ��[0]��ʾÿ���ֶ�Ӧ����ʱ��� [1]��ʾÿ�����ڻ���ʮ�ֵ���ʱ��Ƭ����


char temp_class_arr[4][2] = { {0} };      
static uint8 temp_cnt = 0;                      //����ʮ�ּ�¼ʰȡ��Ƭ�Ĵ���
uint8 five_Flag = 0;                     //�Ƿ���5��ı�־λ�� 0-û�е�5�ࣻ  1-��1�ŵ����ࣻ  2-�����ŵ����ࣻ 3-��1�ŵ����࣬�ҵ�6���ǵ�1��
char five_class = 0;                     //����������
static uint8 five_unload_finish_Flag = 0;       //������ж����ɱ�־λ

uint8 false_cnt_max1 = 10;      //����ʮ��ʰȡ��������Ƭ��������������
uint8 false_cnt_max2 = 5;       //��������ʰȡ��Ƭ��������������

//��Ƭ��¼
//box_num:      �ֺţ� 0-3
//card_class��  ��Ƭ��� 'A'-'O'
//operate:      0 - ȡ����  1 - ����
void Box_Record(uint8 box_num, char card_class, uint8 operate)
{
    if (operate == 0)
    {
        store_list[box_num][(int)store_list[box_num][9]-1] = 0;
        store_list[box_num][9] -= 1; //��Ӧ��λ�Ŀ�Ƭ������1
    }
    else if (operate == 1)
    {
        store_list[box_num][9] += 1; //��Ӧ��λ�Ŀ�Ƭ������1
        store_list[box_num][(int)store_list[box_num][9]-1] = card_class;
    }
}



//-----------------------------------------------------------------------------------------------
// ������� ��Ƭ�����Լ���¼
// ����˵��  card_class��ʶ��Ŀ�Ƭ���
// ����˵��  cross_roundabout_Flag���Ƿ�Ϊ����ʮ��
// ����˵��  isRecord���Ƿ��¼
// ���ز���  �Ƿ�ʰȡ�ɹ������ݻ�е���ϵĴ�������ģ�
// ʹ��ʾ��  
// ��ע��Ϣ  �������߿�ѡ���Ƿ��¼������ʮ��Ĭ�϶����¼
//-----------------------------------------------------------------------------------------------
bool Box_In(char card_class, uint8 cross_roundabout_Flag)
{
    bool state = false;
    if (!cross_roundabout_Flag) //��������
    {
        if ('A' <= card_class && card_class <= 'E')        //����-1
        {
            // Servo_SetAngle(3, 0);
            // system_delay_ms(500);
            Servo_SetAngle_Slow(3, 0);
        #if is_IR
            if(arm_up())
        #else
            arm_up();
        #endif
            {
                Box_Record(0, '1', 1);
                state = true;
            }
            arm_hang_fast();
        }
        else if ('F' <= card_class && card_class <= 'K')   //����-2
        {
            // Servo_SetAngle(3, 90);
            // system_delay_ms(500);
            Servo_SetAngle_Slow(3, 90);
        #if is_IR
            if(arm_up())
        #else
            arm_up();
        #endif
            {
                Box_Record(1, '2', 1); 
                state = true;
            }
            arm_hang_fast();
        }
        else if ('L' <= card_class && card_class <= 'O')   //����-3
        {
            // Servo_SetAngle(3, 180);
            // system_delay_ms(500);
            Servo_SetAngle_Slow(3, 180);
        #if is_IR
            if(arm_up())
        #else
            arm_up();
        #endif
            {
                Box_Record(2, '3', 1);
                state = true;
            }
            arm_hang_fast();
        }
        return state;
    }
    else      //����ʮ��
    {
        temp_cnt++;
        
        for (uint8 i = 0; i < 4; i++)
        {
            //����λΪ�գ���ռȡ�ò�λ
            if (temp_class_arr[i][0] == 0 )
            {
                
                // Servo_SetAngle(3, i*90);
                // system_delay_ms(500);
                Servo_SetAngle_Slow(3, i*90);
            #if is_IR
                if(arm_up())
            #else
                arm_up();
            #endif
                {
                    temp_class_arr[i][0] = card_class;
                    temp_class_arr[i][1]++;
                }
                arm_hang();
                break;
            }
            //����λ��Ϊ�գ����жϱ���ʰȡ�Ŀ�Ƭ�Ƿ����ڸò�λ
            else if (card_class == temp_class_arr[i][0] )
            {
                if (five_Flag == 1 && i==0)    //�������ǵ����ಢ�ҵ������ǵ�һ��
                {
                    
					// Servo_SetAngle(3, i*90);
					// system_delay_ms(500);
                    Servo_SetAngle_Slow(3, i*90);
				#if is_IR
                    if(arm_up())
                #else
                    arm_up();
                #endif
                    {
                        five_Flag += 2;
                        temp_class_arr[i][1]++;
                    }
					arm_hang();
                    
                    break;
                }
                
                // Servo_SetAngle(3, i*90);
                // system_delay_ms(500);
                Servo_SetAngle_Slow(3, i*90);
            #if is_IR
                if(arm_up())
            #else
                arm_up();
            #endif
                {
                    temp_class_arr[i][1]++;
                }
                arm_hang();
                break;
            }

            //��4����λ��������ϣ���δbreak,˵���ÿ�ƬΪ��5��
            if (i == 3) //��5�Ż��6��Ϊ��5��
            {
                
                // Servo_SetAngle(3, 0);
                // system_delay_ms(500);
                Servo_SetAngle_Slow(3, 0);
            #if is_IR
                if(arm_up())
            #else
                arm_up();
            #endif
                {
                    five_class = card_class;
                    ++five_Flag;
                }
                arm_hang();
                break;
            }
        }
        
    }//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@�߳�ʮ��ʱҪ�����������Ϣ
}


//  ��Ƭȡ���߼�
void Box_Out(char label_num, uint8 cross_roundabout_Flag)
{
    uint8 false_cnt = 0;    //��¼���¡����������е�ʧ�ܴ���
    if (cross_roundabout_Flag)       //������Բ��
    {
        if(label_num == temp_class_arr[0][0])
        {
            if(five_Flag==1)
            {
            #if is_IR    
                false_cnt = 0;
                while( (!arm_exchange(0,1)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else 
                arm_exchange(0,1);
            #endif
                // Servo_SetAngle(3, 0);
                // system_delay_ms(1000);
                Servo_SetAngle_Slow(3, 0);
                for(uint8 i=0;i<temp_class_arr[0][1];i++)
                {
                #if is_IR 
                    while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                    {
                        false_cnt++;
                    }
                    false_cnt = 0;
                #else 
                    arm_down();
                #endif
                    arm_hang();
                }
                false_cnt = 0;
            #if is_IR 
                while( (!arm_exchange(1,0)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else 
                arm_exchange(1,0);
            #endif

                
            }
            else if(five_Flag==2)
            {
            #if is_IR
                false_cnt = 0;
                while( (!arm_exchange(0,1)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
                while( (!arm_exchange(0,1)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
            #else
                arm_exchange(0,1);
                arm_exchange(0,1);
            #endif
                false_cnt = 0;
                // Servo_SetAngle(3, 0);
                // system_delay_ms(1000);
                Servo_SetAngle_Slow(3, 0);
                for(uint8 i=0;i<temp_class_arr[0][1];i++)
                {
                #if is_IR 
                    while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                    {
                        false_cnt++;
                    }
                #else 
                    arm_down();
                #endif
                    arm_hang();
                }

            #if is_IR
                false_cnt = 0;
                while( (!arm_exchange(1,0)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
                while( (!arm_exchange(1,0)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else 
                arm_exchange(1,0);
                arm_exchange(1,0);
            #endif
                
            }
            else if(five_Flag==3)
            {
                // Servo_SetAngle(3, 0);
                // system_delay_ms(1000);
                Servo_SetAngle_Slow(3, 0);
                false_cnt = 0;
            #if is_IR 
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
            #else 
                arm_down();
            #endif
                arm_hang();
                false_cnt = 0;
            #if is_IR    
                while( (!arm_exchange(0,1)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else 
                arm_exchange(0,1);
            #endif    
                // Servo_SetAngle(3, 0);
                // system_delay_ms(800);
                Servo_SetAngle_Slow(3, 0);
                false_cnt = 0;
            #if is_IR
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
            #else
                arm_down();
            #endif 
                arm_hang();

                false_cnt = 0;
            #if is_IR
                while( (!arm_exchange(1,0)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else 
                arm_exchange(1,0);
            #endif 
                five_Flag=1;

            }
            else    //five_Flag==0
            {
                // Servo_SetAngle(3, 0);
                // system_delay_ms(1000);
                Servo_SetAngle_Slow(3, 0);
                for(uint8 i=0;i<temp_class_arr[0][1];i++)
                {
                #if is_IR
                    false_cnt = 0;
                    while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                    {
                        false_cnt++;
                    }
                    false_cnt = 0;
                #else 
                    arm_down();
                #endif 
                    arm_hang();
                }
            }
            temp_class_arr[0][0] = 0;
            temp_class_arr[0][1] = 0;
        }
        else if(label_num == temp_class_arr[1][0])
        {
            // Servo_SetAngle(3, 90);
            // system_delay_ms(1000);
            Servo_SetAngle_Slow(3, 90);
            for(uint8 i=0;i<temp_class_arr[1][1];i++)
            {
            #if is_IR
                false_cnt = 0;
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else 
                arm_down();
            #endif 
                arm_hang();
            }
            temp_class_arr[1][0] = 0;
            temp_class_arr[1][1] = 0;
        }
        else if(label_num == temp_class_arr[2][0])
        {
            // Servo_SetAngle(3, 180);
            // system_delay_ms(1000);
            Servo_SetAngle_Slow(3, 180);
            for(uint8 i=0;i<temp_class_arr[2][1];i++)
            {
            #if is_IR
                false_cnt = 0;
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_down();
            #endif
                arm_hang();
            }
            temp_class_arr[2][0] = 0;
            temp_class_arr[2][1] = 0;
        }
        else if(label_num == temp_class_arr[3][0])
        {
            // Servo_SetAngle(3, 270);
            // system_delay_ms(1000);
            Servo_SetAngle_Slow(3, 270);
            for(uint8 i=0;i<temp_class_arr[3][1];i++)
            {
            #if is_IR
                false_cnt = 0;
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_down();
            #endif
                arm_hang();
            }
            temp_class_arr[3][0] = 0;
            temp_class_arr[3][1] = 0;
        }
        else if(label_num == five_class)              //label_num==five_class
        {
            if(five_Flag==3)
            {
            #if is_IR
                false_cnt = 0;
                while( (!arm_exchange(0,1)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_exchange(0,1);
            #endif
                // Servo_SetAngle(3, 0);
                // system_delay_ms(1000);
                Servo_SetAngle_Slow(3, 0);
                
                false_cnt = 0;
            #if is_IR
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_down();
            #endif
                arm_hang();
                false_cnt = 0;
            #if is_IR
                while( (!arm_exchange(1,0)) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_exchange(1,0);
            #endif
               five_Flag=0;
            }
            // Servo_SetAngle(3, 0);
            // system_delay_ms(1000);
            Servo_SetAngle_Slow(3, 0);
            for(uint8 i=0;i<five_Flag;i++)
            {
                false_cnt = 0;
            #if is_IR
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
            #else
                arm_down();
            #endif
                arm_hang();
            }
            //����
            five_class = 0;
            five_Flag=0;
        }

    }
    else
    {
        //���ж������
        if (label_num == '1')        //����-1
        {   
            // Servo_SetAngle(3, 0);
            // system_delay_ms(800);
            Servo_SetAngle_Slow(3, 0);
            for (uint8 i = 0; i < (int)store_list[0][9]; i++)
            {
                buzzer_set_delay(500);
                system_delay_ms(100);
                //Box_Record(0, '1', 0);
                //arm_unload();
                store_list[0][i] = 0;
            #if is_IR
                false_cnt = 0;
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    ips114_show_int(0,50,(int)store_list[0][9],5);
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_down();
            #endif
                arm_hang();
            }
            store_list[0][9] = 0;
        }
        else if (label_num == '2')   //����-2
        {         
            // Servo_SetAngle(3, 90);
            // system_delay_ms(800);
            Servo_SetAngle_Slow(3, 90);
            for (uint8 i = 0; i < (int)store_list[1][9]; i++)
            {
                //Box_Record(1, '2', 0);
                //arm_unload();
                store_list[1][i] = 0;
            #if is_IR    
                false_cnt = 0;
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_down();
            #endif
                arm_hang();
            }
            store_list[1][9] = 0;
        }
        else if (label_num == '3')   //����-3
        {         
            // Servo_SetAngle(3, 180);
            // system_delay_ms(800);
            Servo_SetAngle_Slow(3, 180);
            for (uint8 i = 0; i < (int)store_list[2][9]; i++)
            {
                //Box_Record(2, '3', 0);
                //arm_unload();
                store_list[2][i] = 0;
            #if is_IR
                false_cnt = 0;
                while( (!arm_down()) && (false_cnt<false_cnt_max1) )
                {
                    false_cnt++;
                }
                false_cnt = 0;
            #else
                arm_down();
            #endif
                arm_hang();
            }
            store_list[2][9] = 0;
        }
    }    
}


	
	
	
	