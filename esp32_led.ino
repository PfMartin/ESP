const int led1 = 16;
const int led2 = 17;
const int led3 = 21;
int t = 100;

int only_light(int ledOn, int ledOut1, int ledOut2) {  
  digitalWrite(ledOn, HIGH);
  digitalWrite(ledOut1, LOW);
  digitalWrite(ledOut2, LOW);
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  
  only_light(led1, led2, led3);
  delay(t);
  only_light(led2, led1, led3);
  delay(t);
  only_light(led3, led1, led2);
  delay(t);
  only_light(led2, led1, led3);
  delay(t);
  
}
