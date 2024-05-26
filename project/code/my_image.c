#include "zf_common_headfile.h"
#include "my_image.h"
#include <math.h>

uint8 Image_Mode = 0;				//图像处理模式， 详见最下面的pit_handler_2()

int16 Slope;						//图像斜率
uint8 cross_flag = 0, roundabout_flag = 0;//环岛十字的标志位，1为到达此处
int8 cross_dir = 0, roundabout_dir = 0;			//十字方向，-1：左十字， 1：右十字； 环岛方向，-1: 左环岛， 1: 右环岛

uint8 boder_L[MT9V03X_H - 5];		//左边扫线（左边界 黄色）
uint8 boder_R[MT9V03X_H - 5];		//右边扫线（右边界 绿色）
uint8 boder_M[MT9V03X_H - 5];		//中线 （蓝色）
uint8 boder_U[MT9V03X_W] = {0};		//上边扫线（上边线 红色）
uint8 diff_boder_L[MT9V03X_H - 6];	//左边界相邻行的点的x坐标之差
uint8 diff_boder_R[MT9V03X_H - 6];	//右边界相邻行的点的x坐标之差
uint8 diff_boder_U[MT9V03X_W-1]; 	//差值
uint8 boder_correct[60];			//用于边线矫正的采样数据点（y坐标）
uint8 longest, index;				//最长白列对应的纵坐标和横坐标

int16 a, b;							//差比和中的a,b
int16 sideline_angle = 0, sideline_distance = 0;///边界矫正的边线倾角误差、边线距离误差（通过这两个数据传入边线矫正的两个并级PID进行边线矫正）
uint8 white_value = 120;			//参考白点默认值

uint32 track_wide = 0;				//赛道宽度(取图像中间三分之一高度的平均赛道宽度)
uint8 lose_point_num_L = 0, lose_point_num_R= 0;		//左、右边线丢线点数

void my_image_init()
{
	mt9v03x_init();
	mt9v03x_set_exposure_time(320);//120
	system_delay_ms(100);
	//设置自动曝光时间以应对差异较大的光线环境？？？
	pit_ms_init(PIT_CH2,5);	//计算斜率、环岛十字的周期
}

//计算白色参考阈值
uint8 find_white_point(uint8 image_array[][188])
{
	uint16 total = 0, cnt=0;
	for (uint8 i = 0; i < 20; i += 2)		//共10列
	{
		for (uint8 j = 0; j < 8; j += 4)	//共2行
		{
			if (image_array[84 + i][100 + j] > 55)//过滤掉灰度太低的像素点 //55
			{
				cnt++;
				total += image_array[84 + i][100 + j];
			}
		}
	}
	//ips114_show_int(188, 70, total / 20, 3);
	//	ips114_draw_point(90,80,RGB565_BLUE);
	//	ips114_draw_point(91,80,RGB565_BLUE);
	//	ips114_draw_point(90,81,RGB565_BLUE);
	//	ips114_draw_point(91,81,RGB565_BLUE);
	if (cnt)return total / (cnt);
	else return 120; //若所选区域为黑则直接返回120作为白色
}



