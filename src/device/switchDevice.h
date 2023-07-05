#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoLog.h>
#include "configuration.hpp"
#include <ArduinoJson.h>
#include "struct.h"

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

        void readEEPROM();
        void writeEEPROM();

        bool getSwitchState(uint32_t id);
        String getSwitchDesc(uint32_t id);
        String getSwitchName(uint32_t id);
        double getSwitchValue(uint32_t id);
        double getSwitchMin(uint32_t id);
        double getSwitchMax(uint32_t id);
        void setSwitchState(uint32_t id, bool state);
        void setSwitchName(uint32_t id, String name);
        void setSwitchValue(uint32_t id, double value);
        double getSwitchStep(uint32_t id);

        // MQTT
        String getSwitchState();

    private:
        struct channel channels[NR_OF_CHANNELS];
#if BOARD == BOARD_OPENASTROPOWERHUB
        OpenAstroPowerHub *_device;
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
        ESP8266_Relay_Module *_device;
#endif
};
