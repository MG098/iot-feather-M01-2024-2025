#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Sparkfun_APDS9301_Library.h>

struct SensorData {
  float temperature;
  float humidity;
  float pressure;
  float lux;
};

bool initSensors();
SensorData readSensors();

#endif // SENSORS_H
