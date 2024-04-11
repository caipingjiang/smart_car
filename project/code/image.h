#ifndef _IMAGE_GB2_H
#define _IMAGE_GB2_H

// ����ͼ�����
#define image_h 120                         // ͼ��߶�
#define image_w 188                         // ͼ����

#define white_pixel 255
#define black_pixel 0

#define bin_jump_num 1                      // ������������
#define border_max image_w - 2              // ���߽�
#define border_min 1                        // ��С�߽�
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];   // ͼ������

extern void image_process(void);            // �ں�����ֱ�Ӵ���ͼ�񣬻����������е��øú���

#endif /* _IMAGE_GB2_H */

