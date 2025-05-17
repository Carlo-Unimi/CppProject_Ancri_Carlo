#ifndef GAPSOLVER_H
#define GAPSOLVER_H

#include "ProblemSolver.h"

class GAPSolver : public ProblemSolver {
public:
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
