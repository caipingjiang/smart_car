#ifndef _my_servo_h_
#define _my_servo_h_

void my_servo_init(void);
void Servo_SetAngle( uint8 servo_num, uint32 angle );
void Servo_SetAngle_Slow(uint8 servo_num, uint32 angle);
bool arm_down();
bool arm_up();
void arm_hang();
void arm_hang_fast();
void magnet_set(uint8 state);
bool Box_In(char card_class, uint8 cross_roundabout_Flag);
void Box_Out(char label_num, uint8 cross_roundabout_Flag);
bool check_temp_IsNull(void);
bool arm_exchange(uint8 a,uint8 b);

bool arm_up_part1();
void arm_up_part2();

extern char temp_class_arr[4][2]; 
extern uint8 five_Flag;                     //是否有5类的标志位， 0-没有第5类；  1-有1张第五类；  2-有两张第五类； 3-有1张第五类，且第6张是第1类
extern char five_class; 
#endif
