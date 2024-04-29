#include "zf_common_headfile.h"
#include "my_image.h"
#include <math.h>
void my_image_init()
{
	mt9v03x_init();
	mt9v03x_set_exposure_time(120);
	system_delay_ms(100);

	//�����Զ��ع�ʱ����Ӧ�Բ���ϴ�Ĺ��߻���������
}


#define		middle	MT9V03X_W/2
//�߽����������������
uint8 boder_L[MT9V03X_H - 5];		//���ɨ�ߣ���߽� ��ɫ��
uint8 boder_R[MT9V03X_H - 5];		//�ұ�ɨ�ߣ��ұ߽� ��ɫ��
uint8 boder_M[MT9V03X_H - 5];		//���� ����ɫ��
uint8 boder_U[MT9V03X_W] = {0};		//�ϱ�ɨ�ߣ��ϱ��� ��ɫ��
uint8 diff_boder_L[MT9V03X_H - 6];	//��߽������еĵ��x����֮��
uint8 diff_boder_R[MT9V03X_H - 6];	//��߽������еĵ��x����֮��
uint8 diff_boder_U[MT9V03X_W-1]; 	//��ֵ
uint8 road_width[MT9V03X_H - 5];  	//������ȣ����ұ߽��ȥ��߽�
uint8 boder_correct[60];			//���ڱ��߽����Ĳ������ݵ㣨y���꣩
uint8 longest, index;				//����ж�Ӧ��������ͺ�����

int16 a, b;							//��Ⱥ��е�a,b
int16 sideline_angle = 0, sideline_distance = 0;///�߽�����ı�����������߾�����ͨ�����������ݴ���߽�������������PID���б��߽�����
uint8 white_value = 120;			//�ο��׵��ֵ


//�����ɫ�ο���ֵ
uint8 find_white_point(uint8 image_array[][188])
{
	uint16 total = 0, cnt=0;
	for (uint8 i = 0; i < 20; i += 2)
	{
		for (uint8 j = 0; j < 8; j += 4)
		{
			if (image_array[84 + i][100 + j] > 55)//���˵��Ҷ�̫�͵����ص�
			{
				cnt++;
				total += image_array[84 + i][100 + j];
			}
		}
	}
	ips114_show_int(90, 70, total / 20, 3);
	//	ips114_draw_point(90,80,RGB565_BLUE);
	//	ips114_draw_point(91,80,RGB565_BLUE);
	//	ips114_draw_point(90,81,RGB565_BLUE);
	//	ips114_draw_point(91,81,RGB565_BLUE);
	if (cnt)return total / (cnt);
	else return 120; //����ѡ����Ϊ����ֱ�ӷ���120��Ϊ��ɫ
}



