from gpiozero import Button
import time
from time import sleep
import threading
import mediapipe as mp
import cv2
import datetime
import os
import send_email
import onenet
import iicself
import voice
import fire

# Global variables and initializations
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

# Function to show data on OLED display and send data to OneNet
def iic_ernv_oled():
    while True:
        with iiclock:
            iicself.oled_show()
            onenet.send_data_to_onenet("fire", all_fire)
        time.sleep(0.8)

# Face detection worker function
def face_detection_worker(frame, detector):
    return detector.find_faces(frame)

# FaceDetector class definition
class FaceDetector:
    def __init__(self, min_detection_confidence=0.5):
        self.mpFaceDetection = mp.solutions.face_detection
        self.mpDraw = mp.solutions.drawing_utils
        self.face_detection = self.mpFaceDetection.FaceDetection(min_detection_confidence=min_detection_confidence)
        self.last_save_time = datetime.datetime.now() - datetime.timedelta(minutes=5)
        self.last_detection_time = None
        self.detection_start_time = None

    def find_faces(self, frame):
        ret, img = cam.read()
        img = cv2.flip(img, 1)  # Flip vertically
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        faces = faceCascade.detectMultiScale(
            gray,
            scaleFactor=1.2,
            minNeighbors=5,
            minSize=(int(minW), int(minH)),
        )

        bboxs = []
        current_time = datetime.datetime.now()
        if len(faces) > 0:
            if self.detection_start_time is None:
                self.detection_start_time = current_time

            for id, (x, y, w, h) in enumerate(faces):
                bbox = (x, y, w, h)
                bboxs.append([id, bbox, None])  # Note: 'detection.score' is not used in this approach
                cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
                id, confidence = recognizer.predict(gray[y:y + h, x:x + w])
                if confidence < 70:
                    id = names[id]
                    confidence_text = "  {0}%".format(round(100 - confidence))
                else:
                    id = "unknown"
                    confidence_text = "  {0}%".format(round(100 - confidence))

                cv2.putText(img, str(id), (x + 5, y - 5), font, 1, (255, 255, 255), 2)
                cv2.putText(img, str(confidence_text), (x + 5, y + h - 5), font, 1, (255, 255, 0), 1)

            if (current_time - self.last_save_time).total_seconds() > 5 * 60 and (
                    current_time - self.detection_start_time).total_seconds() > 1.5:
                self.detection_start_time = None
                self.last_save_time = current_time
                threading.Thread(target=self.handle_detection, args=(img,)).start()

        else:
            self.detection_start_time = None

        return img, bboxs

    def handle_detection(self, frame):
        self.save_frame(frame)
        voice.voice(1)
        send_email.send_email_task("Unknown personnel", "Detect unknown personnel, please be aware-- From intelligent security", "3301934971@qq.com", image_stranger)

    def fancy_draw(self, frame, bbox, l=30, t=10):
        global X_P, Y_P, lastError_x, lastError_y
        x, y, w, h = bbox
        x1, y1 = x + w, y + h
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 255), 1)
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
        cv2.imwrite(filename, frame)
        print(f"Saved {filename}")

# Function to handle environmental alarm
def environment_alarm():
    global all_fire
    while True:
        print("Alarm Alarm Alarm Alarm Alarm")
        f1, f2, f3 = fire.fire_detection()
        all_fire = f1 + f2 + f3

        if all_fire > 0:
            voice.voice(2)
            send_email.send_email_task("Abnormal environmental detection", "Suspected fire, please note! - from intelligent security", "3301934971@qq.com", image_fire)

        iicself.tvoc_alarm()
        time.sleep(1)

# Function to control servo
def servo_control():
    global X_P, Y_P
    Kp = 0.45
    while True:
        iicself.set_pwmss(11, min(1023, max(0, X_P * Kp)))
        iicself.set_pwmss(12, min(1023, max(0, Y_P * Kp)))
        time.sleep(0.065)

if __name__ == '__main__':
    recognizer = cv2.face.LBPHFaceRecognizer_create()
    recognizer.read('trainer/trainer.yml')
    cascadePath = "haarcascade_frontalface_default.xml"
    faceCascade = cv2.CascadeClassifier(cascadePath)

    font = cv2.FONT_HERSHEY_SIMPLEX
    id = 0
    names = ['None', 'ID=1', 'ID=2', 'ID=3', 'Z', 'W']
    cam = cv2.VideoCapture(0)
    cam.set(3, 640)  # set video width
    cam.set(4, 480)  # set video height
    minW = 0.1 * cam.get(3)
    minH = 0.1 * cam.get(4)
    frame_count, pTime, cTime = 0, 0, 0

    # Start threads
    thread_iic_ernv_oled = threading.Thread(target=iic_ernv_oled)
    thread_iic_ernv_oled.start()

    thread_environment_alarm = threading.Thread(target=environment_alarm)
    thread_environment_alarm.start()

    thread_servo_control = threading.Thread(target=servo_control)
    thread_servo_control.start()

    detector = FaceDetector()

    while True:
        ret, img = cam.read()
        if not ret:
            break

        img, bboxs = detector.find_faces(img)
        frame_count += 1
        cTime = time.time()
        fps = 1 / (cTime - pTime)
        pTime = cTime
        text = "FPS : " + str(int(fps))
        cv2.putText(img, text, (20, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 1)
        cv2.imshow('camera', img)

        k = cv2.waitKey(10) & 0xff  # Press 'ESC' for exiting video
        if k == 27:
            break

    # Do a bit of cleanup
    print("\n [INFO] Exiting Program and cleanup stuff")
    cam.release()
    cv2.destroyAllWindows()