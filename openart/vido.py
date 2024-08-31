# MJPEG Video Recording Example
#
# Note: You will need an SD card to run this demo.
#
# You can use your OpenMV Cam to record mjpeg files. You can either feed the
# recorder object JPEG frames or RGB565/Grayscale frames. Once you've finished
# recording a Mjpeg file you can use VLC to play it. If you are on Ubuntu then
# the built-in video player will work too.

import sensor, image, time, mjpeg, pyb
import seekfree

lcd = seekfree.LCD180(2)
lcd.full()

RED_LED_PIN = 1
BLUE_LED_PIN = 3

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.QVGA) # or sensor.QQVGA (or others)
sensor.skip_frames(time = 200) # Let new settings take affect.
sensor.set_brightness(1000)

clock = time.clock() # Tracks FPS.

pyb.LED(RED_LED_PIN).on()

pyb.LED(RED_LED_PIN).off()
pyb.LED(BLUE_LED_PIN).on()

m = mjpeg.Mjpeg("example.mjpeg")

print("You're on camera!")
for i in range(4000):
    clock.tick()
    img = sensor.snapshot()
    m.add_frame(img)
    lcd.show_image(img, 320, 240, zoom=2)
    print(clock.fps())

m.close(clock.fps())
pyb.LED(BLUE_LED_PIN).off()
print("Done! Reset the camera to see the saved recording.")


if __name__ == '__main__':
    main()
