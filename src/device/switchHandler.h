#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <WiFi.h>
#include <HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include "configuration.hpp"
#include "switchDevice.h"

class SwitchHandler
{
    WebServer* _server;

    public:
        SwitchHandler(WebServer* server);
        
        void handlerMgmtVersions();
        void handlerMgmtDescription();
        void handlerMgmtConfiguredDevices();

        void handlerConnected();
        void handlerDescriptionGet();
        void handlerDriverInfoGet();
        void handlerDriverVersionGet();
        void handlerInterfaceVersionGet();
        void handlerNameGet();
        void handlerSupportedActionsGet();

        void handleAction();
        void handleCommandBlind();
        void handleCommandBool();
        void handleCommandString();

        void handlerDriver0Maxswitch();
        void handlerDriver0CanWrite();
        void handlerDriver0SwitchDescription();
        void handlerDriver0SwitchState();
        void handlerDriver0SwitchName();
        void handlerDriver0SwitchValue();
        void handlerDriver0MinSwitchValue();
        void handlerDriver0MaxSwitchValue();
        void handlerDriver0SwitchStep();
    
    private:
        uint32_t transID;
        uint32_t clientID;
        uint32_t serverTransactionID = 0;
        String uniqueID = "4431281c-8560-4ad7-982f-5a6e507dda19";

        SwitchDevice* switchDevice;

        void incrementServerTransID();

        void returnEmpty(String errMsg, int errNr);

        void returnStringValue(String val, String errMsg, int errNr);
        void returnBoolValue(bool val, String errMsg, int errNr);
        void returnIntValue(int val, String errMsg, int errNr);
        void returnFloatValue(float val, String errMsg, int errNr);
        void returnJsonArrayValue(JsonArray val, String errMsg, int errNr);
        void returnDoubleValue(double val, String errMsg, int errNr);

        void debugServerQuery();
        
};
