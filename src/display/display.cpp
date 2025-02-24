#include "mqtt/mqtt.h"
#include "common.h"
#include "display.h"
#include <LiquidCrystal_I2C.h>
#include <queue>
#include <string>

extern LiquidCrystal_I2C lcd;
std::queue<Message> messageQueue;
Message currentMessage;
unsigned long lastDisplayTime = 0;
const unsigned long displayInterval = 8000;
bool alertIsOn = false;

void activateAlert() {
  tone(buzzPin, 1000);
  alertIsOn = true;
}

void deactivateAlert() {
  noTone(buzzPin);
  alertIsOn = false;
}

void displayMessage(const Message& msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg.topic.c_str());
  lcd.setCursor(0, 1);
  lcd.print(msg.payload.c_str());
  
  if (msg.isAlert) {
    activateAlert();
  } else if (alertIsOn) {
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