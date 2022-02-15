#include "batteryStatusChecker.h"
#include <cassert>

void test_batteryIsOK(){
    const Parameter temperature1 = {15, "celsius", 0, 45};
    const Parameter soc1 = {50, "units", 20, 80};
    const Parameter chargeRate1 = {0.5, "percent", 0, 0.8};
    const Parameter temperature2 = {55, "celsius", 0, 45};
    const Parameter soc2 = {90, "units", 20, 80};
    const Parameter chargeRate2 = {1.0, "percent", 0, 0.8};

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
    Parameter temperature1 = {25, "celsius", 0, 45};
    Parameter temperature2 = {55, "celsius", 0, 45};
    assert(isTemperatureWithinRange(temperature1) == true);
    assert(isTemperatureWithinRange(temperature2) == false);
}

void test_isSOCWithinRange(){
    Parameter soc1 = {70, "units", 20, 80};
    Parameter soc2 = {90, "units", 20, 80};
    assert(isSOCWithinRange(soc1) == true);
    assert(isSOCWithinRange(soc2) == false);
}

void test_isChargeRateWithinRange(){
    Parameter chargeRate1 = {0.7, "percent", 0, 0.8};
    Parameter chargeRate2 = {0.9, "percent", 0, 0.8};
    assert(isSOCWithinRange(chargeRate1) == true);
    assert(isSOCWithinRange(chargeRate2) == false);
}

int main() {
    test_batteryIsOK();
    test_isTemperatureWithinRange();
    test_isSOCWithinRange();
    test_isChargeRateWithinRange();
    test_batteryParameterWithinRange();
}