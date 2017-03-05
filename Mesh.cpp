#include "Mesh.h"

Mesh::Mesh(int size) {
    readFile(points, "polyMesh/points");
    readFile(faces,  "polyMesh/faces");
    readFile(owner,"polyMesh/owner");
    readFile(neighbour, "polyMesh/neighbour");

    readBoundaryFile();

    makeInterBoundFaces();

    nCell = 10;

    calcFaceCenters();

    calcFaceAreas();

    calcCellCentersVolumes();
}

void Mesh::typeSelect(Boundary &boundary, const ssource &v){
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

void Mesh::readBoundaryFile()
{
    Boundary boundary;
    ifstream ifs=setFile("polyMesh/boundary");

    int size = readSize(ifs);

    readBracket(ifs);
    for(int i=0; i<size; i++){
        boundary.name = readWord(ifs)[0];
        readBracket(ifs);
        for(int i=0; i<4; i++){
            typeSelect(boundary, readWord(ifs));
        }
        boundarys.push_back(boundary);
        readBracket(ifs);
    }
}

void Mesh::makeInterBoundFaces()
{
    forEach(boundarys, i){
        int startFace = boundarys[i].startFace;
        int nFaces = boundarys[i].nFaces;
        isource tmp(nFaces);
        for(int f=0; f<nFaces; f++){
            tmp[f] = startFace + f;
        }
        boundaryFaces.push_back(tmp);
    }

    for(int i=0; i<boundaryFaces[0][0]; i++)
        internalFaces.push_back(i);
}


void Mesh::calcFaceCenters() 
{
    faceCenters = matrix(faces.size(), source(3, 0.0));
    forEach(faces, i) {
        for(int p=1; p<=faces[i][0]; p++)
            faceCenters[i] += points[faces[i][p]];
        faceCenters[i] /= faces[i][0];
    }
}

void Mesh::calcFaceAreas()
{
    faceAreas = matrix(faces.size(), source(3, 0.0));
    forEach(faces, f){
        int nPoint = faces[f][0];
        source faceCenter = faceCenters[f];
        for(int p=0; p<nPoint; p++){
            int next = (p+1) % nPoint;
            faceAreas[f] += (points[faces[f][next+1]] - points[faces[f][p+1]]) ^
                (faceCenter - points[faces[f][p+1]]);
        }
    }

}

void Mesh::calcCellCentersVolumes()
{
    cellCenters = matrix(nCell, source(3, 0.0));
    cellVolumes = source(nCell);
    matrix cellCentersEst = matrix(10, source(3, 0.0));
    isource numCellFaces(nCell);

    forEach(owner, facei)
    {
        cellCentersEst[owner[facei]] += faceCenters[facei];
        numCellFaces[owner[facei]] += 1;
    }

    forEach(neighbour, facei)
    {
        cellCentersEst[neighbour[facei]] += faceCenters[facei];
        numCellFaces[neighbour[facei]] += 1;
    }

    forEach(numCellFaces, celli)
    {
        cellCentersEst[celli] /= numCellFaces[celli];
    }

    forEach(owner, facei)
    {
        double pyramid3Volume = faceAreas[facei] & 
            (faceCenters[facei] - cellCentersEst[owner[facei]]);
       
        source pc = (3.0/4.0)*faceCenters[facei] + 
            (1.0/4.0)*cellCentersEst[owner[facei]];

        cellCenters[owner[facei]] += pc*pyramid3Volume;

        cellVolumes[owner[facei]] += pyramid3Volume;
    }

    forEach(neighbour, facei)
    {
        double pyramid3Volume = (-1)*faceAreas[facei] & 
            (faceCenters[facei] - cellCentersEst[neighbour[facei]]);
       
        source pc = (3.0/4.0)*faceCenters[facei] + 
            (1.0/4.0)*cellCentersEst[neighbour[facei]];

        cellCenters[neighbour[facei]] += pc*pyramid3Volume;

        cellVolumes[neighbour[facei]] += pyramid3Volume;
    }

    forEach(cellCenters, celli)
        cellCenters[celli] /= cellVolumes[celli];
}
