#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
#include "my_servo.h"
#include "imu660ra.h"
//-----------------------------------------------------------------------------------------------
// 函数简介  十字运动控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void cross_move_control()
{
    if(cross_flag == 2 && turn_flag == 0)
	{
		Image_Mode = 4;	//进入休闲模式，关闭十字判别，放
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);
		Control_Mode = 3;
		angle_turn = -cross_dir*90;
		system_delay_ms(1500);	//等待转向完成
		angle_turn *= -1;	//往回转180度
		system_delay_ms(1500); //等待转向完成
		turn_flag = 1;
		Control_Mode = 1;
		v_x = cross_dir*20;
		Image_Mode = 1;	//此时进入边界矫正，故需要切换图像处理模式
	}
	else if(cross_flag == 3)
	{
		turn_flag = 0;	//清零上次的标志位
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);

		Control_Mode = 3;
		v_x = 0;
		v_y = 0;
		angle_turn = -cross_dir * 90;

		Image_Mode = 4;			//转为空闲模式，防止在出十字时误判
		system_delay_ms(1500);	//等待转向完成
		turn_flag = 1;

		Image_Mode = 3;
		Control_Mode = 0;		//先走一段,不判断十字,确保出十字
		v_x = 0;
		v_y = 30;
		system_delay_ms(2000);
		// Control_Mode = 4;		//先直行一段确保出十字
		// forward();
		// system_delay_ms(2000);
		Control_Mode = 0;

		Image_Mode = 0;
		turn_flag = 0;	//走出十字后清零转向标志位

	}
}


//-----------------------------------------------------------------------------------------------
// 函数简介  环岛运动控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void roundabout_move_control()
{
    if(roundabout_flag == 1 && turn_flag==0)
	{
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		Image_Mode = 4;
		system_delay_ms(500);   //等待停车
		move(90-roundabout_dir*30, 15);
        system_delay_ms(1500);
		angle_turn = -(roundabout_dir*160);

        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
		system_delay_ms(1400);	//等待转向完成
        turn_flag = 1;

        Control_Mode = 1;
		Image_Mode = 1;
		v_x = -(roundabout_dir*20);
        
	}
	else if(roundabout_flag == 2)
	{
		turn_flag = 0;	//清零上次的标志位
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);  //等待停下

        angle_turn = roundabout_dir*90;
        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
        system_delay_ms(1500);  //等待转向完成

        Control_Mode = 4;
        move(90, 10);
        system_delay_ms(1000);
        move(90+roundabout_dir*90, 20);
        system_delay_ms(1000);
        move(0, 0);
        system_delay_ms(1000);
        move(90-roundabout_dir*90, 20);
        system_delay_ms(1500);

        Control_Mode = 3;
        v_x = 0;
        v_y = 0;
        angle_now = Gyro_Angle.Zdata;
        angle_turn = -roundabout_dir*90;
        system_delay_ms(1000);//等待转向完成
        turn_flag = 1;
	}
    else if(roundabout_flag == 3)
    {
        turn_flag = 0;//清零上一状态的标志位
        Control_Mode = 0;
		Image_Mode = 0; 
        v_x = 0;
        v_y = 30;
    }
}

//-----------------------------------------------------------------------------------------------
// 函数简介  始终线发车停车控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void start_finish_line_control()
{
    static uint8 find_times  = 0;	//起始线识别次数
    if(find_start_finish_line())
	{
		find_times++;
        if(find_times == 1)
        {
			Image_Mode = 3;
            system_delay_ms(600);//确保发车成功
            Image_Mode = 0;
        }
        if(find_times == 2) //第二次识别就停车
        {
            move(0,0);
		    Control_Mode = 4;
        }
	}
}

//-----------------------------------------------------------------------------------------------
// 函数简介  通过分析OpenART传回来的数据来控制小车运动
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void ART_control()
{
	static uint8 art_turn_flag = 0;
	
	if(packge1_finish_flag)
	{
		ips114_show_int(40,20,uart1_data_arr[0],4);
		ips114_show_int(40,40,uart1_data_arr[1],4);
		//ips114_show_string(40,60,(const char)data_arr[2]);

		// Control_Mode = 2;
	}
	if((!art_turn_flag) && packge4_finish_flag)
	{
		packge4_finish_flag = 0;
		ips114_show_int(40,60,uart4_data_arr[0],4);
		ips114_show_int(40,80,uart4_data_arr[1],4);
		ips114_show_int(40,80,uart4_data_arr[2],4);
		if(uart4_data_arr[0]>=0)	//x大于图像W/2,认为卡片在赛道的右边
		{
			move(0,0);	//停车
			Control_Mode = 4;
			system_delay_ms(1000);
			angle_now = Gyro_Angle.Zdata;
			angle_turn = -90;
			Control_Mode = 3;
			system_delay_ms(1000);	//等待转向完成
			Control_Mode = 2;	//-------mode = 2------->
			w = 0;	
			system_delay_ms(2500);
			arm_up();
			arm_hang();
			
			angle_now = Gyro_Angle.Zdata;
			angle_turn = 90;
			Control_Mode = 3;
			system_delay_ms(1000);	//等待转向完成
			v_x = 0;v_y = 20;
			Control_Mode = 0;
		}
		else
		{
			move(0,0);
			Control_Mode = 4;
			system_delay_ms(1000);
			angle_now = Gyro_Angle.Zdata;
			angle_turn = 90;
			Control_Mode = 3;
			system_delay_ms(1000);
			Control_Mode = 2;	//mode = 2
			move(0,0);
			system_delay_ms(2500);
			arm_up();
			arm_hang();
			
			angle_now = Gyro_Angle.Zdata;
			angle_turn = -90;
			Control_Mode = 3;
			system_delay_ms(1000);	//等待转向完成
			v_x = 0;v_y = 20;
			Control_Mode = 0;
		}
		//art_turn_flag = 1;
		//system_delay_ms(2000);
		
	}
}