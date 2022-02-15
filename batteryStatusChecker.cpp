#include <iostream>
#include "batteryStatusChecker.h"

output_languages selected_language = output_languages::German;

using warning_list = std::map<std::string, std::string>;

warning_list english_output_msg = {
        {"TEMP_OUT_OF_RANGE" ,"Temperature out of range"},
        {"SOC_OUT_OF_RANGE","soc out of range"},
        {"CHARGE_RATE_OUT_OF_RANGE","chargeRate out of range"}
};

warning_list german_output_msg = {
        {"TEMP_OUT_OF_RANGE" ,"Temperatur außerhalb des Bereichs"},
        {"SOC_OUT_OF_RANGE","soc außer Reichweite"},
        {"CHARGE_RATE_OUT_OF_RANGE","Laderate außerhalb des Bereichs"}
};

std::map<output_languages, warning_list> errorMsgsCollection = {
        {output_languages::English, english_output_msg},
        {output_languages::German,  german_output_msg}
};

void reportEarlyWarning(const float value, const float minRange, const float maxRange){
    const auto warningToleranceNumber = maxRange * WARNING_TOLERANCE;
    const auto lowerLimitTolerance = minRange + warningToleranceNumber;
    const auto upperLimitTolerance = maxRange - warningToleranceNumber;
    if(lowerLimitTolerance >= value && value >= minRange){
        std::cout << "Warning!! Parameter nearing lower limit" << std::endl;
        std::cout << lowerLimitTolerance << " " << value <<" " <<minRange << std::endl;
    }
    else if (upperLimitTolerance <= value && value <= maxRange){
        std::cout <<"Warning!! Parameter nearing upper limit" <<std::endl;
        std::cout << upperLimitTolerance << " " << value << maxRange<< " " << std::endl;
    }
}

bool isParamWithinRange(float value, float minRange, float maxRange){
    reportEarlyWarning(value, minRange, maxRange);
    if(value < minRange || value > maxRange){
        return false;
    }
    return true;
}

bool isTemperatureWithinRange(const Parameter& temperatureParam){
    const auto temperature = temperatureParam.value;
    const auto minRange = temperatureParam.lowerLimit;
    const auto maxRange = temperatureParam.upperLimit;
    if(!isParamWithinRange(temperature, minRange, maxRange)){
        std::cout << errorMsgsCollection[selected_language]["TEMP_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool isSOCWithinRange(const Parameter& socParam){
    const auto soc = socParam.value;
    const auto minRange = socParam.lowerLimit;
    const auto maxRange = socParam.upperLimit;
    if(!isParamWithinRange(soc, minRange, maxRange)){
        std::cout << errorMsgsCollection[selected_language]["SOC_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool isChargeRateWithinRange(const Parameter& chargeRateParam){
    const auto chargeRate = chargeRateParam.value;
    const auto minRange = chargeRateParam.lowerLimit;
    const auto maxRange = chargeRateParam.upperLimit;
    if(!isParamWithinRange(chargeRate, minRange, maxRange)){
        std::cout << errorMsgsCollection[selected_language]["CHARGE_RATE_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool batteryIsOk(const std::vector<Parameter>& paramCollection) {
    std::vector<bool> resultCollection;
    resultCollection.push_back(isTemperatureWithinRange(paramCollection[0]));
    resultCollection.push_back(isSOCWithinRange(paramCollection[1]));
    resultCollection.push_back(isChargeRateWithinRange(paramCollection[2]));
    return std::all_of(std::begin(resultCollection),std::end(resultCollection),[](bool i){ return i;});
}

