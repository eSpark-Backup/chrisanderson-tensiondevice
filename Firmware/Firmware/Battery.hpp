#ifndef BATTERY_HPP
#define BATTERY_HPP

#include <Arduino.h>

const int BATT_ADC = 6; 

const int VMON_EN = 14 ;

// extern float V_ad;

void batteryInit();
int batteryMonitoring();

#endif //BATTERY_HPP