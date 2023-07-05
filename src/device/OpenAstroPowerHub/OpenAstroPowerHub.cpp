#include "device\OpenAstroPowerHub\OpenAstroPowerHub.h"
#include "device\struct.h"

OpenAstroPowerHub::OpenAstroPowerHub() {
  for (int i = NR_OF_CHANNELS - 1; i >= 0; i--) {
    pinMode(CHANNEL_PINS[i], OUTPUT);
  }
  
}

void OpenAstroPowerHub::writeChannelData(int id, double value, struct channel (&channels)[NR_OF_CHANNELS]) {
  Log.traceln(F("writeChannelData nr: %d %T" CR), id, value);
  channels[id].value = value;
  channels[id].state = (value != 0) ? 1 : 0;

  if (channels[id].max == 1 && value == 1){
      // If channelMax = 1, assume binary output
      digitalWrite(CHANNEL_PINS[id], value);
  } else if (channels[id].max > 1){
      // Normalize value between 0-255 and output as PWM
      analogWrite(CHANNEL_PINS[id], ((value - channels[id].min) / (channels[id].max)) * 255);
  }
}