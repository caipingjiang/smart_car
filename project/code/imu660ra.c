#include "zf_common_headfile.h"
#include "imu660ra.h"

gyro_zero_param_t Gyro_Bias;
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
}

#define WINDOW_SIZE 10

float slidingFilter(float newData)
{
    static float buffer[WINDOW_SIZE];
    static int currentIndex = 0;
    static float sum = 0;

    // ���»�������
    sum -= buffer[currentIndex];
    buffer[currentIndex] = newData;
    sum += newData;

    // ���µ�ǰ����
    currentIndex = (currentIndex + 1) % WINDOW_SIZE;

    // ����ƽ��ֵ
    float average = sum / WINDOW_SIZE;

    return average;
}