//-----------------------------------------------------------------------------------------------
// �������  �������(y��С)
// ����˵��  longest���������г���(yֵ)�����ݵĵ�ַ����Ӧǰ���ȫ�ֱ���uint8 longest
// ����˵��  index���������ж�Ӧ����(xֵ)�����ݵĵ�ַ����Ӧǰ���ȫ�ֱ���uint8 index
// ���ز���  void
// ʹ��ʾ��  find_longest(&longest, &index);
// ��ע��Ϣ  �������������find_middle()�����б�����
//-----------------------------------------------------------------------------------------------
uint8 y_threshold = 22;//12 ����ɨ�߶Աȶ���ֵ
void find_longest(uint8* longest, uint8* index)
{
	//----------------�����ұ߽����-----------------
	for (uint8 i = middle; i > 10; i--)
	{
		if (i - 5 < 0)break;
		if (100 * abs(mt9v03x_image[MT9V03X_H - 10][i] - mt9v03x_image[MT9V03X_H - 10][i - 5]) / (mt9v03x_image[MT9V03X_H - 10][i] + mt9v03x_image[MT9V03X_H - 10][i - 5] + 1) > 25)//��ĸ�Ӹ�1��ֹ��0
		{
			ips114_draw_circle(i, MT9V03X_H - 10, 4, RGB565_PURPLE);
			break;
		}
	}
	for (uint8 i = middle; i < MT9V03X_W; i++)
	{
		if (i + 5 > MT9V03X_W)break;
		if (100 * abs(mt9v03x_image[MT9V03X_H - 10][i] - mt9v03x_image[MT9V03X_H - 10][i + 5]) / (mt9v03x_image[MT9V03X_H - 10][i] + mt9v03x_image[MT9V03X_H - 10][i + 5] + 1) > 25)//��ĸ�Ӹ�1��ֹ��0
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
		for (int16 j = MT9V03X_H - 6; j >= 0; j -= 1)		//???????,Ҫ����10����Ե�Ҷ�ֵ�ܴ�?????????//���Ż�-=3��
		{
			a = j;
			b = a + 4;

			uint8 value_1 = 100 * abs(mt9v03x_image[a][i] - mt9v03x_image[b][i]) / (mt9v03x_image[a][i] + mt9v03x_image[b][i] + 1);//>>>>>>>��ĸ�Ӹ�1,��ֹ��0
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

				if (j < *longest) //���������
				{
					*longest = j; //j
					*index = i;
				}
				//if (j <= 20 && 100 * abs(mt9v03x_image[0][i + 14] - white_value) / (mt9v03x_image[0][i + 14] + white_value) < 12 && high_l == 0)
				//{
				//	high_l = *index;  //��ߴ�Ϊ�հף����¼����һ�п�ʼ��ߴ��հ�
				//	ips114_draw_circle(high_l, j, 3, RGB565_RED);
				//	break;
				//}
				//if (j <= 20 && 100 * abs(mt9v03x_image[0][i - 14] - white_value) / (mt9v03x_image[0][i - 14] + white_value) < 12 && high_l != 0 && high_r == 0)
				//{
				//	high_r = *index;
				//	ips114_draw_circle(high_r, j, 3, RGB565_YELLOW);
				//	break;
				//}
				break;//ÿ���ҵ���һ���ڵ��Ͳ��ټ����������ˣ�ֱ�ӽ�����һ��
			}

		}
	}
	//ips114_show_uint(50,50,high_l,3);
	//ips114_show_uint(80,50,high_r,3);

	if (high_l && high_r) *index = (high_l + high_r) / 2;	//����Ϊ�հף��򷵻����index
	if (highest_count != 0 && high_sum != 0 && abs(high_sum /highest_count - *index) < 40)
	{
		*longest = 0; //j
		*index = high_sum / highest_count;
	}

	//ips114_show_int(150,80, high_sum / (highest_count+1) - *index, 3);
	//ips114_show_int(150, 90, high_sum / (highest_count+1) , 3);
}

//-----------------------------------------------------------------------------------------------
// �������  ��������
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
uint8 x_threshold = 15;//15����ɨ�߶Աȶ���ֵ
#define SHORTEST (MT9V03X_H - 20)//��������е����ֵ������С�����ֵ��ֱ��return����Ϊ�ܳ�������
void find_middle()
{
	find_longest(&longest, &index);
	if(longest>SHORTEST)return;	//С�����ֵ��ֱ��return����Ϊ�ܳ�������
	ips114_draw_line(index, MT9V03X_H - 10, index, longest, RGB565_PURPLE);

	//����п�ʼѰ�����ұ߽�
	for (uint8 i = longest; i < MT9V03X_H - 5; i++)
	{
		//����߽�
		for (int16 j = index; j >= 0; j -= 1)
		{
			if(index<5)//����п����������
			{
				boder_L[i] = 0;
				ips114_draw_point(0, i, RGB565_YELLOW);
				break;
			}

			a = j;
			b = a - 5;
			uint8 value_1 = 100 * abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b] + 1);	//>>>>>>>��ĸ�Ӹ�1,��ֹ��0
			uint8 value_2 = 100 * abs(mt9v03x_image[i][b] - white_value) / (mt9v03x_image[i][b] + white_value + 1);
			if (b == 0) //��û���ҵ���߽�㣬����������Ϊ��߽��
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

		//���ұ߽�
		for (int16 j = index; j < MT9V03X_W; j += 1)
		{
			if (index > MT9V03X_W-6)//����п��������ұ�
			{
				boder_L[i] = 0;
				ips114_draw_point(0, i, RGB565_YELLOW);
				break;
			}
			a = j;
			b = a + 5;
			uint8 value_1 = 100 * abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b] + 1);//>>>>>>>��ĸ�Ӹ�1,��ֹ��0
			uint8 value_2 = 100 * abs(mt9v03x_image[i][b] - white_value) / (mt9v03x_image[i][b] + white_value + 1);
			if (b == MT9V03X_W-1) //��û���ҵ��ұ߽�㣬������ҵ���Ϊ�ұ߽��
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


