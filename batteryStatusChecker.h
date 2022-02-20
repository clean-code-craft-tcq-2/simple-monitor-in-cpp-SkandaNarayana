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
#define WARNING_FOR_TEMPERATURE 1
#define WARNING_FOR_SOC 1
#define WARNING_FOR_CHARGERATE 1

enum class Available_language{
    English,
    German
};
enum class ParameterUnits{
    Celsius,
    Fahrenheit,
    Percentage,
    Ah

};

struct Parameter{
    float value;
    ParameterUnits units;
    std::string paramName;
    bool earlyWarningNeeded;
};


float convertToCelsius(float input, ParameterUnits unit);
bool isParamNearingBreachLimit(float lowerBoundary, float value, float upperBoundary);
bool isParamWithinRange(float value, float minRange, float maxRange);
bool isTemperatureWithinRange(Parameter&);
bool isSOCWithinRange(Parameter&);
bool isChargeRateWithinRange(Parameter&);
bool batteryIsOk(std::vector<Parameter>&);

#endif //SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
