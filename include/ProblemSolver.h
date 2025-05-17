// include/ProblemSolver.h
#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include "ProblemInstance.h"
#include "ProblemSolution.h"
#include <memory>

class ProblemSolver {
public:
    virtual std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) = 0;
    virtual ~ProblemSolver() = default;
};

#endif
