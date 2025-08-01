//
// Created by sasch on 01.08.2025.
//

#include "../include/BatteryMonitor.h"

BatteryMonitor::BatteryMonitor(uint8_t pin) : batteryPin(pin) {
    analogReadResolution(12); // For ESP32 or boards with >10-bit ADC
}

float BatteryMonitor::getVoltage() const {
    const int raw = analogRead(batteryPin);
    const float voltage = (raw / 4095.0) * 3.3;
    return voltage * 2; // Adjust based on voltage divider (e.g., 100k/100k)
}

int BatteryMonitor::getPercentage() const {
    const float voltage = getVoltage();
    const int percent = (voltage - minVoltage) / (maxVoltage - minVoltage) * 100;
    return constrain(percent, 0, 100);
}
