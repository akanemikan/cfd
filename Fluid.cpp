#include "Utils.h"
#include "Mesh.h"
#include "scalarField.h"

int main() {
    Mesh mesh(0);
    scalarField T(mesh);
    showSource(T.mesh.cellVolumes);

    showMatrix(T.boundVals);

    return 0;
}
