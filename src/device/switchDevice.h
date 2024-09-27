#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include "configuration.hpp"

class SwitchDevice
{
    public:
        SwitchDevice();

        bool connected = false;
        String uniqueID = "";

        bool relayState0 = false;
        bool relayState1 = false;
        bool relayState2 = false;
        bool relayState3 = false;
        bool relayState4 = false;
        bool relayState5 = false;
        bool relayState6 = false;
        bool relayState7 = false;

        double relayValue0 = 0.0;
        double relayValue1 = 0.0;
        double relayValue2 = 0.0;
        double relayValue3 = 0.0;
        double relayValue4 = 0.0;
        double relayValue5 = 0.0;
        double relayValue6 = 0.0;
        double relayValue7 = 0.0;

        bool relayStateBool[8] = {false, false, false, false, false, false, false};
        double relayStateValue[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

        void setRelayState(int relayNr, bool state);
        void setRelayValue(int relayNr, double value);

    private:
        void writeRelayData(int relay, int boolValue, double doubleValue);
        byte relayData = B00000000;
};
