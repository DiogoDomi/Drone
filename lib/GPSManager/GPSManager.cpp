#include "GPSManager.h"
#include "Pins.h"
#include "Flags.h"
#include <Arduino.h>

namespace { constexpr uint16_t SERIAL_BAUDRATE = 9600; }

GPSManager::GPSManager() :
    m_swSerial(Pins::GPS::RX_PIN, Pins::GPS::TX_PIN)
    {}

void GPSManager::begin() {
    m_swSerial.begin(SERIAL_BAUDRATE);
}

void GPSManager::update() { 
    while (m_swSerial.available() > 0) {
        char c = m_swSerial.read();
        Serial.print(c);
        if (m_gps.encode(c)) { 
            if (m_gps.location.isUpdated() && m_gps.location.isValid() && m_gps.altitude.isUpdated() && m_gps.altitude.isValid()) {
                m_currentData.lat = m_gps.location.lat();
                m_currentData.lon = m_gps.location.lng();
                m_currentData.alt = m_gps.altitude.meters();
                m_isNewDataAvailable = true;
            }
            Serial.println();
        }
    }
}

bool GPSManager::getDataIfNew(GPSData& data) {
    if (!m_isNewDataAvailable) { return false; }

    if (isDataDifferent(m_currentData.alt, m_lastSentData.alt) ||
        isDataDifferent(m_currentData.lat, m_lastSentData.lat) ||
        isDataDifferent(m_currentData.lon, m_lastSentData.lon))
    {
        data = m_currentData;
        m_lastSentData = m_currentData;
        m_isNewDataAvailable = false;
        return true;
    }

    m_isNewDataAvailable = false;
    return false;
}

bool GPSManager::isDataDifferent(float a, float b) {
    constexpr float epsilon = 0.000001F;
    return fabsf(a - b) > epsilon;
}