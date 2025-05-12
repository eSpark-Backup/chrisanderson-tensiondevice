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
  checkButtonToggle();
  // BAttery Monitoring //
  int battPerc = batteryMonitoring();
  displayBattValue(95, 5, battPerc);

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

// Display Tension Values//
if (runFunctionOne) {
  int loadCellValue_1 = loadCell_1();
  int loadCellValue_2 = loadCell_2();
  displayText(5, 20, "Tension 1 : ");
  displayText(5, 40, "Tension 2 : ");
  displayValue_mF(85, 40, loadCellValue_2 );
  displayValue_mF(85, 20, loadCellValue_1);
  digitalWrite(UNITLED2, LOW);
  digitalWrite(UNITLED1, HIGH);
} else {
  int loadCellValue_1 = loadCell_1();
  int loadCellValue_2 = loadCell_2();
  digitalWrite(UNITLED2, HIGH);
  digitalWrite(UNITLED1, LOW);
  displayText(5, 20, "Tension 1 : ");
  displayText(5, 40, "Tension 2 : ");
  displayValue_gF(85, 40, loadCellValue_2);
  displayValue_gF(85, 20, loadCellValue_1);
}



}