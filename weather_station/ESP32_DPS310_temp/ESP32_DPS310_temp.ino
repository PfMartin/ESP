#include <Dps310.h>

// Dps310 Opject
Dps310 Dps310PressureSensor = Dps310();

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Dps310PressureSensor.begin(Wire);
  Serial.println("Init complete!");
}

void loop() {
  float temperature;
  uint8_t oversampling = 7;
  int16_t ret;
  Serial.println();
  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);
  
  if (ret != 0) {
    //Something went wrong.
    //Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" degrees of Celsius");
  }

  //Wait some time
  delay(1000);
}
