//
// Created by sasch on 01.08.2025.
//
#include "../include/AsyncWebServerHandler.h"
#include "secrets.h"

AsyncWebServerHandler::AsyncWebServerHandler(const uint16_t port, BatteryMonitor* batteryMonitor)
  : server(port), battery(batteryMonitor) {}

void AsyncWebServerHandler::begin() {
    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request){
        if(!request->authenticate(HTTP_USERNAME, HTTP_PASSWORD))
            return request->requestAuthentication();
        request->send(200, "text/html", index_html);
    });

    server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(401);
    });

    server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", logout_html);
    });

    server.on("/api/battery", HTTP_GET, [this](AsyncWebServerRequest *request){
        if(!request->authenticate(HTTP_USERNAME, HTTP_PASSWORD))
            return request->requestAuthentication();

        float voltage = battery->getVoltage();
        int percent = battery->getPercentage();
        String json = "{\"battery_voltage\": " + String(voltage, 2) + ", \"battery_percent\": " + String(percent) + "}";
        request->send(200, "application/json", json);
    });

    server.begin();
}
