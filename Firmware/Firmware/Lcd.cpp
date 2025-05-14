#include "Lcd.hpp"
#include <string.h>

UBYTE *BlackImage;
// UWORD ImageSize;

volatile bool displayMode = false;               // false: show both values, true: show difference
unsigned long lastModeSwitch = 0;                // track last switch time
const unsigned long modeSwitchInterval = 30000;  // 30 seconds

void ledinit() {
  System_Init();
  OLED_2IN42_Init();
  Driver_Delay_ms(500);
  OLED_2IN42_Clear();
  createImage();
  Paint_NewImage(BlackImage, OLED_2IN42_WIDTH, OLED_2IN42_HEIGHT, 270, BLACK);
  Serial.print("Paint_NewImage\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);
  Paint_DrawString_EN(30, 30, "Initialization...", &Font8, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
  delay(500);
  displayClear();
}

void createImage() {

  UWORD ImageSize = ((OLED_2IN42_WIDTH % 8 == 0) ? (OLED_2IN42_WIDTH / 8) : (OLED_2IN42_WIDTH / 8 + 1)) * OLED_2IN42_HEIGHT;
  BlackImage = (UBYTE *)malloc(ImageSize);
  if (BlackImage == NULL) {
    Serial.println("Failed to allocate memory for image");
  }
}

void displayText(int x, int y, const char *text) {
  Paint_DrawString_EN(x, y, text, &Font12, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
}

void displayValue_gF(int x, int y, int value) {
  char buffer[16];
  sprintf(buffer, "%4d", value);  // // 4-digit width to overwrite previous text
  Paint_DrawString_EN(x, y, buffer, &Font12, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
}

void displayValue_mF(int x, int y, int value) {
  char buffer[16];
  sprintf(buffer, "%4d", value);  // // 4-digit width to overwrite previous text
  Paint_DrawString_EN(x, y, buffer, &Font12, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
}

void displayBattValue(int x, int y, int value) {
  char buffer[16];
  sprintf(buffer, "%3d", value);  // // 4-digit width to overwrite previous text
  Paint_DrawString_EN(x, y, buffer, &Font12, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
  Paint_DrawString_EN(x + strlen(buffer) * Font12.Width, y, "%", &Font12, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
}

void displayClear() {
  Paint_Clear(BLACK);
}

void updateMode() {
  if (millis() - lastModeSwitch >= modeSwitchInterval) {
    displayMode = !displayMode;
    lastModeSwitch = millis();
    displayClear();  // optional: clear LCD when switching mode
  }
}

void showIndividualTensions() {
  int loadCellValue_1 = loadCell_1();
  int loadCellValue_2 = loadCell_2();

  if (runFunctionOne) {
    loadCellValue_1 = round(loadCellValue_1 * 9.81);
    loadCellValue_2 = round(loadCellValue_2 * 9.81);
    displayText(50, 52, "(mF)");
    displayText(5, 20, "Tension 1 : ");
    displayText(5, 40, "Tension 2 : ");
    displayValue_mF(85, 20, loadCellValue_1);
    displayValue_mF(85, 40, loadCellValue_2);
    ledIndicationFor_mF();
  } else {
    displayText(50, 52, "(gF)");
    displayText(5, 20, "Tension 1 : ");
    displayText(5, 40, "Tension 2 : ");
    displayValue_gF(85, 20, loadCellValue_1);
    displayValue_gF(85, 40, loadCellValue_2);
    ledIndicationFor_gF();
  }
}

void showTensionDifference() {
  int loadCellValue_1 = loadCell_1();
  int loadCellValue_2 = loadCell_2();
  int diff = abs(loadCellValue_1 - loadCellValue_2);

  if (runFunctionOne) {
    diff = round(diff * 9.81);
    displayText(50, 52, "(mF)");
    displayText(5, 30, "Tension Diff:");
    displayValue_mF(100, 30, diff);
    ledIndicationFor_mF();
  } else {
    displayText(50, 52, "(gF)");
    displayText(5, 30, "Tension Diff:");
    displayValue_gF(100, 30, diff);
    ledIndicationFor_gF();
  }
}
