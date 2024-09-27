#include "device\switchDevice.h"

SwitchDevice::SwitchDevice()
{
    pinMode(RELAY_DATA_PIN, OUTPUT);
    pinMode(RELAY_LATCH_PIN, OUTPUT);
    pinMode(RELAY_CLOCK_PIN, OUTPUT);

    writeRelayData(0, 0, 0.0);

    

#ifdef RELAY_PIN_0
    pinMode(RELAY_PIN_0, OUTPUT);
#endif
#ifdef RELAY_PIN_1
    pinMode(RELAY_PIN_1, OUTPUT);
#endif
#ifdef RELAY_PIN_2
    pinMode(RELAY_PIN_2, OUTPUT);
#endif
#ifdef RELAY_PIN_3
    pinMode(RELAY_PIN_3, OUTPUT);
#endif
#ifdef RELAY_PIN_4
    pinMode(RELAY_PIN_4, OUTPUT);
#endif
#ifdef RELAY_PIN_5
    pinMode(RELAY_PIN_5, OUTPUT);
#endif
#ifdef RELAY_PIN_6
    pinMode(RELAY_PIN_6, OUTPUT);
#endif
#ifdef RELAY_PIN_7
    pinMode(RELAY_PIN_7, OUTPUT);
#endif
}

void SwitchDevice::writeRelayData(int relay, int boolValue, double doubleValue)
{
    #if USE_BITSHIFT == 1
    bitWrite(relayData, relay, boolValue);
    digitalWrite(RELAY_LATCH_PIN, LOW);
    shiftOut(RELAY_DATA_PIN, RELAY_CLOCK_PIN, MSBFIRST, relayData);
    digitalWrite(RELAY_LATCH_PIN, HIGH);
    #endif

    switch (relay)
    {
    case 0:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_0, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_0, LOW);
        }
        break;
    case 1:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_1, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_1, LOW);
        }
        break;
    case 2:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_2, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_2, LOW);
        }
        break;
    case 3:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_3, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_3, LOW);
        }
        break;
    case 4:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_4, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_4, LOW);
        }
        break;
    case 5:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_5, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_5, LOW);
        }
        break;
    case 6:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_6, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_6, LOW);
        }
        break;
    case 7:
        if (boolValue == true)
        {
            digitalWrite(RELAY_PIN_7, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN_7, LOW);
        }
        break;
    default:
        break;
    }

    relayStateBool[relay] = boolValue;
    relayStateValue[relay] = doubleValue;
}


void SwitchDevice::setRelayState(int relayNr, bool state)
{
    Log.traceln(F("Relay nr: %d %T" CR), relayNr, state);

    if(state == 1)
    {
        writeRelayData(relayNr, true, 1.0);
    }
    else {
        writeRelayData(relayNr, false, 0.0);
    }

    /*
    switch (relayNr)
    {
    case 0:
        if (state == true)
        {
            writeRelayData(0, 1, 1.0);
        }
        else
        {
            writeRelayData(0, 0);
            // digitalWrite(RELAY_PIN_0, LOW);
            relayState0 = false;
            relayValue0 = 0.0;
        }
        break;
    case 1:
        if (state == true)
        {
            writeRelayData(1, 1);
            //digitalWrite(RELAY_PIN_1, HIGH);
            relayState1 = true;
            relayValue1 = 1.0;
        }
        else
        {
            writeRelayData(1, 0);
            //digitalWrite(RELAY_PIN_1, LOW);
            relayState1 = false;
            relayValue1 = 0.0;
        }
        break;
    case 2:
        if (state == true)
        {
            writeRelayData(2, 1);
            // digitalWrite(RELAY_PIN_2, HIGH);
            relayState2 = true;
            relayValue2 = 1.0;
        }
        else
        {
            writeRelayData(2, 0);
            // digitalWrite(RELAY_PIN_2, LOW);
            relayState2 = false;
            relayValue2 = 0.0;
        }
        break;
    case 3:
        if (state == true)
        {
            writeRelayData(3, 1);
            // digitalWrite(RELAY_PIN_3, HIGH);
            relayState3 = true;
            relayValue3 = 1.0;
        }
        else
        {
            writeRelayData(3, 0);
            // digitalWrite(RELAY_PIN_3, LOW);
            relayState3 = false;
            relayValue3 = 1.0;
        }
        break;
    case 4:
        if (state == true)
        {
            writeRelayData(4, 1);
            // digitalWrite(RELAY_PIN_4, HIGH);
            relayState4 = true;
            relayValue4 = 1.0;
        }
        else
        {
            writeRelayData(4, 0);
            // digitalWrite(RELAY_PIN_4, LOW);
            relayState4 = false;
            relayValue4 = 1.0;
        }
        break;
    case 5:
        if (state == true)
        {
            writeRelayData(5, 1);
            // digitalWrite(RELAY_PIN_5, HIGH);
            relayState5 = true;
            relayValue5 = 1.0;
        }
        else
        {
            writeRelayData(5, 0) ;
            // digitalWrite(RELAY_PIN_5, LOW);
            relayState5 = false;
            relayValue5 = 1.0;
        }
        break;
    #ifdef R6
    case 6:
        if (state == true)
        {
            writeRelayData(6, 1);
            // digitalWrite(RELAY_PIN_6, HIGH);
            relayState6 = true;
            relayValue6 = 1.0;
        }
        else
        {
            writeRelayData(6, 0);
            // digitalWrite(RELAY_PIN_6, LOW);
            relayState6 = false;
            relayValue6 = 1.0;
        }
        break;
    #endif

    #ifdef R7
    case 7:
        if (state == true)
        {
            writeRelayData(7, 1);
            // digitalWrite(RELAY_PIN_7, HIGH);
            relayState7 = true;
            relayValue7 = 1.0;
        }
        else
        {
            writeRelayData(7, 0);
            // digitalWrite(RELAY_PIN_7, LOW);
            relayState7 = false;
            relayValue7 = 1.0;
        }
        break;
    #endif

    default:
        break;
    }
    */
}

