#ifndef GPS_MANAGER_H_
#define GPS_MANAGER_H_

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "GPSData.h"

class GPSManager {
    private:

        static constexpr uint16_t GPS_BAUDRATE = 9600;

        TinyGPSPlus m_gps{};
        SoftwareSerial m_swSerial{};

        GPSData m_gpsData{};

    public:

        GPSManager();

        inline void begin() {
            m_swSerial.begin(GPS_BAUDRATE);
        }
        void update();

        inline const GPSData& getGPSData() const {
            return m_gpsData;
        }

};

#endif