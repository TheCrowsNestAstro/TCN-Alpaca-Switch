#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class ESP8266_Relay_Module {
public:
  ESP8266_Relay_Module();
  void writeRelayData(int relay, int boolValue, double doubleValue, boolean (&registers)[NR_OF_RELAYS], double (&registersDouble)[NR_OF_RELAYS]);
};
