#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  
int LED1 = 3;  // Pin for the first LED
int LED2 = 4;  // Pin for the second LED
int LED3 = 5;  // Pin for the third LED
int x=0;
int y=0;
int z=0;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if(x==1) digitalWrite(LED1, HIGH);
  if(y==1) digitalWrite(LED2, HIGH);
  if(z==1) digitalWrite(LED3, HIGH);
  if (Serial.available() > 0) {
    int numFinger = Serial.read();  // Read the number of fingers from serial
    if (numFinger == '1') {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("One Finger Up");
      digitalWrite(LED1, HIGH);  // Turn on LED1 if 1 finger is detected
      if(x==0) x=1;
      else x=0;
    } else if (numFinger == '2') {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Two Fingers Up");
      digitalWrite(LED1, LOW);
      if(y==0) y=1;
      else y=0;
    } else if (numFinger == '3') {
      digitalWrite(LED1, LOW);
      if(z==0) z=1;
      else z=0;
    }
    else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);  // Turn on LED3 if 3 fingers are detected
      x=0;
      y=0;
      z=0;
    }
  }
}
