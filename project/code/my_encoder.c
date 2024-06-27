#include "zf_common_headfile.h"
#include "my_moter.h"
#define ENCODER_1                   (QTIMER1_ENCODER1)
#define ENCODER_1_A                 (QTIMER1_ENCODER1_CH1_C0)
#define ENCODER_1_B                 (QTIMER1_ENCODER1_CH2_C1)
#define ENCODER_2                   (QTIMER1_ENCODER2)
#define ENCODER_2_A                 (QTIMER1_ENCODER2_CH1_C2)
#define ENCODER_2_B                 (QTIMER1_ENCODER2_CH2_C24)
#define ENCODER_3                   (QTIMER2_ENCODER1)
#define ENCODER_3_A                 (QTIMER2_ENCODER1_CH1_C3)
#define ENCODER_3_B                 (QTIMER2_ENCODER1_CH2_C25)//QTIMER2_ENCODER1_CH2_C4
#define ENCODER_4                   (QTIMER3_ENCODER2)			//>>>>>>>>>>切换时要改
#define ENCODER_4_A                 (QTIMER3_ENCODER2_CH1_B18)//QTIMER2_ENCODER2_CH1_C5
#define ENCODER_4_B                 (QTIMER3_ENCODER2_CH2_B19)//QTIMER2_ENCODER2_CH2_C25//

int16 encoder_data[4];
int16 encoder_data_last[4]={0};
void my_encoder_init(void)
{
    encoder_quad_init(ENCODER_1,ENCODER_1_A,ENCODER_1_B);
    encoder_quad_init(ENCODER_2,ENCODER_2_A,ENCODER_2_B);
    encoder_quad_init(ENCODER_3,ENCODER_3_A,ENCODER_3_B);
    encoder_quad_init(ENCODER_4,ENCODER_4_A,ENCODER_4_B);
}

void pit_handler_0 (void)
{
    //motor_control();
   encoder_data[0] = encoder_get_count(ENCODER_1);
   encoder_clear_count(ENCODER_1);
                                  // 获取编码器计数
    encoder_data[1] = -encoder_get_count(ENCODER_2);
    encoder_clear_count(ENCODER_2);
                                  // 获取编码器计数
    encoder_data[2] = -encoder_get_count(ENCODER_3);
    encoder_clear_count(ENCODER_3);
    //                               // 获取编码器计数
    encoder_data[3] = encoder_get_count(ENCODER_4);
    encoder_clear_count(ENCODER_4);                              // 获取编码器计数
    //ips200_show_int(0,0,encoder_data[0],4);
    motor_control();	
}
 

