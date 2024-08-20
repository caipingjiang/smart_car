#include "zf_common_headfile.h"
#include "menu.h"
#include <math.h>
#include "my_motor.h"

uint8 openart_bright_scale = 20;
//下面的是测试参数，在实际工程中，有其他函数判断得到
uint16 arm_angle1 = 100, arm_angle2 = 40, box_angle = 0+85;//85为偏移量
bool magnet_state = false;
float AngleTh = 30;
uint16 PodaoFlag = 0; 
uint16 BarrierFlag = 0;
uint16 RingFlag = 0;
uint8 datapage = 0;//0：显示ID对应的函数，1：修改arrow对应的参数
float mul = 1;

//用来显示各级菜单
uint8 pagenum = 0;//显示page的数目
int8 arrow = 0;//定义光标所在的行，初始化在第一行


void UI()
{
	if(!datapage)
	{
		UI_Content();//显示ID对应的函数
		UI_ContentKey();//更新ID
	}
	else
	{
		UI_Datapage();  //数据页
        UI_DatapageKey();   //数据按键处理
	}
	if(pagenum!=8)
	{
		DisplayCursor();//光标显示
	}
}


void UI_Content(void)
{
	//ips114_clear();//在显示新一级菜单时，需要清屏
	// 根据pagenum去显示菜单
	switch(pagenum)
    {
        case 0://显示主菜单
		{
			DisplayMain();
		}break;
		case 1://显示总装风曝光参数
		{
			DisplayMt9v03Para();
		}break;
		case 2://显示速度参数
		{
			DisplaySpeedPara();
		}break;
		case 3://显示舵机参数
		{
			DisplayServoPara();
		}break;
		case 4://显示IMU参数
		{
			DisplayIMUPara();
		}break;
		case 5://显示元素参数
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

//返回上一级菜单
uint8 pagenumup(void)
{
	switch(pagenum)
	{
		case 0://在一级菜单
			return 0;
		case 1://在一级菜单
			return 0;
		case 2://在一级菜单
			return 0;
		case 3://在一级菜单
			return 0;
		case 4://在一级菜单
			return 0;
		case 5://在一级菜单
			return 0;
		case 6://在一级菜单
			return 0;
		case 7:
			return 0;
		case 8:	
			return 0;
		default:
			return 0;
	}
}

//进入下一级菜单
//需要判断当前ID：知道在那一页，有些什么参数
//还需要判断光标所在行：知道要进入哪一个变量里面
uint8 pagenumdown(void)
{
	switch(pagenum)
	{
		case 0://在主界面
		{
			switch(arrow)//判断在第几行
			{
				case 0://在第0行---->对应着参数Mt9v03Para
				{
					return 1;//返回Mt9v03Para的ID
				}
				case 1: return 2;//对应SpeedPara
				case 2: return 3;//对应ServoPara
				case 3: return 4;//对应IMUPara
				case 4: return 5;//对应ElemnetPara
				case 5: return 6;//对应StartPara
				case 6: return 7;//对应openartPara
				case 7: return 8;//对应Image
			}
		}break;
		case 1://在Mt9v03Para界面
		{
			return 1;//返回当前界面
			//在该界面下没有下一级，就直接break;
		}break;
		case 2: return 2;		//在SpeedPara界面
		case 3: return 3;		//ServoPara界面
		case 4: return 4;		//IMUPara界面
		case 5://ElemnetPara界面
		{
			switch(arrow)
			{	//标志位，不能更改
				default : return 5;//返回当前界面
			}
		}break;
		
		default:break;
	}
}


void DisplayCursor()//显示光标
{
	ips114_show_string(0,arrow*16,">");//在参数前面显示>
}

//接收按键值，并更新arrow
void UI_ContentKey()
{
	//uint8 key = Get_Key_flag();//获取按键值
    if(KEY_SHORT_PRESS == key_get_state(KEY_1)){//向上 up
        ips114_show_string(0,arrow*16," ");  //需要将当前行的光标隐藏，不然当arrow更新之后，出现两行显示光标
		arrow--;//向上移动，arrow减小
	}
    if(KEY_SHORT_PRESS == key_get_state(KEY_2)){//向下 down
        ips114_show_string(0,arrow*16," ");  arrow++;}//和up同理
	
/**********上面的key1,key2是用来上下移动光标的***********/
/**********下面的key3,key4是用来进入相应的父/子菜单的***********/

    if(KEY_SHORT_PRESS == key_get_state(KEY_3)){//进入子页面  enter
        ips114_clear();//需要将当前显示清屏，用于显示子界面    
		pagenum = pagenumdown();//进入子界面 
		arrow = 0;//从第0行开始
	}
    if(KEY_SHORT_PRESS == key_get_state(KEY_4)){//返回上一个页面 back
        ips114_clear();    
		pagenum = pagenumup();
		arrow = 0;
	}
	if(KEY_LONG_PRESS == key_get_state(KEY_1))//更改参数
	{
		buzzer_set_delay(100);
		system_delay_ms(500);
		ips114_clear();
		   
		datapage = 1;    
		mul = 1;
	}
	
	//对arrow限幅，OLED屏只能显示8行，所以需要限制 0 <= arrow <8
	if(arrow < 0)
		arrow = 7;//意思是：当按下up键，光标一直向上移动，当运动到第一行即arrow=0，
				  //再按下up时，光标直接跳到最后一行，arrow = 7
	else if(arrow >7)
		arrow = 0;

	key_clear_all_state();
}





//显示具体的参数
void UI_Datapage()
{
	uint8 x = 20,y = 190;
	//ips114_clear();
	switch(pagenum)
	{
		case 0:break;//在ID为0的界面没有需要修改的参数
		case 1://对应exposure time
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
			ips114_show_float(y,7*16,mul,4,3);//显示倍率
		}break;
		
		case 2://对应SpeedPara
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
			ips114_show_float(y,7*16,mul,4,3);//显示倍率
		}break;
		case 3://对应ServoPara
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
			ips114_show_float(y,7*16,mul,4,3);//显示倍率
		}break;			
		case 4:break;//对应IMUPara,不支持修改
		case 5:break;//对应ElementPara,不支持修改
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

//更改参数
void UI_DatapageKey()
{
	//uint8 key = Get_Key_flag();
	if(KEY_SHORT_PRESS == key_get_state(KEY_1))//   +
	{
		switch(pagenum)//判断在哪一页
		{
			case 1://mt9v03x_set_exposure_time
			{
				switch(arrow)//哪一行
				{
					case 0:
						mt9v03X_light += mul;
						mt9v03x_set_exposure_time(mt9v03X_light);
						break;
					//其他自行添加，这里做一个示范
					default:break;
				}
			}break;
			case 2://SpeedPara
			{
				switch(arrow)
				{
					case 0:speed_offset += mul;break;
					//其他自行添加，这里做一个示范
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
			// .....后面的就自己根据情况添加
			default:break;
		}
	}
	if(KEY_SHORT_PRESS == key_get_state(KEY_2))// -
	{
		switch(pagenum)//判断在哪一页
		{
			case 1://Mt9v03Para
			{
				switch(arrow)//哪一行
				{
					case 0:
						if(mt9v03X_light>=mul)
							mt9v03X_light -= mul;
						mt9v03x_set_exposure_time(mt9v03X_light);
						break;
					//其他自行添加，这里做一个示范
					default:break;
				}
			}break;
			case 2://RightMotorPara
			{
				switch(arrow)
				{
					case 0:speed_offset -= mul;break;
					//其他自行添加，这里做一个示范
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
			// .....后面的就自己根据情况添加
			default:break;
		}
	}
	if(KEY_SHORT_PRESS == key_get_state(KEY_3))//更改倍率
    {
        mul = mul / 10;
    }
    if(KEY_SHORT_PRESS == key_get_state(KEY_4))// 确认更改参数
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
	ips114_show_string(7,4*16,"5.ElementPara");//元素参数         	
	ips114_show_string(7,5*16,"6.Start");//启动 
	ips114_show_string(7,6*16,"7.OpenArtPara");//停止
	ips114_show_string(7,7*16,"8.Show_Image");//图像显示
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
    //一级菜单显示字符
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

//定义一个结构体包含你想操作内容
typedef struct
{
	uint8 current;
	uint8 next;
	uint8 enter;
	void (*current_operation)(void);

}Menu;

Menu table[13] =
{
	// //开始菜单
	// {0,0,1,start},
	// //1级菜单
	// {1,2,4,m1_0},
	// {2,3,7,one_meue2},
	// {3,1,0,back1},
	// //2.1菜单
	// {4,5,0,two_meue1},
	// {5,6,0,two_meue2},
	// {6,4,1,back2},
	// //2.2菜单
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
	if (Get_key_next == 1)//判断是否按下 下一个选项
	{
		func_index = table[func_index].next;
		//OLED_Clear(); 
	}
	if (Get_key_enter == 1)//判断是否按下 确定选项
	{
		func_index = table[func_index].enter;
		//OLED_Clear(); 
	}

	current_operation_index = table[func_index].current_operation;
	(*current_operation_index)();


}

