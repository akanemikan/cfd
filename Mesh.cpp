#include "Mesh.h"

Mesh::Mesh(int size) {
    ReadFile(points, "polyMesh/points");
    ReadFile(faces,  "polyMesh/faces");
    ReadFile(owner,"polyMesh/owner");
    ReadFile(neighbour, "polyMesh/neighbour");

    ReadBoundaryFile();

    makeInterBoundFaces();

    calcFaceCenter();

    calcFaceAreas();
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

void Mesh::ReadBoundaryFile()
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

void Mesh::makeInterBoundFaces()
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


void Mesh::calcFaceCenter() 
{
    faceCenters = Matrix(faces.size(), Source(3, 0.0));
    forEach(faces, i) {
        for(int p=1; p<=faces[i][0]; p++)
            faceCenters[i] += points[faces[i][p]];
        faceCenters[i] /= faces[i][0];
    }
}

void Mesh::calcFaceAreas()
{
    faceAreas = Matrix(faces.size(), Source(3, 0.0));
    forEach(faces, f){
        int nPoint = faces[f][0];
        Source faceCenter = faceCenters[f];
        for(int p=0; p<nPoint; p++){
            int next = (p+1) % nPoint;
            Source v1 = points[faces[f][next+1]] - points[faces[f][p+1]];
            Source v2 = faceCenter - points[faces[f][p+1]];
            Source area = v1 ^ v2; 
            faceAreas[f] += area;
        }
        cout << magS(faceAreas[f]) << endl;
    }

}
