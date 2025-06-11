// include/ProblemSolver.h
#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include "ProblemInstance.h"
#include "ProblemSolution.h"
#include <memory>

class ProblemSolver {
public:

    /**
     * @brief Solves the given problem instance.
     * @param instance The problem instance to be solved.
     * @return A unique pointer to the solution of the problem.
     * @note This method must be implemented by derived classes to provide specific solving logic.
     */
    virtual std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) = 0;

    /**
     * @brief Standard destructor for the ProblemSolver class.
     * @note This destructor is virtual to ensure proper cleanup of derived classes.
     */
    virtual ~ProblemSolver() = default;
};

#endif