void SwitchDevice::setRelayValue(int relayNr, double value)
{
    Log.traceln(F("Relay nr: %d %D" CR), relayNr, value);
    if(value > 0.0)
    {
        writeRelayData(relayNr, true, 1.0);
    }
    else {
        writeRelayData(relayNr, false, 0.0);
    }
    
    /*
    switch (relayNr)
    {
    case 0:
        if (value == 1.0)
        {
            writeRelayData(0, 1);
            // digitalWrite(RELAY_PIN_0, HIGH);
            relayState0 = true;
            relayValue0 = value;
        }
        else
        {
            writeRelayData(0, 0);
            // digitalWrite(RELAY_PIN_0, LOW);
            relayState0 = false;
            relayValue0 = value;
        }
        break;
    case 1:
        if (value == 1.0)
        {
            writeRelayData(1, 1);
            // digitalWrite(RELAY_PIN_1, HIGH);
            relayState1 = true;
            relayValue1 = value;
        }
        else
        {
            writeRelayData(1, 0);
            // digitalWrite(RELAY_PIN_1, LOW);
            relayState1 = false;
            relayValue1 = value;
        }
        break;
    case 2:
        if (value == 1.0)
        {
            writeRelayData(2, 1);
            // digitalWrite(RELAY_PIN_2, HIGH);
            relayState2 = true;
            relayValue2 = value;
        }
        else
        {
            writeRelayData(2, 0);
            // digitalWrite(RELAY_PIN_2, LOW);
            relayState2 = false;
            relayValue2 = value;
        }
        break;
    case 3:
        if (value == 1.0)
        {
            writeRelayData(3, 1);
            // digitalWrite(RELAY_PIN_3, HIGH);
            relayState3 = true;
            relayValue3 = value;
        }
        else
        {
            writeRelayData(3, 0);
            // digitalWrite(RELAY_PIN_3, LOW);
            relayState3 = false;
            relayValue3 = value;
        }
        break;
    case 4:
        if (value == 1.0)
        {
            writeRelayData(4, 1);
            // digitalWrite(RELAY_PIN_4, HIGH);
            relayState4 = true;
            relayValue4 = value;
        }
        else
        {
            writeRelayData(4, 0);
            // digitalWrite(RELAY_PIN_4, LOW);
            relayState4 = false;
            relayValue4 = value;
        }
        break;
    case 5:
        if (value == 1.0)
        {
            writeRelayData(5, 1);
            // digitalWrite(RELAY_PIN_5, HIGH);
            relayState5 = true;
            relayValue5 = value;
        }
        else
        {
            writeRelayData(5, 0);
            // digitalWrite(RELAY_PIN_5, LOW);
            relayState5 = false;
            relayValue5 = value;
        }
        break;
#ifdef R6
    case 6:
        if (value == 1.0)
        {
            writeRelayData(6, 1);
            // digitalWrite(RELAY_PIN_6, HIGH);
            relayState6 = true;
            relayValue6 = value;
        }
        else
        {
            writeRelayData(6, 0);
            // digitalWrite(RELAY_PIN_6, LOW);
            relayState6 = false;
            relayValue6 = value;
        }
        break;
#endif

#ifdef R7
    case 7:
        if (value == 1.0)
        {
            writeRelayData(7, 1);
            // digitalWrite(RELAY_PIN_7, HIGH);
            relayState7 = true;
            relayValue7 = value;
        }
        else
        {
            writeRelayData(7, 0);
            // digitalWrite(RELAY_PIN_7, LOW);
            relayState7 = false;
            relayValue7 = value;
        }
        break;
#endif
    default:
        break;
    }
    */
}