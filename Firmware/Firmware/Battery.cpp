
#include "Battery.hpp"
float R1 = 100.0;  // resistance 100K
float R2 = 270.0;  // resistance 270K
// float V_ad;

#define WAKE_INTERVAL_SEC 10 

void batteryInit() {
  pinMode(VMON_EN, OUTPUT);
  pinMode(BATT_ADC, INPUT);
  digitalWrite(VMON_EN, HIGH);
}
// int batteryMonitoring() {
//   int adcValue = analogRead(BATT_ADC);
//   float V_min = 3.0;
//   float V_max = 4.2;
//   float V_adc = (adcValue * 4.4) / 4096.0;

//   if (V_adc > V_max) V_adc = V_max;
//   if (V_adc < V_min) V_adc = V_min;
//   float batteryPercentage = ((V_adc - V_min) / (V_max - V_min)) * 100.0;
//   if (batteryPercentage > 100.0) batteryPercentage = 100.0;
//   if (batteryPercentage < 0.0) batteryPercentage = 0.0;
//   Serial.print("Battery Voltage: ");
//   Serial.print(V_adc, 2);
//   Serial.print(" V, Battery Percentage: ");
//   Serial.print(batteryPercentage, 1);
//   Serial.println(" %");
//   batteryPercentage = round(batteryPercentage);
//   return (int)batteryPercentage;
// }

void batteryDisplay() {
  int battPerc = batteryMonitoring();
  displayBattValue(95, 5, battPerc);
}

// Voltage-to-capacity lookup table
struct VoltageCapacity {
  float voltage;
  int capacity;
};

// Table based on your image (1S Li-ion)
VoltageCapacity battTable[] = {
  {4.20, 100},
  {4.15, 95},
  {4.11, 90},
  {4.08, 85},
  {4.02, 80},
  {3.98, 75},
  {3.95, 70},
  {3.91, 65},
  {3.87, 60},
  {3.85, 55},
  {3.84, 50},
  {3.82, 45},
  {3.80, 40},
  {3.79, 35},
  {3.77, 30},
  {3.75, 25},
  {3.73, 20},
  {3.71, 15},
  {3.69, 10},
  {3.61, 5},
  {3.27, 0}
};

// int batteryMonitoring() {
//   int adcValue = analogRead(BATT_ADC);
//   float V_adc = (adcValue * 4.4) / 4096.0; // Adjust this if your ADC reference is different

//   // Safety shutdown at or below 3.98V
//   if (V_adc <= 3.69) {
//     Serial.println("⚠️ Low voltage detected! Shutting down...");
//     displayClear();
//     displayText(5,20, "Battery Low!");
//     delay(1000);
//     displayText(5,30, "Shut Down..");
//     esp_sleep_enable_timer_wakeup(WAKE_INTERVAL_SEC * 1000000ULL);
//     esp_deep_sleep_start();
//   }

//   // Clamp voltage
//   if (V_adc > 4.2) V_adc = 4.2;
//   if (V_adc < 3.27) V_adc = 3.27;

//   // Interpolate capacity based on lookup table
//   int capacity = 0;
//   for (int i = 0; i < sizeof(battTable) / sizeof(battTable[0]) - 1; i++) {
//     if (V_adc >= battTable[i + 1].voltage && V_adc <= battTable[i].voltage) {
//       float slope = (battTable[i].capacity - battTable[i + 1].capacity) /
//                     (battTable[i].voltage - battTable[i + 1].voltage);
//       capacity = battTable[i + 1].capacity +
//                  (V_adc - battTable[i + 1].voltage) * slope;
//       break;
//     }
//   }

//   Serial.print("Battery Voltage: ");
//   Serial.print(V_adc, 2);
//   Serial.print(" V, Battery Percentage: ");
//   Serial.print(capacity);
//   Serial.println(" %");

//   return capacity;
// }


#define NUM_SAMPLES 4
#define MONITOR_INTERVAL 10000  // 10 seconds in milliseconds

unsigned long lastMonitorTime = 0;
int capacitySamples[NUM_SAMPLES];
int sampleIndex = 0;
bool bufferFilled = false;

int batteryMonitoring() {
  unsigned long currentMillis = millis();

  // if (currentMillis - lastMonitorTime >= MONITOR_INTERVAL) 
  //   lastMonitorTime = currentMillis;

    int adcValue = analogRead(BATT_ADC);
    float V_adc = (adcValue * 4.4) / 4096.0;

    // Safety shutdown
    if (V_adc <= 3.69) {
      Serial.println("⚠️ Low voltage detected! Shutting down...");
      displayClear();
      displayText(5,20, "Battery Low!");
      delay(1000);
      displayText(5,30, "Shut Down..");
      esp_sleep_enable_timer_wakeup(WAKE_INTERVAL_SEC * 1000000ULL);
      esp_deep_sleep_start();
    }

    // Clamp voltage
    if (V_adc > 4.2) V_adc = 4.2;
    if (V_adc < 3.27) V_adc = 3.27;

    // Interpolate capacity from table
    int capacity = 0;
    for (int i = 0; i < sizeof(battTable) / sizeof(battTable[0]) - 1; i++) {
      if (V_adc >= battTable[i + 1].voltage && V_adc <= battTable[i].voltage) {
        float slope = (battTable[i].capacity - battTable[i + 1].capacity) /
                      (battTable[i].voltage - battTable[i + 1].voltage);
        capacity = battTable[i + 1].capacity +
                   (V_adc - battTable[i + 1].voltage) * slope;
        break;
      }
    }

    // Store the capacity in the buffer
    capacitySamples[sampleIndex] = capacity;
    sampleIndex++;
    if (sampleIndex >= NUM_SAMPLES) {
      sampleIndex = 0;
      bufferFilled = true;
    }

    // Calculate average
    int sampleCount = bufferFilled ? NUM_SAMPLES : sampleIndex;
    int sum = 0;
    for (int i = 0; i < sampleCount; i++) {
      sum += capacitySamples[i];
    }
    int avgCapacity = sum / sampleCount;

    Serial.print("Battery Voltage: ");
    Serial.print(V_adc, 2);
    Serial.print(" V, Battery Avg Percentage: ");
    Serial.print(avgCapacity);
    Serial.println(" %");
    return avgCapacity;
  // }

}
