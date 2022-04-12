/*
  Calculation of machine epsilon.

  created 20 Dec 2019
  modified 20 Dec 2019
  by Bozhin Karaivanov
*/

float eps_f;
double eps_d;
long double eps_ld;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  eps_f = 1.0f;
  eps_d = 1.0;
  eps_ld = 1.0;
}

void loop() {
  float one_f = 1.0f;
  double one_d = 1.0;
  long double one_ld = 1.0;

  if (one_f + eps_f > one_f) {
    eps_f /= 2.0;
  }

  if (one_d + eps_d > one_d) {
    eps_d /= 2.0;
  }

  if (one_ld + eps_ld > one_ld) {
    eps_ld /= 2.0;
  }

  Serial.println(eps_f);
  Serial.println(eps_d);
  //Serial.println(eps_ld);
  delay(100);
}
