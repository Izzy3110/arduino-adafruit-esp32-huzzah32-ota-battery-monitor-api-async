#include <secrets.h>
#include "config.h"
#include <ESPAsyncWebServer.h>
#include "../include/AsyncWebServerHandler.h"
#include "OTASetup.h"
#include "../include/WiFiConnection.h"
#include "../include/LEDFunctions.h"
#include "HomeAssistant.h"

BatteryMonitor battery(BATTERY_PIN);
AsyncWebServerHandler webHandler(HTTP_PORT, &battery);
WiFiConnection wifi(WIFI_SSID, WIFI_PASSWORD);
OTASetup ota(OTA_HOSTNAME, OTA_PASSWORD);

unsigned long previousMillis = 0;
constexpr long interval = 10000;  // 10 seconds

unsigned long previousMillis_http = 0;
constexpr long interval_http = 5000;  // 10 seconds

void setup(){
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  wifi.begin();        // Connects to WiFi
  ota.begin();
  webHandler.begin();
}

void loop() {
  wifi.handle();  // reconnect if disconnected
  ota.handle(); // must be called regularly to process OTA events

  const unsigned long currentMillis = millis();

  if (currentMillis - previousMillis_http >= interval_http) {
    previousMillis_http = currentMillis;

    const int percent = battery.getPercentage();
    const float voltage = battery.getVoltage();
    sendBatteryToHA(voltage, percent);

    flashLED(1);
  }
}