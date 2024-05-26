#include "zf_common_headfile.h"

// 串口1用于90度摄像头分类，串口四用于130度摄像头目标检测
static  fifo_struct     uart1_fifo, uart4_fifo;
uint8   uart1_buffer[UART_BUFFER_SIZE];    // 数据存放数组
uint8   uart4_buffer[UART_BUFFER_SIZE];
static  uint8           uart_data   = 0;
static  uint8 uart1_rx_state,  uart4_rx_state= 0;
uint8   packge1_finish_flag = 0, packge4_finish_flag = 0; //数据包接收完成标志
static  uint32 length1 = 0, length4; //fifo实际的缓存数据长度

int16 uart1_data_arr[4] = {0}; //解析后的数据，依次为x,y,distance, correct_flag  若x,y,correct_flag为零则说明这一帧没有找到卡片或者找到的卡片的距离大于限定值
int16 uart4_data_arr[4] = {0}; //解析后的数据，依次为x,y,distance,class

void my_uart_init()
{
    uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);
    uart_init(UART_4, 115200, UART4_TX_C16, UART4_RX_C17);

    fifo_init(&uart1_fifo, FIFO_DATA_8BIT, uart1_buffer, UART_BUFFER_SIZE);
    fifo_init(&uart4_fifo, FIFO_DATA_8BIT, uart4_buffer, UART_BUFFER_SIZE);

	uart_rx_interrupt(UART_1, 1);
 	uart_rx_interrupt(UART_4, 1);
    
}

//-----------------------------------------------------------------------------------------------
// 函数简介  串口中断回调函数
// 参数说明  uart_n：串口号
// 返回参数  void
// 使用示例  my_uart_callback(UART_1)
// 备注信息  此函数在isr.c文件的串口中断函数中被调用
//-----------------------------------------------------------------------------------------------
void my_uart_callback(uart_index_enum uart_n)
{
    switch (uart_n)
    {
        //注意：串口1在与ART传输时一定要断开DAP下载线！！！，否则会接收不到
        //注意：串口1在与ART传输时一定要断开DAP下载线！！！，否则会接收不到
        //注意：串口1在与ART传输时一定要断开DAP下载线！！！，否则会接收不到
        case UART_1:
        {
            if(uart_query_byte(UART_1, &uart_data) != 0)
            {
                if(uart1_rx_state == 0 && uart_data == '@')      //接收到包头
                {
                    if(fifo_used(&uart1_fifo)==0) {uart1_rx_state = 1;packge1_finish_flag = 0;}
                }
                else if(uart1_rx_state == 1 && uart_data != '#') //接收到包头但未接收到包尾时正常写入数据到fifo
                {
                    fifo_write_buffer(&uart1_fifo, &uart_data, 1);
                }
                else if(uart1_rx_state == 1 && uart_data == '#') //接收到包尾
                {
                    fifo_write_buffer(&uart1_fifo, "\n", 1);
                    uart1_rx_state = 0;
                    length1 = fifo_used(&uart1_fifo);
                    if(length1>=7)//正常数据的最短长度（x + ',' + y + ',' + distance + correct_flag  + '\n'>=7）， 如果比这个长度还短就不读取
                    {
                        sscanf((const char*)uart1_buffer, "%d,%d,%d,%d\n", &uart1_data_arr[0], &uart1_data_arr[1], &uart1_data_arr[2], &uart1_data_arr[3]);
                    }
                    fifo_clear(&uart1_fifo);
                    packge1_finish_flag = 1;
                }
            }
            break;
        }
        case UART_4:
        {
           if(uart_query_byte(UART_4, &uart_data) != 0)//一定要加上这个查询是否接收成功，不然会一直调用此函数造成卡死（BUG?）
            {        
                if(uart4_rx_state == 0 && uart_data == 'Y')      //接收到包头
                {
                    if(fifo_used(&uart4_fifo)==0) {uart4_rx_state = 1;packge4_finish_flag = 0;}
                }
                else if(uart4_rx_state == 1 && uart_data != 'Z') //接收到包头但未接收到包尾时正常写入数据到fifo
                {
                    fifo_write_buffer(&uart4_fifo, &uart_data, 1);
                }
                else if(uart4_rx_state == 1 && uart_data == 'Z') //接收到包尾
                {
                    fifo_write_buffer(&uart4_fifo, "\n", 1);
                    uart4_rx_state = 0;
                    length4 = fifo_used(&uart4_fifo);
                    if(length4>=4)//正常数据的最短长度（x + ',' + y + '\n'>=4）， 如果比这个长度还短就不读取
                    {
                        sscanf((const char*)uart4_buffer, "%d,%d,%d,%s\n", &uart4_data_arr[0], &uart4_data_arr[1], &uart4_data_arr[2],  &uart4_data_arr[3]);
                    }
                    fifo_clear(&uart4_fifo);
                    packge4_finish_flag = 1;
                }
            }
            break;
        }

    }
    memset(&uart_data, 0, 1);
}