//-----------------------------------------------------------------------------------------------
// 函数简介  找最长白列(y最小)
// 参数说明  longest：存放最长白列长度(y值)的数据的地址，对应前面的全局变量uint8 longest
// 参数说明  index：存放最长白列对应索引(x值)的数据的地址，对应前面的全局变量uint8 index
// 返回参数  void
// 使用示例  find_longest(&longest, &index);
// 备注信息  本函数在下面的find_middle()函数中被调用
//-----------------------------------------------------------------------------------------------
uint8 y_threshold = 22;//12 纵向扫线对比度阈值
void find_longest(uint8* longest, uint8* index)
{
	// //----------------找左右边界起点-----------------
	// for (uint8 i = middle; i > 10; i--)
	// {
	// 	if (i - 5 < 0)break;
	// 	if (100 * abs(mt9v03x_image[MT9V03X_H - 10][i] - mt9v03x_image[MT9V03X_H - 10][i - 5]) / (mt9v03x_image[MT9V03X_H - 10][i] + mt9v03x_image[MT9V03X_H - 10][i - 5] + 1) > 25)//分母加个1防止除0
	// 	{
	// 		ips114_draw_circle(i, MT9V03X_H - 10, 4, RGB565_PURPLE);
	// 		break;
	// 	}
	// }
	// for (uint8 i = middle; i < MT9V03X_W; i++)
	// {
	// 	if (i + 5 > MT9V03X_W)break;
	// 	if (100 * abs(mt9v03x_image[MT9V03X_H - 10][i] - mt9v03x_image[MT9V03X_H - 10][i + 5]) / (mt9v03x_image[MT9V03X_H - 10][i] + mt9v03x_image[MT9V03X_H - 10][i + 5] + 1) > 25)//分母加个1防止除0
	// 	{
	// 		ips114_draw_circle(i, MT9V03X_H - 10, 4, RGB565_PURPLE);
	// 		break;
	// 	}
	// }
	// //-----------------------------------------------

	uint8 high_l = 0, high_r = 0, highest_count = 0;//第一个满屏白列(靠左边)， 最后一个满屏白列(靠右边)， 满屏白列计数值
	uint16 high_sum = 0;	//所有满屏白列x坐标求和值
	*longest = MT9V03X_H - 10;
	white_value = 0.7 * 130 + 0.3 * find_white_point(mt9v03x_image);
	// ips114_show_int(188, 90, white_value, 3);
	for (uint8 i = 0; i < MT9V03X_W; i += 2)		//+=5
	{
		for (int16 j = MT9V03X_H - 6; j >= 0; j -= 1)		//???????,要减个10，边缘灰度值很大?????????//待优化-=3？
		{
			a = j;
			b = a + 4;

			//uint8 value_1 = 100 * abs(mt9v03x_image[a][i] - mt9v03x_image[b][i]) / (mt9v03x_image[a][i] + mt9v03x_image[b][i] + 1);//>>>>>>>分母加个1,防止除0
			uint8 value_2 = 100 * abs(mt9v03x_image[a][i] - white_value) / (mt9v03x_image[a][i] + white_value + 1);
			if (value_2 < y_threshold && a <= 2)	//若一列最上边为白色，说明这一列是满屏高度
			{
				//纪录满屏高度白列数量以及x坐标之和，最后取平均值，作为最长白列的index
				highest_count++;
				high_sum += i;	
				//ips114_draw_point(i, j, RGB565_RED);
			}
			if (value_2 > y_threshold)//25
			{	
				//ips114_draw_point(i, j, RGB565_RED); //j
				boder_U[i] = j;

				if (i >= middle - 30 && i < middle + 30)
				{  
					boder_correct[i - middle + 30] = j;
				}

				if (j < *longest) //更新最长白列
				{
					*longest = j; //j
					*index = i;
				}
			
				break;//每列找到第一个黑点后就不再继续往后找了，直接进行下一列
			}

		}
	}
	//ips114_show_uint(50,50,high_l,3);
	//ips114_show_uint(80,50,high_r,3);

	if (high_l && high_r) *index = (high_l + high_r) / 2;	//顶部为空白，则返回这个index
	if (highest_count != 0 && high_sum != 0 && abs(high_sum /highest_count - *index) < 40)
	{
		*longest = 0; //j
		*index = high_sum / highest_count;
	}

	//ips114_show_int(150,80, high_sum / (highest_count+1) - *index, 3);
	//ips114_show_int(150, 90, high_sum / (highest_count+1) , 3);
}

