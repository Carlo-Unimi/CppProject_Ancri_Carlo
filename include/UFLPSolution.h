#ifndef UFLPSOLUTION_H
#define UFLPSOLUTION_H

#include "ProblemSolution.h"
#include <vector>

class UFLPSolution : public ProblemSolution {
private:

    std::vector<bool> openFacilities; // openFacilities[i] = true if facility[i] is open, false otherwise
    std::vector<int> assignment; // assignment[j] = facility assigned to client j
    int totalCost; // the total cost of the solution

protected:

    /**
     * @brief Prints the solution to the given output stream.
     * @param os The output stream to which the solution will be printed.
     * @return A reference to the output stream after printing the solution.
     */
    std::ostream &print(std::ostream &) const override;

public:

    /**
     * @brief Standard constructor for the UFLPSolution class.
     * @note Initializes the total cost to a default value (0).
     */
    UFLPSolution();

    /**
     * @brief Sets the open facilities for the solution.
     * @param opens A vector of booleans indicating which facilities are open.
     * @note The size of the vector should match the number of facilities in the problem instance.
     */
    void setOpenFacilities(const std::vector<bool>& opens);

    /**
     * @brief Gets the open facilities for the solution.
     * @return A constant reference to a vector of booleans indicating which facilities are open.
     */
    const std::vector<bool>& getOpenFacilities() const;

    /**
     * @brief Sets the assignment of clients to facilities.
     * @param assign A vector where each element represents the facility assigned to the corresponding client.
     * @note The size of the vector should match the number of clients in the problem instance.
     */
    void setAssignment(const std::vector<int>& assign);

    /**
     * @brief Gets the assignment of clients to facilities.
     * @return A constant reference to a vector where each element represents the facility assigned to the corresponding client.
     */
    const std::vector<int>& getAssignment() const;

    /**
     * @brief Computes the total cost of the solution based on the opening costs and service costs.
     * @param openingCost A vector of integers representing the opening costs for each facility.
     * @param serviceCost A 2D vector of integers representing the service costs from each facility to each client.
     * @note The total cost is calculated as the sum of the opening costs for open facilities and the service costs for assigned clients.
     */
    void computeCost(const std::vector<int>& openingCost, const std::vector<std::vector<int>>& serviceCost);

    /**
     * @brief Gets the total cost of the solution (computed with UFLPSolution::computeCosts).
     * @return The total cost as an integer.
     */
    int getTotalCost() const;

};

#endif