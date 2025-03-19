#include <RH_ASK.h>
#include <SPI.h>  // Required on some boards

RH_ASK driver(2000, 11, 12, 10);

const int ledPin = 7;    // WHITE LED
const int ledPin2 = 6;    // STATUS LED
bool runReceiver = false;      // Control flag for receiver
bool ledState = false;        // LED initially off

void setup() {
  Serial.begin(9600);
  if (!driver.init()) {
    Serial.println("RadioHead init failed");
  }
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2,OUTPUT); 

  digitalWrite(ledPin, LOW); 
  digitalWrite(ledPin2, LOW); 
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
    }
  }
}

