#include <stdexcept>
#include <vector>
#include <limits>

#include "APSolver.h"
#include "APInstance.h"
#include "APSolution.h"

std::shared_ptr<ProblemSolution> APSolver::solve(const ProblemInstance* instance) {
    const APInstance* apInst = dynamic_cast<const APInstance*>(instance);
    if (!apInst) {
        throw std::invalid_argument("You need to create an Instance first.");
    }

    const auto& costMatrix = apInst->getCostMatrix();
    int n = apInst->getNumAgents();  // agenti = tasks

    // assegna a ogni agente il task libero a costo minimo
    std::vector<bool> usedTask(n, false);
    std::vector<int> assignment(n, -1);

    for (int i = 0; i < n; ++i) {
        int bestTask = -1;
        int bestCost = std::numeric_limits<int>::max();
        for (int j = 0; j < n; ++j) {
            if (!usedTask[j] && costMatrix[i][j] < bestCost) {
                bestCost = costMatrix[i][j];
                bestTask = j;
            }
        }
        if (bestTask < 0) {
            throw std::runtime_error("APSolver: impossibile trovare task disponibile per agente " + std::to_string(i));
        }
        assignment[i] = bestTask;
        usedTask[bestTask] = true;
    }

    auto solution = std::make_shared<APSolution>();
    solution->setAssignment(assignment);
    solution->computeCost(costMatrix);
    return solution;
}