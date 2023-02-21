#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include "configuration.hpp"
#include "switchDevice.h"

class SwitchHandler
{
    ESP8266WebServer* _server;

    public:
        SwitchHandler(ESP8266WebServer* server);
        
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

        // Custom handlers for webpage
        bool getSwitchState(int id);
        void setSwitchState(int id, bool state);
        String getSwitchName(int id);
        void setSwitchName(int id, String name);
        void storeEEPROM();
    
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