//-----------------------------------------------------------------------------------------------
// 函数简介  计算中线
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
uint8 x_threshold = 15;//15横向扫线对比度阈值
#define SHORTEST (MT9V03X_H - 20)//定义最长白列的最短值，若还小于最短值，直接return，认为跑出赛道了
void find_middle()
{
	lose_point_num_L = 0;	//清零丢线点数
	lose_point_num_R = 0;	//清零丢线点数
	find_longest(&longest, &index);
	if(longest>SHORTEST)return;	//小于最短值，直接return，认为跑出赛道了
	//ips114_draw_line(index, MT9V03X_H - 10, index, longest, RGB565_PURPLE);

	//从最长列开始寻找左右边界
	for (uint8 i = longest; i < MT9V03X_H - 5; i++)
	{
		
		//找左边界
		for (int16 j = index; j >= 0; j -= 1)
		{
			if(index<5)//最长白列靠近了最左边
			{
				boder_L[i] = 0;
				//ips114_draw_point(0, i, RGB565_YELLOW);
				lose_point_num_L++;
				break;
			}

			a = j;
			b = a - 5;
			uint8 value_1 = 100 * abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b] + 1);	//>>>>>>>分母加个1,防止除0
			uint8 value_2 = 100 * abs(mt9v03x_image[i][b] - white_value) / (mt9v03x_image[i][b] + white_value + 1);
			if (b == 0) //若没有找到左边界点，则把最左点作为左边界点
			{
				boder_L[i] = 0;
				//ips114_draw_point(0, i, RGB565_YELLOW);
				lose_point_num_L++;
				break;
			}
			if (value_1*0.6 + value_2*0.4> x_threshold)
			{
				boder_L[i] = b;
				//ips114_draw_point(b, i, RGB565_YELLOW);
				break;
			}
		}

		//找右边界
		for (int16 j = index; j < MT9V03X_W; j += 1)
		{
			if (index > MT9V03X_W-6)//最长白列靠近了最右边
			{
				boder_R[i] = MT9V03X_W-1;
				//ips114_draw_point(MT9V03X_W-1, i, RGB565_GREEN);
				lose_point_num_R++;
				break;
			}
			a = j;
			b = a + 5;
			uint8 value_1 = 100 * abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b] + 1);//>>>>>>>分母加个1,防止除0
			uint8 value_2 = 100 * abs(mt9v03x_image[i][b] - white_value) / (mt9v03x_image[i][b] + white_value + 1);
			if (b == MT9V03X_W-1) //若没有找到右边界点，则把最右点作为右边界点
			{
				boder_R[i] = MT9V03X_W-1;
				//ips114_draw_point(MT9V03X_W-1, i, RGB565_GREEN);
				lose_point_num_R++;
				break;
			}
			if (value_1 * 0.6 + value_2 * 0.4 > x_threshold )
			{
				boder_R[i] = b;
				//ips114_draw_point(b, i, RGB565_GREEN);
				break;
			}
		}

		boder_M[i] = (boder_L[i] + boder_R[i]) / 2;
		//ips114_draw_point(boder_M[i], i, RGB565_BLUE);
	}
}


//-----------------------------------------------------------------------------------------------
// 函数简介  计算斜率
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
int16 slope()
{
	static int16 lastresult;
	if(longest>SHORTEST)return lastresult;	//小于最短值，认为跑出赛道了，就返回上次斜率，
	
	int16 sum1 = 0, sum2 = 0, result;
	for (uint8 i = longest; i <= MT9V03X_H - 10; i++)
	{
		sum1 += (int16)(boder_M[i] - middle);//原来是减去boder_M[MT9V03X_H - 10],有问题:在直道若平行偏离赛道一侧不会矫正回去 遂改为减去图像中间位置middle
		sum2 += (int16)(MT9V03X_H - 10 - i);
	}
	result = 50 * sum1 / (sum2+1); //分母加1防止除0;
	//ips114_show_int(188, 110, (const int32)result, 3);
	lastresult = result;
	return result;
}



//-----------------------------------------------------------------------------------------------
// 函数简介  边线矫正
// 参数说明  side_point：采集点数组的地址（对应前面的全局数组uint8 boder_correct[60];）
// 参数说明  sideline_angle：边线倾角的地址（对应前面的全局变量int16 sideline_angle）
// 参数说明  sideline_distance：边线距离的地址（对应前面的全局变量int16 sideline_angle）
// 返回参数  void
// 使用示例  sideline_correct(boder_correct, &sideline_angle, &sideline_distance)
// 备注信息  此函数调用后即可得到边线倾角误差和边线距离误差，再在my_motor.c文件中调用roundabout_move(&sideline_angle, &sideline_distance);就可实现环岛十字路段横向移动矫正
//-----------------------------------------------------------------------------------------------
void sideline_correct(uint8* side_point, int16* sideline_angle, int16* sideline_distance)
{
	uint16 y1 = 0, y2 = 0;
	for (uint8 i = 0; i < 10; i++)
	{
		y1 += side_point[i];
		y2 += side_point[59 - i];
	}
	*sideline_angle = (y1 - y2);
	*sideline_distance = (y1 + y2) / 2;

	// ips114_show_int(188, 0, *sideline_angle, 4);
	// ips114_show_int(188, 20, *sideline_distance, 4);
}


