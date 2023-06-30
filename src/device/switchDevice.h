#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoLog.h>
#include "configuration.hpp"
#include <ArduinoJson.h>

#if BOARD == BOARD_OPENASTROPOWERHUB
#include "device\OpenAstroPowerHub\OpenAstroPowerHub.h"
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
#include "device\ESP8266 Relay Module\ESP8266_Relay_Module.h"
#endif

class SwitchDevice
{
    public:
        SwitchDevice();

        bool connected = false;
        String uniqueID = "";

        String channelNames[NR_OF_RELAYS] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
        String channelDesc[NR_OF_RELAYS] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
        //bool relayStateBool[NR_OF_RELAYS] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
        //double relayStateValue[NR_OF_RELAYS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,};

        void setRelayState(int idx, bool state);
        void setRelayValue(int idx, double value);

        bool getRelayState(int idx);
        double getRelayStateDouble(int idx);

        void readEEPROM();
        void writeEEPROM();

        // MQTT
        String getSwitchState();

    private:
      #if BOARD == BOARD_OPENASTROPOWERHUB
        OpenAstroPowerHub *_device;
      #elif BOARD == BOARD_ESP8266_RELAY_MODULE
        ESP8266_Relay_Module *_device;
      #endif
        void writeRelayData(int relay, int boolValue, double doubleValue);
        //uint16_t relayData = 0b0000000000000000;
        //byte relayData = B00000000;
        boolean registers[NR_OF_RELAYS];
        double registersDouble[NR_OF_RELAYS];
};
