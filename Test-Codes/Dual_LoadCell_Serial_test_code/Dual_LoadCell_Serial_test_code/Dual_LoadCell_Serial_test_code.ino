#include "HX711.h"

// Load Cell 1 Pins
#define DOUT1 17
#define CLK1  16

// Load Cell 2 Pins
#define DOUT2 8
#define CLK2  18

HX711 scale1;
HX711 scale2;

// Calibration factors based on your 61g reference weights
float calibration_factor1 = 6258.62;
float calibration_factor2 = 5237.57;

void setup() {
  Serial.begin(115200);
  Serial.println("Simple Dual HX711 Weight Reader (Grams Only)");

  // Initialize scales
  scale1.begin(DOUT1, CLK1);
  scale2.begin(DOUT2, CLK2);

  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);

  scale1.tare(); // Reset to zero
  scale2.tare();

  Serial.println("Tared. Reading weights...");
}

void loop() {
  float weight1 = scale1.get_units(5); // Average of 5 readings
  float weight2 = scale2.get_units(5);

  Serial.print("Scale 1: ");
  Serial.print(weight1, 2);
  Serial.print(" g | Scale 2: ");
  Serial.print(weight2, 2);
  Serial.println(" g");

  delay(300);
}
