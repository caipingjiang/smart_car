#include "zf_common_headfile.h"
#include "imu660ra.h"

gyro_zero_param_t Gyro_Bias;
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
}

#define WINDOW_SIZE 10

float slidingFilter(float newData)
{
    static float buffer[WINDOW_SIZE];
    static int currentIndex = 0;
    static float sum = 0;

    // 更新缓存数组
    sum -= buffer[currentIndex];
    buffer[currentIndex] = newData;
    sum += newData;

    // 更新当前索引
    currentIndex = (currentIndex + 1) % WINDOW_SIZE;

    // 计算平均值
    float average = sum / WINDOW_SIZE;

    return average;
}
