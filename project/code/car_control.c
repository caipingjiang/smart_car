#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
#include "my_servo.h"
#include "imu660ra.h"
#include "math.h"
#include "my_servo.h"



//-----------------------------------------------------------------------------------------------
// 函数简介  十字运动控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void cross_move_control()
{
	int16 temp_distance = 0;		//临时距离
	static uint8 cross_card_release_cnt = 0;		//环岛卡片释放次数(到了放置区不管有没有真的放卡片都会加1)
	//Image_Mode = 0;
	static uint8 time = 0;
	static uint8 delay_flag = 0;	//十字刚进入时的延时标志位
	if(cross_flag == 1 && delay_flag == 0)
	{
		delay_flag = 1;	//进入一个就置1，故判断十字后，该部分只会进一次

		buzzer_set_delay(50);
		time = 0;
		Gyro_Angle.Ydata = 0;	//清除零漂
		Image_Mode = 3;
		Control_Mode = 0;
		move(90,30);
		system_delay_ms(500);
		buzzer_set_delay(50);
		Control_Mode = 4;
		move(0,0);
		
		Image_Mode = 0;
		system_delay_ms(20);
		Control_Mode = 7;
		move(90,35);
	}
    else if(cross_flag == 2 && turn_flag == 0)
	{
		Gyro_Angle.Ydata = 0;	//清除零漂
		Image_Mode = 4;	//进入休闲模式，关闭十字判别
		move(0,0);
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
		angle_turn = -cross_dir*90;
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//小于3度才认为转向完成
		{
			Control_Mode = 3;
			system_delay_ms(200);    //等待转向完成
		}

		Control_Mode = 4;
		move(90,20);
		system_delay_ms(400);	//大十字*****************600
		move(0,0);
		if(!uart1_data_arr[0])	//如果十字没有卡片就直接走出来，不再进行边界矫正
		{
			Control_Mode = 4;
			move(-90,15);
			system_delay_ms(600); //先后退一段距离

			move(0,0);
			angle_turn = (-angle_turn+10*cross_dir);
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>10)	//小于3度才认为转向完成
			{
				Control_Mode = 3;
				system_delay_ms(200);    //等待转向完成
			}

			Control_Mode = 1; //边界矫正
			Image_Mode = 2;	
			system_delay_ms(50); //	
			move(90 + cross_dir*90,30);
			while(longest>5)
			{	
				system_delay_ms(50);
			}
			if((cross_dir > 0) ? (MT9V03X_W/2 - index):(index - MT9V03X_W/2) > cross_dir*10)
			{
				Control_Mode = 4;
				move(90 + cross_dir*90, 30);
				system_delay_ms(500);
				move(90,20);
				system_delay_ms(400);
				
				Image_Mode = 3;
				system_delay_ms(20);
				Control_Mode = 0;
				move(90,20);
				system_delay_ms(100);
			}
			
			
			Image_Mode = 0;
			system_delay_ms(50);
			v_x = 0;
			v_y = 30;
			w = 0;
			Control_Mode = 0;
			cross_flag = 0;
			delay_flag = 0;
			return;		//直接退出
		}

		while(isSame(uart1_data_arr[0]))	//如果识别到了有卡片就一直拾取，直到拾取完
		{
			time = 0;
			uart_write_byte(UART_4, '0');
			temp_distance = 0;//临时距离
			do
			{	
				if(uart1_data_arr[0]==0)
				{
					time++;
					if(time>20)	//矫正一直不动超过3s就退出矫正
					{
						Control_Mode = 4;
						while(!uart1_data_arr[0])
						{
							time++;
							if(time>30)
							{
								time = 0;
								break;
							}
							move(90,20);
							system_delay_ms(300);

							move(-90,20);
							system_delay_ms(300);
						}
						move(0,0);
						time = 0;
						break;
					}
				}
				Control_Mode = 2;
				Correct_Mode = 0;
				w = 0;
				system_delay_ms(100);//等待矫正完成
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
			}
			while(temp_distance>10 && isSame(uart1_data_arr[0]));//距离大于30就一直矫正

			//能到这说明距离已经小于30了
			Control_Mode = 4;
			move(0,0);				

			uart_write_byte(UART_4, '0'); 
			system_delay_ms(500);
			// while(uart4_data_arr[1]!=1)
			// {
			// 	system_delay_ms(100);
			// }
			//system_delay_ms(1000);//延时，前面几张给过滤掉
			if(uart4_data_arr[1]==1)        //识别到卡片
			{
				//ips114_show_string(120,(uart4_data_arr[0]-65)*8,(const char*)&uart4_data_arr[0]);
				ips114_show_string(30,60,"b");
				ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
				uart_write_byte(UART_4, '0');  
				while(!('A' <= uart4_data_arr[0] && uart4_data_arr[0] <= 'O')) 
				{
                    system_delay_ms(50);
                } 
				Box_In((char)uart4_data_arr[0],1);
				
			}	

		}
		
		Control_Mode = 4;
		move(-90,15);
		system_delay_ms(200); //***************700大十字	//先后退一段距离

		move(0,0);
		angle_turn = -angle_turn+15*cross_dir;
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//小于3度才认为转向完成
		{
			Control_Mode = 3;
			system_delay_ms(200);    //等待转向完成
		}
		move(0,0);
		Control_Mode = 1;
		move(90+cross_dir*90, 15);
		
		uint8 temp_time = 0;	//临时计数
		//中心捡完卡片后，先边界矫正反向行驶到弧道的开始位置，确保cross_flag = 3时，不会遗漏第一个放置区
		temp_time = 0;
		Image_Mode = 2;
		system_delay_ms(50);	//不可删除，必须得等总钻风刷新一下图片
		while(!(longest<5 && cross_dir*(MT9V03X_W/2 - index)>0))
		{
			system_delay_ms(50);
			temp_time++;
			if(temp_time>40)
			{
				break;
			}
		}
		Control_Mode = 4;
		move(90,10);
		system_delay_ms(500);
		Image_Mode = 1;
		turn_flag = 1;
		system_delay_ms(50);	//不能去除，确保cross_flag被置为3
		move(0,0);
		
	}
	else if(cross_flag == 3)
	{
		uart_write_byte(UART_4, '1');	
		system_delay_ms(2);
		//system_delay_ms(500);
		turn_flag = 0;	//清零上一状态的转向标志
		Control_Mode = 1;
		v_x = cross_dir*15;
		v_y = 0;
		Image_Mode = 1;	//此时进入边界矫正，故需要切换图像处理模式

		
		if(abs(uart1_data_arr[0] - finial_point_2[0])<(20+5-5))	//如果识别到了有卡片就一直拾取，直到拾取完
		{	
			//buzzer_set_delay(50);
			v_x = 0;
			
			buzzer_set_delay(10);
			// move(0,0);
			// Control_Mode = 4;
			// move(90,15);
			// system_delay_ms(200);
			temp_distance = 0;	//临时距离
			time = 0;
			do
			{
				if(uart1_data_arr[0]==0)
				{
					time++;
					Control_Mode = 4;
					move(90,10);
					system_delay_ms(100);
					move(0,20);
					if(time>20)//10
					{
						Control_Mode = 4;
						while(!uart1_data_arr[0])
						{
							time++;
							if(time>25)//45
							{
								time = 0;
								goto Flag0;
								//break;
							}
							move(90,10);
							system_delay_ms(300);

							move(-90,10);
							system_delay_ms(300);
						}
						move(0,0);
						time = 0;
						temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
						break;
					}
				}
				else
				{
					time++;
					temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
					Control_Mode = 2;
					Correct_Mode = 1;
					w = 0;
					system_delay_ms(100);//等待矫正完成	
				}
				// temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				// Control_Mode = 2;
				// Correct_Mode = 1;
				// w = 0;
				// system_delay_ms(50);//等待矫正完成
			}
			while(temp_distance>30);//距离大于30就一直矫正


			//能到这说明距离已经小于30了
			Control_Mode = 4;
			move(0,0);
			time = 0;	

			system_delay_ms(1000);	//过滤掉开头几帧？？？
			while(1)
			{
				if(uart4_data_arr[1]==1)        //识别到卡片
				{
					time = 0;
					while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
					{
						time++;
						if(time>30)
						{
							time = 0;
							goto Flag0;
						}
						system_delay_ms(100);
					}
					//system_delay_ms(1000);
					if('A'<=uart4_data_arr[0] && uart4_data_arr[0] <= 'O')
					{
						Flag0:
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						Box_Out((char)uart4_data_arr[0],1);
						cross_card_release_cnt++;	//记录到放置区停下来的次数

						Control_Mode = 4;  
						if(cross_card_release_cnt>=5)	
						{
							cross_card_releaseFinish = true;

							for(uint8 i = 0; i<4; i++)	//即使识别错误，也可确保最后把所有卡片放完
							{
								if(temp_class_arr[i][1] != 0)
								{
									Box_Out(temp_class_arr[i][0],1);
								}
							}
							if(five_Flag != 0)
							{
								Box_Out(five_class, 1);
							}
						}
						buzzer_set_delay(20);
						move(-90,15);
						system_delay_ms(500);      

						Image_Mode = 1;
						system_delay_ms(20);	//不能去掉，让矫正图像能刷新 sideline_distance，否则sideline_distance==0时会导致v_x = 0,(见my_motor.c里面的roundabout_move函数)
						Control_Mode = 1;
						v_x = cross_dir*(15);
						v_y = 0;
			
						buzzer_set(1);
						system_delay_ms(700);  
						buzzer_set(0);  

						break;
					}
				}	
				else
				{
					time++;
					system_delay_ms(100);
					if(time>20)
					{
						goto Flag0;
						time = 0;
					}
				}
				
			}	
				

		}
	
	}
	else if (cross_flag == 4)
	{
		Gyro_Angle.Ydata = 0;	//清除零漂
		turn_flag = 0;	//清零上次的标志位
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
		Control_Mode = 4;
    	move(0,0);
		system_delay_ms(200);

		Control_Mode = 3;
		v_x = 0;
		v_y = 0;
		angle_turn = -cross_dir * 90;

		Image_Mode = 4;			//转为空闲模式，防止在出十字时误判
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
		{
			Control_Mode = 3;
			system_delay_ms(100);    //等待转向完成
		}
		turn_flag = 1;

		Image_Mode = 3;
		Control_Mode = 0;		//先走一段,不判断十字,确保出十字
		v_x = 0;
		v_y = tracking_speed;
		system_delay_ms(600);
//		Control_Mode = 4;		//先直行一段确保出十字
//		forward();
//		system_delay_ms(2000);
		
		Image_Mode = 0;
		system_delay_ms(300);
		Control_Mode = 0;

		turn_flag = 0;						//走出十字后清零转向标志位
		cross_card_release_cnt = 0;			//清零上次记录状态
		cross_card_releaseFinish = false;	
		memset(temp_class_arr, 0, sizeof(temp_class_arr));	//在出环岛和十字时将记录数组全部清零，即使本次环岛（十字）出错也不影响下次环岛（十字）的记录与判别
		delay_flag = 0;
		uart_write_byte(UART_4, '0');//十字
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
	int16 temp_distance = 0;
	static uint8 roundabout_card_release_cnt = 0;	//环岛放完卡片类别计数
    static uint8 time = 0;
	if(roundabout_flag == 1 && turn_flag==0)
	{
		Gyro_Angle.Ydata = 0;	//清除零漂
		time = 0;
		angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		Image_Mode = 4;
		//system_delay_ms(500);   //等待停车
		move(90-roundabout_dir*30, 30);
        system_delay_ms(900);
		buzzer_set_delay(20);
		move(0,0);
		for(uint8 i= 0; i < 5; i++)
		{
			isSame(uart1_data_arr[0]);
			system_delay_ms(50);
		}
		if(!isSame(uart1_data_arr[0]))	//如果环岛没有卡片就直接走出来，不再进行边界矫正
		{
			Control_Mode = 4;
			move(90 + roundabout_dir*90, 20);
			system_delay_ms(500);
			
			// Control_Mode = 3;
			// move(0,0);
			// angle_turn = roundabout_dir*90;
			// while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
			// {
			// 	Control_Mode = 3;
			// 	system_delay_ms(200);    //等待转向完成
			// }
			
			// Control_Mode = 1;		//横向平移过去
			// Image_Mode = 2;
			// move(0,0);
			// v_x = roundabout_dir*25;
			// system_delay_ms(1800);

			// angle_now = Gyro_Angle.Zdata;
			// move(0,0);
			// angle_turn = -(roundabout_dir*90);
			// while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度就认为转向完成
			// {
			// 	Control_Mode = 3;
			// 	system_delay_ms(200);    //等待转向完成
			// }
			// w = 0;
			// Image_Mode = 0;
			// system_delay_ms(200);
			// Control_Mode = 0;
			// v_x = 0;
			// v_y = 20;
			// roundabout_flag = 0;
			// system_delay_ms(500);
			// v_y = tracking_speed;
			// w = 0;

			Image_Mode = 3;
			system_delay_ms(50);
			Control_Mode = 0;
			v_x = 0;
			system_delay_ms(1200);
			roundabout_flag = 0;
			buzzer_set_delay(50);
			Image_Mode = 0;
			move(0,0);
			//system_delay_ms(1000);
			return;		//直接退出
		}

		
		while(isSame(uart1_data_arr[0]) || uart4_data_arr[1])	//如果识别到了有卡片就一直拾取，直到拾取完
		{	
			time = 0;
			uart_write_byte(UART_4, '0');
			temp_distance = 0;	//临时距离
			do
			{
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
				Control_Mode = 2;
				Correct_Mode = 0;
				w = 0;
				system_delay_ms(50);//等待矫正完成
			}
			while(temp_distance>10 && isSame(uart1_data_arr[0]));//距离大于30就一直矫正
			//system_delay_ms(500); 	//等待几秒让art先进几张图片冲刷一下以前的图片
			Control_Mode = 4;
			move(0,0);
			// while(uart4_data_arr[1]!=1)
			// {
			// 	system_delay_ms(100);
			// }
			// system_delay_ms(1000);//延时，前面几张给过滤掉
			if(uart4_data_arr[1]==1)        //识别到卡片
			{
				//ips114_show_string(200,(uart4_data_arr[0]-65)*8,(const char*)&uart4_data_arr[0]);
				ips114_show_string(30,60,"b");
				//ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
				
				while(!('A' <= uart4_data_arr[0] && uart4_data_arr[0] <= 'O')) 
				{
                    system_delay_ms(100);
                } 
				//ips114_show_string(200,(uart4_data_arr[0]-65)*8,(const char*)&uart4_data_arr[0]);
				// system_delay_ms(1000);
				ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
				Box_In((char)uart4_data_arr[0],1);
			}	

		}
		angle_turn = -(roundabout_dir*180);
        Control_Mode = 3;
		Image_Mode = 1;		//不能去除，因为要更新roundabout_flag标志位
        v_x = 0;
		v_y = 0;
		uart_write_byte(UART_4, '1');
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>8)	//小于3度就认为转向完成
		{
			uart_write_byte(UART_4, '1');
			Control_Mode = 3;
			system_delay_ms(100);    //等待转向完成
		}	//等待转向完成
		uart_write_byte(UART_4, '1');
		Control_Mode = 4;
		move(90,15);
		system_delay_ms(700);	//400
		move(0,0);
        turn_flag = 1;
        
	}
	
	else if(roundabout_flag == 2)
	{
		static int16 near_distance = 20;
		Gyro_Angle.Ydata = 0;	//清除零漂
		time = 0;
		uart_write_byte(UART_4, '1'); 
		turn_flag = 0;	//清零上次的标志位
		Control_Mode = 1;
		v_x = -roundabout_dir*15;
		v_y = 0;
		Image_Mode = 1;	//此时进入边界矫正，故需要切换图像处理模式

		if(roundabout_card_release_cnt==0)
		{
			near_distance = 30;
		}
		else
		{
			near_distance = 20;
		}
		
		if(abs(uart1_data_arr[0] - finial_point_2[0])<near_distance)	//如果识别到了有卡片就一直拾取，直到拾取完
		{	
			
			Image_Mode = 4;
			v_x = 0;
			// system_delay_ms(2000); //先矫正一下车身
			// while(abs(uart1_data_arr[0] - finial_point_2[0])>35)//等待x方向矫正完成
			// {
			// 	Control_Mode = 5;
			// 	system_delay_ms(100);
			// }
			// arm_up();
			// system_delay_ms(1000);
			move(0,0);
			temp_distance = 0;	//临时距离
			do
			{
				if(uart1_data_arr[0]==0)
				{
					
					time++;
					Control_Mode = 4;
					move(90,10);
					system_delay_ms(100);
					move(0,0);
					if(time>15)
					{
						Control_Mode = 4;
						while(!uart1_data_arr[0])
						{
							time++;
							if(time>20)
							{
								time = 0;
								goto Flag1;
								//break;
							}
							move(90,10);
							system_delay_ms(300);

							move(-90,10);
							system_delay_ms(300);
						}
						move(0,0);
						time = 0;
						temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
						//buzzer_set_delay(20);
						break;
					}
				}
				else
				{
					time++;
					temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
					Control_Mode = 2;
					Correct_Mode = 1;
					w = 0;
					system_delay_ms(100);//等待矫正完成	
				}
				
			}
			while(temp_distance>20);//距离大于30就一直矫正


			//能到这说明距离已经小于30了
			Control_Mode = 4;
			move(0,0);		
			
			time = 0;

			system_delay_ms(1000);
			while(1)
			{
				if(uart4_data_arr[1]==1)        //识别到卡片
				{
					time = 0;
					while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
					{
						time++;
						if(time>30)	//如果3s过后还是没有正确数据（此时大概率没有找到矩形，uart4_data_arr[0]为0），就不再等待了
						{
							time = 0;
							goto Flag1;
						}
						system_delay_ms(100);
					}
					//system_delay_ms(1000);
					if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
					{
						system_delay_ms(500);	//过滤掉开头几帧？？？
						Flag1:
						roundabout_card_release_cnt++;	//注意：是到了一个放置区就加1
						ips114_show_int(80,80,roundabout_card_release_cnt,2);
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						Box_Out((char)uart4_data_arr[0],1);
						buzzer_set_delay(50);
						
						Control_Mode = 4;
						
						if(roundabout_card_release_cnt>=4)//(longest < 5 && (roundabout_dir>0?(index < MT9V03X_W/2): (index > MT9V03X_W/2)) && roundabout_card_release_cnt>=4)	
						{
							roundabout_card_releaseFinish = true;
						}
						Control_Mode = 4;  
						move(-90,10);
						system_delay_ms(500);       
						Control_Mode = 1;
						v_x = -roundabout_dir*(10+5);
						v_y = 0;
						Image_Mode = 1;
						system_delay_ms(700);    
						break;
					}
					
				}
				else
				{
					time++;
					system_delay_ms(100);
					if(time>20)
					{
						goto Flag1;
						time = 0;
					}

				}
			}

		}
		
	}
    else if(roundabout_flag == 3)
    {
		roundabout_card_releaseFinish = false;	//清零上一状态

		angle_now = Gyro_Angle.Zdata;
		Control_Mode = 4;
		move(0,0);
		Image_Mode = 4;	//挂起总钻风
		system_delay_ms(200);  //等待停下

        angle_turn = roundabout_dir*90;
        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
        while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//小于5度才认为转向完成
		{
			Control_Mode = 3;
			system_delay_ms(100);    //等待转向完成
		}
        Image_Mode = 1;			//不能去掉，否则无法对roundabout_flag置标志位
        turn_flag = 1;
		system_delay_ms(50);

		//以下，原本在roundabout_flag == 4里
		Control_Mode = 4;	
        move(90, 20);
        system_delay_ms(400);
		Image_Mode = 2;
		Control_Mode = 1;
		v_x = -(roundabout_dir*15);
		system_delay_ms(400);
		move(0,0);
		
    }
	else if(roundabout_flag == 4)
	{
		Gyro_Angle.Ydata = 0;	//清除零漂
		turn_flag = 0;	//清零上次的标志位
		Image_Mode = 2;
		Control_Mode = 1;
		v_x = -(roundabout_dir*15);

		if(abs(uart1_data_arr[0] - finial_point_2[0])<20)	//如果识别到了有卡片就一直拾取，直到拾取完
		{	
			// while(!uart1_data_arr[0])//如果突然没有了，那么就等待没隔100ms再判断一次，直到再次看到（注意这一过程仍有v_x,仍在边界矫正）
			// {
			// 	system_delay_ms(100);
			// }
			move(0,0);
			v_x = 0;
			temp_distance = 0;	//临时距离
			time = 0;
			do
			{
				if(uart1_data_arr[0]==0)
				{
					
					time++;
					Control_Mode = 4;
					move(90,10);
					system_delay_ms(100);
					move(0,0);
					if(time>10)
					{
						Control_Mode = 4;
						while(!uart1_data_arr[0])
						{
							time++;
							if(time>15)
							{
								time = 0;
								goto Flag2;
								//break;
							}
							move(90,10);
							system_delay_ms(300);

							move(-90,10);
							system_delay_ms(300);
						}
						move(0,0);
						time = 0;
						temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
						break;
					}
				}
				else
				{
					time++;
					temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
					Control_Mode = 2;
					Correct_Mode = 1;
					w = 0;
					system_delay_ms(100);//等待矫正完成	
				}

				// temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				// Control_Mode = 2;
				// Correct_Mode = 1;
				// w = 0;
				// system_delay_ms(200);//等待矫正完成
			}
			while(temp_distance>20);//距离大于30就一直矫正

			Control_Mode = 4;
			move(0,0);	
			//能到这说明距离已经小于30了
			Control_Mode = 4;
			move(0,0);		
			
			if(uart4_data_arr[1]==1)        //识别到卡片
			{
				uart_write_byte(UART_4, '1');     
				//system_delay_ms(500);

				while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
				{
					system_delay_ms(100);
				}
				if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
				{
					system_delay_ms(500);	//过滤掉开头几帧？？？
					Flag2:
					ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
					Box_Out((char)uart4_data_arr[0],1);
					//---------确保识别错误的卡片也会被放出来------------
					for(uint8 i = 0; i<4; i++)	//即使识别错误，也可确保最后把所有卡片放完
					{
						if(temp_class_arr[i][1] != 0)
						{
							Box_Out(temp_class_arr[i][0],1);
						}
					}
					if(five_Flag != 0)
					{
						Box_Out(five_class, 1);
					}
					//-----------------------
					Control_Mode = 4;  
					move(-90,10);
					system_delay_ms(500);       
					Control_Mode = 1;
					v_x = roundabout_dir*40;	//30
					v_y = 0;
					Image_Mode = 2;		//不能为1
					system_delay_ms(1200);  //1800  

					
					Control_Mode = 3;
					angle_now = Gyro_Angle.Zdata;
					move(0,0);
					angle_turn = -angle_turn;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>8)	//小于3度就认为转向完成
					{
						Control_Mode = 3;
						system_delay_ms(50);    //等待转向完成
					}
					
					Image_Mode = 0;
					system_delay_ms(20);	//等待把roundabout_flag 置为0
					Control_Mode = 0;
					v_x = 0;
					v_y = tracking_speed;
					w = 0;

					roundabout_card_release_cnt = 0;	//清零上一状态
					roundabout_card_releaseFinish = false;
					memset(temp_class_arr, 0, sizeof(temp_class_arr));	//在出环岛和十字时将记录数组全部清零，即使本次环岛（十字）出错也不影响下次环岛（十字）的记录与判别
					uart_write_byte(UART_4, '0');     
				}
	
			}
			
			
		}
		else
		{
			
		}
		

	}
}

