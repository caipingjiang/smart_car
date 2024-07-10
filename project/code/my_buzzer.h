#ifndef _BUZZER_H_
#define _BUZZER_H_
#include "zf_common_headfile.h"

void buzzer_init(void);
void buzzer_set(bool state);
void buzzer_set_delay(uint16 x_ms);

#endif