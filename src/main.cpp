#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>
#include <Wifi.h>
#include <PubSubClient.h>
#include "display/display.h"
#include "mqtt/mqtt.h"
#include "common.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  setup_wifi();

  pinMode(buzzPin, OUTPUT);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  handleDisplay();
}