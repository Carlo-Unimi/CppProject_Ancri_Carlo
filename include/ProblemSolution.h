#ifndef PROBLEMSOLUTION_H
#define PROBLEMSOLUTION_H

#include <ostream>
#include <string>

class ProblemSolution {
protected:
    virtual std::ostream &print(std::ostream &) const = 0;
public:
    virtual ~ProblemSolution() = default;

    friend std::ostream& operator<<(std::ostream& os, const ProblemSolution& sol) {
        sol.print(os);
        return os;
    }
};

#endif