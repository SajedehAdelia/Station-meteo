#include "display.h"
#include "mqtt/mqtt.h"
#include "common.h"
#include <LiquidCrystal.h>
#include <queue>
#include <string>

extern LiquidCrystal lcd;
std::queue<Message> messageQueue;
Message currentMessage;
unsigned long lastDisplayTime = 0;
const unsigned long displayInterval = 5000;

const int buzzPin = D8;
const int redPin = D0;
const int greenPin = D1;
const int bluePin = D7;

void activateAlert() {
  tone(buzzPin, 1000);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void deactivateAlert() {
  noTone(buzzPin);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void displayMessage(const Message& msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg.topic.c_str());
  lcd.setCursor(0, 1);
  lcd.print(msg.payload.c_str());

  if (msg.isAlert) {
    Serial.println("Alerte activée !");
    activateAlert();
  } else {
    Serial.println("Alerte désactivée !");
    deactivateAlert();
  }
}

void handleDisplay() {
  unsigned long currentTime = millis();
  if (currentTime - lastDisplayTime >= displayInterval && !messageQueue.empty()) {
    currentMessage = messageQueue.front();
    messageQueue.pop();
    displayMessage(currentMessage);
    lastDisplayTime = currentTime;
  }
}