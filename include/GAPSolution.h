#ifndef GAPSOLUTION_H
#define GAPSOLUTION_H

#include "ProblemSolution.h"
#include <vector>

class GAPSolution : public ProblemSolution {
private:

    std::vector<int> assignment; // Assignment vector where assignment[i] is the task assigned to agent i
    std::vector<int> capacityUsed; // Capacity used by each agent, where capacityUsed[i] is the total resources used by agent i
    int totalCost; // Total cost of the assignment

protected:

    /**
     * @brief Prints the solution to the given output stream.
     * @param os The output stream to which the solution will be printed.
     * @return A reference to the output stream after printing the solution.
     */
    std::ostream &print(std::ostream &) const override;

public:

    /**
     * @brief Standard constructor for the GAPSolution class.
     * @note Initializes the total cost to a default value (0).
     */
    GAPSolution();

    /**
     * @brief Sets the assignment attribute for the solution class.
     * @param assign A vector where assign[i] is the task assigned to agent i.
     */
    void setAssignment(const std::vector<int>& assign);

    /**
     * @brief Gets the assignment attribute for the solution class.
     * @return A reference to the assignment vector.
     * @note The assignment vector contains the task assigned to each agent, where assignment[i] is the task assigned to agent i.
     */
    const std::vector<int>& getAssignment() const;

    /**
     * @brief Computes the total cost of the assignment based on the provided cost matrix.
     * @param cost A 2D vector representing the costs associated with each agent and task.
     * @param resource A 2D vector representing the resources required by each agent for each task.
     * @note The cost[i][j] represents the cost for agent i to perform task j, and resource[i][j] represents the resources required by agent i for task j. The total cost is computed as the sum of costs for each agent-task assignment, and the capacity used by each agent is updated accordingly.
     */
    void computeResourcesAndCost(const std::vector<std::vector<int>>& cost, const std::vector<std::vector<int>>& resource);

    /**
     * @brief Gets the total cost (calculated by GAPSolution::computeResourcesAndCost) of the assignment.
     * @return The total cost of the assignment.
     */
    int getTotalCost() const;

    /**
     * @brief Gets the capacity used by each agent.
     * @return A reference to the vector of capacities used by each agent.
     * @note The capacityUsed vector contains the total resources used by each agent, where capacityUsed[i] is the total resources used by agent i.
     */
    const std::vector<int>& getCapacityUsed() const;
};

#endif