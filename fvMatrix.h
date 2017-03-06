#ifndef __FVMATRIX_H_INCLUDED__
#define __FVMATRIX_H_INCLUDED__
#include "Utils.h"

class fvMatrix {
public:
    int matSize; //size of Matrix 
    matrix lhMatrix;
    source rhSource;
    fvMatrix(int nCells);
    void showMatrix();
    fvMatrix& operator+=(const fvMatrix &fvm);
    fvMatrix operator+(const fvMatrix& fvm);

};

#endif
