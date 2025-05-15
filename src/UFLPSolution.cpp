#include "UFLPSolution.h"
#include <ostream>

UFLPSolution::UFLPSolution() : totalCost(0) {}

void UFLPSolution::setOpenFacilities(const std::vector<bool>& opens) {
    openFacilities = opens;
}

const std::vector<bool>& UFLPSolution::getOpenFacilities() const {
    return openFacilities;
}

void UFLPSolution::setAssignment(const std::vector<int>& assign) {
    assignment = assign;
}

const std::vector<int>& UFLPSolution::getAssignment() const {
    return assignment;
}

void UFLPSolution::computeCost(
    const std::vector<int>& openingCost,
    const std::vector<std::vector<int>>& serviceCost) {
    totalCost = 0;
    for (size_t i = 0; i < openFacilities.size(); ++i) {
        if (openFacilities[i]) totalCost += openingCost[i];
    }
    for (size_t j = 0; j < assignment.size(); ++j) {
        totalCost += serviceCost[assignment[j]][j];
    }
}

int UFLPSolution::getTotalCost() const {
    return totalCost;
}

void UFLPSolution::print(std::ostream& os) const {
    os << "UFLP Solution:\n";
    os << "Total Cost: " << totalCost << "\n";
    os << "Open Facilities:\n";
    for (size_t i = 0; i < openFacilities.size(); ++i) {
        if (openFacilities[i]) os << "Facility " << i << " is open\n";
    }
    os << "Assignment (client -> facility):\n";
    for (size_t j = 0; j < assignment.size(); ++j) {
        os << "Client " << j << " -> Facility " << assignment[j] << "\n";
    }
}