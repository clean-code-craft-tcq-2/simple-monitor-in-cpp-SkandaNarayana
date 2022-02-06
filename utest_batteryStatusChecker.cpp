#include "batteryStatusChecker.h"
#include <cassert>
#include <array>

void test_batteryIsOK(const Battery &battery, const bool expectedValue){
    assert(batteryIsOk(battery) == expectedValue);
}
void test_batteryParameterWithinRange(const float parameter, const float minRange, const float maxRange,
                                      const bool expectedValue){
    assert(batteryParameterWithinRange(parameter, minRange, maxRange) == expectedValue);
}

int main() {
    Battery battery1(25, 70, 0.7);
    Battery battery2(50, 85, 0);

    test_batteryIsOK(battery1, true);
    test_batteryIsOK(battery2, false);

    test_batteryParameterWithinRange(25, MINIMUM_TEMP, MAXIMUM_TEMP, true);
    test_batteryParameterWithinRange(85, MINIMUM_TEMP, MAXIMUM_TEMP, false);
    test_batteryParameterWithinRange(25, MINIMUM_SOC, MAXIMUM_SOC, true);
    test_batteryParameterWithinRange(85, MINIMUM_SOC, MAXIMUM_SOC, false);
    test_batteryParameterWithinRange(0.8, MINIMUM_CHARGE_RATE, MAXIMUM_CHARGE_RATE, true);
    test_batteryParameterWithinRange(0.9, MINIMUM_CHARGE_RATE, MAXIMUM_CHARGE_RATE, false);
}