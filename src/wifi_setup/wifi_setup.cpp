#include "wifi_setup.h"
#include <WiFi.h>
#include "config.h"

void connectWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        digitalWrite(PIN_LED, HIGH);
        WiFi.begin(SSID, PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWiFi connecté");
        digitalWrite(PIN_LED, LOW);
    }
    
}