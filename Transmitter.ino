#include <RH_ASK.h>
#include <SPI.h>
#include <servo.h>


RH_ASK driver(2000, 11, 12, 10);

const int buttonPin = 2;      // Launch PushButton 
bool runTransmitter = false;   


int lastButtonState = HIGH;  
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;  // 50 milliseconds debounce

void setup() {
  Serial.begin(9600);

  if (!driver.init()) {
    Serial.println("RadioHead init failed");
  }
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  if (runTransmitter) {
    int reading = digitalRead(buttonPin);

    // If the button reading has changed, reset the debounce timer
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
  
      if (reading != buttonState) {
        buttonState = reading;
        if (buttonState == LOW) {
          const char* msg = "TOGGLE";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();  
          Serial.println("Sent TOGGLE command");
          delay(500); 
        }
      }
    }
    
    lastButtonState = reading;

  
  }
}


