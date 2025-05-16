#include "GAPInstance.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

void GAPInstance::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error("Impossible to open file: " + filename);
    
    std::string line;
    int m = 0, n = 0;

    while (std::getline(infile, line)) {
        if (line.rfind("m:", 0) == 0) {
            std::istringstream(line.substr(2)) >> m;
        } else if (line.rfind("n:", 0) == 0) {
            std::istringstream(line.substr(2)) >> n;
        }
        if (m>0 && n>0) { // when m & n are initialized
            numAgents = m;
            numTasks = n;
            break;
        }
    }

    cost.assign(m, std::vector<int>(n));
    resource.assign(m, std::vector<int>(n));
    capacities.clear();

    while (std::getline(infile, line) && line.find("c_ij:") == std::string::npos);
    for (int i=0; i<m; ++i) {
        if (!std::getline(infile, line))
            throw std::runtime_error("costMatrix's rows are missing.");
        std::istringstream ss(line);
        for (int j=0; j<n; ++j) {
            if (!(ss >> cost[i][j]))
                throw std::runtime_error("costMatrix parsing error at row: " + std::to_string(i));
        }
    }

    while (std::getline(infile, line) && line.find("r_ij:") == std::string::npos);
    for (int i=0; i<m; ++i) {
        if (!std::getline(infile, line))
            throw std::runtime_error("resourceMatrix's rows are missing.");
        std::istringstream ss(line);
        for (int j=0; j<n; ++j) {
            if (!(ss >> resource[i][j]))
                throw std::runtime_error("resourceMatrix parsing error at row: " + std::to_string(i));
        }
    }

    while (std::getline(infile, line) && line.find("b_i:") == std::string::npos);
    std::getline(infile, line);
    std::istringstream ss(line);
    int b;
    while (ss >> b) capacities.push_back(b);
    if ((int)capacities.size() != m)
        throw std::runtime_error("Elements of capacity != m.");
}

const std::vector<std::vector<int>>& GAPInstance::getCostMatrix() const {
    return cost;
}

const std::vector<std::vector<int>>& GAPInstance::getResourceMatrix() const {
    return resource;
}

const std::vector<int>& GAPInstance::getCapacities() const {
    return capacities;
}

int GAPInstance::getNumTasks() const {
    return numTasks;
}

int GAPInstance::getNumAgents() const {
    return numAgents;
}