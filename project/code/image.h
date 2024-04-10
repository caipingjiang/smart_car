#ifndef _IMAGE_GB2_H
#define _IMAGE_GB2_H

// 定义图像参数
#define image_h 120                         // 图像高度
#define image_w 188                         // 图像宽度

#define white_pixel 255
#define black_pixel 0

#define bin_jump_num 1                      // 跳过的像素数
#define border_max image_w - 2              // 最大边界
#define border_min 1                        // 最小边界
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];   // 图像数组

extern void image_process(void);            // 在函数中直接处理图像，或在主函数中调用该函数

#endif /* _IMAGE_GB2_H */

