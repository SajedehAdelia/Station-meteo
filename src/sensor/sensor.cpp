#include "sensor.h"
#include <WiFi.h>  // ESP32 uses WiFi.h
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "../mqtt_client/mqtt_client.h"
#include "config.h"
#include <BH1750.h>
#include <DHT.h>

// Adafruit_BMP085 bmp;
BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);

void initSensors() {
    Wire.begin();
    lightMeter.begin();

    dht.begin();

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
        std::string topic = std::string(TOPIC_SENSOR_LUMINOSITE) + "/" + TOPIC_ERREUR;
        publishMessage(topic.c_str(), ERREUR_BRANCHEMENT);
    } else {
        publishMessage(TOPIC_SENSOR_LUMINOSITE, String(lux).c_str());
        
        if (lux < LUMINOSITE_MIN_ALERTE) {
            std::string topic = std::string(TOPIC_SENSOR_LUMINOSITE) + "/" + TOPIC_ALERTE;
            publishMessage(topic.c_str(), ALERTE_MIN_LUMINOSITE);
        } else if (lux > LUMINOSITE_MAX_ALERTE) {
            std::string topic = std::string(TOPIC_SENSOR_LUMINOSITE) + "/" + TOPIC_ALERTE;
            publishMessage(topic.c_str(), ALERTE_MAX_LUMINOSITE);
        }
    }

    float temperature = dht.readTemperature();
    float humidite = dht.readHumidity();

    if (std::isnan(temperature)) {
        std::string topic = std::string(TOPIC_SENSOR_THERMOMETRE) + "/" + TOPIC_ERREUR;
        publishMessage(topic.c_str(), ERREUR_BRANCHEMENT);
    }
    if (std::isnan(humidite)) {
        std::string topic = std::string(TOPIC_SENSOR_HUMIDITE) + "/" + TOPIC_ERREUR;
        publishMessage(topic.c_str(), ERREUR_BRANCHEMENT);
    }
    else {
        publishMessage(TOPIC_SENSOR_THERMOMETRE, String(temperature).c_str());
        publishMessage(TOPIC_SENSOR_HUMIDITE, String(humidite).c_str());

        if (temperature < TEMPERATURE_MIN_ALERTE) {
            std::string topic = std::string(TOPIC_SENSOR_THERMOMETRE) + "/" + TOPIC_ALERTE;
            publishMessage(topic.c_str(), ALERTE_MIN_TEMPERATURE);
        } else if (temperature > TEMPERATURE_MAX_ALERTE) {
            std::string topic = std::string(TOPIC_SENSOR_THERMOMETRE) + "/" + TOPIC_ALERTE;
            publishMessage(topic.c_str(), ALERTE_MAX_TEMPERATURE);
        }

        if (humidite < HUMIDITE_MIN_ALERTE) {
            std::string topic = std::string(TOPIC_SENSOR_HUMIDITE) + "/" + TOPIC_ALERTE;
            publishMessage(topic.c_str(), ALERTE_MIN_HUMIDITE);
        } else if (humidite > HUMIDITE_MAX_ALERTE) {
            std::string topic = std::string(TOPIC_SENSOR_HUMIDITE) + "/" + TOPIC_ALERTE;
            publishMessage(topic.c_str(), ALERTE_MAX_HUMIDITE);
        }
    }
}