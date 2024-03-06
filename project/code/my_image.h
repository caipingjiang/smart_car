
#ifndef _MY_IMAGE_H_
#define _MY_IMAGE_H_


void my_image_init();
uint8 start_finish_line_find();
void find_longest(uint8* longest, uint8* index);
void find_middle();
int16 slope();
uint8 otsu(uint8 *image, uint16 width, uint16 height);


//#define RESULT_ROW 100//结果图行列
//#define RESULT_COL 114
//#define         USED_ROW                120  //用于透视图的行列
//#define         USED_COL                188
//#define PER_IMG     mt9v03x_image//SimBinImage:用于透视变换的图像
//#define ImageUsed   *PerImg_ip//*PerImg_ip定义使用的图像，ImageUsed为用于巡线和识别的图像
//typedef unsigned char       uint8_t;                                              // 无符号  8 bits
//uint8_t *PerImg_ip[RESULT_ROW][RESULT_COL];
//void ImagePerspective_Init(void);

#endif
