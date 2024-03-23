#include "zf_common_headfile.h"
#include "my_image.h"
#include <math.h>
void my_image_init()
{
	mt9v03x_init();
//    while(1)
//   {
//       if(mt9v03x_init())
//           ips114_show_string(0, 16, "mt9v03x reinit.");
//       else
//           break;
//       system_delay_ms(500);                                                   // ����ʱ�������Ʊ�ʾ�쳣
//   }
   //ips114_show_string(0, 16, "init success.");
}



//�߽����������������
uint8 boder_L[MT9V03X_H-5];
uint8 boder_R[MT9V03X_H-5];
uint8 boder_M[MT9V03X_H-5];
uint8 red_point[25];
int8 diff_y[25];
uint8 longest, index;			//����ж�Ӧ��������ͺ�����
int16 a, b;						//��Ⱥ��е�a,b


uint8 start_finish_line_find()
{
	uint16 total = 0;
	ips114_draw_line(40,105,130,105,RGB565_GREEN);
	for(uint8 i=40; i<130; i++)
	{
		total += mt9v03x_image[105][i];
	}
	total/=90;
	//ips114_show_uint(20,70,total,3);
	if(total<125&&func_abs(slope())<10)return 1;
	else return 0;
}
//�����ɫ�ο���ֵ
uint8 find_white_point(uint8 image_array[][188])
{
	uint16 total = 0;
	for(uint8 i=0; i<18; i+=2)			
	{
		for(uint8 j = 0; j<10; j+=2)
		{
			total+=image_array[90+i][90+j];
		}
	}
//	ips114_draw_point(90,80,RGB565_BLUE);
//	ips114_draw_point(91,80,RGB565_BLUE);
//	ips114_draw_point(90,81,RGB565_BLUE);
//	ips114_draw_point(91,81,RGB565_BLUE);
	return total/45;
}


uint8 y_threshold=12;
void find_longest(uint8* longest, uint8* index)
{
	uint8 high_l, high_r;
	*longest = MT9V03X_H-10;
	uint8 white_value = find_white_point(mt9v03x_image);
	ips114_show_uint(90,90,white_value,3);
	for(uint8 i=10; i<MT9V03X_W; i+=2)		//+=5
	{
		for(int16 j=MT9V03X_H-10; j>0; j-=2)		//???????,Ҫ����10����Ե�Ҷ�ֵ�ܴ�?????????//���Ż�-=3��
		{
			a = j;
			b = a - 5;
			if(b<0)break;
			if((i<20||i>170) && j<50)break;		//�ų�����������û�б��߽�ռ�ݵĲ���
			if(mt9v03x_image[a][i]<3||mt9v03x_image[b][i]<12)break;
			//if(100*abs(mt9v03x_image[a][i] - mt9v03x_image[b][i]) / (mt9v03x_image[a][i]+mt9v03x_image[b][i])>17)	//��Ⱥ��жϺڵ�  ������15������
			uint8 value_1 = 100*abs(mt9v03x_image[a][i] - mt9v03x_image[b][i]) / (mt9v03x_image[a][i]+mt9v03x_image[b][i]);
			uint8 value_2 = 100*abs(mt9v03x_image[a][i] - white_value) / (mt9v03x_image[a][i]+white_value);
			if( (value_1*0 + value_2*1) > y_threshold)//25
			{
				ips114_draw_point(i,j,RGB565_RED);
				
				red_point[(i-10)/5]=j;
				if(i>10)
				{
					if(	(red_point[(i-10)/5] - red_point[(i-10)/5-1]) <-25)
					{
						//ips114_draw_square(i-5,red_point[(i-10)/5-1], 4,RGB565_YELLOW);
						
					}
				}
				
				if(j < *longest) 
				{
					*longest = j;
					*index = i;
				}
				if(j<=10 && 100*abs(mt9v03x_image[0][i+4]-white_value) / (mt9v03x_image[0][i+4]+white_value)<12 && high_l == 0) 
				{
					high_l = *index;  //��ߴ�Ϊ�հף����¼����һ�п�ʼ��ߴ��հ�
					break;
				}
				if(j<=10 && 100*abs(mt9v03x_image[0][i-4]-white_value) / (mt9v03x_image[0][i-4]+white_value)<12 && high_l != 0 && high_r == 0) 
				{
					high_r = *index;
					break; 
				}
				break;//ÿ���ҵ���һ���ڵ��Ͳ��ټ����������ˣ�ֱ�ӽ�����һ��
			}
			
		}
	}
	//ips114_show_uint(50,50,high_l,3);
	//ips114_show_uint(80,50,high_r,3);
	
	if(high_l && high_r) *index = (high_l + high_r)/2;	//����Ϊ�հף��򷵻����index
}

