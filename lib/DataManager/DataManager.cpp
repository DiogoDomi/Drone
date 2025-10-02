#include "DataManager.h"
#include "Flags.h"
#include <cmath>

DataManager::DataManager(WiFiManager& wifi, GPSManager& gps) :
    m_wifi(wifi),
    m_gps(gps)
    {}

void DataManager::update() {
    m_currentTelemetry.rssi = m_wifi.getRSSI();
    m_currentTelemetry.gps = m_gps.getData();
}

bool DataManager::shouldSendToWeb() {
    if (isTelemetryDifferent(m_previousWebTelemetry, m_currentTelemetry)) {
        m_previousWebTelemetry = m_currentTelemetry;
        return true;
    }
    return false;
}

bool DataManager::shouldSendToBD() {
    if (isTelemetryDifferent(m_previousDBTelemetry, m_currentTelemetry) &&
    isTelemetryValid(m_currentTelemetry)) {
        m_previousDBTelemetry = m_currentTelemetry;
        return true;
    }
    return false;
}

TelemetryData DataManager::getCurrentTelemetry() const {
    return m_currentTelemetry;
}

bool DataManager::isTelemetryValid(const TelemetryData& telemetry) const {
    if (telemetry.rssi == Flags::WIFI_RSSI_INVALID) { return false; }
    if (telemetry.gps.lat == Flags::GPS_LAT_INVALID || telemetry.gps.lon == Flags::GPS_LON_INVALID) { return false; }
    if (telemetry.gps.alt == Flags::GPS_ALT_INVALID) { return false; }
    return true;
}

bool DataManager::isTelemetryDifferent(const TelemetryData& current, const TelemetryData& previous) const {
    constexpr float EPSILON = 0.000001F;

    if (current.rssi != previous.rssi) { return true; }
    if (fabsf(current.gps.lat - previous.gps.lat) > EPSILON) { return true; }
    if (fabsf(current.gps.lon - previous.gps.lon) > EPSILON) { return true; }
    if (fabsf(current.gps.alt - previous.gps.alt) > EPSILON) { return true; }

    return false;
};