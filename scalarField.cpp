#include "scalarField.h"

scalarField::scalarField(Mesh &mesh) {
    this->mesh = mesh;
    readValFileAndSet();
}

void scalarField::readValFileAndSet()
{
    boundVals = matrix(mesh.boundarys.size());
    forEach(mesh.boundarys, patchI)
        boundVals[patchI] = source(mesh.boundarys[patchI].nFaces);

    ifstream ifs = setFile("0/p");
    ssource v;

    readWord(ifs, "dimensions");

    v = readWord(ifs, "internalField");
    vals = source(mesh.nCell, stod(v[2]));

    readWord(ifs);
    readBracket(ifs);
    forEach(mesh.boundarys, patchI){
        readWord(ifs); 
        readBracket(ifs); 
        v = readWord(ifs);
        for(int facei=0; facei<mesh.boundarys[patchI].nFaces; facei++)
            boundVals[patchI][facei] = stod(v[1]);
        readBracket(ifs);
    }
}
