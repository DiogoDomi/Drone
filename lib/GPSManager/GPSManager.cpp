#include "GPSManager.h"
#include "Pins.h"
#include "Flags.h"

namespace { 
    constexpr uint16_t GPS_BAUDRATE = 9600;
    constexpr uint16_t GPS_TIMEOUT_MS = 2000;
}

GPSManager::GPSManager() :
    m_swSerial(Pins::GPS::RX_PIN, Pins::GPS::TX_PIN),
    m_gpsData{Flags::GPS_LAT_INVALID, Flags::GPS_LON_INVALID, Flags::GPS_ALT_INVALID}
    {}

void GPSManager::begin() {
    m_swSerial.begin(GPS_BAUDRATE);
}

void GPSManager::update() { 
    while (m_swSerial.available() > 0) {
        m_gps.encode(m_swSerial.read());
    }
    if (m_gps.location.isValid() && m_gps.location.age() < GPS_TIMEOUT_MS) {
        m_gpsData.lat = m_gps.location.lat();
        m_gpsData.lon = m_gps.location.lng();
    } else {
        m_gpsData.lat = Flags::GPS_LAT_INVALID;
        m_gpsData.lon = Flags::GPS_LON_INVALID;
    }

    if (m_gps.altitude.isValid() && m_gps.altitude.age() < GPS_TIMEOUT_MS) {
        m_gpsData.alt = m_gps.altitude.meters();
    } else {
        m_gpsData.alt = Flags::GPS_ALT_INVALID;
    }
}

GPSData GPSManager::getGPSData() const { return m_gpsData; }