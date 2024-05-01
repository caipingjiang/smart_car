#include "zf_common_headfile.h"
#include "filter.h"

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
