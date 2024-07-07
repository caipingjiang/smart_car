#include "zf_common_headfile.h"

#define IR_Pin  D17 //ºìÍâÄ£¿éÒı½Å

void IR_init()
{
    gpio_init(IR_Pin, GPI, GPIO_HIGH, GPI_PULL_DOWN);
}

bool IR_get_state()
{
    return (bool)gpio_get_level(IR_Pin);
}