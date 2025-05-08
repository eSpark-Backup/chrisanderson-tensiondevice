#include "LoadCell.hpp"

float calibration_factor1 = 6258.62;
float calibration_factor2 = 2610;
int weight1;
int weight2;

HX711 scale1;
HX711 scale2;

void loadCellInit(){
  Serial.println("Simple Dual HX711 Weight Reader (Grams Only)");
  // Initialize scales
  scale1.begin(DOUT1, CLK1);
  scale2.begin(DOUT2, CLK2);
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);
  scale1.tare(calibration_factor1); // Reset to zero
  scale2.tare(calibration_factor2);
  Serial.println("Tared. Reading weights...");
}

int loadCell_1()
{
    weight1 = scale1.get_units(5); // Average of 5 readings
    return weight1;
}

int loadCell_2()
{
    weight2 = scale2.get_units(5); // Average of 5 readings
    return weight2;
}

void resetLoadCell(){
   Serial.println("Call tare to calibrate zero..");
  scale1.tare(); 
  scale2.tare();
}