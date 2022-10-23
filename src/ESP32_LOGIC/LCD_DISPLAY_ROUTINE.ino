#include <LCD_I2C.h>
//#include <stdio.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

// Displays the Heart Rate into the lcd Screen
void printHeartRate();

// LOW Priority task defined in ESP32_LOGIC
// Displays the >Heart Rate to the LCD display
void DisplayHeartRate(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  lcd.begin();
  lcd.backlight();

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
    sprintf(buffer, "%d", heartRate);
    lcd.print(buffer);
    xSemaphoreGive(xHeartRateData);
    vTaskDelay(500);
}