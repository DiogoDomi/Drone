#ifndef WIFI_MANAGER_H_
#define WIFI_MANAGER_H_

#include <cstdint>
#include <ESP8266WiFi.h>

class WiFiManager {
    private:

        int8_t m_rssiData{};

    private:

        void setupAP();
        void setupSTA();

    public:

        WiFiManager();
        void begin();
        void update();

        inline int8_t getRSSIData() const { 
            return m_rssiData;
        }

        inline wl_status_t getWiFiStatus() const {
            return WiFi.status();
        }

};

#endif