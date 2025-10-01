#ifndef GPS_MANAGER_H_
#define GPS_MANAGER_H_

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "GPSData.h"

class GPSManager {
    private:

        TinyGPSPlus m_gps{};
        SoftwareSerial m_swSerial{};

        GPSData m_currentData{};
        GPSData m_lastSentData{};

        bool m_isNewDataAvailable{};

    private:

        bool isDataDifferent(float a, float b);

    public:

        GPSManager();
        void begin();
        void update();
        bool getDataIfNew(GPSData& data);

};

#endif