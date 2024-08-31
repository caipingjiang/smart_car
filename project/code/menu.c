#include "zf_common_headfile.h"
#include "menu.h"
#include <math.h>
#include "my_motor.h"

uint8 openart_bright_scale = 20;
//������ǲ��Բ�������ʵ�ʹ����У������������жϵõ�
uint16 arm_angle1 = 100, arm_angle2 = 40, box_angle = 0+85;//85Ϊƫ����
bool magnet_state = false;
float AngleTh = 30;
uint16 PodaoFlag = 0; 
uint16 BarrierFlag = 0;
uint16 RingFlag = 0;
uint8 datapage = 0;//0����ʾID��Ӧ�ĺ�����1���޸�arrow��Ӧ�Ĳ���
float mul = 1;

//������ʾ�����˵�
uint8 pagenum = 0;//��ʾpage����Ŀ
int8 arrow = 0;//���������ڵ��У���ʼ���ڵ�һ��


void UI()
{
	if(!datapage)
	{
		UI_Content();//��ʾID��Ӧ�ĺ���
		UI_ContentKey();//����ID
	}
	else
	{
		UI_Datapage();  //����ҳ
        UI_DatapageKey();   //���ݰ�������
	}
	if(pagenum!=8)
	{
		DisplayCursor();//�����ʾ
	}
}


void UI_Content(void)
{
	//ips114_clear();//����ʾ��һ���˵�ʱ����Ҫ����
	// ����pagenumȥ��ʾ�˵�
	switch(pagenum)
    {
        case 0://��ʾ���˵�
		{
			DisplayMain();
		}break;
		case 1://��ʾ��װ���ع����
		{
			DisplayMt9v03Para();
		}break;
		case 2://��ʾ�ٶȲ���
		{
			DisplaySpeedPara();
		}break;
		case 3://��ʾ�������
		{
			DisplayServoPara();
		}break;
		case 4://��ʾIMU����
		{
			DisplayIMUPara();
		}break;
		case 5://��ʾԪ�ز���
		{
			DisplayElementPara();
		}break;
		case 6://Start
		{
			DisplayStartPara();
		}break;
		case 7://OpenArt brightness
		    DisplayOpenArtPara();
			break;
		case 8:
		    DisplayImage();
			break;
		default:
		{
			DisplayMain();	
		}break;
	}
}

//������һ���˵�
uint8 pagenumup(void)
{
	switch(pagenum)
	{
		case 0://��һ���˵�
			return 0;
		case 1://��һ���˵�
			return 0;
		case 2://��һ���˵�
			return 0;
		case 3://��һ���˵�
			return 0;
		case 4://��һ���˵�
			return 0;
		case 5://��һ���˵�
			return 0;
		case 6://��һ���˵�
			return 0;
		case 7:
			return 0;
		case 8:	
			return 0;
		default:
			return 0;
	}
}

//������һ���˵�
//��Ҫ�жϵ�ǰID��֪������һҳ����Щʲô����
//����Ҫ�жϹ�������У�֪��Ҫ������һ����������
uint8 pagenumdown(void)
{
	switch(pagenum)
	{
		case 0://��������
		{
			switch(arrow)//�ж��ڵڼ���
			{
				case 0://�ڵ�0��---->��Ӧ�Ų���Mt9v03Para
				{
					return 1;//����Mt9v03Para��ID
				}
				case 1: return 2;//��ӦSpeedPara
				case 2: return 3;//��ӦServoPara
				case 3: return 4;//��ӦIMUPara
				case 4: return 5;//��ӦElemnetPara
				case 5: return 6;//��ӦStartPara
				case 6: return 7;//��ӦopenartPara
				case 7: return 8;//��ӦImage
			}
		}break;
		case 1://��Mt9v03Para����
		{
			return 1;//���ص�ǰ����
			//�ڸý�����û����һ������ֱ��break;
		}break;
		case 2: return 2;		//��SpeedPara����
		case 3: return 3;		//ServoPara����
		case 4: return 4;		//IMUPara����
		case 5://ElemnetPara����
		{
			switch(arrow)
			{	//��־λ�����ܸ���
				default : return 5;//���ص�ǰ����
			}
		}break;
		
		default:break;
	}
}


void DisplayCursor()//��ʾ���
{
	ips114_show_string(0,arrow*16,">");//�ڲ���ǰ����ʾ>
}

