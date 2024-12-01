 
import cv2 as cv
import numpy as np
import os 
import time
recognizer = cv.face.LBPHFaceRecognizer_create()
recognizer.read('trainer/trainer.yml')
cascadePath = "haarcascade_frontalface_default.xml"
faceCascade = cv.CascadeClassifier(cascadePath);

font = cv.FONT_HERSHEY_SIMPLEX
id = 0
names = ['None', 'ID=1', 'ID=2', 'ID=3', 'Z', 'W'] 
cam = cv.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)
frame_count,pTime, cTime = 0, 0,0 
while True:
    ret, frame =cam.read()
    frame = cv.flip(frame, 1) # Flip vertically
    gray = cv.cvtColor(frame,cv.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )
    for(x,y,w,h) in faces:
        cv.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 2)
        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
        if (confidence < 70):
            id = names[id]
            confidence = "  {0}%".format(round(100 - confidence))
        else:
            id = "unknown"
            confidence = "  {0}%".format(round(100 - confidence))
        cv.putText(frame, str(id), (x+5,y-5), font, 1, (255,255,255), 2)
        cv.putText(frame, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  
    frame_count += 1
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime
    text = "FPS : " + str(int(fps))
    cv.putText(frame, text, (20, 30), cv.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 1)#frame_count,pTime, cTime = 0, 0,0 
    cv.imshow('camera',frame) 
    k = cv.waitKey(10) & 0xff # Press 'ESC' for exiting video
    if k == 27:
        break
# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv.destroyAllWindows()
 
