#include "WiFiManager.h"
#include <ESP8266WiFi.h>

namespace {
    const char *AP_SSID = "DroneController";
    const char *AP_PSWD = "12345678";

    const IPAddress AP_LOCAL_IP(192, 168, 4, 200);
    const IPAddress AP_GATEWAY(192, 168, 4, 1);
    const IPAddress AP_SUBNET(255, 255, 255, 0);

    const char *STA_SSID = "LEO_2_4G";
    const char *STA_PSWD = "Leovegildocesar1#";

    const IPAddress STA_LOCAL_IP(192, 168, 0, 200);
    const IPAddress STA_GATEWAY(192, 168, 0, 1);
    const IPAddress STA_SUBNET(255, 255, 255, 0);
}

WiFiManager::WiFiManager() {}

void WiFiManager::setupAP() {
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY, AP_SUBNET); 
    WiFi.softAP(AP_SSID, AP_PSWD);
}

void WiFiManager::setupSTA() {
    WiFi.config(STA_LOCAL_IP, STA_GATEWAY, STA_SUBNET);
    WiFi.begin(STA_SSID, STA_PSWD);
}

void WiFiManager::update() {
    WiFi.RSSI();
}

void WiFiManager::begin() {
    WiFi.mode(WiFiMode_t::WIFI_AP_STA);
    setupAP();
    setupSTA();
}