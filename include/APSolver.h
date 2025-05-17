#ifndef APSOLVER_H
#define APSOLVER_H

#include "ProblemSolver.h"

class APSolver : public ProblemSolver {
public:
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
