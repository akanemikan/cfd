#ifndef __MESH_H_INCLUDED__
#define __MESH_H_INCLUDED__
#include "Utils.h"
#include "FileIO.h"
#include "Boundary.h"

class Mesh {
public:
    Mesh(){};
    Mesh(int);

    matrix points;
    imatrix faces;
    isource owner;
    isource neighbour;

    vector<Boundary> bounds;
     
    imatrix boundaryFaces;
    isource internalFaces;

    matrix faceCenters;
    matrix cellCenters;
    matrix faceAreas;
    source cellVolumes;

    int nCells;

    void typeSelect(Boundary &boundary, const ssource &v);
    void readBoundaryFile();

    void makeInterBoundFaces();

    void calcFaceCenters();
    void calcFaceAreas();
    void calcCellCentersVolumes();
};

#endif
