//
// Created by sasch on 01.08.2025.
//

#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <Arduino.h>

class BatteryMonitor {
public:
    BatteryMonitor(uint8_t pin);

    float getVoltage() const;             // Get actual battery voltage
    int getPercentage() const;            // Get battery percentage

private:
    uint8_t batteryPin;
    const float maxVoltage = 4.2;   // Full battery voltage
    const float minVoltage = 3.0;   // Empty battery voltage
};

#endif