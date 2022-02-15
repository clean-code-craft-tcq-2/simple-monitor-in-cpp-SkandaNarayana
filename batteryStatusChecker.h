#ifndef SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
#define SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H

#include <map>
#include <vector>
#include <algorithm>

#define WARNING_TOLERANCE 0.05
#define MINIMUM_TEMP 0
#define MAXIMUM_TEMP 45
#define MINIMUM_SOC 20
#define MAXIMUM_SOC 80
#define MINIMUM_CHARGE_RATE 0
#define MAXIMUM_CHARGE_RATE 0.8

enum class output_languages{
    English,
    German
};

struct Parameter{
    float value;
    std::string units;
};

float convertToCelsius(float input, std::string units);
bool isParamNearingBreachLimit(float lowerBoundary, float value, float upperBoundary);
bool isParamWithinRange(float value, float minRange, float maxRange);
bool isTemperatureWithinRange(const Parameter&);
bool isSOCWithinRange(const Parameter&);
bool isChargeRateWithinRange(const Parameter&);
bool batteryIsOk(const std::vector<Parameter>&);

#endif //SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
