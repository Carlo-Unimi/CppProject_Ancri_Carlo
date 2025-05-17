#include "GAPSolver.h"
#include "GAPInstance.h"
#include "GAPSolution.h"

#include <stdexcept>
#include <limits>
#include <vector>

std::unique_ptr<ProblemSolution> GAPSolver::solve(const ProblemInstance* instance) {
    const GAPInstance* gapInstance = dynamic_cast<const GAPInstance*>(instance);

    int m = gapInstance->getNumAgents();
    int n = gapInstance->getNumTasks();
    const auto& cost = gapInstance->getCostMatrix();
    const auto& resource = gapInstance->getResourceMatrix();
    const auto& capacity = gapInstance->getCapacities();

    std::vector<int> resid = capacity;
    std::vector<int> assignment(n, -1);

    for (int i=0; i<n; ++i) {
        int bestAgent = -1, bestCost = std::numeric_limits<int>::max();
        for (int j=0; j<m; ++j) {
            if (resource[j][i] <= resid[j] && cost[j][i] < bestCost) {
                bestCost = cost[j][i];
                bestAgent = j;
            }
        }

        if (bestAgent == -1)
            throw std::runtime_error("Couldn't assign task: "+ std::to_string(i));
        
        assignment[i] = bestAgent;
        resid[bestAgent] -= resource[bestAgent][i];
    }

    auto solution = std::make_unique<GAPSolution>();
    solution->setAssignment(assignment);
    solution->computeResourcesAndCost(cost, resource);
    return solution;
}