//���հ���ֵ��������arrow
void UI_ContentKey()
{
	//uint8 key = Get_Key_flag();//��ȡ����ֵ
    if(KEY_SHORT_PRESS == key_get_state(KEY_1)){//���� up
        ips114_show_string(0,arrow*16," ");  //��Ҫ����ǰ�еĹ�����أ���Ȼ��arrow����֮�󣬳���������ʾ���
		arrow--;//�����ƶ���arrow��С
	}
    if(KEY_SHORT_PRESS == key_get_state(KEY_2)){//���� down
        ips114_show_string(0,arrow*16," ");  arrow++;}//��upͬ��
	
/**********�����key1,key2�����������ƶ�����***********/
/**********�����key3,key4������������Ӧ�ĸ�/�Ӳ˵���***********/

    if(KEY_SHORT_PRESS == key_get_state(KEY_3)){//������ҳ��  enter
        ips114_clear();//��Ҫ����ǰ��ʾ������������ʾ�ӽ���    
		pagenum = pagenumdown();//�����ӽ��� 
		arrow = 0;//�ӵ�0�п�ʼ
	}
    if(KEY_SHORT_PRESS == key_get_state(KEY_4)){//������һ��ҳ�� back
        ips114_clear();    
		pagenum = pagenumup();
		arrow = 0;
	}
	if(KEY_LONG_PRESS == key_get_state(KEY_1))//���Ĳ���
	{
		buzzer_set_delay(100);
		system_delay_ms(500);
		ips114_clear();
		   
		datapage = 1;    
		mul = 1;
	}
	
	//��arrow�޷���OLED��ֻ����ʾ8�У�������Ҫ���� 0 <= arrow <8
	if(arrow < 0)
		arrow = 7;//��˼�ǣ�������up�������һֱ�����ƶ������˶�����һ�м�arrow=0��
				  //�ٰ���upʱ�����ֱ���������һ�У�arrow = 7
	else if(arrow >7)
		arrow = 0;

	key_clear_all_state();
}





//��ʾ����Ĳ���
void UI_Datapage()
{
	uint8 x = 20,y = 190;
	//ips114_clear();
	switch(pagenum)
	{
		case 0:break;//��IDΪ0�Ľ���û����Ҫ�޸ĵĲ���
		case 1://��Ӧexposure time
		{
			switch(arrow)
			{
				case 0://kp
				{
					ips114_show_string(x,0,"exposure time is:"); 
					ips114_show_int(y,1*16,mt9v03X_light,4);
					ips114_show_string(x,3*16,"white value:"); 
					ips114_show_int(y,4*16,find_white_point(mt9v03x_image),3);
				}break;
			
				default:break;
			}
			ips114_show_float(y,7*16,mul,4,3);//��ʾ����
		}break;
		
		case 2://��ӦSpeedPara
		{
			switch(arrow)
			{
				case 0://kp
				{
					ips114_show_string(x,0,"speed_offset"); 
					ips114_show_int(y,2*16,speed_offset,3);
				}break;
				default:break;
			}
			ips114_show_float(y,7*16,mul,4,3);//��ʾ����
		}break;
		case 3://��ӦServoPara
		{
			switch(arrow)
			{
				case 0:
				{
					ips114_show_string(x,0,"arm_servo1"); 
					ips114_show_int(y,3*16,arm_angle1,4);
				}break;
				case 1:
				{
					ips114_show_string(x,0,"arm_servo2"); 
					ips114_show_int(y,3*16,arm_angle2,4);
				}break;
				case 2:
				{
					ips114_show_string(x,0,"box_servo"); 
					ips114_show_int(y,3*16,box_angle,4);
				}break;
				case 3:
				{
					ips114_show_string(x,0,"magnet"); 
					ips114_show_int(y,3*16,magnet_state,4);
				}break;
				default:break;
			}
			ips114_show_float(y,7*16,mul,4,3);//��ʾ����
		}break;			
		case 4:break;//��ӦIMUPara,��֧���޸�
		case 5:break;//��ӦElementPara,��֧���޸�
		case 6:
		{
			if(SPEED_ENABLE)
			{
				ips114_show_string(x,0,"Start Sucess!"); 
			}
			else
			{
				ips114_show_string(x,0,"Long press Key3 to start!"); 
			}
			break;
		}
		case 7:
		    DisplayOpenArtPara();
			break;
		case 8:
		{
			DisplayImage();
		}
		default:break;
	}
}