//-----------------------------------------------------------------------------------------------
// 函数简介  环岛十字识别
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  目前效果不理想，弃用，使用下面新写的cross()和roundabout()
//-----------------------------------------------------------------------------------------------
void roundabout_cross() 
{
	uint16 jump_point[4][2] = { {0} };//存放边线跳变点

	//求左边线相邻行点的x差值
	for (uint8 i = MT9V03X_H - 6; i >= longest + 1; i--)
	{
		diff_boder_L[i-1] = abs(boder_L[i] - boder_L[i - 1]); //diff_boder_L的i-1与boder_L的i-1对应
		if (diff_boder_L[i-1] > 15)
		{
			if (boder_L[i] > boder_L[i - 1] && (jump_point[0][0] * jump_point[0][1]) == 0) //左边线从下到上的第一个突变点
			{ 
				//ips114_draw_circle(boder_L[i], i, 4, RGB565_YELLOW)---; 
				jump_point[0][0] = boder_L[i];  jump_point[0][1] = i;
			}
			else { /*ips114_draw_circle(boder_L[i-1], i-1, 4, RGB565_YELLOW); ---*/}
		}
	}
	//求右边线相邻行点的x差值
	for (uint8 i = MT9V03X_H - 6; i >= longest + 1; i--)
	{
		diff_boder_R[i-1] = abs(boder_R[i] - boder_R[i - 1]);
		if (diff_boder_R[i-1] > 15)
		{
			if(boder_R[i] < boder_R[i - 1] && (jump_point[1][0] * jump_point[1][1]) == 0 && (jump_point[0][0] * jump_point[0][1]) != 0)  //右边线从下到上的第一个突变点
			{
				//ips114_draw_circle(boder_R[i], i, 4, RGB565_GREEN);---
				jump_point[1][0] = boder_R[i];  jump_point[1][1] = i;
			}
			else { /*ips114_draw_circle(boder_R[i-1], i-1, 4, RGB565_GREEN);-*/ }
		}
	}
	//求上边线相邻列点的y差值
	for (uint8 i = 2; i < MT9V03X_W; i+=2)
	{
		diff_boder_U[i] = abs(boder_U[i] - boder_U[i - 2]);
		if (diff_boder_U[i] > 15 && i<90) // 限制X坐标范围，可以判断左右边线
		{
			//ips114_draw_point(30, 30, RGB565_CYAN);
			//ips114_draw_point(i-2, boder_U[i-2], 1, RGB565_CYAN);

			//ips114_draw_circle(i - 2, boder_U[i - 2], 4, RGB565_RED);-------
			jump_point[2][0] = i - 2;  jump_point[2][1] = boder_U[i - 2];
		}
		if (diff_boder_U[i] > 15 && i > 90 && jump_point[2][0]!=0) // 限制X坐标范围，可以判断左右边线
		{
			jump_point[3][0] = i;  jump_point[3][1] = boder_U[i];
			//ips114_draw_point(30, 30, RGB565_CYAN);
			////ips114_draw_point(i-2, boder_U[i-2], 1, RGB565_CYAN);
			//ips114_draw_circle(i, boder_U[i], 4, RGB565_RED);-------------
			//jump_point[1][0] = i - 2;  jump_point[1][1] = boder_U[i - 2];
		}
	}
	uint16 x1 = abs(jump_point[0][0] - jump_point[2][0]);
	uint16 y1 = abs(jump_point[0][1] - jump_point[2][1]);
	uint16 x2 = abs(jump_point[1][0] - jump_point[3][0]);
	uint16 y2 = abs(jump_point[1][1] - jump_point[3][1]);
	uint16 distance1 = x1 * x1 + y1 * y1;
	uint16 distance2 = x2 * x2 + y2 * y2;
	if (distance1 <= 40 && jump_point[0][0]*jump_point[2][0] != 0) {
		ips114_show_int(0, 110, x1, 2);
		ips114_show_int(30, 110, y1, 2);
		ips114_show_string(0, 0, "RA") ;

		roundabout_flag = 1;
	}
	if (distance2 <= 40 && jump_point[1][0]*jump_point[3][0] != 0) {
		ips114_show_int(60, 110, x2, 2);
		ips114_show_int(90, 110, y2, 2);
		ips114_show_string(120, 0, "CR");
		
		cross_flag = 1;
	}
}

