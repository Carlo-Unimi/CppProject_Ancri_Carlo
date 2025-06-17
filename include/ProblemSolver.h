#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include "ProblemInstance.h"
#include "ProblemSolution.h"
#include <memory>

/**
 * @file ProblemSolver.h
 * @brief Declaration of the ProblemSolver class, which is responsible for solving problem instances.
 *
 * The ProblemSolver class defines the general interface for any algorithm or heuristic designed to solve a given optimization problem. It takes a ProblemInstance as input and produces a ProblemSolution.
 * Concrete implementations (such as APSolver, GAPSolver, UFLPSolver) encapsulate the logic required to compute feasible or optimal assignments based on the structure of the specific problem.
 */
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
