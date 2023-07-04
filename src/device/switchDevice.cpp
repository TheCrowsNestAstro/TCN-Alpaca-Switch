#include "device\switchDevice.h"

SwitchDevice::SwitchDevice() {

#if BOARD == BOARD_OPENASTROPOWERHUB
  _device = new OpenAstroPowerHub();
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
  _device = new ESP8266_Relay_Module();
#endif
  // readEEPROM();
  // writeEEPROM(); // FIRST TIME UNCOMMENT

  for (int channel = NR_OF_CHANNELS - 1; channel >= 0; channel--) {
    registers[channel] = 0;
    channelNames[channel] = "";
    channelDesc[channel] = "";
    channelMin[channel] = channelMinDefault[channel];
    channelMax[channel] = channelMaxDefault[channel];
    channelStep[channel] = channelStepDefault[channel];
    _device->writeChannelData(0, 0, 0.0, registers, registersDouble, channelMin[channel], channelMax[channel], channelStep[channel]);
  }
}

void SwitchDevice::readEEPROM()
{
    Log.traceln("readEEPROM called");
    EEPROM.begin(EEPROM_SIZE);
    int address = 0;
    for(int i = 0; i < NR_OF_CHANNELS; i++)
    {
        String channelName;
        EEPROM.get(address, channelName);
        Serial.println(channelName);
        channelNames[i] = channelName;
        address += sizeof(channelName); //update address value
    }
    EEPROM.end();
}

void SwitchDevice::writeEEPROM()
{
    EEPROM.begin(EEPROM_SIZE);
    int address = 0;
    for(int i = 0; i < NR_OF_CHANNELS; i++)
    {
        EEPROM.put(address, channelNames[i]);
        address += sizeof(channelNames[i]); //update address value
    }
    EEPROM.commit();
}

void SwitchDevice::writeChannelData(int channel, int channelValue, double doubleValue) {
  _device->writeChannelData(channel, channelValue, doubleValue, registers, registersDouble, channelMin[channel], channelMax[channel], channelStep[channel]);
}


void SwitchDevice::setChannelState(int idx, bool state)
{
    Log.traceln(F("Channel nr: %d %T" CR), idx, state);
    
    if(state == 1)
    {
        writeChannelData(idx, true, 1.0);
    }
    else {
        writeChannelData(idx, false, 0.0);
    }
    
}

void SwitchDevice::setChannelValue(int idx, double value)
{
    Log.traceln(F("Channel nr: %d %D" CR), idx, value);
    
    if(value > 0.0)
    {
        writeChannelData(idx, true, 1.0);
        
    }
    else {
        writeChannelData(idx, false, 0.0);
    }
    
}

bool SwitchDevice::getChannelState(int idx)
{
    return registers[idx];
}

double SwitchDevice::getChannelStateDouble(int idx)
{
    return registersDouble[idx];
}

String SwitchDevice::getSwitchState()
{
    
    StaticJsonDocument<1024> doc;
    DynamicJsonDocument doc2(1024);

    JsonArray array = doc.createNestedArray("switches");

    for(int i = 0; i < NR_OF_CHANNELS; i++)
    {
        doc2["name"] = channelNames[i];
        doc2["value"] = String(registers[i]);
        array.add(doc2);
    }

    String output;
    serializeJson(array, output);
    return output;
}