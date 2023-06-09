//
// Created by Bikram Bharti on 08-06-2023.
//

#ifndef CMAKE_TEMPLATE_INPUT_DATA_SERVICE_H
#define CMAKE_TEMPLATE_INPUT_DATA_SERVICE_H

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


class InputDataService {
public:
    static InputDataService& getInstance(const std::vector<std::string> &inputs) {
        static InputDataService instance(inputs);
        return instance;
    }

    void loadInputData(const std::string& startDate, const std::string& endDate) {
        std::cout<<"\nLoading Input Data....";
        boost::thread_group readThreads;
        // Start a separate thread for reading each CSV file
        for (const auto& filename : inputNames_) {
            readThreads.create_thread(boost::bind(&InputDataService::readThreadFunction, this, filename, startDate, endDate));
        }

        readThreads.join_all();
    }

    std::vector<std::string>& getAssetNames(const std::string& inputName) {
        return assetNamesByInputName_[inputName];
    }

    std::vector<std::vector<double>>& getInput(const std::string& inputName) {
        return inputs_[inputName];
    }

    std::vector<std::string>& getTimes(const std::string& inputName) {
        return timeByInputName_[inputName];
    }

private:
    // Constructor private to prevent initiation (as Singular Class)
    explicit InputDataService(const std::vector<std::string>& inputs) : inputNames_(inputs.begin(), inputs.end()) {}

    void readThreadFunction(const std::string& input, const std::string& startDate, const std::string& endDate) {
        std::string filename = "input/" + input + ".csv";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::printf("Wrong input supplied, Failed to open file: %s\n", filename.c_str());
            return;
        }

        int rows = 0;
        std::string line;
        while (std::getline(file, line)) {
            // Process each line of the CSV file here
            // Example: Splitting the line into tokens
            std::vector<std::string> tokens;
            boost::split(tokens, line, boost::is_any_of(","));
            if(rows == 0)
            {
                assetNamesByInputName_[input].clear();
                assetNamesByInputName_[input] = std::vector<std::string>(tokens.begin()+1, tokens.end());
            }

            rows++;

            // Continue if current row time is less than start date or first row
            if(tokens[0] < startDate || rows == 1)
                continue;

            // Break loop if current row time is more than end date
            if(tokens[0] > endDate)
                break;

            timeByInputName_[input].push_back(tokens[0]);
            std::vector<double> rowData;
            for (int i=1; i<tokens.size(); i++)
            {
                std::string token = tokens[i];
                double md;
                try {
                    md = std::stod(token);
                } catch(...) {
                    md = NAN;
                }
                rowData.push_back(md);
            }
            inputs_[input].push_back(rowData);
        }

        file.close();
        std::printf("\nFile: %s read with rows: %d", filename.c_str(), rows);
    }

    std::unordered_set<std::string> inputNames_;
    std::unordered_map<std::string, std::vector<std::vector<double>>> inputs_;
    std::unordered_map<std::string, std::vector<std::string>> assetNamesByInputName_;
    std::unordered_map<std::string, std::vector<std::string>> timeByInputName_;
};
#endif //CMAKE_TEMPLATE_INPUT_DATA_SERVICE_H
