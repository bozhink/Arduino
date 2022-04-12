void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A6));
  Serial.println((1023 - analogRead(A6)) * 100.0 / 1024.0);
  delay(1000);
}
