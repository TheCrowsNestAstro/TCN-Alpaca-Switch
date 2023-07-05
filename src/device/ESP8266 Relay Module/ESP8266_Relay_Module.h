#pragma once

#include "configuration.hpp"
#include <Arduino.h>
#include <ArduinoLog.h>

class ESP8266_Relay_Module {
public:
  ESP8266_Relay_Module();
  void writeChannelData(int id, double value, struct channel (&channels)[NR_OF_CHANNELS]);
};
