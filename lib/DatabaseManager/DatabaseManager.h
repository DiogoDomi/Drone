#ifndef DATABASE_MANAGER_H_
#define DATABASE_MANAGER_H_

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "TelemetryData.h"
#include <time.h>

class DatabaseManager {
    static const uint8_t JSON_TELEMETRY_SIZE = 160;

    private:

        WiFiClientSecure m_client{};
        HTTPClient m_http{};

    public:

        DatabaseManager();
        void begin();
        bool sendDBData(const TelemetryData& telemetry, const time_t timestamp);

};

#endif