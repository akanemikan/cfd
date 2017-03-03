#include "Mesh.h"

Mesh::Mesh(int size) {
    points = Matrix(size, Source(size, 0.0));
}
