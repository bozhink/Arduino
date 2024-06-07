// See https://wiki.dfrobot.com/URM09_Ultrasonic_Sensor_(Gravity_Analog)_SKU_SEN0307
// # Editor     : roker
// # Date       : 18.02.2019

// # Product name: URM09 Ultrasonic Sensor(Gravity Analog)(V1.0)
// # Product SKU : SEN0307
// # Version     : 1.0


#define MAX_RANG     (520)    // the max measurement vaule of the module is 520cm (a little bit longer than  effective max range)
#define ADC_SOLUTION (1023.0) // ADC accuracy of Arduino UNO is 10bit

int sensityPin = A0;          // select the input pin
float dist_t;
float sensity_t;

void setup() {
  // Serial init
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensity_t = analogRead(sensityPin);
  dist_t = sensity_t * MAX_RANG  / ADC_SOLUTION;

  Serial.print(dist_t, 0);
  Serial.println("cm");

  delay(500);
}
