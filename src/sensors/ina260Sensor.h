#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include "configuration.hpp"

#include <Adafruit_Sensor.h>
#include <Adafruit_INA260.h>
#include <ArduinoJson.h>

class INA260Sensor
{
    public:
        INA260Sensor();
        void setup();
        String getReading();

    private:
        Adafruit_INA260 ina260;
        bool found;

        float current;
        float voltage;
        float power;
};