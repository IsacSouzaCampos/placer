#include <unistd.h>
#include "quadratic_placement.h"

QuadraticPlacement::QuadraticPlacement() {
    int dimension = gr.cells_list.size();
    initializeMatrix(dimension);
    setMatrixes(dimension);
    printMatrix(dimension);
}

void QuadraticPlacement::initializeMatrix(int dimension) {
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++)
            matrix[i*dimension + j] = 0;
    }
}

void QuadraticPlacement::setMatrixes(int dimension) {
    for(auto& w_weight : gr.wire_cell_weight) {
        pair<string, string> cells = w_weight.first;
        int first_cell = gr.cell_number[cells.first];
        int second_cell = gr.cell_number[cells.second];
        matrix[first_cell*dimension + second_cell] = w_weight.second;
        matrix[second_cell*dimension + first_cell] = w_weight.second;
    }

    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            int index = i*dimension + j;
            matrix[index] *= -1;
        }
    }

}

void QuadraticPlacement::printMatrix(int dimension) {
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            cout << matrix[i*dimension + j] << " ";
        }
        cout << endl;
    }
}
