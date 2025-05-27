#include "UFLPSolver.h"
#include "UFLPInstance.h"
#include "UFLPSolution.h"
#include <memory>
#include <vector>
#include <limits>
#include <iostream>

void UFLPSolver::sortStructure(std::vector<std::pair<double, int>>& score) {
    size_t n = score.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (score[j].first < score[minIndex].first) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(score[i], score[minIndex]);
        }
    }
}

std::unique_ptr<ProblemSolution> UFLPSolver::solve(const ProblemInstance* instance) {
    const UFLPInstance* uflpInst = dynamic_cast<const UFLPInstance*>(instance);

    int m = uflpInst->getNumFacilities();
    int n = uflpInst->getNumClients();
    const auto& cost = uflpInst->getServiceCosts();
    const auto& openCost = uflpInst->getOpeningCosts();

    std::vector<bool> openFacility(m, false);
    std::vector<int> assignment(n, -1);

    std::vector<std::pair<double, int>> score;
    for (int i = 0; i < m; ++i) {
        double avgService = 0;
        for (int j = 0; j < n; ++j)
            avgService += cost[i][j];
        avgService /= n;
        score.push_back({ openCost[i] + avgService, i });
    }

    sortStructure(score);

    int initialOpen = std::max(1, m / 3);
    for (int k = 0; k < initialOpen; ++k)
        openFacility[score[k].second] = true;

    auto computeTotalCost = [&](const std::vector<bool>& openF) -> int {
        int total = 0;
        for (int i = 0; i < m; ++i)
            if (openF[i]) total += openCost[i];
        for (int j = 0; j < n; ++j) {
            int minC = std::numeric_limits<int>::max();
            for (int i = 0; i < m; ++i)
                if (openF[i])
                    minC = std::min(minC, cost[i][j]);
            total += minC;
        }
        return total;
    };

    int bestCost = computeTotalCost(openFacility);
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 0; i < m; ++i) {
            std::vector<bool> trial = openFacility;
            trial[i] = !trial[i]; // toggle

            int trialCost = computeTotalCost(trial);
            if (trialCost < bestCost) {
                openFacility = trial;
                bestCost = trialCost;
                improved = true;
                break;
            }
        }
    }

    for (int j = 0; j < n; ++j) {
        int bestI = -1;
        int minC = std::numeric_limits<int>::max();
        for (int i = 0; i < m; ++i) {
            if (openFacility[i] && cost[i][j] < minC) {
                minC = cost[i][j];
                bestI = i;
            }
        }
        assignment[j] = bestI;
    }

    auto solution = std::make_unique<UFLPSolution>();
    solution->setOpenFacilities(openFacility);
    solution->setAssignment(assignment);
    solution->computeCost(openCost, cost);

    return solution;
}
