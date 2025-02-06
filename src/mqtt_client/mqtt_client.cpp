#include "mqtt_client.h"
#include <WiFiClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void connectMQTT()
{
    if (!client.connected())
    {
        digitalWrite(PIN_LED, HIGH);
        client.setServer(MQTT_SERVER, 1883);
        while (!client.connected())
        {
            Serial.print("Connexion MQTT...");
            if (client.connect(ID_CLIENT_MQTT))
            {
                Serial.println("Connecté !");
            }
            else
            {
                Serial.print("Échec, code erreur : ");
                Serial.println(client.state());
                delay(5000);
            }
        }
        digitalWrite(PIN_LED, LOW);
    }
}

void publishMessage(const char *topic, const char *payload)
{
    String fullTopic = String(TOPIC_ROOT) + "/" + String(TOPIC_LOCALISATION) + "/" + String(topic);
    client.publish(fullTopic.c_str(), payload);
    Serial.print("Send :");
    Serial.print(fullTopic);
    Serial.print(" :");
    Serial.println(payload);
}