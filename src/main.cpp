#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <BH1750.h>
#include <Wire.h>
#include <DHT.h>
#include <DHT_U.h>
#include <PubSubClient.h>
#include <string>
#include <WiFi.h>  

const char* ssid = "Redmi Note 13 Pro 5G MAX";          // Remplace par ton SSID WiFi
const char* password = "dw7zwujfdy8kvcv";       // Remplace par ton mot de passe WiFi
const char* mqtt_server = "192.168.127.95"; // IP du serveur Mosquitto
const char* topic_root = "StationMeteoAdeliaLoanGaelMaxence"; 
const char* topic_localisation = "cuisine"; 
const char* topic_sensor_thermometre = "thermometre"; 
const char* topic_sensor_humidite = "humidite"; 
const char* topic_alert = "alert"; 
const char* id_client_mqtt = "ESP32Client";

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN 4 // Define the GPIO pin for the data pin
#define DHTTYPE DHT11 // Specify the DHT model

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);

    // Connexion WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connecté");

    // Connexion MQTT
    client.setServer(mqtt_server, 1883);
    
    while (!client.connected()) {
        Serial.print("Connexion MQTT...");
        if (client.connect(id_client_mqtt)) {
            Serial.println("Connecté !");
        } else {
            Serial.print("Échec, code erreur : ");
            Serial.println(client.state());
            delay(5000);
        }
    }

    Serial.println(F("BH1750 Test begin"));

    // Initialize the sensor
    dht.begin();
}

void loop() {
    client.loop(); // Gérer les messages MQTT

    static unsigned long lastMsg = 0;
    if (millis() - lastMsg > 5000) {
        lastMsg = millis();

        // Read temperature and humidity
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        String topic = String(topic_root) + "/" + String(topic_localisation) + "/" + String(topic_sensor_thermometre);
        client.publish(topic.c_str(), String(temperature).c_str());

        topic = String(topic_root) + "/" + String(topic_localisation) + "/" + String(topic_sensor_humidite);
        client.publish(topic.c_str(), String(humidity).c_str());

        Serial.println("Message envoyé !");
    }
}