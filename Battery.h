//
// Created by nsk8kor on 06/02/22.
//

#ifndef SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERY_H
#define SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERY_H


class Battery {
    float temperature;
    float soc;
    float chargeRate;
public:
    Battery(float , float, float );
    float getBatteryTemperature() const;
    float getSOC() const;
    float getChargeRate() const;

};


#endif //SIMPLE_MONITOR_IN_CPP_SKANDANARAYANA_BATTERY_H
