#include <Arduino.h>
#include "Lcd.hpp"
#include "LoadCell.hpp"
#include "Button.hpp"
#include "Battery.hpp"

void setup() {
  Serial.begin(115200);
  ledinit();
  loadCellInit();
  batteryInit();
  buttonSetup();
}

void loop() {
  // BAttery Monitoring //
  int battPerc = batteryMonitoring();
  displayBattValue(95, 5, battPerc);

  // Display Tension Values
  int loadCellValue_1 = loadCell_1();
  int loadCellValue_2 = loadCell_2();
  displayText(5, 20, "Tension 1 : ");
  displayText(5, 40, "Tension 2 : ");
  // if (loadCellValue_1 > 0 || loadCellValue_2 > 0) {
    displayValue(85, 40, loadCellValue_2);
    displayValue(85, 20, loadCellValue_1);
  // } 
  // else {
  //   displayValue(85, 40, 0);
  //   displayValue(85, 20, 0);
  // }

  // Motor Running //
  if (motInterruptTriggered) {
    if (digitalRead(MOT) == HIGH) {
      motorRun();
    } else {
      motorStop();
    }
  }  
 
 // Tare Button Reset Functionality //
  if (digitalRead(TARE_BUTTON) == HIGH){
    resetLoadCell();
  }



}