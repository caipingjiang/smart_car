#include "zf_common_headfile.h"

#define     Buzzer_Pin  B11      

void buzzer_init(void)
{
    gpio_init(B11, GPO, 0, GPO_PUSH_PULL);
}

//0¹Ø±Õ£¬ 1¿ªÆô
void buzzer_set(bool state)
{
    if(state) gpio_high(B11);
    else     gpio_low(B11);
}

void buzzer_set_delay(uint16 x_ms)
{
    gpio_high(B11);
    system_delay_ms(x_ms);
    gpio_low(B11);
}