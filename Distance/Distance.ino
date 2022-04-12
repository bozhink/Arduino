#define ECHOPIN 2  // Pin "Echo" to a digital pin2 
#define TRIGPIN 3  // Pin "Trig" to a digital pin3

int sensorPin = A0;
int sensorValue = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

void loop()
{
  // Start Ranging
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  // Compute distance
  float distance = pulseIn(ECHOPIN, HIGH);
  distance = distance / 58;
  Serial.println(distance);

  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  Serial.println(sensorValue * 520.0 / 1024.0);
  delay(200);
}
