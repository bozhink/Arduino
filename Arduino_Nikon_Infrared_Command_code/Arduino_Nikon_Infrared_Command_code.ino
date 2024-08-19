/* https://www.christidis.info/index.php/personal-projects/arduino-nikon-infrared-command-code */

#define LEDpin 6
#define buttongpin 0

void setup() {
  pinMode(LEDpin, OUTPUT);    //led
  pinMode(Buttonpin, INPUT);  // button
}

void loop() {

  if (digitalRead(buttonpin) == 1) {
    takephoto();
    delay(1000);
  }
}

void takePhoto(void) {
  int i;
  for (i = 0; i < 76; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(7);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(7);
  }
  delay(27);
  delayMicroseconds(810);
  for (i = 0; i < 16; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(7);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(7);
  }
  delayMicroseconds(1540);
  for (i = 0; i < 16; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(7);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(7);
  }
  delayMicroseconds(3545);
  for (i = 0; i < 16; i++) {
    digitalWrite(LEDpin, HIGH);
    delayMicroseconds(7);
    digitalWrite(LEDpin, LOW);
    delayMicroseconds(7);
  }
}