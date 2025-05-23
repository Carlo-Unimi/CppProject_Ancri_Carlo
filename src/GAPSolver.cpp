#include "GAPSolver.h"
#include "GAPInstance.h"
#include "GAPSolution.h"

#include <stdexcept>
#include <limits>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>

void GAPSolver::shuffleIndex(std::vector<int>& index) {
    srand(time(NULL));
    for (size_t i = 0; i < index.size(); ++i) {
        int j = rand() % index.size();
        std::swap(index[i], index[j]);
    }
}

std::unique_ptr<ProblemSolution> GAPSolver::solve(const ProblemInstance* instance) {
    const GAPInstance* gapInst = dynamic_cast<const GAPInstance*>(instance);
    if (!gapInst) 
        throw std::invalid_argument("GAPSolver::solve richiede un GAPInstance valido");

    int m = gapInst->getNumAgents();
    int n = gapInst->getNumTasks();
    const auto& cost = gapInst->getCostMatrix();
    const auto& resource = gapInst->getResourceMatrix();
    const auto& capacity = gapInst->getCapacities();

    std::vector<int> agentIndex(m);
    for (int i = 0; i < m; ++i) agentIndex[i] = i;






    
}