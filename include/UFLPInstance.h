// include/UFLPInstance.h
#ifndef UFLPINSTANCE_H
#define UFLPINSTANCE_H

#include "ProblemInstance.h"
#include <vector>
#include <string>

class UFLPInstance : public ProblemInstance {
private:
    int numFacilities;                          // m
    int numClients;                             // n
    std::vector<int> openingCosts;              // f_i, dimension m
    std::vector<std::vector<int>> serviceCosts; // c_ij, dimensions m × n

public:
    void loadFromFile(const std::string& filename) override;

    int getNumFacilities() const;
    int getNumClients() const;
    const std::vector<int>& getOpeningCosts() const;
    const std::vector<std::vector<int>>& getServiceCosts() const;
};

#endif
