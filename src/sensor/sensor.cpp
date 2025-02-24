#include "sensor.h"
#include <WiFi.h>  // ESP32 uses WiFi.h
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "../mqtt_client/mqtt_client.h"
#include "config.h"
#include <BH1750.h>

// Adafruit_BMP085 bmp;
BH1750 lightMeter;

void initSensors() {
    Wire.begin();
    lightMeter.begin();

    Serial.println(F("BH1750 Test begin"));
//     if (!bmp.begin(BMP085_STANDARD)) {
//         while (1) {
//             sleep(1000); 
//             Serial.println("Could not find a valid BMP085 sensor, check wiring!");
//         }
//   }
}

void readAndSendSensorData() {
    float lux = lightMeter.readLightLevel();
    if (isnan(lux)) {
        publishMessage(TOPIC_ERREUR, ERREUR_BRANCHEMENT);
    } else {
        publishMessage(TOPIC_SENSOR_LUMINOSITE, String(lux).c_str());
        
        if (lux < LUMINOSITE_MIN_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MIN_LUMINOSITE);
        } else if (lux > LUMINOSITE_MAX_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MAX_LUMINOSITE);
        }
    }
}