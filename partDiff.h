#ifndef __PARTDIFF_H_INCLUDED__
#define __PARTDIFF_H_INCLUDED__
#include "fvMatrix.h"
#include "scalarField.h"

class partDiff {
public:
    static fvMatrix laplacian(double diffCoeff, scalarField &scf);
};

#endif
