#ifndef __MESH_H_INCLUDED__
#define __MESH_H_INCLUDED__
#include "Utils.h"
#include "FileIO.h"
#include "Boundary.h"

class Mesh {
public:
    Mesh(){};
    Mesh(int);

    Matrix points;
    iMatrix faces;
    iSource owner;
    iSource neighbour;

    vector<Boundary> boundarys;
     
    iMatrix boundaryFaces;
    iSource internalFaces;

    void typeSelect(Boundary &boundary, const sSource &v);
    void ReadBoundary();

    void makeIBFaces();
};

#endif
