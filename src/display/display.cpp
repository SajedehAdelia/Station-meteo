#include "display.h"
#include "mqtt/mqtt.h"
#include "common.h"
#include <LiquidCrystal.h>
#include <queue>
#include <string>

extern LiquidCrystal lcd;
extern std::queue<Message> messageQueue;
extern Message currentMessage;
extern unsigned long lastDisplayTime;
extern const unsigned long displayInterval;

const int buzzPin = D8;
const int redPin = D0;
const int greenPin = D1;
const int bluePin = D7;

void activateAlert() {
  digitalWrite(buzzPin, HIGH);
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void deactivateAlert() {
  digitalWrite(buzzPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void displayMessage(const Message& msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg.topic.c_str());
  lcd.setCursor(0, 1);
  lcd.print(msg.payload.c_str());

  if (msg.isAlert) {
    activateAlert();
  } else {
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