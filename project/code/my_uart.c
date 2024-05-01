#include "zf_common_headfile.h"

static  fifo_struct         uart_fifo;
uint8   uart_buffer[UART_BUFFER_SIZE];    // 数据存放数组
static  uint8               uart_data   = 0;
static  uint8 uart_rx_state = 0;
uint8 packge_finish_flag = 0; //数据包接收完成标志
static uint32 length = 0; //fifo实际的缓存数据长度

uint16 data_arr[3] = {0}; //解析后的数据，依次为x,y,class

void my_uart_init()
{
    uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);
    uart_init(UART_4, 115200, UART4_TX_C16, UART4_RX_C17);
    //uart_init(UART_3, 115200, UART3_TX_C8, UART3_RX_C9);
    fifo_init(&uart_fifo, FIFO_DATA_8BIT, uart_buffer, UART_BUFFER_SIZE);
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
                if(uart_rx_state == 0 && uart_data == '@')      //接收到包头
                {
                    if(fifo_used(&uart_fifo)==0) {uart_rx_state = 1;packge_finish_flag = 0;}
                }
                else if(uart_rx_state == 1 && uart_data != '#') //接收到包头但未接收到包尾时正常写入数据到fifo
                {
                    fifo_write_buffer(&uart_fifo, &uart_data, 1);
                }
                else if(uart_rx_state == 1 && uart_data == '#') //接收到包尾
                {
                    fifo_write_buffer(&uart_fifo, "\n", 1);
                    uart_rx_state = 0;
                    length = fifo_used(&uart_fifo);
                    if(length>=4)//正常数据的最短长度（x + ',' + y + '\n'>=4）， 如果比这个长度还短就不读取
                    {
                        sscanf((const char*)uart_buffer, "%d，%d,%c\n", &data_arr[0], &data_arr[1], &data_arr[2]);
                    }
                    fifo_clear(&uart_fifo);
                    packge_finish_flag = 1;
                }
            }
            break;
        }
        case UART_4:
        {
           if(uart_query_byte(UART_4, &uart_data) != 0)//一定要加上这个查询是否接收成功，不然会一直调用此函数造成卡死（BUG?）
                printf("uart4_test");
                //printf("uart4:%s\n",&uart_data);
            break;
        }

    }
    memset(&uart_data, 0, 1);
}