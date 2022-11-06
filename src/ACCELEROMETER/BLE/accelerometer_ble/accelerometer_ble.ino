#include <Arduino_LSM9DS1.h>
#include <Wire.h>

float x, y, z;

void requestEvent() {
  //Serial.println("requested!");
  char msg[18];
  sprintf(msg, "%5.3f\t%5.3f\t%5.3f", x, y, z);
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
  delay(100);
}