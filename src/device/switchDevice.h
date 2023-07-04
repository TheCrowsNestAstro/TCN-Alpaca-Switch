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

        String channelNames[NR_OF_CHANNELS];
        String channelDesc[NR_OF_CHANNELS];
        int channelMin[NR_OF_CHANNELS];
        int channelMax[NR_OF_CHANNELS];
        int channelStep[NR_OF_CHANNELS];

        //bool channelStateBool[NR_OF_CHANNELS] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
        //double channelStateValue[NR_OF_CHANNELS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,};

        void setChannelState(int idx, bool state);
        void setChannelValue(int idx, double value);

        bool getChannelState(int idx);
        double getChannelStateDouble(int idx);

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
        void writeChannelData(int relay, int channelValue, double doubleValue);
        //uint16_t channelData = 0b0000000000000000;
        //byte channelData = B00000000;
        int registers[NR_OF_CHANNELS];
        double registersDouble[NR_OF_CHANNELS];
};
