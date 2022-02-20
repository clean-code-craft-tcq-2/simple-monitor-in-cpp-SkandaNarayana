#include <iostream>
#include "batteryStatusChecker.h"

Available_language selected_language = Available_language::German;

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

std::map<Available_language, outputMsgsLanguageMap> outputMsgsCollection = {
        {Available_language::English, english_output_msg},
        {Available_language::German,  german_output_msg}
};

bool isParamNearingBreachLimit(const float lowerBoundary, const float value, const float upperBoundary){
    if(lowerBoundary <= value && value <= upperBoundary){
        return true;
    }
    return false;
}

void printToConsole(std::string& output_string){
    std::cout << output_string << std::endl;
}

double getLowerToleranceLimit(const float &minRange, const double &warningToleranceNumber) {
    return minRange + warningToleranceNumber;

}

double getUpperLimitTolerance(const float &maxRange, const double &warningToleranceNumber) {
    return maxRange - warningToleranceNumber;
}

double getToleranceNumber(const float &maxRange) {
    return maxRange * WARNING_TOLERANCE;
}

bool isEarlyWarningNeeded(const Parameter Param, const float minRange, const float maxRange){
    if(!Param.earlyWarningNeeded) return false;
    const auto warningToleranceNumber = getToleranceNumber(maxRange);
    const auto lowerLimitTolerance = getLowerToleranceLimit(minRange, warningToleranceNumber);
    const auto upperLimitTolerance = getUpperLimitTolerance(maxRange, warningToleranceNumber);
    if(isParamNearingBreachLimit(minRange, Param.value, lowerLimitTolerance)){
        printToConsole(outputMsgsCollection[selected_language]["WARN_LOWER_LIMIT"]);
        return true;
    }
    else if (isParamNearingBreachLimit(upperLimitTolerance, Param.value, maxRange)){
        printToConsole(outputMsgsCollection[selected_language]["WARN_UPPER_LIMIT"]);
        return true;
    }
    return false;
}

bool isParamWithinRange(const float value, const float minRange, const float maxRange){
    if(value < minRange || value > maxRange){
        return false;
    }
    return true;
}

float convertToCelsius(float input, const ParameterUnits unit){
    if (unit == ParameterUnits::Fahrenheit){
        input = (input - 32) * 5 / 9;
    }
    else if( unit == ParameterUnits::Celsius){
        return input;
    }
}

bool isTemperatureWithinRange(Parameter& temperatureParam){
    temperatureParam.value = convertToCelsius(temperatureParam.value, temperatureParam.units);
    if (isEarlyWarningNeeded(temperatureParam, MINIMUM_TEMP, MAXIMUM_TEMP)){
        // If early warning is needed, implicitly means parameter is within Range, hence return true;
        return true;
    }
    if(!isParamWithinRange(temperatureParam.value, MINIMUM_TEMP, MAXIMUM_TEMP)){
        std::cout << outputMsgsCollection[selected_language]["TEMP_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool isSOCWithinRange(Parameter& socParam){
    const auto soc = socParam.value;
    if (isEarlyWarningNeeded(socParam, MINIMUM_SOC, MAXIMUM_SOC)){
        // If early warning is needed, implicitly means parameter is within Range, hence return true;
        return true;
    }
    if(!isParamWithinRange(soc, MINIMUM_SOC, MAXIMUM_SOC)){
        std::cout << outputMsgsCollection[selected_language]["SOC_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool isChargeRateWithinRange(Parameter& chargeRateParam){
    const auto chargeRate = chargeRateParam.value;
    if (isEarlyWarningNeeded(chargeRateParam, MINIMUM_CHARGE_RATE, MAXIMUM_CHARGE_RATE)){
        // If early warning is needed, implicitly means parameter is within Range, hence return true;
        return true;
    }
    if(!isParamWithinRange(chargeRate, MINIMUM_CHARGE_RATE, MAXIMUM_CHARGE_RATE)){
        std::cout << outputMsgsCollection[selected_language]["CHARGE_RATE_OUT_OF_RANGE"] << std::endl;
        return false;
    }
    return true;
}

bool batteryIsOk(std::vector<Parameter>& paramCollection) {
    std::vector<bool> resultCollection;
    resultCollection.push_back(isTemperatureWithinRange(paramCollection[0]));
    resultCollection.push_back(isSOCWithinRange(paramCollection[1]));
    resultCollection.push_back(isChargeRateWithinRange(paramCollection[2]));
    return std::all_of(std::begin(resultCollection),std::end(resultCollection),[](bool i){ return i;});
}