void sideline_correct(uint8* side_point, int16* sideline_angle, int16* sideline_distance);

//-----------------------------------------------------------------------------------------------
// �������  ����б��
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
int16 slope()
{
	static int16 lastresult;
	if(longest>SHORTEST)return lastresult;	//С�����ֵ����Ϊ�ܳ������ˣ��ͷ����ϴ�б�ʣ�
	sideline_correct(boder_correct, &sideline_angle, &sideline_distance);
	int16 sum1 = 0, sum2 = 0, result;
	for (uint8 i = longest; i <= MT9V03X_H - 10; i++)
	{
		sum1 += (int16)(boder_M[i] - middle);//ԭ���Ǽ�ȥboder_M[MT9V03X_H - 10]
		sum2 += (int16)(MT9V03X_H - 10 - i);
	}
	result = 50 * sum1 / (sum2+1); //��ĸ��1��ֹ��0;
	ips114_show_int(50, 80, (const int32)result, 3);
	lastresult = result;
	return result;
}



//-----------------------------------------------------------------------------------------------
// �������  ���߽���
// ����˵��  
// ���ز���  side_point���ɼ�������ĵ�ַ����Ӧǰ���ȫ������uint8 boder_correct[60];��
// ʹ��ʾ��  
// ��ע��Ϣ  �˺������ú󼴿ɵõ�����������ͱ��߾���������my_motor.c�ļ��е���roundabout_move(&sideline_angle, &sideline_distance);�Ϳ�ʵ�ֻ���ʮ��·�κ����ƶ�����
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

	ips114_show_int(120, 20, *sideline_angle, 5);
	ips114_show_int(120, 40, *sideline_distance, 4);
}


