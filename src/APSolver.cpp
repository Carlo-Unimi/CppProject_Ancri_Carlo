#include <stdexcept>
#include <vector>
#include <limits>

#include "APSolver.h"
#include "APInstance.h"
#include "APSolution.h"

std::unique_ptr<ProblemSolution> APSolver::solve(const ProblemInstance* instance) {
    auto apInstance = dynamic_cast<const APInstance*>(instance);

    const auto& costMatrix = apInstance->getCostMatrix();
    int n = apInstance->getNumAgents();

    std::vector<bool> used(n, false);
    std::vector<int> assignment(n, -1);

    for (int i=0; i<n; ++i) {
        int bestT = -1;
        int bestCost = std::numeric_limits<int>::max();

        for (int j=0; j<n; ++j) {
            if (!used[j] && costMatrix[i][j]<bestCost) {
                bestCost = costMatrix[i][j];
                bestT = j;
            }
        }

        if (bestT < 0)
            throw std::runtime_error("Couldn't find a free task for agent " + std::to_string(i));
        
        assignment[i] = bestT;
        used[bestT] = true;
    }

    auto solution = std::make_unique<APSolution>();
    solution->setAssignment(assignment);
    solution->computeCost(costMatrix);

    return solution;
}