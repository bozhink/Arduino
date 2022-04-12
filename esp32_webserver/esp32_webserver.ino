#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "s";
const char* password = "esp32_server@123";

IPAddress local_ip(192, 168, 12, 1);
IPAddress gateway(192, 168, 12, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

int listen;
int H, T;
void handle_root();

void setup() {
  // Create SoftAP
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  server.on("/", handle_root);
  server.onNotFound([](){ server.send(404, "text/plain", "The content was not found."); });
  server.begin();
}

void loop() {
  while (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 115) {
      listen = !listen;
    }

    Serial.println(listen ? "WEB on" : "WEB off");
  }

  if (listen) {
    server.handleClient();
  } else {
    delay(1980);
  }

  delay(10);
}

void handle_root() {
  if (server.args() == 0) {    
     server.send(200, "text/html", "H+T");    // Handle root url (/)
  } else {
    char command = server.arg("c").charAt(0);
    char answer[50];
    switch (command) {
      case 104:        // h set time
        //setTime(server.arg("n").toInt());
        sprintf(answer,"%s","New time");
        break;
      case 116:        // t temperature and humidity
        getTemperature();
        strcpy (answer,workBuffer);
        break;
    }
    sprintf(workBuffer, "%s %s", getTime(),answer);
    Serial.println(workBuffer);
    server.send(200, "text/html",workBuffer);
  }
}
