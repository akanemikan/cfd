#include "fvMatrix.h"

fvMatrix::fvMatrix(int nCells)
{
    matSize = nCells;
    lhMatrix = matrix(nCells, source(nCells));
    rhSource = source(nCells);
}

void fvMatrix::showMatrix()
{
    for(int c=0; c<matSize; c++){
        for(int r=0; r<matSize; r++){
            cout << lhMatrix[c][r] << "\t";
        }
        cout << rhSource[c] << endl;
    }
}

fvMatrix& fvMatrix::operator+=(const fvMatrix &fvm){
    for(int c=0; c<this->matSize; c++){
        for(int r=0; r<this->matSize; r++){
            this->lhMatrix[c][r] +=fvm.lhMatrix[c][r];
        }
        this->rhSource[c] += fvm.rhSource[c];
    }
    return *this;
}

fvMatrix fvMatrix::operator+(const fvMatrix& fvm1){
    fvMatrix fvm = *this;
    fvm += fvm1;
    return fvm;
}
