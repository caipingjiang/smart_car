#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
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
    if(cross_flag == 2 && turn_flag==0)
	{
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);
		Control_Mode = 3;
		angle_turn = -abs(Slope)/Slope*90;
		system_delay_ms(1000);	//等待转向完成
		if(uart1_data_arr[3]==1)        //识别到卡片
		{
			while(!&uart1_data_arr[4])
			{
			position_correct();     //等待图片矫正完成
			}
			v_x = 0;
			v_y = 0;
			w = 0;
			system_delay_ms(100);
			while(uart1_data_arr[3])
			{
				Box_In(uart1_data_arr[2],1);
			}
			
		}
		
		angle_turn *= -1;	//往回转180度
		system_delay_ms(1000); //等待转向完
		turn_flag = 1;
		Control_Mode = 1;
		v_x = abs(Slope)/Slope*20;
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
		if(index<MT9V03X_W/2)angle_turn = 90;
		else angle_turn = -90;
		system_delay_ms(1000);	//等待转向完成
		turn_flag = 1;

		Control_Mode = 4;		//先直行一段确保出十字
		forward();
		system_delay_ms(1000);

		v_x = 0;
		v_y = 30;
		Control_Mode = 0;
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
            move(90,30);
            Control_Mode = 4;
            system_delay_ms(600);//确保发车成功

            Control_Mode = 0;
        }
        if(find_times == 2) //第二次识别就停车
        {
            move(0,0);
		    Control_Mode = 4;
        }
	}
}