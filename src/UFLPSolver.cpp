#include "UFLPSolver.h"
#include "UFLPInstance.h"
#include "UFLPSolution.h"
#include <memory>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
std::unique_ptr<ProblemSolution> UFLPSolver::solve(const ProblemInstance* instance) {
    const UFLPInstance* uflpInst = dynamic_cast<const UFLPInstance*>(instance);
    if (!uflpInst) {
        throw std::invalid_argument("UFLPSolver::solve richiede un UFLPInstance.");
    }

    int m = uflpInst->getNumFacilities();
    int n = uflpInst->getNumClients();
    const auto& cost = uflpInst->getServiceCosts();     // m x n
    const auto& openCost = uflpInst->getOpeningCosts(); // m

    std::vector<bool> openFacility(m, false);     // inizialmente tutte chiuse
    std::vector<int> assignment(n, -1);

    // STEP 1: apri facility iniziali con rapporto costo apertura medio
    std::vector<std::pair<double, int>> score; // (costo medio, index)
    for (int i = 0; i < m; ++i) {
        double avgService = 0;
        for (int j = 0; j < n; ++j)
            avgService += cost[i][j];
        avgService /= n;
        score.push_back({ openCost[i] + avgService, i });
    }

    std::sort(score.begin(), score.end());  // preferisco le più convenienti

    int initialOpen = std::max(1, m / 3); // apri circa un terzo
    for (int k = 0; k < initialOpen; ++k) {
        openFacility[score[k].second] = true;
    }

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

    // STEP 2: Local Search (apri o chiudi se migliora)
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
                break;  // accetta subito la modifica
            }
        }
    }

    // STEP 3: assegna ogni cliente alla facility più vicina tra quelle aperte
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
