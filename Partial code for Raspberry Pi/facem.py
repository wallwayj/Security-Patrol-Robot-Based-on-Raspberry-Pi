import cv2
import numpy as np
import os
import threading

recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath)

font = cv2.FONT_HERSHEY_SIMPLEX

# names related to ids: example ==> Marcelo: id=1, etc
names = ['None', 'ID=1', 'ID=2', 'ID=3', 'Z', 'W']

# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 320)  # set video width
cam.set(4, 240)  # set video height

# Define min window size to be recognized as a face
minW = 0.1 * cam.get(3)
minH = 0.1 * cam.get(4)

# Shared variables
ret = False
img = None
gray = None
faces = []

# Lock for thread synchronization
lock = threading.Lock()

def process_frame():
    global ret, img, gray, faces
    while True:
        with lock:
            ret, img = cam.read()
            if ret:
                img = cv2.flip(img, 1)  # Flip vertically
                gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                faces = faceCascade.detectMultiScale(
                    gray,
                    scaleFactor=1.1,  # Adjusted scaleFactor for faster detection
                    minNeighbors=3,   # Adjusted minNeighbors for faster detection
                    minSize=(int(minW), int(minH)),
                )

# Start frame processing in a separate thread
thread = threading.Thread(target=process_frame)
thread.daemon = True
thread.start()

while True:
    with lock:
        if ret:
            for (x, y, w, h) in faces:
                cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
                id, confidence = recognizer.predict(gray[y:y+h, x:x+w])
                if confidence < 70:
                    id = names[id]
                    confidence_text = "  {0}%".format(round(100 - confidence))
                else:
                    id = "unknown"
                    confidence_text = "  {0}%".format(round(100 - confidence))
                cv2.putText(img, str(id), (x + 5, y - 5), font, 1, (255, 255, 255), 2)
                cv2.putText(img, str(confidence_text), (x + 5, y + h - 5), font, 1, (255, 255, 0), 1)
            cv2.imshow('camera', img)

    k = cv2.waitKey(10) & 0xff  # Press 'ESC' for exiting video
    if k == 27:
        break

# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()


#frame_count,pTime, cTime = 0, 0,0 

'''
    frame_count += 1
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime
    text = "FPS : " + str(int(fps))
    cv2.putText(img, text, (20, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 1)
'''    

