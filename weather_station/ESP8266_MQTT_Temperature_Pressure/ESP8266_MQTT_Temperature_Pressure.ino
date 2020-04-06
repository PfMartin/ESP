#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTPIN 5
#define DHTTYPE DHT11

//wLAN credentials
//const char* ssid = "idn";
//const char* wifi_password = "MxWpQGQue0$G@0FN";

const char* ssid = "Range_Extender";
const char* wifi_password = "01059047167980913948";
//Creates a Dps310 object
DHT dht(DHTPIN, DHTTYPE);

//MQTT settings
const char* mqtt_server = "192.168.178.62";
const char* temp_topic = "temperature";
const char* hum_topic = "humidity";
//const char* mqtt_username = "";
//const char* mqtt_password = "";
const char* clientID = "D1 Mini";

//Initiate the wLAN and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient);

void setup() {
  Serial.begin(115200);

  Serial.println("Initializing DHT11");
  dht.begin();

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

  unsigned long t;
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  char TempValue[50];
  char HumValue[50];
  
  Serial.println();
  
  
  dtostrf(temp, 5, 2, TempValue);
  dtostrf(hum, 5, 2, HumValue);

  Serial.println(TempValue);
  Serial.println(HumValue);

  if (client.publish(temp_topic, TempValue)) {
      Serial.println("The temperature value has been sent");
      Serial.print("Time: ");
      t = millis();
      Serial.println(t);
      Serial.print("TempValue: ");
      Serial.println(TempValue);
    } else {
      Serial.println("The message has failed to send");
    }

  delay(500);
  
  if (client.publish(hum_topic, HumValue)){
    Serial.println("The humidity value has been sent");
    Serial.print("Time: ");
    t = millis();
    Serial.println(t);
    Serial.print("HumValue: ");
    Serial.println(HumValue);
  } else {
    Serial.println("The message has failed to send");
  }
  
  delay(1000);
  
  // 1e6us = 1s 
  ESP.deepSleep(30e6);
//
//  // 10 min
//  ESP.deepSleep(6e8);
//  // 30 min
//  // ESP.deepSleep(1.8e9);
}

void loop() {
  
}
