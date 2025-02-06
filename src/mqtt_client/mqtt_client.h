#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
extern PubSubClient client;
void connectMQTT();
void publishMessage(const char* topic, const char* payload);

#endif