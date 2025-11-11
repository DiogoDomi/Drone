#ifndef DATABASE_MANAGER_H_
#define DATABASE_MANAGER_H_

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "TelemetryData.h"

class DatabaseManager {
    static const uint8_t JSON_TELEMETRY_SIZE = 180;

    private:

        WiFiClientSecure m_client{};
        HTTPClient m_http{};

    public:

        DatabaseManager();
        void begin();
        void sendDBData(const TelemetryData& telemetry);

};

#endif