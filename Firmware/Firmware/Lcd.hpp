#ifndef LCD_HPP
#define LCD_HPP

#include "src/OLED/DEV_Config.h"
#include "src/OLED/OLED_Driver.h"
#include "src/OLED/GUI_Paint.h"
#include "src/OLED/Debug.h"
#include "src/OLED/ImageData.h"
#include "LoadCell.hpp"
#include "IO_Handler.hpp"

extern volatile bool displayMode;

void ledinit();
void createImage();
void displayText(int x, int y, const char* text);
void displayValue_gF(int x, int y, int value);
void displayValue_mF(int x, int y, int value);
void displayClear();
void calibrationDisplay();
void removeWeightDisplay1();
void removeWeightDisplay2();
void placeWeightDisplay();
void displayBattValue(int x, int y, int value);
void updateMode();
void showIndividualTensions();
void showTensionDifference();

#endif  // LCD_HPP
