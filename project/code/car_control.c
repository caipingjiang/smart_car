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
		angle_turn *= -1;	//����ת180��
		system_delay_ms(1000); //�ȴ�ת�����
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

}