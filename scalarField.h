#ifndef __SCALARFIELD_H_INCLUDED__
#define __SCALARFIELD_H_INCLUDED__
#include "Mesh.h"
#include "Utils.h"

class scalarField {
public:
    scalarField(Mesh &mesh);
    Mesh mesh;
    source vals;
    matrix boundVals;
    void readValFileAndSet();
    source calcPtAvr(ofstream &ofs);
    void writeResult();
};

#endif
