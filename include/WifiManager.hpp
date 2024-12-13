#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP

#include <WiFi101.h>

class WifiManager {
public:
    WifiManager();
    void startAccessPoint();
    bool connectToWiFi(const char* ssid, const char* password);
    void handleWebConfig();
    void getStoredCredentials(char* ssid, char* password, char* token);
    void sendConfigPage(WiFiClient& client);

private:
    char _ssid[32];
    char _password[64];
    char _token[64];
    WiFiServer _server;
    bool parseFormData(const String& request);
};

#endif // WIFI_MANAGER_HPP