#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
#include "my_servo.h"
#include "imu660ra.h"
#include "math.h"
//-----------------------------------------------------------------------------------------------
// 函数简介  十字运动控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void cross_move_control()
{
	//Image_Mode = 0;
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
		// while(uart1_data_arr[0])	//如果识别到了有卡片就一直拾取，直到拾取完
		// {
		// 	Control_Mode = 2;
		// 	w = 0;
		// 	system_delay_ms(2000);//等待矫正完成
		// 	Control_Mode = 4;
		// 	move(0,0);
		// 	if(uart4_data_arr[1]==1)        //识别到卡片
		// 	{
		// 		uart_write_byte(UART_4, '0');     
		// 		system_delay_ms(1000);

		// 		while(uart4_data_arr[1]==1)
		// 		{
		// 			ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
		// 			Box_In((char)uart4_data_arr[0],1);
		// 			system_delay_ms(1000);
		// 		}					
		// 	}
		// 	Control_Mode=4;
		// 	v_x = 0;
		// 	v_y = -20;
		// 	w = 0;
		// 	system_delay_ms(500);
		// }
		Control_Mode = 3;
		angle_turn *= -1;	//往回转180度
		system_delay_ms(1500); //等待转向完成
		turn_flag = 1;
		Control_Mode = 1;
		v_x = cross_dir*20;
		v_y = 0;
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
		system_delay_ms(1500);
//		Control_Mode = 4;		//先直行一段确保出十字
//		forward();
//		system_delay_ms(2000);
		
		Image_Mode = 0;
		system_delay_ms(500);
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
		Image_Mode = 4;
		system_delay_ms(500);   //等待停车
		move(90-roundabout_dir*30, 15);
        system_delay_ms(1500);
//		while(uart1_data_arr[0])	//如果识别到了有卡片就一直拾取，直到拾取完
//			{
//				Control_Mode = 2;
//				w = 0;
//				system_delay_ms(2000);//等待矫正完成
//				Control_Mode = 4;
//				move(0,0);
//				if(uart4_data_arr[1]==1)        //识别到卡片
//					{
//						uart_write_byte(UART_4, '0');     
//						system_delay_ms(1000);

//					while(uart4_data_arr[1]==1)
//						{
//							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
//							Box_In((char)uart4_data_arr[0],1);
//							system_delay_ms(1000);
//						}
//							
//					}
//			}
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
		Image_Mode = 4;	//挂起总钻风
		system_delay_ms(500);  //等待停下

        angle_turn = roundabout_dir*90;
        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
        system_delay_ms(1500);  //等待转向完成

        Control_Mode = 4;
        move(90, 10);
        system_delay_ms(1000);
//        move(90+roundabout_dir*90, 20);
//        system_delay_ms(1000);
//        move(0, 0);
//        system_delay_ms(1000);
//        move(90-roundabout_dir*90, 20);
//        system_delay_ms(1500);

		Image_Mode = 1;
		Control_Mode = 1;
		v_x = -(roundabout_dir*20);
		system_delay_ms(1000);
		v_x = roundabout_dir*20;
		system_delay_ms(1500);
		
        Control_Mode = 3;
        v_x = 0;
        v_y = 0;
        angle_now = Gyro_Angle.Zdata;
        angle_turn = -roundabout_dir*90;
        system_delay_ms(1500);//等待转向完成
        turn_flag = 1;
	}
    else if(roundabout_flag == 3)
    {
        turn_flag = 0;//清零上一状态的标志位
		Image_Mode = 0; 
		system_delay_ms(100);
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
	static uint8 unload_card_cnt = 0;//三大类卡片放置完成计数
    if(find_start_finish_line())
	{
		find_times++;
        // if(find_times == 1)
        // {
		// 	Image_Mode = 3;
        //     system_delay_ms(600);//确保发车成功
        //     Image_Mode = 0;
        // }
        if(find_times == 1) //第二次识别，开始放卡片
        {
			angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
			angle_turn = -90;
			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//开启边界矫正
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
			{
				Control_Mode = 3;
				system_delay_ms(200);    //等待转向完成
			}
			target_angle = angle_now-90;
			Control_Mode = 6;
			// move(90,10);
			// system_delay_ms(500);


			move(-90,10);
			system_delay_ms(400);
			move(0,20);
			Control_Mode = 1;

			while(1)
			{
				if(mt9v03x_finish_flag)
				{
					if(start_finial_line_car_find() && uart1_data_arr[0])
					{
						move(90,20);
						Control_Mode = 4;
						system_delay_ms(1000);
						move(0,0);

						int16 temp_distance = 0;//临时距离
						do
						{ 	
							Control_Mode = 2;
							Correct_Mode = 1;	
							system_delay_ms(200);	//等待矫正完成
							temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
						}
						while( temp_distance > 30 ); //大于30，就一直矫正；若矫正后距离仍然很大，就认为是误识别了，不执行拾取操作

						//能到这说明已矫正完成	
						if(uart4_data_arr[1]==1)        //识别到卡片
						{
							uart_write_byte(UART_4, '1');     
							system_delay_ms(1000);	//等待art返回分类结果
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
							{
								Box_Out((char)uart4_data_arr[0], 0);
								unload_card_cnt++;
							}
							Control_Mode = 4;
							move(-90,20);
							system_delay_ms(1000);
							if( unload_card_cnt!=3 )
							{	
								move(0,20);
								Control_Mode = 1;
								system_delay_ms(500);	//确保上一次的位置不会被再次判断
							}
							else
							{
								move(180,30);
								Control_Mode = 1;
								system_delay_ms(3000);
								Control_Mode = 4;
								move(0,0);
								system_delay_ms(1000);
								return;
							}
							//system_delay_ms(2500);
						}

					}
				}
				
			}
			

			for(uint8 i = 0; i <-1; i++) //临时去掉不用
			{
				// move(0,20);
				// system_delay_ms(1000);
				// move(0,0);
				// system_delay_ms(500);	//后期可去除，不用延时
				//----------------------------------------------------------------


				//----------------------------------------------------------------
				int16 temp_distance = 0;//临时距离
				do
				{
					temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					Control_Mode = 2;
					Correct_Mode = 1;	
					system_delay_ms(200);	//等待矫正完成
				}
				while( temp_distance > 30 ); //大于30，就一直矫正；若矫正后距离仍然很大，就认为是误识别了，不执行拾取操作

				//能到这说明已矫正完成	
				if(uart4_data_arr[1]==1)        //识别到卡片
				{
					uart_write_byte(UART_4, '1');     
					system_delay_ms(1000);	//等待art返回分类结果
					ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
					if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
					{
						Box_Out((char)uart4_data_arr[0],0);
					}
					
					//system_delay_ms(2500);
				}
			}
			


			// for(uint8 cnt = 0; cnt<3; cnt++)
			// {
			// 	v_x = 20;
			// 	w = 0;
			// 	Control_Mode = 1;	
			// 	if(uart1_data_arr[0])	
			// 	{
			// 		Control_Mode = 5;
			// 		system_delay_ms(1500);//等待x方向矫正完成
			// 		Control_Mode = 2;
			// 		w = 0;
			// 		system_delay_ms(1500);//等待接近卡片完成
			// 		Control_Mode = 4;
			// 		move(0,0);
			// 		system_delay_ms(1000);
			// 		arm_down();
			// 		// if(uart4_data_arr[1]==1)        //识别到卡片
			// 		// {
			// 		// 	uart_write_byte(UART_4, '1');     
			// 		// 	system_delay_ms(500);
			// 		// 	ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
			// 		// 	Box_Out((char)uart4_data_arr[0],0);
			// 		// }
			// 	}
			// 	Control_Mode = 4;
			// 	move(-90,15);
			// 	system_delay_ms(500);//倒车
			// 	if(cnt == 3)
			// 	{
			// 		v_x = 0;
			// 		v_y = 0;
			// 		Control_Mode = 3;
			// 		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
			// 		angle_turn = 90;
			// 		system_delay_ms(1500);
			// 		Image_Mode = 0;
			// 		system_delay_ms(100);
			// 		v_y = 30;
			// 		Control_Mode = 0;
			// 	}
			// }
		}
		else if(find_times == 3) //第二次识别就停车,开始放卡片
        {
			move(0, 0);
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
	static uint8 time = 0; 
	if(packge1_finish_flag)
	{
		switch (uart1_data_arr[3])	//correct_flag
		{
			case 0:break;	//未检测到卡片或卡片的距离未小于设定值
			case 1://转弯和矫正卡片
			{
				Image_Mode = 4;	//挂起总钻风，防止误判
				//停车
				Control_Mode = 4;
				move(0,0);
				//system_delay_ms(1000);	

				//90度转向
				angle_now = Gyro_Angle.Zdata;
				if(uart1_data_arr[0]<160)angle_turn = 90;
				else angle_turn = -90;
				while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
				{
					Control_Mode = 3;
					system_delay_ms(200);    //等待转向完成
				}
				
				
				
				//进入卡片矫正
				time = 0;//清零上次值
				while( !uart1_data_arr[0] )//先确保转弯后矫正前能看到卡片
				{
					
					if(time>60)	//如果三秒过后还没看到卡片就原路回转
					{
						time = 0;
						angle_now = Gyro_Angle.Zdata;
						angle_turn = -angle_turn;
						Control_Mode = 3;
						v_x = 0;
						v_y = 0;
						system_delay_ms(1500);

						v_y = 30;
						w = 0;
						Image_Mode = 0;
						system_delay_ms(50);
						Control_Mode = 0;
						return;
					}

					Image_Mode = 2;
					Control_Mode = 1;
					if(angle_turn>0)v_x = 20;
					else v_x = -20;
					system_delay_ms(50);
					time += 1;
				}
				
				while(uart1_data_arr[0])	//如果识别到了有卡片就一直拾取，直到拾取完
				{
					int16 temp_distance = 0;//临时距离
					do
					{
						temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
						Control_Mode = 2;
						Correct_Mode = 0;
						w = 0;
						system_delay_ms(200);//等待矫正完成
					}
					while(temp_distance>30);//距离大于30就一直矫正


					//能到这说明距离已经小于30了
					Control_Mode = 4;
					move(0,0);				
					if(uart4_data_arr[1]==1)        //识别到卡片
					{
						uart_write_byte(UART_4, '0');     
						system_delay_ms(1000);

						if(uart4_data_arr[1]==1)
						{
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							Box_In((char)uart4_data_arr[0],0);
							//system_delay_ms(1000);
						}
						
					}

				}

				//回转
				angle_now = Gyro_Angle.Zdata;
				angle_turn = - angle_turn;
				while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度就认为转向完成
				{
					Control_Mode = 3;
					system_delay_ms(200);    //等待转向完成
				}
				
				//复位循迹
				Control_Mode = 0;
				v_x = 0;
				v_y = 30;
				w = 0;
				Image_Mode = 0;

				//break;
				
			}
			
		}

	}
	
}