#include "zf_common_headfile.h"
#include "my_image.h"
#include "my_moter.h"
#include "imu660ra.h"

//-----------------------------------------------------------------------------------------------
// �������  ʮ���˶�����
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
void cross_move_control()
{
    if(cross_flag == 2 && turn_flag==0)
	{
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
		system_delay_ms(1000);
		Control_Mode = 3;
		angle_turn = -abs(Slope)/Slope*90;
		system_delay_ms(1000);	//�ȴ�ת�����
		if(uart1_data_arr[3]==1)        //ʶ�𵽿�Ƭ
		{
			while(!&uart1_data_arr[4])
			{
			position_correct();     //�ȴ�ͼƬ�������
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
		
		angle_turn *= -1;	//����ת180��
		system_delay_ms(1000); //�ȴ�ת����
		turn_flag = 1;
		Control_Mode = 1;
		v_x = abs(Slope)/Slope*20;
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
		if(index<MT9V03X_W/2)angle_turn = 90;
		else angle_turn = -90;
		system_delay_ms(1000);	//�ȴ�ת�����
		turn_flag = 1;

		Control_Mode = 4;		//��ֱ��һ��ȷ����ʮ��
		forward();
		system_delay_ms(1000);

		v_x = 0;
		v_y = 30;
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
    if(roundabout_flag == 1 && turn_flag==0)
	{
		angle_now = Gyro_Angle.Zdata; //�����뻷��ǰ�ĽǶȴ��� 
    	v_x = 0;
		v_y = 0;
		w = 0;
		Control_Mode = 4;
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
            move(90,30);
            Control_Mode = 4;
            system_delay_ms(600);//ȷ�������ɹ�

            Control_Mode = 0;
        }
        if(find_times == 2) //�ڶ���ʶ���ͣ��
        {
            move(0,0);
		    Control_Mode = 4;
        }
	}
}