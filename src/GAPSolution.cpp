#include "GAPSolution.h"
#include <ostream>

GAPSolution::GAPSolution() : totalCost(0) {}

void GAPSolution::computeResourcesAndCost(const std::vector<std::vector<int>>& cost, const std::vector<std::vector<int>>& resource) {
    totalCost = 0;
    capacityUsed.assign(resource.size(), 0);
    for (size_t j = 0; j < assignment.size(); ++j) {
        int agent = assignment[j];
        totalCost += cost[agent][j];
        capacityUsed[agent] += resource[agent][j];
    }
}

std::ostream &GAPSolution::print(std::ostream& os) const {
    os << "GAP Solution:\n";
    os << "Total Cost: " << totalCost << "\n";
    os << "Assignment (task -> agent):\n";
    for (size_t j = 0; j < assignment.size(); ++j) {
        os << "Task " << j << " -> Agent " << assignment[j] << "\n";
    }
    os << "Capacity Used per Agent:\n";
    for (size_t i = 0; i < capacityUsed.size(); ++i) {
        os << "Agent " << i << " : " << capacityUsed[i] << "\n";
    }
    return os;
}

void GAPSolution::setAssignment(const std::vector<int>& assign) {
    assignment = assign;
}

const std::vector<int>& GAPSolution::getAssignment() const {
    return assignment;
}

int GAPSolution::getTotalCost() const {
    return totalCost;
}

const std::vector<int>& GAPSolution::getCapacityUsed() const {
    return capacityUsed;
}