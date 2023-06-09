//
// Created by Bikram Bharti on 09-06-2023.
//

#ifndef CMAKE_TEMPLATE_OUTPUT_DATA_SERVICE_H
#define CMAKE_TEMPLATE_OUTPUT_DATA_SERVICE_H

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include "algo.h"
#include "nan_check_util.h"
#define DOCKER_OUTPUT_DIRECTORY "/output/"

class OutputDataService {
public:
    static OutputDataService& getInstance() {
        static OutputDataService instance;
        return instance;
    }

    void saveOutput(const std::string& algoName, std::vector<double>& outputRow) {
        outputByAlgo_[algoName].push_back(outputRow);
    }

    void setTimes(const std::string& algoName, std::vector<std::string>& times) {
        timesByAlgo_[algoName] = times;
    }

    void setAssets(const std::string& algoName, std::vector<std::string>& assets) {
        assetsByAlgo_[algoName] = assets;
    }

    void writeSavedData() {
        std::cout<<"\nAbout to write all the results.";
        boost::thread_group writeThreads;
        // Start a separate thread for CSV writer
        for (const auto& algoOutput : outputByAlgo_) {
            std::string algoName = algoOutput.first;
            writeThreads.create_thread(boost::bind(&OutputDataService::writeThreadFunction, this, algoName, assetsByAlgo_[algoName], timesByAlgo_[algoName]));
        }
        writeThreads.join_all();
    }

private:
    // Constructor private to prevent initiation (as Singular Class)
    explicit OutputDataService()   = default;

    template <typename T>
    void writeRow(const std::string& time, std::vector<T>& row, std::ofstream& file) {
        file<<time<<",";
        for(size_t i=0; i<row.size(); ++i) {
            if(!isNaN(row[i]))
                file << row[i];
            if(i != row.size()-1)
                file << ",";
        }
        file<<"\n";
    }

    void writeThreadFunction(const std::string& algoName, std::vector<std::string>& assets, std::vector<std::string> &times) {
        // validate assets, time length with output
        auto& data = outputByAlgo_[algoName];
        if(data.size() != times.size() || data[0].size() != assets.size()){
            std::printf("\n Inconsistencies in data (data rows: %zu cols: %zu, assets size: %zu, times size: %zu)", data.size(), data[0].size(), times.size(), assets.size());
            return;
        }

        std::string fileName = DOCKER_OUTPUT_DIRECTORY + algoName + "_results.csv";
        std::ofstream file(fileName, std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return;
        }

        // Write assets in first row
        writeRow("", assets, file);
        // Write all the data
        for(size_t i=0; i<data.size(); i++)
            writeRow(times[i], data[i], file);

        file.close();
        std::cout << "\nCSV file written: " << fileName;
    }

    std::unordered_map<std::string, std::vector<std::vector<double>>> outputByAlgo_;
    std::unordered_map<std::string, std::vector<std::string>> timesByAlgo_;
    std::unordered_map<std::string, std::vector<std::string>> assetsByAlgo_;
};

#endif //CMAKE_TEMPLATE_OUTPUT_DATA_SERVICE_H
