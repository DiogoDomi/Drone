#include "WiFiManager.h"
#include "Flags.h"

namespace {
    const char *AP_SSID = "DroneController";
    const char *AP_PSWD = "12345678";

    const IPAddress AP_LOCAL_IP(192, 168, 4, 200);
    const IPAddress AP_GATEWAY(192, 168, 4, 1);
    const IPAddress AP_SUBNET(255, 255, 255, 0);

    const char *STA_SSID = "LEO_2_4G";
    const char *STA_PSWD = "Leovegildocesar1#";
}

WiFiManager::WiFiManager() :
    m_rssiData(Flags::WIFI_RSSI_INVALID)
    {}

void WiFiManager::begin() {
    WiFi.mode(WiFiMode_t::WIFI_AP_STA);
    WiFi.persistent(false);
    setupAP();
    setupSTA();
}

void WiFiManager::setupAP() {
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY, AP_SUBNET); 
    WiFi.softAP(AP_SSID, AP_PSWD);
}

void WiFiManager::setupSTA() {
    WiFi.begin(STA_SSID, STA_PSWD);
}

void WiFiManager::update() {
    if (WiFi.status() == WL_CONNECTED) {
        m_rssiData = WiFi.RSSI();
    } else {
        m_rssiData = Flags::WIFI_RSSI_INVALID;
    }
}