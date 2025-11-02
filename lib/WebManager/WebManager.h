#ifndef WEB_MANAGER_H_
#define WEB_MANAGER_H_

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "JoystickData.h"
#include "TelemetryData.h"
#include "State.h"

class WebManager {
    private:

        AsyncWebServer& m_server;
        AsyncWebSocket& m_socket;

        State m_cachedState{};
        TelemetryData m_cachedTelemetry{};

        JoystickData m_joystickData{};
        volatile bool m_stateChangeRequested{};

        JsonDocument m_requestDoc{};

    private:

        void setupServer();
        void setupSocket();
        void onEventHandler(AsyncWebSocket* socket, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);
        void handleWebSocketMessage(void* arg, uint8_t* data, size_t len);
        void onConnectSendTelemetry(AsyncWebSocketClient* client) const;
        void onConnectSendJoystickData(AsyncWebSocketClient* client) const;

    public:

        WebManager(AsyncWebServer& server, AsyncWebSocket& socket);
        void begin();
        void update();
        void cacheTelemetry(const TelemetryData& telemetry, State state);
        void sendTelemetry(const TelemetryData& telemetry, State state) const;
        bool hasStateChangeRequest();
        JoystickData getJoystickData() const;

};

#endif