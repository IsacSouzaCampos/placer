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

    gr.cells_list.push_back("a");
    gr.cells_list.push_back("b");
    gr.cells_list.push_back("c");
    gr.cells_list.push_back("d");
    gr.cells_list.push_back("e");
    gr.cells_list.push_back("f");
    gr.cells_list.push_back("g");
    gr.cells_list.push_back("h");

    gr.initialPlacement(gr.cells_list);

    gr.addToNetlist("a", "c");
    gr.addToNetlist("b", "c");
    gr.addToNetlist("d", "f");
    gr.addToNetlist("e", "f");
    gr.addToNetlist("c", "g");
    gr.addToNetlist("f", "g");
    gr.addToNetlist("g", "h");

    // cout << "\n" << endl;

    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++)
            cout << gr.cell_map[i+j*gr.columns] << " ";
        cout << endl;
    }

    cout << endl;

    gr.randomIterativeImprovementPlace(gr.cells_list);
}
