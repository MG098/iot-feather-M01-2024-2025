#include <Arduino.h>
#include "display_manager.hpp"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool initOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    return false;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  return true;
}

void displayStartupMessage() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Starting..."));
  display.display();
  delay(2000);
}

void displayToOLED(const SensorData& data) {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print(F("Temp: ")); display.print(data.temperature); display.println(F(" C"));
  display.print(F("Hum: ")); display.print(data.humidity); display.println(F(" %"));
  display.print(F("Pres: ")); display.print(data.pressure); display.println(F(" hPa"));
  display.print(F("Lux: ")); display.print(data.lux); display.println(F(" lx"));

  display.display();
}
