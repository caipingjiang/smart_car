#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM1             (PWM4_MODULE2_CHA_C30)  //机械臂舵机1                     // 定义主板上舵机对应引脚
#define SERVO_MOTOR_PWM2             (PWM2_MODULE1_CHA_C8)   //机械臂舵机2
#define SERVO_MOTOR_PWM3             (PWM2_MODULE0_CHB_C7)   //储物舱舵机
#define magnet_PWM             		  (PWM1_MODULE3_CHA_B10)  //PWM2_MODULE3_CHA_B9 //(PWM1_MODULE3_CHA_B10)  //电磁铁


#define SERVO_MOTOR_FREQ            (150)                   // 定义主板上舵机频率  请务必注意范围 50-300
#define SERVO_MOTOR_MaxRange1       (180)                   //180度舵机
#define SERVO_MOTOR_MaxRange2       (360)                   //360度舵机  (储物舱的舵机)
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
#define SERVO_SPEED	1		//舵机打角速度，0为正常模式，1为slow模式
#define is_IR   true        //是否开启IR来检测卡片拾取是否到位

//用于在Servo_SetAngle_Slow里记录角度	
static uint32 current_angle[3] = {100, 40, 0};    //初始化为主板上电后各个舵机的角度，对应pwm初始设置的参数

void my_servo_init(void)
{  
    pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(100));
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, (uint32)Arm_Servo1_Angle(40));
    system_delay_ms(200);
    pwm_init(SERVO_MOTOR_PWM3, SERVO_MOTOR_FREQ, (uint32)Box_Servo_Angle(0+BOX_OFFSET));
	
	//电磁铁初始化
	pwm_init(magnet_PWM, 10000, 0);

    //pwm_init(PWM2_MODULE3_CHA_B9, 1000, 9000);
    gpio_init(B9, GPO, 1, GPO_PUSH_PULL);
	current_angle[0] = 100;
	current_angle[1] = 40;
	current_angle[2] = 0+BOX_OFFSET;
	
}
//电磁铁， 0关闭， 1开启
void magnet_set(uint8 state)
{
	if(state == 0){ pwm_set_duty(magnet_PWM, 0); }
	else if(state == 1){pwm_set_duty(magnet_PWM, 7142); }//7142
}

void Servo_SetAngle( uint8 servo_num, uint32 angle )
{
    current_angle[servo_num-1] = angle;   //更新当前角度
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
            current_angle[2] = angle+BOX_OFFSET;   //更新记录的当前角度,不要忘了有偏移角度
            break;
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
        //system_delay_ms(5);       //设置的延时时间
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

//返回值:是否拾取上来，false-没有拾取上来，true-成功拾取上来
bool arm_up()
{
    bool state;     //记录本次拾取是否成功

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

//无任何延时的hang,用在art_control捡完卡片时
void arm_hang_fast()
{
    magnet_set(0);
    Servo_SetAngle(1, 100);
    Servo_SetAngle(2, 100);
}

bool arm_exchange(uint8 a,uint8 b)//取仓a一张卡片放仓b
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


// 储物舱全局记录------------------------------------------->

//赛道两边储存信息，每个仓的最后一个元素记录本仓的卡片个数
static char store_list[4][10] = { {0} };

//环岛十字储存信息，4个仓（ >>>不包含第五类<<< ），每个仓储存两个信息：[0]表示每个仓对应的临时类别， [1]表示每个仓在环岛十字的临时卡片数量


char temp_class_arr[4][2] = { {0} };      
static uint8 temp_cnt = 0;                      //环岛十字记录拾取卡片的次数
uint8 five_Flag = 0;                     //是否有5类的标志位， 0-没有第5类；  1-有1张第五类；  2-有两张第五类； 3-有1张第五类，且第6张是第1类
char five_class = 0;                     //第五类的类别
static uint8 five_unload_finish_Flag = 0;       //第五类卸货完成标志位

uint8 false_cnt_max1 = 10;      //环岛十字拾取、交换卡片错误最大次数限制
uint8 false_cnt_max2 = 5;       //赛道两边拾取卡片错误最大次数限制

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



//-----------------------------------------------------------------------------------------------
// 函数简介 卡片放入以及记录
// 参数说明  card_class，识别的卡片类别
// 参数说明  cross_roundabout_Flag，是否为环岛十字
// 参数说明  isRecord，是否记录
// 返回参数  是否拾取成功（根据机械臂上的传感器测的）
// 使用示例  
// 备注信息  赛道两边可选择是否记录，环岛十字默认都会记录
//-----------------------------------------------------------------------------------------------
bool Box_In(char card_class, uint8 cross_roundabout_Flag)
{
    bool state = false;
    if (!cross_roundabout_Flag) //赛道两边
    {
        if ('A' <= card_class && card_class <= 'E')        //大类-1
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
        else if ('F' <= card_class && card_class <= 'K')   //大类-2
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
        else if ('L' <= card_class && card_class <= 'O')   //大类-3
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
    else      //环岛十字
    {
        temp_cnt++;
        
        for (uint8 i = 0; i < 4; i++)
        {
            //若仓位为空，则占取该仓位
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
            //若仓位不为空，则判断本次拾取的卡片是否属于该仓位
            else if (card_class == temp_class_arr[i][0] )
            {
                if (five_Flag == 1 && i==0)    //第五张是第五类并且第六张是第一类
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

            //若4个仓位都遍历完毕，仍未break,说明该卡片为第5类
            if (i == 3) //第5张或第6张为第5类
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
        
    }//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@走出十字时要清零其相关信息
}


//  卡片取出逻辑
void Box_Out(char label_num, uint8 cross_roundabout_Flag)
{
    uint8 false_cnt = 0;    //记录放下、交换过程中的失败次数
    if (cross_roundabout_Flag)       //环岛和圆环
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
            //清零
            five_class = 0;
            five_Flag=0;
        }

    }
    else
    {
        //最后卸三大类
        if (label_num == '1')        //大类-1
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
        else if (label_num == '2')   //大类-2
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
        else if (label_num == '3')   //大类-3
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


	
	
	
	