#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class OpenAstroPowerHub {
public:
  OpenAstroPowerHub();
  void writeRelayData(int relay, int boolValue, double doubleValue, boolean (&registers)[NR_OF_RELAYS], double (&registersDouble)[NR_OF_RELAYS]);
};
