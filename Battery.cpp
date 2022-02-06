//
// Created by nsk8kor on 06/02/22.
//

#include "Battery.h"

Battery::Battery(const float temp, const float soc, const float chargeRate):
                temperature(temp),
                soc(soc),
                chargeRate(chargeRate){}
float Battery::getBatteryTemperature() const{
    return temperature;
}
float Battery::getSOC() const{
    return soc;
}
float Battery::getChargeRate() const{
    return chargeRate;
}