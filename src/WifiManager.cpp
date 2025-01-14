#include "WifiManager.hpp"
#include "constants.h"
#include "Display_manager.hpp"

void connectToWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WiFi: ");
    Serial.println(SSID);
    displayToOledText("Connecting to ");
    displayToOledLine(SSID);
    WiFi.begin(SSID, PASS);
    delay(5000);
  }
  Serial.println("Connected to WiFi!");
  displayToOledLine("Connected to WiFi!");
}

