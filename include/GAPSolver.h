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
     * 
     * @details The strategy used is critically drive, where more difficult tasks are assigned first, in order to avoid infeasible solutions.
     * - First of all, the tasks are ordered by criticality, which is defined as the number of agents that can perform the task.
     * - The algorithm assigns tasks to agents in the order of criticality, assigning each task to the agent that can perform it with the lowest cost.
     * - If no agent has enough residual capacity, it chooses the agent with the leas capacity overflow (as a fallback); then it updates the residual capacities of the agents.
     * - After attempting to assign all tasks, it checks if all tasks have been assigned; if not, throws a runtime error.
     * - Once all tasks are assigned, it computes the total resources used and the total cost of the assignment and builds a GAPSolution object. (It sets the assignment, computes resources and cost, and returns it.)
     */
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;
};

#endif
