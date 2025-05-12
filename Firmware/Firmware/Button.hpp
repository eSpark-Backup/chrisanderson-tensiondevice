#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>
#include "Lcd.hpp"
extern int TARE_BUTTON;
extern int UNIT_TOGGLE;
extern int MOT;


# define UNITLED1 4
# define UNITLED2 5
# define MOT_LDO 9

extern volatile bool motInterruptTriggered;
extern volatile bool runFunctionOne;

void buttonSetup();
void handleMotInterrupt();
void handleUnitInterrupt();
void motorRun();
void motorStop();
void checkButtonToggle();


#endif  //BUTTON_HPP