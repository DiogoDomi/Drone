#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include "WiFiManager.h"
#include "GPSManager.h"
#include "TelemetryData.h"

class DataManager {
    private:

        WiFiManager& m_wifi;
        GPSManager& m_gps;

        TelemetryData m_currentTelemetry{};
        TelemetryData m_previousWebTelemetry{};
        TelemetryData m_previousDBTelemetry{};

    private:

        bool isTelemetryValid(const TelemetryData& telemetry) const;
        bool isTelemetryDifferent(const TelemetryData& current, const TelemetryData& previous) const;

    public:

        DataManager(WiFiManager& wifi, GPSManager& gps);
        void update();
        bool shouldSendToWeb();
        bool shouldSendToBD();
        TelemetryData getCurrentTelemetry() const;
};

#endif