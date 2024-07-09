import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time
import math

# Establish serial communication with Arduino
arduino = serial.Serial('COM4', 9600)  # Replace 'COM4' with the correct serial port and baud rate
time.sleep(2)  # Allow time for the Arduino to initialize

cap = cv2.VideoCapture(0)  # Open the default camera
detector = HandDetector(detectionCon=0.8, maxHands=1)  # Adjust the confidence threshold and maxHands if needed

while True:
    success, img = cap.read()
    img = cv2.flip(img, 1)  # Flip the image horizontally for a mirrored view
    hands, img = detector.findHands(img)
    distance = 0

    if hands:
        hand = hands[0]  # Assuming only one hand is detected
        lmList = hand["lmList"]
        if len(lmList) >= 4:  # Make sure at least 4 landmarks are detected (thumb and index finger)
            x1, y1 = lmList[4][1:]  # Thumb tip coordinates
            x2, y2 = lmList[8][1:]  # Index finger tip coordinates
            length = math.hypot(x2 - x1, y2 - y1)  # Calculate Euclidean distance between the two points
            distance = int(length)  # Convert distance to an integer

    arduino.write(str(distance).encode())  # Send the distance value to the Arduino
    print(distance)

    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()