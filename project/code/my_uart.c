#include "zf_common_headfile.h"

static  fifo_struct         uart_fifo;
uint8   uart_buffer[UART_BUFFER_SIZE];    // ���ݴ������
static  uint8               uart_data   = 0;
static  uint8 uart_rx_state = 0;
uint8 packge_finish_flag = 0; //���ݰ�������ɱ�־
static uint32 length = 0; //fifoʵ�ʵĻ������ݳ���

uint16 data_arr[3] = {0}; //����������ݣ�����Ϊx,y,class

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
// �������  �����жϻص�����
// ����˵��  uart_n�����ں�
// ���ز���  void
// ʹ��ʾ��  my_uart_callback(UART_1)
// ��ע��Ϣ  �˺�����isr.c�ļ��Ĵ����жϺ����б�����
//-----------------------------------------------------------------------------------------------
void my_uart_callback(uart_index_enum uart_n)
{
    switch (uart_n)
    {
        //ע�⣺����1����ART����ʱһ��Ҫ�Ͽ�DAP�����ߣ��������������ղ���
        //ע�⣺����1����ART����ʱһ��Ҫ�Ͽ�DAP�����ߣ��������������ղ���
        //ע�⣺����1����ART����ʱһ��Ҫ�Ͽ�DAP�����ߣ��������������ղ���
        case UART_1:
        {
            if(uart_query_byte(UART_1, &uart_data) != 0)
            {
                if(uart_rx_state == 0 && uart_data == '@')      //���յ���ͷ
                {
                    if(fifo_used(&uart_fifo)==0) {uart_rx_state = 1;packge_finish_flag = 0;}
                }
                else if(uart_rx_state == 1 && uart_data != '#') //���յ���ͷ��δ���յ���βʱ����д�����ݵ�fifo
                {
                    fifo_write_buffer(&uart_fifo, &uart_data, 1);
                }
                else if(uart_rx_state == 1 && uart_data == '#') //���յ���β
                {
                    fifo_write_buffer(&uart_fifo, "\n", 1);
                    uart_rx_state = 0;
                    length = fifo_used(&uart_fifo);
                    if(length>=4)//�������ݵ���̳��ȣ�x + ',' + y + '\n'>=4���� �����������Ȼ��̾Ͳ���ȡ
                    {
                        sscanf((const char*)uart_buffer, "%d��%d,%c\n", &data_arr[0], &data_arr[1], &data_arr[2]);
                    }
                    fifo_clear(&uart_fifo);
                    packge_finish_flag = 1;
                }
            }
            break;
        }
        case UART_4:
        {
           if(uart_query_byte(UART_4, &uart_data) != 0)//һ��Ҫ���������ѯ�Ƿ���ճɹ�����Ȼ��һֱ���ô˺�����ɿ�����BUG?��
                printf("uart4_test");
                //printf("uart4:%s\n",&uart_data);
            break;
        }

    }
    memset(&uart_data, 0, 1);
}