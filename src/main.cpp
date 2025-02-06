#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Wifi.h>
#include <PubSubClient.h>
#include "display/display.h"
#include "mqtt/mqtt.h"
#include "common.h"

LiquidCrystal lcd(D10, D9, D5, D4, D3, D2);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);

  setup_wifi();

  pinMode(buzzPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  handleDisplay();
}