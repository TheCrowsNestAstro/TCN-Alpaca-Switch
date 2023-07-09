#include "device\switchDevice.h"

SwitchDevice::SwitchDevice() {

#if BOARD == BOARD_OPENASTROPOWERHUB
  _device = new OpenAstroPowerHub();
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
  _device = new ESP8266_Relay_Module();
#endif
  // readEEPROM();
  // writeEEPROM(); // FIRST TIME UNCOMMENT

  for (int id = NR_OF_CHANNELS - 1; id >= 0; id--) {
    channels[id].value = 0;
    channels[id].name = "";
    channels[id].desc = "";
    channels[id].min = channelMinDefault[id];
    channels[id].max = channelMaxDefault[id];
    channels[id].step = channelStepDefault[id];
    _device->writeSwitchData(0, 0.0, channels);
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
        channels[i].name = channelName;
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
        EEPROM.put(address, channels[i].name);
        address += sizeof(channels[i].name); //update address value
    }
    EEPROM.commit();
}

bool SwitchDevice::getSwitchState(uint32_t id)
{
    return channels[id].state;
}

String SwitchDevice::getSwitchDesc(uint32_t id)
{
    return channels[id].desc;
}

String SwitchDevice::getSwitchName(uint32_t id)
{
    return channels[id].name;
}

double SwitchDevice::getSwitchValue(uint32_t id)
{
    return channels[id].value;
}

double SwitchDevice::getSwitchMin(uint32_t id)
{
    return channels[id].min;
}

double SwitchDevice::getSwitchMax(uint32_t id)
{
    return channels[id].max;
}

void SwitchDevice::setSwitchState(uint32_t id, bool state)
{
    Log.traceln(F("Switch ID: %d State: %s" CR), id, state ? "True" : "False");
    
    if(state == true)
    {
        _device->writeSwitchData(id, channels[id].max, channels);
    }
    else {
        _device->writeSwitchData(id, 0, channels);
    }
}

void SwitchDevice::setSwitchName(uint32_t id, String name)
{
      channels[id].name = name;
}

void SwitchDevice::setSwitchValue(uint32_t id, double value)
{
    Log.traceln(F("Channel nr: %d %D" CR), id, value);
    _device->writeSwitchData(id, value, channels);  
}

double SwitchDevice::getSwitchStep(uint32_t id)
{
    return channels[id].step;
}

////////////////////////////////
// Custom handlers for webpage//
////////////////////////////////
String SwitchDevice::getSwitchState()
{
    
    StaticJsonDocument<1024> doc;
    DynamicJsonDocument doc2(1024);

    JsonArray array = doc.createNestedArray("switches");

    for(int id = 0; id < NR_OF_CHANNELS; id++)
    {
        doc2["name"] = channels[id].name;
        doc2["value"] = String(channels[id].value);
        array.add(doc2);
    }

    String output;
    serializeJson(array, output);
    return output;
}