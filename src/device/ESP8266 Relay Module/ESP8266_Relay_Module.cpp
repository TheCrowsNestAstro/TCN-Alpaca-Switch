#include "device\ESP8266 Relay Module\ESP8266_Relay_Module.h"

ESP8266_Relay_Module::ESP8266_Relay_Module() {
  pinMode(RELAY_DATA_PIN, OUTPUT);
  pinMode(RELAY_LATCH_PIN, OUTPUT);
  pinMode(RELAY_CLOCK_PIN, OUTPUT);
  pinMode(RELAY_OE_PIN, OUTPUT);
}

void ESP8266_Relay_Module::writeChannelData(int channel, int channelValue, double doubleValue, int (&registers)[NR_OF_CHANNELS], double (&registersDouble)[NR_OF_CHANNELS], int channelMin, int channelMax, int channelStep) {
  Log.traceln(F("writeChannelData nr: %d %T" CR), channel, channelValue);
  registers[channel] = (channelValue == channelMax) ? 1 : 0;
  registersDouble[channel] = doubleValue;

  digitalWrite(RELAY_LATCH_PIN, LOW);
  for (int i = NR_OF_CHANNELS - 1; i >= 0; i--) {
    digitalWrite(RELAY_CLOCK_PIN, LOW);
    int val = registers[i];
    digitalWrite(RELAY_DATA_PIN, val);
    digitalWrite(RELAY_CLOCK_PIN, HIGH);
  }
  digitalWrite(RELAY_LATCH_PIN, HIGH);

  // channelStateBool[channel] = (channelValue > 0) ? 1 : 0;
  // channelStateValue[channel] = doubleValue;
}
