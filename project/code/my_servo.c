#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM1             (PWM4_MODULE2_CHA_C30)   //机械臂舵机1                     // 定义主板上舵机对应引脚
#define SERVO_MOTOR_PWM2             (PWM2_MODULE1_CHA_C8)   //机械臂舵机2
#define SERVO_MOTOR_PWM3             (PWM2_MODULE0_CHB_C7)   //储物舱舵机
#define magnet_PWM             		 (PWM1_MODULE3_CHA_B10)   //储物舱舵机


#define SERVO_MOTOR_FREQ            (50 )                                           // 定义主板上舵机频率  请务必注意范围 50-300
#define SERVO_MOTOR_MaxRange1       (180)   //180度舵机
#define SERVO_MOTOR_MaxRange2       (320)    //320度舵机  (储物舱的舵机)
#define SERVO_MOTOR_MaxRange3       (360)    //360度舵机(可控制角度)  (机械臂上面的舵机)

#if (SERVO_MOTOR_FREQ<50 || SERVO_MOTOR_FREQ>300)
    #error "SERVO_MOTOR_FREQ ERROE!"
#endif
// ------------------ 舵机占空比计算方式 ------------------
// 
// 舵机对应的 0-180 活动角度对应 控制脉冲的 0.5ms-2.5ms 高电平
// 
// 那么不同频率下的占空比计算方式就是
// PWM_DUTY_MAX/(1000/freq)*(0.5+Angle*2/180) 在 50hz 时就是 PWM_DUTY_MAX/(1000/50)*(0.5+Angle*2/180)
// 
// 那么 100hz 下 90度的打角 即高电平时间1.5ms 计算套用为
// PWM_DUTY_MAX/(1000/100)*(1+90*2/SERVO_MOTOR_MaxRange) = PWM_DUTY_MAX/10*1.5
// 
// ------------------ 舵机占空比计算方式 ------------------
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
	
	//电磁铁初始化
	pwm_init(magnet_PWM, 1000, 0);
	
	system_delay_ms(1000);
}
//电磁铁， 0关闭， 1开启
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
void arm_unload()       //搬完卸货
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




// 储物舱全局记录------------------------------------------->

//赛道两边储存信息，每个仓的最后一个元素记录本仓的卡片个数
static char store_list[4][10] = { {0} };

//环岛十字储存信息，4个仓（ >>>不包含第五类<<< ），每个仓储存两个信息：[0]表示每个仓对应的临时类别， [1]表示每个仓在环岛十字的临时卡片数量
static char temp_class_arr[4][2] = { {0} };          
static uint8 temp_cnt = 0;                      //环岛十字记录拾取卡片的次数
static uint8 five_Flag = 0;                     //是否有5类的标志位， 0-没有第5类；  1-有1张第五类；  2-有两张第五类； 3-有1张第五类，且第6张是第1类
static char five_class = 0;                     //第五类的类别
static uint8 five_unload_finish_Flag = 0;       //第五类卸货完成标志位

//卡片记录
//box_num:      仓号， 0-3
//card_class：  卡片类别， 'A'-'O'
//operate:      0 - 取出，  1 - 放入
void Box_Record(uint8 box_num, char card_class, uint8 operate)
{
    if (operate == 0)
    {
        store_list[box_num][(int)store_list[box_num][9]-1] = 0;
        store_list[box_num][9] -= 1; //对应仓位的卡片个数减1
    }
    else if (operate == 1)
    {
        store_list[box_num][9] += 1; //对应仓位的卡片个数加1
        store_list[box_num][(int)store_list[box_num][9]-1] = card_class;
    }
}



//  卡片放入逻辑
void Box_In(char card_class, uint8 cross_roundabout_Flag)
{
    
    if (!cross_roundabout_Flag) //赛道两边
    {
        if ('A' <= card_class && card_class <= 'E')        //大类-1
        {
            Box_Record(0, '1', 1);
            //Servo_SetAngle(3, 0);
        }
        else if ('F' <= card_class && card_class <= 'K')   //大类-2
        {
            Box_Record(1, '2', 1);
            //Servo_SetAngle(3, 90);
        }
        else if ('L' <= card_class && card_class <= 'O')   //大类-3
        {
            Box_Record(2, '3', 1);
            //Servo_SetAngle(3, 180);
        }
    }
    else      //环岛十字
    {
        temp_cnt++;
        
        for (uint8 i = 0; i < 4; i++)
        {
            //若仓位为空，则占取该仓位
            if (temp_class_arr[i][0] == 0 )
            {
                temp_class_arr[i][0] = card_class;
                temp_class_arr[i][1]++;
                //Servo_SetAngle(3, i*90);
                break;
            }
            //若仓位不为空，则判断本次拾取的卡片是否属于该仓位
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

            //若4个仓位都遍历完毕，仍未break,说明该卡片为第5类
            if (i == 3) //第5张或第6张为第5类
            {
                five_class = card_class;
                ++five_Flag;
                //Servo_SetAngle(3, 0);
                break;
            }
        }
        
    }//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@走出十字时要清零其相关信息
}

//  卡片取出逻辑
void Box_Out(char label_num, uint8 cross_roundabout_Flag)
{
    //环岛十字
    if (cross_roundabout_Flag)
    {
        //先卸货第5类
        if (!five_unload_finish_Flag)
        {
            //根据five_Flag进行分类
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

                //等待到达下一位置

                //Servo_SetAngle(3, 0);
                //arm_unload();
            }
            five_Flag = 0;
            five_class = 0;
            five_unload_finish_Flag = 1;
            return;//再前面进行卸第5类时，卸完可直接结束此函数调用，等待走到下一放置处，故此时调用此函数 参数没有意义
        }
        
        //再卸前四类
        for (uint8 i = 0; i < 4; i++)
        {
            if (label_num == temp_class_arr[i][0])
            {
                //Servo_SetAngle(3, i*90);
                for (uint8 j = 0; j < (int)temp_class_arr[i][1]; j++)
                {
                    //arm_unload();
                }
                temp_class_arr[i][1] = 0;  //卸完清零
                temp_class_arr[i][0] = 0;   //卸完清零
                break;
            }
        }
    }
    else
    {
        //最后卸三大类
        if (label_num == '1')        //大类-1
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
        else if (label_num == '2')   //大类-2
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
        else if (label_num == '3')   //大类-3
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


	
	
	
	