#define track_wide_limit		(MT9V03X_W * MT9V03X_H * 4 / 15)	//十字|环岛路段的赛道宽度判断限制
#define start_height 			(MT9V03X_H / 3)						//计算赛道宽度的开始行
#define end_height 				(MT9V03X_H * 2 / 3)					//计算赛道宽度的结束行
#define cross_longest_limit 	20		//十字路段最长白列判断限制
#define cross_slope_limit		12		//十字路段最大斜率判断限制
#define lose_point_num_limit_1	70		//丢线点数限制1
#define lose_point_num_limit_2	5		//丢线点数限制2
//-----------------------------------------------------------------------------------------------
// 函数简介  十字路段状态机
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  
//-----------------------------------------------------------------------------------------------
void cross()//十字
{
	track_wide = 0;	//清零上次计算的赛道宽度
	if(cross_flag == 0)
	{
		for (uint16 i = start_height; i < end_height; i++)
		{
			track_wide += (boder_R[i] - boder_L[i]);//注意这里是：累加赛道宽度
		}
		//ips114_show_int(90, 70, track_wide/ MT9V03X_W, 2);
		if (track_wide > track_wide_limit && longest < cross_longest_limit)//限制一个最长白列的最短长度限制，长度大于此值认为是急弯过滤掉
		{
			//通过左右丢线点数再一次过滤，避免环岛误判
			if(lose_point_num_L > lose_point_num_limit_1 && lose_point_num_R > lose_point_num_limit_1)
			{
				cross_flag = 1;		//检测到十字路段的宽度变化，且左右都丢线
			}
		}	

	}
	else if(cross_flag == 1)
	{
		if(abs(Slope)>cross_slope_limit)
		{
			if(Slope<0)cross_dir = -1;
			else cross_dir = 1;
			cross_flag = 2;		//检测到斜率增大到限制，即已经进入十字，下一步进行90度转向
		}
	}
	else if(cross_flag == 2)
	{
		if(longest<5 && turn_flag == 1)	//出十字判断，一般情况出十字最长白列会突然变长（直接到图像最上方）
		{
			cross_flag = 3;		//检测到最长白列长度突然变大，说明即将走出十字，下一步90度转向
		}
	}
	else if(cross_flag == 3)
	{
		if(Image_Mode == 0)
		{
			cross_flag=0;		//确保走出十字才复位十字标志位
		}
	}	
}


//-----------------------------------------------------------------------------------------------
// 函数简介  环岛路段状态机
// 参数说明  
// 返回参数  void
// 使用示例  
// 备注信息  环岛判断函数需放在十字判断后面调用,因为环岛使用了在十字判断函数中计算的赛道宽度
//-----------------------------------------------------------------------------------------------
void roundabout()
{
	if(roundabout_flag == 0)
	{
		if(track_wide > track_wide_limit && longest < cross_longest_limit )	//借用十字的赛道宽度判断
		{
			//左环岛
			if(lose_point_num_L > lose_point_num_limit_1 && lose_point_num_R < lose_point_num_limit_2)
			{
				roundabout_flag = 1;		//检测到环岛路段宽度变化且左右边线只有一边丢线
				roundabout_dir = -1;		//标记环岛方向
			}
			//右环岛
			else if(lose_point_num_L < lose_point_num_limit_2 && lose_point_num_R > lose_point_num_limit_1)
			{
				roundabout_flag = 1;		//检测到环岛路段宽度变化且左右边线只有一边丢线
				roundabout_dir = 1;			//标记环岛方向
			}
		}
	}
	else if(roundabout_flag == 1)
	{
		if(longest < 5 && (roundabout_dir>0?(index < MT9V03X_W/2): (index > MT9V03X_W/2)))	//(index < roundabout_dir*MT9V03X_W/2)-->防止进入环岛刚转向时识别为出环岛
		{
			roundabout_flag = 2;		//检测到最长白列长度突然变大，说明即将走出环岛，下一步90度转向
		}
	}
	else if(roundabout_flag == 2)
	{
		if(turn_flag == 1)roundabout_flag=3;	//转向完成(继检测到最长白列高度突变后); 用模式1走到环岛对侧的卡片放置区放完卡片在回到原处
	}
	else if(roundabout_flag == 3)
	{
		if(Image_Mode == 0)roundabout_flag=0;	//在回到循迹模式时清除环岛标志位
	}
}

