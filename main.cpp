#include <iostream>
#include <time.h>
#include "graph.h"

using namespace std;

int total_hpwl(Graph gr);

int main(int argc, char* argv[]) {
    Graph gr = Graph();
    gr.readFile();
    map<pair<int, int>, string> best_position_content;
    int best_hpwl;

    int higher = gr.rows > gr.columns ? gr.rows : gr.columns;
    
    for(int i = 0; i < higher; i++) {
        for(int j = 0; j < gr.columns; j++) {
            pair<int, int> grid = make_pair(i, j);
            gr.position_content[grid] = "_";
        }
    }

    gr.initialPlacement(gr.cells_list);

    gr.printGrids(gr.rows, gr.columns, gr.position_content);
    
    best_hpwl = total_hpwl(gr);
    cout << "\n" << best_hpwl << "\n" << endl;

    for(int i = 0; i < gr.rows; i++) {
        cout << i << endl;
        gr.simulatedAnnealing();
        int current_hpwl = total_hpwl(gr);
        if(current_hpwl < best_hpwl) {
            best_hpwl = current_hpwl;
            best_position_content = gr.position_content;
            cout << "!" << endl;
        }
    }

    cout << "\n" << best_hpwl << "\n" << endl;

    gr.printGrids(gr.rows, gr.columns, best_position_content);
}

int total_hpwl(Graph gr) {
    int total_hpwl = 0;
    for(auto& cell : gr.cells_list)
        total_hpwl += gr.healfPerimeterWireLength(gr.cell_position[cell], gr.netlist_map[cell]);
    return total_hpwl;
}
