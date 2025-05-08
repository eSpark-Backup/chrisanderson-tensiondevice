#ifndef LOADCELL_HPP
#define LOADCELL_HPP
#include "HX711.h"

// Load Cell 1 Pins
#define DOUT1 17
#define CLK1  16

// Load Cell 2 Pins
#define DOUT2 8
#define CLK2  18

// Calibration factors based on your 61g reference weights


void loadCellInit();
int loadCell_1();
int loadCell_2();
void resetLoadCell();

#endif  //LOADCELL_HPP