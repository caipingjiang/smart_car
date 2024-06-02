
#ifndef _MY_IMAGE_H_
#define _MY_IMAGE_H_

#define		middle	MT9V03X_W/2
#define     distance(x1,y1,x2,y2)    ( sqrt( pow((x1)-(x2), 2) + pow((y1)-(y2), 2) ) )   //计算两点之间的距离

void pit_handler_2();
void my_image_init();
uint8 find_white_point(uint8 image_array[][188]);
void find_longest(uint8* longest, uint8* index);
void find_middle();
int16 slope();
void sideline_correct(uint8* side_point, int16* sideline_err, int16* sideline_distance);
void find_start_point(uint8 image[][188]);
void roundabout_cross(); //环岛
uint8 find_start_finish_line();
void cross();
void roundabout();
uint8 start_finial_line_car_find();
void Image_change(uint8 image[][MT9V03X_W], uint16 width, uint16 height);
uint8 otsu(uint8* image, uint16 width, uint16 height);

extern uint8 cross_flag, roundabout_flag;
extern int8  cross_dir, roundabout_dir;
extern uint8 boder_correct[60];
extern uint8 longest, index;
extern uint8 lose_point_num_L, lose_point_num_R;
extern uint8 Image_Mode;
extern uint32 track_wide;
extern bool roundabout_card_finished;
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
