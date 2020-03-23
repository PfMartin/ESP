#include <Pals2.h>


#define IRED_CURRENT 10 //100 mA
#define DISABLE 0
#define ENABLE 1

Pals2 pals;
char buffer[100];

void setup() {
  delay(1000);

  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("---------------------------------------"));
  Serial.println(F("  INFINEON PALS  - Proximity  "));
  Serial.println(F("---------------------------------------"));
  
  pals.begin();
  pals.setProximityMeasurementRate(16);
  pals.setProximityOutput(IRED1, IRED_CURRENT);
  pals.setProximityPeriodicMeasurements(ENABLE);

}
void loop() {
  sprintf(buffer,"Proximity = %d \n", pals.readProximity());
  Serial.print(buffer);
  
  delay(1000);
}

void dumpRegisterContents(){

  Serial.print("------------------------------- \n");
  Serial.print("PALS2 Registers\n");
  Serial.print("------------------------------- \n");
  for(int a=0x80;a<=0x9C;a++){
    Serial.print("0x");
    Serial.print(a, HEX);
    Serial.print(" = ");
    Serial.print("0x");
    Serial.print(pals.dumpRegister(a),HEX);
    Serial.print(" \n");
  }
  Serial.print("------------------------------- \n");
} 
