#include "sensor.h"
#include <WiFi.h>  // ESP32 uses WiFi.h
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "../mqtt_client/mqtt_client.h"
#include "config.h"

Adafruit_BMP085 bmp;

void initSensors() {
    if (!bmp.begin(BMP085_STANDARD)) {
        while (1) {
            sleep(1000); 
            Serial.println("Could not find a valid BMP085 sensor, check wiring!");
        }
  }
}

void readAndSendSensorData() {
    float temperature = bmp.readTemperature();
    int32_t pression = bmp.readPressure();

    if (isnan(temperature) || isnan(pression)) {
        publishMessage(TOPIC_ERREUR, ERREUR_BRANCHEMENT);
    } else {
        publishMessage(TOPIC_SENSOR_THERMOMETRE, String(temperature).c_str());
        publishMessage(TOPIC_SENSOR_PRESSION, String(pression).c_str());

        if (temperature < TEMPERATURE_MIN_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MIN_TEMPERATURE);
        } else if (temperature > TEMPERATURE_MAX_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MAX_TEMPERATURE);
        }

        if (pression < PRESSION_MIN_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MIN_PRESSION);
        } else if (pression > PRESSION_MAX_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MAX_PRESSION);
        }
    }
}