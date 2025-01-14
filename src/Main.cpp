#include <Arduino.h>
#include <ArduinoJson.h>
#include "main.hpp"
#include "WifiManager.hpp"
#include "MQTT.hpp"

WiFiClient wifiClient;
PubSubClient client(wifiClient);
SensorData sensorData;
// Create global WifiManager instance
// WifiManager wifiManager;
bool isWebConfigured = false;
int seconds = 0;
void setup() {
  Serial.begin(115200);
    while (!Serial) {
    ;
  }
  WiFi.setPins(WIFI_SHIELD_PINS);

  // Inicjalizacja sensorów
  if (!initSensors()) {
    Serial.println(F("Sensor initialization failed!"));
  }
  
  // Inicjalizacja OLED
  if (!initOLED()) {
    Serial.println(F("OLED initialization failed!"));
  }

  client.setServer(MQTT_SERVER, MQTT_PORT);

  connectToWiFi();


  displayStartupMessage();
}

unsigned long lastMillis = 0;

void loop() {

    if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  if (!client.connected()) {
    connectToMQTT();
  }
  /* Sensor data capture and display */
  unsigned long currentMillis = millis();

  if(currentMillis - lastMillis >= CAPTURE_INTERVAL){
    sensorData = readSensors();
    printToSerial(sensorData);
    displayToOLED(sensorData);
    seconds++;
    lastMillis = currentMillis;
  }
    
    client.loop();

if(seconds>=60)
{
  seconds=0;
  /* code */

    JsonDocument doc;
doc["temperature"] = sensorData.temperature;
doc["humidity"] = sensorData.humidity;
doc["pressure"] = sensorData.pressure;
doc["lux"] = sensorData.lux;

char payload[200];
serializeJson(doc, payload, sizeof(payload));

  if (client.publish(MQTT_TOPIC, payload)) {
    Serial.print("Data published: ");
    Serial.println(payload);
  } else {
    Serial.println("Failed to publish data");
  }
}

  
}

