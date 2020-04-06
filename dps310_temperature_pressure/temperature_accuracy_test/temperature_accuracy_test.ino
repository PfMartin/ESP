#include <Dps310.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Dps310 Dps310PressureSensor = Dps310();

void setup() {
  Serial.begin(115200);

  Serial.println("Connecting the Sensor");
  Dps310PressureSensor.begin(Wire);
}

void loop() {
  float temperature;
  uint8_t oversampling = 1;
  int16_t ret;

  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);
  
  Serial.println(temperature);

  delay(1000);
}
