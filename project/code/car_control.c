#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
#include "my_servo.h"
#include "imu660ra.h"
#include "math.h"
#include "my_servo.h"



//-----------------------------------------------------------------------------------------------
// �������  ʮ���˶�����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
void cross_move_control()
{
	int16 temp_distance = 0;		//��ʱ����
	static uint8 cross_card_release_cnt = 0;		//������Ƭ�ͷŴ���(���˷�����������û����ķſ�Ƭ�����1)
	//Image_Mode = 0;
	static uint8 time = 0;
	static uint8 delay_flag = 0;	//ʮ�ָս���ʱ����ʱ��־λ
	if(cross_flag == 1 && delay_flag == 0)
	{
		delay_flag = 1;	//����һ������1�����ж�ʮ�ֺ󣬸ò���ֻ���һ��

		buzzer_set_delay(50);
		time = 0;
		Gyro_Angle.Ydata = 0;	//�����Ư
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
		Gyro_Angle.Ydata = 0;	//�����Ư
		Image_Mode = 4;	//��������ģʽ���ر�ʮ���б�
		move(0,0);
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
		angle_turn = -cross_dir*90;
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//С��3�Ȳ���Ϊת�����
		{
			Control_Mode = 3;
			system_delay_ms(200);    //�ȴ�ת�����
		}

		Control_Mode = 4;
		move(90,20);
		system_delay_ms(400);	//��ʮ��*****************600
		move(0,0);
		if(!uart1_data_arr[0])	//���ʮ��û�п�Ƭ��ֱ���߳��������ٽ��б߽����
		{
			Control_Mode = 4;
			move(-90,15);
			system_delay_ms(600); //�Ⱥ���һ�ξ���

			move(0,0);
			angle_turn = (-angle_turn+10*cross_dir);
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>10)	//С��3�Ȳ���Ϊת�����
			{
				Control_Mode = 3;
				system_delay_ms(200);    //�ȴ�ת�����
			}

			Control_Mode = 1; //�߽����
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
			return;		//ֱ���˳�
		}

		while(isSame(uart1_data_arr[0]))	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{
			time = 0;
			uart_write_byte(UART_4, '0');
			temp_distance = 0;//��ʱ����
			do
			{	
				if(uart1_data_arr[0]==0)
				{
					time++;
					if(time>20)	//����һֱ��������3s���˳�����
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
				system_delay_ms(100);//�ȴ��������
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
			}
			while(temp_distance>10 && isSame(uart1_data_arr[0]));//�������30��һֱ����

			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);				

			uart_write_byte(UART_4, '0'); 
			system_delay_ms(500);
			// while(uart4_data_arr[1]!=1)
			// {
			// 	system_delay_ms(100);
			// }
			//system_delay_ms(1000);//��ʱ��ǰ�漸�Ÿ����˵�
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
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
		system_delay_ms(200); //***************700��ʮ��	//�Ⱥ���һ�ξ���

		move(0,0);
		angle_turn = -angle_turn+15*cross_dir;
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//С��3�Ȳ���Ϊת�����
		{
			Control_Mode = 3;
			system_delay_ms(200);    //�ȴ�ת�����
		}
		move(0,0);
		Control_Mode = 1;
		move(90+cross_dir*90, 15);
		
		uint8 temp_time = 0;	//��ʱ����
		//���ļ��꿨Ƭ���ȱ߽����������ʻ�������Ŀ�ʼλ�ã�ȷ��cross_flag = 3ʱ��������©��һ��������
		temp_time = 0;
		Image_Mode = 2;
		system_delay_ms(50);	//����ɾ��������õ������ˢ��һ��ͼƬ
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
		system_delay_ms(50);	//����ȥ����ȷ��cross_flag����Ϊ3
		move(0,0);
		
	}
	else if(cross_flag == 3)
	{
		uart_write_byte(UART_4, '1');	
		system_delay_ms(2);
		//system_delay_ms(500);
		turn_flag = 0;	//������һ״̬��ת���־
		Control_Mode = 1;
		v_x = cross_dir*15;
		v_y = 0;
		Image_Mode = 1;	//��ʱ����߽����������Ҫ�л�ͼ����ģʽ

		
		if(abs(uart1_data_arr[0] - finial_point_2[0])<(20+5-5))	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	
			//buzzer_set_delay(50);
			v_x = 0;
			
			buzzer_set_delay(10);
			// move(0,0);
			// Control_Mode = 4;
			// move(90,15);
			// system_delay_ms(200);
			temp_distance = 0;	//��ʱ����
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
					system_delay_ms(100);//�ȴ��������	
				}
				// temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				// Control_Mode = 2;
				// Correct_Mode = 1;
				// w = 0;
				// system_delay_ms(50);//�ȴ��������
			}
			while(temp_distance>30);//�������30��һֱ����


			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);
			time = 0;	

			system_delay_ms(1000);	//���˵���ͷ��֡������
			while(1)
			{
				if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
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
						cross_card_release_cnt++;	//��¼��������ͣ�����Ĵ���

						Control_Mode = 4;  
						if(cross_card_release_cnt>=5)	
						{
							cross_card_releaseFinish = true;

							for(uint8 i = 0; i<4; i++)	//��ʹʶ�����Ҳ��ȷ���������п�Ƭ����
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
						system_delay_ms(20);	//����ȥ�����ý���ͼ����ˢ�� sideline_distance������sideline_distance==0ʱ�ᵼ��v_x = 0,(��my_motor.c�����roundabout_move����)
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
		Gyro_Angle.Ydata = 0;	//�����Ư
		turn_flag = 0;	//�����ϴεı�־λ
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
		Control_Mode = 4;
    	move(0,0);
		system_delay_ms(200);

		Control_Mode = 3;
		v_x = 0;
		v_y = 0;
		angle_turn = -cross_dir * 90;

		Image_Mode = 4;			//תΪ����ģʽ����ֹ�ڳ�ʮ��ʱ����
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
		{
			Control_Mode = 3;
			system_delay_ms(100);    //�ȴ�ת�����
		}
		turn_flag = 1;

		Image_Mode = 3;
		Control_Mode = 0;		//����һ��,���ж�ʮ��,ȷ����ʮ��
		v_x = 0;
		v_y = tracking_speed;
		system_delay_ms(600);
//		Control_Mode = 4;		//��ֱ��һ��ȷ����ʮ��
//		forward();
//		system_delay_ms(2000);
		
		Image_Mode = 0;
		system_delay_ms(300);
		Control_Mode = 0;

		turn_flag = 0;						//�߳�ʮ�ֺ�����ת���־λ
		cross_card_release_cnt = 0;			//�����ϴμ�¼״̬
		cross_card_releaseFinish = false;	
		memset(temp_class_arr, 0, sizeof(temp_class_arr));	//�ڳ�������ʮ��ʱ����¼����ȫ�����㣬��ʹ���λ�����ʮ�֣�����Ҳ��Ӱ���´λ�����ʮ�֣��ļ�¼���б�
		delay_flag = 0;
		uart_write_byte(UART_4, '0');//ʮ��
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
	static uint8 roundabout_card_release_cnt = 0;	//�������꿨Ƭ������
    static uint8 time = 0;
	if(roundabout_flag == 1 && turn_flag==0)
	{
		Gyro_Angle.Ydata = 0;	//�����Ư
		time = 0;
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		Image_Mode = 4;
		//system_delay_ms(500);   //�ȴ�ͣ��
		move(90-roundabout_dir*30, 30);
        system_delay_ms(900);
		buzzer_set_delay(20);
		move(0,0);
		for(uint8 i= 0; i < 5; i++)
		{
			isSame(uart1_data_arr[0]);
			system_delay_ms(50);
		}
		if(!isSame(uart1_data_arr[0]))	//�������û�п�Ƭ��ֱ���߳��������ٽ��б߽����
		{
			Control_Mode = 4;
			move(90 + roundabout_dir*90, 20);
			system_delay_ms(500);
			
			// Control_Mode = 3;
			// move(0,0);
			// angle_turn = roundabout_dir*90;
			// while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
			// {
			// 	Control_Mode = 3;
			// 	system_delay_ms(200);    //�ȴ�ת�����
			// }
			
			// Control_Mode = 1;		//����ƽ�ƹ�ȥ
			// Image_Mode = 2;
			// move(0,0);
			// v_x = roundabout_dir*25;
			// system_delay_ms(1800);

			// angle_now = Gyro_Angle.Zdata;
			// move(0,0);
			// angle_turn = -(roundabout_dir*90);
			// while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ⱦ���Ϊת�����
			// {
			// 	Control_Mode = 3;
			// 	system_delay_ms(200);    //�ȴ�ת�����
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
			return;		//ֱ���˳�
		}

		
		while(isSame(uart1_data_arr[0]) || uart4_data_arr[1])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	
			time = 0;
			uart_write_byte(UART_4, '0');
			temp_distance = 0;	//��ʱ����
			do
			{
				temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_1[0], 2)+pow(uart1_data_arr[1] - finial_point_1[1], 2));
				Control_Mode = 2;
				Correct_Mode = 0;
				w = 0;
				system_delay_ms(50);//�ȴ��������
			}
			while(temp_distance>10 && isSame(uart1_data_arr[0]));//�������30��һֱ����
			//system_delay_ms(500); 	//�ȴ�������art�Ƚ�����ͼƬ��ˢһ����ǰ��ͼƬ
			Control_Mode = 4;
			move(0,0);
			// while(uart4_data_arr[1]!=1)
			// {
			// 	system_delay_ms(100);
			// }
			// system_delay_ms(1000);//��ʱ��ǰ�漸�Ÿ����˵�
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
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
		Image_Mode = 1;		//����ȥ������ΪҪ����roundabout_flag��־λ
        v_x = 0;
		v_y = 0;
		uart_write_byte(UART_4, '1');
		while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>8)	//С��3�Ⱦ���Ϊת�����
		{
			uart_write_byte(UART_4, '1');
			Control_Mode = 3;
			system_delay_ms(100);    //�ȴ�ת�����
		}	//�ȴ�ת�����
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
		Gyro_Angle.Ydata = 0;	//�����Ư
		time = 0;
		uart_write_byte(UART_4, '1'); 
		turn_flag = 0;	//�����ϴεı�־λ
		Control_Mode = 1;
		v_x = -roundabout_dir*15;
		v_y = 0;
		Image_Mode = 1;	//��ʱ����߽����������Ҫ�л�ͼ����ģʽ

		if(roundabout_card_release_cnt==0)
		{
			near_distance = 30;
		}
		else
		{
			near_distance = 20;
		}
		
		if(abs(uart1_data_arr[0] - finial_point_2[0])<near_distance)	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	
			
			Image_Mode = 4;
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
					system_delay_ms(100);//�ȴ��������	
				}
				
			}
			while(temp_distance>20);//�������30��һֱ����


			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);		
			
			time = 0;

			system_delay_ms(1000);
			while(1)
			{
				if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
				{
					time = 0;
					while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
					{
						time++;
						if(time>30)	//���3s������û����ȷ���ݣ���ʱ�����û���ҵ����Σ�uart4_data_arr[0]Ϊ0�����Ͳ��ٵȴ���
						{
							time = 0;
							goto Flag1;
						}
						system_delay_ms(100);
					}
					//system_delay_ms(1000);
					if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
					{
						system_delay_ms(500);	//���˵���ͷ��֡������
						Flag1:
						roundabout_card_release_cnt++;	//ע�⣺�ǵ���һ���������ͼ�1
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
		roundabout_card_releaseFinish = false;	//������һ״̬

		angle_now = Gyro_Angle.Zdata;
		Control_Mode = 4;
		move(0,0);
		Image_Mode = 4;	//���������
		system_delay_ms(200);  //�ȴ�ͣ��

        angle_turn = roundabout_dir*90;
        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
        while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//С��5�Ȳ���Ϊת�����
		{
			Control_Mode = 3;
			system_delay_ms(100);    //�ȴ�ת�����
		}
        Image_Mode = 1;			//����ȥ���������޷���roundabout_flag�ñ�־λ
        turn_flag = 1;
		system_delay_ms(50);

		//���£�ԭ����roundabout_flag == 4��
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
		Gyro_Angle.Ydata = 0;	//�����Ư
		turn_flag = 0;	//�����ϴεı�־λ
		Image_Mode = 2;
		Control_Mode = 1;
		v_x = -(roundabout_dir*15);

		if(abs(uart1_data_arr[0] - finial_point_2[0])<20)	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
		{	
			// while(!uart1_data_arr[0])//���ͻȻû���ˣ���ô�͵ȴ�û��100ms���ж�һ�Σ�ֱ���ٴο�����ע����һ��������v_x,���ڱ߽������
			// {
			// 	system_delay_ms(100);
			// }
			move(0,0);
			v_x = 0;
			temp_distance = 0;	//��ʱ����
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
					system_delay_ms(100);//�ȴ��������	
				}

				// temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point_2[0], 2)+pow(uart1_data_arr[1] - finial_point_2[1], 2));
				// Control_Mode = 2;
				// Correct_Mode = 1;
				// w = 0;
				// system_delay_ms(200);//�ȴ��������
			}
			while(temp_distance>20);//�������30��һֱ����

			Control_Mode = 4;
			move(0,0);	
			//�ܵ���˵�������Ѿ�С��30��
			Control_Mode = 4;
			move(0,0);		
			
			if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
			{
				uart_write_byte(UART_4, '1');     
				//system_delay_ms(500);

				while(!('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O'))
				{
					system_delay_ms(100);
				}
				if('A'<=uart4_data_arr[0] && uart4_data_arr[0]<= 'O')
				{
					system_delay_ms(500);	//���˵���ͷ��֡������
					Flag2:
					ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
					Box_Out((char)uart4_data_arr[0],1);
					//---------ȷ��ʶ�����Ŀ�ƬҲ�ᱻ�ų���------------
					for(uint8 i = 0; i<4; i++)	//��ʹʶ�����Ҳ��ȷ���������п�Ƭ����
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
					Image_Mode = 2;		//����Ϊ1
					system_delay_ms(1200);  //1800  

					
					Control_Mode = 3;
					angle_now = Gyro_Angle.Zdata;
					move(0,0);
					angle_turn = -angle_turn;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>8)	//С��3�Ⱦ���Ϊת�����
					{
						Control_Mode = 3;
						system_delay_ms(50);    //�ȴ�ת�����
					}
					
					Image_Mode = 0;
					system_delay_ms(20);	//�ȴ���roundabout_flag ��Ϊ0
					Control_Mode = 0;
					v_x = 0;
					v_y = tracking_speed;
					w = 0;

					roundabout_card_release_cnt = 0;	//������һ״̬
					roundabout_card_releaseFinish = false;
					memset(temp_class_arr, 0, sizeof(temp_class_arr));	//�ڳ�������ʮ��ʱ����¼����ȫ�����㣬��ʹ���λ�����ʮ�֣�����Ҳ��Ӱ���´λ�����ʮ�֣��ļ�¼���б�
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
// �������  ʼ���߷���ͣ������
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
#define MOVE_MODE	0			//������������ƶ���ʽ��0Ϊ3�ſ�Ƭ�����Ҳ⣬1Ϊ3�ſ�Ƭ������࣬2Ϊ����඼��
static uint8 find_times  = 0;	//��ʼ��ʶ�����
static uint8 unload_card_cnt = 0;//�����࿨Ƭ������ɼ���
static uint8 finish_line_flag = 0;	//�Ƿ�ʶ�𵽰����߱�־λ
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
            system_delay_ms(600);//ȷ�������ɹ�
            Image_Mode = 0;
        }
        else if(find_times == 2) //�ڶ���ʶ�𣬿�ʼ�ſ�Ƭ
        {	
			finish_line_flag = 1;
			buzzer_set_delay(5);
			uart_write_byte(UART_4, '1'); 
		#if		MOVE_MODE == 0
			angle_turn = -90;
			angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
			
			Control_Mode = 4;
			move(-90,0); 	//��ͣ��
			system_delay_ms(500);

			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//�����߽����
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
			{
				Control_Mode = 3;
				system_delay_ms(200);    //�ȴ�ת�����
			}
			target_angle = angle_now + angle_turn;
			Control_Mode = 6;
			move(45,15);
			system_delay_ms(300);
			move(0,15);
			
			
			while(1)	//û�������
			{
				uart_write_byte(UART_4, '1');
				if(uart1_data_arr[0]- finial_point_2[0]>0 && uart1_data_arr[0]- finial_point_2[0]<40)
				{
					int16 temp_distance = 0;//��ʱ����
					do
					{ 	
						Control_Mode = 2;
						Correct_Mode = 1;
						system_delay_ms(100);	//�ȴ��������
						temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					}
					while( temp_distance > 10  || abs(uart1_data_arr[0]- finial_point_2[0]>20));

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
						  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//�ȴ�art���ط�����
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
							angle_turn = -angle_turn;
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
							{
								Control_Mode = 3;
								system_delay_ms(200);    //�ȴ�ת�����
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
			angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
			
			Control_Mode = 4;
			move(-90,0); 	//��ͣ��
			system_delay_ms(500);
			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//�����߽����
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
			{
				Control_Mode = 3;
				system_delay_ms(200);    //�ȴ�ת�����
			}
			target_angle = angle_now + angle_turn;
			Control_Mode = 6;
			move(135,15);
			system_delay_ms(300);
			move(180,15);
			
			
			while(1)	//û�������
			{
				uart_write_byte(UART_4, '1');
				if(uart1_data_arr[0]- finial_point_2[0]<0 && uart1_data_arr[0]- finial_point_2[0]<-40)
				{
					int16 temp_distance = 0;//��ʱ����
					do
					{ 	
						Control_Mode = 2;
						Correct_Mode = 1;
						system_delay_ms(100);	//�ȴ��������
						temp_distance = distance(uart1_data_arr[0], uart1_data_arr[1],finial_point_2[0],finial_point_2[1]);
					}
					while( temp_distance > 10  || abs(uart1_data_arr[0]- finial_point_2[0]>20));

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
						  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//�ȴ�art���ط�����
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
							angle_turn = -angle_turn;
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
							{
								Control_Mode = 3;
								system_delay_ms(200);    //�ȴ�ת�����
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
			angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ���
			Image_Mode = 2;	
			//��ͣ��

			Control_Mode = 4;
			move(-90,0); 
			system_delay_ms(500);

			v_x = 0;
			v_y = 0;
			Image_Mode = 2;		//�����߽����
			uart_write_byte(UART_4, '1');
			while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
			{
				Control_Mode = 3;
				system_delay_ms(100);    //�ȴ�ת�����
				uart_write_byte(UART_4, '1');
			}
			target_angle = angle_now + angle_turn;
			//Control_Mode = 6;
			Control_Mode = 1;
			move(0,15);
			
			
			
			while(1)	//û�������
			{
				uart_write_byte(UART_4, '1');
				system_delay_ms(50);
				cnt_time++;
				if(cnt_time>80 && unload_card_cnt<3)	//������ʱ�����5s,���ܼ��˶����ţ�ֱ��180��ת�������ƽ�Ƽ�Ƭ
				{
					angle_turn = -180;
					angle_now = Gyro_Angle.Zdata;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
					{
						Control_Mode = 3;
						system_delay_ms(200);    //�ȴ�ת�����
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
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>3)	//С��3�Ȳ���Ϊת�����
					{
						Control_Mode = 3;
						system_delay_ms(200);    //�ȴ�ת�����
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
					int16 temp_distance = 0;//��ʱ����
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
						
						system_delay_ms(100);	//�ȴ��������
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
					if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
					{
						ips114_show_string(30,60,"b");
						ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
						  
						while(!('1' <= uart4_data_arr[0] && uart4_data_arr[0] <= '3')) 
						{
                            system_delay_ms(100);
                        }  
						//system_delay_ms(1000);	//�ȴ�art���ط�����
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
						system_delay_ms(500);	//ȷ����һ�ε�λ�ò��ᱻ�ٴ��ж�

						
					}
				}
			}


		

		#endif
			
		}
		else if(find_times == 3) //�ڶ���ʶ���ͣ��,��ʼ�ſ�Ƭ
        {
			buzzer_set_delay(1000);
			Control_Mode = 4;
			move(0, 0);
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
int16 ref_point_L[2] = {50, 200};		//����������ο���
int16 ref_point_R[2] = {270, 200};		//���������Ҳο���
int16 pos_cor_distance = 30;			//position�����ľ��뷶Χ	
void ART_control()
{
	static uint8 art_turn_flag = 0;
	static uint8 time = 0; 
	if(packge1_finish_flag && !(cross_flag || roundabout_flag) && !finish_line_flag)	
	{
		switch (uart1_data_arr[3])	//correct_flag
		{
			case 0:break;	//δ��⵽��Ƭ��Ƭ�ľ���δС���趨ֵ
			case 1://ת��ͽ�����Ƭ
			{
				uart_write_byte(UART_4, '0'); 
				int16 temp_distance_L = distance(uart1_data_arr[0], uart1_data_arr[1], ref_point_L[0], ref_point_L[1]);
				int16 temp_distance_R = distance(uart1_data_arr[0], uart1_data_arr[1], ref_point_R[0], ref_point_R[1]);
				int16 short_diatance = (temp_distance_L<temp_distance_R?temp_distance_L:temp_distance_R);
				if(short_diatance < 80)//if(uart1_data_arr[2]<150+20)
				{
									
					int8 temp_slope = Slope;

					Image_Mode = 2;	//��������磬��ֹ����
					//ͣ��
					Control_Mode = 4;
					move(0,0);
					//system_delay_ms(1000);	

					//90��ת��
					angle_now = Gyro_Angle.Zdata;

					if(temp_distance_L < temp_distance_R)angle_turn = 90;
					else angle_turn = -90;
					// if(uart1_data_arr[0]<160)angle_turn = 90;
					// else angle_turn = -90;
					while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//С��3�Ȳ���Ϊת�����
					{
						Control_Mode = 3;
						system_delay_ms(50);    //�ȴ�ת�����
					}
					
					
					
					//���뿨Ƭ����
					time = 0;//�����ϴ�ֵ
					while( !uart1_data_arr[0] )//��ȷ��ת������ǰ�ܿ�����Ƭ
					{
						
						if(time>30)	//���1.5�����û������Ƭ��ԭ·��ת
						{
							time = 0;
							angle_turn = 0;
							move(0,0);
							while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//С��3�Ⱦ���Ϊת�����
							{
								Control_Mode = 3;
								system_delay_ms(200);    //�ȴ�ת�����
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
					

					uint8 temp_cnt = 0;		//��¼���ο�Ƭʰȡ������������ο�Ƭ����5�λ�û��ʰȡ�������Ͳ���Ƭ��
					bool is_number = false;		//�Ƿ����ĸ��ʶ��Ϊ��Ƭ
					while(uart1_data_arr[0])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
					{
						int16 temp_distance = 0;//��ʱ����
						time = 0;
						do
						{	
							//���жϼ���ȥ��Ϊ�˽��ת���Ƭ����ȴΪ0�����½���ʱv_x��v_yҲΪ���һֱ����������������������һ����������ڰѺ�Ӱ��ʶ���˿�Ƭ
							if(!isSame(uart1_data_arr[0]))
							{
								time++;
								if(time>40)	//����һֱ��������2s���˳�����
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
							system_delay_ms(50);//�ȴ��������
							uart_write_byte(UART_4, '0');     
						}
						while(temp_distance>pos_cor_distance);//�������30��һֱ����
						

						//�ܵ���˵�������Ѿ�С��30��
						Control_Mode = 4;
						move(0,0);				
						if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
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
									pos_cor_distance = 30; //��λ�����������
									break;
								}
								if(temp_cnt>=1)	//�����һ��δ��ɹ�������ĵĽ������Ⱦ͸���һ��
								{
									pos_cor_distance = 10;
								}
								if(temp_cnt>=3)//������ο�Ƭ����5�λ�û��ʰȡ���������Ѿ�ʰȡ������һ�ţ��Ͳ���Ƭ��
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

					if(abs(temp_slope) > 15 || is_number)	//�����Ƭ����������ܼ�����ô��ת��ǰ��У�������������߽紹ֱ
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
						while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>5)	//С��3�Ⱦ���Ϊת�����
						{
							Control_Mode = 3;
							system_delay_ms(100-50);    //�ȴ�ת�����
						}
					}
					else
					{
						angle_now = Gyro_Angle.Zdata;
						if(angle_turn>0)angle_turn = -90+3;		//�����Ƭ����ߣ��ͼ��ϸ��ǶȲ������Ա��ܿ�������
						else if(angle_turn<0)angle_turn = 90-3;	//�����Ƭ���ұߣ��ͼ������ǶȲ������Ա��ܿ�������
						while(abs(Gyro_Angle.Zdata - angle_now - angle_turn)>2)
						{
							Control_Mode = 3;
							v_x = 0; v_y = 0;
							system_delay_ms(100);    //�ȴ�ת�����
						}
					}
					

					//��λѭ��
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
					
					Gyro_Angle.Ydata = 0;	//�����Ư
					break;
				}

				
			}
			
		}

	}
	
}

//-----------------------------------------------------------------------------------------------
// �������  �µ��˶�����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
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
// �������  �ϰ����⼰����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
#define barrier_width_limit1	3200	//�ж��ϰ���Ŀ�����ƣ�С�ڴ�ֵ��Ϊ�������ϰ�
#define barrier_width_limit2	1000
#define barrier_slope_limit		20		//�ж��ϰ����б�����ƣ�б�ʾ���ֵ����С�ڴ�ֵ���ܽ����ж�
#define diff_limit				20		//��ֵ����
#define var_limit1				8000	//���߷�������1
#define var_limit2				500		//���߷�������2
void barrier_control()
{
	static uint16 sum_L = 0, sum_R = 0;		//���
	static uint8 mean_L = 0, mean_R = 0;	//��ֵ
	static uint16 var_L = 0, var_R = 0;		//����

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