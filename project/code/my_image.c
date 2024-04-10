#include "zf_common_headfile.h"
#include "my_image.h"
#include <math.h>
void my_image_init()
{
	mt9v03x_init();
	mt9v03x_set_exposure_time(120);
	system_delay_ms(100);

	//设置自动曝光时间以应对差异较大的光线环境？？？
}


#define		middle	MT9V03X_W/2
//边界点坐标与中线坐标
uint8 boder_L[MT9V03X_H - 5];		//左边扫线（左边界 黄色）
uint8 boder_R[MT9V03X_H - 5];		//右边扫线（右边界 绿色）
uint8 boder_M[MT9V03X_H - 5];		//中线 （蓝色）
uint8 boder_U[MT9V03X_W] = {0};		//上边扫线（上边线 红色）
uint8 diff_boder_L[MT9V03X_H - 6];	//差值
uint8 diff_boder_R[MT9V03X_H - 6];	//差值
uint8 diff_boder_M[MT9V03X_H - 6];	//差值
uint8 diff_boder_U[MT9V03X_W-1]; 	//差值
uint8 boder_correct[60];
uint8 red_point[25];
int8  diff_y[25];
uint8 longest, index;				//最长白列对应的纵坐标和横坐标
int16 a, b;							//差比和中的a,b
int16 sideline_err = 0, sideline_distance = 0;//边界矫正中与前方赛道边界的相对倾斜度，以及与边界的距离
uint8 white_value = 120;			//差比和中的a,b


//计算白色参考阈值
uint8 find_white_point(uint8 image_array[][188])
{
	uint16 total = 0;
	for (uint8 i = 0; i < 18; i += 2)
	{
		for (uint8 j = 0; j < 10; j += 2)
		{
			total += image_array[90 + i][90 + j];
		}
	}
	ips114_show_int(90, 70, total / 45, 3);
	//	ips114_draw_point(90,80,RGB565_BLUE);
	//	ips114_draw_point(91,80,RGB565_BLUE);
	//	ips114_draw_point(90,81,RGB565_BLUE);
	//	ips114_draw_point(91,81,RGB565_BLUE);
	return total/45;
}


