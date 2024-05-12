#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM1             (PWM4_MODULE2_CHA_C30)  //机械臂舵机1                     // 定义主板上舵机对应引脚
#define SERVO_MOTOR_PWM2             (PWM2_MODULE1_CHA_C8)   //机械臂舵机2
#define SERVO_MOTOR_PWM3             (PWM2_MODULE0_CHB_C7)   //储物舱舵机
#define magnet_PWM             		 (PWM1_MODULE3_CHA_B10)  //电磁铁


#define SERVO_MOTOR_FREQ            (50 )                   // 定义主板上舵机频率  请务必注意范围 50-300
#define SERVO_MOTOR_MaxRange1       (180)                   //180度舵机
#define SERVO_MOTOR_MaxRange2       (360)                   //320度舵机  (储物舱的舵机)
#define SERVO_MOTOR_MaxRange3       (360)                   //360度舵机(可控制角度)  (机械臂上面的舵机)

#if (SERVO_MOTOR_FREQ<50 || SERVO_MOTOR_FREQ>330)
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

#define BOX_OFFSET	85
//用于在Servo_SetAngle_Slow里记录角度	
static uint32 current_angle[3] = {100, 40, 0};    //初始化为主板上电后各个舵机的角度，对应pwm初始设置的参数

void my_servo_init(void)
{  
    pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(100));
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(40));
    system_delay_ms(200);
    pwm_init(SERVO_MOTOR_PWM3, SERVO_MOTOR_FREQ, (uint32)Box_Servo_Angle(0+BOX_OFFSET));
	
	//电磁铁初始化
	pwm_init(magnet_PWM, 50, 0);
	
}
//电磁铁， 0关闭， 1开启
void magnet_set(uint8 state)
{
	if(state == 0){ pwm_set_duty(magnet_PWM, 0); }
	else if(state == 1){pwm_set_duty(magnet_PWM, 9999); }//7142
}

void Servo_SetAngle( uint8 servo_num, uint32 angle )
{
    current_angle[servo_num-1] = angle;   //更新当前角度
    switch (servo_num)
    {
        case 1:
            pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(angle));
            break;
        case 2:
            pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(angle));
            break;
        case 3:
            pwm_set_duty(SERVO_MOTOR_PWM3,(uint32)Box_Servo_Angle(angle+BOX_OFFSET));
        default:
            break;
    }
}

//-----------------------------------------------------------------------------------------------
// 函数简介  设置舵机角度（有延时，转得慢）
// 参数说明  servo_num：舵机编号， angle：要设置的角度
// 返回参数  void
// 使用示例  
// 备注信息  若在my_servo_init里初始化pwm时改了初始设置的角度，则这里也应更改静态数组current_angle的初始值
//-----------------------------------------------------------------------------------------------
void Servo_SetAngle_Slow(uint8 servo_num, uint32 angle)
{
    while(current_angle[servo_num-1]!=angle)
    {
        if     (current_angle[servo_num-1]<angle)current_angle[servo_num-1]+=1;
        else if(current_angle[servo_num-1]>angle)current_angle[servo_num-1]-=1;

        switch (servo_num)
        {
            case 1:
                pwm_set_duty(SERVO_MOTOR_PWM1,(uint32)Arm_Servo1_Angle(current_angle[servo_num-1]));
                break;
            case 2:
                pwm_set_duty(SERVO_MOTOR_PWM2,(uint32)Arm_Servo2_Angle(current_angle[servo_num-1]));
                break;
            case 3:
                pwm_set_duty(SERVO_MOTOR_PWM3,(uint32)Box_Servo_Angle(current_angle[servo_num-1]));
            default:
                break;
        }
        system_delay_ms(5);       //设置的延时时间
    }
}   

void arm_down()
{
    Servo_SetAngle(1, 80);
    Servo_SetAngle(2, 26);
    magnet_set(1);
    system_delay_ms(1200);
    Servo_SetAngle(1, 95);
    system_delay_ms(200);
    Servo_SetAngle(2, 228);
    system_delay_ms(800);
    Servo_SetAngle(1, 130);
    system_delay_ms(300);
    magnet_set(0);
	system_delay_ms(50);
}

void arm_up()
{
	Servo_SetAngle(1, 150);
    Servo_SetAngle(2, 234);
	system_delay_ms(800);
    magnet_set(1);
	Servo_SetAngle(1, 162);
	system_delay_ms(400);
	Servo_SetAngle(1, 130);
	system_delay_ms(100);
	Servo_SetAngle(2, 70);
	system_delay_ms(500);
	Servo_SetAngle(1, 100);
    system_delay_ms(800);
    Servo_SetAngle(2, 28);
    Servo_SetAngle(1, 90);
    system_delay_ms(500);
    magnet_set(0);
}



