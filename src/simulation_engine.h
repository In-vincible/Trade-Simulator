//
// Created by Bikram Bharti on 08-06-2023.
//

#ifndef CMAKE_TEMPLATE_SIMULATION_ENGINE_H
#define CMAKE_TEMPLATE_SIMULATION_ENGINE_H

#include <cstdio>
#include <functional>
#include "algo.h"
#include "simulation_config.h"
#include "input_data_service.h"
#include "output_data_service.h"
#include "../algos/simulation_algo_definitions.cpp"
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

class SimulationEngine {
public:
    explicit SimulationEngine(const std::string& simulation_config_name) : simulationConfig_(simulation_config_name) {}

    void initConfig() {
        simulationConfig_.parseConfig();
        InputDataService& inputDataService_ = InputDataService::getInstance(simulationConfig_.getInputs());
        inputDataService_.loadInputData(simulationConfig_.getStartTime(), simulationConfig_.getEndTime());
        simulationConfig_.printInfo();
    }

    void run_algo(Algo& algo) {
        std::printf("\nRunning %s..", algo.getAlgoName().c_str());
        InputDataService& inputDataService = InputDataService::getInstance(simulationConfig_.getInputs());
        OutputDataService& outputDataService = OutputDataService::getInstance();
        std::function<std::vector<double>(int,std::vector<std::vector<double>>&, std::vector<std::string>&, std::unordered_map<std::string, double>& )> algoStrategy \
                = findFunction(algo.getAlgoName());

        if(algoStrategy) {
            auto& inputForAlgo = inputDataService.getInput(algo.getInputName());
            auto& assetsForInput = inputDataService.getAssetNames(algo.getInputName());
            auto& timesForInput = inputDataService.getTimes(algo.getInputName());

            // Set output params for algo
            outputDataService.setTimes(algo.getAlgoName(), timesForInput);
            outputDataService.setAssets(algo.getAlgoName(), assetsForInput);

            int time_index = 0;
            while(time_index < inputForAlgo.size()){
                std::vector<double> output = algoStrategy(time_index, inputForAlgo, assetsForInput, algo.getAllParams());
                outputDataService.saveOutput(algo.getAlgoName(), output);
                time_index++;
            }
        } else {
            std::printf("\nFunction for algo: %s not defined (algos/simulation_algo_definitions.cpp)", algo.getAlgoName().c_str());
        }
    }

    void run_all_strategies() {
        std::cout<< "\nAbout to run algos." << std::endl;
        auto allAlgos = simulationConfig_.getAlgos();

        boost::thread_group strategyThread;
        for(Algo algo: allAlgos)
            strategyThread.create_thread(boost::bind(&SimulationEngine::run_algo, this, algo));

        strategyThread.join_all();
        OutputDataService& outputDataService = OutputDataService::getInstance();
        outputDataService.writeSavedData();
        std::cout<<"\nFinished simulation.";
    }

private:
    SimulationConfig simulationConfig_;
};

#endif //CMAKE_TEMPLATE_SIMULATION_ENGINE_H
