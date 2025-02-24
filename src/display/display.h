#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>
#include <queue>
#include <string>
#include "common.h"

const int buzzPin = D10;

extern LiquidCrystal_I2C lcd;
extern std::queue<Message> messageQueue;
extern Message currentMessage;
extern unsigned long lastDisplayTime;
extern const unsigned long displayInterval;

void displayMessage(const Message& msg);
void handleDisplay();
void activateAlert();
void deactivateAlert();

#endif