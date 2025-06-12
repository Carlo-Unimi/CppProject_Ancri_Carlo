#ifndef GAPSOLVER_H
#define GAPSOLVER_H

#include <vector>

#include "ProblemSolver.h"

class GAPSolver : public ProblemSolver {
public:

    /**
     * @brief Solves the given generalized assignment problem instance.
     * @param instance The generalized assignment problem instance to be solved.
     * @return A unique pointer to the solution of the generalized assignment problem.
     * @details 
     */
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
