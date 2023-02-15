#include "sensors/ina260Sensor.h"

INA260Sensor::INA260Sensor()
{
    found = false;
    current = 0.0f;
    voltage = 0.0f;
    power = 0.0f;
}

void INA260Sensor::setup()
{
    ina260 = Adafruit_INA260();

    if (!ina260.begin()) {
        Log.errorln("%S" CR, "Couldn't find INA260 chip");
    }
    else {
        Log.traceln("%S" CR, "Found INA260 chip");
        found = true;
    }
}

String INA260Sensor::getReading()
{
    if(found)
    {
        current = ina260.readCurrent();
        voltage = ina260.readBusVoltage();
        power = ina260.readPower();
    }

    DynamicJsonDocument doc(1024);
    doc["sensor"] = "psu_24v";
    doc["current"] = current;
    doc["voltage"] = voltage;
    doc["power"] = power;

    String output;
    serializeJson(doc, output);
    return output;
    
}