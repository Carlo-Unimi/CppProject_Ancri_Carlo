#ifndef PROBLEMINSTANCE_H
#define PROBLEMINSTANCE_H

#include <string>

/**
 * @file ProblemInstance.h
 * @brief Declaration of the ProblemInstance class, which represents a problem instance to be solved.
 *
 * The ProblemInstance class serves as an abstract base for all problem-specific input data structures. It defines the interface for loading and accessing information about a particular optimization problem instance, sush as cost matrices, capacity constraints, or resource requirements.
 * Each subclass extends this insteface to handle its own data format and logic for parsing files.
 */
class ProblemInstance {
public:

    /**
     * @brief Loads the problem instance from a file.
     * @param filename The name of the file containing the problem instance.
     * @note The file format and content should be defined by the specific problem being solved.
     */
    virtual void loadFromFile(const std::string& filename) = 0;
    
    /**
     * @brief Standard destructor for the ProblemInstance class.
     * @note This destructor is virtual to ensure proper cleanup of derived classes.
     */
    virtual ~ProblemInstance() = default;
};

#endif
