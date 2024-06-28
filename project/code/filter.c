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

//-----------------------------------------------------------------------------------------------
// 函数简介  滑动窗口滤波v2.0
// 参数说明  filter_ptr：slidingFilter_struct的结构体指针
// 返回参数  返回窗口数据均值
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
float slidingFilter_v2(slidingFilter_struct* filter_ptr, float newData)
{

    // 更新缓存数组
    filter_ptr->sum -= filter_ptr->buffer[filter_ptr->currentIndex];
    filter_ptr->buffer[filter_ptr->currentIndex] = newData;
    filter_ptr->sum += newData;

    // 更新当前索引
    filter_ptr->currentIndex = (filter_ptr->currentIndex + 1) % filter_ptr->window_size;

    // 计算平均值
    float average = filter_ptr->sum / filter_ptr->window_size;
    return average;

}
slidingFilter_struct slidingFilter_1 = {
    .window_size = 10,
    .sum = 0,
    .currentIndex = 0
};

bool isSame(int16 newData)
{
    static int16 dataRecord[3] = {0};
    dataRecord[0] = dataRecord[1];
    dataRecord[1] = dataRecord[2];
    dataRecord[2] = newData;
    if(newData == 0 && newData ==  dataRecord[0] && newData ==  dataRecord[1])
        return false;
    else 
        return true;
}