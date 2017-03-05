#include "partDiff.h"

fvMatrix partDiff::laplacian(double diffCoeff, scalarField &scf)
{
    int sMat = scf.mesh.nCells;
    fvMatrix fvm(sMat);
    double d;
    source s = scf.mesh.calcS();

    forEach(scf.mesh.internalFaces, iFacei){
        int facei = scf.mesh.internalFaces[iFacei];
        int owner = scf.mesh.owner[facei];
        int neighbour = scf.mesh.neighbour[facei];
        d = calcDistance(
                         scf.mesh.cellCenters[owner],
                         scf.mesh.cellCenters[neighbour] 
                        );

        fvm.lhMatrix[owner][owner] += s[facei]*diffCoeff/d;
        fvm.lhMatrix[owner][neighbour] += -s[facei]*diffCoeff/d;
        fvm.lhMatrix[neighbour][owner] += -s[facei]*diffCoeff/d;
        fvm.lhMatrix[neighbour][neighbour] += s[facei]*diffCoeff/d;

    }

    for(int i=0; i<scf.mesh.boundaryFaces.size()-1; i++){
        isource patch = scf.mesh.boundaryFaces[i];
        forEach(patch, facei){
            int face = patch[facei];  
            int owner = scf.mesh.owner[face];
            d = calcDistance(
                             scf.mesh.cellCenters[owner], 
                             scf.mesh.faceCenters[face]
                            );
            fvm.lhMatrix[owner][owner] += s[face]*diffCoeff/d;
            fvm.rhSource[owner] += scf.boundVals[i][facei]*s[face]*diffCoeff/d;
        }
    }
    return fvm;
}
