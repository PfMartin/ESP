void setup() {
  Serial.begin(115200);
  Serial.println("Start up the ESP32");
  Serial.println("The ESP32 works fine");
}

void loop() {
  int counter = 0;
  counter += 1;
  Serial.println(counter);
}
