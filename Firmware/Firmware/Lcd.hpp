#ifndef LCD_HPP
#define LCD_HPP

#include "src/OLED/DEV_Config.h"
#include "src/OLED/OLED_Driver.h"
#include "src/OLED/GUI_Paint.h"
#include "src/OLED/Debug.h"
#include "src/OLED/ImageData.h"



void ledinit();
// void lcdText();
void createImage();
void displayText(int x, int y, const char* text) ;
void displayValue(int x, int y, int value);
void displayClear();
void displayBattValue(int x, int y, int value);

#endif  // LCD_HPP
