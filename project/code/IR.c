#include "zf_common_headfile.h"

#define IR_Pin  C27//D17 //ºìÍâÄ£¿éÒı½Å

void IR_init()
{
    gpio_init(IR_Pin, GPI, GPIO_HIGH, GPI_PULL_UP);
}

bool IR_get_state()
{
    return (bool)gpio_get_level(IR_Pin);
}