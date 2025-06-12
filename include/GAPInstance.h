#ifndef GAPINSTANCE_H
#define GAPINSTANCE_H

#include "ProblemInstance.h"
#include <vector>

class GAPInstance : public ProblemInstance {
private:

    int numTasks; // Number of tasks in the problem instance
    int numAgents; // Number of agents in the problem instance
    std::vector<std::vector<int>> cost; // Cost matrix representing the costs associated with each agent and task
    std::vector<std::vector<int>> resource; // Resource matrix representing the resources required by each agent for each task
    std::vector<int> capacities; // Capacities of each agent, representing the maximum resources they can provide

public:

    /**
     * @brief Loads the generalized assignment problem instance from a file.
     * @param filename The name of the file containing the generalized assignment problem instance.
     * @note The file should contain the cost matrix, resource matrix, and capacities of agents.
     */
    void loadFromFile(const std::string& filename) override;

    /**
     * @brief Getter for the cost matrix.
     * @return A reference to the cost matrix.
     */
    const std::vector<std::vector<int>>& getCostMatrix() const;

    /**
     * @brief Getter for the resource matrix.
     * @return A reference to the resource matrix.
     */
    const std::vector<std::vector<int>>& getResourceMatrix() const;

    /**
     * @brief Getter for the capacities of agents.
     * @return A reference to the vector of capacities.
     */
    const std::vector<int>& getCapacities() const;

    /**
     * @brief Getter for the number of tasks in the problem instance.
     * @return The number of tasks.
     */
    int getNumTasks() const;

    /**
     * @brief Getter for the number of agents in the problem instance.
     * @return The number of agents.
     */
    int getNumAgents() const;

};

#endif
