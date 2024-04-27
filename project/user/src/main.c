#include "zf_common_headfile.h"
#include "my_moter.h"
#include "my_servo.h"
#include "my_encoder.h"
#include "my_image.h"
#include "image.h"
#include "math.h"
#include "imu660ra.h"
uint8 data_buffer[32];
uint8 dat;
int16 Target_Speed=0;
int16 Slope ;
char send_data[10]={0};
float angle=0;                //�����ںϺ�ĽǶ� 
uint16 count=0;
float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;



void pit_handler_1()
{           
//	JF_Data.data[0] = Kp_T;
//	JF_Data.data[1] = Kd_T;
//	JF_Data.data[2] = 0.45;
//	JF_Data.data[3] = -3.36;
//	JustFloat_Send();
FW_Data[0].type = 'd';
FW_Data[1].type = 'd';
FW_Data[2].type = 'f';
FW_Data[0].int_data   = encoder_data[0];
FW_Data[1].int_data   = encoder_data[1];
FW_Data[2].float_data = 1.657;
FireWater_Send();
    //��ֵ�˲�
//    float min=0, max=0, temp_angle;
//	for(uint8 i=0; i<10; i++)
//	{
//		//imu660ra_get_acc();
//		imu660ra_get_gyro();
//		tra_gyro_z = (imu660ra_gyro_transition(imu660ra_gyro_z));

//        (tra_gyro_z>max) ? (max=tra_gyro_z):0;
//		(tra_gyro_z<min) ? (min=tra_gyro_z):0;
//        temp_angle += tra_gyro_z;
//	}
//    tra_gyro_z = (temp_angle - min - max)/8;
	//imu660ra_get_acc();
	//imu660ra_get_gyro();
	//tra_gyro_z = (imu660ra_gyro_transition(imu660ra_gyro_z)+0.0160  );
	
	angle += (tra_gyro_z*0.005-Gyro_Bias.Zdata);
	
	// angle = angle_calc(imu963ra_acc_y, imu660ra_gyro_z);
	// w = (int16)w_PID(180, tra_gyro_z);
}
uint8 image_copy[MT9V03X_H][MT9V03X_W];
extern int16 temp;
int main(void)
{
	
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��
	system_delay_ms(500);

	//ע�⣡������Ļ�Ե����Ӱ��
	//spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_D12, SPI1_MOSI_D14, SPI1_MISO_D15, SPI1_CS0_D13);
	//ips200_init(IPS200_TYPE_SPI);
	//(IPS200_CROSSWISE);
	//ips200_init(IPS200_TYPE_PARALLEL8);
	ips114_set_dir(IPS114_CROSSWISE);
	ips114_init();

    // �˴���д�û����� ���������ʼ�������

	//imu660ra_init();
	//imu660_zeroBias();
	my_motor_init();	//--->>>>>>>>>ע�������D12-D15������ips200��csi�ظ�ʹ�ã�����ͬʱʹ��
	my_encoder_init();	//����Ļ��ʾ����Ҳ��Ӱ��
	my_servo_init();
	 //my_image_init();
    wireless_uart_init();
	//ImagePerspective_Init();
	
	
	//timer_init(GPT_TIM_1,TIMER_US);
	uart_init(UART_4, 115200, UART4_TX_C16, UART4_RX_C17);
	pit_ms_init(PIT_CH1, 25);
	
	interrupt_set_priority(LPUART8_IRQn,4);
	interrupt_set_priority(PIT_IRQn, 1);
	interrupt_global_enable(0);
    // �˴���д�û����� ���������ʼ�������
	arm_down();
    while(1)
    {
		//printf("fdsf");
		//dat = uart_read_byte(UART_4);printf("is:%d",dat);
		//if(uart_read_byte(UART_4, data_buffer))printf("data is: %d", data_buffer);
			
		//printf("%d, %d, %d, %d\n", Pwm[0],Pwm[1], Pwm[2], Pwm[3]);
 		//uint8 data_len = wireless_uart_read_buffer(data_buffer, 32);  
// 		if(data_len != 0)                                                       // �յ�����Ϣ ��ȡ�����᷵��ʵ�ʶ�ȡ�������ݸ���
//         {
//			 //printf(data_buffer);
//             wireless_uart_send_buffer(data_buffer, data_len);                     // ���յ�����Ϣ���ͻ�ȥ
//             //memset(data_buffer, 0, 32);
//// 			sscanf((const char*)data_buffer, "@:%d,%d",&v_x, &v_y);
//// 			memset(data_buffer, 0, 32);
//         }
		//printf("%d,%d, %d\n",v_x, v_y, w);
		//system_delay_ms(1500);
		//system_delay_ms(1000);
		//		Target_Speed = 35;
		//		system_delay_ms(4000);
		// 		Target_Speed = -35;
		// 		system_delay_ms(4000);

//		if(mt9v03x_finish_flag)
//		{	zf_assert(NULL != &image_copy[0][0]);
//			mt9v03x_finish_flag = 0;
//		
//			memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
//			wireless_uart_send_buffer((const uint8*)preFrame, sizeof(int)*7);
//			wireless_uart_send_buffer(&image_copy[0][0], MT9V03X_IMAGE_SIZE);

//		}
		
//		if(mt9v03x_finish_flag)
//        {
//		 	mt9v03x_finish_flag = 0;
//			//Image_change((uint8 **)mt9v03x_image, MT9V03X_W, MT9V03X_H);
//		 	//image_process();
//         	// ips200_displayimage03x((const uint8 *)mt9v03x_image,MT9V03X_W,MT9V03X_H);
// 			//ips200_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
////			ips200_show_gray_image(100, 0, (const uint8 *)image_changed, MT9V03X_W-2, MT9V03X_H-2, 188-2, 120-2, 0);
//			ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
//  			
//			//start _finish_line_find();
//			
// 			find_middle();
//			Slope= slope();
//		
// 			// if(start_finish_line_find())ips200_draw_square(60,100,8,RGB565_PINK);
//		}

			 
			 //��͸��
//			 uint8_t show[RESULT_ROW][RESULT_COL];
//                for(int i=0;i<RESULT_ROW;i++)
//                {
//                    for(int j=0;j<RESULT_COL;j++)
//                    {
//                        show[i][j]=ImageUsed[i][j];
//                    }
//                }
//            ips200_show_gray_image(0,130,show[0],RESULT_COL,RESULT_ROW,RESULT_COL,RESULT_ROW,0);

		
    }

}

//��ʱ������ʱ��
//			 timer_start(GPT_TIM_1);			 			 
//			 timer_stop(GPT_TIM_1);
//			 uint32 time = timer_get(GPT_TIM_1);
//			 timer_clear(GPT_TIM_1);
//			 ips200_show_int(50, 50, time, 4);

