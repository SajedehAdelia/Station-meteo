#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <WiFi.h>
#include <SPI.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char* ssid = "Redmi Note 13 Pro 5G MAX";          // Remplace par ton SSID WiFi
const char* password = "dw7zwujfdy8kvcv";       // Remplace par ton mot de passe WiFi
const char* mqtt_server = "192.168.127.95"; // IP du serveur Mosquitto
const char* topic_root = "StationMeteoAdeliaLoanGaelMaxence"; 
const char* topic_localisation = "cuisine"; 
const char* topic_sensor_thermometre = "thermometre"; 
const char* topic_alert = "alert"; 
const char* id_client_mqtt = "ESP32Client";

Adafruit_BMP085 bmp;

void setup() {
    Serial.begin(115200);
    delay(1000); // Petit délai pour stabiliser l'affichage série

    // Connexion au WiFi
    Serial.print("Connexion au WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnecté au WiFi!");

    // Initialisation du capteur BMP180
    if (!bmp.begin()) {
        Serial.println("Impossible de trouver un capteur BMP085/BMP180, vérifie le câblage !");
        while (1);
    }
}

void loop() {
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure() / 100.0F;

    Serial.print("Température = ");
    Serial.print(temperature, 1);
    Serial.println(" °C");
    
    Serial.print("Pression = ");
    Serial.print(pressure);
    Serial.println(" hPa");

    delay(1000);
}
