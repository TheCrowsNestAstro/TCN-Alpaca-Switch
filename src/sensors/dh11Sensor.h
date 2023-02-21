#pragma once

#include <Arduino.h>
#include "configuration.hpp"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ArduinoJson.h>

class DH11Sensor
{
    public:
        DH11Sensor();
        void setup();
        float getTemperature();
        float getHumidity();
        String getReading();

    private:
       
        DHT* dht;

        float t;
        float h;
};