#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM1             (PWM4_MODULE2_CHA_C30)   //��е�۶��1                     // ���������϶����Ӧ����
#define SERVO_MOTOR_PWM2             (PWM2_MODULE1_CHA_C8)   //��е�۶��2
#define SERVO_MOTOR_PWM3             (PWM2_MODULE0_CHB_C7)   //����ն��
#define magnet_PWM             		 (PWM1_MODULE3_CHA_B10)   //����ն��


#define SERVO_MOTOR_FREQ            (50 )                                           // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
#define SERVO_MOTOR_MaxRange1       (180)   //180�ȶ��
#define SERVO_MOTOR_MaxRange2       (320)    //320�ȶ��  (����յĶ��)
#define SERVO_MOTOR_MaxRange3       (360)    //360�ȶ��(�ɿ��ƽǶ�)  (��е������Ķ��)

#if (SERVO_MOTOR_FREQ<50 || SERVO_MOTOR_FREQ>300)
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
	

void servo_init(void)
{  
    pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, 0);
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, 0);
    pwm_init(SERVO_MOTOR_PWM3, SERVO_MOTOR_FREQ, 0);
	
	pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(80));
    pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(40));
    pwm_set_duty(SERVO_MOTOR_PWM3,(uint32)Box_Servo_Angle(0));
	
	//�������ʼ��
	pwm_init(magnet_PWM, 1000, 0);
	
	system_delay_ms(1000);
}
//������� 0�رգ� 1����
void magnet_set(uint8 state)
{
	if(state == 0){ pwm_set_duty(magnet_PWM, 0); }
	else if(state == 1){pwm_set_duty(magnet_PWM, 9999); }
}

void Servo_SetAngle( uint8 servo_num, uint32 angle )
{
    switch (servo_num)
    {
        case 1:
            pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(angle));
            break;
        case 2:
            pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(angle));
            break;
        case 3:
            pwm_set_duty(SERVO_MOTOR_PWM3,(uint32)Box_Servo_Angle(angle));
        default:
            break;
    }
}

void arm_down()
{
    for(uint8 i = 0; i<118; i++)
    {
        Servo_SetAngle(2, 100+i);
        if(i>=0&&i<=68)
        {
            Servo_SetAngle(1, 90-i);
        }
        system_delay_ms(10);
    }
      
    magnet_set(1);
}

void arm_up()
{

    // for(uint8 i = 0; i<118; i++)
    // {
        
    //     if(i>=0&&i<=68)
    //     {
    //         Servo_SetAngle(1, 22+i);
    //     }
    //     if(i>68)
    //     {
    //         Servo_SetAngle(2, 218-i);
    //     }
    //     system_delay_ms(10);
    // }
    
    magnet_set(1);
}
void arm_hang()
{
    Servo_SetAngle(1, 90);
    Servo_SetAngle(2, 100);
    system_delay_ms(100);
    magnet_set(1);
}
void arm_unload()       //����ж��
{
    Servo_SetAngle(1, 90);
    Servo_SetAngle(2, 100);
    system_delay_ms(100);
    magnet_set(1);
    system_delay_ms(500);
    Servo_SetAngle(1, 0);
    Servo_SetAngle(2, 18);
    magnet_set(0);
}




// �����ȫ�ּ�¼------------------------------------------->

//�������ߴ�����Ϣ��ÿ���ֵ����һ��Ԫ�ؼ�¼���ֵĿ�Ƭ����
static char store_list[4][10] = { {0} };

//����ʮ�ִ�����Ϣ��4���֣� >>>������������<<< ����ÿ���ִ���������Ϣ��[0]��ʾÿ���ֶ�Ӧ����ʱ��� [1]��ʾÿ�����ڻ���ʮ�ֵ���ʱ��Ƭ����
static char temp_class_arr[4][2] = { {0} };          
static uint8 temp_cnt = 0;                      //����ʮ�ּ�¼ʰȡ��Ƭ�Ĵ���
static uint8 five_Flag = 0;                     //�Ƿ���5��ı�־λ�� 0-û�е�5�ࣻ  1-��1�ŵ����ࣻ  2-�����ŵ����ࣻ 3-��1�ŵ����࣬�ҵ�6���ǵ�1��
static char five_class = 0;                     //����������
static uint8 five_unload_finish_Flag = 0;       //������ж����ɱ�־λ

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