//-----------------------------------------------------------------------------------------------
// 函数简介  始终线发车停车控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
#define MOVE_MODE	0			//到达三大类的移动方式：0为3张卡片都在右测，1为3张卡片都在左侧，2为内外侧都有
static uint8 find_times  = 0;	//起始线识别次数
static uint8 unload_card_cnt = 0;//三大类卡片放置完成计数
static uint8 finish_line_flag = 0;	//是否识别到斑马线标志位
void start_finish_line_control()
{
    if(find_start_finish_line() && !(cross_flag || roundabout_flag))
	{
		if(lose_point_num_L<15 && lose_point_num_R<15)
		{
			find_times++;
			buzzer_set_delay(5);
		}
		
        if(find_times == 1)
        {
			Image_Mode = 3;
			buzzer_set_delay(50);
            system_delay_ms(600);//确保发车成功
            Image_Mode = 0;
        }
        else if(find_times == 2) //第二次识别，开始放卡片
        {	
			finish_line_flag = 1;
			buzzer_set_delay(5);
			uart_write_byte(UART_4, '1'); 
		#if		MOVE_MODE == 0
			angle_turn = -90;
			angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
			
			Control_Mode = 4;
			move(-90,0); 	//先停车
			system_delay_ms(500);

			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//开启边界矫正
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
			{
				Control_Mode = 3;
				system_delay_ms(200);    //等待转向完成
			}
			target_angle = angle_now + angle_turn;
			Control_Mode = 6;
			move(45,15);
			system_delay_ms(300);
			move(0,15);
			
			
			while(1)	//没加总钻风
			{
				uart_write_byte(UART_4, '1');
				if(uart1_data_arr[0]- finial_point_2[0]>0 && uart1_data_arr[0]- finial_point_2[0]<40)
				{
					int16 temp_distance = 0;//临时距离
					do
					{ 	
						Control_Mode = 2;
						Correct_Mode = 1;
						system_delay_ms(100);	//等待矫正完成
						temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					}
					while( temp_distance > 10  || abs(uart1_data_arr[0]- finial_point_2[0]>20));

					Control_Mode = 4;
					move(0,0);

					
					while(uart4_data_arr[1]!=1)
					{
						system_delay_ms(100);
					}
					if(uart4_data_arr[1]==1)        //识别到卡片
					{
						ips114_show_string(30,60,"b");
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//等待art返回分类结果
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
						{
							buzzer_set_delay(30);
							ips114_show_string(30,60,"c");
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							Box_Out((char)uart4_data_arr[0], 0);
							unload_card_cnt++;
						}
						move(0,15);
						Control_Mode = 6;
						system_delay_ms(500);	//确保上一次的位置不会被再次判断

						if(unload_card_cnt>=3)
						{
							Control_Mode = 4;
							Image_Mode = 4;
							move(-90,15);
							system_delay_ms(500);
							move(0,0);
							Control_Mode = 3;
							angle_now = Gyro_Angle.Zdata;
							angle_turn = -angle_turn;
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
							{
								Control_Mode = 3;
								system_delay_ms(200);    //等待转向完成
							}
							system_delay_ms(200);
							move(0,0);
							Control_Mode = 7;
							Image_Mode = 3;
							v_y = 50;
							system_delay_ms(1500);
							v_y = 0;
							system_delay_ms(20000);
							
							
						}
						
					}
				}
			}

		#elif 	MOVE_MODE == 1

			angle_turn = 90;
			angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入 
			
			Control_Mode = 4;
			move(-90,0); 	//先停车
			system_delay_ms(500);
			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//开启边界矫正
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
			{
				Control_Mode = 3;
				system_delay_ms(200);    //等待转向完成
			}
			target_angle = angle_now + angle_turn;
			Control_Mode = 6;
			move(135,15);
			system_delay_ms(300);
			move(180,15);
			
			
			while(1)	//没加总钻风
			{
				uart_write_byte(UART_4, '1');
				if(uart1_data_arr[0]- finial_point_2[0]<0 && uart1_data_arr[0]- finial_point_2[0]<-40)
				{
					int16 temp_distance = 0;//临时距离
					do
					{ 	
						Control_Mode = 2;
						Correct_Mode = 1;
						system_delay_ms(100);	//等待矫正完成
						temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					}
					while( temp_distance > 10  || abs(uart1_data_arr[0]- finial_point_2[0]>20));

					Control_Mode = 4;
					move(0,0);

					
					while(uart4_data_arr[1]!=1)
					{
						system_delay_ms(100);
					}
					if(uart4_data_arr[1]==1)        //识别到卡片
					{
						ips114_show_string(30,60,"b");
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//等待art返回分类结果
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
						{
							buzzer_set_delay(30);
							ips114_show_string(30,60,"c");
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							Box_Out((char)uart4_data_arr[0], 0);
							unload_card_cnt++;
						}
						move(180,15);
						Control_Mode = 6;
						system_delay_ms(500);	//确保上一次的位置不会被再次判断

						if(unload_card_cnt>=3)
						{
							Control_Mode = 4;
							Image_Mode = 4;
							move(-90,15);
							system_delay_ms(500);
							move(0,0);
							Control_Mode = 3;
							angle_now = Gyro_Angle.Zdata;
							angle_turn = -angle_turn;
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
							{
								Control_Mode = 3;
								system_delay_ms(200);    //等待转向完成
							}
							system_delay_ms(200); 
							move(0,0);
							Control_Mode = 7;
							Image_Mode = 3;
							v_y = 50;
							system_delay_ms(1500);
							v_y = 0;
							system_delay_ms(20000);
							
						}
						
					}
				}
			}
			
		#elif 	MOVE_MODE == 2	
		
			static uint8 cnt_time = 0;
			angle_turn = -90;
			angle_now = Gyro_Angle.Zdata; //将进入环岛前的角度传入
			Image_Mode = 2;	
			//先停车

			Control_Mode = 4;
			move(-90,0); 
			system_delay_ms(500);

			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//开启边界矫正
			uart_write_byte(UART_4, '1');
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
			{
				Control_Mode = 3;
				system_delay_ms(100);    //等待转向完成
				uart_write_byte(UART_4, '1');
			}
			target_angle = angle_now + angle_turn;
			//Control_Mode = 6;
			Control_Mode = 1;
			move(0,15);
			
			
			
			while(1)	//没加总钻风
			{
				uart_write_byte(UART_4, '1');
				system_delay_ms(50);
				cnt_time++;
				if(cnt_time>80 && unload_card_cnt<3)	//横向滑行时间大于5s,不管拣了多少张，直接180度转向对面在平移拣卡片
				{
					angle_turn = -180;
					angle_now = Gyro_Angle.Zdata;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
					{
						Control_Mode = 3;
						system_delay_ms(200);    //等待转向完成
					}
					Image_Mode = 2;
					Control_Mode = 4;
					move(-90,20);
					system_delay_ms(400);
					Control_Mode = 1;
					target_angle = angle_now + angle_turn;
					move(0,15);
					cnt_time = 0;
				}
				if(cnt_time>90 || unload_card_cnt>=3)
				{
					move(0,0);
					angle_turn = -90;
					angle_now = Gyro_Angle.Zdata;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//小于3度才认为转向完成
					{
						Control_Mode = 3;
						system_delay_ms(200);    //等待转向完成
					}
					cnt_time = 0;
					Image_Mode = 3;
					move(0,0);
					system_delay_ms(50);
					Control_Mode = 0;
					move(90,50);
					system_delay_ms(2000);
					Control_Mode = 4;
					move(0,0);
					system_delay_ms(20000);
					finish_line_flag = 0;
					break;
				}

				if(uart1_data_arr[0]- finial_point_2[0]>0 && uart1_data_arr[0]- finial_point_2[0]<40)//if(abs(uart1_data_arr[0]- finial_point_2[0]<20))
				{
					int16 temp_distance = 0;//临时距离
					do
					{ 	
						if(uart1_data_arr[0] == 0)
						{
							Control_Mode = 4;
							move(90, 5);
						}
						else
						{
							Control_Mode = 2;
							Correct_Mode = 1;
						}
						
						system_delay_ms(100);	//等待矫正完成
						temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					}
					while( temp_distance > 10  || abs(uart1_data_arr[0]- finial_point_2[0]>20));
					Control_Mode = 4;
					move(0,0);
					buzzer_set_delay(100);
					
					while(uart4_data_arr[1]!=1)
					{
						system_delay_ms(100);
					}
					if(uart4_data_arr[1]==1)        //识别到卡片
					{
						ips114_show_string(30,60,"b");
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//等待art返回分类结果
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
						{
							buzzer_set_delay(30);
							ips114_show_string(30,60,"c");
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							Box_Out((char)uart4_data_arr[0], 0);
							unload_card_cnt++;
						}
						Image_Mode = 2;
						Control_Mode = 4;
						move(-90,20);
						system_delay_ms(400);
						Control_Mode = 1;
						move(0,15);
						system_delay_ms(500);	//确保上一次的位置不会被再次判断

						
					}
				}
			}


		

		#endif
			
		}
		else if(find_times == 3) //第二次识别就停车,开始放卡片
        {
			buzzer_set_delay(1000);
			Control_Mode = 4;
			move(0, 0);
		}
    }
}


