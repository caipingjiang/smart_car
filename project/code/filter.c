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

//-----------------------------------------------------------------------------------------------
// �������  ���������˲�v2.0
// ����˵��  filter_ptr��slidingFilter_struct�Ľṹ��ָ��
// ���ز���  ���ش������ݾ�ֵ
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
float slidingFilter_v2(slidingFilter_struct* filter_ptr, float newData)
{

    // ���»�������
    filter_ptr->sum -= filter_ptr->buffer[filter_ptr->currentIndex];
    filter_ptr->buffer[filter_ptr->currentIndex] = newData;
    filter_ptr->sum += newData;

    // ���µ�ǰ����
    filter_ptr->currentIndex = (filter_ptr->currentIndex + 1) % filter_ptr->window_size;

    // ����ƽ��ֵ
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