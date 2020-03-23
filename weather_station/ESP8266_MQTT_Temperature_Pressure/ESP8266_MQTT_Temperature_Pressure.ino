#include <Dps310.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//wLAN credentials
//const char* ssid = "idn";
//const char* wifi_password = "MxWpQGQue0$G@0FN";

const char* ssid = "Range_Extender";
const char* wifi_password = "01059047167980913948";

//Creates a Dps310 object
Dps310 Dps310PressureSensor = Dps310();

//MQTT settings
const char* mqtt_server = "192.168.178.62";
const char* mqtt_topic = "temperature";
//const char* mqtt_username = "";
//const char* mqtt_password = "";
const char* clientID = "";

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

  float temperature;
  uint8_t oversampling = 7;
  int16_t ret;
  char TempValue[50];

  Serial.println();
  
  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);
  dtostrf(temperature, 5, 2, TempValue);

  Serial.println(temperature);

  if (client.publish(mqtt_topic, TempValue)) {
      Serial.println("The temperature has been sent");
      Serial.print("TempValue: ");
      Serial.println(TempValue);
    } else {
      Serial.println("The message has failed to send");
    }
  
  // 1e6us = 1s 
//  ESP.deepSleep(30e6);
}

void loop() {
  
}
