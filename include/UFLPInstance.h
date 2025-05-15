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
    std::vector<int> openingCosts;              // f_i, dimensione m
    std::vector<std::vector<int>> serviceCosts; // c_ij, dimensione m × n

public:
    // Carica l'istanza da file nel formato:
    // NAME: ...
    // m: <numFacilities>
    // n: <numClients>
    // c_ij:
    //   <m righe di n valori ciascuna>
    // f_i:
    //   <linea con m valori>
    void loadFromFile(const std::string& filename) override;

    // Getter
    int getNumFacilities() const;
    int getNumClients() const;
    const std::vector<int>& getOpeningCosts() const;
    const std::vector<std::vector<int>>& getServiceCosts() const;
};

#endif // UFLPINSTANCE_H
