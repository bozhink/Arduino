#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

// Fingerprint for URL
// echo -n | openssl s_client -connect eu-west-1.aws.webhooks.mongodb-stitch.com:443 -CAfile /usr/share/ca-certificates/mozilla/DigiCert_Assured_ID_Root_CA.crt | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > ./x.pem
// openssl x509 -noout -in x.pem -fingerprint -sha1
const uint8_t fingerprint[20] = { 0x85, 0x41, 0x43, 0x19, 0xCA, 0x5A, 0x2E, 0x57, 0x4B, 0x0B, 0xD1, 0xC9, 0x44, 0x93, 0x5D, 0xF8, 0xEB, 0x30, 0x00, 0x73 };

#ifndef STASSID
#define STASSID "============="
#define STAPSK  "============="
#endif

#ifndef APIURI
#define APIURI "https://eu-west-1.aws.webhooks.mongodb-stitch.com/api/client/v2.0/app/iot-bcyxm/service/iotc/incoming_webhook/w?secret=Ni7aedaafohgh3th"
#endif

#ifndef USER_AGENT
#define USER_AGENT "NodeMCU"
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(STASSID, STAPSK);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient https;

    if (https.begin(*client, APIURI)) {
      https.addHeader("Content-Type", "application/json");
      https.addHeader("User-Agent", USER_AGENT);

      int httpCode = https.POST("{\"sender\":\"" USER_AGENT "\",\"version\":\"" VERSION "\"}");

      // httpCode will be negative on error
      if (httpCode > 0) {
                  String payload = https.getString();
          Serial.println(payload);
        
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.printf("[HTTPS] POST... success with successful status code: %d\n", httpCode);
        } else {
          Serial.printf("[HTTPS] POST... failed with unsuccessful status code: %d\n", httpCode);
        }
      } else {
        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}
