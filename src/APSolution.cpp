#include "APSolution.h"
#include <ostream>

APSolution::APSolution() : totalCost(0) {}

void APSolution::setAssignment(const std::vector<int>& assign) {
    assignment = assign;
}

const std::vector<int>& APSolution::getAssignment() const {
    return assignment;
}

void APSolution::computeCost(const std::vector<std::vector<int>>& costMatrix) {
    totalCost = 0;
    for (size_t i = 0; i < assignment.size(); ++i) {
        totalCost += costMatrix[i][assignment[i]];
    }
}

int APSolution::getTotalCost() const {
    return totalCost;
}

std::ostream &APSolution::print(std::ostream& os) const {
    os << "AP Solution:\n";
    os << "Total Cost: " << totalCost << "\n";
    os << "Assignment (agent -> task):\n";
    for (size_t i = 0; i < assignment.size(); ++i) {
        os << "Agent " << i << " -> Task " << assignment[i] << "\n";
    }
    return os;
}
