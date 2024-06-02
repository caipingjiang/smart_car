#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
#include "my_servo.h"
#include "imu660ra.h"
#include "math.h"




//-----------------------------------------------------------------------------------------------
// �������  ʮ���˶�����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
void cross_move_control()
{
	static bool temp_cnt = false;	//ʮ�����Ŀ�Ƭ�Ƿ����
	int16 temp_distance = 0;//��ʱ����
	//Image_Mode = 0;
    if(cross_flag == 2 && turn_flag == 0)
	{
		Image_Mode = 4;	//��������ģʽ���ر�ʮ���б𣬷�
		move(0,0);
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
		angle_turn = -cross_dir*90;
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
		{
			Control_Mode = 3;
			system_delay_ms(200);    //�ȴ�ת�����
		}

		Control_Mode = 4;
		move(90,10);
		system_delay_ms(500);
		move(0,0);
		while(uart1_data_arr[0])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{
			temp_distance = 0;//��ʱ����
			do
			{		
				Control_Mode = 2;
				Correct_Mode = 0;
				w = 0;
				system_delay_ms(100);//�ȴ��������
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
			}
			while(temp_distance>30);//�������30��һֱ����

			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);				

			while(uart4_data_arr[1]!=1)
			{
				system_delay_ms(100);
			}
			system_delay_ms(1000);//��ʱ��ǰ�漸�Ÿ����˵�
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			{
				ips114_show_string(200,(uart4_data_arr[0]-65)*8,(const char*)&uart4_data_arr[0]);
				ips114_show_string(30,60,"b");
				ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
				uart_write_byte(UART_4, '0');  
				while(!('A' <= uart4_data_arr[0] && uart4_data_arr[0] <= 'O')) 
				{
                    system_delay_ms(100);
                } 
				Box_In((char)uart4_data_arr[0],1);
			}	

		}
		
		Control_Mode = 4;
		move(-90,15);
		system_delay_ms(700); //�Ⱥ���һ�ξ���

		move(0,0);
		angle_turn = -angle_turn-20;
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
		{
			Control_Mode = 3;
			system_delay_ms(200);    //�ȴ�ת�����
		}
		Control_Mode = 4; 
		move(90+cross_dir*90, 10);
		system_delay_ms(700); 

		Image_Mode = 1;
		turn_flag = 1;
		system_delay_ms(50);	//����ȥ����ȷ��cross_flag����Ϊ3
		
	}
	else if(cross_flag == 3)
	{
		turn_flag = 0;	//������һ״̬��ת���־
		Control_Mode = 1;
		v_x = cross_dir*15;
		v_y = 0;
		Image_Mode = 1;	//��ʱ����߽����������Ҫ�л�ͼ����ģʽ

		
		if(abs(uart1_data_arr[0] - finial_point_2[0])<20)	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	

			v_x = 0;
			// system_delay_ms(2000); //�Ƚ���һ�³���
			// while(abs(uart1_data_arr[0] - finial_point_2[0])>35)//�ȴ�x����������
			// {
			// 	Control_Mode = 5;
			// 	system_delay_ms(100);
			// }
			// arm_up();
			// system_delay_ms(1000);
			move(0,0);
			temp_distance = 0;	//��ʱ����
			do
			{
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				Control_Mode = 2;
				Correct_Mode = 1;
				w = 0;
				system_delay_ms(200);//�ȴ��������
			}
			while(temp_distance>30);//�������30��һֱ����


			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);		
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			{
				uart_write_byte(UART_4, '1');     
				system_delay_ms(2000);

				while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
				{
					system_delay_ms(100);
				}
				system_delay_ms(1000);
				if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
				{
					ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
					Box_Out((char)uart4_data_arr[0],1);

					Control_Mode = 4;  
					move(-90,15);
					system_delay_ms(500);       
					Control_Mode = 1;
					v_x = cross_dir*15;
					v_y = 0;
					Image_Mode = 1;
					system_delay_ms(700);    
					
					
					//system_delay_ms(1000);
				}
				
			}		

		}
	
	}
	else if (cross_flag == 4)
	{
		turn_flag = 0;	//�����ϴεı�־λ
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(500);

		Control_Mode = 3;
		v_x = 0;
		v_y = 0;
		angle_turn = -cross_dir * 90;

		Image_Mode = 4;			//תΪ����ģʽ����ֹ�ڳ�ʮ��ʱ����
		system_delay_ms(1000);	//�ȴ�ת�����
		turn_flag = 1;

		Image_Mode = 3;
		Control_Mode = 0;		//����һ��,���ж�ʮ��,ȷ����ʮ��
		v_x = 0;
		v_y = 30;
		system_delay_ms(1500);
//		Control_Mode = 4;		//��ֱ��һ��ȷ����ʮ��
//		forward();
//		system_delay_ms(2000);
		
		Image_Mode = 0;
		system_delay_ms(500);
		Control_Mode = 0;
		turn_flag = 0;	//�߳�ʮ�ֺ�����ת���־λ

	}
	
}


