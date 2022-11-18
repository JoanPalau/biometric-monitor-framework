// Medium Priority task defined in ESP32_LOGIC
// Computes the Health Risk Status of teh user based on the received information

using namespace Eloquent::ML::Port;

int getIndexMov(const char* res){
  if(strcmp(res, "rest") == 0) {
    return 1;
  }
  if(strcmp(res, "running") == 0) {
    return 2;
  }if(strcmp(res, "walking") == 0) {
    return 3;
  }
  return 0; // null
}

int getIndexUnexpected(const char* res){
  if(strcmp(res, "erratic") == 0) {
    return 1;
  }
  if(strcmp(res, "falling") == 0) {
    return 2;
  }
  return 0; // null
}

riskMonitorStatus getRiskStatusfromIndex(int index) {
  if (index == 1) {
    return RLOW;
  }
  if (index == 1) {
    return RMEDIUM;
  }
  if (index == 1) {
    return RHIGH;
  }
  return RUNCERTAIN;
}

void updateRisk(){
  char res[ACCELEROMETER_RESULT_SIZE];
  xSemaphoreTake(xAccelerometerData, TICKS_TO_WAIT_HEART);
  strcpy(res, accelerometerResult);
  xSemaphoreGive(xAccelerometerData);
  xSemaphoreTake(xHeartRateData, TICKS_TO_WAIT_HEART);
  float bpm = (float) heartRate;
  xSemaphoreGive(xHeartRateData);

  float dataPrediction[4];
  int indexMov = getIndexMov(res);
  int indexUnexpected = getIndexUnexpected(res);
  float bpmGrowth = 0;

  dataPrediction[0] = (float) indexMov;
  dataPrediction[1] = (float) indexMov;
  dataPrediction[2] = (float) bpm;
  dataPrediction[3] = (float) bpmGrowth;
  DecisionTree decissionTree;
  int resultIndex = decissionTree.predict(dataPrediction);

  xSemaphoreTake(xRiskStatusData, TICKS_TO_WAIT_RISK);
  status = getRiskStatusfromIndex(resultIndex);
  xSemaphoreGive(xRiskStatusData);
}

void DetermineRiskStatus(void *pvParameters)
{
  (void) pvParameters;
  // Main routine loop
  for(;;)
  {
    updateRisk();
    vTaskDelay(1000);
  }
}