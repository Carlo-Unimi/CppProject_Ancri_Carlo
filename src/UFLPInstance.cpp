// src/UFLPInstance.cpp
#include "UFLPInstance.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void UFLPInstance::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    bool readingService = false;
    bool readingOpening = false;
    int currentRow = 0;

    while (std::getline(infile, line)) {
        if (line.empty()) continue;
        // trim leading spaces
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);

        if (line.rfind("m:", 0) == 0) {
            std::istringstream ss(line.substr(2));
            ss >> numFacilities;
            continue;
        }
        if (line.rfind("n:", 0) == 0) {
            std::istringstream ss(line.substr(2));
            ss >> numClients;
            serviceCosts.resize(numFacilities);
            continue;
        }
        if (line.find("c_ij:") != std::string::npos) {
            readingService = true;
            readingOpening = false;
            currentRow = 0;
            continue;
        }
        if (line.find("f_i:") != std::string::npos) {
            readingService = false;
            readingOpening = true;
            openingCosts.clear();
            continue;
        }
        if (readingService) {
            if (currentRow >= numFacilities) break;
            std::istringstream ss(line);
            int v;
            while (ss >> v) {
                serviceCosts[currentRow].push_back(v);
            }
            if (serviceCosts[currentRow].size() != static_cast<size_t>(numClients)) {
                throw std::runtime_error("Wrong number of columns in row " + std::to_string(currentRow));
            }
            ++currentRow;
        } else if (readingOpening) {
            std::istringstream ss(line);
            int v;
            while (ss >> v) {
                openingCosts.push_back(v);
            }
        }
    }

    // Validazioni finali
    if (serviceCosts.size() != static_cast<size_t>(numFacilities)) {
        throw std::runtime_error("Number of serviceCosts rows different from m");
    }
    if (openingCosts.size() != static_cast<size_t>(numFacilities)) {
        throw std::runtime_error("Number of openingCosts elements different from m");
    }
}

// Getter implementations
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