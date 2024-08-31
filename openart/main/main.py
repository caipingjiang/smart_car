# Untitled - By: 86152 - Wed Jun 5 2024

import seekfree, pyb
import sensor, image, time, math
import os, tf,gc
from machine import UART

lcd = seekfree.LCD180(2)
lcd.full()

uart = UART(2, baudrate=115200)  # 初始化串��? 波特率设置为115200 TX是B12 RX是B13

sensor.reset()
sensor.set_pixformat(sensor.RGB565)  # 设置摄像头像素格��?
sensor.set_framesize(sensor.QVGA)   # 设置摄像头分辨率
sensor.set_brightness(700)          # 设置摄像头亮�� ?
sensor.skip_frames(time = 200)
clock = time.clock()


#设置模型路径
face_detect ='/sd/yolo3_iou_smartcar_final_with_post_processing1.tflite'
#载入模型
net = tf.load(face_detect)


net_path_a = "mobilenet_a.tflite" # 定义模型的路��?
labels = [line.rstrip() for line in open("/sd/labels.txt")]   # 加载标签
net2 = tf.load(net_path_a, load_to_fb=True)                                  # 加载模型

net_path_d = "mobilenet_d.tflite" # 定义模型的路��?
labels_d = [line.rstrip() for line in open("/sd/labels_d.txt")]   # 加载标签
net3 = tf.load(net_path_d, load_to_fb=True)                                  # 加载模型


label_map = {
    0: "object"
   }


find_card = 0
sorted_list= []
uart_data= '0'
brightness=700

card_class_record = [0,0,0,0,0]   # 前五次记录的卡片类别

def uart_classify(img):
    global find_card,sorted_list,uart_data
    if uart_data=='0':
        img0 = img.copy(x_size=240,y_size=240)
        for obj in tf.detect(net,img0):
            x1,y1,x2,y2,label,scores = obj
            if(scores>0.70):
                find_card += 1
                #print(obj)
                w = x2- x1
                h = y2 - y1
                x1 = int((x1)*img.width())
                y1 = int(y1*img.height())
                w = int(w*img.width())
                h = int(h*img.height())
                if x1<0:
                    x1=0
                if y1<0:
                    y1=0
                img.draw_rectangle((x1,y1,w,h),thickness=2)
                label_name = label_map.get(label, "未知类别")
                img1 = img.copy(roi = (x1,y1,w,h),copy_to_fb=False)
                for obj1 in tf.classify(net2, img1, min_scale=1.0, scale_mul=0.5, x_overlap=0.0, y_overlap=0.0):
                    sorted_list = sorted(zip(labels, obj1.output()), key = lambda x: x[1], reverse = True)
    elif uart_data=='1':
        for r in img.find_rects(threshold = 40000):             # 在图像中搜索矩形
            s = r.w()*r.h()
            #print("S:%d"%s)
            if(s > 20000 or s < 5000):
                continue

            find_card += 1
            img.draw_rectangle(r.rect(), color = (255, 0, 0))   # 绘制矩形外框，便于在IDE上查看识别到的矩形位置
            img1 = img.copy(1, 1, r.rect())                           # 拷贝矩形框内的图像
            for obj1 in tf.classify(net3, img1, min_scale=1.0, scale_mul=0.5, x_overlap=0.0, y_overlap=0.0):
                sorted_list = sorted(zip(labels_d, obj1.output()), key = lambda x: x[1], reverse = True)

# 前几次类别记录
def class_record(card_class):
    global card_class_record

    #将传入的最新卡片类别更新到前五次类别记录列表中
    for i in range(2):
        card_class_record[i] = card_class_record[i+1]

    card_class_record[2] = card_class

    # 判断前五次类别是否相同
    if all(card_class == each_class for each_class in card_class_record[:3]):
#        print('okokokok')
        return True
    else:
#        print('nononono')
        return False


while(True):
    while uart.any():
       uart_data = uart.read(1).decode() # 读取串口数据

    if uart_data =='a':
        brightness+=50
        uart_data='0'
    elif uart_data =='b':
        brightness-=50
        uart_data='0'
    sensor.set_brightness(brightness)          # 设置摄像头亮�� ?

    find_card = 0

    img = sensor.snapshot()
    uart_classify(img)
    lcd.show_image(img, 320, 240, zoom=2)
    # 更新记录列表并判断与前4次是否相等
    if sorted_list:
        if((find_card>0) and class_record(sorted_list[0][0])):
            uart.write("Y%s,1Z" %(sorted_list[0][0]))
            lcd.show_str(sorted_list[0][0],0, 44, lcd.RED, 1)
            #print("Y%s,1Z,%s" %(sorted_list[0][0],uart_data))
        else:
            uart.write("Y0,0Z")
            lcd.show_str(sorted_list[0][0],0, 44, lcd.RED, 1)
            #lcd.show_str("0",0, 44, lcd.RED, 1)
           # print("Y%s,0Z,%s" %(sorted_list[0][0],uart_data))
        #lcd.show_image(img, 320, 240, zoom=2)
        #lcd.show_str(sorted_list[0][0],0, 44, lcd.RED, 1)
    #sorted_list= []
    #sorted_list[0] = ("0", sorted_list[0][1])
    lcd.show_str(uart_data,0, 0, lcd.RED, 1)
    lcd.show_str(str(brightness),0, 60, lcd.RED, 1)
    gc.collect()



if __name__ == '__main__':
    main()
