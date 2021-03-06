#include "Utils.h"
#include "Mesh.h"
#include "scalarField.h"
#include "partDiff.h"
#include "Solver.h"

int main() {
    Mesh mesh(0);
    scalarField T(mesh);

    fvMatrix fvm(T.mesh.nCells);

    fvm += partDiff::laplacian(1.0e+3, T);

    fvm.showMatrix();

    Solver::CGSolver(fvm.lhMatrix, fvm.rhSource, T.vals, T.mesh.nCells);

    T.writeResult();

    return 0;
}