//���Ĳ���
void UI_DatapageKey()
{
	//uint8 key = Get_Key_flag();
	if(KEY_SHORT_PRESS == key_get_state(KEY_1))//   +
	{
		switch(pagenum)//�ж�����һҳ
		{
			case 1://mt9v03x_set_exposure_time
			{
				switch(arrow)//��һ��
				{
					case 0:
						mt9v03X_light += mul;
						mt9v03x_set_exposure_time(mt9v03X_light);
						break;
					//����������ӣ�������һ��ʾ��
					default:break;
				}
			}break;
			case 2://SpeedPara
			{
				switch(arrow)
				{
					case 0:speed_offset += mul;break;
					//����������ӣ�������һ��ʾ��
					default:break;
				}
			}break;
			case 3://ServoPara
			{
				switch(arrow)
				{
					case 0:arm_angle1 += mul;Servo_SetAngle(1,arm_angle1);break;
					case 1:arm_angle2 += mul;Servo_SetAngle(2,arm_angle2);break;
					case 2:box_angle  += mul;Servo_SetAngle(3,box_angle);break;
					case 3:magnet_state = !magnet_state;magnet_set(magnet_state);break;
					default:break;
				}
			}break;
			case 7:
			{
				uart_write_byte(UART_4, 'a');
				openart_bright_scale ++;
				break;
			}
			// .....����ľ��Լ�����������
			default:break;
		}
	}
	if(KEY_SHORT_PRESS == key_get_state(KEY_2))// -
	{
		switch(pagenum)//�ж�����һҳ
		{
			case 1://Mt9v03Para
			{
				switch(arrow)//��һ��
				{
					case 0:
						if(mt9v03X_light>=mul)
							mt9v03X_light -= mul;
						mt9v03x_set_exposure_time(mt9v03X_light);
						break;
					//����������ӣ�������һ��ʾ��
					default:break;
				}
			}break;
			case 2://RightMotorPara
			{
				switch(arrow)
				{
					case 0:speed_offset -= mul;break;
					//����������ӣ�������һ��ʾ��
					default:break;
				}
			}break;
			case 3://ServoPara
			{
				switch(arrow)
				{
					case 0:arm_angle1 -= mul;Servo_SetAngle(1,arm_angle1);break;
					case 1:arm_angle2 -= mul;Servo_SetAngle(2,arm_angle2);break;
					case 2:box_angle  -= mul;Servo_SetAngle(3,box_angle);break;
					case 3:magnet_state = !magnet_state;magnet_set(magnet_state);break;
					default:break;
				}
			}break;
			case 7:
			{
				if(openart_bright_scale>0)
				{
					uart_write_byte(UART_4, 'b');
					openart_bright_scale --;
				}
				break;
			}
			// .....����ľ��Լ�����������
			default:break;
		}
	}
	if(KEY_SHORT_PRESS == key_get_state(KEY_3))//���ı���
    {
        mul = mul / 10;
    }
    if(KEY_SHORT_PRESS == key_get_state(KEY_4))// ȷ�ϸ��Ĳ���
    {
        mul = mul * 10;
    }
	if(KEY_LONG_PRESS == key_get_state(KEY_1))
	{
		buzzer_set_delay(100);
		system_delay_ms(500);
		datapage = 0;
	}
	if(KEY_LONG_PRESS == key_get_state(KEY_3))
	{
		buzzer_set_delay(100);
		system_delay_ms(1500);
		SPEED_ENABLE = true;
		datapage = 0;
	}
	
	key_clear_all_state();
}


