#ifndef _my_servo_h_
#define _my_servo_h_

void my_servo_init(void);
void Servo_SetAngle( uint8 servo_num, uint32 angle );
void Servo_SetAngle_Slow(uint8 servo_num, uint32 angle);
void arm_down();
void arm_up();
void arm_hang();
void magnet_set(uint8 state);
void Box_In(char card_class, uint8 cross_roundabout_Flag);
void Box_Out(char label_num, uint8 cross_roundabout_Flag);
void arm_exchange(uint8 a,uint8 b);

void Box_In(char card_class, uint8 cross_roundabout_Flag);
void Box_Out(char label_num, uint8 cross_roundabout_Flag);

#endif
