#include "device\switchDevice.h"

SwitchDevice::SwitchDevice() {

#if BOARD == BOARD_OPENASTROPOWERHUB
  _device = new OpenAstroPowerHub();
#elif BOARD == BOARD_ESP8266_RELAY_MODULE
  _device = new ESP8266_Relay_Module();
#endif
  // readEEPROM();
  // writeEEPROM(); // FIRST TIME UNCOMMENT

  for (int i = NR_OF_RELAYS - 1; i >= 0; i--) {
    registers[i] = false;
    channelNames[i] = "";
    channelDesc[i] = "";
  }
  _device->writeRelayData(0, false, 0.0, registers, registersDouble);
}

void SwitchDevice::readEEPROM()
{
    Log.traceln("readEEPROM called");
    EEPROM.begin(EEPROM_SIZE);
    int address = 0;
    for(int i = 0; i < NR_OF_RELAYS; i++)
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
    for(int i = 0; i < NR_OF_RELAYS; i++)
    {
        EEPROM.put(address, channelNames[i]);
        address += sizeof(channelNames[i]); //update address value
    }
    EEPROM.commit();
}

void SwitchDevice::writeRelayData(int relay, int boolValue, double doubleValue) {
  _device->writeRelayData(relay, boolValue, doubleValue, registers, registersDouble);
}


void SwitchDevice::setRelayState(int idx, bool state)
{
    Log.traceln(F("Relay nr: %d %T" CR), idx, state);
    
    if(state == 1)
    {
        writeRelayData(idx, true, 1.0);
    }
    else {
        writeRelayData(idx, false, 0.0);
    }
    
}

void SwitchDevice::setRelayValue(int idx, double value)
{
    Log.traceln(F("Relay nr: %d %D" CR), idx, value);
    
    if(value > 0.0)
    {
        writeRelayData(idx, true, 1.0);
        
    }
    else {
        writeRelayData(idx, false, 0.0);
    }
    
}

bool SwitchDevice::getRelayState(int idx)
{
    return registers[idx];
}

double SwitchDevice::getRelayStateDouble(int idx)
{
    return registersDouble[idx];
}

String SwitchDevice::getSwitchState()
{
    
    StaticJsonDocument<1024> doc;
    DynamicJsonDocument doc2(1024);

    JsonArray array = doc.createNestedArray("switches");

    for(int i = 0; i < NR_OF_RELAYS; i++)
    {
        doc2["name"] = channelNames[i];
        doc2["value"] = String(registers[i]);
        array.add(doc2);
    }

    String output;
    serializeJson(array, output);
    return output;
}