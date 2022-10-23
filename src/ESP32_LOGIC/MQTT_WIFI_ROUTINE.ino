#include <WiFi.h>
#include <PubSubClient.h>

// Serial port displays to show status of the connection process
void displayConnectingWifiMessage();
void displayStartConnectingWiFiMessage();
void displayConnectedWiFiMessage();

// Serial port display to show the data received
void displayReceivedWifiData(char* topic, byte* payload, unsigned int length);

void wifi_setup();
void wifi_start();


const char* ssid = "JMGS20FE";
const char* password = "pwsf9034";
const char* mqtt_server = "192.168.106.84";

const char* clientID ="ESP32";
const char* clientUserName="ESP32";
const char* clientPassword="x";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[WIFI_MSG_BUFFER_SIZE];
int value = 0;


// HIGH Priority task defined in ESP32_LOGIC
// Obtains data from the MQTT server
void ObtainData(void *pvParameters)
{
  // Initialize the local variables here
  (void) pvParameters;
  wifi_start();
  // Main routine loop
  for(;;)
  {
    client.loop();
    vTaskDelay(10);
  }
}

void wifi_setup()
{
  vTaskDelay(10);
  // We start by connecting to a WiFi network
  displayStartConnectingWiFiMessage();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    displayConnectingWifiMessage();
    vTaskDelay(500);
  }

  //randomSeed(micros()); Is it really needed? It seems to work fine like this

  displayConnectedWiFiMessage();
}


void wifi_start()
{
    wifi_setup();
    client.setServer(mqtt_server, 1883);
    client.setCallback(displayReceivedWifiData);
    //client.connect(clientID,clientUserName,clientPassword);
    client.connect(clientID);
    client.subscribe("test/topic");
}

void displayConnectingWifiMessage()
{
  xSemaphoreTake(xSerialPort, TICKS_TO_WAIT_SERIAL);
  Serial.print(".");
  xSemaphoreGive(xSerialPort);
}

void displayStartConnectingWiFiMessage()
{
  xSemaphoreTake(xSerialPort, TICKS_TO_WAIT_SERIAL);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  xSemaphoreGive(xSerialPort);
}

void displayConnectedWiFiMessage()
{
  xSemaphoreTake(xSerialPort, TICKS_TO_WAIT_SERIAL);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  xSemaphoreGive(xSerialPort);
}

void displayReceivedWifiData(char* topic, byte* payload, unsigned int length)
{
  xSemaphoreTake(xHeartRateData, TICKS_TO_WAIT_HEART);
  heartRate = atoi((const char*)payload);
  xSemaphoreGive(xHeartRateData);

  xSemaphoreTake(xSerialPort, TICKS_TO_WAIT_SERIAL);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  xSemaphoreGive(xSerialPort);
}
