#include "partDiff.h"

fvMatrix partDiff::laplacian(double diffCoeff, scalarField &scf)
{
    int matSize = scf.mesh.nCells;
    fvMatrix fvm(matSize);
    double d;
    source s = scf.mesh.calcS();

    forEach(scf.mesh.internalFaces, iFaceId){
        int facei = scf.mesh.internalFaces[iFaceId];
        int own = scf.mesh.owner[facei];
        int nei = scf.mesh.neighbour[facei];
        d = calcDistance(
                         scf.mesh.cellCenters[own],
                         scf.mesh.cellCenters[nei] 
                        );

        fvm.lhMatrix[own][own] +=  s[facei]*diffCoeff/d;
        fvm.lhMatrix[own][nei] += -s[facei]*diffCoeff/d;
        fvm.lhMatrix[nei][own] += -s[facei]*diffCoeff/d;
        fvm.lhMatrix[nei][nei] +=  s[facei]*diffCoeff/d;

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
