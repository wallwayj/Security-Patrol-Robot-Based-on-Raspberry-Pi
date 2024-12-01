import serial
import time

ser = serial.Serial("/dev/ttyAMA0", 115200)




def send_data_to_serial(co2, tvoc, lux, fire, alt, temper, humi, atmos,peo):
     
   # message1 = "CO2:{}TVOC:{}lux:{}fire:{}alt:{}".format(co2, tvoc, lux, fire, alt)
    #message2 = "temper: {} C\nhumi: {} %\natmos: {} pa\n".format(temper, humi, atmos)
    
    #message="st{}{}{}{}{}{}{}{}\r\n".format(co2, tvoc, lux, fire, alt,temper, humi, atmos,peo)
    message = "CO2:{};TVOC:{};LUX:{};FIRE:{};ALT:{};TEMPER:{};HUMI:{};ATMOS:{};peo:{};\r\n".format(co2, tvoc, lux, fire, alt, temper, humi, atmos,peo)
    ser.write(message.encode())
    
    time.sleep(0.2)   
    '''
    ser.write(message2.encode())
    time.sleep(0.1)  
    '''
''' 
def main():
    while True:
        #ser.write("hello".encode())
        co2 = 444
        tvoc = 1
        lux = 384.8
        fire = 0
        alt = 1870
        temper = 24.18
        humi = 43.82
        atmos = 82575.36
        print("LL")
        send_data_to_serial(co2, tvoc, lux, fire, alt, temper, humi, atmos,0)
        count = ser.inWaiting()
        if count != 0:
            recv = ser.read(count)
            ser.write(recv)
        time.sleep(0.1)
if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        if ser != None:
            ser.close()
'''
