#include "device\ESP8266 Relay Module\ESP8266_Relay_Module.h"

ESP8266_Relay_Module::ESP8266_Relay_Module() {
  pinMode(RELAY_DATA_PIN, OUTPUT);
  pinMode(RELAY_LATCH_PIN, OUTPUT);
  pinMode(RELAY_CLOCK_PIN, OUTPUT);
  pinMode(RELAY_OE_PIN, OUTPUT);
}

void ESP8266_Relay_Module::writeRelayData(
    int relay, int boolValue, double doubleValue,
    boolean (&registers)[NR_OF_RELAYS],
    double (&registersDouble)[NR_OF_RELAYS]) {
  Log.traceln(F("writeRelayData nr: %d %T" CR), relay, boolValue);
  registers[relay] = boolValue;
  registersDouble[relay] = doubleValue;

  digitalWrite(RELAY_LATCH_PIN, LOW);
  for (int i = NR_OF_RELAYS - 1; i >= 0; i--) {
    digitalWrite(RELAY_CLOCK_PIN, LOW);
    int val = registers[i];
    digitalWrite(RELAY_DATA_PIN, val);
    digitalWrite(RELAY_CLOCK_PIN, HIGH);
  }
  digitalWrite(RELAY_LATCH_PIN, HIGH);

  // relayStateBool[relay] = boolValue;
  // relayStateValue[relay] = doubleValue;
}
