#include <Arduino.h>
#include "Utils.hpp"

void printToSerial(const SensorData& data) {
  Serial.println(F("=== Sensor Data ==="));
  Serial.print(F("Temperature: ")); Serial.println(data.temperature);
  Serial.print(F("Humidity: ")); Serial.println(data.humidity);
  Serial.print(F("Pressure: ")); Serial.println(data.pressure);
  Serial.print(F("Luminance: ")); Serial.println(data.lux);
  Serial.println();
}
