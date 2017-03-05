#include "fvMatrix.h"

fvMatrix::fvMatrix(int nCells)
{
    sMat = nCells;
    lhMatrix = matrix(nCells, source(nCells));
    rhSource = source(nCells);
}

void fvMatrix::showMat()
{
    for(int c=0; c<sMat; c++){
        for(int r=0; r<sMat; r++){
            cout << lhMatrix[c][r] << "\t";
        }
        cout << rhSource[c] << endl;
    }
}

fvMatrix& fvMatrix::operator+=(const fvMatrix &fvm){
    for(int c=0; c<this->sMat; c++){
        for(int r=0; r<this->sMat; r++){
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
