
#include "Battery.hpp"
float R1      =     100.0  ;// resistance 100K
float R2     =      270.0 ;// resistance 270K
// float V_ad;
void batteryInit(){
  pinMode(VMON_EN, OUTPUT);
  pinMode(BATT_ADC, INPUT);
  digitalWrite(VMON_EN, HIGH);
}
int batteryMonitoring()
  {
    int adcValue = analogRead(BATT_ADC);
    float V_min = 3.0;  
    float V_max = 4.2;  
    //  Serial.println(adcValue);
    float V_adc =  (adcValue * 4.4 ) / 4096.0;
    
    // Serial.print("Mapping Value  is : ");
    // Serial.println(V_adc);
   
    if (V_adc > V_max) V_adc = V_max;
    if (V_adc < V_min) V_adc = V_min;
    float batteryPercentage = ((V_adc - V_min) / (V_max - V_min)) * 100.0;
    if (batteryPercentage > 100.0) batteryPercentage = 100.0;
    if (batteryPercentage < 0.0) batteryPercentage = 0.0;
    // Serial.print("Battery Voltage: ");
    // Serial.print(V_adc, 2);
    // Serial.print(" V, Battery Percentage: ");
    // Serial.print(batteryPercentage, 1);
    // Serial.println(" %");
    batteryPercentage = round(batteryPercentage);
    return (int)batteryPercentage;
  }