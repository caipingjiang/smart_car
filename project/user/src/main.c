#include "zf_common_headfile.h"
#include "my_moter.h"
#include "my_servo.h"
#include "my_encoder.h"
#include "my_image.h"
#include "image.h"
#include "math.h"
#include "imu660ra.h"

int16 Slope ;
char send_data[10]={0};

float angle=0;                //数据融合后的角度 


extern int16 Target_Speed;
extern int16 v_x, v_y;
uint16 count=0;
float tra_acc_x, tra_acc_y, tra_acc_z, tra_gyro_x,tra_gyro_y, tra_gyro_z;



void pit_handler_1()
{
//	 sprintf(send_data, "%f", Slope);
//     wireless_uart_send_string(send_data);
//     wireless_uart_send_string("\n");
//	count++;
//	count%=2;
//	if(count == 1)Target_Speed = 25;
//	else Target_Speed = -25;

    //均值滤波
    float min=0, max=0, temp_angle;
	for(uint8 i=0; i<10; i++)
	{
		//imu660ra_get_acc();
		imu660ra_get_gyro();
		tra_gyro_z = (imu660ra_gyro_transition(imu660ra_gyro_z));

        (tra_gyro_z>max) ? (max=tra_gyro_z):0;
		(tra_gyro_z<min) ? (min=tra_gyro_z):0;
        temp_angle += tra_gyro_z;
	}
    tra_gyro_z = (temp_angle - min - max)/8;
	//imu660ra_get_acc();
	//imu660ra_get_gyro();
	//tra_gyro_z = (imu660ra_gyro_transition(imu660ra_gyro_z)+0.0160  );
	
	angle += (tra_gyro_z*0.005-Gyro_Bias.Zdata);
	
//	angle = angle_calc(imu963ra_acc_y, imu660ra_gyro_z);
//	sprintf(send_data, "%d", w);
//	wireless_uart_send_string(send_data);
//	wireless_uart_send_string("\n");
	// w = (int16)w_PID(180, tra_gyro_z);
}
int main(void)
{
	
    clock_init(SYSTEM_CLOCK_600M);  // 不可删除
    debug_init();                   // 调试端口初始化
	system_delay_ms(500);

	//注意！！！屏幕对电机有影响
//	spi_init(SPI_1, 0, 1*1000*1000, SPI1_SCK_D12, SPI1_MOSI_D14, SPI1_MISO_D15, SPI1_CS0_D13);
////	ips200_init(IPS200_TYPE_SPI);
	//ips200_init(IPS200_TYPE_PARALLEL8);
	
    // 此处编写用户代码 例如外设初始化代码等
	my_motor_init();	//--->>>>>>>>>注意这里的D12-D15引脚与ips200的csi重复使用，不能同时使用
	my_encoder_init();	//对屏幕显示可能也有影响
	//my_servo_init();
	my_image_init();
    wireless_uart_init();
	//ImagePerspective_Init();
	//imu660ra_init();
	//imu660_zeroBias();
	//ips200_show_float(0,240,Gyro_Bias.Zdata,6,3);
	//timer_init(GPT_TIM_1,TIMER_US);
	//pit_ms_init(PIT_CH1, 5);
	
	//interrupt_set_priority(LPUART8_IRQn,0);
	interrupt_set_priority(PIT_IRQn, 1);
	interrupt_global_enable(0);
    // 此处编写用户代码 例如外设初始化代码等
	
    while(1)
    {
		// Target_Speed = 35;
		// system_delay_ms(4000);
//		Target_Speed = -35;
//		system_delay_ms(4000);
//        sprintf(send_data, "%f", tra_gyro_x);
//		wireless_uart_send_string(send_data);
//		wireless_uart_send_string(",");
//        sprintf(send_data, "%f", tra_gyro_y);
//        wireless_uart_send_string(send_data);
//		wireless_uart_send_string(",");
//		sprintf(send_data, "%f", tra_gyro_z);
//		wireless_uart_send_string(send_data);
//		wireless_uart_send_string("\n");
//        for(uint8 i=0; i<8; i++)
//        {
//            if(i<4) sprintf(send_data, "%d", encoder_data[i]);
//            else    sprintf(send_data, "%d", Pwm[i-4]);
//            if(i==0) wireless_uart_send_string("V:");
//            wireless_uart_send_string(send_data); 
//            if(i<7) wireless_uart_send_string(",");
//            else    wireless_uart_send_string(",");
//        }        
//        sprintf(send_data, "%f", Inc_Kp[1]);
//        wireless_uart_send_string(send_data);
//        wireless_uart_send_string(",");
//        sprintf(send_data, "%f", Inc_Ki[1]);
//        wireless_uart_send_string(send_data);
//        wireless_uart_send_string(",");
//        sprintf(send_data, "%f", Inc_Kd[1]);
//        wireless_uart_send_string(send_data);
//        wireless_uart_send_string("\n");

//        ips200_show_float(0,0,tra_acc_x,5,3);
//        ips200_show_float(0,20,tra_acc_y,5,3);
//        ips200_show_float(0,40,tra_acc_z,5,3);
//        ips200_show_float(0,60,tra_gyro_x,5,3);
//        ips200_show_float(0,80,tra_gyro_y,5,3);
        //  ips200_show_float(0,100,angle,6,3);

        // ips200_show_float(0.,250,imu660ra_gyro_z,6,3);
         //ips200_show_float(0,280,imu660ra_gyro_transition(imu660ra_gyro_z),6,3);
 		 if(mt9v03x_finish_flag)
          {
 			 
 			 //image_process();
              //ips200_displayimage03x((const uint8 *)mt9v03x_image,MT9V03X_W,MT9V03X_H);
  			//ips200_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
 //			ips200_show_gray_image(0, 0, (const uint8 *)mt9v03x_image,MT9V03X_W, MT9V03X_H,240,153,threshold );
 //			 timer_start(GPT_TIM_1);
  			//start_finish_line_find();
 			 find_middle();
 			
			Slope= slope();
			sprintf(send_data, "%d", Slope);
			wireless_uart_send_string(send_data);
			 wireless_uart_send_string(",");
			 sprintf(send_data, "%f", Kp_T); 
			  wireless_uart_send_string(send_data);
			  wireless_uart_send_string(",");
			 sprintf(send_data, "%f", Kd_T); 
			  wireless_uart_send_string(send_data);
			wireless_uart_send_string("\n");
			//system_delay_ms(5);              
			  mt9v03x_finish_flag = 0;
//  			if(start_finish_line_find())ips200_draw_square(60,100,8,RGB565_PINK);
		  }
			 
			 
			 
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

             
        // 此处编写需要循环执行的代码
      }
}



