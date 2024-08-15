#include "zf_common_headfile.h"
#include "my_moter.h"
#include "my_servo.h"
#include "my_encoder.h"
#include "my_image.h"
#include "my_key.h"
#include "image.h"
#include "math.h"
#include "imu660ra.h"
#include "car_control.h"
#include "my_buzzer.h"
#include "menu.h"

uint8 data_buffer[32];//������
int16 Target_Speed=1; //������

void pit_handler_3()
{
	// FW_Data[0].type = 'd';
	// FW_Data[1].type = 'd';
	// FW_Data[2].type = 'd';
	// // FW_Data[2].type = 'f';
	// // FW_Data[3].type = 'd';
	// // FW_Data[4].type = 'd';
	// FW_Data[0].int_data = track_wide;
	// FW_Data[1].int_data = lose_point_num_L;
	// FW_Data[2].int_data = lose_point_num_R;
	// // FW_Data[2].float_data =  imu660ra_gyro_z;
	// // FW_Data[3].int_data =  track_wide;
	// // FW_Data[4].int_data =  Slope;
	// FireWater_Send();

	if(abs(Gyro_Angle.Zdata - angle_now - angle_turn)<5)	//С��3�Ⱦ���Ϊת�����
	{
		Image_Mode = 0;
		Control_Mode = 0;
		pit_disable(PIT_CH3);
	}
	else
	{
		Control_Mode = 3;
	}
}

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
	key_index_enum key_index_array[KEY_NUMBER] = {KEY_1,KEY_2,KEY_3,KEY_4};
    key_init(5);
    // �˴���д�û����� ���������ʼ�������
	my_imu660ra_init();
	imu660_zeroBias();
	my_servo_init();
	
	//my_key_init();
	buzzer_init();
    //wireless_uart_init();
	
	//ImagePerspective_Init();
	my_uart_init();
	//����������ʼ�����������Ϊ����pit��ʼ��
	
	my_image_init();
	my_motor_init();	//--->>>>>>>>>ע�������D12-D15������ips200��csi�ظ�ʹ�ã�����ͬʱʹ��
 	my_encoder_init();	//����Ļ��ʾ����Ҳ��Ӱ��
	//timer_init(GPT_TIM_1,TIMER_US);
	IR_init();

 	interrupt_set_priority(LPUART8_IRQn,4);
	interrupt_set_priority(PIT_IRQn, 0);
	interrupt_set_priority(LPUART1_IRQn,1);
	interrupt_set_priority(LPUART4_IRQn,2);
	interrupt_global_enable(0);

	pit_ms_init(PIT_CH0, 3);	//������
	pit_ms_init(PIT_CH1, 5);	//������
	pit_ms_init(PIT_CH2, 5);	//�����
	pit_ms_init(PIT_CH3, 10);	//���ߴ��ڷ���
	pit_disable(PIT_CH3);
    // �˴���д�û����� ���������ʼ�������
												
	ips114_draw_line(middle -  30, 20, middle + 30, 20, RGB565_GREEN);
	ips114_draw_line(0,40,187+40,40,RGB565_PURPLE);
	ips114_draw_line(0,80,187+40,80,RGB565_PURPLE);
	ips114_draw_line(188,20,187+40,20,RGB565_GREEN);
	ips114_draw_line(188,100,187+40,100,RGB565_GREEN);
	while(1)
    {	
		if(mt9v03x_finish_flag)
        {
			mt9v03x_finish_flag = 0;
			//ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);

			// mt9v03x_finish_flag = 0;
			// sideline_correct(boder_correct, &sideline_angle, &sideline_distance);
		
		}
		//ips114_show_uint(90,90,track_wide,4);
		// show_boder_line();
		//ips114_show_int(188, 70, find_white_point(mt9v03x_image), 3);
		// ips114_show_int(30,10,roundabout_flag, 2);
		// ips114_show_int(30,30,lose_point_num_L, 3);
		// ips114_show_int(30,50,lose_point_num_R, 3);
		// ips114_show_int(30,70,curvity_calculate(boder_L, &longest), 6);
		// ips114_show_int(30,90,curvity_calculate(boder_R, &longest), 4);
		
		//ips114_show_int(50,110,Slope, 2);
		// ips114_show_int(50,40,uart1_data_arr[0], 4);
		// ips114_show_int(90,40,uart1_data_arr[1], 4);
		// system_delay_ms(10);
		
		// ips114_show_float(0,0,Gyro_Angle.Ydata,3,2);
		// ips114_show_float(0,20,Acc_Angle.Ydata,3,2);
		// ips114_show_float(0,40,Fusion_Angle.Ydata,3,2);
		//Slope_Mode = 2;
		//target_slope  = -30;

//		arm_exchange(0,1);
//		/ystem_delay_ms(500);
//		arm_exchange(1,2);
//		arm_exchange(2,1);
//		arm_exchange(1,0);
		start_finish_line_control();
		cross_move_control();
		roundabout_move_control();
		ART_control();
		
		ramp_control();
		barrier_control();	

		system_delay_ms(5);
		key_scanner();
		
		UI();
		 
		// else if(KEY_LONG_PRESS == key_get_state(KEY_2))
		// {
		// 	ips114_show_string(0,40,"key2");
		// }

		//ips114_show_string(0,120,"test6");
		//arm_down();
		// arm_exchange(0,1);
		//arm_hang();
		//arm_up();
		//arm_hang();
		//curvity_calculate(boder_L,&longest);
//		system_delay_ms(5);
		
    }
}







