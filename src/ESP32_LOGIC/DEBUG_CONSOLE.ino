// LOW Priority task defined in ESP32_LOGIC
// Displays the Debug information through the Serial port
void DisplayDebugInformation(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  // Main routine loop
  for(;;)
  {
    vTaskDelay(10000);
  }
}