#ifndef PROBLEMINSTANCE_H
#define PROBLEMINSTANCE_H

#include <string>

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
