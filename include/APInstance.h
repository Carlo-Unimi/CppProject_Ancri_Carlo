#ifndef APINSTANCE_H
#define APINSTANCE_H

#include "ProblemInstance.h"
#include <vector>

class APInstance : public ProblemInstance {
private:

    std::vector<std::vector<int>> costMatrix; // Cost matrix representing the costs associated with each agent and task
    int numAgents; // Number of agents in the problem instance

public:

    /**
     * @brief Loads the assignment problem instance from a file.
     * @param filename The name of the file containing the assignment problem instance.
     * @note The file should contain a square matrix representing the costs associated with each agent and task.
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Getter for the cost matrix.
     * @return A reference to the cost matrix.
     * @note The cost matrix is a 2D vector where costMatrix[i][j] represents the cost for agent i to perform task j.
     */
    const std::vector<std::vector<int>>& getCostMatrix() const;

    /**
     * @brief Getter for the number of agents.
     * @return The number of agents in the assignment problem instance.
     */
    int getNumAgents() const;

};

#endif
