#include "APInstance.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>

void APInstance::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    bool readingMatrix = false;
    int rowCount = 0;

    while (std::getline(infile, line)) {
        if (line.empty()) continue;


        if (line.rfind("n:", 0) == 0) {
            std::istringstream ss(line.substr(2));
            ss >> numAgents;
            numTasks = numAgents;
            costMatrix.resize(numAgents);
            continue;
        }


        if (line.find("c_ij:") != std::string::npos) {
            readingMatrix = true;
            continue;
        }

        if (readingMatrix) {
            if (rowCount >= numAgents) break;

            std::istringstream ss(line);
            int cost;
            while (ss >> cost) {
                costMatrix[rowCount].push_back(cost);
            }


            if (costMatrix[rowCount].size() != static_cast<size_t>(numTasks)) {
                throw std::runtime_error("Wrong number of columns in row " + std::to_string(rowCount));
            }

            rowCount++;
        }
    }

    if (rowCount != numAgents) {
        throw std::runtime_error("Number of lines read different from n.");
    }
}

const std::vector<std::vector<int>>& APInstance::getCostMatrix() const {
    return costMatrix;
}

int APInstance::getNumAgents() const {
    return numAgents;
}

int APInstance::getNumTasks() const {
    return numTasks;
}