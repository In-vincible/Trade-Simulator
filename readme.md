[![Docker Image CI](https://github.com/In-vincible/Trade-Simulator/actions/workflows/docker-image.yml/badge.svg?branch=master)](https://github.com/In-vincible/Trade-Simulator/actions/workflows/docker-image.yml)
[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FAndriyKalashnykov%2Fcpp-sample-app&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
# Trade Simulator

Simulator program that calculates the history of holding position (i.e. the dollar amount held per stock) according to various portfolio trading algorithm codes provided by the user.

### Clone repo

```bash
git clone https://github.com/In-vincible/Trade-Simulator.git
```
### Requirements

Docker (Tested on 24.0.2 but any version >20 should be fine)

### How to build/run?

```bash
cd Trade-Simulator
// Build 
docker build -t simulator:1.0 .
// Run (we mount a directory on host to docker container so that we don't loose output even after container exits.)
docker run -t -v "<Absolute Path of Output directory>:/output" simulator:1.0
eg. docker run -t -v "C:\Users\Bikram Bharti\Trade-Simulator:/output" simulator:1.0
```

### Config Format (JSON)

```json
{
  "Simulation": {
    "Info": {
      "StartTime": "2020-01-01",
      "EndTime": "2022-12-31"
    },
    "Algo": {
      "SimSample1": {
        "Algoname": "Algo1",
        "param1": 1.0,
        "param2": 24,
        "input": "Close"
      }
    }
  }
}
```

### Inputs (Historical Market Data)

Each input provided in Algo config - need to be present in /input folder, for eg. input/Close.csv is present.

### Output (Simulation Result)

Output of each algo simulation is stored in output directory (mounted on docker in above command) with <Algo_Name>_results.csv.

### Steps to add a new algo for simulation

1. Add algo config in `config/simulation_config.json`.
2. Add input provided in 1 in `input/` directory with csv extension. (Same input can be used for multiple algos, so if already there not required to add)
3. Implement Algo in `algos/simulation_algo_definitions.cpp` in below fashion -
```cpp
// Function Signature should look like below - basically exactly same arguments and return
std::vector<double> SimSample1(int time_index, std::vector<std::vector<double>> &close_price, std::vector<std::string> &assetNames, std::unordered_map<std::string, double>& stateVariables)
// Add below function to `functionMap` variable defined at the bottom of the file
{"<Algo_Name_defined in config>", &"<Function_Defined_above>"}
```
> **_NOTE:_** Even if a function is defined in 3., if you remove algo from config(json) it won't run -> this gives you flexibility to not run algos you don't want to run.


## On Program design and Flow

### Program Flow (Code Entry Point: src/trade_simulator.cpp)

1. Config gets loaded (`config/simulation_config.json`)
2. Input Data gets loaded provided in above config. (`input/<>.csv`) [Runs in parallel one thread per unique input file]
3. Each Algo function runs. (Function defined - `algos/simulation_algo_definitions.cpp`) [Runs in parallel one thread per Algo]
4. Results are written to corresponding csv files. (saved in `output` directory) [Runs in parallel one thread per Algo]

> **_NOTE:_** Above 4 steps runs sequentially, and we wait for each step to complete before starting with next.


### Different modules and their function - 
1. `simlution_algo_definitions.cpp` => definitions of algos for simulation to be defined here.
2. `trade_simulator.cpp` => entry point of code which runs everything.
3. `algo.h` => Defined the Algo details like algo name, params etc.
2. `input_data_service.h` => Loads input data provided in configs from csv.
3. `output_data_service.h` => writes final results of simulation to csv.
4. `simulation_config.h` => loads the config provided in json format.
5. `simulation_engine.h` => runs algos.
6. `nan_check_util` => to check "Not a Number"  scenarios generated via strategy.
7. `shared_memory_wrapper.h` (not used, but wrapper to save 2D array in disk efficiently important if we were to handle GBs of market data per strategy)


### Problems not addressed due time constraint 
1. Each algo can have more than one input (Already solved in design but due lack of testing time avoided for now).
2. Would have used `boost::multiprecision` rather for data (instead of double).
2. Currently, program can go into OOM if too many threads opened also number of threads are not chosen cleverly - ideally Core/Logical Processors should be in the configs and we should decide number of threads (concurrently) accordingly - and everything else should be sequential.
3. Ideally - Input Data Service, Out Put Data Service, Simulation Engine should run in 3 separate containers. (here all 3 containers could have been horizontally scaled as well)
4. Data(input/output) is currently loaded in memory(RAM) - we should load them in shared memory to be able to scale to 100s of strategies with months of data. (I wrote shared memory wrapper(committed) but due time constraint didn't use it).
5. Add plug and play profiler for memory, latency, CPU usage, RAM usage and number of open threads.

> **_NOTE:_** Shared memory would have been slower than memory but still average latency is like 300 nano secs which is good enough for any simulation purposes, Another benefit of shared is all 3 containers(input/output/algo engine) could talk to each other and behave accordingly.

### Build Details - 
1. Code is writen to run linux/amd64 env, and docker uses latest ubuntu as base image.
2. Docker/Cmake are the build tools used for the cross-platform flexibility provided by them.
3. Uses latest version of Boost library.
4. Boost Tests runs as a part of build to have preventive alerts. (check CMakeLists.txt).
