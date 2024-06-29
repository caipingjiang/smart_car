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

uint8 data_buffer[32];//测试用
int16 Target_Speed=1; //测试用

void pit_handler_3()
{
	FW_Data[0].type = 'd';
	FW_Data[1].type = 'd';
	FW_Data[2].type = 'd';
	// FW_Data[2].type = 'f';
	// FW_Data[3].type = 'd';
	// FW_Data[4].type = 'd';
	FW_Data[0].int_data = track_wide;
	FW_Data[1].int_data = lose_point_num_L;
	FW_Data[2].int_data = lose_point_num_R;
	// FW_Data[2].float_data =  imu660ra_gyro_z;
	// FW_Data[3].int_data =  track_wide;
	// FW_Data[4].int_data =  Slope;
	FireWater_Send();
}

int main(void)
{
	
    clock_init(SYSTEM_CLOCK_600M);  // 不可删除
    debug_init();                   // 调试端口初始化
	system_delay_ms(500);

	//注意！！！屏幕对电机有影响
	//spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_D12, SPI1_MOSI_D14, SPI1_MISO_D15, SPI1_CS0_D13);
	//ips200_init(IPS200_TYPE_SPI);
	//(IPS200_CROSSWISE);
	//ips200_init(IPS200_TYPE_PARALLEL8);
	ips114_set_dir(IPS114_CROSSWISE);
	ips114_init();

    // 此处编写用户代码 例如外设初始化代码等
	my_imu660ra_init();
	imu660_zeroBias();
	my_servo_init();
//	my_key_init();
	
    wireless_uart_init();
	
	//ImagePerspective_Init();
	my_uart_init();
	//下面三个初始化放在最后，因为含有pit初始化
	
	my_image_init();
	my_motor_init();	//--->>>>>>>>>注意这里的D12-D15引脚与ips200的csi重复使用，不能同时使用
 	my_encoder_init();	//对屏幕显示可能也有影响
	//timer_init(GPT_TIM_1,TIMER_US);
	
 	interrupt_set_priority(LPUART8_IRQn,4);
	interrupt_set_priority(PIT_IRQn, 0);
	interrupt_set_priority(LPUART1_IRQn,1);
	interrupt_set_priority(LPUART4_IRQn,2);
	interrupt_global_enable(0);

	pit_ms_init(PIT_CH0, 3);	//编码器
	pit_ms_init(PIT_CH1, 5);	//陀螺仪
	pit_ms_init(PIT_CH2, 5);	//总钻风
	//pit_ms_init(PIT_CH3, 20);	//无线串口发送

    // 此处编写用户代码 例如外设初始化代码等
												
	ips114_draw_line(middle -  30, 20, middle + 30, 20, RGB565_GREEN);
	ips114_draw_line(0,40,187+40,40,RGB565_PURPLE);
	ips114_draw_line(0,80,187+40,80,RGB565_PURPLE);
	ips114_draw_line(188,20,187+40,20,RGB565_GREEN);
	ips114_draw_line(188,100,187+40,100,RGB565_GREEN);
	while(1)
    {	
			ips114_show_uint(90,90,track_wide,4);
		if(mt9v03x_finish_flag)
        {
			ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
		
		// uint16 temp_width = 0;
		// uint16 temp_width1 = 0, temp_width2 = 0;
		// for(uint8 i = 120*2/3;i <120;i++)
		// {
		// 	temp_width += (boder_R[i] - boder_L[i]);
		// 	temp_width1 += boder_R[i];
		// 	temp_width2 += boder_R[i-40];
		// }
		// ips114_show_float(0,80,(float)track_wide/temp_width,2,3);
		// ips114_show_int(0,100,temp_width1-temp_width2,4);

		//r = (float)temp_sum[0] / (sqrt((float)temp_sum[1] * sqrt(temp_sum[2])));
		//if(r>0.7);
//		ips114_show_float(60,0,r,5,3);ips114_show_float(140,0,r*r,5,3);
//		ips114_show_int(0,20,(const int32)temp_sum[0],10);
//		ips114_show_int(0,40,(const int32)temp_sum[1],10);
//		ips114_show_int(0,60,(const int32)temp_sum[2],10);
//		//ips114_show_int(0,80,(const int32)mean_x,10);
//		ips114_show_float(0,80,(float)temp_sum[0],8,2);

		}

//		ips114_show_int(50,110,Slope, 2);
		// ips114_show_int(50,40,uart1_data_arr[0], 4);
		// ips114_show_int(90,40,uart1_data_arr[1], 4);
		// system_delay_ms(10);
		ips114_show_float(0,0,Gyro_Angle.Ydata,3,2);
		start_finish_line_control();
		cross_move_control();
		roundabout_move_control();
		ART_control();
		
		ramp_control();
		
		//barrier_control();
//		system_delay_ms(5);
		
    }
}







//------------------------------测试代码------------------------------------

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



//定时器测量时间
//			 timer_start(GPT_TIM_1);			 			 
//			 timer_stop(GPT_TIM_1);
//			 uint32 time = timer_get(GPT_TIM_1);
//			 timer_clear(GPT_TIM_1);
//			 ips200_show_int(50, 50, time, 4);


 //逆透视
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
// 		if(data_len != 0)                                                       // 收到了消息 读取函数会返回实际读取到的数据个数
//         {
//			 //printf(data_buffer);
//             wireless_uart_send_buffer(data_buffer, data_len);                     // 将收到的消息发送回去
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
//------------------------------测试代码------------------------------------