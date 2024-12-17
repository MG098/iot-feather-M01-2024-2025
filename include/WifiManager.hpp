#ifndef WIFI_MANAGER_HPP
#define WIFI_MANAGER_HPP

#include <WiFi101.h>
#include <HTTPClient.h>
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
    //WiFiSSLClient SSLClient;
    String _Cloudtoken = "Feather_TOKEN";   //"Feather_TOKEN"  "cc2d945c-4a74-4178-bfbc-8050ce7ee3b9";
    String _Cloudserver = "iot.makowski.edu.pl";    //"iot.makowski.edu.pl"    "webhook.site"
    StaticJsonDocument<2048> jsonbuf;
    String reqstr;
    bool parseFormData(const String& request);
    const char* rootCACertificate = "-----BEGIN CERTIFICATE-----\n" \
    "MIIDhDCCAwqgAwIBAgISA4j3snC9QrDXgPA8VnRGo6NKMAoGCCqGSM49BAMDMDIx\n" \
    "CzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQDEwJF\n" \
    "NTAeFw0yNDEyMTMxMzEyMTJaFw0yNTAzMTMxMzEyMTFaMBwxGjAYBgNVBAMMESou\n" \
    "bWFrb3dza2kuZWR1LnBsMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAElX8RH6ke\n" \
    "ycHqn+/cozoYdvhVE9hHKTZEVr3Jzh1xTi394v28qaBYtXxy81NEDgPS5zn6aqfY\n" \
    "5t6RGOsu7SBoXKOCAhQwggIQMA4GA1UdDwEB/wQEAwIHgDAdBgNVHSUEFjAUBggr\n" \
    "BgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUEBe5Q48b\n" \
    "Gi6EadDuXyBCQshXpR0wHwYDVR0jBBgwFoAUnytfzzwhT50Et+0rLMTGcIvS1w0w\n" \
    "VQYIKwYBBQUHAQEESTBHMCEGCCsGAQUFBzABhhVodHRwOi8vZTUuby5sZW5jci5v\n" \
    "cmcwIgYIKwYBBQUHMAKGFmh0dHA6Ly9lNS5pLmxlbmNyLm9yZy8wHAYDVR0RBBUw\n" \
    "E4IRKi5tYWtvd3NraS5lZHUucGwwEwYDVR0gBAwwCjAIBgZngQwBAgEwggEFBgor\n" \
    "BgEEAdZ5AgQCBIH2BIHzAPEAdgCi4wrkRe+9rZt+OO1HZ3dT14JbhJTXK14bLMS5\n" \
    "UKRH5wAAAZPAW4BpAAAEAwBHMEUCIQDRof9doBBfqx5iScjw4v5Z1YMuAbioIdgF\n" \
    "4kmGvwpv3gIgbIqAOHsYWugVhB2dbn6mlTCjbOH/tUAWzB81eQfufAsAdwATSt8a\n" \
    "tZhCCXgMb+9MepGkFrcjSc5YV2rfrtqnwqvgIgAAAZPAW4EtAAAEAwBIMEYCIQDI\n" \
    "Ys+2vZRNSxwIDlJidV8ekg29g5AEaP9UfOevYalYRgIhAJybjLYpQ25VdVBjZoX8\n" \
    "9SLd4g6SipHMVDGmfwFwe2EFMAoGCCqGSM49BAMDA2gAMGUCMQDfUU3s9HQP5vGp\n" \
    "mF1dhCvb50NGvURz4n00AF3vzXvHtLspdqMjJ3F4oN4EaKrUnbACMCTo5du1VvCT\n" \
    "LT8IFCfj8yY5GO/bxZD6IbmosppNTn94AjDcrODdA2uogHBb5k05hQ==\n" \
    "-----END CERTIFICATE-----\n";
};

#endif // WIFI_MANAGER_HPP