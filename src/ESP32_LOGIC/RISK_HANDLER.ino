
// Medium Priority task defined in ESP32_LOGIC
// Computes the Health Risk Status of teh user based on the received information

using namespace Eloquent::ML::Port;

#define QUEUE_SIZE_MONITOR 15
#define QUEUE_SIZE_BPM 10


class QueueMonitorStatus {
  int index = 0;
  int numberItems = 0;
  activityMonitorStatus content[QUEUE_SIZE_MONITOR];

  public:

  QueueMonitorStatus() {
    this->index = 0;
    this->numberItems = 0;
  }

  void addItem(activityMonitorStatus value) {
    content[index] = value;
    index++;
    if (index > numberItems) {
      numberItems = index;
    }
    index = index % QUEUE_SIZE_MONITOR;

  }

  activityMonitorStatus mostCommon() {
    int counter[NUMBER_STATUS_ACITIVTY_MONITOR];
    for(int i = 0; i < NUMBER_STATUS_ACITIVTY_MONITOR; i++) {
      counter[i] = 0;
    }
    int maxVal = 0;
    activityMonitorStatus mostCommonValue = SREST;
    for(int i = 0; i < numberItems; i++) {
      activityMonitorStatus status = content[i];
      counter[status] += 1;
      if (counter[status] > maxVal) {
        mostCommonValue = status;
        maxVal = counter[status];
      }
    }

    return mostCommonValue;
  }
};

class QueueRiskMonitor {
  int index = 0;
  int numberItems = 0;
  riskMonitorStatus content[QUEUE_SIZE_MONITOR];

  public:

  QueueRiskMonitor() {
    this->index = 0;
    this->numberItems = 0;
  }

  void addItem(riskMonitorStatus value) {
    content[index] = value;
    index++;
    if (index > numberItems) {
      numberItems = index;
    }
    index = index % QUEUE_SIZE_MONITOR;

  }

  riskMonitorStatus mostCommon() {
    int counter[NUMBER_RISK_MONITOR_STATUS];
    for(int i = 0; i < NUMBER_RISK_MONITOR_STATUS; i++) {
      counter[i] = 0;
    }
    int maxVal = 0;
    riskMonitorStatus mostCommonValue = RUNCERTAIN;
    for(int i = 0; i < numberItems; i++) {
      riskMonitorStatus status = content[i];
      counter[status] += 1;
      if (counter[status] > maxVal) {
        mostCommonValue = status;
        maxVal = counter[status];
      }
    }

    return mostCommonValue;
  }
};

class QueueBPM {
  int start = 0;
  int end = 0;
  int numberItems = 0;
  float content[QUEUE_SIZE_BPM];

  public:

  QueueBPM() {
    this->start = 0;
    this->end = 0;
    this->numberItems = 0;
  }

  void addItem(float value) {
    content[end] = value;
    end++;
    if (numberItems < QUEUE_SIZE_BPM) {
      numberItems++;
    }
    end = end % QUEUE_SIZE_BPM;
    if (end == start) {
      start = (start + 1) % QUEUE_SIZE_BPM;
    }
  }

  float growthRate() {
     if (numberItems < 2) {
      // Cannot calculate the growth rate with less than 2 elements in the array
      return 0;
    }

    float growthRate = 0;
    int lastIndex = (end - 1);
    if (end == 0) {
      lastIndex = QUEUE_SIZE_BPM - 1;
    }
    for (int i = start; i != lastIndex; i = (i + 1) % QUEUE_SIZE_BPM) {
      int nextIndex = (i + 1) % QUEUE_SIZE_BPM;
      growthRate += (content[nextIndex] - content[i]);
    }
    return growthRate / (numberItems - 1);
  }
};

QueueBPM queueBPM;
QueueMonitorStatus queueMonitorStatus;
QueueRiskMonitor queueRiskMonitor;


int getIndexMov(activityMonitorStatus res){
  if(res == SREST) {
    return 1;
  }
  if(res == SRUNNING) {
    return 2;
  }if(res == SWALKING) {
    return 3;
  }
  return 0; // null
}

int getIndexUnexpected(activityMonitorStatus res){
  if(res == SERRATIC) {
    return 1;
  }
  if(res == SFALLING) {
    return 2;
  }
  return 0; // null
}

riskMonitorStatus getRiskStatusfromIndex(int index) {
  if (index == 1) {
    return RLOW;
  }
  if (index == 2) {
    return RMEDIUM;
  }
  if (index == 3) {
    return RHIGH;
  }
  return RUNCERTAIN;
}

void updateRisk(){
  if (!wifiConnected) {
    return;
  }
  activityMonitorStatus latestStatus;
  xSemaphoreTake(xAccelerometerData, TICKS_TO_WAIT_HEART);
  latestStatus = accelerometerResult;
  xSemaphoreGive(xAccelerometerData);
  xSemaphoreTake(xHeartRateData, TICKS_TO_WAIT_HEART);
  float bpm = (float) heartRate;
  xSemaphoreGive(xHeartRateData);
  
  queueBPM.addItem(bpm);
  queueMonitorStatus.addItem(latestStatus);
  activityMonitorStatus commonMonitor = queueMonitorStatus.mostCommon();
  
  // activityMonitorStatus commonMonitor = latestStatus;

  float dataPrediction[4];
  int indexMov = getIndexMov(commonMonitor);
  int indexUnexpected = getIndexUnexpected(commonMonitor);
  float bpmGrowth = queueBPM.growthRate();
  // float bpmGrowth = 0;

  dataPrediction[0] = (float) indexMov;
  dataPrediction[1] = (float) indexUnexpected;
  dataPrediction[2] = (float) bpm;
  dataPrediction[3] = (float) bpmGrowth;
  DecisionTree decissionTree;
  int resultIndex = decissionTree.predict(dataPrediction);
  riskMonitorStatus resultStatus = getRiskStatusfromIndex(resultIndex);
  
  queueRiskMonitor.addItem(resultStatus);
  riskMonitorStatus commonResultStatus = queueRiskMonitor.mostCommon();
  
  //riskMonitorStatus commonResultStatus = resultStatus;

  xSemaphoreTake(xRiskStatusData, TICKS_TO_WAIT_RISK);
  status = commonResultStatus;
  xSemaphoreGive(xRiskStatusData);

  xSemaphoreTake(xSerialPort, TICKS_TO_WAIT_SERIAL);
  Serial.println("Data");
  Serial.println(commonMonitor);
  Serial.println(bpm);
  Serial.println(bpmGrowth);
  Serial.print("Current: ");
  Serial.print(resultStatus);
  Serial.print(" Common: ");
  Serial.println(commonResultStatus);
  Serial.print("Acc Result: ");
  Serial.println(accelerometerResult);
  Serial.println();
  xSemaphoreGive(xSerialPort);
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