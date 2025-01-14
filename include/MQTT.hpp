#ifndef MQTT_HPP
#define MQTT_HPP

#include <WiFi101.h>
#include <PubSubClient.h>
#include "WifiManager.hpp"

// extern WiFiClient wifiClient;

extern PubSubClient client;

void connectToMQTT();

#endif //MQTT_HPP