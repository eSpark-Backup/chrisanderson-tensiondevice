#ifndef LOADCELL_HPP
#define LOADCELL_HPP
#include "HX711.h"


// Load Cell 1 Pins
#define DOUT1 17
#define CLK1 16

// Load Cell 2 Pins
#define DOUT2 8
#define CLK2 18

void loadCellInit();
int loadCell_1();
int loadCell_2();
void resetLoadCell();

void calibrateBothLoadCells();

#endif  //LOADCELL_HPP