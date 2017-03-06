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

source scalarField::calcPtAvr(ofstream &ofs)
{
    source ptAvr(mesh.points.size());
    isource nPtOwn(mesh.points.size());

    forEach(mesh.internalFaces, iFaceId) {
        int facei = mesh.internalFaces[iFaceId];
        double ownVal = vals[mesh.owner[facei]];
        double neiVal = vals[mesh.neighbour[facei]];
        isource facePts = mesh.faces[facei];

        for(isource::iterator ptItr=facePts.begin()+1; ptItr!=facePts.end();  ptItr++){
            ptAvr[*ptItr] += ownVal + neiVal;
            nPtOwn[*ptItr] += 2;
        }
    }

    forEach(mesh.boundaryFaces, patchI){
        forEach(mesh.boundaryFaces[patchI], bFaceId){
            int facei = mesh.boundaryFaces[patchI][bFaceId];

            double ownVal = vals[mesh.owner[facei]];

            isource facePts = mesh.faces[facei]; //point of face (0, 1, 2, 3)

            for(isource::iterator ptItr=facePts.begin()+1; ptItr!=facePts.end();  ptItr++){
                ptAvr[*ptItr] += ownVal;
                nPtOwn[*ptItr] += 1;
            }
        }
    }

    ptAvr /= nPtOwn;

    return ptAvr;

}

void scalarField::writeResult()
{
   ofstream ofs = setFile();

   string Header ="# vtk DataFile Version 2.0\nresult\nASCII\nDATASET UNSTRUCTURED_GRID";
   ofs << Header << endl;

   ofs << "POINTS " << mesh.points.size() << " float" << endl;
   forEach(mesh.points, pti){
       vector<double> coord = mesh.points[pti];
       ofs << coord[0] << " ";
       ofs << coord[1] << " ";
       ofs << coord[2] << endl;
   }

   ofs << "CELLS " << mesh.faces.size() << " " << mesh.faces.size()*5 << endl;
   for(int f=0; f<mesh.faces.size(); f++){
       for(int p=0; p<mesh.faces[f].size(); p++){
           ofs << mesh.faces[f][p] << " ";
       }
       ofs << endl;
   }

   ofs << "CELL_TYPES " << mesh.faces.size() << endl;
   for(int f=0; f<mesh.faces.size(); f++){
       ofs << 9 << endl;
   }

    ofs << "POINT_DATA " << mesh.points.size() << endl;
    ofs << "SCALARS " << "T " << "float " << 1 << endl;
    ofs << "LOOKUP_TABLE default" << endl;
    vector<double> ptAvr = calcPtAvr(ofs);
    for(int i=0; i<ptAvr.size(); i++){
        ofs << ptAvr[i] << endl;
    }
}
