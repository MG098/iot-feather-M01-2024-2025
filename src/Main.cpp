#include <Arduino.h>
#include "main.hpp"
#include "WifiManager.hpp"

// Create global WifiManager instance
WifiManager wifiManager;

void setup() {
  Serial.begin(115200);
  WiFi.setPins(WIFI_SHIELD_PINS);

  // Inicjalizacja sensorów
  if (!initSensors()) {
    Serial.println(F("Sensor initialization failed!"));
  }
  
  // Inicjalizacja OLED
  if (!initOLED()) {
    Serial.println(F("OLED initialization failed!"));
  }

  // Start Access Point for initial configuration
  wifiManager.startAccessPoint();
  displayStartupMessage();
}

unsigned long lastMillis = 0;
void loop() {
  // Handle web configuration
  wifiManager.handleWebConfig();

  unsigned long currentMillis = millis();

  // Sensor data capture and display
  if(currentMillis - lastMillis >= CAPTURE_INTERVAL){
    SensorData sensorData = readSensors();
    printToSerial(sensorData);
    displayToOLED(sensorData);
    lastMillis = currentMillis;
    
    Serial.print("Adres IP: ");
    IPAddress apip = WiFi.localIP();
    Serial.println(apip);
  }
}