//------------------------------���Դ���------------------------------------

// ips114_show_int(30,30,roundabout_flag, 2);
// ips114_show_int(30,50,track_wide, 5);
// ips114_show_int(30,70,turn_flag, 2);
// ips114_show_int(30,90,cross_flag, 2);
// ips114_show_int(30,110,Control_Mode, 2);



// system_delay_ms(10);
// for(uint8 i = 0; i<=3; i++)
// {
// 	Servo_SetAngle(3,i*93);
// 	system_delay_ms(1500);
// 	arm_down();
// 	arm_hang();
// } 	

// //	JF_Data.data[0] = Kp_T;
// //	JF_Data.data[1] = Kd_T;
// //	JF_Data.data[2] = 0.45;
// //	JF_Data.data[3] = -3.36;
// //	JustFloat_Send();
// FW_Data[0].type = 'd';
// FW_Data[1].type = 'd';
// //FW_Data[2].type = 'd';
// //FW_Data[3].type = 'd';

//  FW_Data[4].type = 'f';
//  FW_Data[5].type = 'f';

// //FW_Data[6].type = 'd';
// //FW_Data[7].type = 'd';

// FW_Data[0].int_data = encoder_data[0];
// FW_Data[1].int_data = encoder_data[1];
// // FW_Data[2].int_data = encoder_data[2];
// // FW_Data[3].int_data = encoder_data[3];

//  FW_Data[4].float_data = Kp_correct2;
//  FW_Data[5].float_data = Kd_correct2;
// // FW_Data[6].int_data = Pwm[0];
// // FW_Data[7].int_data = Pwm[1];
// FireWater_Send();



//��ʱ������ʱ��
//			 timer_start(GPT_TIM_1);			 			 
//			 timer_stop(GPT_TIM_1);
//			 uint32 time = timer_get(GPT_TIM_1);
//			 timer_clear(GPT_TIM_1);
//			 ips200_show_int(50, 50, time, 4);


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


//		uint8 image_copy[MT9V03X_H][MT9V03X_W];
//		if(mt9v03x_finish_flag)
//		{	zf_assert(NULL != &image_copy[0][0]);
//			mt9v03x_finish_flag = 0;
//		
//			memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
//			wireless_uart_send_buffer((const uint8*)preFrame, sizeof(int)*7);
//			wireless_uart_send_buffer(&image_copy[0][0], MT9V03X_IMAGE_SIZE);
//		}


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


// if(packge_finish_flag)
		// 	//printf("data:%d,%d,%c\n", data_arr[0], data_arr[1], data_arr[2]);
		// 	ips200_show_int(20,20,data_arr[0],3);
		// 	ips200_show_int(20,40,data_arr[1],3);
			//packge_finish_flag = 0;



		// v_y = 0;
		// v_x =0;
		// system_delay_ms(2000);
		// v_y = -90;//0;
		// v_x =0;//-30;
		// system_delay_ms(2000);
//		v_y = -30;
//		v_x =0;
//		system_delay_ms(1000);
//		v_y = 0;
//		v_x =30;
//		system_delay_ms(1000);

//system_delay_ms(1500);
		//system_delay_ms(1000);
		//		Target_Speed = 35;
		//		system_delay_ms(4000);
		// 		Target_Speed = -35;
		// 		system_delay_ms(4000);


//my_key_work();
		//ips114_show_float(100,100,Kp_T, 2,1);
		// ips114_show_float(0,20,Kp_correct1, 3,3);
		// ips114_show_float(0,40,Kd_correct1, 3,3);
//------------------------------���Դ���------------------------------------