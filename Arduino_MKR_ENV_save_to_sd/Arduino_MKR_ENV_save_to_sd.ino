/*
  MKR ENV Shield - Read Sensors

  This example reads the sensors on-board the MKR ENV Shield
  and prints them to the Serial Monitor once a second.

  The circuit:
  - Arduino MKR board
  - Arduino MKR ENV Shield attached
  - SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  This example code is in the public domain.
*/

#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 4;

File myFile;

void setup() {
  Serial.begin(9600);

  if (!ENV.begin()) {
    if (!!Serial) Serial.println("Failed to initialize MKR ENV Shield!");

    while (1) {
      // loop forever
    }
  }

  if (!!Serial) Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    if (!!Serial) Serial.println("initialization failed!");
    while (1) {
      // loop forever
    }
  }

  if (!!Serial) Serial.println("initialization done.");
}

void loop() {

  // read all the sensor values
  float temperature = ENV.readTemperature();
  float humidity = ENV.readHumidity();
  float pressure = ENV.readPressure();
  float illuminance = ENV.readIlluminance();
  float uva = ENV.readUVA();
  float uvb = ENV.readUVB();
  float uvIndex = ENV.readUVIndex();

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("env.txt", FILE_WRITE);

  if (!!Serial) {
    // print each of the sensor values
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    = ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Pressure    = ");
    Serial.print(pressure);
    Serial.println(" kPa");

    Serial.print("Illuminance = ");
    Serial.print(illuminance);
    Serial.println(" lx");

    Serial.print("UVA         = ");
    Serial.println(uva);

    Serial.print("UVB         = ");
    Serial.println(uvb);

    Serial.print("UV Index    = ");
    Serial.println(uvIndex);

    // print an empty line
    Serial.println();
  }

  // if the file opened okay, write to it:
  if (myFile) {

    myFile.print("{");

    myFile.print("\"Temperature[°C]\":");
    myFile.print(temperature);
    myFile.print(",");

    myFile.print("\"Pressure[kPa]\":");
    myFile.print(pressure);
    myFile.print(",");

    myFile.print("\"Illuminance[lx]\":");
    myFile.print(illuminance);
    myFile.print(",");

    myFile.print("\"UVA\":");
    myFile.print(uva);
    myFile.print(",");

    myFile.print("\"UVB\":");
    myFile.print(uvb);
    myFile.print(",");

    myFile.print("\"UV Index\":");
    myFile.print(uvIndex);

    myFile.println("}");

    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    if (!!Serial) Serial.println("error opening env.txt");
  }

  // wait 5 seconds to print again
  delay(5000);
}
