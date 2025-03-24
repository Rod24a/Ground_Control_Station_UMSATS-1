#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 11, 12, 10);

// Button pin definitions
const int toggleButtonPin = 2;    // For LED toggle command ("TOGGLE")
const int servoButton0Pin = 3;      // For servo position 0° ("SERVO0")
const int servoButton45Pin = 4;     // For servo position 45° ("SERVO45")
const int servoButton180Pin = 5;    // For servo position 180° ("SERVO180")

// Control flag to enable transmitter actions
bool runTransmitter = true;

// Debounce variables for toggle button
int lastToggleButtonState = HIGH;
int toggleButtonState = HIGH;
unsigned long lastDebounceTimeToggle = 0;

// Debounce variables for servo button (0°)
int lastServoButton0State = HIGH;
int servoButton0State = HIGH;
unsigned long lastDebounceTime0 = 0;

// Debounce variables for servo button (45°)
int lastServoButton45State = HIGH;
int servoButton45State = HIGH;
unsigned long lastDebounceTime45 = 0;

// Debounce variables for servo button (180°)
int lastServoButton180State = HIGH;
int servoButton180State = HIGH;
unsigned long lastDebounceTime180 = 0;

const unsigned long debounceDelay = 50;  // milliseconds

void setup() {
  Serial.begin(9600);
  if (!driver.init()) {
    Serial.println("RadioHead init failed");
  }
  
  // Initialize push button pins with internal pull-up resistors
  pinMode(toggleButtonPin, INPUT_PULLUP);
  pinMode(servoButton0Pin, INPUT_PULLUP);
  pinMode(servoButton45Pin, INPUT_PULLUP);
  pinMode(servoButton180Pin, INPUT_PULLUP);
}

void loop() {
  if (runTransmitter) {
    // --- Check Toggle Button for LED ---
    int readingToggle = digitalRead(toggleButtonPin);
    if (readingToggle != lastToggleButtonState) {
      lastDebounceTimeToggle = millis();
    }
    if ((millis() - lastDebounceTimeToggle) > debounceDelay) {
      if (readingToggle != toggleButtonState) {
        toggleButtonState = readingToggle;
        if (toggleButtonState == LOW) {  // Button pressed
          const char* msg = "TOGGLE";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          Serial.println("Sent TOGGLE command");
          delay(500);
        }
      }
    }
    lastToggleButtonState = readingToggle;
    
    // --- Check Servo Button for 0° ---
    int reading0 = digitalRead(servoButton0Pin);
    if (reading0 != lastServoButton0State) {
      lastDebounceTime0 = millis();
    }
    if ((millis() - lastDebounceTime0) > debounceDelay) {
      if (reading0 != servoButton0State) {
        servoButton0State = reading0;
        if (servoButton0State == LOW) {
          const char* msg = "SERVO0";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          Serial.println("Sent SERVO0 command");
          delay(500);
        }
      }
    }
    lastServoButton0State = reading0;
    
    // --- Check Servo Button for 45° ---
    int reading45 = digitalRead(servoButton45Pin);
    if (reading45 != lastServoButton45State) {
      lastDebounceTime45 = millis();
    }
    if ((millis() - lastDebounceTime45) > debounceDelay) {
      if (reading45 != servoButton45State) {
        servoButton45State = reading45;
        if (servoButton45State == LOW) {
          const char* msg = "SERVO45";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          Serial.println("Sent SERVO45 command");
          delay(500);
        }
      }
    }
    lastServoButton45State = reading45;
    
    // --- Check Servo Button for 180° ---
    int reading180 = digitalRead(servoButton180Pin);
    if (reading180 != lastServoButton180State) {
      lastDebounceTime180 = millis();
    }
    if ((millis() - lastDebounceTime180) > debounceDelay) {
      if (reading180 != servoButton180State) {
        servoButton180State = reading180;
        if (servoButton180State == LOW) {
          const char* msg = "SERVO180";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          Serial.println("Sent SERVO180 command");
          delay(500);
        }
      }
    }
    lastServoButton180State = reading180;
  }
}



