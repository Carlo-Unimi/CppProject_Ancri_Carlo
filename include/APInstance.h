#ifndef APINSTANCE_H
#define APINSTANCE_H

#include "ProblemInstance.h"
#include <vector>

class APInstance : public ProblemInstance {
private:
    std::vector<std::vector<int>> costMatrix;
    int numAgents;
    int numTasks;

public:
    void loadFromFile(const std::string& filename);

    const std::vector<std::vector<int>>& getCostMatrix() const;
    int getNumAgents() const;
    int getNumTasks() const;

};

#endif
