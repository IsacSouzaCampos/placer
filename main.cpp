#include <iostream>
#include <time.h>
#include "graph.h"

using namespace std;

void printGrids() {
    for(int )
}

int main(int argc, char* argv[]) {
    Graph gr = Graph();
    cout << "linhas: " << flush;
    cin >> gr.rows;
    cout << "colunas: " << flush;
    cin >> gr.columns;
    
    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++) {
            gr.isGridAvailable[make_pair(i, j)] = true;
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

    gr.addToNetlist("a", "c");
    gr.addToNetlist("b", "c");
    gr.addToNetlist("d", "f");
    gr.addToNetlist("e", "f");
    gr.addToNetlist("c", "g");
    gr.addToNetlist("f", "g");
    gr.addToNetlist("g", "h");
    
    int total_HPWL = 0;
    for(auto& netlist : gr.netlist_map)
        total_HPWL += gr.healfPerimeterWireLength(netlist.first, netlist.second);
    cout << "\n" << total_HPWL << "\n" << endl;

    for(auto& a : gr.get_id_from_int)
        cout << a.first << " - " << a.second << endl;
    cout << endl;

    clock_t t_begin, t_end, t_result;
    int cont = 0;
    t_result = 0;
    t_begin = clock();
    while(cont < 5000) {
        if(!gr.randomIterativeImprovementPlace())
            cont++;
        
        t_end = clock();
        t_result = ((t_end - t_begin) / (CLOCKS_PER_SEC / 1000));
    }

    total_HPWL = 0;
    for(auto& netlist : gr.netlist_map)
        total_HPWL += gr.healfPerimeterWireLength(netlist.first, netlist.second);
    cout << total_HPWL << "\n" << endl;

    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++)
            cout << gr.get_id_from_int[j+i*gr.columns] << " ";
        cout << endl;
    }
}
