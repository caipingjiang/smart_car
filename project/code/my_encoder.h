#ifndef _my_encoder_h_
#define _my_encoder_h_

#include "zf_common_headfile.h"
void my_encoder_init(void);
void pit_handler (void);

extern int16 encoder_data_1;     //��������ٶ�
extern int16 encoder_data_2;     //�ұ������ٶ�

#endif
