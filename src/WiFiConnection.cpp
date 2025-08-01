#include "../include/WiFiConnection.h"
#include <LEDFunctions.h>

WiFiConnection::WiFiConnection(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void WiFiConnection::begin() const {
    if (!WiFi.config(localIP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("⚠️ Failed to configure static IP");
    }

    connectWiFi();
}

void WiFiConnection::connectWiFi() const {
    if (WiFi.status() == WL_CONNECTED) return;

    Serial.print("🔌 Connecting to WiFi: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
}

void WiFiConnection::handle() {
    const unsigned long now = millis();
    if (now - lastCheck < checkInterval) return;
    lastCheck = now;

    if (WiFi.status() != WL_CONNECTED) {
        flashLED(4);
        Serial.println("⚠️ WiFi disconnected, reconnecting...");
        connectWiFi();
    }
}
