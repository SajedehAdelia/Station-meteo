#include "sensor.h"
#include <DHT.h>
#include "Wire.h"
#include "../mqtt_client/mqtt_client.h"
#include "config.h"

DHT dht(DHTPIN, DHTTYPE);

void initSensors() {
    dht.begin();
}

void readAndSendSensorData() {
    float temperature = dht.readTemperature();
    float humidite = dht.readHumidity();

    if (isnan(temperature) || isnan(humidite)) {
        publishMessage(TOPIC_ERREUR, ERREUR_BRANCHEMENT);
    } else {
        publishMessage(TOPIC_SENSOR_THERMOMETRE, String(temperature).c_str());
        publishMessage(TOPIC_SENSOR_HUMIDITE, String(humidite).c_str());

        if (temperature < TEMPERATURE_MIN_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MIN_TEMPERATURE);
        } else if (temperature > TEMPERATURE_MAX_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MAX_TEMPERATURE);
        }

        if (humidite < HUMIDITE_MIN_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MIN_HUMIDITE);
        } else if (humidite > HUMIDITE_MAX_ALERTE) {
            publishMessage(TOPIC_ALERTE, ALERTE_MAX_HUMIDITE);
        }
    }
}