//
// Created by Bikram Bharti on 08-06-2023.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "algo.h"

class SimulationConfig {
public:
    explicit SimulationConfig(std::string  configFile) : configFile_(std::move(configFile)) {}

    std::vector<Algo> &getAlgos() {
        return algos_;
    }

    void addAlgo(const Algo &algo) {
        algos_.push_back(algo);
    }

    std::string &getStartTime() {
        return startTime_;
    }

    void setStartTime(const std::string &startTime) {
        startTime_ = startTime;
    }

    std::string &getEndTime()  {
        return endTime_;
    }

    void setEndTime(const std::string &endTime) {
        endTime_ = endTime;
    }

    std::vector<std::string> &getInputs() {
        return inputs_;
    }

    void addInput(const std::string &input) {
        inputs_.push_back(input);
    }

    void parseConfig() {
        boost::property_tree::ptree pt;
        boost::property_tree::json_parser::read_json(configFile_, pt);

        // Parse Simulation.Info section
        boost::property_tree::ptree infoSection = pt.get_child(boost::property_tree::ptree::path_type("Simulation.Info"));
        setStartTime(infoSection.get<std::string>("StartTime"));
        setEndTime(infoSection.get<std::string>("EndTime"));

        // Parse Simulation.Algo section
        boost::property_tree::ptree algoSection = pt.get_child("Simulation.Algo");
        for (const auto& sample : algoSection) {
            std::string sampleName = sample.first;
            boost::property_tree::ptree sampleProperties = sample.second;
            std::string algoName = sampleProperties.get<std::string>("Algoname");
            std::string inputName = sampleProperties.get<std::string>("input");

            Algo algo(algoName, inputName);
            addInput(inputName);

            for (const auto& property : sampleProperties) {
                if (property.first != "Algoname" && property.first != "input") {
                    algo.addParam(property.first, property.second.data());
                }
            }

            addAlgo(algo);
        }
    }

    void printInfo() {
        std::printf("\nStart Time: %s, End Time: %s, configFile: %s", getStartTime().c_str(), getEndTime().c_str(), configFile_.c_str());

        for(const auto& algo: getAlgos())
        {
            algo.printInfo();
            std::cout<<std::endl;
        }
    }

private:
    std::string configFile_;
    std::vector<Algo> algos_;
    std::string startTime_;
    std::string endTime_;
    std::vector<std::string> inputs_;
};

#endif // CONFIG_H
