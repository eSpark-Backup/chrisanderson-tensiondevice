
#include "Button.hpp"

int TARE_BUTTON = 1;
int UNIT_TOGGLE = 2;

int MOT_LS = 13;       // the PWM pin the LED is attached to
int brightness = 100;  // how bright the LED is
int MOT = 38;

volatile bool motInterruptTriggered = false;
volatile bool buttonPressed = false;  // Flag set in ISR
unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200 / portTICK_PERIOD_MS;  // milliseconds

volatile bool runFunctionOne = true; 
// int motState;

void buttonSetup() {
  pinMode(UNITLED1, OUTPUT);
  pinMode(UNITLED2, OUTPUT);
  pinMode(TARE_BUTTON, INPUT);
  pinMode(UNIT_TOGGLE, INPUT);
  pinMode(MOT, INPUT);
  pinMode(MOT_LDO, OUTPUT);
  pinMode(MOT_LS, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(MOT), handleMotInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(UNIT_TOGGLE), handleUnitInterrupt, RISING);
}

void IRAM_ATTR handleMotInterrupt() {
  motInterruptTriggered = true;
  // motState = digitalRead(MOT);
}

void motorRun() {
  Serial.println("Motor Start runing");
  digitalWrite(MOT_LDO, HIGH);
  analogWrite(MOT_LS, brightness);
}

void motorStop() {
  motInterruptTriggered = false;
  analogWrite(MOT_LS, 0);
  digitalWrite(MOT_LDO, LOW);
}

void IRAM_ATTR handleUnitInterrupt() {
  unsigned long currentTime = millis();
  // Debounce: Only allow if time since last interrupt is greater than debounce delay
  if (currentTime - lastInterruptTime > debounceDelay) {
    buttonPressed = true;
    Serial.println("Interrupt comes");
    displayClear();
    lastInterruptTime = currentTime;
  }
}

void checkButtonToggle() {
  if (buttonPressed) {
    buttonPressed = false;
    runFunctionOne = !runFunctionOne;
    if (runFunctionOne) {
      Serial.println("Switched to Function milliForce");
    } else {
      Serial.println("Switched to Function gram-Force");
    }
  }
}
