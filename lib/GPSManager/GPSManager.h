#ifndef GPS_MANAGER_H_
#define GPS_MANAGER_H_

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "GPSData.h"

class GPSManager {
    private:

        TinyGPSPlus m_gps{};
        SoftwareSerial m_swSerial{};

        GPSData m_gpsData{};

    public:

        GPSManager();
        void begin();
        void update();
        const GPSData& getGPSData() const;

};

#endif