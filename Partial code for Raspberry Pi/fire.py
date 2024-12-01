from gpiozero import Button
import time
from gpiozero import LED
from time import sleep
#fire_ward = Button(24)
fire_zuo = Button(23)
fire_you = Button(24)
led_Spray = LED(0)
def fire_detection():
	f1=0
	f2=0
	f3=0
	#if fire_ward.is_pressed:
		#return 1
	if fire_zuo.is_pressed:
		return 2
	if fire_you.is_pressed:
		return 3
	return 0
      
		
	 
def Spray_on():
	led_Spray.on()
	time.sleep(0.100)
	led_Spray.off()
def Spray_off():
	led_Spray.on()
	time.sleep(0.100)
	led_Spray.off()
	time.sleep(0.1)
	led_Spray.on()
	time.sleep(0.1)
	led_Spray.off()
	
 
'''
try:
	while True: 
		f=fire_detection()
		print("f=:", f)
		time.sleep(1.5) 

	
		Spray_on()
		time.sleep(3)
		led_Spray.off()

		
except KeyboardInterrupt:

    pass
''' 
 
