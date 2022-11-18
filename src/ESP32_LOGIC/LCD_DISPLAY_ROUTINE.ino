#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

// Define custom bytes for the lcd display
byte leftHeartFull[] = {
  B01100,
  B11110,
  B11111,
  B01111,
  B00111,
  B00011,
  B00001,
  B00000
};

byte leftHeartEmpty[] = {
  B01100,
  B10010,
  B10001,
  B01000,
  B00100,
  B00010,
  B00001,
  B00000
};

byte rightHeartFull[] = {
  B00110,
  B01111,
  B11111,
  B11111,
  B11100,
  B11000,
  B10000,
  B00000
};

byte rightHeartEmpty[] = {
  B00110,
  B01001,
  B10001,
  B00001,
  B00100,
  B01000,
  B10000,
  B00000
};
//Used to handle the animation freq.
unsigned long heart_animation_time = millis();

// Checks if there is heart rate valid data to be displayed
bool hasValidData();
// Displays the display title
void printLcdTitle();
// Displays a placeholder for heart rate values
void printDefault();
// Displays the Heart Rate into the lcd Screen
void printHeartRate();
// Displays a beating heart animation
void printHeartAnimation();


// Medium Priority task defined in ESP32_LOGIC
// Displays the >Heart Rate to the LCD display
void DisplayHeartRate(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  lcd.begin();
  lcd.createChar(0, leftHeartFull);
  lcd.createChar(1, rightHeartFull);
  lcd.createChar(2, leftHeartEmpty);
  lcd.createChar(3, rightHeartEmpty);
  lcd.backlight();

  // Main routine loop
  for(;;)
  {
    lcd.clear();
    printLcdTitle();
    lcd.setCursor(7, 1);
    if(hasValidData())
    {
      printHeartRate();
      printHeartAnimation();
    }
    else {
      printDefault();
    }
    vTaskDelay(500);
  }
}

void printHeartRate()
{
    char buffer[5];
    int localHeartRate;
    xSemaphoreTake(xHeartRateData, TICKS_TO_WAIT_HEART);
    localHeartRate = heartRate;
    xSemaphoreGive(xHeartRateData);
    sprintf(buffer, "%d", localHeartRate);
    lcd.print(buffer);
    
}

bool hasValidData()
{
  return heartRate != -1.0;
}

void printLcdTitle()
{
  lcd.setCursor(3, 0);
  lcd.print("HR Monitor");
}

void printDefault()
{
  char buffer[5];
  sprintf(buffer, "--");
  lcd.print(buffer);
}

void printHeartAnimation()
{
  unsigned long timeSpan = millis() - heart_animation_time;
  if(timeSpan <= 525)
  {
    lcd.setCursor(10, 1);
    lcd.write(0);
    lcd.setCursor(11, 1);
    lcd.write(1);
  }
  else
  {
    lcd.setCursor(10, 1);
    lcd.write(2);
    lcd.setCursor(11, 1);
    lcd.write(3);
    heart_animation_time = millis();
  }
}