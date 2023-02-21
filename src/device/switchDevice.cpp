#include "device\switchDevice.h"

SwitchDevice::SwitchDevice()
{
    pinMode(RELAY_DATA_PIN, OUTPUT);
    pinMode(RELAY_LATCH_PIN, OUTPUT);
    pinMode(RELAY_CLOCK_PIN, OUTPUT);
    pinMode(RELAY_OE_PIN, OUTPUT);

    //readEEPROM();
    
    for(int i = NR_OF_RELAYS-1; i >=  0; i--){
        registers[i] = false;
    }
    writeRelayData(0, false, 0.0);
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

void SwitchDevice::writeRelayData(int relay, int boolValue, double doubleValue)
{
    Log.traceln(F("writeRelayData nr: %d %T" CR), relay, boolValue);
    registers[relay] = boolValue;
    registersDouble[relay] = doubleValue;
    
    digitalWrite(RELAY_LATCH_PIN, LOW);
    for(int i = NR_OF_RELAYS-1; i >=  0; i--)
    {
        digitalWrite(RELAY_CLOCK_PIN, LOW); int val = registers[i];
        digitalWrite(RELAY_DATA_PIN, val);
        digitalWrite(RELAY_CLOCK_PIN, HIGH);
    }
    digitalWrite(RELAY_LATCH_PIN, HIGH);
    
    //relayStateBool[relay] = boolValue;
    //relayStateValue[relay] = doubleValue;
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