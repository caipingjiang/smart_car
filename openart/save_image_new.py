## Untitled - By: 86152 - Sat May 11 2024
#使用目标检测框出图片并保存
import pyb,seekfree
import struct
from pyb import LED
import sensor, image, time, math, tf
import os,gc

lcd = seekfree.LCD180(2)
lcd.full()

sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # 设置摄像头像素格��?
sensor.set_framesize(sensor.QVGA)   # 设置摄像头分辨率
sensor.set_brightness(1000)          # 设置摄像头亮��?
sensor.skip_frames(time = 200)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False,(0,0,0))
clock = time.clock()
face_detect ='/sd/yolo3_iou_smartcar_final_with_post_processing.tflite'
net = tf.load(face_detect)
label_map = {
    0: "object"
  }

def snapshot(count):
    img = sensor.snapshot()
    for obj in tf.detect(net,img):
        x1,y1,x2,y2,label,scores = obj
        if(scores>0.60):
            print(obj)
            w = x2- x1
            h = y2 - y1
            x1 = int((x1-0.1)*img.width())
            y1 = int(y1*img.height())
            w = int(w*img.width())
            h = int(h*img.height())
            if x1<0:
                x1=0
            if y1<0:
                y1=0
            img_cropped = img.copy(roi = (x1,y1,w,h),copy_to_fb=False)
            lcd.show_image(img, 320, 240, zoom=2)
            img_cropped.save("/sd/dataset/F/%d.jpg" % count)
            img.draw_rectangle((x1,y1,w,h),thickness=2)


count = 58

while(True):
    img = sensor.snapshot()
    snapshot(count)
    count += 1
    time.sleep(1)
    print(count)


if __name__ == '__main__':
    main()
