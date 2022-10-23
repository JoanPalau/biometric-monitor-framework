// LOW Priority task defined in ESP32_LOGIC
// Displays the Health Status activating a Servo
void DisplayHealthStatus(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  // Main routine loop
  for(;;)
  {
    vTaskDelay(10000);
  }
}