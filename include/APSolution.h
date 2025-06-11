#ifndef APSOLUTION_H
#define APSOLUTION_H

#include "ProblemSolution.h"
#include <vector>

class APSolution : public ProblemSolution {
private:
    std::vector<int> assignment; // Assignment vector where assignment[i] is the task assigned to agent i
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
     * @brief Standard constructor for the APSolution class.
     * @note Initializes the total cost to a default value. [0]
     */
    APSolution();

    /**
     * @brief Sets the assignment for the solution.
     * @param assign A vector where assign[i] is the task assigned to agent i.
     */
    void setAssignment(const std::vector<int>& assign);

    /**
     * @brief Gets the assignment for the solution.
     * @return A reference to the assignment vector.
     * @note The assignment vector contains the task assigned to each agent, where assignment[i] is the task assigned to agent i.
     */
    const std::vector<int>& getAssignment() const;


    /**
     * @brief Computes the total cost of the assignment based on the provided cost matrix.
     * @param costMatrix A 2D vector representing the costs associated with each agent and task.
     * @note The costMatrix[i][j] represents the cost for agent i to perform task j. The total cost is computed as the sum of costs for each agent-task assignment.
     */
    void computeCost(const std::vector<std::vector<int>>& costMatrix);

    /**
     * @brief Gets the total cost (from APSolution::computeCost) of the assignment.
     * @return The total cost of the assignment.
     */
    int getTotalCost() const;
};

#endif