//-----------------------------------------------------------------------------------------------
// 函数简介  始终线判断
// 参数说明  
// 返回参数  0-没有检测到始终线， 1-检测到始终线
// 使用示例  
// 备注信息  定义的阈值参数可调，还未达到最理想的状态
//-----------------------------------------------------------------------------------------------
#define GrayThreshold	85	//灰度阈值界限， 小于此值认为是黑点，大于此值认为是白点
uint8 find_start_finish_line()
{
	uint8 judge_state = 0;		//判断状态
	uint8 black_block_num = 0;	//统计的斑马线黑色块数量
	for(uint8 i = 0; i<MT9V03X_W; i++)
	{
		switch(judge_state)
		{
			case 0:{if(mt9v03x_image[70][i]>GrayThreshold)judge_state = 1; break;}
			case 1:{if(mt9v03x_image[70][i]<GrayThreshold)judge_state = 2; break;}
			case 2:{if(mt9v03x_image[70][i]>GrayThreshold){judge_state = 1;black_block_num++;} break;}
		}
	}
	//ips114_show_int(70,70,black_block_num, 3);
	if(black_block_num>7)return 1;//黑色块大于7个就认为是斑马线了
	else return 0;
}

void pit_handler_2()
{
	if(mt9v03x_finish_flag)
    {
	 	mt9v03x_finish_flag = 0;
		//ips114_show_gray_image(0, 0, (const uint8 *)mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
		//find_start_finish_line();
		
		switch (Image_Mode)		//不同的图像处理模式
		{
			case 0:
			    find_middle();
				Slope = slope();
				cross();
				roundabout();
			    break;
			case 1:
				find_middle();
				cross();
				roundabout();
				sideline_correct(boder_correct, &sideline_angle, &sideline_distance);
				break;
			case 2:	//赛道两边找卡片时的边界矫正
				find_longest(&longest, &index);
				sideline_correct(boder_correct, &sideline_angle, &sideline_distance);
			    break;
			case 3:
				find_middle();
				Slope = slope();
			    break;
			case 4:
			    break;

		}
 		
		//sideline_correct(boder_correct, &sideline_angle, &sideline_distance);
		
		
	}
}





//---------------------------以下为未使用-------------------------------
/*!
 *  @brief      大津法二值化0.8ms程序
 *  @date:   2018-10
 *  @since      v1.2
 *  *image ：图像地址
 *  width:  图像宽
 *  height：图像高
 *  @author     Z小旋
 */

uint8 otsu(uint8* image, uint16 width, uint16 height)
{
#define GrayScale 256
	int pixelCount[GrayScale] = { 0 };//每个灰度值所占像素个数
	float pixelPro[GrayScale] = { 0 };//每个灰度值所占总像素比例
	int i, j;
	int Sumpix = width * height;   //总像素点
	uint8 threshold = 0;
	uint8* data = image;  //指向像素数据的指针


	//统计灰度级中每个像素在整幅图像中的个数
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
			//   pixelCount[(int)image[i][j]]++;    若不用指针用这个
		}
	}
	float u = 0;
	for (i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / Sumpix;   //计算每个像素在整幅图像中的比例
		u += i * pixelPro[i];  //总平均灰度
	}


	float maxVariance = 0.0;  //最大类间方差
	float w0 = 0, avgValue = 0;  //w0 前景比例 ，avgValue 前景平均灰度
	for (int i = 0; i < 256; i++)     //每一次循环都是一次完整类间方差计算 (两个for叠加为1个)
	{
		w0 += pixelPro[i];  //假设当前灰度i为阈值, 0~i 灰度像素所占整幅图像的比例即前景比例
		avgValue += i * pixelPro[i];

		float variance = pow((avgValue / w0 - u), 2) * w0 / (1 - w0);    //类间方差
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = (uint8)i;
		}
	}


	return threshold;

}


