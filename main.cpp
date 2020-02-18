#include <iostream>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    Graph gr = Graph();
    cout << "linhas: " << flush;
    cin >> gr.rows;
    cout << "colunas: " << flush;
    cin >> gr.columns;
    // int grid[gr.rows][gr.columns] = {};

    gr.addCell("a", 0, 0);
    gr.addCell("b", 0, 1);
    gr.addCell("c", 0, 2);
    gr.addCell("d", 0, 3);
    gr.addCell("e", 1, 0);
    gr.addCell("f", 1, 1);
    gr.addCell("g", 1, 2);
    gr.addCell("h", 1, 3);

    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++)
            cout << gr.cell_map[i+j*gr.columns] << " ";
        cout << endl;
    }
}
