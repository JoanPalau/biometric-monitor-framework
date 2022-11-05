#include <Wire.h>


void setup() {
    Serial.begin(9600);
    while (!Serial);
    Wire.begin(); // join i2c bus (address optional for writer)

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }

    Serial.print("Accelerometer sample rate = ");
    Serial.print(IMU.accelerationSampleRate());
    Serial.println(" Hz");
    Serial.println();
    Serial.println("Acceleration in g's");
    Serial.println("X\tY\tZ");
}


void loop() {
    Wire.beginTransmission(8); // transmit to device #8
    Wire.print("TEST");        // sends the given value
    Wire.endTransmission();    // stop transmitting

    float x, y, z;

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