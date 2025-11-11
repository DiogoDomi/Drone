#include "DatabaseManager.h"
#include <ArduinoJson.h>

namespace {
    const char* FIREBASE_URL = "https://banco-de-dados---drone-default-rtdb.firebaseio.com/readings.json";
}

DatabaseManager::DatabaseManager() {}

void DatabaseManager::begin() {
    m_client.setInsecure();
}

void DatabaseManager::sendDBData(const TelemetryData& telemetry) {
    if (!m_http.begin(m_client, FIREBASE_URL)) { return; }

    StaticJsonDocument<JSON_TELEMETRY_SIZE> doc{};

    doc["valid"] =  telemetry.isValid;
    doc["ts"] =     telemetry.timestamp;
    doc["rssi"] =   telemetry.rssi;
    doc["lat"] =    telemetry.gps.lat;
    doc["lon"] =    telemetry.gps.lon;
    doc["alt"] =    telemetry.gps.alt;

    char output[JSON_TELEMETRY_SIZE]{};
    serializeJson(doc, output, JSON_TELEMETRY_SIZE);

    m_http.addHeader("Content-Type", "application/json");
    m_http.POST(output);

    m_http.end();
}