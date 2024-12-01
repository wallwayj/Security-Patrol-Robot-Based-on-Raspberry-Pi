import time
import board
import busio
import adafruit_ccs811
import adafruit_tca9548a
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import Adafruit_PCA9685

#import onenet
import send_email
import voice
import uart
 
i2c_bus = busio.I2C(board.SCL, board.SDA)
tca = adafruit_tca9548a.TCA9548A(i2c_bus, address=0x70)

ccs811_channel = 0 
ccs811_i2c = tca[ccs811_channel]
ccs811 = adafruit_ccs811.CCS811(ccs811_i2c)

OLED_WIDTH = 128
OLED_HEIGHT = 32
oled_channel = 7
oled_i2c = tca[oled_channel]
oled = adafruit_ssd1306.SSD1306_I2C(OLED_WIDTH, OLED_HEIGHT, oled_i2c)
oled.fill(0)
oled.fill(0)
oled.show()

oled2_channel = 6
oled2_i2c = tca[oled2_channel]
oled2 = adafruit_ssd1306.SSD1306_I2C(OLED_WIDTH, OLED_HEIGHT, oled2_i2c)
 
oled2.fill(0)
oled2.fill(0)
oled2.show()


 

image = Image.new("1", (OLED_WIDTH, OLED_HEIGHT))
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()
 
image2 = Image.new("1", (OLED_WIDTH, OLED_HEIGHT))
draw2 = ImageDraw.Draw(image)
font2 = ImageFont.load_default()
 
import smbus
import adafruit_veml7700
GY39_ADDR = 0x5B
bus = smbus.SMBus(3)   

def read_gy39_data():
    lux_high = bus.read_byte_data(GY39_ADDR, 0x00)
    lux_low = bus.read_byte_data(GY39_ADDR, 0x01)
    b_lux_high = bus.read_byte_data(GY39_ADDR, 0x02)
    b_lux_low = bus.read_byte_data(GY39_ADDR, 0x03)
    temp_high = bus.read_byte_data(GY39_ADDR, 0x04)
    temp_low = bus.read_byte_data(GY39_ADDR, 0x05)
    pressure_high = bus.read_byte_data(GY39_ADDR, 0x06)
    pressure_low = bus.read_byte_data(GY39_ADDR, 0x07)
    humi_high = bus.read_byte_data(GY39_ADDR, 0x0a)
    humi_low = bus.read_byte_data(GY39_ADDR, 0x0b)
    alt_high = bus.read_byte_data(GY39_ADDR, 0x0c)
    alt_low = bus.read_byte_data(GY39_ADDR, 0x0d) 
    
    
    alt = ((alt_high << 8) | alt_low)      
    lux = (((lux_high << 24) | (lux_low<<16)|b_lux_high<<8)|b_lux_low )/100
    temp = ((temp_high << 8) | temp_low) / 100.0   
    pressure = ((pressure_high << 24) | (pressure_low << 16)) / 100  
    humi = ((humi_high << 8) | humi_low) / 100.0  
 
    return lux, temp, pressure, humi,alt
 
 
''' 
pwm_channel = 2
pwm_i2c = tca[pwm_channel]
pwm = PCA9685(pwm_i2c)
pwm.frequency = 60
def set_pwmss(chann,duty):
    dutyss=65535 /4095*duty
    pwm.channels[chann].duty_cycle =int(dutyss )
set_pwmss(1,650 - 230)
set_pwmss(2,650 - 123)
'''
import time
import pygame
from adafruit_pca9685 import PCA9685
import board
import busio
import smbus
from adafruit_pca9685 import PCA9685
pwm = Adafruit_PCA9685.PCA9685(busnum=4)
pwm.set_pwm_freq(60)
 

def set_pwmss(chann,duty):
    dutyss=4095 /4095*duty
    pwm.set_pwm(chann, 0,int(dutyss))
 
 # Initialize pygame and create a display window
pygame.init()
screen = pygame.display.set_mode((400, 300))  # Set up a window for pygame to capture events



try:
    x, y = 480, 480 

# Set initial values for channels

    running = 0    
    if running!=0:
        set_pwmss(11, x)
        set_pwmss(12, y)
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Get the state of all keys
        keys = pygame.key.get_pressed()

        # Check each key and update x or y accordingly
        if keys[pygame.K_q]:
            x += 1
            set_pwmss(11, x)
            print(f"x increased to {x}, y = {y}")
        if keys[pygame.K_w]:
            x -= 1
            set_pwmss(11, x)
            print(f"x decreased to {x}, y = {y}")
        if keys[pygame.K_a]:
            y += 1
            set_pwmss(12, y)
            print(f"x = {x}, y increased to {y}")
        if keys[pygame.K_s]:
            y -= 1
            set_pwmss(12, y)
            print(f"x = {x}, y decreased to {y}")

        # Delay to control the speed of continuous input
        time.sleep(0.05)  # Adjust the delay for faster or slower response


