#include "mqtt.h"
#include "display/display.h"
#include "common.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <queue>
#include <string>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

WiFiClient espClient;
PubSubClient client(espClient);
std::queue<Message> messageQueue;
Message currentMessage;
unsigned long lastDisplayTime = 0;
const unsigned long displayInterval = 5000;

const char *ssid = "Redmi Note 13 Pro 5G MAX";
const char *password = "dw7zwujfdy8kvcv";
const char *mqtt_server = "192.168.127.95";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Message wifiMessage = {"WiFi", std::string("connected: ") + WiFi.localIP().toString().c_str(), false};
  displayMessage(wifiMessage);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Ecran")) {
      Serial.println("connected");
      client.subscribe("StationMeteoAdeliaLoanGaelMaxence/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  std::string payloadStr((char*)payload, length);
  bool isAlert = strstr(topic, "alerte") != nullptr;

  Message msg = {topic, payloadStr, isAlert};
  if (isAlert) {
    // If it's an alert, display it immediately
    displayMessage(msg);
    lastDisplayTime = millis();
  } else {
    // Otherwise, add it to the queue
    messageQueue.push(msg);
  }
}