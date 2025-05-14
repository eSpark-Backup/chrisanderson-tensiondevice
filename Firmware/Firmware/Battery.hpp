#ifndef BATTERY_HPP
#define BATTERY_HPP

#include <Arduino.h>
#include "Lcd.hpp"

const int BATT_ADC = 6;

const int VMON_EN = 14;

void batteryInit();
int batteryMonitoring();
void batteryDisplay();

#endif  //BATTERY_HPP