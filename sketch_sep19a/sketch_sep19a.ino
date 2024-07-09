int LED1 = 3;  // Pin for the first LED
int LED2 = 4;  // Pin for the second LED
int LED3 = 5;  // Pin for the third LED

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) {
    int numFinger = Serial.read();  // Read the number of fingers from serial
    if (numFinger == '1') {
      digitalWrite(LED1, HIGH);  // Turn on LED1 if 1 finger is detected
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    } else if (numFinger == '2') {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);  // Turn on LED2 if 2 fingers are detected
      digitalWrite(LED3, LOW);
    } else if (numFinger == '3') {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);  // Turn on LED3 if 3 fingers are detected
    }
    else if (numFinger == '0') {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);  // Turn on LED3 if 3 fingers are detected
    }
    else {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);  // Turn on LED3 if 3 fingers are detected
    }
  }
}
