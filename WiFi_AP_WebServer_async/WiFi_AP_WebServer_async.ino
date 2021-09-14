//
// A simple server implementation showing how to:
//  * serve static messages
//  * turn LED with GET parameters
//  * handle missing pages / 404s
//
// reference: 
// - https://techtutorialsx.com/2017/12/01/esp32-arduino-asynchronous-http-webserver/
// required libs:
// - https://github.com/me-no-dev/AsyncTCP
// - https://github.com/me-no-dev/ESPAsyncWebServer

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* ssid = "ESP32";
const char* password = "ESP32123";

//const char* PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
    
    Serial.begin(115200);
    // Builtin LED GPIO02
    pinMode(2, OUTPUT);
    
    // Turn into Access Point
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();    
    Serial.print("IP Address: ");
    Serial.println(myIP);

    // Handle / (root)
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String resp, action;
        resp = "<!doctype html><html><body><p>Turn LED <a href=\"/?led=on\">on</a></p><p>Turn LED <a href=\"/?led=off\">off</a></p></body><html>";

        // Turn LED on and off with GET '/?led=on' or '/?led=off'
        if (request->hasParam("led")) { 
          action = request->getParam("led")->value();
          if (action == "on") {
              digitalWrite(2, HIGH);
              
          } else if (action == "off") {
              digitalWrite(2, LOW);              
          }
        }
        request->send(200, "text/html", resp);
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
}
