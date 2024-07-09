#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
void setup() {
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {

  if (Serial.available() > 0) {
    
    byte buffer[4];  
    Serial.readBytes(buffer, sizeof(buffer));
    int num = convertBytesToInt(buffer);
    // Map value from Python 0-255 range to analogWrite 0-1023 range
    lcd.setCursor(0,0);
    lcd.print(num); 
    analogWrite(A0, num);

  }
}

int convertBytesToInt(byte buffer[]) {

  int num = 0;
  
  for (int i=0; i<sizeof(buffer); i++) {
    num += buffer[i] - '0';  
    if (i < sizeof(buffer)-1) {
      num *= 10;
    }
  }

  return num;

}