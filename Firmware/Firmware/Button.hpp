#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>

extern int TARE_BUTTON;
extern int UNIT_TOGGLE;
extern int MOT;


# define UNITLED1 4
# define UNITLED2 5
# define MOT_LDO 9

extern volatile bool motInterruptTriggered;


void buttonSetup();
void handleMotInterrupt();
void handleMotInterruptOff();
void motorRun();
void motorStop();

#endif  //BUTTON_HPP