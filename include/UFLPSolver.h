#ifndef UFLPSOLVER_H
#define UFLPSOLVER_H

#include "ProblemSolver.h"

class UFLPSolver : public ProblemSolver {
public:
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
