#include <Arduino.h>
#include "wifi_setup/wifi_setup.h"
#include "mqtt_client/mqtt_client.h"
#include "sensor/sensor.h"
#include "config.h"

void setup() {
    Serial.begin(115200);
    pinMode(PIN_LED,OUTPUT);
    initSensors();
}

unsigned long lastMsg = 0;
void loop() {
    connectWiFi();
    connectMQTT();
    
    client.loop();
    if (millis() - lastMsg > 5000) {
        lastMsg = millis();
        readAndSendSensorData();
    }
}