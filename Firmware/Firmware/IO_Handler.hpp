#ifndef IO_HANDLER_HPP
#define IO_HANDLER_HPP

#include <Arduino.h>
#include "Lcd.hpp"

const int TARE_BUTTON = 1;
const int UNIT_TOGGLE = 2;
const int MOT = 38;


#define UNITLED1 4
#define UNITLED2 5
#define MOT_LDO 9

extern volatile bool runFunctionOne;

void buttonSetup();
void handleUnitInterrupt();
bool checkMotorButtonStatus();
bool checkTareButtonStatus();
void motorRun();
void motorStop();
void checkButtonToggle();
void ledIndicationFor_mF();
void ledIndicationFor_gF();


#endif  // IO_HANDLER_HPP