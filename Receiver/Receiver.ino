#include <RH_ASK.h>
#include <SPI.h>
#include <Servo.h>  // Include the Servo library

RH_ASK driver(2000, 11, 12, 10);

const int ledPin = 7;    // LED for TOGGLE command
const int ledPin2 = 6;   // Status LED
bool runReceiver = true;      // Enable receiver (set to true)
bool ledState = false;        // LED initially off

Servo myServo;         // Create a Servo object
const int servoPin = 8; // Servo control pin

void setup() {
  Serial.begin(9600);
  if (!driver.init()) {
    Serial.println("RadioHead init failed");
  }
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT); 

  digitalWrite(ledPin, LOW); 
  digitalWrite(ledPin2, LOW); 

  // Attach the servo to the designated pin and set initial position to 0°
  myServo.attach(servoPin);
  myServo.write(0);
}

void loop() {
  if (runReceiver) {
    digitalWrite(ledPin2, HIGH);
    
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    
    if (driver.recv(buf, &buflen)) {
      if (buflen < RH_ASK_MAX_MESSAGE_LEN) {
        buf[buflen] = '\0';
      }
      String receivedMsg = (char*)buf;
      Serial.print("Received: ");
      Serial.println(receivedMsg);
      
      if (receivedMsg == "TOGGLE") {
        ledState = !ledState;  
        digitalWrite(ledPin, ledState ? HIGH : LOW);
        Serial.print("LED toggled to ");
        Serial.println(ledState ? "ON" : "OFF");
      }
      else if (receivedMsg == "SERVO0") {
        myServo.write(0);  // Move servo to 0° position
        Serial.println("Servo set to 0°");
      }
      else if (receivedMsg == "SERVO45") {
        myServo.write(45); // Move servo to 45° position
        Serial.println("Servo set to 45°");
      }
      else if (receivedMsg == "SERVO180") {
        myServo.write(90); // Move servo to 180° position
        Serial.println("Servo set to 180°");
      }
    }
  }
}


