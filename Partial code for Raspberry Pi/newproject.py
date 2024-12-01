from gpiozero import Button
import time
from time import sleep
import threading 
import mediapipe as mp
import cv2 as cv
import datetime
import os
import send_email
import onenet
import iicself
import voice
import fire

import numpy as np
 
recognizer = cv.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascade_frontalface_default.xml"
faceCascade = cv.CascadeClassifier(cascadePath);
font = cv.FONT_HERSHEY_SIMPLEX
id = 0
names = ['None', 'ID=1', 'ID=2', 'ID=3', 'Z', 'W'] 
capture = cv.VideoCapture(-1)
capture.set(3, 640) # set video widht
capture.set(4, 480) # set video height
minW = 0.1*capture.get(3)
minH = 0.1*capture.get(4)
iiclock = threading.Lock()
onenetlock = threading.Lock()

Kp =0.49
X_P = 395/Kp
Y_P = 480/Kp
X_max=650/Kp  
X_min=140/Kp  
Y_max=650/Kp 
Y_min=430/Kp 
lastError_x = 0
lastError_y = 0
stranger = 0   
all_fire = 0
st=0 
def iic_ernv_oled():
    sp_flag=1
    global all_fire
    while True:
        with iiclock:
            iicself.oled_show()
            onenet.send_data_to_onenet("fire", all_fire)     
            onenet.fetch_data_from_onenet()
            if(onenet.feeding==0 and sp_flag==0):
                fire.Spray_off()
                sp_flag=1
            elif sp_flag==1 and onenet.feeding!=0:
                sp_flag=0
                fire.Spray_on()
        time.sleep(0.8)
def face_detection_worker(frame, detector):
    return detector.find_faces(frame)

class FaceDetector:
    def __init__(self, min_detection_confidence=0.5):
        self.mpFaceDetection = mp.solutions.face_detection
        self.mpDraw = mp.solutions.drawing_utils
        self.face_detection = self.mpFaceDetection.FaceDetection(min_detection_confidence=min_detection_confidence)
        self.last_save_time = datetime.datetime.now() - datetime.timedelta(minutes=5)
        self.last_detection_time = None
        self.detection_start_time = None

    def find_faces(self, frame):
       
        global peo,st
                
        if st==1:
            self.save_frame(frame,1)
            st=2
        
        bboxs = [] 
     
        current_time = datetime.datetime.now()
        gray = cv.cvtColor(frame,cv.COLOR_BGR2GRAY)
        faces = faceCascade.detectMultiScale( 
            gray,
            scaleFactor = 1.2,
            minNeighbors = 5,
            minSize = (int(minW), int(minH)),
           )
        for(x,y,w,h) in faces:
            bbox = x, y, w, h
            bboxs.append([0, bbox, 0])
            frame = self.fancy_draw(frame, bbox)
            #cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 2)
            id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
            if (confidence < 70):
                id = names[id]
                confidence = "  {0}%".format(round(100 - confidence))
                iicself.peo=0
            
            else:
                if self.detection_start_time is None:
                    self.detection_start_time = current_time
                if (current_time - self.last_save_time).total_seconds() > 5 * 60 and (current_time - self.detection_start_time).total_seconds() > 1.5:
                    self.detection_start_time = None 
                    self.last_save_time = current_time
                    threading.Thread(target=self.handle_detection, args=(frame,)).start()
                id = "unknown"
                confidence = "  {0}%".format(round(100 - confidence))
                iicself.peo=1
            
            cv.putText(frame, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
            cv.putText(frame, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)   
          
        return frame, bboxs           
        
    def handle_detection(self, frame):
        self.save_frame(frame,0)
        voice.voice(1)
        send_email.send_alarm(1)
        
    def fancy_draw(self, frame, bbox, l=30, t=10):
        global X_P, Y_P, lastError_x, lastError_y
        x, y, w, h = bbox
        x1, y1 = x + w, y + h
        cv.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 255), 1)
        cx, cy = x + w // 2, y + h // 2
        thisError_x = cx - 320
        thisError_y = cy - 240
        print(f"x={cx},ex={thisError_x},x={cy},ex={thisError_y}\n")
        pwm_x = thisError_x * 5 + 1 * (thisError_x - lastError_x)
        pwm_y = thisError_y * 5 + 1 * (thisError_y - lastError_y)
        lastError_x = thisError_x
        lastError_y = thisError_y
        XP = pwm_x / 100
        YP = pwm_y / 100
        X_P = X_P + int(XP)
        Y_P = Y_P + int(YP)
        max_movement = 10 
        global X_max,X_min,Y_max,Y_min
        if X_P > X_max:
            X_P = X_max
        if X_P < X_min:
            X_P = X_min
        if Y_P > Y_max:
            Y_P = Y_max
        if Y_P < Y_min:
            Y_P = Y_min
         
        return frame
    def save_frame(self, frame,w):
        save_dir = "./"
        if not os.path.exists(save_dir):
            os.makedirs(save_dir)
        if w==0:
            filename = os.path.join(save_dir, "5.jpg")
        else :
            filename = os.path.join(save_dir, "4.jpg")
        cv.imwrite(filename, frame)
        print(f"Saved {filename}")


