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
        
        // ASCOM Alpaca Management API - Management Interface Methods
        void handlerMgmtVersions();
        void handlerMgmtDescription();
        void handlerMgmtConfiguredDevices();

        // ASCOM Alpaca Device API - ASCOM Methods Common To All Devices
        void handleAction();
        void handleCommandBlind();
        void handleCommandBool();
        void handleCommandString();
        void handlerConnected();
        void handlerDescriptionGet();
        void handlerDriverInfoGet();
        void handlerDriverVersionGet();
        void handlerInterfaceVersionGet();
        void handlerNameGet();
        void handlerSupportedActionsGet();

        // ASCOM Alpaca Device API - Switch Specific Methods
        void handlerDriver0Maxswitch();
        void handlerDriver0CanWrite();
        void handlerDriver0SwitchState();
        void handlerDriver0SwitchDescription();
        void handlerDriver0SwitchName();
        void handlerDriver0SwitchValue();
        void handlerDriver0MinSwitchValue();
        void handlerDriver0MaxSwitchValue();
        void handlerDriver0SwitchStep();

        // Custom handlers for webpage
        bool getSwitchState(uint32_t id);
        void setSwitchState(uint32_t id, bool state);
        String getSwitchName(uint32_t id);
        void setSwitchName(uint32_t id, String name);
        void storeEEPROM();

        // MQTT
        String getSwitchState();
    
    private:
        uint32_t transID;
        uint32_t clientID;
        uint32_t serverTransactionID = 0;
        String uniqueID = "4431281c-8560-4ad7-982f-5a6e507dda19";

        SwitchDevice* switchDevice;

        void incrementServerTransID();

        // Handler Return Methods
        void returnEmpty(String errMsg, int errNr);
        void returnStringValue(String val, String errMsg, int errNr);
        void returnBoolValue(bool val, String errMsg, int errNr);
        void returnIntValue(uint32_t val, String errMsg, int errNr);
        void returnFloatValue(float val, String errMsg, int errNr);
        void returnJsonArrayValue(JsonArray val, String errMsg, int errNr);
        void returnDoubleValue(double val, String errMsg, int errNr);

        void debugServerQuery();
        
};