//梯度图像
uint8 t_b = 30, k = 1;
uint8 x_operator[8][2] = { {0,1}, {-1,1}, {-1,0}, {0,-1}, {1,-1}, {1,0}, {1,1} };
uint8 image_changed[MT9V03X_H - 2][MT9V03X_W - 2];
void Image_change(uint8 image[][MT9V03X_W], uint16 width, uint16 height)
{
	for (uint8 i = 1; i <= MT9V03X_W - 2; i++)
	{
		for (uint8 j = 1; j <= MT9V03X_H - 2; j++)
		{
			//image_changed[j-1][i-1] = k*(image[j][i+1] - image[j][i-1] + image[j+1][i] - image[j-1][i] + t_b);
			int16 x_diff = (image[j][i + 1] - image[j][i - 1]);
			int16 y_diff = (image[j + 1][i] - image[j - 1][i]);
			image_changed[j - 1][i - 1] = (uint8)sqrt(x_diff * x_diff + y_diff * y_diff);
		}
	}
}



//灰度八领域
#define 	DISTANCE 	3
uint8 l_edge[MT9V03X_H] = { 0 };
uint8 r_edge[MT9V03X_H] = { 0 };
static uint8 start_point_l[2] = { 0 };
static uint8 start_point_r[2] = { 0 };

void find_start_point(uint8 image[][188])
{
	for (uint8 i = MT9V03X_W - 5; i > MT9V03X_W - 15; i--)
	{
		for (uint8 j = 0; j < MT9V03X_W / 2; j++)
		{
			if (middle - j - 5 < 0 || middle + j + 5 > MT9V03X_W)
			{
				break;
			}
			else
			{
				//左起点
				if (100 * abs(image[i][middle - j] - image[i][middle - j - 5]) / (image[i][middle - j] + image[i][middle - j - 5]) > 20)
				{
					start_point_l[0] = middle + j; start_point_l[1] = i;
				}
				//右起点
				if (100 * abs(image[i][middle + j] - image[i][middle + j + 5]) / (image[i][middle + j] + image[i][middle + j + 5]) > 20)
				{
					start_point_r[0] = middle - j; start_point_r[1] = i;
				}
			}
		}
	}
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>逆透视变换>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// Created by RUPC on 2022/9/20.
//


//void ImagePerspective_Init(void) {
// 
//    static uint8_t BlackColor = 0;
//    double change_un_Mat[3][3] = {          //114w*100h
//            { -0.01609759704190238, 0.01932561893613478, -2.040617594981866 }, {
//                    0.0004352209945470896, -0.000367865364438621,
//                    -0.7035606436969671 }, { 1.115951268069474e-005,
//                    0.0001970185393508392, -0.03104642853440032 }, };
//    for (int i = 0; i < RESULT_COL ;i++) {
//        for (int j = 0; j < RESULT_ROW ;j++) {
//            int local_x = (int) ((change_un_Mat[0][0] * i
//                    + change_un_Mat[0][1] * j + change_un_Mat[0][2])
//                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
//                            + change_un_Mat[2][2]));
//            int local_y = (int) ((change_un_Mat[1][0] * i
//                    + change_un_Mat[1][1] * j + change_un_Mat[1][2])
//                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
//                            + change_un_Mat[2][2]));
//            if (local_x
//                    >= 0&& local_y >= 0 && local_y < USED_ROW && local_x < USED_COL){
//                PerImg_ip[j][i] = &PER_IMG[local_y][local_x];
//            }
//            else {
//                PerImg_ip[j][i] = &BlackColor;          //&PER_IMG[0][0];
//            }
// 
//        }
//    }
// 
//}
 
 
//完成摄像头初始化后，调用一次ImagePerspective_Init，此后，直接调用ImageUsed   即为透视结果
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<逆透视变换<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

