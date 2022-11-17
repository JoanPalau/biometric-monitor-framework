#include <Arduino_LSM9DS1.h>
#include <Wire.h>
#include <josalhor-project-1_81_inferencing.h>

float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };
float x, y, z;
int i = 0;
const char* bestLabel = NULL;
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal


void requestEvent() {
  Serial.println("requested!");
  char msg[30];
  const char* pred = "NULL";
  if (bestLabel != NULL) {
    pred = bestLabel;
  }
  sprintf(msg, "%5.3f\t%5.3f\t%5.3f\t%s", x, y, z, pred);
  Wire.write(msg);
}



void setup() {
  Serial.begin(9600);
  // while (!Serial);
  Wire.begin(8);  // join i2c bus (address optional for writer)

  if (!IMU.begin()) {
    while (1) {
      Serial.println("Failed to initialize IMU!");
    }
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");
  Wire.onRequest(requestEvent);

  for(i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++){
    buffer[i] = 0;
  }
}

void loop() {

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
  }

  if (i >= EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE){
    for(int j = 3; j < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; j++){
      buffer[j - 3] = buffer[j];
    }
    i -= 3;
  }

  buffer[i] = x;
  buffer[i + 1] = y;
  buffer[i + 2] = z;
  i += 3;

  signal_t signal;
  int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  if (err != 0) {
      ei_printf("Failed to create signal from buffer (%d)\n", err);
      return;
  }

  // Run the classifier
  ei_impulse_result_t result = { 0 };

  err = run_classifier(&signal, &result, debug_nn);
  if (err != EI_IMPULSE_OK) {
      ei_printf("ERR: Failed to run classifier (%d)\n", err);
      return;
  }

  // print the predictions
  ei_printf("Predictions ");
  ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
      result.timing.dsp, result.timing.classification, result.timing.anomaly);
  ei_printf(": \n");
  float bestValue = -1;
  int bestI = 0;
  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    if (bestValue < result.classification[ix].value){
      bestI = ix;
      bestValue = result.classification[ix].value;
    }
  }
  bestLabel = result.classification[bestI].label;
  ei_printf("%s: %.5f\n", result.classification[bestI].label, result.classification[bestI].value);

  delay(100);
}