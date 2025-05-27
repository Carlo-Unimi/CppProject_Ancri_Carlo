#ifndef UFLPSOLVER_H
#define UFLPSOLVER_H

#include <vector>

#include "ProblemSolver.h"

class UFLPSolver : public ProblemSolver {
private:
    void sortStructure(std::vector<std::pair<double, int>>& score);
public:
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