//-----------------------------------------------------------------------------------------------
// �������  �����˶�����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
void roundabout_move_control()
{
	int16 temp_distance = 0;
	static uint8 card_finish_cnt = 0;	//�������꿨Ƭ������
    if(roundabout_flag == 1 && turn_flag==0)
	{
		card_finish_cnt = 0;	//������һ״̬
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		Image_Mode = 4;
		system_delay_ms(500);   //�ȴ�ͣ��
		move(90-roundabout_dir*30, 15);
        system_delay_ms(1500);

		move(0,0);

		while(uart1_data_arr[0])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	
			temp_distance = 0;	//��ʱ����
			do
			{
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
				Control_Mode = 2;
				Correct_Mode = 0;
				w = 0;
				system_delay_ms(200);//�ȴ��������
			}
			while(temp_distance>30);//�������30��һֱ����


			Control_Mode = 4;
			move(0,0);
			while(uart4_data_arr[1]!=1)
			{
				system_delay_ms(100);
			}
			system_delay_ms(1000);//��ʱ��ǰ�漸�Ÿ����˵�
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			{
				ips114_show_string(200,(uart4_data_arr[0]-65)*8,(const char*)&uart4_data_arr[0]);
				ips114_show_string(30,60,"b");
				ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
				uart_write_byte(UART_4, '0');  
				while(!('A' <= uart4_data_arr[0] && uart4_data_arr[0] <= 'O')) 
				{
                    system_delay_ms(100);
                } 
				system_delay_ms(1000);
				Box_In((char)uart4_data_arr[0],1);
			}	

		}
		angle_turn = -(roundabout_dir*180);
        Control_Mode = 3;
		Image_Mode = 1;		//����ȥ������ΪҪ����roundabout_flag��־λ
        v_x = 0;
		v_y = 0;
		system_delay_ms(1400);	//�ȴ�ת�����

		Control_Mode = 4;
		move(90,15);
		system_delay_ms(700);
		move(0,0);
        turn_flag = 1;
        
	}
	else if(roundabout_flag == 2)
	{
		turn_flag = 0;	//�����ϴεı�־λ
		Control_Mode = 1;
		v_x = -roundabout_dir*15;
		v_y = 0;
		Image_Mode = 1;	//��ʱ����߽����������Ҫ�л�ͼ����ģʽ

		if(abs(uart1_data_arr[0] - finial_point_2[0])<20)	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	

			v_x = 0;
			// system_delay_ms(2000); //�Ƚ���һ�³���
			// while(abs(uart1_data_arr[0] - finial_point_2[0])>35)//�ȴ�x����������
			// {
			// 	Control_Mode = 5;
			// 	system_delay_ms(100);
			// }
			// arm_up();
			// system_delay_ms(1000);
			move(0,0);
			temp_distance = 0;	//��ʱ����
			do
			{
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				Control_Mode = 2;
				Correct_Mode = 1;
				w = 0;
				system_delay_ms(200);//�ȴ��������
			}
			while(temp_distance>30);//�������30��һֱ����


			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);		
			
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			{
				uart_write_byte(UART_4, '1');     
				system_delay_ms(2000);

				while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
				{
					system_delay_ms(100);
				}
				//system_delay_ms(1000);
				if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
				{
					ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
					Box_Out((char)uart4_data_arr[0],1);
					card_finish_cnt ++;	//ע�⣺�ǵ���һ���������ͼ�1
					
					Control_Mode = 4;
					
					if(longest < 5 && (roundabout_dir>0?(index < MT9V03X_W/2-30): (index > MT9V03X_W/2+30)) || card_finish_cnt>=4)	
					{
						roundabout_card_finished = true;
					}
					Control_Mode = 4;  
					move(-90,10);
					system_delay_ms(500);       
					Control_Mode = 1;
					v_x = -roundabout_dir*10;
					v_y = 0;
					Image_Mode = 1;
					system_delay_ms(700);    

				}
				
			}		

		}

		
	}
    else if(roundabout_flag == 3)
    {
		roundabout_card_finished = false;	//������һ״̬

		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		Image_Mode = 4;	//���������
		system_delay_ms(500);  //�ȴ�ͣ��

        angle_turn = roundabout_dir*90;
        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
        system_delay_ms(1500);  //�ȴ�ת�����
        Image_Mode = 1;			//����ȥ���������޷���roundabout_flag�ñ�־λ
        turn_flag = 1;
		system_delay_ms(200);

		//���£�ԭ����roundabout_flag == 4��
		Control_Mode = 4;	
        move(90, 10);
        system_delay_ms(1000);
		move(0,0);
		
        
    }
	else if(roundabout_flag == 4)
	{
		turn_flag = 0;	//�����ϴεı�־λ
		
		Image_Mode = 2;
		Control_Mode = 1;
		v_x = -(roundabout_dir*15);

		// while(!uart1_data_arr[0])	//����ȥ��
		// {
		// 	system_delay_ms(100);
		// }
		if(abs(uart1_data_arr[0] - finial_point_2[0])<20)	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	
			// while(!uart1_data_arr[0])//���ͻȻû���ˣ���ô�͵ȴ�û��100ms���ж�һ�Σ�ֱ���ٴο�����ע����һ��������v_x,���ڱ߽������
			// {
			// 	system_delay_ms(100);
			// }
			move(0,0);
			v_x = 0;
			temp_distance = 0;	//��ʱ����
			do
			{
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				Control_Mode = 2;
				Correct_Mode = 1;
				w = 0;
				system_delay_ms(200);//�ȴ��������
			}
			while(temp_distance>30);//�������30��һֱ����

			Control_Mode = 4;
			move(0,0);	
			if(uart4_data_arr[0])	//ֻҪ���п�Ƭ��һֱִ������Ĳ���
			{


				//�ܵ���˵�������Ѿ�С��30��
				Control_Mode = 4;
				move(0,0);		
				
				if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
				{
					uart_write_byte(UART_4, '1');     
					system_delay_ms(2000);

					while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
					{
						system_delay_ms(100);
					}
					system_delay_ms(1000);
					if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
					{
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						Box_Out((char)uart4_data_arr[0],1);

						
						Control_Mode = 4;  
						move(-90,10);
						system_delay_ms(500);       
						Control_Mode = 1;
						v_x = roundabout_dir*30;
						v_y = 0;
						Image_Mode = 2;		//����Ϊ1
						system_delay_ms(1700);    

						
						Control_Mode = 3;
						angle_now = Gyro_Angle.Zdata;
						move(0,0);
						angle_turn = -angle_turn;
						system_delay_ms(1500);	//�ȴ�ת�����
						
						Image_Mode = 0;
						system_delay_ms(200);	//�ȴ���roundabout_flag ��Ϊ0
						Control_Mode = 0;
						v_x = 0;
						v_y = 30;
						w = 0;
						//system_delay_ms(1000);
					}

				}		
			}
			
			
		}

	}
}

