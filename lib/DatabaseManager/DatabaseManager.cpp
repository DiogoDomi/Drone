#include "DatabaseManager.h"
#include <ArduinoJson.h>

namespace {
    const char* FIREBASE_URL = "https://banco-de-dados---drone-default-rtdb.firebaseio.com/readings.json";
}

DatabaseManager::DatabaseManager() {}

void DatabaseManager::begin() {
    m_client.setInsecure();
}

bool DatabaseManager::sendDBData(const TelemetryData& telemetry, time_t timeStamp) {
    if (!m_http.begin(m_client, FIREBASE_URL)) { return false; }

    JsonDocument doc{};

    char formattedTime[25];
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localtime(&timeStamp));

    doc["isValid"] = telemetry.isValid;
    doc["datetime"] = formattedTime;
    doc["rssi"] = telemetry.rssi;
    doc["lat"] = telemetry.gps.lat;
    doc["lon"] = telemetry.gps.lon;
    doc["alt"] = telemetry.gps.alt;

    char output[UINT8_MAX]{};
    serializeJson(doc, output);

    m_http.addHeader("Content-Type", "application/json");
    uint8_t httpCode = m_http.POST(output);

    m_http.end();

    return (httpCode == HTTP_CODE_OK);
}