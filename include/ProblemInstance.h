#ifndef PROBLEMINSTANCE_H
#define PROBLEMINSTANCE_H

#include <string>

class ProblemInstance {
public:
    virtual void loadFromFile(const std::string& filename) = 0;
    virtual ~ProblemInstance() = default;
};

#endif // PROBLEMINSTANCE_H
