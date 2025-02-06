#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include <queue>
#include <string>
#include "common.h"

extern LiquidCrystal lcd;
extern std::queue<Message> messageQueue;
extern Message currentMessage;
extern unsigned long lastDisplayTime;
extern const unsigned long displayInterval;

extern const int buzzPin;
extern const int redPin;
extern const int greenPin;
extern const int bluePin;

void displayMessage(const Message& msg);
void handleDisplay();
void activateAlert();
void deactivateAlert();

#endif