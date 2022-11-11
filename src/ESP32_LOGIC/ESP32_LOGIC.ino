#define WIFI_MSG_BUFFER_SIZE (50)
#define PRIORITY_CORE 0
#define SERIAL_BAUD_RATE 115200
#define TICKS_TO_WAIT_SERIAL 150
#define TICKS_TO_WAIT_HEART 500

// Controls access to the Heart Rate data variable
SemaphoreHandle_t xHeartRateData;
int heartRate = -1; // TODO: remove this when real data available

// Controls access to the Serial Port to display data
SemaphoreHandle_t xSerialPort;

void initializeGlobalVariables()
{
  xHeartRateData = xSemaphoreCreateBinary();
  xSerialPort = xSemaphoreCreateBinary();
  // free the "mutex" to allow tasks to start using it
  xSemaphoreGive(xHeartRateData);
  xSemaphoreGive(xSerialPort);
}

void initializeLowPriorityTasks()
{

  xTaskCreatePinnedToCore(
    DisplayDebugInformation,
    "Display Debug Information through Serial Port",
    2048,
    NULL,
    1,
    NULL,
    0
  );
}

void initializeMediumPriorityTasks()
{
  xTaskCreatePinnedToCore(
    DetermineRiskStatus,
    "Compute the risk status of the user",
    2048,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    DisplayHeartRate,
    "Display Heart Rate (HR)",
    2048,
    NULL,
    1,
    NULL,
    0
  );

  xTaskCreatePinnedToCore(
    DisplayHealthStatus,
    "Display Health Status",
    4096,
    NULL,
    1,
    NULL,
    0
  );
}

void initializeHighPriorityTasks()
{
  xTaskCreatePinnedToCore(
      ObtainData,
      "Obtain data from the MQTT server",
      2048,
      NULL,
      1,
      NULL,
      1       // We execute this task in a separate core
    );
}

void setupTasks(){
  initializeHighPriorityTasks();
  initializeMediumPriorityTasks();
  initializeLowPriorityTasks();
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  // Here we define the tasks/routines that will be implemented
  initializeGlobalVariables();
  setupTasks();
  
}

// Ignore main loop as we are using FreeRTOS
void loop() {}
