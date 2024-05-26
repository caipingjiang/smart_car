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
	Image_Mode = 0;
    if(cross_flag == 2 && turn_flag == 0)
	{
		Image_Mode = 4;	//��������ģʽ���ر�ʮ���б𣬷�
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);
		Control_Mode = 3;
		angle_turn = -cross_dir*90;
		system_delay_ms(1500);	//�ȴ�ת�����
		while(uart1_data_arr[0])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
			{
				Control_Mode = 2;
				w = 0;
				system_delay_ms(2000);//�ȴ��������
				Control_Mode = 4;
				move(0,0);
				if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
					{
						uart_write_byte(UART_4, '0');     
						system_delay_ms(1000);

					while(uart4_data_arr[1]==1)
						{
							ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
							Box_In((char)uart4_data_arr[0],1);
							system_delay_ms(1000);
						}
							
					}
					Control_Mode=4;
				v_x = 0;
				v_y = -20;
				w = 0;
				system_delay_ms(500);
			}
		Control_Mode = 3;
		angle_turn *= -1;	//����ת180��
		system_delay_ms(1500); //�ȴ�ת�����
		turn_flag = 1;
		Control_Mode = 1;
		v_x = cross_dir*20;
		Image_Mode = 1;	//��ʱ����߽����������Ҫ�л�ͼ����ģʽ
	}
	else if(cross_flag == 3)
	{
		turn_flag = 0;	//�����ϴεı�־λ
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);

		Control_Mode = 3;
		v_x = 0;
		v_y = 0;
		angle_turn = -cross_dir * 90;

		Image_Mode = 4;			//תΪ����ģʽ����ֹ�ڳ�ʮ��ʱ����
		system_delay_ms(1500);	//�ȴ�ת�����
		turn_flag = 1;

		Image_Mode = 3;
		Control_Mode = 0;		//����һ��,���ж�ʮ��,ȷ����ʮ��
		v_x = 0;
		v_y = 30;
		system_delay_ms(2000);
		// Control_Mode = 4;		//��ֱ��һ��ȷ����ʮ��
		// forward();
		// system_delay_ms(2000);
		Control_Mode = 0;

		Image_Mode = 0;
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
    if(roundabout_flag == 1 && turn_flag==0)
	{
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		Image_Mode = 4;
		system_delay_ms(500);   //�ȴ�ͣ��
		move(90-roundabout_dir*30, 15);
        system_delay_ms(1500);
		angle_turn = -(roundabout_dir*160);

        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
		system_delay_ms(1400);	//�ȴ�ת�����
        turn_flag = 1;

        Control_Mode = 1;
		Image_Mode = 1;
		v_x = -(roundabout_dir*20);
        
	}
	else if(roundabout_flag == 2)
	{
		turn_flag = 0;	//�����ϴεı�־λ
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);  //�ȴ�ͣ��

        angle_turn = roundabout_dir*90;
        Control_Mode = 3;
        v_x = 0;
		v_y = 0;
        system_delay_ms(1500);  //�ȴ�ת�����

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
        system_delay_ms(1000);//�ȴ�ת�����
        turn_flag = 1;
	}
    else if(roundabout_flag == 3)
    {
        turn_flag = 0;//������һ״̬�ı�־λ
        Control_Mode = 0;
		Image_Mode = 0; 
        v_x = 0;
        v_y = 30;
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
    if(find_start_finish_line())
	{
		find_times++;
        if(find_times == 1)
        {
			Image_Mode = 3;
            system_delay_ms(600);//ȷ�������ɹ�
            Image_Mode = 0;
        }
        if(find_times == 2) //�ڶ���ʶ���ͣ��
        {
            move(0,0);
		    Control_Mode = 4;
        }
	}
}

//-----------------------------------------------------------------------------------------------
// �������  ͨ������OpenART������������������С���˶�
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
extern int16 finial_point[2];
void ART_control()
{
	static uint8 art_turn_flag = 0;
	
	if(packge1_finish_flag)
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
				system_delay_ms(1000);	

				//90��ת��
				angle_now = Gyro_Angle.Zdata;
				if(uart1_data_arr[0]<160)angle_turn = 90;
				else angle_turn = -90;
				Control_Mode = 3;
				system_delay_ms(1500);    //�ȴ�ת�����
				
				
				//���뿨Ƭ����
				while( !uart1_data_arr[0] )//��ȷ��ת������ǰ�ܿ�����Ƭ
				{
					Control_Mode = 4;
					if(angle_turn>0)move(0, 20);
					else move(180, 20);
				}
				
				while(uart1_data_arr[0])	//���ʶ�����п�Ƭ��һֱʰȡ��ֱ��ʰȡ��
				{
					Control_Mode = 2;
					w = 0;
					system_delay_ms(2000);//�ȴ��������
					Control_Mode = 4;
					move(0,0);
					
					int16 temp_distance = 0;//��ʱ����
					temp_distance = sqrt(pow(uart1_data_arr[0] - finial_point[0], 2)+pow(uart1_data_arr[1] - finial_point[1], 2));
					if( temp_distance < 30 ) //С��30����Ϊ�����ɹ����������������Ȼ�ܴ󣬾���Ϊ����ʶ���ˣ���ִ��ʰȡ����
					{
						if(uart4_data_arr[1]==1)        //ʶ�𵽿�Ƭ
						{
							uart_write_byte(UART_4, '0');     
							system_delay_ms(1000);

							while(uart4_data_arr[1]==1)
							{
								ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
								Box_In((char)uart4_data_arr[0],0);
								system_delay_ms(1000);
							}
							
						}
					}
				}

				//��ת
				angle_now = Gyro_Angle.Zdata;
				angle_turn = - angle_turn;
				Control_Mode = 3;
				system_delay_ms(1500); 
				
				//��λѭ��
				Control_Mode = 0;
				v_x = 0;
				v_y = 30;
				w = 0;
				Image_Mode = 0;
	
				break;
				
			}
			
		}

	}
	
}