uint8 y_threshold = 22;//12
void find_longest(uint8* longest, uint8* index)
{
	//----------------找左右边界起点-----------------
	for (uint8 i = middle; i > 10; i--)
	{
		if (i - 5 < 0)break;
		if (100 * abs(mt9v03x_image[MT9V03X_H - 10][i] - mt9v03x_image[MT9V03X_H - 10][i - 5]) / (mt9v03x_image[MT9V03X_H - 10][i] + mt9v03x_image[MT9V03X_H - 10][i - 5] + 1) > 25)//分母加个1防止除0
		{
			ips114_draw_circle(i, MT9V03X_H - 10, 4, RGB565_PURPLE);
			break;
		}
	}
	for (uint8 i = middle; i < MT9V03X_W; i++)
	{
		if (i + 5 > MT9V03X_W)break;
		if (100 * abs(mt9v03x_image[MT9V03X_H - 10][i] - mt9v03x_image[MT9V03X_H - 10][i + 5]) / (mt9v03x_image[MT9V03X_H - 10][i] + mt9v03x_image[MT9V03X_H - 10][i + 5] + 1) > 25)//分母加个1防止除0
		{
			ips114_draw_circle(i, MT9V03X_H - 10, 4, RGB565_PURPLE);
			break;
		}
	}
	//-----------------------------------------------

	uint8 high_l = 0, high_r = 0, highest_count = 0;
	uint16 high_sum = 0;
	*longest = MT9V03X_H - 10;
	white_value = 0.7 * 130 + 0.3 * find_white_point(mt9v03x_image);
	ips114_show_int(90, 90, white_value, 3);
	for (uint8 i = 0; i < MT9V03X_W; i += 2)		//+=5
	{
		for (int16 j = MT9V03X_H - 6; j >= 0; j -= 1)		//???????,要减个10，边缘灰度值很大?????????//待优化-=3？
		{
			a = j;
			b = a + 4;

			uint8 value_1 = 100 * abs(mt9v03x_image[a][i] - mt9v03x_image[b][i]) / (mt9v03x_image[a][i] + mt9v03x_image[b][i] + 1);//>>>>>>>分母加个1,防止除0
			uint8 value_2 = 100 * abs(mt9v03x_image[a][i] - white_value) / (mt9v03x_image[a][i] + white_value + 1);
			if (value_1 * 0 + value_2 * 1 < y_threshold && a <= 2)
			{
				highest_count++;
				high_sum += i;
				ips114_draw_point(i, j, RGB565_RED);
			}
			if ((value_1 * 0 + value_2 * 1) > y_threshold)//25
			{	
				ips114_draw_point(i, j, RGB565_RED); //j
				boder_U[i] = j;

				if (i >= middle - 30 && i < middle + 30)
				{  
					boder_correct[i - middle + 30] = j;
					ips114_draw_line(middle - 30, 20, middle + 30, 20, RGB565_GREEN);
				}

				if (j < *longest)
				{
					*longest = j; //j
					*index = i;
				}
				//if (j <= 20 && 100 * abs(mt9v03x_image[0][i + 14] - white_value) / (mt9v03x_image[0][i + 14] + white_value) < 12 && high_l == 0)
				//{
				//	high_l = *index;  //最高处为空白，则记录从那一列开始最高处空白
				//	ips114_draw_circle(high_l, j, 3, RGB565_RED);
				//	break;
				//}
				//if (j <= 20 && 100 * abs(mt9v03x_image[0][i - 14] - white_value) / (mt9v03x_image[0][i - 14] + white_value) < 12 && high_l != 0 && high_r == 0)
				//{
				//	high_r = *index;
				//	ips114_draw_circle(high_r, j, 3, RGB565_YELLOW);
				//	break;
				//}
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

uint8 x_threshold = 15;//15
void find_middle()
{

	find_longest(&longest, &index);
	ips114_draw_line(index, MT9V03X_H - 10, index, longest, RGB565_PURPLE);

	//从最长列开始寻找左右边界
	for (uint8 i = longest; i < MT9V03X_H - 5; i++)
	{
		//找左边界
		for (int16 j = index; j >= 0; j -= 1)
		{
			if(index<5)//最长白列靠近了最左边
			{
				boder_L[i] = 0;
				ips114_draw_point(0, i, RGB565_YELLOW);
				break;
			}

			a = j;
			b = a - 5;
			uint8 value_1 = 100 * abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b] + 1);	//>>>>>>>分母加个1,防止除0
			uint8 value_2 = 100 * abs(mt9v03x_image[i][b] - white_value) / (mt9v03x_image[i][b] + white_value + 1);
			if (b == 0) //若没有找到左边界点，则把最左点作为左边界点
			{
				boder_L[i] = 0;
				ips114_draw_point(0, i, RGB565_YELLOW);
				break;
			}
			if (value_1*0.6 + value_2*0.4> x_threshold)
			{
				boder_L[i] = b;
				ips114_draw_point(b, i, RGB565_YELLOW);
				break;
			}
		}

		//找右边界
		for (int16 j = index; j < MT9V03X_W; j += 1)
		{
			if (index > MT9V03X_W-6)//最长白列靠近了最右边
			{
				boder_L[i] = 0;
				ips114_draw_point(0, i, RGB565_YELLOW);
				break;
			}
			a = j;
			b = a + 5;
			uint8 value_1 = 100 * abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b] + 1);//>>>>>>>分母加个1,防止除0
			uint8 value_2 = 100 * abs(mt9v03x_image[i][b] - white_value) / (mt9v03x_image[i][b] + white_value + 1);
			if (b == MT9V03X_W-1) //若没有找到右边界点，则把最右点作为右边界点
			{
				boder_R[i] = MT9V03X_W-1;
				ips114_draw_point(MT9V03X_W-1, i, RGB565_GREEN);
				break;
			}
			if (value_1 * 0.6 + value_2 * 0.4 > x_threshold )
			{
				boder_R[i] = b;
				ips114_draw_point(b, i, RGB565_GREEN);
				break;
			}
		}

		boder_M[i] = (boder_L[i] + boder_R[i]) / 2;
		ips114_draw_point(boder_M[i], i, RGB565_BLUE);
	}
}
void sideline_correct(uint8* side_point, int16* sideline_err, int16* sideline_distance);
int16 slope()
{
	sideline_correct(boder_correct, &sideline_err, &sideline_distance);
	int16 sum1 = 0, sum2 = 0, result;
	for (uint8 i = longest; i <= MT9V03X_H - 10; i++)
	{
		sum1 += (int16)(boder_M[i] - boder_M[MT9V03X_H - 10]);
		sum2 += (int16)(MT9V03X_H - 10 - i);
	}
	result = 50 * sum1 / (sum2+1); //分母加1防止除0;
	ips114_show_int(50, 80, (const int32)result, 3);

	return result;
}

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

