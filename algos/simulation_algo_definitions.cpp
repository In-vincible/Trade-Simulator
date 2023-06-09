//
// Created by Bikram Bharti on 08-06-2023.
//

#include <cmath>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>


// Define the actual Algos below
// Algo 1
std::vector<double> SimSample1(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}

// Algo 2
std::vector<double> SimSample3(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}


// Algo 3
std::vector<double> SimSample4(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}


// Algo 4
std::vector<double> SimSample5(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}

// Algo5
std::vector<double> SimSample6(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}

// Algo6
std::vector<double> SimSample7(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}

// Algo7
std::vector<double> SimSample8(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}

// Algo8
std::vector<double> SimSample9(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables){
    int numberOfInstruments = (int)assetNames.size();
    std::vector<double> finalPositions(numberOfInstruments, NAN);

    // Validation for indices
    if(time_index < 2)
        return finalPositions;

    for(int ii=0; ii<numberOfInstruments; ii++) {
        if(close_price[time_index-2][ii] != 0)
            finalPositions[ii] = -(close_price[time_index-1][ii] - close_price[time_index-2][ii])/close_price[time_index-2][ii] * 10000;
    }

    return finalPositions;
}

// Define a map to store function pointers
std::map<std::string, std::function<std::vector<double>(int,std::vector<std::vector<double>>&, std::vector<std::string>&, std::unordered_map<std::string, double>& )>> \
functionMap = {
        {"Algo1", &SimSample1},
        {"Algo2", &SimSample3},
        {"Algo3", &SimSample4},
        {"Algo4", &SimSample5},
        {"Algo5", &SimSample6},
        {"Algo6", &SimSample7},
        {"Algo7", &SimSample8},
        {"Algo8", &SimSample9}
};

// Function registration helper function
void registerFunction(const std::string& name, std::function<std::vector<double>(int,std::vector<std::vector<double>>&, std::vector<std::string>&, std::unordered_map<std::string, double>& )> func) {
    functionMap[name] = std::move(func);
}

// Function lookup function
std::function<std::vector<double>(int,std::vector<std::vector<double>>&, std::vector<std::string>&, std::unordered_map<std::string, double>& )> findFunction(const std::string& name) {
    auto it = functionMap.find(name);
    if (it != functionMap.end()) {
        return it->second;
    }
    return nullptr;
}


