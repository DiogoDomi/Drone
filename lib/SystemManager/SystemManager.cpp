#include "SystemManager.h"

namespace {
    constexpr uint16_t TELEMETRY_INTERVAL = 5000;
}

SystemManager& SystemManager::getInstance() {
    static SystemManager instance;
    return instance;
}

SystemManager::SystemManager() :   
    m_server(80),
    m_socket("/ws"),

    m_imu(),
    m_wifi(),
    m_gps(),
    m_time(),
    m_database(),

    m_flight(m_imu),
    m_web(m_server, m_socket),
    m_telemetry(m_wifi, m_gps, m_flight, m_time),

    m_telemetryPreviousTime(0)
    {}

void SystemManager::setup() {
    m_flight.begin();
    // m_gps.begin();
    delay(4000);
    m_imu.begin();
    m_wifi.begin();
    m_web.begin();
    // m_time.begin();
    // m_database.begin();
}

void SystemManager::loop() {
    m_web.update();

    m_imu.update();
    bool hasStateChangeRequest = m_web.hasStateChangeRequest();
    JoystickData joystickData = m_web.getJoystickData();
    m_flight.update(hasStateChangeRequest, joystickData);

    // m_time.update();
    // m_gps.update();

    unsigned long currentTime = millis();
    bool sendTelemetry = (currentTime - m_telemetryPreviousTime >= TELEMETRY_INTERVAL);

    if (hasStateChangeRequest || sendTelemetry) {
        m_telemetryPreviousTime = currentTime;

        m_wifi.update();
        m_telemetry.update();

        TelemetryData telemetry = m_telemetry.getTelemetry();

        m_web.sendTelemetry(telemetry);
        m_web.cacheTelemetry(telemetry);

        // if (m_wifi.getWiFiStatus() == WL_CONNECTED) {
        //     m_database.sendDBData(telemetry);
        // }
    }
}