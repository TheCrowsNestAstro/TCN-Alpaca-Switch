#include "dh11Sensor.h"

DH11Sensor::DH11Sensor()
{
    t = 0.0f;
    h = 0.0f;
}

void DH11Sensor::setup()
{
    DH11Sensor::dht = new DHT(DHT_PIN, DHT11);
}

float DH11Sensor::getTemperature()
{
    float tRead = dht->readTemperature();
    if (!isnan(tRead))
    {
        t = tRead;
    }
    return t;
}

float DH11Sensor::getHumidity()
{
    float hRead = dht->readHumidity();
    if (!isnan(hRead))
    {
        t = hRead;
    }
    return t;
}

String DH11Sensor::getReading()
{
    float tR = getTemperature();
    float hR = getHumidity();
    
    DynamicJsonDocument doc(1024);
    doc["sensor"] = "SwitchTemperature";
    doc["temperature"] = tR;
    doc["humidity"] = hR;

    String output;
    serializeJson(doc, output);
    return output;
    
}