void arm_hang()
{
    magnet_set(0);
    system_delay_ms(500);
    Servo_SetAngle(1, 100);
    Servo_SetAngle(2, 100);
}

void arm_exchange(uint8 a,uint8 b)        //取仓a一张卡片放仓b
{
    Servo_SetAngle(3, a*90);
    system_delay_ms(800);
	 Servo_SetAngle(1, 80);
    Servo_SetAngle(2, 26);
    magnet_set(1);
    system_delay_ms(1200);
    Servo_SetAngle(1, 95);
    system_delay_ms(200);
    Servo_SetAngle(2, 228);
	system_delay_ms(500);
    Servo_SetAngle(3, b*90);
    system_delay_ms(800);
    Servo_SetAngle(1, 130);
	system_delay_ms(100);
	Servo_SetAngle(2, 70);
	system_delay_ms(500);
	Servo_SetAngle(1, 100);
    system_delay_ms(800);
    Servo_SetAngle(2, 28);
    Servo_SetAngle(1, 90);
    system_delay_ms(500);
    magnet_set(0);
    arm_hang();
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
            Servo_SetAngle(3, 0);
             system_delay_ms(500);
            arm_up();
            arm_hang();
        }
        else if ('F' <= card_class && card_class <= 'K')   //大类-2
        {
            Box_Record(1, '2', 1);
            Servo_SetAngle(3, 90);
            system_delay_ms(500);
            arm_up();
            arm_hang();
        }
        else if ('L' <= card_class && card_class <= 'O')   //大类-3
        {
            Box_Record(2, '3', 1);
            Servo_SetAngle(3, 180);
            system_delay_ms(500);
            arm_up();
            arm_hang();
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
                Servo_SetAngle(3, i*90);
                system_delay_ms(500);
                arm_up();
                arm_hang();
                break;
            }
            //若仓位不为空，则判断本次拾取的卡片是否属于该仓位
            else if (card_class == temp_class_arr[i][0] )
            {
                if (five_Flag == 1 &&i==0)    //第五张是第五类并且第六张是第一类
                {
                    five_Flag += 2;
					Servo_SetAngle(3, i*90);
					system_delay_ms(500);
					arm_up();
					arm_hang();
					
					
                    break;
                }
                temp_class_arr[i][1]++;
                Servo_SetAngle(3, i*90);
                system_delay_ms(500);
                arm_up();
                arm_hang();
                break;
            }

            //若4个仓位都遍历完毕，仍未break,说明该卡片为第5类
            if (i == 3) //第5张或第6张为第5类
            {
                five_class = card_class;
                ++five_Flag;
                Servo_SetAngle(3, 0);
                system_delay_ms(500);
                arm_up();
                arm_hang();
                break;
            }
        }
        
    }//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@走出十字时要清零其相关信息
}

