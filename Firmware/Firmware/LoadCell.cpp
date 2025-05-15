#include "LoadCell.hpp"
#include <Preferences.h>
#include "Lcd.hpp"

float calibration_factor1 = 3350.0;
float calibration_factor2 = 2610.0;
int weight1;
int weight2;

HX711 scale1;
HX711 scale2;

Preferences prefs;

#define CALIB_KEY1 "calib1"
#define CALIB_KEY2 "calib2"

#define KNOWNWEIGHT 100.0   //put 100g for calibrartion 

void loadCellInit() {
  Serial.println("Simple Dual HX711 Weight Reader (Grams Only)");
  prefs.begin("loadcell", false);
  calibration_factor1 = prefs.getFloat(CALIB_KEY1, 3350.0); // Default if not saved
  calibration_factor2 = prefs.getFloat(CALIB_KEY2, 2610.0);
  prefs.end();
  // Initialize scales
  scale1.begin(DOUT1, CLK1);
  scale2.begin(DOUT2, CLK2);
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);
  scale1.tare(calibration_factor1);  // Reset to zero
  scale2.tare(calibration_factor2);
  Serial.println("Tared. Reading weights...");
}

void calibrateLoadCell(HX711 &scale, const char* key, float &calibFactor) {
  
  Serial.println("Taring... Remove any weight.");
  scale.set_scale();
  scale.tare();
  delay(2000);
  placeWeightDisplay();
  Serial.println("Place a known weight on the scale...");
  delay(5000); // Wait for user to place weight

  float raw = scale.get_units(5); // Raw units
  Serial.print("Raw value: ");
  Serial.println(raw);

  // Serial.print("Enter known weight in grams: ");
  // while (!Serial.available());  // Wait for input
  // float knownWeight = Serial.parseFloat();
  //  float knownWeight = 110.0;
  // Serial.println(knownWeight);

  // calibFactor = knownWeight / raw;
  scale.calibrate_scale(KNOWNWEIGHT,5);
  calibFactor = scale.get_scale();
  scale.set_scale(calibFactor);

  Serial.print("Calibration factor set: ");
  Serial.println(calibFactor);

  prefs.begin("loadcell", false);
  prefs.putFloat(key, calibFactor);
  prefs.end();
}

void calibrateBothLoadCells() {
  Serial.println("Calibrating Load Cell 1...");
  calibrationDisplay();
  delay(2000);
  removeWeightDisplay1();
  calibrateLoadCell(scale1, CALIB_KEY1, calibration_factor1);
  removeWeightDisplay2();
  Serial.println("Calibrating Load Cell 2...");
  calibrateLoadCell(scale2, CALIB_KEY2, calibration_factor2);
}


int loadCell_1() {
  weight1 = scale1.get_units(5);  // Average of 5 readings
  return weight1;
}

int loadCell_2() {
  weight2 = scale2.get_units(5);  // Average of 5 readings
  return weight2;
}

void resetLoadCell() {
  Serial.println("Call tare to calibrate zero..");
  scale1.tare();
  scale2.tare();
}