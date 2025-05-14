
#include "IO_Handler.hpp"

int MOT_LS = 13;
int brightness = 100;

volatile bool buttonPressed = false;
unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;
volatile bool runFunctionOne = true;


void buttonSetup() {
  pinMode(UNITLED1, OUTPUT);
  pinMode(UNITLED2, OUTPUT);
  pinMode(TARE_BUTTON, INPUT);
  pinMode(UNIT_TOGGLE, INPUT);
  pinMode(MOT, INPUT);
  pinMode(MOT_LDO, OUTPUT);
  pinMode(MOT_LS, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(UNIT_TOGGLE), handleUnitInterrupt, FALLING);
}

void IRAM_ATTR handleUnitInterrupt() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelay) {
    buttonPressed = true;
    displayClear();
    lastInterruptTime = currentTime;
  }
}

bool checkMotorButtonStatus() {
  return digitalRead(MOT) == HIGH;
}

bool checkTareButtonStatus() {
  return digitalRead(TARE_BUTTON) == HIGH;
}

void ledIndicationFor_mF() {
  digitalWrite(UNITLED2, LOW);
  digitalWrite(UNITLED1, HIGH);
}

void ledIndicationFor_gF() {
  digitalWrite(UNITLED2, HIGH);
  digitalWrite(UNITLED1, LOW);
}

void motorRun() {
  Serial.println("Motor Start runing");
  digitalWrite(MOT_LDO, HIGH);
  analogWrite(MOT_LS, brightness);
}

void motorStop() {
  analogWrite(MOT_LS, 0);
  digitalWrite(MOT_LDO, LOW);
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
