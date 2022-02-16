#include "batteryStatusChecker.h"
#include <cassert>

void test_batteryIsOK(){
    const Parameter temperature1 = {44, ParameterUnits::Celsius};
    const Parameter soc1 = {50, ParameterUnits::Percentage};
    const Parameter chargeRate1 = {0.5, ParameterUnits::Ah};
    const Parameter temperature2 = {55, ParameterUnits::Celsius};
    const Parameter soc2 = {90, ParameterUnits::Percentage};
    const Parameter chargeRate2 = {1.0, ParameterUnits::Ah};

    const std::vector<Parameter> parameterCollection1 = { temperature1, soc1, chargeRate1};
    const std::vector<Parameter> parameterCollection2 = { temperature2, soc2, chargeRate2};
    assert(batteryIsOk(parameterCollection1) == true);
    assert(batteryIsOk(parameterCollection2) == false);
}
void test_batteryParameterWithinRange(){
    assert(isParamWithinRange(5, 10, 20) == false);
    assert(isParamWithinRange(15, 10, 20) == true);
}

void test_isTemperatureWithinRange(){
    const Parameter temperature1 = {35, ParameterUnits::Fahrenheit};
    const Parameter temperature2 = {55, ParameterUnits::Celsius};
    assert(isTemperatureWithinRange(temperature1) == true);
    assert(isTemperatureWithinRange(temperature2) == false);
}

void test_isSOCWithinRange(){
    const Parameter soc1 = {70, ParameterUnits::Percentage};
    const Parameter soc2 = {90, ParameterUnits::Percentage};
    assert(isSOCWithinRange(soc1) == true);
    assert(isSOCWithinRange(soc2) == false);
}

void test_isChargeRateWithinRange(){
    const Parameter chargeRate1 = {0.7, ParameterUnits::Ah};
    const Parameter chargeRate2 = {0.9, ParameterUnits::Ah};
    assert(isChargeRateWithinRange(chargeRate1) == true);
    assert(isChargeRateWithinRange(chargeRate2) == false);
}
void test_isParamNearingBreachLimit(){
    assert(isParamNearingBreachLimit(5, 6, 10) == true);
    assert(isParamNearingBreachLimit(5, 11, 10) == false);
}

void test_convertToCelsius(){
    assert(convertToCelsius(68, ParameterUnits::Fahrenheit) == 20);
    assert(convertToCelsius(20, ParameterUnits::Celsius) == 20);
}

int main() {
    test_batteryIsOK();
    test_isTemperatureWithinRange();
    test_isSOCWithinRange();
    test_isChargeRateWithinRange();
    test_batteryParameterWithinRange();
    test_isParamNearingBreachLimit();
    test_convertToCelsius();
}