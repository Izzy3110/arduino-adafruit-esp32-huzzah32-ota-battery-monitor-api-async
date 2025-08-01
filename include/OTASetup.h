//
// Created by sasch on 01.08.2025.
//

#ifndef OTA_SETUP_H
#define OTA_SETUP_H

#include <ArduinoOTA.h>

class OTASetup {
public:
    OTASetup(const char* hostname, const char* password);

    void begin() const;

    static void handle();  // Call this regularly in loop()

private:
    const char* hostname;
    const char* password;
};

#endif // OTA_SETUP_H
