#define SSID "Redmi Note 13 Pro 5G MAX"
#define PASSWORD "dw7zwujfdy8kvcv"
#define MQTT_SERVER "192.168.231.95"
#define ID_CLIENT_MQTT "ESP32-lum-terrasse"

#define TOPIC_ROOT "StationMeteoAdeliaLoanGaelMaxence"
#define TOPIC_LOCALISATION "terrasse"
#define TOPIC_SENSOR_LUMINOSITE "luminosite"
#define TOPIC_ALERTE "luminosite/alerte"
#define TOPIC_ERREUR "luminosite/erreur"

#define ERREUR_BRANCHEMENT "Le capteur est mal branché"
#define ALERTE_MAX_LUMINOSITE "luminosite > max"
#define ALERTE_MIN_LUMINOSITE "luminosite < min"

const int LUMINOSITE_MAX_ALERTE = 1000;
const int LUMINOSITE_MIN_ALERTE = 10;

#define PIN_LED 2
#define ADRESS 0x77