#include <iostream>
#include <time.h>
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
            cout << gr.cell_number_map[i+j*gr.columns] << " ";
        cout << endl;
    }

    cout << endl;
    
    int total_HPWL = 0;
    for(auto& netlist : gr.netlist_map) {
        // gr.healfPerimeterWireLength(netlist.first, netlist.second);
        total_HPWL += gr.healfPerimeterWireLength(netlist.first, netlist.second);
    }
    cout << total_HPWL << "\n" << endl;

    clock_t t_begin, t_end, t_result;
    int cont = 0;
    t_result = 0;
    t_begin = clock();
    while(cont < 500) {
        gr.randomIterativeImprovementPlace();
        cont++;
        
        t_end = clock();
        t_result = ((t_end - t_begin) / (CLOCKS_PER_SEC / 1000));
    }

    total_HPWL = 0;
    for(auto& netlist : gr.netlist_map) {
        // gr.healfPerimeterWireLength(netlist.first, netlist.second);
        total_HPWL += gr.healfPerimeterWireLength(netlist.first, netlist.second);
    }
    cout << total_HPWL << "\n" << endl;
}
