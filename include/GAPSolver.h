#ifndef GAPSOLVER_H
#define GAPSOLVER_H

#include <vector>

#include "ProblemSolver.h"

class GAPSolver : public ProblemSolver {
private:
    void shuffleIndex(std::vector<int>& index);
public:
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
