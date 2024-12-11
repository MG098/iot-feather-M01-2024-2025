#include <Arduino.h>
#include "main.hpp"

void setup() {
  Serial.begin(115200);

  // Inicjalizacja sensorów
  if (!initSensors()) {
    Serial.println(F("Sensor initialization failed!"));
  }

  // Inicjalizacja OLED
  if (!initOLED()) {
    Serial.println(F("OLED initialization failed!"));
  }

  displayStartupMessage();
}
unsigned long lastMillis = 0;
void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - lastMillis >= CAPTURE_INTERVAL){
    SensorData sensorData = readSensors();
    printToSerial(sensorData);
    displayToOLED(sensorData);
    lastMillis = currentMillis;
  }
}