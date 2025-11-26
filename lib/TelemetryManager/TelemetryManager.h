#ifndef TELEMETRY_MANAGER_H_
#define TELEMETRY_MANAGER_H_

#include "WiFiManager.h"
#include "GPSManager.h"
#include "TelemetryData.h"
#include "FlightManager.h"
#include "TimeManager.h"
#include "DatabaseManager.h"

class TelemetryManager {
    private:

        WiFiManager& m_wifi;
        GPSManager& m_gps;
        FlightManager& m_flight;
        TimeManager& m_time;
        DatabaseManager& m_db;

        TelemetryData m_telemetry{};

    private:

        bool isTelemetryValid(const TelemetryData& telemetry) const;

    public:

        TelemetryManager(WiFiManager& wifi, GPSManager& gps, FlightManager& flight, TimeManager& time, DatabaseManager& db);
        void update();

        inline const TelemetryData& getTelemetry() const {
            return m_telemetry;
        }
};

#endif