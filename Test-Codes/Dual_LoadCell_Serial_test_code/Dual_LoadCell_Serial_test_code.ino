#include "HX711.h"

// Load Cell 1 (Connected to DOUT=GPIO8, SCK=GPIO18)
#define DT_PIN1 8   
#define SCK_PIN1 18  
float calibration_factor1 = 0.01019; 

// Load Cell 2 (Connected to DOUT=GPIO17, SCK=GPIO16)
#define DT_PIN2 17   
#define SCK_PIN2 16  
float calibration_factor2 = 0.01006; 

// Manual tare button
#define TARE_BUTTON 1  

HX711 scale1;
HX711 scale2;

void setup() {
    Serial.begin(115200);
    pinMode(TARE_BUTTON, INPUT_PULLDOWN);

    scale1.begin(DT_PIN1, SCK_PIN1);
    scale2.begin(DT_PIN2, SCK_PIN2);

    Serial.println("Taring... Remove any weight from the scales.");
    delay(2000);

    scale1.tare(); // Tare on startup
    scale2.tare(); 

    Serial.println("Tared successfully! Ready for measurement.");
}

void loop() {
    if (digitalRead(TARE_BUTTON) == HIGH) {
        Serial.println("Manual tare triggered...");
        scale1.tare();
        scale2.tare();
        delay(1000); // Debounce delay
    }

    float raw_value1 = scale1.get_units(10); // Average of 10 readings
    float raw_value2 = scale2.get_units(10);

    float weight1 = raw_value1 * calibration_factor1; // Convert to grams
    float weight2 = raw_value2 * calibration_factor2;

    Serial.print("Load Cell 1 Weight (grams): ");
    Serial.println(weight1);

    Serial.print("Load Cell 2 Weight (grams): ");
    Serial.println(weight2);

    Serial.println("----------------------");
    delay(500);
}
