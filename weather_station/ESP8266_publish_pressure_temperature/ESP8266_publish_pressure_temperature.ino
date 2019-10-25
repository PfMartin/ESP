#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <Dps310.h>

//WiFi
const char* ssid = "idn";
const char* wifi_password = "MxWpQGQue0$G@0FN";

//MQTT
const char* mqtt_server = "10.120.128.52";
const char* mqtt_topic = "DPS310";
const char* mqtt_username = "Martin";
const char* mqtt_password = "Infineon";
const char* clientID = "ESP266 D1 mini";

//Initialize the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

//Initialize the Dps310 object
Dps310 Dps310PressureSensor = Dps310();

void setup() {
  Serial.begin(115200);

  Dps310PressureSensor.begin(Wire);
  Serial.print("DPS310 initialized");

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  } 
}

void loop() {
  float temperature;
  float pressure;
  uint8_t oversampling = 7;
  int16_t ret;
  char temperatureValue[15]; //Character array for the temperature
  char pressureValue[15]; //Character array for the pressure 

  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);

  // Convert float temperature into character array
  // client.publish can't send float, it can only send char[]
  dtostrf(temperature, 11, 4, temperatureValue);

  ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);

  // Convert float pressure into character array
  // client.publish can't send float, it can only send char[]
  dtostrf(pressure, 11, 4, pressureValue);  
  
  //client.publish returns a boolean whether the payload was sent or not
  //If it was sent successfully print the line
  if (client.publish(mqtt_topic, temperatureValue)) {
    Serial.println("Temperature value sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Temperature value failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_topic, temperatureValue);
  }

  if (client.publish(mqtt_topic, pressureValue)) {
    Serial.println("Pressure value sent!");
    delay(500);
  }
  else {
    Serial.println("Pressure value failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10);
    client.publish(mqtt_topic, pressureValue);
  }
}
