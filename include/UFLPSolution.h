#ifndef UFLPSOLUTION_H
#define UFLPSOLUTION_H

#include "ProblemSolution.h"
#include <vector>

class UFLPSolution : public ProblemSolution {
private:
    std::vector<bool> openFacilities;  // openFacilities[i] = true se la struttura i è aperta
    std::vector<int> assignment;       // assignment[j] = struttura a cui è assegnato il cliente j
    int totalCost;

protected:
    void print(std::ostream& os) const override;

public:
    UFLPSolution();

    void setOpenFacilities(const std::vector<bool>& opens);
    const std::vector<bool>& getOpenFacilities() const;

    void setAssignment(const std::vector<int>& assign);
    const std::vector<int>& getAssignment() const;

    void computeCost(
        const std::vector<int>& openingCost,
        const std::vector<std::vector<int>>& serviceCost);
    int getTotalCost() const;
};

#endif