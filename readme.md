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

### Local usage

```bash
cd Trade-Simulator
// Build 
docker build -t simulator:1.0 .
// Run (we mount a directory on host to docker container so that we don't loose output even after container exits.)
docker run -t -v "<Absolute Path of Output directory>:/output" simulator:1.0
eg. docker run -t -v "C:\Users\Bikram Bharti\Trade-Simulator:/output" simulator:1.0
```

### Config Format

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