//计算边线倾角，便于矫正
void sideline_correct(uint8* side_point, int16* sideline_err, int16* sideline_distance)
{
	uint16 y1 = 0, y2 = 0;
	for (uint8 i = 0; i < 10; i++)
	{
		y1 += side_point[i];
		y2 += side_point[59 - i];
	}
	*sideline_err = (y1 - y2);
	*sideline_distance = (y1 + y2) / 2;

	// uint16 odd_sum = 0, even_sum =0;
	// for (uint8 i = 0; i < 60; i++)
	// {
	// 	//&1相当于对2取余（%2）
	// 	if((i&1) == 1){odd_sum  += side_point[i];}
	// 	else{even_sum += side_point[i];}
	// }
	// *sideline_err = odd_sum - even_sum ;

//	double total_slope = 0.0;
//	for (uint8 i = 0; i < 59; i++) {
//		double slope = (side_point[i+1] - side_point[i]) /                      1.0; // 计算相邻点之间的斜率
//		total_slope += slope;
//	}
	// double average_slope = total_slope ; // 计算平均斜率
	// *sideline_err = average_slope; // 将平均斜率存储在sideline_err中

	//ips114_show_int(120, 20, *sideline_err, 5);
	//ips114_show_int(120, 40, *sideline_distance, 4);
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


void roundabout() //环岛
{
	for (uint8 i = MT9V03X_H - 6; i >= longest + 1; i--)
	{
		diff_boder_L[i-1] = abs(boder_L[i] - boder_L[i - 1]); //diff_boder_L的i-1与boder_L的i-1对应
		if (diff_boder_L[i-1] > 15)
		{
			if(boder_L[i] > boder_L[i - 1] ){ ips114_draw_circle(boder_L[i], i, 4, RGB565_YELLOW); }
			else { ips114_draw_circle(boder_L[i-1], i-1, 4, RGB565_YELLOW); }
		}
	}
	
	for (uint8 i = MT9V03X_H - 6; i >= longest + 1; i--)
	{
		diff_boder_R[i-1] = abs(boder_R[i] - boder_R[i - 1]);
		if (diff_boder_R[i-1] > 15)
		{
			if(boder_R[i] > boder_R[i - 1]){ ips114_draw_circle(boder_R[i], i, 4, RGB565_GREEN); }
			else { ips114_draw_circle(boder_R[i-1], i-1, 4, RGB565_GREEN); }
		}
	}

	for (uint8 i = 4; i < MT9V03X_W; i+=2)
	{
		diff_boder_U[i] = abs(boder_U[i] - boder_U[i - 4]);
		if(diff_boder_U[i]>20) ips114_draw_circle(i, diff_boder_U[i], 4, RGB565_RED);
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


