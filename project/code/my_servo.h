#ifndef _my_servo_h_
#define _my_servo_h_

void servo_init(void);
void Servo_SetAngle( uint8 servo_num, uint32 angle );
void arm_down();
void arm_up();

#endif
