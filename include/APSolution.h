#ifndef APSOLUTION_H
#define APSOLUTION_H

#include "ProblemSolution.h"
#include <vector>

class APSolution : public ProblemSolution {
private:
    std::vector<int> assignment; // assignment[i] = task assegnato all'agente i
    int totalCost;

protected:
    void print(std::ostream& os) const override;

public:
    APSolution();

    void setAssignment(const std::vector<int>& assign);
    const std::vector<int>& getAssignment() const;

    void computeCost(const std::vector<std::vector<int>>& costMatrix);
    int getTotalCost() const;
};

#endif