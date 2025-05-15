#include <Arduino.h>
#include "Lcd.hpp"
#include "LoadCell.hpp"
#include "IO_Handler.hpp"
#include "Battery.hpp"
#include "WebPage.hpp"


void setup() {
  Serial.begin(115200);
  ledinit();
  loadCellInit();
  batteryInit();
  buttonSetup();
  webSetup();
}

void loop() {

  serverHandler();

  // BAttery Monitoring //
  batteryDisplay();

  // Unite Button Interrupt //
  checkButtonToggle();

  // Motor Running //
  if (checkMotorButtonStatus()) {
    motorRun();
  } else {
    motorStop();
  }

  // Tare Button Reset Functionality //
  if (checkTareButtonStatus()) {
    // calibrateBothLoadCells();
    resetLoadCell();
  }

  // Load cell calibrartion When tare and unit toggle button press 
  if (areBothButtonsPressed()){
    calibrationLedIndication();
    calibrateBothLoadCells();
  }

  // Automatically switch mode every 30 seconds //
  updateMode();

  // Display Tension Values//
  if (!displayMode) {
    showIndividualTensions();
  } else {
    showTensionDifference();
  }
  delay(100);


}