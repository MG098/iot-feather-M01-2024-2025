#include "MQTT.hpp"
#include "constants.h"
#include "Display_manager.hpp"

void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT broker...");
    displayToOledLine("Connecting to MQTT broker...");
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
      Serial.println("Connected to MQTT broker!");
      displayToOledLine("Connected to MQTT broker!");
    } else {
      Serial.print("Failed to connect. State: ");
      Serial.println(client.state());
      displayToOledLine("Failed to connect");
      delay(1000);
    }
  }
}