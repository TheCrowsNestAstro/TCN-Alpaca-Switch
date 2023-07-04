#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class ESP8266_Relay_Module {
public:
  ESP8266_Relay_Module();
  void writeChannelData(int channel, int channelValue, double doubleValue, int (&registers)[NR_OF_CHANNELS], double (&registersDouble)[NR_OF_CHANNELS], int channelMin, int channelMax, int channelStep);
};
