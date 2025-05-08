#include "Lcd.hpp"
#include <string.h>

UBYTE *BlackImage;
// UWORD ImageSize;

void ledinit(){
  System_Init();
  OLED_2IN42_Init();
  Driver_Delay_ms(500); 
  OLED_2IN42_Clear();
  
  createImage();

  Paint_NewImage(BlackImage, OLED_2IN42_WIDTH, OLED_2IN42_HEIGHT, 270, BLACK);
  Serial.print("Paint_NewImage\r\n");
  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);

  Paint_DrawString_EN(30, 20, "Setup", &Font12, BLACK, RED);
  OLED_2IN42_Display(BlackImage);
  Paint_DrawString_EN(30, 30, "Init...", &Font12, BLACK, RED);
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

void displayText(int x, int y, const char* text) {
    Paint_DrawString_EN(x, y, text, &Font12, BLACK, RED);
    OLED_2IN42_Display(BlackImage);
   
}

void displayValue(int x, int y, int value) {
    char buffer[16];
    sprintf(buffer, "%4d", value); // // 4-digit width to overwrite previous text
    Paint_DrawString_EN(x, y, buffer, &Font12, BLACK, RED);
    OLED_2IN42_Display(BlackImage);
    Paint_DrawString_EN(x + strlen(buffer) * Font12.Width , y,"-N", &Font12, BLACK, RED);
    OLED_2IN42_Display(BlackImage);
}

void displayBattValue(int x, int y, int value) {
    char buffer[16];
    sprintf(buffer, "%3d", value); // // 4-digit width to overwrite previous text
    Paint_DrawString_EN(x, y, buffer, &Font12, BLACK, RED);
    OLED_2IN42_Display(BlackImage);
    Paint_DrawString_EN(x + strlen(buffer) * Font12.Width , y,"%", &Font12, BLACK, RED);
    OLED_2IN42_Display(BlackImage);
}

void displayClear()
{
    Paint_Clear(BLACK);
}