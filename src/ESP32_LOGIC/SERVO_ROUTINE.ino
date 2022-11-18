#include <ESP32Servo.h>

#define UNCERTAIN_DEGREES 180
#define LOW_DEGREES 0
#define MEDIUM_DEGREES 60
#define HIGH_DEGREES 120

int statusToDegrees(int riskStatus);

// Medium Priority task defined in ESP32_LOGIC
// Displays the Health Status activating a Servo
void DisplayHealthStatus(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  Servo riskMonitor;

  
  riskMonitor.setPeriodHertz(50);    // standard 50 hz servo
	riskMonitor.attach(12, 500, 2400);
  riskMonitor.write(UNCERTAIN_DEGREES);

  // Main routine loop
  for(;;)
  {
    if(status == RUNCERTAIN) {
        riskMonitor.write(statusToDegrees(status));
        status = RLOW;
    } else {
      riskMonitor.write(30);
      status = RUNCERTAIN;
    }
    
    
    vTaskDelay(10000);
  }
}

int statusToDegrees(int riskStatus)
{
  switch(riskStatus)
  {
    case RUNCERTAIN:
      return UNCERTAIN_DEGREES;
      break;
    case RLOW:
      return LOW_DEGREES;
      break;
    case RMEDIUM:
      return MEDIUM_DEGREES;
      break;
    case RHIGH:
      return HIGH_DEGREES;
      break;
    default:
      return UNCERTAIN_DEGREES;
  }
}