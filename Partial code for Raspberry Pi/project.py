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

iiclock = threading.Lock()
onenetlock = threading.Lock()
image_stranger = ["/home/pi/temp/myjob/5.jpg"]
image_fire = ["/home/pi/temp/myjob/4.jpg"]
X_P = 425
Y_P = 425
lastError_x = 0
lastError_y = 0
stranger = 0   

all_fire = 0

def iic_ernv_oled():
    while True:
        with iiclock:
            iicself.oled_show()
            onenet.send_data_to_onenet("fire", all_fire)     
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
        img_RGB = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
        results = self.face_detection.process(img_RGB)
        bboxs = []
        current_time = datetime.datetime.now()
        if results.detections:
            if self.detection_start_time is None:
                self.detection_start_time = current_time
            
            for id, detection in enumerate(results.detections):
                bboxC = detection.location_data.relative_bounding_box
                ih, iw, ic = frame.shape
                bbox = int(bboxC.xmin * iw), int(bboxC.ymin * ih), \
                       int(bboxC.width * iw), int(bboxC.height * ih)
                bboxs.append([id, bbox, detection.score])
                frame = self.fancy_draw(frame, bbox)
            if (current_time - self.last_save_time).total_seconds() > 5 * 60 and (current_time - self.detection_start_time).total_seconds() > 1.5:
                self.detection_start_time = None 
                self.last_save_time = current_time
                threading.Thread(target=self.handle_detection, args=(frame,)).start()
 
               
        else:
            self.detection_start_time = None  
 
        return frame, bboxs       

    def handle_detection(self, frame):
        self.save_frame(frame)
        voice.voice(1)
        send_email.send_email_task("Unknown personnel", "Detect unknown personnel, please be aware-- From intelligent security", "3301934971@qq.com", image_stranger)
        
    def fancy_draw(self, frame, bbox, l=30, t=10):
        global X_P, Y_P, lastError_x, lastError_y
        x, y, w, h = bbox
        x1, y1 = x + w, y + h
        cv.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 255), 1)
        cx, cy = x + w // 2, y + h // 2
        thisError_x = cx - 320
        thisError_y = cy - 240
        pwm_x = thisError_x * 5 + 1 * (thisError_x - lastError_x)
        pwm_y = thisError_y * 5 + 1 * (thisError_y - lastError_y)
        lastError_x = thisError_x
        lastError_y = thisError_y
        XP = pwm_x / 100
        YP = pwm_y / 100
        X_P = X_P + int(XP)
        Y_P = Y_P + int(YP)
        max_movement = 10 
        if X_P > 670:
            X_P = 670
        if X_P < 0:
            X_P = 0
        if Y_P > 650:
            Y_P = 650
        if Y_P < 0:
            Y_P = 0
        return frame
    def save_frame(self, frame):
        save_dir = "/home/pi/temp/myjob"
        if not os.path.exists(save_dir):
            os.makedirs(save_dir)
        filename = os.path.join(save_dir, "5.jpg")
        cv.imwrite(filename, frame)
        print(f"Saved {filename}")

def environment_alarm():
    global all_fire
    while True:
        print("Alarm Alarm Alarm Alarm Alarm")
        f1, f2, f3 = fire.fire_detection()
        all_fire = f1 + f2 + f3
        
        if all_fire > 0:  
            voice.voice(2)
            send_email_task("Abnormal environmental detection", "Suspected fire, please note! - from intelligent security", "3301934971@qq.com", image_fire)
        
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
    global X_P, Y_P
    Kp = 0.45
    while True:
        iicself.set_pwmss(11, min(1023, max(0, X_P * Kp)))  
        iicself.set_pwmss(12, min(1023, max(0, Y_P *+ Kp)))
        time.sleep(0.065)

if __name__ == '__main__':
    capture = cv.VideoCapture(-1)
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
