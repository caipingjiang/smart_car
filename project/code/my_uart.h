#ifndef __MY_UART_H__
#define __MY_UART_H__

#define UART_BUFFER_SIZE 12 //���￼�ǵ����ݰ�ֻ����3������(x,y,class)��������ݰ����������ݽ϶�����ʵ����ӻ�����size
extern uint8 packge_finish_flag; 
extern uint8 uart_buffer[UART_BUFFER_SIZE];
extern uint16 data_arr[3];
void my_uart_init();

#endif