#include "GAPInstance.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>    // std::setw

void GAPInstance::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    bool readingCost = false, readingResource = false, readingCapacity = false;
    int currentRow = 0;

    while (std::getline(infile, line)) {
        if (line.empty()) continue;

        if (line.rfind("m:", 0) == 0) {
            std::istringstream ss(line.substr(2));
            ss >> numAgents;
        } else if (line.rfind("n:", 0) == 0) {
            std::istringstream ss(line.substr(2));
            ss >> numTasks;
        } else if (line.find("c_ij:") != std::string::npos) {
            readingCost = true;
            readingResource = readingCapacity = false;
            cost.resize(numAgents, std::vector<int>());
            currentRow = 0;
        } else if (line.find("r_ij:") != std::string::npos) {
            readingResource = true;
            readingCost = readingCapacity = false;
            resource.resize(numAgents, std::vector<int>());
            currentRow = 0;
        } else if (line.find("b_i:") != std::string::npos) {
            readingCapacity = true;
            readingCost = readingResource = false;
            capacities.clear();
        } else if (readingCost) {
            std::istringstream ss(line);
            int value;
            while (ss >> value) {
                cost[currentRow].push_back(value);
            }
            if (cost[currentRow].size() != static_cast<size_t>(numTasks)) {
                throw std::runtime_error("Error in cost matrix at line " + std::to_string(currentRow));
            }
            currentRow++;
        } else if (readingResource) {
            std::istringstream ss(line);
            int value;
            while (ss >> value) {
                resource[currentRow].push_back(value);
            }
            if (resource[currentRow].size() != static_cast<size_t>(numTasks)) {
                throw std::runtime_error("Resource matrix error at row " + std::to_string(currentRow));
            }
            currentRow++;
        } else if (readingCapacity) {
            std::istringstream ss(line);
            int value;
            while (ss >> value) {
                capacities.push_back(value);
            }
        }
    }

    // Validazioni finali
    if (cost.size() != static_cast<size_t>(numAgents) || resource.size() != static_cast<size_t>(numAgents)) {
        throw std::runtime_error("Wrong number of rows in cost/resource.");
    }
    if (capacities.size() != static_cast<size_t>(numAgents)) {
        throw std::runtime_error("Incorrect capacity number (b_i).");
    }
}



const std::vector<std::vector<int>>& GAPInstance::getCostMatrix() const { return cost; }
const std::vector<std::vector<int>>& GAPInstance::getResourceMatrix() const { return resource; }
const std::vector<int>& GAPInstance::getCapacities() const { return capacities; }
int GAPInstance::getNumTasks() const { return numTasks; }
int GAPInstance::getNumAgents() const { return numAgents; }