//-----------------------------------------------------------------------------------------------
// 函数简介  通过分析OpenART传回来的数据来控制小车运动
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  ART_control用于赛道两边的拣卡片
//-----------------------------------------------------------------------------------------------
int16 ref_point_L[2] = {50, 200};		//计算距离的左参考点
int16 ref_point_R[2] = {270, 200};		//计算距离的右参考点
int16 pos_cor_distance = 30;			//position矫正的距离范围	
void ART_control()
{
	static uint8 art_turn_flag = 0;
	static uint8 time = 0; 
	if(packge1_finish_flag && !(cross_flag || roundabout_flag) && !finish_line_flag)	
	{
		switch (uart1_data_arr[3])	//correct_flag
		{
			case 0:break;	//未检测到卡片或卡片的距离未小于设定值
			case 1://转弯和矫正卡片
			{
				uart_write_byte(UART_4, '0'); 
				int16 temp_distance_L = distance(uart1_data_arr[0], uart1_data_arr[1], ref_point_L[0], ref_point_L[1]);
				int16 temp_distance_R = distance(uart1_data_arr[0], uart1_data_arr[1], ref_point_R[0], ref_point_R[1]);
				int16 short_diatance = (temp_distance_L<temp_distance_R?temp_distance_L:temp_distance_R);
				if(short_diatance < 80)//if(uart1_data_arr[2]<150+20)
				{
									
					int8 temp_slope = Slope;

					Image_Mode = 2;	//挂起总钻风，防止误判
					//停车
					Control_Mode = 4;
					move(0,0);
					//system_delay_ms(1000);	

					//90度转向
					angle_now = Gyro_Angle.Zdata;

					if(temp_distance_L < temp_distance_R)angle_turn = 90;
					else angle_turn = -90;
					// if(uart1_data_arr[0]<160)angle_turn = 90;
					// else angle_turn = -90;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//小于3度才认为转向完成
					{
						Control_Mode = 3;
						system_delay_ms(50);    //等待转向完成
					}
					
					
					
					//进入卡片矫正
					time = 0;//清零上次值
					while( !uart1_data_arr[0] )//先确保转弯后矫正前能看到卡片
					{
						
						if(time>30)	//如果1.5秒过后还没看到卡片就原路回转
						{
							time = 0;
							angle_turn = 0;
							move(0,0);
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//小于3度就认为转向完成
							{
								Control_Mode = 3;
								system_delay_ms(200);    //等待转向完成
							}

							w = 0;
							Image_Mode = 0;
							system_delay_ms(50);
							Control_Mode = 0;
							v_y = tracking_speed;
							w = 0;
							return;
						}

						Image_Mode = 2;
						Control_Mode = 1;
						if(angle_turn>0)v_x = 25;
						else v_x = -25;
						system_delay_ms(50);
						time += 1;
					}
					

					uint8 temp_cnt = 0;		//记录本次卡片拾取次数，如果本次卡片大于5次还没有拾取上来，就不拣卡片了
					bool is_number = false;		//是否把字母误识别为卡片
					while(uart1_data_arr[0])	//如果识别到了有卡片就一直拾取，直到拾取完
					{
						int16 temp_distance = 0;//临时距离
						time = 0;
						do
						{	
							//此判断加上去是为了解决转向后卡片坐标却为0，导致矫正时v_x和v_y也为零而一直不动的尴尬情况，这种情况一般可能是由于把黑影误识别了卡片
							if(!isSame(uart1_data_arr[0]))
							{
								time++;
								if(time>40)	//矫正一直不动超过2s就退出矫正
								{
									time = 0;
									break;
								}
							}
							
							temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
							Control_Mode = 2;
							Correct_Mode = 0;
							// ips114_show_int(188,20,uart1_data_arr[0],3);
							// ips114_show_int(188,40,uart1_data_arr[1],3);
							w = 0;
							system_delay_ms(50);//等待矫正完成
							uart_write_byte(UART_4, '0');     
						}
						while(temp_distance>pos_cor_distance);//距离大于30就一直矫正
						

						//能到这说明距离已经小于30了
						Control_Mode = 4;
						move(0,0);				
						if(uart4_data_arr[1]==1)        //识别到卡片
						{
							uart_write_byte(UART_4, '0');     
							//system_delay_ms(1000);

							if(uart4_data_arr[1]==1)
							{
								bool isOK = Box_In((char)uart4_data_arr[0],0);
								temp_cnt++;
								
								ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
								
								if(isOK)
								{
									temp_cnt = 0;
									pos_cor_distance = 30; //复位常规矫正距离
									break;
								}
								if(temp_cnt>=1)	//如果第一次未拣成功，后面的的矫正精度就给高一点
								{
									pos_cor_distance = 10;
								}
								if(temp_cnt>=3)//如果本次卡片大于5次还没有拾取上来或者已经拾取上来了一张，就不拣卡片了
								{
									temp_cnt = 0;
									if(!isOK)
									{
										is_number = true;
										pos_cor_distance = 30;
									}
									break;
								}
								
							}
							
						}

					}

					if(abs(temp_slope) > 15 || is_number)	//如果卡片所处的弯道很急，那么在转弯前先校正车身与赛道边界垂直
					{
						Control_Mode = 4;
						move(-90, 20);
						system_delay_ms(200);
						move(0,0);
						Image_Mode = 2;
						system_delay_ms(50);
						Control_Mode = 1;
						target_y = 480;
						system_delay_ms(400);	//600

						
						Control_Mode = 4;
						target_y = 430;
						// move(90, 15);
						// system_delay_ms(300);
						move(0,0);

					}

					
					if(!is_number)
					{
						angle_turn = 0;
						while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//小于3度就认为转向完成
						{
							Control_Mode = 3;
							system_delay_ms(100-50);    //等待转向完成
						}
					}
					else
					{
						angle_now = Gyro_Angle.Zdata;
						if(angle_turn>0)angle_turn = -90+3;		//如果卡片在左边，就加上负角度补偿，以便能看到环岛
						else if(angle_turn<0)angle_turn = 90-3;	//如果卡片在右边，就加上正角度补偿，以便能看到环岛
						while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>2)
						{
							Control_Mode = 3;
							v_x = 0; v_y = 0;
							system_delay_ms(100);    //等待转向完成
						}
					}
					

					//复位循迹
					Image_Mode = 0;
					Control_Mode = 4;
					move(0,0);
					system_delay_ms(500);

					
					if(is_number)
					{
						is_number = false;
						Control_Mode = 7;
						v_x = 0;
						v_y = 20;
					}
					else
					{
						Control_Mode = 0;
						v_y = 30;
					}
					w = 0;
					
					Gyro_Angle.Ydata = 0;	//清除零漂
					break;
				}

				
			}
			
		}

	}
	
}

