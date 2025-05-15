#ifndef GAPSOLUTION_H
#define GAPSOLUTION_H

#include "ProblemSolution.h"
#include <vector>

class GAPSolution : public ProblemSolution {
private:
    std::vector<int> assignment; // assignment[j] = agente a cui è assegnato il task j
    std::vector<int> capacityUsed; // capacityUsed[i] = risorsa usata dall'agente i
    int totalCost;

protected:
    void print(std::ostream& os) const override;

public:
    GAPSolution();

    void setAssignment(const std::vector<int>& assign);
    const std::vector<int>& getAssignment() const;

    void computeResourcesAndCost(
        const std::vector<std::vector<int>>& cost,
        const std::vector<std::vector<int>>& resource);
    int getTotalCost() const;
    const std::vector<int>& getCapacityUsed() const;
};

#endif