//-----------------------------------------------------------------------------------------------
// �������  ʼ���߷���ͣ������
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
void start_finish_line_control()
{
    static uint8 find_times  = 0;	//��ʼ��ʶ�����
	static uint8 unload_card_cnt = 0;//�����࿨Ƭ������ɼ���
    if(find_start_finish_line())
	{
		find_times++;
        // if(find_times == 1)
        // {
		// 	Image_Mode = 3;
        //     system_delay_ms(600);//ȷ�������ɹ�
        //     Image_Mode = 0;
        // }
        if(find_times == 1) //�ڶ���ʶ�𣬿�ʼ�ſ�Ƭ
        {
			angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
			angle_turn = -90;
			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//�����߽����
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
			{
				Control_Mode = 3;
				system_delay_ms(200);    //�ȴ�ת�����
			}
			target_angle = angle_now-90;
			Control_Mode = 6;
			move(0,15);
			// move(90,10);
			// system_delay_ms(500);


			// move(-90,10);
			// system_delay_ms(400);
			// move(0,20);
			// Control_Mode = 1;

			// while(1)//���������
			// {
			// 	if(mt9v03x_finish_flag)
			// 	{
			// 		if(start_finial_line_car_find() && uart1_data_arr[0])
			// 		{
			// 			ips114_show_string(30,60,"a");
			// 			move(90,10);
			// 			Control_Mode = 4;
			// 			system_delay_ms(300);
			// 			move(0,0);

			// 			int16 temp_distance = 0;//��ʱ����
			// 			do
			// 			{ 	
			// 				Control_Mode = 2;
			// 				Correct_Mode = 1;	
			// 				system_delay_ms(200);	//�ȴ��������
			// 				temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
			// 			}
			// 			while( temp_distance > 30 ); //����30����һֱ�������������������Ȼ�ܴ󣬾���Ϊ����ʶ���ˣ���ִ��ʰȡ����

			// 			//�ܵ���˵���ѽ������
			// 			move(0,0);
			// 			Control_Mode = 4;
			// 			system_delay_ms(1000);
			// 			while(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			// 			{
			// 				ips114_show_string(30,60,"b");
			// 				uart_write_byte(UART_4, '1');     
			// 				system_delay_ms(1000);	//�ȴ�art���ط�����
			// 				ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
			// 				if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
			// 				{
			// 					ips114_show_string(30,60,"c");
			// 					ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
			// 					Box_Out((char)uart4_data_arr[0], 0);
			// 					unload_card_cnt++;
			// 				}
			// 				Control_Mode = 4;
			// 				move(-90,10);
			// 				system_delay_ms(500);
			// 				if( unload_card_cnt!=3 )
			// 				{	

			// 					move(0,10);
			// 					Control_Mode = 1;
			// 					system_delay_ms(500);	//ȷ����һ�ε�λ�ò��ᱻ�ٴ��ж�
			// 					break;
			// 				}
			// 				else
			// 				{
			// 					move(180,30);
			// 					Control_Mode = 1;
			// 					system_delay_ms(2000);
			// 					Control_Mode = 4;
			// 					move(0,0);
			// 					system_delay_ms(1000);
			// 					return;
			// 				}
			// 				//system_delay_ms(2500);
			// 			}
						

			// 		}
			// 	}
				
			// }
			
			while(1)	//û�������
			{
				if(uart1_data_arr[0]- finial_point_2[0]>0&& uart1_data_arr[0]- finial_point_2[0]<40)
				{
					int16 temp_distance = 0;//��ʱ����
					do
					{ 	
						Control_Mode = 2;
						Correct_Mode = 1;
						system_delay_ms(100);	//�ȴ��������
						temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					}
					while( temp_distance > 30  && abs(uart1_data_arr[0]- finial_point_2[0]>20));

					Control_Mode = 4;
					move(0,0);

					while(uart4_data_arr[1]!=1)
					{
						system_delay_ms(100);
					}
					if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
					{
						ips114_show_string(30,60,"b");
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						uart_write_byte(UART_4, '1');  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//�ȴ�art���ط�����
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						if('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')
						{
							ips114_show_string(30,60,"c");
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							Box_Out((char)uart4_data_arr[0], 0);
							unload_card_cnt++;
						}
						move(0,10);
						Control_Mode = 6;
						system_delay_ms(500);	//ȷ����һ�ε�λ�ò��ᱻ�ٴ��ж�

						if(unload_card_cnt>=3)
						{
							Control_Mode = 4;
							Image_Mode = 4;
							move(-90,15);
							system_delay_ms(500);
							move(0,0);
							Control_Mode = 3;
							angle_now = Gyro_Angle.Zdata;
							angle_turn = - 90;
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
							{
								Control_Mode = 3;
								system_delay_ms(200);    //�ȴ�ת�����
							}
							system_delay_ms(200);
							move(0,0);
							Control_Mode = 7;
							v_y = 40;
							system_delay_ms(2000);
							v_y = 0;
							system_delay_ms(10000);
							
							
						}
						
					}
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
			// 		system_delay_ms(1500);//�ȴ�x����������
			// 		Control_Mode = 2;
			// 		w = 0;
			// 		system_delay_ms(1500);//�ȴ��ӽ���Ƭ���
			// 		Control_Mode = 4;
			// 		move(0,0);
			// 		system_delay_ms(1000);
			// 		arm_down();
			// 		// if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			// 		// {
			// 		// 	uart_write_byte(UART_4, '1');     
			// 		// 	system_delay_ms(500);
			// 		// 	ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
			// 		// 	Box_Out((char)uart4_data_arr[0],0);
			// 		// }
			// 	}
			// 	Control_Mode = 4;
			// 	move(-90,15);
			// 	system_delay_ms(500);//����
			// 	if(cnt == 3)
			// 	{
			// 		v_x = 0;
			// 		v_y = 0;
			// 		Control_Mode = 3;
			// 		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
			// 		angle_turn = 90;
			// 		system_delay_ms(1500);
			// 		Image_Mode = 0;
			// 		system_delay_ms(100);
			// 		v_y = 30;
			// 		Control_Mode = 0;
			// 	}
			// }
		}
		else if(find_times == 3) //�ڶ���ʶ���ͣ��,��ʼ�ſ�Ƭ
        {
			move(0, 0);
			Control_Mode = 4;
		}
    }
}


//-----------------------------------------------------------------------------------------------
// �������  ͨ������OpenART������������������С���˶�
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  ART_control�����������ߵļ�Ƭ
//-----------------------------------------------------------------------------------------------
void ART_control()
{
	static uint8 art_turn_flag = 0;
	static uint8 time = 0; 
	if(packge1_finish_flag && !(cross_flag || roundabout_flag))	
	{
		switch (uart1_data_arr[3])	//correct_flag
		{
			case 0:break;	//δ��⵽��Ƭ��Ƭ�ľ���δС���趨ֵ
			case 1://ת��ͽ�����Ƭ
			{
				Image_Mode = 4;	//��������磬��ֹ����
				//ͣ��
				Control_Mode = 4;
				move(0,0);
				//system_delay_ms(1000);	

				//90��ת��
				angle_now = Gyro_Angle.Zdata;
				if(uart1_data_arr[0]<160)angle_turn = 90;
				else angle_turn = -90;
				while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
				{
					Control_Mode = 3;
					system_delay_ms(200);    //�ȴ�ת�����
				}
				
				
				
				//���뿨Ƭ����
				time = 0;//�����ϴ�ֵ
				while( !uart1_data_arr[0] )//��ȷ��ת������ǰ�ܿ�����Ƭ
				{
					
					if(time>60)	//����������û������Ƭ��ԭ·��ת
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
				
				while(uart1_data_arr[0])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
				{
					int16 temp_distance = 0;//��ʱ����
					do
					{
						temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
						Control_Mode = 2;
						Correct_Mode = 0;
						w = 0;
						system_delay_ms(200);//�ȴ��������
					}
					while(temp_distance>30);//�������30��һֱ����


					//�ܵ���˵�������Ѿ�С��30��
					Control_Mode = 4;
					move(0,0);				
					if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
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

				//��ת
				angle_now = Gyro_Angle.Zdata;
				angle_turn = - angle_turn;
				while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ⱦ���Ϊת�����
				{
					Control_Mode = 3;
					system_delay_ms(200);    //�ȴ�ת�����
				}
				
				//��λѭ��
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