//-----------------------------------------------------------------------------------------------
// 函数简介  坡道运动控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void ramp_control()
{
	if(Gyro_Angle.Ydata<-10)//if(imu660ra_gyro_y<-500)
	{
		target_angle = Gyro_Angle.Zdata;
		Control_Mode = 6;
		Image_Mode = 4;
		move(-90,20);
		system_delay_ms(700);
		move(0,30);
		system_delay_ms(600);
		move(90,50);
		system_delay_ms(1700);
		move(180,30);
		system_delay_ms(800);
		move(0,0);
		Image_Mode = 0;
		system_delay_ms(50);
		Control_Mode = 0;
		v_x = 0;
		w = 0;
		//tracking_speed = 60;
		
	}
}


//-----------------------------------------------------------------------------------------------
// 函数简介  障碍物检测及控制
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
#define barrier_width_limit1	3200	//判断障碍物的宽度限制，小于此值认为肯能有障碍
#define barrier_width_limit2	1000
#define barrier_slope_limit		20		//判断障碍物的斜率限制，斜率绝对值必须小于此值才能进行判断
#define diff_limit				20		//差值限制
#define var_limit1				8000	//边线方差限制1
#define var_limit2				500		//边线方差限制2
void barrier_control()
{
	static uint16 sum_L = 0, sum_R = 0;		//求和
	static uint8 mean_L = 0, mean_R = 0;	//均值
	static uint16 var_L = 0, var_R = 0;		//方差

	if(Control_Mode == 0 && !(cross_flag||roundabout_flag)) //&& find_times == 1
	{
		if(track_wide < barrier_width_limit1 
		&& track_wide > barrier_width_limit2
		&& abs(Slope) < barrier_slope_limit
		&& longest < 10
		&& lose_point_num_L<20
		&& lose_point_num_R<20)
		{
			if(curvity_calculate(boder_L,&longest) > var_limit1 && curvity_calculate(boder_R,&longest) < var_limit2 )//if(boder_L[70] - boder_L[80] > diff_limit && abs(boder_R[70] - boder_R[80])<10)
			{
				//target_slope = 15;
				//v_x = 20; 
				target_angle = Gyro_Angle.Zdata;
				Image_Mode = 4;
				Control_Mode = 6;
				move(-90,30);
				system_delay_ms(300);
				move(0,20);
				system_delay_ms(500);
				move(90,30);
				system_delay_ms(1000);
				move(180,20);
				system_delay_ms(500);
				v_y = tracking_speed;
				v_x = 0;
				Image_Mode = 0;
				system_delay_ms(50);
				Control_Mode = 0;
			}
			else if(curvity_calculate(boder_L,&longest) < var_limit2 && curvity_calculate(boder_R,&longest) > var_limit1)//else if(boder_R[80] - boder_R[90] < -(diff_limit) && abs(boder_L[80] - boder_L[90])<10)
			{
				target_angle = Gyro_Angle.Zdata;
				Image_Mode = 4;
				Control_Mode = 6;
				move(-90,30);
				system_delay_ms(300);
				move(180,20);
				system_delay_ms(500);
				move(90,30);
				system_delay_ms(1000);
				move(0,20);
				system_delay_ms(500);
				v_y = tracking_speed;
				v_x = 0;
				Image_Mode = 0;
				system_delay_ms(50);
				Control_Mode = 0;
			}
			else
			{
				// buzzer_set_delay(500);
			}
			
		}
//		ips114_show_int(50,30,boder_L[80] - boder_L[90], 3);
//		ips114_show_int(50,50,boder_R[80] - boder_R[90], 3);
	} 
	
}