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
 	my_motor_init();	//--->>>>>>>>>注意这里的D12-D15引脚与ips200的csi重复使用，不能同时使用
 	my_encoder_init();	//对屏幕显示可能也有影响
	my_servo_init();
//	my_key_init();
	my_image_init();
    wireless_uart_init();
	//ImagePerspective_Init();
	my_uart_init();
	
	timer_init(GPT_TIM_1,TIMER_US);
	
 	interrupt_set_priority(LPUART8_IRQn,4);
	interrupt_set_priority(PIT_IRQn, 3);
	interrupt_set_priority(LPUART1_IRQn,1);
	interrupt_set_priority(LPUART4_IRQn,2);
	interrupt_global_enable(0);
 	interrupt_set_priority(LPUART8_IRQn,4);
	interrupt_set_priority(PIT_IRQn, 3);
	interrupt_set_priority(LPUART1_IRQn,1);
	interrupt_set_priority(LPUART4_IRQn,2);
	interrupt_global_enable(0);
    // 此处编写用户代码 例如外设初始化代码等

	ips114_draw_line(middle - 30, 20, middle + 30, 20, RGB565_GREEN);
	while(1)
    {		
		
		//Control_Mode  =	2;
		if(mt9v03x_finish_flag)
        {
		 	//mt9v03x_finish_flag = 0;
			//Image_change((uint8 **)mt9v03x_image, MT9V03X_W, MT9V03X_H);
		 	//image_process();
			ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
 			// find_middle();
			// sideline_correct(boder_correct, &sideline_angle, &sideline_distance);
			// Slopdabout();e = slope();
			// cross();
			// roun
		}
		
		 
		// v_y =slidingFilter(1500/(abs(Slope)+20));
		// system_delay_ms(10);
		
		
		// start_finish_line_control();
		// cross_move_control();
		// roundabout_move_control();

		ips114_show_int(0,20,cross_flag,2);
		ips114_show_int(0,40,roundabout_flag,2);
		//ips114_show_int(80,20,Slope,3);
		// ips114_show_int(0,60,lose_point_num_L,3);
		// ips114_show_int(0,80,lose_point_num_R,3);
		// ART_control();
		ips114_show_int(60,30,uart4_data_arr[1], 2);
		if(uart4_data_arr[1]==1)        //识别到卡片
		{
			Control_Mode=4;
			system_delay_ms(1000);
			v_x = 0;
			v_y = 0;
			w = 0;
			while(uart4_data_arr[1]==1)
			{
				ips114_show_string(0,60,(const char*)&uart4_data_arr[0]);
				Box_In((char)uart4_data_arr[0],0);
				
				system_delay_ms(1000);
			}
			
		 }
		
    }
}







//------------------------------测试代码------------------------------------
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