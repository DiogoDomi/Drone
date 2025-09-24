#ifndef WIFI_MANAGER_H_
#define WIFI_MANAGER_H_

class WiFiManager {
    private:

        void setupAP();
        void setupSTA();

    public:

        WiFiManager();
        void begin();
        void update();

};

#endif