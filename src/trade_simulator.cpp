//
// Created by Bikram Bharti on 08-06-2023.
//

#include <iostream>
#include <memory>
#include "simulation_engine.h"


int main(int argc, char *argv[]){
    std::cout<<"Running Simulation...."<<std::endl;
    SimulationEngine simulationEngine = SimulationEngine("config/simulation_config.json");
    simulationEngine.initConfig();
    simulationEngine.run_all_strategies();
    return 0;
}