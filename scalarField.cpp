#include "scalarField.h"

scalarField::scalarField(Mesh &mesh) {
    this->mesh = mesh;
    readValFileAndSet();
}

void scalarField::readValFileAndSet()
{
    boundVals = matrix(mesh.bounds.size());
    forEach(mesh.bounds, patchi)
        boundVals[patchi] = source(mesh.bounds[patchi].nFaces);

    ifstream ifs = setFile("0/p");
    ssource v;

    readWord(ifs, "dimensions");

    v = readWord(ifs, "internalField");
    vals = source(mesh.nCells, stod(v[2]));

    readWord(ifs);
    readBracket(ifs);
    forEach(mesh.bounds, patchi){
        readWord(ifs); 
        readBracket(ifs); 
        v = readWord(ifs);
        for(int facei=0; facei<mesh.bounds[patchi].nFaces; facei++)
            boundVals[patchi][facei] = stod(v[1]);
        readBracket(ifs);
    }
}
