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

// float slidingFilter_v2(slidingFilter_struct* filter_ptr, float newData)
// {

//     // ���»�������
//     filter_ptr->sum -= filter_ptr->buffer[filter_ptr->currentIndex];
//     buffer[currentIndex] = newData;
//     sum += newData;

//     // ���µ�ǰ����
//     currentIndex = (currentIndex + 1) % WINDOW_SIZE;

//     // ����ƽ��ֵ
//     float average = sum / WINDOW_SIZE;

//     return average;
// }
// slidingFilter_struct slidingFilter_1 = {
//     .window_size = 10,
//     .sum = 0,
//     .currentIndex = 0
// };