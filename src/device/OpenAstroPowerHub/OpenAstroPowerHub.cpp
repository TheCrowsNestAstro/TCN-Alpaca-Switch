#include "device\OpenAstroPowerHub\OpenAstroPowerHub.h"

OpenAstroPowerHub::OpenAstroPowerHub() {
  for (int i = NR_OF_RELAYS - 1; i >= 0; i--) {
    pinMode(RELAY_PINS[i], OUTPUT);
  }
  
}

void OpenAstroPowerHub::writeRelayData(int relay, int boolValue, double doubleValue, boolean (&registers)[NR_OF_RELAYS], double (&registersDouble)[NR_OF_RELAYS]) {
  Log.traceln(F("writeRelayData nr: %d %T" CR), relay, boolValue);
  registers[relay] = boolValue;
  registersDouble[relay] = doubleValue;

  digitalWrite(RELAY_PINS[relay], boolValue);
}