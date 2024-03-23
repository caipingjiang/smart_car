#include "zf_common_headfile.h"
#include "my_moter.h"
#include "my_servo.h"
#include "my_encoder.h"
#include "my_image.h"
#include "image.h"
#include "math.h"
#include "imu660ra.h"
uint8 data_buffer[32];
int16 Target_Speed=0;
int16 Slope ;
char send_data[10]={0};
float angle=0;                //数据融合后的角度 
uint16 count=0;
float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;

#define CH_COUNT 4
struct justfloat_struct 
{
    float fdata[CH_COUNT];	//JustFloat格式只能发送float类型的数据
    unsigned char tail[4];	//帧尾
	
} vofa;

#define		IMG_ID			0
#define 		IMG_SIZE			188*120
#define 		IMG_WIDTH		188	
#define 		IMG_HEIGHT		120
#define		IMG_FORMAT		24
// 先发送前导帧
int preFrame[7] = {
    IMG_ID, 
    IMG_SIZE, 
    IMG_WIDTH, 
    IMG_HEIGHT, 
    IMG_FORMAT, 
    0x7F800000, 
    0x7F800000
};

void pit_handler_1()
{           
//	vofa.fdata[0] = Kp_T;
//	vofa.fdata[1] = Kd_T;
//	vofa.fdata[2] = 0;
//	vofa.fdata[3] = 0;
//	wireless_uart_send_buffer((const uint8*)vofa.fdata, sizeof(float) * CH_COUNT);
//	wireless_uart_send_buffer(vofa.tail, 4);

	sprintf(send_data, "%d", Pwm[0]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", Pwm[1]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", Pwm[2]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", Pwm[3]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", encoder_data[0]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", encoder_data[1]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", encoder_data[2]);
	wireless_uart_send_string(send_data);
	wireless_uart_send_string(",");
	sprintf(send_data, "%d", encoder_data[3]);
	wireless_uart_send_string(send_data);
	

	wireless_uart_send_string("\n");
	
    //均值滤波
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

	//imu660ra_init();
	//imu660_zeroBias();
	my_motor_init();	//--->>>>>>>>>注意这里的D12-D15引脚与ips200的csi重复使用，不能同时使用
	my_encoder_init();	//对屏幕显示可能也有影响
	//my_servo_init();
	my_image_init();
    wireless_uart_init();
	//ImagePerspective_Init();
	
	//ips200_show_float(0,240,Gyro_Bias.Zdata,6,3);
	//timer_init(GPT_TIM_1,TIMER_US);
	pit_ms_init(PIT_CH1, 5);
	
	interrupt_set_priority(LPUART8_IRQn,0);
	interrupt_set_priority(PIT_IRQn, 1);
	interrupt_global_enable(0);
    // 此处编写用户代码 例如外设初始化代码等
	

	vofa.tail[0] = 0x00;
	vofa.tail[1] = 0x00;
	vofa.tail[2] = 0x80;
	vofa.tail[3] = 0x7f;

    while(1)
    {
		//printf("%d, %d, %d, %d\n", Pwm[0],Pwm[1], Pwm[2], Pwm[3]);
// 		uint8 data_len = wireless_uart_read_buffer(data_buffer, 32);  
// 		if(data_len != 0)                                                       // 收到了消息 读取函数会返回实际读取到的数据个数
//         {
//             //wireless_uart_send_buffer(data_buffer, data_len);                     // 将收到的消息发送回去
//             //memset(data_buffer, 0, 32);
// //			removeFirstNChars((char*)data_buffer, 2) ;
// //            func_str_to_int((char *)data_buffer);
// 			sscanf((const char*)data_buffer, "@:%d,%d",&v_x, &v_y);
// 			memset(data_buffer, 0, 32);
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

		if(mt9v03x_finish_flag)
        {
		 	mt9v03x_finish_flag = 0;
			//Image_change((uint8 **)mt9v03x_image, MT9V03X_W, MT9V03X_H);
		 	//image_process();
         	// ips200_displayimage03x((const uint8 *)mt9v03x_image,MT9V03X_W,MT9V03X_H);
 			ips200_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
//			ips200_show_gray_image(100, 0, (const uint8 *)image_changed, MT9V03X_W-2, MT9V03X_H-2, 188-2, 120-2, 0);
			//ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
  			
			//start _finish_line_find();
			
 			find_middle();
			Slope= slope();
			//ips114_clear();
 			// if(start_finish_line_find())ips200_draw_square(60,100,8,RGB565_PINK);
		}

			 
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

        // 此处编写需要循环执行的代码
		
    }

}

//定时器测量时间
//			 timer_start(GPT_TIM_1);			 			 
//			 timer_stop(GPT_TIM_1);
//			 uint32 time = timer_get(GPT_TIM_1);
//			 timer_clear(GPT_TIM_1);
//			 ips200_show_int(50, 50, time, 4);

