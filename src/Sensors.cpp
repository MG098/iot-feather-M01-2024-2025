
#include "Sensors.hpp"
#include <Wire.h>

Adafruit_BME280 bme;
APDS9301 apds;

bool initSensors() {
  bool success = true;
  
  if (!bme.begin(0x77)) {
    Serial.println(F("Failed to initialize BME280 sensor"));
    success = false;
  }
  
  if (!apds.begin(0x39)) {
    Serial.println(F("Failed to initialize APDS9301 sensor"));
    success = false;
  }
  
  return success;
}

SensorData readSensors() {
  SensorData data;
  data.temperature = bme.readTemperature();
  data.humidity = bme.readHumidity();
  data.pressure = bme.readPressure() / 100.0F;
  data.lux = apds.readLuxLevel();
  return data;
}
