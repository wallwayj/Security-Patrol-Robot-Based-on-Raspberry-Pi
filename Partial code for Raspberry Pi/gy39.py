#!/usr/bin/env python3
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
    
    lux = (((lux_high << 24) | (lux_low<<16)|b_lux_high<<8)|b_lux_low )/100
    temp = ((temp_high << 8) | temp_low) / 100.0   
    pressure = ((pressure_high << 24) | (pressure_low << 16)) / 100  
    humi = ((humi_high << 8) | humi_low) / 100.0  
    alt = ((alt_high << 8) | alt_low)  
    return lux, temp, pressure, humi, alt
 
while  True:
	lux, temp, pressure, humi, alt = read_gy39_data()

	print("lux  {}       temp {}     pressure {} Pa   humi {}%       alt   {} m".format(lux, temp, pressure, humi, alt))

 




