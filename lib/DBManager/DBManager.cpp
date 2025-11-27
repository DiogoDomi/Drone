#include "DBManager.h"
#include <ArduinoJson.h>

namespace {
    const char* FIREBASE_URL = "https://banco-de-dados---drone-default-rtdb.firebaseio.com/readings.json";
}

DBManager::DBManager() 
    {}

void DBManager::begin() {
    m_client.setInsecure();
    m_http.setReuse(true);
}

bool DBManager::flush() {
    if (m_logsCount == 0) return true;

    if (!m_http.begin(m_client, FIREBASE_URL)) { return false; }

    m_http.addHeader("Content-Type", "application/json");

    char output[JSON_TELEMETRY_SIZE]{};

    for (uint8_t i = 0; i < m_logsCount; i++) {
        StaticJsonDocument<JSON_TELEMETRY_SIZE> doc{};

        if (m_logs[i].isValid) {
            doc["ts"]       = m_logs[i].timestamp;
            doc["rssi"]     = m_logs[i].rssi;
            doc["lat"]      = m_logs[i].gps.lat;
            doc["lon"]      = m_logs[i].gps.lon;
            doc["alt"]      = m_logs[i].gps.alt;
        } else {
            doc["isValid"]  = m_logs[i].isValid;
        }

        serializeJson(doc, output, JSON_TELEMETRY_SIZE);

        m_http.POST(output);

        yield();
    }

    m_http.end();
    m_logsCount = 0;

    return true;
}