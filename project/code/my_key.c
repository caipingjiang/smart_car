#include "zf_common_headfile.h"

void my_key_init()
{
	key_init(20);
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
