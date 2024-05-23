#include "zf_common_headfile.h"

// ����4����90������ͷ���࣬����1����130������ͷĿ����
static  fifo_struct     uart1_fifo, uart4_fifo;
uint8   uart1_buffer[UART_BUFFER_SIZE];    // ���ݴ������
uint8   uart4_buffer[UART_BUFFER_SIZE];
static  uint8           uart_data   = 0;
static  uint8 uart1_rx_state,  uart4_rx_state= 0;
uint8   packge1_finish_flag = 0, packge4_finish_flag = 0; //���ݰ�������ɱ�־
static  uint32 length1 = 0, length4; //fifoʵ�ʵĻ������ݳ���

int16 uart1_data_arr[2] = {0}; //����������ݣ�����Ϊclass��ʶ�𵽿�Ƭ��־λ
int16 uart4_data_arr[2] = {0}; //����������ݣ�����Ϊclass��ʶ�𵽿�Ƭ��־λ

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
                if(uart1_rx_state == 0 && uart_data == '@')      //���յ���ͷ
                {
                    if(fifo_used(&uart1_fifo)==0) {uart1_rx_state = 1;packge1_finish_flag = 0;}
                }
                else if(uart1_rx_state == 1 && uart_data != '#') //���յ���ͷ��δ���յ���βʱ����д�����ݵ�fifo
                {
                    fifo_write_buffer(&uart1_fifo, &uart_data, 1);
                }
                else if(uart1_rx_state == 1 && uart_data == '#') //���յ���β
                {
                    fifo_write_buffer(&uart1_fifo, "\n", 1);
                    uart1_rx_state = 0;
                    length1 = fifo_used(&uart1_fifo);
                    if(length1>=3)//�������ݵ���̳��ȣ�x + ',' + y + '\n'>=4���� �����������Ȼ��̾Ͳ���ȡ
                    {
                        sscanf((const char*)uart1_buffer, "%c,%d\n",&uart1_data_arr[0], &uart1_data_arr[1]);
						
                    }
                    fifo_clear(&uart1_fifo);
                    packge1_finish_flag = 1;
                }
            }
            break;
        }
        case UART_4:
        {
           if(uart_query_byte(UART_4, &uart_data) != 0)//һ��Ҫ���������ѯ�Ƿ���ճɹ�����Ȼ��һֱ���ô˺�����ɿ�����BUG?��
            {        
                if(uart4_rx_state == 0 && uart_data == 'Y')      //���յ���ͷ
                {
                    if(fifo_used(&uart4_fifo)==0) {uart4_rx_state = 1;packge4_finish_flag = 0;}
                }
                else if(uart4_rx_state == 1 && uart_data != 'Z') //���յ���ͷ��δ���յ���βʱ����д�����ݵ�fifo
                {
                    fifo_write_buffer(&uart4_fifo, &uart_data, 1);
                }
                else if(uart4_rx_state == 1 && uart_data == 'Z') //���յ���β
                {
                    fifo_write_buffer(&uart4_fifo, "\n", 1);
                    uart4_rx_state = 0;
                    length4 = fifo_used(&uart4_fifo);
                    if(length4>=3)//�������ݵ���̳��ȣ�x + ',' + y + '\n'>=4���� �����������Ȼ��̾Ͳ���ȡ
                    {
                         sscanf((const char*)uart1_buffer, "%c,%d\n",&uart4_data_arr[0], &uart4_data_arr[1]);
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