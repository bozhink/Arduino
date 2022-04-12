#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>

#define USE_SERIAL Serial

#define USER_AGENT "ESP8266"
#define EVENT "reading"
#define VERSION "0.0.1"
#define SERVER_IP "192.168.0.0:8080"
#define NUMBER_OF_READINGS 3

#ifndef STASSID
#define STASSID "----"
#define STAPSK  "-----"
#endif

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp; // I2C

void initializeSerial(void);
void initializeSensor(void);
void initializeWiFi(void);
char* getReading();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  initializeSerial();
  initializeSensor();
  initializeWiFi();
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    char* readings[NUMBER_OF_READINGS];
    for (int i = 0; i < NUMBER_OF_READINGS; /*Skip increment here*/) {
      char* reading = getReading();
      delay(2000);
      if (reading != NULL) {
        readings[i] = reading;
        i++;
      }
    }


    String payload = "{\"sender\":\""USER_AGENT"\",\"event\":\""EVENT"\",\"readings\":[";
    payload.concat(readings[0]);
    for (int i = 0; i < NUMBER_OF_READINGS; i++) {
      payload.concat(',');
      payload.concat(readings[i]);
    }
    payload.concat("],\"version\":\""VERSION"\"}");

    USE_SERIAL.println(payload);

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");

    // configure targed server and url
    http.begin("http://" SERVER_IP "/api/v1/events"); //HTTP
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", USER_AGENT);
    http.addHeader("X-IOT-VERSION", VERSION);
    http.addHeader("X-IOT-EVENT", EVENT);

    USE_SERIAL.print("[HTTP] POST...\n");

    // start connection and send HTTP header and body
    int httpCode = http.POST(payload);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        USE_SERIAL.println("received payload:\n<<");
        USE_SERIAL.println(http.getString());
        USE_SERIAL.println(">>");
      }
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(30000);
}

void initializeSerial(void) {
  USE_SERIAL.begin(115200);
}

void initializeSensor(void) {
  if (!bmp.begin()) {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  //bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void initializeWiFi(void) {
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    USE_SERIAL.print(".");
  }

  USE_SERIAL.println("");
  USE_SERIAL.print("Connected! IP address: ");
  USE_SERIAL.println(WiFi.localIP());
}

char* getReading() {
  if (bmp.performReading()) {
    char data[128];
    sprintf(data,
            "{\"sensor\":\"%s\",\"temperature\":%0.2f,\"pressure\":%0.2f,\"altitude\":%0.2f}",
            "BMP388",
            bmp.temperature,
            bmp.pressure / 100.0,
            bmp.readAltitude(SEALEVELPRESSURE_HPA));
    return data;
  } else {
    return NULL;
  }
}
