#ifndef __SOLVER_H_INCLUDED__
#define __SOLVER_H_INCLUDED__
#include "Utils.h"

class Solver {
public:
    static void CGSolver(const matrix &A, const source &b, source &x, int n);
};

#endif
