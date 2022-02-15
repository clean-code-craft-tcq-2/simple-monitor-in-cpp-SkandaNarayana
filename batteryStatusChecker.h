#ifndef SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
#define SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H

#include "Battery.h"
#include <map>
#include <vector>
#include <algorithm>

#define WARNING_TOLERANCE 0.05

enum class output_languages{
    English,
    German
};

struct Parameter{
    float value;
    std::string units;
    float lowerLimit;
    float upperLimit;
};


bool isParamWithinRange(float value, float minRange, float maxRange);
bool isTemperatureWithinRange(const Parameter&);
bool isSOCWithinRange(const Parameter&);
bool isChargeRateWithinRange(const Parameter&);
bool batteryIsOk(const std::vector<Parameter>&);

#endif //SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
