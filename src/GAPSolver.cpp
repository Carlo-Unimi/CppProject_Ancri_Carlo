#include "GAPSolver.h"
#include "GAPInstance.h"
#include "GAPSolution.h"

#include <stdexcept>
#include <limits>
#include <vector>
#include <time.h>
#include <cstdlib>

void GAPSolver::shuffleIndex(std::vector<int>& index) {
    srand(time(NULL));
    for (size_t i = 0; i < index.size(); ++i) {
        int j = rand() % index.size();
        std::swap(index[i], index[j]);
    }
}

std::unique_ptr<ProblemSolution> GAPSolver::solve(const ProblemInstance* instance) {
    const GAPInstance* gapInstance = dynamic_cast<const GAPInstance*>(instance);

    int m = gapInstance->getNumAgents();
    int n = gapInstance->getNumTasks();
    const auto& cost = gapInstance->getCostMatrix();
    const auto& resource = gapInstance->getResourceMatrix();
    const auto& capacity = gapInstance->getCapacities();

    std::vector<int> resid = capacity;
    std::vector<int> assignment(n, -1);

    

    auto solution = std::make_unique<GAPSolution>();
    solution->setAssignment(assignment);
    solution->computeResourcesAndCost(cost, resource);
    return solution;
}