uint8 x_threshold = 20;
void find_middle()
{

	find_longest(&longest, &index);
	ips114_draw_line(index, MT9V03X_H-10, index, longest, RGB565_PURPLE);
	
	//����п�ʼѰ�����ұ߽�
	for(uint8 i=longest;i<=MT9V03X_H-10;i++)
	{
		//����߽�
		for(int16 j=index; j>0; j-=2)
		{	
			a = j;
			b = a - 5;
			if(b<0) //��û���ҵ���߽�㣬����������Ϊ��߽��
			{
				boder_L[i]=0;
				ips114_draw_point(0,i,RGB565_YELLOW);
				break;
			}
			if(100*abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b])>x_threshold)
			{
				boder_L[i]=b;
				ips114_draw_point(b,i,RGB565_YELLOW);
				break;
			}
		}
		
		//���ұ߽�
		for(int16 j=index; j<MT9V03X_W; j+=2)
		{	
			a = j;
			b = a + 5;
			if(b>MT9V03X_W) //��û���ҵ��ұ߽�㣬������ҵ���Ϊ�ұ߽��
			{
				boder_R[i]=MT9V03X_W;
				ips114_draw_point(MT9V03X_W,i,RGB565_GREEN);
				break;
			}
			if(100*abs(mt9v03x_image[i][a] - mt9v03x_image[i][b]) / (mt9v03x_image[i][a] + mt9v03x_image[i][b])>x_threshold)
			{
				boder_R[i]=b;									
				ips114_draw_point(b,i,RGB565_GREEN);
				break;
			}
		}
		
		boder_M[i] = (boder_L[i] + boder_R[i]) / 2;
		ips114_draw_point(boder_M[i],i,RGB565_BLUE);
	}
}

int16 slope()
{
	int16 sum1 = 0, sum2 = 0, result;
	for(uint8 i=longest;i<=MT9V03X_H-10;i++)
	{
		sum1 += (int16)(boder_M[i]-boder_M[MT9V03X_H-10]);
		sum2 += (int16)(MT9V03X_H-10-i);
	}
	result = 50*sum1/sum2;
	ips114_show_int(50,80,(const int32)result,3);
	
	return result;
}

/*!
 *  @brief      ��򷨶�ֵ��0.8ms����
 *  @date:   2018-10
 *  @since      v1.2
 *  *image ��ͼ���ַ
 *  width:  ͼ���
 *  height��ͼ���
 *  @author     ZС��
 */


uint8 otsu(uint8 *image, uint16 width, uint16 height)
{
    #define GrayScale 256
    int pixelCount[GrayScale] = {0};//ÿ���Ҷ�ֵ��ռ���ظ���
    float pixelPro[GrayScale] = {0};//ÿ���Ҷ�ֵ��ռ�����ر���
    int i,j;
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


    float maxVariance=0.0;  //�����䷽��
    float w0 = 0, avgValue  = 0;  //w0 ǰ������ ��avgValue ǰ��ƽ���Ҷ�
    for(int i = 0; i < 256; i++)     //ÿһ��ѭ������һ��������䷽����� (����for����Ϊ1��)
    {
        w0 += pixelPro[i];  //���赱ǰ�Ҷ�iΪ��ֵ, 0~i �Ҷ�������ռ����ͼ��ı�����ǰ������
        avgValue  += i * pixelPro[i];

        float variance = pow((avgValue/w0 - u), 2) * w0 /(1 - w0);    //��䷽��
        if(variance > maxVariance)
        {
            maxVariance = variance;
            threshold = (uint8)i;
        }
    }


    return threshold;

}    

//�ݶ�ͼ��
uint8 t_b=30, k=1;
uint8 x_operator[8][2] = {{0,1}, {-1,1}, {-1,0}, {0,-1}, {1,-1}, {1,0}, {1,1}};
uint8 image_changed[MT9V03X_H-1][MT9V03X_W-1];
void Image_change(uint8* image[0], uint16 width, uint16 height)
{
	for(uint8 i = 1; i <=MT9V03X_W-2; i++)
	{
		for(uint8 j = 1; j<=MT9V03X_H-2; j++)
		{
			image_changed[j-1][i-1] = k*(image[j][i+1] - image[j][i-1] + image[j+1][i] - image[j-1][i] + t_b);
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


