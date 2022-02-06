#ifndef SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
#define SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H

#include "Battery.h"

#define MINIMUM_TEMP 0
#define MAXIMUM_TEMP 45
#define MINIMUM_SOC 20
#define MAXIMUM_SOC 80
#define MINIMUM_CHARGE_RATE 0
#define MAXIMUM_CHARGE_RATE 0.8

bool batteryParameterWithinRange(const float parameter, const float minRange, const float maxRange);
bool batteryIsOk(const Battery& battery);

#endif //SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERYSTATUSCHECKER_H
