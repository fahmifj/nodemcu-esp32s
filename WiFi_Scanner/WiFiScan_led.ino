/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"

int LED_BUILTIN = 2;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void loop()
{
    // LED on indicates the scan is starting
    digitalWrite(LED_BUILTIN, HIGH);
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    if (n == 0) {
        Serial.println("No networks found");
    } else {
        Serial.println("Available networks: ");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print("[");
            Serial.print(i + 1);
            Serial.print("] ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            int wifiSig = WiFi.RSSI(i);           
            if (wifiSig < -85) { // -86 and below is poor wifi signal
              Serial.print("Poor"); 
            } else if (wifiSig < -65){ // -85 and up until -66 is medium wifi signal
              Serial.print("Medium");
            } else { // -65 above is strong wifi signal
              Serial.print("Strong");
            }
            Serial.print(", ");
            Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"open":"secured");
            Serial.print(")");
            Serial.println("");
            delay(10);
        }
    }
    Serial.println("");
    // Wait a bit before scanning again
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000*30);
    
}
