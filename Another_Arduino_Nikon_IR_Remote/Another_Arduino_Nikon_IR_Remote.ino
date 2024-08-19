/* See https://www.rei-labs.net/another-arduino-nikon-ir-remote/ */
/* code by dejko1 rei-labs.net */
/* based on code from https://hackaday.io/project/1293-turn-a-cigarette-lighter-into-an-ir-nikon-remote */

/*
The IR LED should be connected to pin 3 using a current limiting resistor.

The code uses arduino timer 2 to generate the signal with approximately the right carrier frequency. The timer is running all the time, but PWM output is being turned on/off by setting and resetting the COM2B1 bit.

Note that this code does not just fire a single shot like the original code. It fires a shot every two seconds, so basically we have a simple intervalometer. The time can be changed by varying the amount of time in the delay(2000); statement.

I didn’t have an IR led on hand, so I tried it out with a red laser module and a blue led (connected in series with a 470 ohm resistor). Lol, when I started experimenting I thought I had an IR led, but the LED I got from an arduino IR transmitter + receiver + led package turned out to be just normal blue led…

Arduino IR remote

Actually I got the camera to fire using a blue led as the emitter, but the range was really small, like 50cm or so. I also tried removing the resistor to get higher current, but that didn’t increase the range significantly and it may be bad for the LED and the arduino pins.

DSC_0101a

So here is the selfie an Arduino took. Not much to see actually 🙂 LED is the white spot connected with wires to Arduino.

I have to try this with a real IR led to figure out what range I can achieve. Additionally the modulation depth and frequency could be tuned a bit to get even better range.

Note that there are actually quite a few libraries avaliable for arduino which are specifically made to control the Nikon and other cameras. Using these might be easier than “bit banging” the IR protocol.
 */

void setup() {
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS21);
  OCR2A = 52;
  OCR2B = 20;
}

void loop() {
  delay(60);
  pulse();
  pulse();
  delay(2000);
}

void pulse() {
  TCCR2A |= _BV(COM2B1);
  delayMicroseconds(2000);
  TCCR2A &= ~_BV(COM2B1);
  delay(28);
  TCCR2A |= _BV(COM2B1);
  delayMicroseconds(390);
  TCCR2A &= ~_BV(COM2B1);
  delayMicroseconds(1580);
  TCCR2A |= _BV(COM2B1);
  delayMicroseconds(410);
  TCCR2A &= ~_BV(COM2B1);
  delayMicroseconds(3580);
  TCCR2A |= _BV(COM2B1);
  delayMicroseconds(400);
  TCCR2A &= ~_BV(COM2B1);
  delay(63);
}