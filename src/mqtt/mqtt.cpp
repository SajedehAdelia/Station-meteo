#include "mqtt.h"
#include "display/display.h"
#include "common.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <queue>
#include <string>

WiFiClient espClient;
PubSubClient client(espClient);

const char *ssid = "Redmi Note 13 Pro 5G MAX";
const char *password = "dw7zwujfdy8kvcv";
const char *mqtt_server = "192.168.231.95";

const std::string mainTopic = "StationMeteoAdeliaLoanGaelMaxence/";

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

  Message wifiMessage = {"WiFi connected: ", WiFi.localIP().toString().c_str(), false};
  displayMessage(wifiMessage);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Ecran")) {
      Serial.println("connected");
      client.subscribe((mainTopic + "#").c_str());
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
  std::string topicStr(topic);
  size_t pos = topicStr.find(mainTopic);
  if (pos != std::string::npos) {
    // Extraire la partie "location"
    pos += mainTopic.length();
    size_t endPos = topicStr.find('/', pos);
    std::string location = topicStr.substr(pos, endPos - pos);

    // Extraire la partie "capteur"
    pos = endPos + 1;
    endPos = topicStr.find('/', pos);
    std::string capteur = topicStr.substr(pos, endPos - pos);
    if (!capteur.empty()) capteur[0] = toupper(capteur[0]);
    if (capteur.length() > 5) {
      capteur = capteur.substr(0, 5);
    }

    Message msg = {capteur + " " + location + " :", payloadStr, isAlert};

    bool messageExists = false;
    std::queue<Message> tempQueue;
    while (!messageQueue.empty()) {
      Message existingMsg = messageQueue.front();
      messageQueue.pop();
      if (existingMsg.topic == msg.topic) {
        messageExists = true;
        tempQueue.push(msg);
      } else {
        tempQueue.push(existingMsg);
      }
    }
    messageQueue = tempQueue;

    if (isAlert) {
      // If it's an alert, display it immediately
      displayMessage(msg);
      Serial.println("Alerte !");
      lastDisplayTime = millis();
    }
    else if (!messageExists) {
      messageQueue.push(msg);
    }
  }
}