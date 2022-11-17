#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute = 0;
int beatAvg;
long foundDevice = 0;
long lastIrValue = 0;

// Update these with values suitable for your network.

const char* ssid = "JMGS20FE";
const char* password = "pwsf9034";
const char* mqtt_server = "192.168.45.84";

#define TOPIC_HEART_RATE "sensor/heart"
#define TOPIC_DEFAULT "-1.0"

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), TOPIC_HEART_RATE, 0, 1, TOPIC_DEFAULT)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(TOPIC_HEART_RATE, TOPIC_DEFAULT);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
}

void setupheart() {
  // Initialize sensor
  //if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  Wire.begin(0, 2);
  if (!particleSensor.begin()) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
  } else {
    foundDevice = 1;
     
    Serial.println("Place your index finger on the sensor with steady pressure.");

    particleSensor.setup(); //Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  }
}

void cleanUpData(){
  for (byte x = 0 ; x < RATE_SIZE ; x++) {
    rates[x] = 0;
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  cleanUpData();
  setupheart();
}

void updateBPM() {
  if (foundDevice == 1) {    
    lastIrValue = particleSensor.getIR();
    if (checkForBeat(lastIrValue) == true)
    {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }
  }
}

void reportMQTT() {
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    float report = -1.0;
    if (
      foundDevice == 1 && lastIrValue > 50000 && beatAvg > 30
    ) {
      report = beatAvg;
    } else if (foundDevice == 1 && lastIrValue < 50000) {
      cleanUpData();
    }
    snprintf (msg, MSG_BUFFER_SIZE, "%f",  (float) report);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(TOPIC_HEART_RATE, msg);
  }
}

void loop() {
  updateBPM();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  reportMQTT();
}
