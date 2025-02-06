#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "common.h"

extern WiFiClient espClient;
extern PubSubClient client;
extern const char* mqtt_server;

void setup_wifi();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);

#endif