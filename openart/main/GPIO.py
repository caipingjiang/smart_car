from machine import Pin # 从pyb导入Pin
import time

#初始化引脚
#Pin.OUT为输出， Pin.IN为输入
pin0=Pin("B0", Pin.OUT)
pin1=Pin("B1", Pin.OUT)
pin2=Pin("B2", Pin.OUT)
pin3=Pin("B3", Pin.OUT)

pin4=Pin("B12", Pin.OUT)
pin5=Pin("B13", Pin.OUT)
pin6=Pin("B16", Pin.OUT)

pin7=Pin("C6", Pin.OUT)
pin8=Pin("C7", Pin.OUT)
pin9=Pin("C8", Pin.OUT)
pin10=Pin("C9", Pin.OUT)


while(True):
    #pin0.value()如果没有参数会返回引脚电平，有参数1输出高电平或0输出低电平
    pin0.value(not pin0.value())
    pin1.value(not pin1.value())
    pin2.value(not pin2.value())
    pin3.value(not pin3.value())
    pin4.value(not pin4.value())
    pin5.value(not pin5.value())
    pin6.value(not pin6.value())
    pin7.value(not pin7.value())
    pin8.value(not pin8.value())
    pin9.value(not pin9.value())
    pin10.value(not pin10.value())
    #延时100ms
    time.sleep_ms(100)