//  卡片取出逻辑
void Box_Out(char label_num, uint8 cross_roundabout_Flag)
{
    //环岛十字
    // if (cross_roundabout_Flag)
    // {
    //     //先卸货第5类
    //     if (!five_unload_finish_Flag)
    //     {
    //         //根据five_Flag进行分类
    //         if (five_Flag == 1 || five_Flag == 2)
    //         {
    //             //Servo_SetAngle(3, 0);
    //             //arm_unload();
    //             if (five_Flag == 2)
    //             {
    //                 //arm_unload();
    //             }
    //         }
    //         else if (five_Flag == 3)
    //         {
    //             //Servo_SetAngle(3, 0);
    //             //arm_unload();

    //             //等待到达下一位置

    //             //Servo_SetAngle(3, 0);
    //             //arm_unload();
    //         }
    //         five_Flag = 0;
    //         five_class = 0;
    //         five_unload_finish_Flag = 1;
    //         return;//再前面进行卸第5类时，卸完可直接结束此函数调用，等待走到下一放置处，故此时调用此函数 参数没有意义
    //     }
        
    //     //再卸前四类
    //     for (uint8 i = 0; i < 4; i++)
    //     {
    //         if (label_num == temp_class_arr[i][0])
    //         {
    //             //Servo_SetAngle(3, i*90);
    //             for (uint8 j = 0; j < (int)temp_class_arr[i][1]; j++)
    //             {
    //                 //arm_unload();
    //             }
    //             temp_class_arr[i][1] = 0;  //卸完清零
    //             temp_class_arr[i][0] = 0;   //卸完清零
    //             break;
    //         }
    //     }
    // }
    if (cross_roundabout_Flag)       //环岛和圆环
     {
        if(label_num== temp_class_arr[0][0])
        {
            if(five_Flag==1)
            {
                arm_exchange(0,1);
                for(uint8 i=0;i<temp_class_arr[0][1];i++)
                {
                 Servo_SetAngle(3, 0);
                 system_delay_ms(800);
                 arm_down();
                 arm_hang();
                }
                arm_exchange(1,0);

            }
            else if(five_Flag==2)
            {
                arm_exchange(0,1);
                arm_exchange(0,1);
                for(uint8 i=0;i<temp_class_arr[0][1];i++)
                {
                 Servo_SetAngle(3, 0);
                 system_delay_ms(800);
                 arm_down();
                 arm_hang();
                }
                arm_exchange(1,0);
                arm_exchange(1,0);
                
            }
            else if(five_Flag==3)
            {
                Servo_SetAngle(3, 0);
                system_delay_ms(800);
                arm_down();
                arm_hang();
                arm_exchange(0,1);
                
                Servo_SetAngle(3, 0);
                system_delay_ms(800);
                arm_down();
                arm_hang();
                arm_exchange(1,0);
                five_Flag=1;
                
            }
            else
            {
                for(uint8 i=0;i<temp_class_arr[0][1];i++)
                {
                 Servo_SetAngle(3, 0);
                 system_delay_ms(800);
                 arm_down();
                 arm_hang();
                }
            }

        temp_class_arr[0][1]=0;
        }
        else if(label_num== temp_class_arr[1][0])
        {
            for(uint8 i=0;i<temp_class_arr[1][1];i++)
                {
                 Servo_SetAngle(3, 90);
                system_delay_ms(800);
                arm_down();
                arm_hang();
                }
            temp_class_arr[1][1]=0;
        }
         else if(label_num== temp_class_arr[2][0])
        {
            for(uint8 i=0;i<temp_class_arr[2][1];i++)
                {
                Servo_SetAngle(3, 180);
                system_delay_ms(800);
                arm_down();
                arm_hang();
                }
             temp_class_arr[2][1]=0;
        }
         else if(label_num== temp_class_arr[3][0])
        {
            for(uint8 i=0;i<temp_class_arr[3][1];i++)
                {
                Servo_SetAngle(3, 270);
                system_delay_ms(800);
                arm_down();
                arm_hang();
                }
             temp_class_arr[3][1]=0;
        }
        else              //label_num==five_class
        {
            if(five_Flag==3)
            {
                arm_exchange(0,1);
                Servo_SetAngle(3, 0);
                system_delay_ms(800);
                arm_down();
                arm_hang();
                arm_exchange(1,0);

               five_Flag=0;
            }
            for(uint8 i=0;i<five_Flag;i++)
            {
                Servo_SetAngle(3, 0);
                system_delay_ms(800);
                arm_down();
                arm_hang();
            }
            five_Flag=0;
        }

     }


    else
    {
       
        //最后卸三大类
        if (label_num == '1')        //大类-1
        {
            
            for (uint8 i = 0; i < (int)store_list[0][9]; i++)
            {
                Box_Record(0, '1', 0);
                //arm_unload();
                store_list[0][i] = 0;
                Servo_SetAngle(3, 0);
                system_delay_ms(800);
                arm_down();
                arm_hang();
				
            }
            store_list[0][9] = 0;

        }
        else if (label_num == '2')   //大类-2
        {
			
            
            for (uint8 i = 0; i < (int)store_list[1][9]; i++)
            {
                Box_Record(1, '2', 0);
                //arm_unload();
                store_list[1][i] = 0;
                Servo_SetAngle(3, 90);
                system_delay_ms(800);
                arm_down();
                arm_hang();
            }
            store_list[1][9] = 0;
        }
        else if (label_num == '3')   //大类-3
        {
			
            
            for (uint8 i = 0; i < (int)store_list[2][9]; i++)
            {
                Box_Record(2, '3', 0);
                //arm_unload();
                store_list[2][i] = 0;
                Servo_SetAngle(3, 180);
                system_delay_ms(800);
                arm_down();
                arm_hang();
            }
            store_list[2][9] = 0;
        }
    }    
}


	
	
	
	