#include "zf_common_headfile.h"
#include "my_servo.h"
void my_key_init()
{
	key_init(10);
}

//��my_key_init��ʼ���� ֱ������ѭ�����ж��У����ô˺�������
void my_key_work(void)
{
	key_scanner();

    uint8 Key_num = 0;
    for(Key_num = KEY_1; Key_num <= KEY_4; Key_num++)
    {
        if( KEY_SHORT_PRESS == key_get_state(Key_num))
        {
            switch(Key_num)
            {
            case KEY_1:
                //ips114_show_string(40,40,"key1");//arm_up();
                break;
            case KEY_2:
                Kp_correct1+=0.5;//Kp_T+=0.1;////arm_down(); 
                break;
            case KEY_3:
                Kp_correct1-=0.5;//Kp_T-=0.1;//arm_hang();
                break;
            case KEY_4:
                Kd_correct1+=0.5;//arm_up();
                break;
            default:
                break;
            }

            key_clear_state(Key_num);// Ҳ����������а���״̬key_clear_all_state();     
        }
        else if(KEY_LONG_PRESS == key_get_state(Key_num))
        {
            switch(Key_num)
            {
            case KEY_1:
                ;
                break;
            case KEY_2:
                ; 
                break;
            case KEY_3:
                ;
                break;
            case KEY_4:
                ;
                break;
            }
              
        }
    }
    key_clear_state(Key_num);// Ҳ����������а���״̬key_clear_all_state();   
	
}

//�����жϸ���������			
//        if( KEY_SHORT_PRESS == key_get_state(KEY_1) ||
//            KEY_SHORT_PRESS == key_get_state(KEY_2) ||
//            KEY_SHORT_PRESS == key_get_state(KEY_3) ||
//            KEY_SHORT_PRESS == key_get_state(KEY_4))                            // ���ⰴ���̰�
//        {}
