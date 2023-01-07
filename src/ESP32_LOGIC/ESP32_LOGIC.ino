#define WIFI_MSG_BUFFER_SIZE (50)
#define PRIORITY_CORE 0
#define SERIAL_BAUD_RATE 115200
#define TICKS_TO_WAIT_SERIAL 150
#define TICKS_TO_WAIT_HEART 500
#define TICKS_TO_WAIT_RISK 500

#define NO_DATA_INPUT_FLOAT -1.0
#define NO_DATA_INPUT_INT -1

// Controls access to the Heart Rate data variable
SemaphoreHandle_t xHeartRateData;
int heartRate = NO_DATA_INPUT_INT; // Initial value when no data is feeded

SemaphoreHandle_t xAccelerometerData;
float accelerometerX = NO_DATA_INPUT_FLOAT; // Initial values when no data is feeded
float accelerometerY = NO_DATA_INPUT_FLOAT; 
float accelerometerZ = NO_DATA_INPUT_FLOAT; 
#define ACCELEROMETER_RESULT_SIZE 10

SemaphoreHandle_t xRiskStatusData;
enum riskMonitorStatus {
  RUNCERTAIN = 0,
  RLOW = 1,
  RMEDIUM = 2,
  RHIGH = 3
};
#define NUMBER_RISK_MONITOR_STATUS 4
riskMonitorStatus status = RUNCERTAIN;

enum activityMonitorStatus {
  SREST = 0,
  SWALKING = 1,
  SRUNNING = 2,
  SFALLING = 3,
  SERRATIC = 4
};
#define NUMBER_STATUS_ACITIVTY_MONITOR 5
activityMonitorStatus accelerometerResult;

float data = NO_DATA_INPUT_FLOAT;

// Controls access to the Serial Port to display data
SemaphoreHandle_t xSerialPort;

void initializeGlobalVariables()
{
  xHeartRateData = xSemaphoreCreateBinary();
  xSerialPort = xSemaphoreCreateBinary();
  xAccelerometerData = xSemaphoreCreateBinary();
  xRiskStatusData = xSemaphoreCreateBinary();
  // free the "mutex" to allow tasks to start using it
  xSemaphoreGive(xHeartRateData);
  xSemaphoreGive(xSerialPort);
  xSemaphoreGive(xAccelerometerData);
  xSemaphoreGive(xRiskStatusData);
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
      4096,
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
