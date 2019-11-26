import cv2
import numpy as np
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
def nothing(x):
    pass
cap = cv2.VideoCapture(0)
cv2.namedWindow("frame")
cv2.createTrackbar("KP", "frame", 0, 10, nothing)
cv2.createTrackbar("KD", "frame", 0, 10, nothing)
cv2.createTrackbar("KI", "frame", 0, 10, nothing)
cv2.createTrackbar("SP", "frame", 0, 100, nothing)
spAtual = 1
kiAtual = 1
kpAtual = 1
kdAtual = 1
while True:
    _, frame = cap.read()
    kp = cv2.getTrackbarPos("KP", "frame")    
    ki = cv2.getTrackbarPos("KI", "frame")
    kd = cv2.getTrackbarPos("KD", "frame")
    sp = cv2.getTrackbarPos("SP", "frame")

    if (sp != spAtual):
    	ser.write(b'sp' + str(sp).encode())
    if (kp != kpAtual):
    	ser.write(b'kp' + str(kp).encode())
    if (ki != kiAtual):
    	ser.write(b'ki' + str(ki).encode())
    if (kd != kdAtual):
    	ser.write(b'kd' + str(kd).encode())


    spAtual = sp
    kpAtual = kp
    kiAtual = ki
    kdAtual = kd
    cv2.imshow("frame", frame)
    key = cv2.waitKey(1)
    if key == 27:
        break
cap.release()
cv2.destroyAllWindows()
