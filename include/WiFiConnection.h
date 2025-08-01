#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <WiFi.h>
#include <IPAddress.h>

class WiFiConnection {
public:
    WiFiConnection(const char* ssid, const char* password);

    void begin() const;    // Start WiFi connection
    void handle();   // Call regularly in loop() to check and reconnect if disconnected

private:
    const char* ssid;
    const char* password;

    const IPAddress localIP   = IPAddress(192, 168, 137, 130);
    const IPAddress gateway   = IPAddress(192, 168, 137, 253);
    const IPAddress subnet    = IPAddress(255, 255, 255, 0);
    const IPAddress primaryDNS   = IPAddress(8, 8, 8, 8);
    const IPAddress secondaryDNS = IPAddress(1, 1, 1, 1);

    unsigned long lastCheck = 0;
    const unsigned long checkInterval = 5000; // check every 5 seconds

    void connectWiFi() const;
};

#endif // WIFI_CONNECTION_H
