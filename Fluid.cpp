#include "Utils.h"
#include "Mesh.h"

int main() {
    Mesh mesh(0);

    showMatrix(mesh.boundaryFaces);
    
    return 0;
}
