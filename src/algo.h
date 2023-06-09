//
// Created by Bikram Bharti on 08-06-2023.
//

#ifndef CMAKE_TEMPLATE_ALGO_H
#define CMAKE_TEMPLATE_ALGO_H

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <unistd.h>

class Algo {
public:
    Algo(std::string  name, std::string  inputName) : name_(std::move(name)), inputName_(std::move(inputName)) {}

    std::string getAlgoName() {
        return name_;
    }

    std::string getInputName() {
        return inputName_;
    }

    std::unordered_map<std::string, double>& getAllParams() {
        return params_;
    }

    void addParam(const std::string& paramName, const std::string& paramValue) {
        try {
            params_[paramName] = std::stod(paramValue);
        } catch (const std::exception& e) {
            std::printf("\nError parsing parameter: %s, value: %s, algo: %s", paramName.c_str(), paramValue.c_str(), name_.c_str());
        }

    }

    double getParam(const std::string& paramName) const {
        auto it = params_.find(paramName);
        if (it != params_.end())
            return it->second;

        // Return a default value if the parameter is not found or parsing fails
        return 0.0;
    }

    void printInfo() const {
        std::printf("\nAlgo Name: %s, Input Name: %s", name_.c_str(), inputName_.c_str());
        for (const auto& param : params_) {
            std::printf("\n %s: %f", param.first.c_str(), param.second);
        }
    }

private:
    std::string name_;
    std::string inputName_;
    std::unordered_map<std::string, double> params_;
};

#endif //CMAKE_TEMPLATE_ALGO_H
