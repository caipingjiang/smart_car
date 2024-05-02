#include "zf_common_headfile.h"
#include "imu660ra.h"

gyro_zero_param_t Gyro_Bias;    //��������Ʈ
gyro_zero_param_t Gyro_Angle;   //������ʵʱ�Ƕ�
float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;//ת��Ϊ��ÿ���Ľ��ٶ�

void imu660_zeroBias(void)//��������Ư
{
	Gyro_Bias.Zdata = 0;//��ʼ��
	for (uint16_t i = 0; i < 500; i++)
	{
		imu660ra_get_gyro();//��ȡ���ٶ�
		Gyro_Bias.Zdata += (imu660ra_gyro_transition(imu660ra_gyro_z)*0.005);//�ۼ�������
		system_delay_ms(5);
	}
	Gyro_Bias.Zdata /= 500;//ȡƽ����
	
	pit_ms_init(PIT_CH1, 5);//ע��pit����ʱ������Ʈ֮�󣬱�����my_imu660ra_init�����Gyro_Angle.Zdata�������
}

void my_imu660ra_init()
{
	imu660ra_init();
	Gyro_Angle.Zdata = 0;
}
void pit_handler_1()
{           

    //��ֵ�˲�
//    float min=0, max=0, temp_angle;
//	for(uint8 i=0; i<10; i++)
//	{
//		//imu660ra_get_acc();
//		imu660ra_get_gyro();
//		tra_gyro_z = (imu660ra_gyro_transition(imu660ra_gyro_z));

//        (tra_gyro_z>max) ? (max=tra_gyro_z):0;
//		(tra_gyro_z<min) ? (min=tra_gyro_z):0;
//        temp_angle += tra_gyro_z;
//	}
//    tra_gyro_z = (temp_angle - min - max)/8;
	imu660ra_get_acc();
	imu660ra_get_gyro();      
    tra_gyro_z = imu660ra_gyro_transition(imu660ra_gyro_z);//ת��Ϊ��ÿ���Ľ��ٶ�
	Gyro_Angle.Zdata += (tra_gyro_z*0.005-Gyro_Bias.Zdata);
	//ips114_show_float(0,20,Gyro_Angle.Zdata,6,3);�жϲ�Ҫ���κ���ʾ
}

