#ifndef APSOLVER_H
#define APSOLVER_H

#include "ProblemSolver.h"

class APSolver : public ProblemSolver {
public:

    /**
     * @brief Solves the given assignment assignment problem instance.
     * @param instance The assignment problem instance to be solved.
     * @return A unique pointer to the solution of the assignment problem.
     * 
     * @details This is a simple greedy algorithm that assigns agents to tasks one by one:
     * - For each agent, it selects the cheapest available task
     * - Once a task is assigned, it becomes unavailable for other agents
     * - It proceeds sequentially through the agents and does not backtrack
     * This approach does not guarantee optimality, but it provides a feasible assignment.
     * 
     * @throws std::runtime_error if it is not possible to assign all agents to tasks.
     */
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
