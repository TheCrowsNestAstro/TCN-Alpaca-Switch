#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class OpenAstroPowerHub {
public:
  OpenAstroPowerHub();
  void writeChannelData(int channel, int channelValue, double doubleValue, int (&registers)[NR_OF_CHANNELS], double (&registersDouble)[NR_OF_CHANNELS], int channelMin, int channelMax, int channelStep);
};
