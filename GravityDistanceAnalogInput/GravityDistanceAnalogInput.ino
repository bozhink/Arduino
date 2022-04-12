int sensorPin = A0;
int sensorValue = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  Serial.println(sensorValue * 520.0 / 1024.0);
  delay(200);
}
