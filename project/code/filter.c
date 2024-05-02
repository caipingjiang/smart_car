#include "zf_common_headfile.h"
#include "filter.h"

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
