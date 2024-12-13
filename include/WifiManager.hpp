#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP

#include <WiFi101.h>

class WifiManager {
public:
    // Constructor
    WifiManager();

    // Start Access Point mode
    void startAccessPoint();

    // Connect to WiFi with given credentials
    bool connectToWiFi(const char* ssid, const char* password);

    // Handle incoming web requests for WiFi configuration
    void handleWebConfig();

    // Get stored WiFi credentials
    void getStoredCredentials(char* ssid, char* password, char* token);
    void sendConfigPage(WiFiClient& client);
private:
    // WiFi credentials storage
    char _ssid[32];
    char _password[64];
    char _token[64];

    // WiFi server for configuration
    WiFiServer _server;

    // Parse form data from HTTP request
    bool parseFormData(const String& request);
};

#endif // WIFI_MANAGER_HPP