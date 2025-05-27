#include "UFLPInstance.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

void UFLPInstance::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error("Impossible to open file: " + filename);
    
    std::string line;
    int m = 0, n = 0;
    bool foundDimensions = false;

    while (std::getline(infile, line)) {
        if (line.find("m:") == 0) {
            std::istringstream(line.substr(2)) >> m;
        } else if (line.find("n:") == 0) {
            std::istringstream(line.substr(2)) >> n;
        }
        
        if (m > 0 && n > 0) {
            foundDimensions = true;
            numFacilities = m;
            numClients = n;
            serviceCosts.assign(m, std::vector<int>(n));
            openingCosts.clear();
            break;
        }
    }

    if (!foundDimensions) {
        throw std::runtime_error("Could not find valid m and n dimensions");
    }

    while (std::getline(infile, line)) {
        if (line.find("c_ij:") != std::string::npos) {
            break;
        }
    }

    for (int i = 0; i < m; ++i) {
        if (!std::getline(infile, line)) {
            throw std::runtime_error("Missing row " + std::to_string(i) + " in costs matrix.");
        }
        
        std::istringstream ss(line);
        for (int j = 0; j < n; ++j) {
            if (!(ss >> serviceCosts[i][j])) {
                throw std::runtime_error("Error reading costs matrix at row " + std::to_string(i) + ", col " + std::to_string(j));
            }
        }
    }

    while (std::getline(infile, line)) {
        if (line.find("f_i:") != std::string::npos) {
            break;
        }
    }

    if (std::getline(infile, line)) {
        std::istringstream ss(line);
        int cost;
        while (ss >> cost) {
            openingCosts.push_back(cost);
        }
    }

    if ((int)openingCosts.size() != m) {
        throw std::runtime_error("Number of opening costs (" + std::to_string(openingCosts.size()) + 
                                ") != m (" + std::to_string(m) + ")");
    }

    infile.close();
}

int UFLPInstance::getNumFacilities() const {
    return numFacilities;
}

int UFLPInstance::getNumClients() const {
    return numClients;
}

const std::vector<int>& UFLPInstance::getOpeningCosts() const {
    return openingCosts;
}

const std::vector<std::vector<int>>& UFLPInstance::getServiceCosts() const {
    return serviceCosts;
}