#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>

// Update these with values suitable for your network.

const char* ssid = "JMGS20FE";
const char* password = "pwsf9034";
const char* mqtt_server = "192.168.45.84";

#define TOPIC_ACCELEROMETER "sensor/accelerometer"
#define TOPIC_DEFAULT "-1.0"
#define MSG_LNG 30

WiFiClient espClient;
PubSubClient client(espClient);


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
    if (client.connect(clientId.c_str(), TOPIC_ACCELEROMETER, 0, 1, TOPIC_DEFAULT)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(TOPIC_ACCELEROMETER, TOPIC_DEFAULT);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
}

void reportMQTT(const char* msg) {
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(TOPIC_ACCELEROMETER, msg);
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  Wire.begin(0, 2);
}


void loop() {
    char msg[MSG_LNG];
    Wire.requestFrom(8, MSG_LNG);
    int i = 0;
    while (Wire.available()) { // peripheral may send less than requested
        char c = Wire.read(); // receive a byte as character
        msg[i] = c;
        i++;
  }
  msg[i] = '\0';
  reportMQTT(msg);


  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(150);
}
