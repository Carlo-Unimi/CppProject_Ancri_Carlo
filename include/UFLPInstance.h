#ifndef UFLPINSTANCE_H
#define UFLPINSTANCE_H

#include "ProblemInstance.h"
#include <vector>
#include <string>

class UFLPInstance : public ProblemInstance {
private:

    int numFacilities; // Number of facilities
    int numClients; // Number of clients
    std::vector<int> openingCosts; // Opening costs for facilities
    std::vector<std::vector<int>> serviceCosts; // Transportation costs from facilities to every client

public:

    /**
     * @brief Loads the uncapacitated facility location problem instance from a file.
     * @param filename The name of the file containing the generalized assignment problem instance.
     * @note The file should contain the number of facilities, number of clients, opening costs for each facility, and service costs from each facility to each client.
     */
    void loadFromFile(const std::string& filename) override;

    /**
     * @brief Getter for the number of facilities.
     * @return The number of facilities.
     */
    int getNumFacilities() const;

    /**
     * @brief Getter for the number of clients.
     * @return The number of clients.
     */
    int getNumClients() const;

    /**
     * @brief Getter for the opening cost of every facility.
     * @return A reference to the opening costs array.
     */
    const std::vector<int>& getOpeningCosts() const;

    /**
     * @brief Getter for the service cost of each client (from a particular facility).
     * @return A reference to the service cost matrix.
     */
    const std::vector<std::vector<int>>& getServiceCosts() const;
};

#endif
