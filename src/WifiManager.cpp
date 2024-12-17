#include "WifiManager.hpp"
#include "constants.h"


WifiManager::WifiManager() : _server(80) {
    memset(_ssid, 0, sizeof(_ssid));
    memset(_password, 0, sizeof(_password));
    memset(_token, 0, sizeof(_token));
}


void WifiManager::startAccessPoint() {
    WiFi.end();
    
    Serial.println("Rozpoczynanie konfiguracji Wi-Fi w trybie Access Point...");
    
    WiFi.config(IPAddress(192, 168, 1, 1));
    WiFi.beginAP(AP_SSID, AP_PASS);
    
    Serial.print("Access Point uruchomiony. Adres IP: ");
    IPAddress apip = WiFi.localIP();
    Serial.println(apip);

    _server.begin();
    Serial.println("Serwer HTTP uruchomiony.");
}


bool WifiManager::connectToWiFi(const char* ssid, const char* password) {
    WiFi.end();
    
    Serial.print("\n\u0141ączenie z siecią Wi-Fi: ");
    Serial.print(ssid);

    for (int attempt = 1; attempt <= 3; attempt++) {
        Serial.print("\r\nPróba połączenia (");
        Serial.print(attempt);
        Serial.println(")...");

        WiFi.begin(ssid, password);

        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startTime < 5000) {
            delay(500);
            Serial.print(".");
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\nPołączono z siecią Wi-Fi.");
            Serial.print("Adres IP: ");
            Serial.println(WiFi.localIP());
            
            strncpy(_ssid, ssid, sizeof(_ssid) - 1);
            strncpy(_password, password, sizeof(_password) - 1);
            
            return true;
        }

        delay(1000);
    }

    Serial.println("\nNie udało się połączyć z siecią Wi-Fi.");
    return false;
}


bool WifiManager::checkAvailability() {
    bool isAvailable = false;

    client = _server.available();
    if (!client) {
        isAvailable =  false;
    }

    if (!client.available()) {
        delay(50);
        return isAvailable;
    }

    isAvailable = true;
    return isAvailable;
}


bool WifiManager::handleWebConfig() {
    bool isWebConfigured = 0;

    if(checkAvailability()){
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();
        
        if (request.indexOf("GET /submit?") < 0) {
            sendConfigPage(client);
            return false;
        }


        if (parseFormData(request)) {
            client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
            client.print("<h1>Dane zostały zapisane!</h1>");
            client.stop();
            delay(1000);

            if (!connectToWiFi(_ssid, _password)) {
                Serial.println("Nie udało się połączyć. Przywracanie trybu Access Point...");
                startAccessPoint();
            }else{
                Serial.println("Pomyślnie połączono z siecią.");
                isWebConfigured = true;
            }
        }
    }
    return isWebConfigured;
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


bool WifiManager::openCloudConnection(){
    if (!client.connected()){
        Serial.print("Connecting to \"");
        Serial.print(_Cloudserver);
        Serial.print("\"...");

        if (!client.connect("iot.makowski.edu.pl", 80)) {
            Serial.println(" failed");
            return false;
        }else {
            Serial.println(": Cloud connected");
            return true;
        }
    }else {
        Serial.println("Already connected");
        return true;
    }
}


void WifiManager::publishData(SensorData data){
    String jsonstr = "";
    int jsonlen = 0;
    jsonlen = 0;

    /* Compose JSON */
    jsonbuf["Temperature"] = data.temperature;
    jsonbuf["Humidity"] = data.humidity;
    jsonbuf["Pressure"] = data.pressure;
    jsonbuf["Luminance"] = data.lux;

    serializeJson(jsonbuf, jsonstr);
    jsonlen = jsonstr.length();

    /* Compose HTTP POST request*/
    reqstr = "POST /api/v1/" + _Cloudtoken + "/telemetry HTTP/1.1\r\nHost: " + _Cloudserver + "\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: " + jsonlen + "\r\n\r\n" + jsonstr;
    //reqstr = "POST /" + _Cloudtoken + " HTTP/1.1\r\nHost: " + _Cloudserver + "\r\nContent-Length: " + jsonlen + "\r\n\r\n" + jsonstr;

    Serial.println("\r\nHTTP Request: ");
    Serial.print(reqstr);

    /* Send HTTP POST request*/
    client.print(reqstr);

    /* Wait till the answer of the server */
    uint32_t start = millis();

    while (client.connected() && !client.available() && millis() - start < 2000L) {
        delay(50);
    }

    /* Read received HTTP reply */
    Serial.println("\r\nHTTP Reply: ");

    if (client.available()){
        start = millis();
        while (client.connected() && (millis() - start) < 5000L) {
            if (client.available()) {
                Serial.write(client.read());
                start = millis();
            }
        }
    } else {
        Serial.println("... No Reply received\r\n");
    }
}


void WifiManager::closeCloudconnection(void) {
  if (client.connected()) {
    client.stop();
    Serial.println("Cloud disconnected\r\n");
  }
}


