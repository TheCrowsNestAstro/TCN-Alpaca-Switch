#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoLog.h>
#include "configuration.hpp"

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

    private:
        void writeRelayData(int relay, int boolValue, double doubleValue);
        //uint16_t relayData = 0b0000000000000000;
        //byte relayData = B00000000;
        boolean registers[NR_OF_RELAYS];
        double registersDouble[NR_OF_RELAYS];
};
