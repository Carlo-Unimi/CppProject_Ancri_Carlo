#ifndef GAPINSTANCE_H
#define GAPINSTANCE_H

#include "ProblemInstance.h"
#include <vector>

class GAPInstance : public ProblemInstance {
private:
    int numTasks;
    int numAgents;
    std::vector<std::vector<int>> cost;
    std::vector<std::vector<int>> resource;
    std::vector<int> capacities;

public:
    void loadFromFile(const std::string& filename) override;

    const std::vector<std::vector<int>>& getCostMatrix() const;
    const std::vector<std::vector<int>>& getResourceMatrix() const;
    const std::vector<int>& getCapacities() const;
    int getNumTasks() const;
    int getNumAgents() const;

};

#endif
