#include "Mesh.h"

Mesh::Mesh(int size) {
    ReadFile(points, "polyMesh/points");
    ReadFile(faces,  "polyMesh/faces");
    ReadFile(owner,"polyMesh/owner");
    ReadFile(neighbour, "polyMesh/neighbour");

    ReadBoundary();

    makeIBFaces();
}

void Mesh::typeSelect(Boundary &boundary, const sSource &v){
    string word = v[0];
    string value = v[1];
    if(word ==  "type")
        boundary.type = value;
    if(word ==  "inGroups")
        boundary.inGroups = value;
    if(word ==  "nFaces")
        boundary.nFaces = stoi(value);
    if(word ==  "startFace")
        boundary.startFace = stoi(value);
}

void Mesh::ReadBoundary()
{
    Boundary boundary;
    ifstream ifs=setFile("polyMesh/boundary");

    int size = ReadSize(ifs);

    ReadBracket(ifs);
    for(int i=0; i<size; i++){
        boundary.name = ReadWord(ifs)[0];
        ReadBracket(ifs);
        for(int i=0; i<4; i++){
            typeSelect(boundary, ReadWord(ifs));
        }
        boundarys.push_back(boundary);
        ReadBracket(ifs);
    }
}

void Mesh::makeIBFaces()
{
    forEach(boundarys, i){
        int startFace = boundarys[i].startFace;
        int nFaces = boundarys[i].nFaces;
        iSource tmp(nFaces);
        for(int f=0; f<nFaces; f++){
            tmp[f] = startFace + f;
        }
        boundaryFaces.push_back(tmp);
    }

    for(int i=0; i<boundaryFaces[0][0]; i++)
        internalFaces.push_back(i);
}
