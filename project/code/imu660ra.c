#include "zf_common_headfile.h"
#include "imu660ra.h"
#include "math.h"
#define isZero_Bias		1	//�Ƿ�����Ư��0-�رգ� 1-����
gyro_param_t Gyro_Bias;    //��������Ʈ
gyro_param_t Gyro_Angle;   //������ʵʱ�Ƕ�
gyro_param_t Acc_Angle;
gyro_param_t Fusion_Angle;	//�����ںϺ�Ƕ�
float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;//ת��Ϊ��ÿ���Ľ��ٶ�
float K = 0.1f;	//�����˲�ϵ��

void imu660_zeroBias(void)//��������Ư
{
#if(isZero_Bias)
	if(isZero_Bias)
	{
		Gyro_Bias.Zdata = 0;//��ʼ��
		for (uint16_t i = 0; i < 500; i++)
		{
			imu660ra_get_gyro();//��ȡ���ٶ�
			Gyro_Bias.Zdata += (imu660ra_gyro_transition(imu660ra_gyro_z)*0.005);//�ۼ�������
			system_delay_ms(5);
		}		
	}
	Gyro_Bias.Zdata /= 500;//ȡƽ����
#endif	

}

void my_imu660ra_init()
{
	imu660ra_init();
	Gyro_Angle.Zdata = 0;
	Gyro_Angle.Ydata = 0;
	Gyro_Bias.Zdata = 0;
	Acc_Angle.Xdata = 0;
	Acc_Angle.Ydata = 0;
	Acc_Angle.Zdata = 0;
	Fusion_Angle.Ydata = 0;
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
	tra_gyro_y = imu660ra_gyro_transition(imu660ra_gyro_y);
	Gyro_Angle.Zdata += (tra_gyro_z*0.005-Gyro_Bias.Zdata);
	Gyro_Angle.Ydata += (tra_gyro_y*0.005-Gyro_Bias.Ydata);

	// tra_acc_x = imu660ra_acc_transition(imu660ra_acc_x);
	// tra_acc_z = imu660ra_acc_transition(imu660ra_acc_z);
	// if (imu660ra_acc_z == 0)
	// 	Acc_Angle.Ydata = 90;
    // else
	// 	Acc_Angle.Ydata = atan((float)imu660ra_acc_x/imu660ra_acc_z)*180/3.14;

	// Fusion_Angle.Ydata = K*Acc_Angle.Ydata + (1-K)*Gyro_Angle.Ydata;


}
