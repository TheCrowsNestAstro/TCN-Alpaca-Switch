#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class OpenAstroPowerHub {
public:
  OpenAstroPowerHub();
  void writeSwitchData(int id, double value, struct channel (&channels)[NR_OF_CHANNELS]);
};
