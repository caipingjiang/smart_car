#include "zf_common_headfile.h"
#include "imu660ra.h"

gyro_zero_param_t Gyro_Bias;    //陀螺仪零飘
gyro_zero_param_t Gyro_Angle;   //陀螺仪实时角度
float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;//转换为度每秒后的角速度

void imu660_zeroBias(void)//陀螺仪零漂
{
	Gyro_Bias.Zdata = 0;//初始化
	for (uint16_t i = 0; i < 500; i++)
	{
		imu660ra_get_gyro();//获取角速度
		Gyro_Bias.Zdata += (imu660ra_gyro_transition(imu660ra_gyro_z)*0.005);//累加陀螺仪
		system_delay_ms(5);
	}
	Gyro_Bias.Zdata /= 500;//取平均数
	
	pit_ms_init(PIT_CH1, 5);//注意pit开启时间在零飘之后，崩放在my_imu660ra_init里，否则Gyro_Angle.Zdata会出问题
}

void my_imu660ra_init()
{
	imu660ra_init();
	Gyro_Angle.Zdata = 0;
}
void pit_handler_1()
{           

    //均值滤波
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
    tra_gyro_z = imu660ra_gyro_transition(imu660ra_gyro_z);//转换为度每秒后的角速度
	Gyro_Angle.Zdata += (tra_gyro_z*0.005-Gyro_Bias.Zdata);
	//ips114_show_float(0,20,Gyro_Angle.Zdata,6,3);中断不要放任何显示
}

