#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_SSD1306.h>
#include "Sensors.hpp"

bool initOLED();
void displayStartupMessage();
void displayToOLED(const SensorData& data);
void displayToOledText(const char* text);
void displayToOledLine(const char* text);

extern Adafruit_SSD1306 display;
#endif // DISPLAY_MANAGER_H