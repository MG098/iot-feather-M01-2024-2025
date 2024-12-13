#include "WifiManager.hpp"
#include "constants.h"

WifiManager::WifiManager() : _server(80) {
    memset(_ssid, 0, sizeof(_ssid));
    memset(_password, 0, sizeof(_password));
    memset(_token, 0, sizeof(_token));
}

void WifiManager::startAccessPoint() {
    // Rozłącz z aktualnym połączeniem
    WiFi.disconnect();
    
    Serial.println("Rozpoczynanie konfiguracji Wi-Fi w trybie Access Point...");
    
    // Ustaw tryb Access Point
    WiFi.config(IPAddress(192, 168, 1, 1));
    WiFi.beginAP(AP_SSID, AP_PASS);
    
    Serial.print("Access Point uruchomiony. Adres IP: ");
    IPAddress apip = WiFi.localIP();
    Serial.println(apip);

    _server.begin();
    Serial.println("Serwer HTTP uruchomiony.");
}

bool WifiManager::connectToWiFi(const char* ssid, const char* password) {
    // Rozłącz z poprzedniego połączenia
    WiFi.disconnect();
    
    Serial.print("\n\u0141ączenie z siecią Wi-Fi: ");
    Serial.println(ssid);

    // Spróbuj kilka razy nawiązać połączenie
    for (int attempt = 1; attempt <= 3; attempt++) {
        Serial.print("Próba połączenia (");
        Serial.print(attempt);
        Serial.println(")...");

        // Rozpocznij próbę połączenia
        WiFi.begin(ssid, password);

        // Odczekaj maksymalnie 10 sekund na połączenie
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
            delay(500);
            Serial.print(".");
        }

        // Sprawdź status połączenia
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\nPołączono z siecią Wi-Fi.");
            Serial.print("Adres IP: ");
            Serial.println(WiFi.localIP());
            
            // Zapisz pomyślnie użyte dane
            strncpy(_ssid, ssid, sizeof(_ssid) - 1);
            strncpy(_password, password, sizeof(_password) - 1);
            
            return true;
        }

        // Krótka przerwa przed kolejną próbą
        delay(1000);
    }

    Serial.println("\nNie udało się połączyć z siecią Wi-Fi.");
    return false;
}

void WifiManager::handleWebConfig() {
    WiFiClient client = _server.available();
    if (!client) {
        return;
    }

    while (!client.available()) {
        delay(1);
    }

    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("GET /submit?") >= 0) {
        if (parseFormData(request)) {
            // Wyślij odpowiedź przed próbą połączenia
            client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
            client.print("<h1>Dane zostały zapisane! Próba połączenia z siecią Wi-Fi...</h1>");
            client.stop();

            // Krótka przerwa
            delay(1000);

            // Próba połączenia z siecią
            if (!connectToWiFi(_ssid, _password)) {
                Serial.println("Nie udało się połączyć. Przywracanie trybu Access Point...");
                startAccessPoint();
                return;
            }

            // Jeśli połączenie się powiodło, możesz dodać dodatkowe działania
            Serial.println("Pomyślnie połączono z siecią.");
            return;
        }
    }

    // Wysłanie strony konfiguracyjnej
    sendConfigPage(client);
}

bool WifiManager::parseFormData(const String& request) {
    int ssidIndex = request.indexOf("ssid=");
    int tokenIndex = request.indexOf("token=");
    int passwordIndex = request.indexOf("password=");

    if (ssidIndex >= 0 && tokenIndex >= 0 && passwordIndex >= 0) {
        sscanf(request.c_str() + ssidIndex, "ssid=%31[^&]&", _ssid);
        sscanf(request.c_str() + tokenIndex, "token=%63[^&]&", _token);
        sscanf(request.c_str() + passwordIndex, "password=%63[^ ]", _password);

        Serial.println("Dane odebrane:");
        Serial.print("SSID: ");
        Serial.println(_ssid);
        Serial.print("Token: ");
        Serial.println(_token);
        Serial.print("Password: ");
        Serial.println(_password);

        return true;
    }
    return false;
}

void WifiManager::sendConfigPage(WiFiClient& client) {
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print("<!DOCTYPE html><html><head>");
    client.print("<title>Konfiguracja Wi-Fi</title>");
    client.print("<meta charset='UTF-8'>");
    client.print("<style>");
    client.print("body { font-family: Arial, sans-serif; max-width: 400px; margin: 0 auto; padding: 20px; }");
    client.print("input { width: 100%; padding: 10px; margin: 10px 0; }");
    client.print("input[type='submit'] { background-color: #4CAF50; color: white; border: none; }");
    client.print("</style>");
    client.print("</head><body>");
    client.print("<h1>Konfiguracja Wi-Fi</h1>");
    client.print("<form action=\"/submit\" method=\"get\">");
    client.print("<label>SSID sieci:</label><br>");
    client.print("<input type=\"text\" name=\"ssid\" required placeholder=\"Nazwa sieci WiFi\"><br>");
    client.print("<label>Token (opcjonalnie):</label><br>");
    client.print("<input type=\"text\" name=\"token\" placeholder=\"Token dostępu\"><br>");
    client.print("<label>Hasło:</label><br>");
    client.print("<input type=\"password\" name=\"password\" required placeholder=\"Hasło sieci WiFi\"><br>");
    client.print("<input type=\"submit\" value=\"Połącz\">");
    client.print("</form>");
    client.print("</body></html>");
    client.stop();
}

void WifiManager::getStoredCredentials(char* ssid, char* password, char* token) {
    strncpy(ssid, _ssid, 32);
    strncpy(password, _password, 64);
    strncpy(token, _token, 64);
}