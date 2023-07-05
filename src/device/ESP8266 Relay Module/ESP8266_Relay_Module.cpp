#include "device\ESP8266 Relay Module\ESP8266_Relay_Module.h"
#include "device\struct.h"

ESP8266_Relay_Module::ESP8266_Relay_Module() {
  pinMode(RELAY_DATA_PIN, OUTPUT);
  pinMode(RELAY_LATCH_PIN, OUTPUT);
  pinMode(RELAY_CLOCK_PIN, OUTPUT);
  pinMode(RELAY_OE_PIN, OUTPUT);
}

void ESP8266_Relay_Module::writeChannelData(int id, double value, struct channel (&channels)[NR_OF_CHANNELS]) {
  Log.traceln(F("writeChannelData nr: %d %T" CR), id, value);
  channels[id].value = (value == channels[id].max) ? 1 : 0;
  channels[id].state = (value != 0) ? 1 : 0;

  digitalWrite(RELAY_LATCH_PIN, LOW);
  for (int i = NR_OF_CHANNELS - 1; i >= 0; i--) {
    digitalWrite(RELAY_CLOCK_PIN, LOW);
    int val = channels[i].state;
    digitalWrite(RELAY_DATA_PIN, val);
    digitalWrite(RELAY_CLOCK_PIN, HIGH);
  }
  digitalWrite(RELAY_LATCH_PIN, HIGH);
}
