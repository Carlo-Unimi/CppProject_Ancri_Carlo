#ifndef UFLPSOLVER_H
#define UFLPSOLVER_H

#include <vector>

#include "ProblemSolver.h"

class UFLPSolver : public ProblemSolver {
private:

    /**
     * @brief Sort a list of (score, index) pairs in ascending order by score.
     * @param score A reference to the vector of pairs to be sorted. Each element score[i] is a std::pair<double,int> whose first member is used as the sorting key.
     */
    void sortStructure(std::vector<std::pair<double, int>>& score);

public:

    /**
     * @brief Solves the given uncapacitated facility location problem instance.
     * @param instance The uncapacitated facility location problem instance to be solved.
     * @return A unique pointer to the solution of the uncapacitated facility location problem.
     * 
     * @details The strategy used is a greedy local search algorithm.
     * - This function first constructs an initial facility opening configuration by selecting approximately one third of all facilities with the best combined opening‐and‐average‐service cost.
     * - It then applies a local search that toggles each facility open/closed, accepting any change that lowers the total cost (opening + service) until no further improvement is possible.
     * - Finally, each client is assigned to its nearest open facility.
     * - Once all clients are assigned, it computes the total cost of the solution and builds a UFLPSolution object. (It sets the assignment, computes the total cost, and returns it.)
     */
    std::unique_ptr<ProblemSolution> solve(const ProblemInstance* instance) override;

};

#endif
