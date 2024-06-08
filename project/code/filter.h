#ifndef _FILTER_H_
#define _FILTER_H_

typedef struct{
    uint8 window_size;
    int currentIndex;
    float sum;
} slidingFilter_struct;


#define WINDOW_SIZE   2

#define WINDOW_SIZE_2   5

extern float slidingFilter(float newData);

#endif
