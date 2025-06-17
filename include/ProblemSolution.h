#ifndef PROBLEMSOLUTION_H
#define PROBLEMSOLUTION_H

#include <ostream>
#include <string>

/**
 * @file ProblemSolution.h
 * @brief Declaration of the ProblemSolution class, which represents a solution to a problem instance.
 *
 * The ProblemSolution class is the abstract base that encapsulates the output of a solver. It holds the final decisions made by the algorithm—such as task assignments, facility openings, or resource usages—and provides methods for evaluating their cost or validity.
 * Derived classes like APSolution, GAPSolution, and UFLPSolution implement problem-specific logic to compute objective values and display results in a readable format.
 */
class ProblemSolution {
protected:
    /**
     * @brief Prints the solution to the given output stream.
     * @param os The output stream to which the solution will be printed.
     * @return A reference to the output stream after printing the solution.
     * @note This method must be implemented by derived classes to provide specific solution details.
     */
    virtual std::ostream &print(std::ostream &) const = 0;

public:

    /**
     * @brief Standard destructor for the ProblemSolution class.
     * @note This destructor is virtual to ensure proper cleanup of derived classes.
     */
    virtual ~ProblemSolution() = default;

    /**
     * @brief Outputs the solution to the given output stream.
     * @param os The output stream to which the solution will be printed.
     * @return A reference to the output stream after printing the solution.
     * @note This operator allows the ProblemSolution to be printed directly using the `<<` operator. It calls the `print` method to handle the actual printing, so derived classes must implement `print` to define how the solution is displayed.
     */
    friend std::ostream& operator<<(std::ostream& os, const ProblemSolution& sol) {
        sol.print(os);
        return os;
    }
};

#endif