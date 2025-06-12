#include "GAPSolver.h"
#include "GAPInstance.h"
#include "GAPSolution.h"

#include <stdexcept>
#include <limits>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <algorithm>

std::unique_ptr<ProblemSolution> GAPSolver::solve(const ProblemInstance* instance) {
    const GAPInstance* gapInst = dynamic_cast<const GAPInstance*>(instance);
    if (!gapInst)
        throw std::invalid_argument("GAPSolver:: solve requires a GAPInstance");

    int m = gapInst->getNumAgents();
    int n = gapInst->getNumTasks();
    const auto& cost = gapInst->getCostMatrix();
    const auto& resource = gapInst->getResourceMatrix();
    const auto& capacity = gapInst->getCapacities();

    // a critic task is one that has the least number of feasible agents
    std::vector<std::pair<int, int>> taskCriticality; // (num_feasible_agents, task_id)
    
    for (int j = 0; j < n; ++j) {
        int feasibleAgents = 0;
        for (int i = 0; i < m; ++i) {
            if (resource[i][j] <= capacity[i]) {
                feasibleAgents++;
            }
        }
        taskCriticality.push_back({feasibleAgents, j});
    }
    
    // order by criticality (least feasible agents first)
    std::sort(taskCriticality.begin(), taskCriticality.end());

    std::vector<int> assignment(n, -1);
    std::vector<int> residual = capacity;
    
    // assign tasks to agents (ordered by criticality)
    for (const auto& pair : taskCriticality) {
        int j = pair.second;
        
        int bestAgent = -1;
        int bestCost = std::numeric_limits<int>::max();
        
        // first agent that can do the task
        for (int i = 0; i < m; ++i) {
            if (resource[i][j] <= residual[i] && cost[i][j] < bestCost) {
                bestCost = cost[i][j];
                bestAgent = i;
            }
        }
        
        // if no agent can do the task, find the one with the least overflow (shouldn't happen)
        if (bestAgent == -1) {
            int minOverflow = std::numeric_limits<int>::max();
            for (int i = 0; i < m; ++i) {
                int overflow = resource[i][j] - residual[i];
                if (overflow < minOverflow) {
                    minOverflow = overflow;
                    bestAgent = i;
                }
            }
        }
        
        assignment[j] = bestAgent;
        residual[bestAgent] -= resource[bestAgent][j];
    }
    
    // check if all tasks are assigned
    for (int j = 0; j < n; ++j) {
        if (assignment[j] == -1)
            throw std::runtime_error("GAPSolver::solve: not all tasks assigned");
    }
    
    auto solution = std::make_unique<GAPSolution>();
    solution->setAssignment(assignment);
    solution->computeResourcesAndCost(cost, resource);
    return solution;
}