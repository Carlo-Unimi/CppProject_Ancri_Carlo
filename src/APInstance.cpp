#include "APInstance.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>

void APInstance::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error("Impossible to open file: " + filename);
    
    std::string line;
    numAgents = 0;
    bool found = false;

    while (std::getline(infile, line)) {
        if (line.find("n:") == 0) {
            std::istringstream ss(line.substr(2));
            ss >> numAgents;
            if (numAgents <= 0) throw std:: runtime_error("Non valid value of n.");
            costMatrix.resize(numAgents);
            found = true;
            break;
        }
    }

    if (!found) throw std::runtime_error("The 'n:' parameter was not found in the file.");

    while(std::getline(infile, line)) {
        if (line.find("c_ij:") != std::string::npos) break;
    }

    int row = 0;
    while (row < numAgents && std::getline(infile, line)) {
        std::istringstream ss(line);
        int value;
        while(ss >> value)
            costMatrix[row].push_back(value);
        if (costMatrix[row].size() != static_cast<size_t>(numAgents))
            throw std::runtime_error("Row " + std::to_string(row) + " doesn't have " + std::to_string(numAgents) + " columns.");
        row++;
    }

    if (row != numAgents)
        throw std::runtime_error("Matrix's number of rows different from n.");
}

const std::vector<std::vector<int>>& APInstance::getCostMatrix() const {
    return costMatrix;
}

int APInstance::getNumAgents() const {
    return numAgents;
}
