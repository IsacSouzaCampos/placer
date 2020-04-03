#ifndef QUADRATIC_PLACEMENT_H
#define QUADRATIC_PLACEMENT_H

#include "graph.h"

class QuadraticPlacement {
 public:
    QuadraticPlacement();
    Graph gr = Graph();
    void initializeMatrix(int dimension);
    void setMatrixes(int dimension);
    void printMatrix(int dimension);
    int matrix[];
};

#endif