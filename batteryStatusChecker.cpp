#include <iostream>
#include "batteryStatusChecker.h"

output_languages selected_language = output_languages::German;

using outputMsgsLanguageMap = std::map<std::string, std::string>;

outputMsgsLanguageMap english_output_msg = {
        {"TEMP_OUT_OF_RANGE" ,"ALERT!! Temperature out of range"},
        {"SOC_OUT_OF_RANGE","ALERT!! soc out of range"},
        {"CHARGE_RATE_OUT_OF_RANGE","ALERT!! chargeRate out of range"},
        {"WARN_LOWER_LIMIT" ,"WARNING!! Parameter nearing lower limit "},
        {"WARN_UPPER_LIMIT" ,"WARNING!! Parameter nearing upper limit "},
};

outputMsgsLanguageMap german_output_msg = {
        {"TEMP_OUT_OF_RANGE" ,"Temperatur außerhalb des Bereichs"},
        {"SOC_OUT_OF_RANGE","soc außer Reichweite"},
        {"CHARGE_RATE_OUT_OF_RANGE","Laderate außerhalb des Bereichs"},
        {"WARN_LOWER_LIMIT" ,"WARNUNG!! Parameter nähert sich dem unteren Grenzwert "},
        {"WARN_UPPER_LIMIT" ,"WARNUNG!! Parameter nähert sich der Obergrenze "},
};

std::map<output_languages, outputMsgsLanguageMap> outputMsgsCollection = {
        {output_languages::English, english_output_msg},
        {output_languages::German,  german_output_msg}
};

bool isParamNearingBreachLimit(const float lowerBoundary, const float value, const float upperBoundary){
    if(lowerBoundary <= value && value <= upperBoundary){
        return true;
    }
    return false;
}

void reportEarlyWarning(const float value, const float minRange, const float maxRange){
    const auto warningToleranceNumber = maxRange * WARNING_TOLERANCE;
    const auto lowerLimitTolerance = minRange + warningToleranceNumber;
    const auto upperLimitTolerance = maxRange - warningToleranceNumber;
    if(isParamNearingBreachLimit(minRange, value, lowerLimitTolerance)){
        std::cout << outputMsgsCollection[selected_language]["WARN_LOWER_LIMIT"] << std::endl;
    }
    else if (isParamNearingBreachLimit(upperLimitTolerance, value, maxRange)){
        std::cout <<outputMsgsCollection[selected_language]["WARN_UPPER_LIMIT"] <<std::endl;
    }
}

bool isParamWithinRange(const float value, const float minRange, const float maxRange){
    reportEarlyWarning(value, minRange, maxRange);
    if(value < minRange || value > maxRange){
        return false;
    }
    return true;
}

float convertToCelsius(float input, std::string units){
    if (units == "fahrenheit"){
        return (input - 32) * 5 / 9;
    }
    else if (units == "celsius"){
        return input;
    }
}

bool isTemperatureWithinRange(const Parameter& temperatureParam){
    auto temperature = convertToCelsius(temperatureParam.value, temperatureParam.units);
    std::cout <<" Temp is " << temperature << std::endl;
    if(!isParamWithinRange(temperature, MINIMUM_TEMP, MAXIMUM_TEMP)){
        std::cout << outputMsgsCollection[selected_language]["TEMP_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool isSOCWithinRange(const Parameter& socParam){
    const auto soc = socParam.value;
    if(!isParamWithinRange(soc, MINIMUM_SOC, MAXIMUM_SOC)){
        std::cout << outputMsgsCollection[selected_language]["SOC_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool isChargeRateWithinRange(const Parameter& chargeRateParam){
    const auto chargeRate = chargeRateParam.value;
    if(!isParamWithinRange(chargeRate, MINIMUM_CHARGE_RATE, MAXIMUM_CHARGE_RATE)){
        std::cout << outputMsgsCollection[selected_language]["CHARGE_RATE_OUT_OF_RANGE"] << std::endl;
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

