#include <iostream>
#include "Battery.h"
#include "batteryStatusChecker.h"
using namespace std;

bool batteryParameterWithinRange(const float parameter, const float minRange, const float maxRange){
    if(parameter < minRange || parameter > maxRange) return false;
    return true;
}

bool batteryIsOk(const Battery& battery) {
    const float temperature = battery.getBatteryTemperature();
    const float soc = battery.getSOC();
    const float chargeRate = battery.getChargeRate();

    bool temperatureParamWithinRange = batteryParameterWithinRange(temperature, MINIMUM_TEMP, MAXIMUM_TEMP);
    bool socParamWithinRange = batteryParameterWithinRange(soc, MINIMUM_SOC, MAXIMUM_SOC);
    bool chargeRateParamWithinRange = batteryParameterWithinRange(chargeRate, MINIMUM_CHARGE_RATE, MAXIMUM_CHARGE_RATE);
    return (temperatureParamWithinRange && socParamWithinRange && chargeRateParamWithinRange);
}

