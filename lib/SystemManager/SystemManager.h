#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include "WiFiManager.h"
#include "WebManager.h"
#include "IMUManager.h"
#include "FlightManager.h"
#include "GPSManager.h"
#include "DataManager.h"

class SystemManager {
    private:

        SystemManager();
        SystemManager(const SystemManager&) = delete;
        void operator=(const SystemManager&) = delete;

        AsyncWebServer m_server;
        AsyncWebSocket m_socket;

        unsigned long m_previousTelemetryTime{};
    
    private:

        WiFiManager m_wifi{};
        WebManager m_web;
        IMUManager m_imu{};
        FlightManager m_flight;
        GPSManager m_gps{};
        DataManager m_data;

    public:

        static SystemManager& getInstance();
        void setup();
        void loop();

};

#endif