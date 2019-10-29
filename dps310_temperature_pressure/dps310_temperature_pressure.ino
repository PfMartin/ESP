#include <Dps310.h>

// Create a DPS310 Object
Dps310 Dps310PressureSensor = Dps310();

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Dps310PressureSensor.begin(Wire);

  Serial.println("Your DPS310 is all setup");
}

void loop() {
  float temperature;
  float pressure;
  uint8_t oversampling = 7;
  int16_t ret;
  Serial.println();

  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);

  if (ret != 0) {
    Serial.print("Fail! ret = ");
    Serial.println(ret);
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees Celsius");
  }

  ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);

  if (ret != 0) {
    Serial.print("Fail! ret = ");
    Serial.println(ret);
  }
  else {
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" Pascal");
  }

  delay(1000);
}
