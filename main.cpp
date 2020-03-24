#include <iostream>
#include <time.h>
#include "graph.h"

using namespace std;

void printGrids(int rows, int columns, map<pair<int, int>, string> position_content) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << position_content[make_pair(i, j)] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    Graph gr = Graph();
    // cout << "linhas: " << flush;
    // cin >> gr.rows;
    // cout << "colunas: " << flush;
    // cin >> gr.columns;
    gr.rows = 5;
    gr.columns = 5;

    gr.number_of_grids = gr.rows*gr.columns;
    
    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++) {
            pair<int, int> grid = make_pair(i, j);
            gr.isGridAvailable[grid] = true;
            gr.position_content[grid] = "_";
        }
    }

    gr.cells_list.push_back("a");
    gr.cells_list.push_back("b");
    gr.cells_list.push_back("c");
    gr.cells_list.push_back("d");
    gr.cells_list.push_back("e");
    gr.cells_list.push_back("f");
    gr.cells_list.push_back("g");
    gr.cells_list.push_back("h");

    gr.initialPlacement(gr.cells_list);

    printGrids(gr.rows, gr.columns, gr.position_content);

    gr.addToNetlist("a", "c");
    gr.addToNetlist("b", "c");
    gr.addToNetlist("d", "f");
    gr.addToNetlist("e", "f");
    gr.addToNetlist("c", "g");
    gr.addToNetlist("f", "g");
    gr.addToNetlist("g", "h");
    
    int total_HPWL = 0;
    for(auto& cell : gr.cells_list)
        total_HPWL += gr.healfPerimeterWireLength(gr.cell_position[cell], gr.netlist_map[cell]);
    cout << "\n" << total_HPWL << "\n" << endl;

    // for(auto& a : gr.get_id_from_int)
    //     cout << a.first << " - " << a.second << endl;
    // cout << endl;

    for(auto& cell : gr.cells_list) {
        gr.randomIterativeImprovementPlace(cell);
    }

    total_HPWL = 0;
    for(auto& cell : gr.cells_list)
        total_HPWL += gr.healfPerimeterWireLength(gr.cell_position[cell], gr.netlist_map[cell]);
    cout << total_HPWL << "\n" << endl;

    // for(int i = 0; i < gr.rows; i++) {
    //     for(int j = 0; j < gr.columns; j++)
    //         cout << gr.get_id_from_int[j+i*gr.columns] << " ";
    //     cout << endl;
    // }

    printGrids(gr.rows, gr.columns, gr.position_content);

}
