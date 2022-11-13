#include <LCD_I2C.h>
//#include <stdio.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

byte leftHeart[] = {
  B01100,
  B11110,
  B11111,
  B01111,
  B00111,
  B00011,
  B00001,
  B00000
};

byte rightHeart[] = {
  B00110,
  B01111,
  B11111,
  B11111,
  B11100,
  B11000,
  B10000,
  B00000
};

// Displays the Heart Rate into the lcd Screen
void printHeartRate();

// Medium Priority task defined in ESP32_LOGIC
// Displays the >Heart Rate to the LCD display
void DisplayHeartRate(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  lcd.begin();
  lcd.backlight();

  lcd.createChar(0, leftHeart);
  lcd.createChar(1, rightHeart);

  // Main routine loop
  for(;;)
  {
    lcd.clear();
    printHeartRate();
    vTaskDelay(500);
  }
}

void printHeartRate()
{
    char buffer[5];
    xSemaphoreTake(xHeartRateData, TICKS_TO_WAIT_HEART);
    lcd.setCursor(3, 0);
    lcd.print("HR Monitor");
    lcd.setCursor(7, 1);
    if(heartRate != -1.0){
      sprintf(buffer, "%d", heartRate);
      lcd.print(buffer);
      lcd.setCursor(10, 1);
      lcd.write(0);
      lcd.setCursor(11, 1);
      lcd.write(1);
    } else {
      sprintf(buffer, "--");
      lcd.print(buffer);
    }
    
    
    xSemaphoreGive(xHeartRateData);
    vTaskDelay(500);
}