def environment_alarm():
    global all_fire,st
    while True:
        
        print("Alarm Alarm Alarm Alarm Alarm")
        all_fire = fire.fire_detection()
        if   st==2:  
            voice.voice(2)
            send_email.send_alarm(0)
            st=3
        iicself.tvoc_alarm()
        time.sleep(1)
        
'''
def onenet_worker():
    while True:
        onenet.fetch_data_from_onenet()
        print("Onenet Onenet Onenet Onenet Onenet Onenet")        
        time.sleep(1.33)
'''
def servo_control():
    global X_P, Y_P,all_fire,st,Kp
    
    while True:
        '''
        if all_fire==2:
            
            iicself.set_pwmss(11,480)
            iicself.set_pwmss(12,200)
            time.sleep(0.8)
            if st==0:
                st=1
            time.sleep(1.2)
            
        elif all_fire==3:
            iicself.set_pwmss(11,100)
            iicself.set_pwmss(12,200)
            time.sleep(0.8)
            if st==0:
                st=1
            time.sleep(1.2)
          
                     
        else:
        '''

         #iicself.set_pwmss(11, min(1023, max(0, X_P * Kp)))  
         #iicself.set_pwmss(12, min(1023, max(0, Y_P *+ Kp)))
        iicself.set_pwmss(11, X_P * Kp)
        iicself.set_pwmss(12,Y_P *Kp)
        time.sleep(0.065)
        #if st==2:
         #   st=0
       

if __name__ == '__main__':

    capture.set(6, cv.VideoWriter.fourcc('M', 'J', 'P', 'G'))
    capture.set(cv.CAP_PROP_FRAME_WIDTH, 640)
    capture.set(cv.CAP_PROP_FRAME_HEIGHT, 480)
    print("capture get FPS : ", capture.get(cv.CAP_PROP_FPS))
    pTime, cTime = 0, 0
    face_detector = FaceDetector(0.75)


    thread_iic_ernv_oled = threading.Thread(target=iic_ernv_oled)
    thread_iic_ernv_oled.start()
  
    thread_environment_alarm = threading.Thread(target=environment_alarm)
    thread_environment_alarm.start()
    '''  
    thread_onenet_worker = threading.Thread(target=onenet_worker)
    thread_onenet_worker.start()
    '''
    thread_servo_control = threading.Thread(target=servo_control)
    
    thread_servo_control.start()

    while capture.isOpened():
        ret, frame = capture.read()
        frame = cv.flip(frame, 1)   
        frame, bboxs = face_detection_worker(frame, face_detector)
        if cv.waitKey(1) & 0xFF == ord('q'): break
        cTime = time.time()
        fps = 1 / (cTime - pTime)
        pTime = cTime
        text = "FPS : " + str(int(fps))
        cv.putText(frame, text, (20, 30), cv.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 1)
        cv.imshow('frame', frame)
    capture.release()
    cv.destroyAllWindows()