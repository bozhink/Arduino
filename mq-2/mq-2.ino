
#include <MQ2.h>

const int gasPin = A7;

int lpg, co, smoke;

MQ2 mq2(gasPin);

void setup() {
  Serial.begin(9600);
  mq2.begin();
}

void loop() {
  Serial.println(analogRead(gasPin));

  float* values = mq2.read(true); // set it false if you don't want to print the values in the Serial.

  //lpg = values[0];
  //co = values[1];
  //smoke = values[2];
  
  //Serial.println(String("LPG = " + lpg) + String("; CO = " + co) + String("; Smoke = " + smoke));

  //lpg = mq2.readLPG();
  //co = mq2.readCO();
  //smoke = mq2.readSmoke();
  
  //Serial.println(String("LPG = " + lpg) + String("; CO = " + co) + String("; Smoke = " + smoke));
  
  delay(1000);
}
