#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class OpenAstroPowerHub {
public:
  OpenAstroPowerHub();
  void writeRelayData(int relay, int boolValue, double doubleValue, boolean (&registers)[NR_OF_RELAYS], double (&registersDouble)[NR_OF_RELAYS]);
  // uint16_t relayData = 0b0000000000000000;
  // byte relayData = B00000000;
};
