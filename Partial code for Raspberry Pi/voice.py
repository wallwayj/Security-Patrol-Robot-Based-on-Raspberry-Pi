import pygame
 
pygame.init()
 
pygame.mixer.init(devicename='usb')
 

def voice(who):	
	if who==1:
		sound = pygame.mixer.Sound('./Stranger.mp3')
	elif who==2:
		sound = pygame.mixer.Sound('/home/pi/temp/myjob/fire.mp3')		
	elif who==3:
		sound = pygame.mixer.Sound('/home/pi/temp/myjob/air.mp3')				
	elif who==4:
		sound = pygame.mixer.Sound('/home/pi/temp/myjob/way0.mp3')				
	sound.play()
	while pygame.mixer.get_busy():
		pygame.time.delay(100)
	print("///////////////////////////////////voice voice voice///////////////////////////////")
'''
voice(1)
voice(2)
voice(3)
voice(4)
'''
