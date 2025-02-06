#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "common.h"

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