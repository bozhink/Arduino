#define ECHOPIN 2  // Pin "Echo" to a digital pin2 
#define TRIGPIN 3  // Pin "Trig" to a digital pin3
 
void setup()
{
  Serial.begin(9600);
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
  distance= distance/58;
  Serial.println(distance);
  delay(200);
}