void DisplayMain(void)
{
	ips114_show_string(7,0*16,"1.mt9v03X exposure time"); 		
    ips114_show_string(7,1*16,"2.SpeedPara");   	
    ips114_show_string(7,2*16,"3.ServoPara");   	 
	ips114_show_string(7,3*16,"4.IMUPara");  	 
	ips114_show_string(7,4*16,"5.ElementPara");//Ԫ�ز���         	
	ips114_show_string(7,5*16,"6.Start");//���� 
	ips114_show_string(7,6*16,"7.OpenArtPara");//ֹͣ
	ips114_show_string(7,7*16,"8.Show_Image");//ͼ����ʾ
}
void DisplayMt9v03Para(void)
{
	ips114_show_string(7,0*16,"exposure time");       	ips114_show_int(190,0,mt9v03X_light,4);
	ips114_show_string(7,1*16,"white value");			ips114_show_int(190,1*16,find_white_point(mt9v03x_image),3);
}
void DisplayOpenArtPara(void)
{
	ips114_show_string(7,0*16,"OpenArt brightness");    ips114_show_int(190,0,openart_bright_scale,4);
}
void DisplaySpeedPara(void)
{
	ips114_show_string(7,0*16,"speed offset ");      	ips114_show_int(190,0*16,speed_offset,3);
}
void DisplayServoPara(void)
{
	ips114_show_string(7,0*16,"servo1_angle");       	ips114_show_int(190,0,arm_angle1,4);
	ips114_show_string(7,1*16,"servo2_angle");      	ips114_show_int(190,1*16,arm_angle2,4);
    ips114_show_string(7,2*16,"box_angle");      		ips114_show_int(190,2*16,box_angle,4);
	ips114_show_string(7,3*16,"magnet_state");      	ips114_show_int(190,3*16,magnet_state,4);
}
void DisplayIMUPara(void)
{
	ips114_show_string(7,0*16,"pitch_angle");       	ips114_show_float(190,0,Gyro_Angle.Ydata,4,2);
	ips114_show_string(7,1*16,"yaw_angle");      		ips114_show_float(190,1*16,Gyro_Angle.Zdata,4,2);
    ips114_show_string(7,2*16,"roll_angle");      		ips114_show_float(190,2*16,Gyro_Angle.Xdata,4,2);
}
void DisplayElementPara(void)
{
	ips114_show_string(7,0*16,"cross");					ips114_show_int(190,0*16,cross_flag,1);
	ips114_show_string(7,1*16,"roundabout");			ips114_show_int(190,1*16,roundabout_flag,1);
	ips114_show_string(7,2*16,"barrier");				ips114_show_int(190,2*16,BarrierFlag,1);
}

void DisplayStartPara(void)
{
	ips114_show_string(7,0*16,"is_start_enable");		ips114_show_int(190,0*16,SPEED_ENABLE,1);
}

void DisplayImage(void)
{
	if(mt9v03x_finish_flag)
	{
		mt9v03x_finish_flag = 0;
		ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
		show_boder_line();
	}
}






 char strings[20][30] ={
    //һ���˵���ʾ�ַ�
    "back",
    "mt9v03X exposure time",
    "OpenART exposure time",
    "MCX Vision exposure time",
    "arm servo angle set",
    "speed set",

	//1.1
	"back",
	"mt9v03X exposure time",

	//1.2

	//1.3
        
 };

void print_string(uint8 current_index)
{
    
}
void start() { ips114_show_string(0,20,"start:camera image"); }

void m1_0(){

}
void m1_1() {

}
void m1_2() {
}
void m1_3(){

}
void m1_4()
{

}
void m1_5(){

}

void m1_1_0(){}
void m1_1_1(){}

void m1_2_0(){}
void m1_2_1(){}

void m1_3_0(){}
void m1_3_1(){}

void m1_4_0(){}
void m1_4_1(){}
void m1_4_2(){}


void m1_5_0(){}
void m1_5_1(){}

//����һ���ṹ����������������
typedef struct
{
	uint8 current;
	uint8 next;
	uint8 enter;
	void (*current_operation)(void);

}Menu;

Menu table[13] =
{
	// //��ʼ�˵�
	// {0,0,1,start},
	// //1���˵�
	// {1,2,4,m1_0},
	// {2,3,7,one_meue2},
	// {3,1,0,back1},
	// //2.1�˵�
	// {4,5,0,two_meue1},
	// {5,6,0,two_meue2},
	// {6,4,1,back2},
	// //2.2�˵�
	// {7,8,0,two_meue11},
	// {8,9,0,two_meue22},
	// {9,7,1,back22},

};

void Menu_key_set(void)
{
	static int func_index = 0;
	void (*current_operation_index)(void);


	int Get_key_next;
	int Get_key_enter;
	if (Get_key_next == 1)//�ж��Ƿ��� ��һ��ѡ��
	{
		func_index = table[func_index].next;
		//OLED_Clear(); 
	}
	if (Get_key_enter == 1)//�ж��Ƿ��� ȷ��ѡ��
	{
		func_index = table[func_index].enter;
		//OLED_Clear(); 
	}

	current_operation_index = table[func_index].current_operation;
	(*current_operation_index)();


}

