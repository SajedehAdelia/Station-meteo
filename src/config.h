#define SSID "Redmi Note 13 Pro 5G MAX"
#define PASSWORD "dw7zwujfdy8kvcv"
#define MQTT_SERVER "192.168.127.95"
#define ID_CLIENT_MQTT "ESP32-Temp-hum-cuisine"

#define TOPIC_ROOT "StationMeteoAdeliaLoanGaelMaxence"
#define TOPIC_LOCALISATION "cuisine"
#define TOPIC_SENSOR_THERMOMETRE "thermometre"
#define TOPIC_SENSOR_PRESSION "pression"
#define TOPIC_ALERTE "alerte"
#define TOPIC_ERREUR "erreur"

#define ERREUR_BRANCHEMENT "Le capteur est mal branché"
#define ALERTE_MAX_TEMPERATURE "temperature > max"
#define ALERTE_MIN_TEMPERATURE "temperature < min"
#define ALERTE_MAX_PRESSION "pression > max"
#define ALERTE_MIN_PRESSION "pression < min"

const int TEMPERATURE_MAX_ALERTE = 26;
const int TEMPERATURE_MIN_ALERTE = 18;

const int PRESSION_MAX_ALERTE = 1040;
const int PRESSION_MIN_ALERTE = 990;

#define PIN_LED 2
#define ADRESS 0x77