//-----------------------------------------------------------------------------------------------
// �������  ����ʮ��ʶ��
// ����˵��  
// ���ز���  void
// ʹ��ʾ��  
// ��ע��Ϣ  
//-----------------------------------------------------------------------------------------------
void roundabout_cross() 
{
	uint16 jump_point[4][2] = { {0} };//��ű��������

	//������������е��x��ֵ
	for (uint8 i = MT9V03X_H - 6; i >= longest + 1; i--)
	{
		diff_boder_L[i-1] = abs(boder_L[i] - boder_L[i - 1]); //diff_boder_L��i-1��boder_L��i-1��Ӧ
		if (diff_boder_L[i-1] > 15)
		{
			if (boder_L[i] > boder_L[i - 1] && (jump_point[0][0] * jump_point[0][1]) == 0) //����ߴ��µ��ϵĵ�һ��ͻ���
			{ 
				ips114_draw_circle(boder_L[i], i, 4, RGB565_YELLOW); 
				jump_point[0][0] = boder_L[i];  jump_point[0][1] = i;
			}
			else { ips114_draw_circle(boder_L[i-1], i-1, 4, RGB565_YELLOW); }
		}
	}
	//���ұ��������е��x��ֵ
	for (uint8 i = MT9V03X_H - 6; i >= longest + 1; i--)
	{
		diff_boder_R[i-1] = abs(boder_R[i] - boder_R[i - 1]);
		if (diff_boder_R[i-1] > 15)
		{
			if(boder_R[i] < boder_R[i - 1] && (jump_point[1][0] * jump_point[1][1]) == 0 && (jump_point[0][0] * jump_point[0][1]) != 0)  //�ұ��ߴ��µ��ϵĵ�һ��ͻ���
			{
				ips114_draw_circle(boder_R[i], i, 4, RGB565_GREEN);
				jump_point[1][0] = boder_R[i];  jump_point[1][1] = i;
			}
			else { ips114_draw_circle(boder_R[i-1], i-1, 4, RGB565_GREEN); }
		}
	}
	//���ϱ��������е��y��ֵ
	for (uint8 i = 2; i < MT9V03X_W; i+=2)
	{
		diff_boder_U[i] = abs(boder_U[i] - boder_U[i - 2]);
		if (diff_boder_U[i] > 15 && i<90) // ����X���귶Χ�������ж����ұ���
		{
			//ips114_draw_point(30, 30, RGB565_CYAN);
			//ips114_draw_point(i-2, boder_U[i-2], 1, RGB565_CYAN);
			ips114_draw_circle(i - 2, boder_U[i - 2], 4, RGB565_RED);
			jump_point[2][0] = i - 2;  jump_point[2][1] = boder_U[i - 2];
		}
		if (diff_boder_U[i] > 15 && i > 90 && jump_point[2][0]!=0) // ����X���귶Χ�������ж����ұ���
		{
			jump_point[3][0] = i;  jump_point[3][1] = boder_U[i];
			//ips114_draw_point(30, 30, RGB565_CYAN);
			////ips114_draw_point(i-2, boder_U[i-2], 1, RGB565_CYAN);
			ips114_draw_circle(i, boder_U[i], 4, RGB565_RED);
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
		ips114_show_int(50, 60, x1, 2);
		ips114_show_int(50, 70, y1, 2);
		ips114_show_string(50, 90, "RA") ;
	}
	if (distance2 <= 40 && jump_point[1][0]*jump_point[3][0] != 0) {
		ips114_show_int(130, 60, x2, 2);
		ips114_show_int(130, 70, y2, 2);
		ips114_show_string(130, 90, "CR");
	}
}








//---------------------------����Ϊδʹ��-------------------------------
/*!
 *  @brief      ��򷨶�ֵ��0.8ms����
 *  @date:   2018-10
 *  @since      v1.2
 *  *image ��ͼ���ַ
 *  width:  ͼ���
 *  height��ͼ���
 *  @author     ZС��
 */

uint8 otsu(uint8* image, uint16 width, uint16 height)
{
#define GrayScale 256
	int pixelCount[GrayScale] = { 0 };//ÿ���Ҷ�ֵ��ռ���ظ���
	float pixelPro[GrayScale] = { 0 };//ÿ���Ҷ�ֵ��ռ�����ر���
	int i, j;
	int Sumpix = width * height;   //�����ص�
	uint8 threshold = 0;
	uint8* data = image;  //ָ���������ݵ�ָ��


	//ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
			//   pixelCount[(int)image[i][j]]++;    ������ָ�������
		}
	}
	float u = 0;
	for (i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / Sumpix;   //����ÿ������������ͼ���еı���
		u += i * pixelPro[i];  //��ƽ���Ҷ�
	}


	float maxVariance = 0.0;  //�����䷽��
	float w0 = 0, avgValue = 0;  //w0 ǰ������ ��avgValue ǰ��ƽ���Ҷ�
	for (int i = 0; i < 256; i++)     //ÿһ��ѭ������һ��������䷽����� (����for����Ϊ1��)
	{
		w0 += pixelPro[i];  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷ�������ռ����ͼ��ı�����ǰ������
		avgValue += i * pixelPro[i];

		float variance = pow((avgValue / w0 - u), 2) * w0 / (1 - w0);    //��䷽��
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = (uint8)i;
		}
	}


	return threshold;

}


//�ݶ�ͼ��
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



//�ҶȰ�����
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
				//�����
				if (100 * abs(image[i][middle - j] - image[i][middle - j - 5]) / (image[i][middle - j] + image[i][middle - j - 5]) > 20)
				{
					start_point_l[0] = middle + j; start_point_l[1] = i;
				}
				//�����
				if (100 * abs(image[i][middle + j] - image[i][middle + j + 5]) / (image[i][middle + j] + image[i][middle + j + 5]) > 20)
				{
					start_point_r[0] = middle - j; start_point_r[1] = i;
				}
			}
		}
	}
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>��͸�ӱ任>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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
 
 
//�������ͷ��ʼ���󣬵���һ��ImagePerspective_Init���˺�ֱ�ӵ���ImageUsed   ��Ϊ͸�ӽ��
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��͸�ӱ任<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

