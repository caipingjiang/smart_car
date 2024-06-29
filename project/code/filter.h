#ifndef _FILTER_H_
#define _FILTER_H_

#define WINDOW_SIZE   2
#define WINDOW_MAX_SIZE     50
typedef struct{
    const uint8 window_size;
    float buffer[WINDOW_MAX_SIZE];   //最大窗口大小
    int currentIndex;
    float sum;
} slidingFilter_struct;

float slidingFilter(float newData);
float slidingFilter_v2(slidingFilter_struct* filter_ptr, float newData);
bool isSame(int16 newData);

#endif
