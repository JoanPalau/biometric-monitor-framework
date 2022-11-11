// Medium Priority task defined in ESP32_LOGIC
// Computes the Health Risk Status of teh user based on the received information
void DetermineRiskStatus(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  // Main routine loop
  for(;;)
  {
    vTaskDelay(10000);
  }
}