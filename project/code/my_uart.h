#ifndef __MY_UART_H__
#define __MY_UART_H__

#define UART_BUFFER_SIZE 15 //���￼�ǵ����ݰ�ֻ����3������(x,y,class)��������ݰ����������ݽ϶�����ʵ����ӻ�����size
extern uint8 packge1_finish_flag, packge4_finish_flag; 
extern uint8 uart1_buffer[UART_BUFFER_SIZE], uart4_buffer[UART_BUFFER_SIZE];
extern int16 uart1_data_arr[2], uart4_data_arr[3]; 
void my_uart_init();
#endif