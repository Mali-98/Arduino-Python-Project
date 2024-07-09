import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time

# Establish serial communication with Arduino
arduino = serial.Serial('COM9', 9600)  # Replace 'COM4' with the correct serial port and baud rate
time.sleep(2)  # Allow time for the Arduino to initialize

cap = cv2.VideoCapture(0)  # Open the default camera
detector = HandDetector(detectionCon=0.8, maxHands=1)  # Adjust the confidence threshold and maxHands if needed

while True:
    success, img = cap.read()
    img = cv2.flip(img, 1)  # Flip the image horizontally for a mirrored view
    hands, img = detector.findHands(img)
    num_finger = 0

    if hands:
        hand = hands[0]  # Assuming only one hand is detected
        lmList = hand["lmList"]
        num_finger = detector.fingersUp(hand).count(1)  # Count the number of fingers held up

    arduino.write(str(num_finger).encode())  # Send the number of fingers to the Arduino
    print(num_finger)

    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()