#ifndef __MY_UART_H__
#define __MY_UART_H__

#define UART_BUFFER_SIZE 15 //这里考虑到数据包只包含3个数据(x,y,class)，如果数据包包含的数据较多可以适当增加缓冲区size
extern uint8 packge1_finish_flag, packge4_finish_flag; 
extern uint8 uart1_buffer[UART_BUFFER_SIZE], uart4_buffer[UART_BUFFER_SIZE];
extern int16 uart1_data_arr[2], uart4_data_arr[3]; 
void my_uart_init();
#endif