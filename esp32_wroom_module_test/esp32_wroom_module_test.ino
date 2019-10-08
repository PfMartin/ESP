#include "WiFi.h"

int counter = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  counter++;
  
  Serial.println(counter);
  delay(200);
}
