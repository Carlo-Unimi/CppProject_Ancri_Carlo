#ifndef PROBLEMSOLUTION_H
#define PROBLEMSOLUTION_H

#include <ostream>
#include <string>

class ProblemSolution {
protected:
    // Stampa la soluzione sullo stream; implementata nelle sottoclassi
    virtual void print(std::ostream& os) const = 0;

public:
    virtual ~ProblemSolution() = default;

    // Operatore di stream per tutte le soluzioni
    friend std::ostream& operator<<(std::ostream& os, const ProblemSolution& sol) {
        sol.print(os);
        return os;
    }
};

#endif