//  ��Ƭ�����߼�
void Box_In(char card_class, uint8 cross_roundabout_Flag)
{
    
    if (!cross_roundabout_Flag) //��������
    {
        if ('A' <= card_class && card_class <= 'E')        //����-1
        {
            Box_Record(0, '1', 1);
            //Servo_SetAngle(3, 0);
        }
        else if ('F' <= card_class && card_class <= 'K')   //����-2
        {
            Box_Record(1, '2', 1);
            //Servo_SetAngle(3, 90);
        }
        else if ('L' <= card_class && card_class <= 'O')   //����-3
        {
            Box_Record(2, '3', 1);
            //Servo_SetAngle(3, 180);
        }
    }
    else      //����ʮ��
    {
        temp_cnt++;
        
        for (uint8 i = 0; i < 4; i++)
        {
            //����λΪ�գ���ռȡ�ò�λ
            if (temp_class_arr[i][0] == 0 )
            {
                temp_class_arr[i][0] = card_class;
                temp_class_arr[i][1]++;
                //Servo_SetAngle(3, i*90);
                break;
            }
            //����λ��Ϊ�գ����жϱ���ʰȡ�Ŀ�Ƭ�Ƿ����ڸò�λ
            else if (card_class == temp_class_arr[i][0] )
            {
                if (five_Flag == 1 &&i==0)
                {
                    five_Flag += 2;
                    break;
                }
                temp_class_arr[i][1]++;
                //Servo_SetAngle(3, i*90);
                break;
            }

            //��4����λ��������ϣ���δbreak,˵���ÿ�ƬΪ��5��
            if (i == 3) //��5�Ż��6��Ϊ��5��
            {
                five_class = card_class;
                ++five_Flag;
                //Servo_SetAngle(3, 0);
                break;
            }
        }
        
    }//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@�߳�ʮ��ʱҪ�����������Ϣ
}

//  ��Ƭȡ���߼�
void Box_Out(char label_num, uint8 cross_roundabout_Flag)
{
    //����ʮ��
    if (cross_roundabout_Flag)
    {
        //��ж����5��
        if (!five_unload_finish_Flag)
        {
            //����five_Flag���з���
            if (five_Flag == 1 || five_Flag == 2)
            {
                //Servo_SetAngle(3, 0);
                //arm_unload();
                if (five_Flag == 2)
                {
                    //arm_unload();
                }
            }
            else if (five_Flag == 3)
            {
                //Servo_SetAngle(3, 0);
                //arm_unload();

                //�ȴ�������һλ��

                //Servo_SetAngle(3, 0);
                //arm_unload();
            }
            five_Flag = 0;
            five_class = 0;
            five_unload_finish_Flag = 1;
            return;//��ǰ�����ж��5��ʱ��ж���ֱ�ӽ����˺������ã��ȴ��ߵ���һ���ô����ʴ�ʱ���ô˺��� ����û������
        }
        
        //��жǰ����
        for (uint8 i = 0; i < 4; i++)
        {
            if (label_num == temp_class_arr[i][0])
            {
                //Servo_SetAngle(3, i*90);
                for (uint8 j = 0; j < (int)temp_class_arr[i][1]; j++)
                {
                    //arm_unload();
                }
                temp_class_arr[i][1] = 0;  //ж������
                temp_class_arr[i][0] = 0;   //ж������
                break;
            }
        }
    }
    else
    {
        //���ж������
        if (label_num == '1')        //����-1
        {
            //Servo_SetAngle(3, 0);
            for (uint8 i = 0; i < (int)store_list[0][9]; i++)
            {
                Box_Record(0, '1', 0);
                //arm_unload();
                store_list[0][i] = 0;
            }
            store_list[0][9] = 0;

        }
        else if (label_num == '2')   //����-2
        {
            //Servo_SetAngle(3, 90);
            for (uint8 i = 0; i < (int)store_list[1][9]; i++)
            {
                Box_Record(1, '2', 0);
                //arm_unload();
                store_list[1][i] = 0;
            }
            store_list[1][9] = 0;
        }
        else if (label_num == '3')   //����-3
        {
            //Servo_SetAngle(3, 180);
            for (uint8 i = 0; i < (int)store_list[2][9]; i++)
            {
                Box_Record(2, '3', 0);
                //arm_unload();
                store_list[2][i] = 0;
            }
            store_list[2][9] = 0;
        }
    }    
}


	
	
	
	