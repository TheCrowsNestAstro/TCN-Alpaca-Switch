#pragma once

#include <Arduino.h>

struct channel {
public:
    String name;
    String desc;
    double min;
    double max;
    double step;
public:
    bool state;
    double value;
};