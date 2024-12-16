#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP

#include <WiFi101.h>
#include <ArduinoJson.h>
#include "Sensors.hpp"

class WifiManager {
public:
    WifiManager();
    void startAccessPoint();
    bool connectToWiFi(const char* ssid, const char* password);
    bool handleWebConfig();
    void getStoredCredentials(char* ssid, char* password, char* token);
    void sendConfigPage(WiFiClient& client);
    bool openCloudConnection();
    void publishData(SensorData data);
    void closeCloudconnection();
    bool checkAvailability();
private:
    WiFiServer _server;
    char _ssid[32];
    char _password[64];
    char _token[64];

    WiFiClient client;
    String _Cloudtoken = "cc2d945c-4a74-4178-bfbc-8050ce7ee3b9"; //"Feather_TOKEN"  "cc2d945c-4a74-4178-bfbc-8050ce7ee3b9";
    String _Cloudserver = "webhook.site";                        //"iot.makowski.edu.pl"    "webhook.site"
    StaticJsonDocument<2048> jsonbuf;
    String reqstr;
    bool parseFormData(const String& request);
};

#endif // WIFI_MANAGER_HPP