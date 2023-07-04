#include "device\OpenAstroPowerHub\OpenAstroPowerHub.h"

OpenAstroPowerHub::OpenAstroPowerHub() {
  for (int i = NR_OF_CHANNELS - 1; i >= 0; i--) {
    pinMode(CHANNEL_PINS[i], OUTPUT);
  }
  
}

void OpenAstroPowerHub::writeChannelData(int channel, int channelValue, double doubleValue, int (&registers)[NR_OF_CHANNELS], double (&registersDouble)[NR_OF_CHANNELS], int channelMin, int channelMax, int channelStep) {
  Log.traceln(F("writeChannelData nr: %d %T" CR), channel, channelValue);

  if (channelMax == 1 && channelValue == 1){
      // If channelMax = 1, assume binary output
      digitalWrite(CHANNEL_PINS[channel], channelValue);
  } else if (channelMax > 1){
      // Normalize channelValue between 0-255 and output as PWM
      analogWrite(CHANNEL_PINS[channel], ((channelValue - channelMin) / (channelMax)) * 255);
  }
  registers[channel] = channelValue;
  registersDouble[channel] = doubleValue;
}