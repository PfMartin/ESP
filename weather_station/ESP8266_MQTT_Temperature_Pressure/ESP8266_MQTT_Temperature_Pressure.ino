#include <Dps310.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//wLAN credentials
//const char* ssid = "idn";
//const char* wifi_password = "MxWpQGQue0$G@0FN";

const char* ssid = "FRITZ!Box 7490";
const char* wifi_password = "01059047167980913948";

//Creates a Dps310 object
Dps310 Dps310PressureSensor = Dps310();

//MQTT settings
const char* mqtt_server = "192.168.178.62";
const char* mqtt_topic = "weather_stats";
//const char* mqtt_username = "";
//const char* mqtt_password = "";
const char* clientID = "weather_station";

//Initiate the wLAN and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

void setup() {
  Serial.begin(115200);

  Dps310PressureSensor.begin(Wire);

  Serial.print("\n Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  } else {
    Serial.println("Connection to MQTT Broker failed...");
  }  
}

void loop() {
  float pressure;
  float temperature;
  uint8_t oversampling = 7;
  int16_t ret;
  char PressureValue[15];
  char TempValue[15];

  Serial.println();

  ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);

  dtostrf(pressure, 8, 2, PressureValue);

  if (ret != 0) {
    Serial.print("Fail! ret = ");
    Serial.print(ret);
  } else if (client.publish(mqtt_topic, PressureValue)) {
    Serial.println(PressureValue);
    Serial.println(" Pascal");
  } else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID);
    delay(10);
    client.publish(mqtt_topic, PressureValue);
  }

  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);

  dtostrf(temperature, 8, 2, TempValue);

  if (ret != 0) {
    Serial.print("Fail! ret = ");
    Serial.print(ret);
  } else if (client.publish(mqtt_topic, TempValue)) {
    Serial.println(TempValue);
    Serial.println(" degree Celsius");
  } else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID);
    delay(10);
    client.publish(mqtt_topic, TempValue);
  }  

  delay(1000);
  
}