except KeyboardInterrupt:
    print("Program terminated")
finally:
    pygame.quit()
    
    
  
while not ccs811.data_ready:
    pass

print("CCS811 ")
co2 = ccs811.eco2
tvoc = ccs811.tvoc   
temper = 1
humi = 2
atmos = 3
last_onenet_times = time.time()
nnn=0
peo=0
tvoc=0
def oled_show():
    global last_onenet_times
    global nnn,peo,tvoc
    lux, temper, atmos, humi,alt= read_gy39_data()
    co2 = ccs811.eco2
    tvoc = ccs811.tvoc   
    fire=0
    '''   
    draw.rectangle((0, 0, OLED_WIDTH, OLED_HEIGHT), outline=0, fill=0) 
    draw.text((0, 0), "CO2: {} ppm".format(co2), font=font, fill=255)
    draw.text((0, 16), "TVOC: {} ppb".format(tvoc), font=font, fill=255)
    draw.text((0, 32), "lux: {} C".format(lux), font=font, fill=255)
    draw.text((0, 48), "fire: {} ^".format(fire), font=font, fill=255)
    oled.image(image)
    oled.show()
    
    draw2.rectangle((0, 0, OLED_WIDTH, OLED_HEIGHT), outline=0, fill=0) 
    draw2.text((0, 0), "temper: {} C".format(temper), font=font, fill=255)
    draw2.text((0, 16), "humi: {} %".format(humi), font=font, fill=255)
    draw2.text((0, 32), "atmos: {} pa".format(atmos), font=font, fill=255)
    draw2.text((0, 48), "alt: {} m".format(alt), font=font, fill=255)
    oled2.image(image)
    oled2.show()
    '''
    draw.rectangle((0, 0, OLED_WIDTH, OLED_HEIGHT), outline=0, fill=0) 
    draw.text((0, 0), "CO2: {} ppm".format(co2), font=font, fill=255)
    draw.text((0, 10), "TVOC: {} ppb".format(tvoc), font=font, fill=255)
    draw.text((0, 20), "lux: {} C".format(lux), font=font, fill=255)
    draw.text((76, 0), "fire: {} ^".format(fire), font=font, fill=255)
    draw.text((76, 20), "alt: {} m".format(alt), font=font, fill=255)
    oled.image(image)
    oled.show()
    
    draw2.rectangle((0, 0, OLED_WIDTH, OLED_HEIGHT), outline=0, fill=0) 
    draw2.text((0, 0), "temper: {} C".format(temper), font=font, fill=255)
    draw2.text((0, 10), "humi: {} %".format(humi), font=font, fill=255)
    draw2.text((0, 20), "atmos: {} pa".format(atmos), font=font, fill=255)
    oled2.image(image)
    oled2.show() 

 
        
         
    '''
    if time.time() - last_onenet_times > 5:
        nnn+=1
        if nnn==1:
            onenet.send_data_to_onenet("co2",co2)
        elif nnn==2:
            onenet.send_data_to_onenet("tvoc",tvoc)
        elif nnn==3:
            onenet.send_data_to_onenet("temp",temper)
        elif nnn==4:
            onenet.send_data_to_onenet("humi",humi)
        elif nnn==5:
            onenet.send_data_to_onenet("atmos",atmos)
        elif nnn==6:
            onenet.send_data_to_onenet("alt",alt)
        elif nnn==7:
            onenet.send_data_to_onenet("lux",lux)
            nnn=0
    '''
    if time.time() - last_onenet_times > 2:
        uart.send_data_to_serial(co2, tvoc, lux, fire, alt, temper, humi, atmos,peo)
        last_onenet_times = time.time()          
    print("Environment Environment Environment Environment Environment")  
          
        
last_email_tvoc=0
def tvoc_alarm():
    global last_email_tvoc,tvoc
    if tvoc>500 and time.time()-last_email_tvoc>5*60:         
        voice.voice(3)
        send_email.send_alarm(2)
        last_email_tvoc=time.time()	
        
        
'''        

try:
    while True: 
        lux, temp, pressure, humi ,alt= read_gy39_data()
        oled_show()
        tvoc_alarm()
        print("CO2:", co2, "ppm")
        print("TVOC:", tvoc, "ppb")			
        time.sleep(1)

except KeyboardInterrupt:

    pass

'''
