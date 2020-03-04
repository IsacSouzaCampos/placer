#include <iostream>
#include <math.h>
#include "graph.h"

Graph::Graph() = default;

void Graph::initialPlacement(list<string> list) {
    int i = 0, j = 0;
    for(auto& list_ : list) {
        addCell(list_, i%rows, j%columns);
        // cout << list_ << " " << i%rows << " " << j%columns << endl;
        if(!(++j%columns))
            ++i;
    }
}

void Graph::addCell(string cell_id, int row, int column) {
    try {
        if(row > rows-1 || column > columns-1)
            throw 1;
        cell_map[row+column*columns] = cell_id;
    } catch(exception& e) {
        cout << "erro: " << e.what() << endl;
    } catch(int e) {
        cout << "erro " << e << ": out of range" << endl;
    }
}

void Graph::addToNetlist(string cell1, string cell2) {
    netlist_map[cell1].push_back(cell2);
    netlist_map[cell2].push_back(cell1);
}

int Graph::healfPerimeterWireLength(list<string> netlist) {
    int x_min = rows, x_max = 0, y_min = columns, y_max = 0;

    try {
        for(auto& net : netlist) {
            if(cell_position_map[net].first > x_max)
                x_max = cell_position_map[net].first;
            if(cell_position_map[net].first < x_min)
                x_min = cell_position_map[net].first;
            if(cell_position_map[net].second > y_max)
                y_max = cell_position_map[net].second;
            if(cell_position_map[net].second < y_min)
                y_min = cell_position_map[net].second;
        }
    } catch(exception e) {
        cout << "erro: " << e.what() << endl;
        return 0;
    }

    return (x_max-x_min)+(y_max-y_min);
}

void Graph::randomIterativeImprovementPlace(list<string> cell_id_list) {
    for(auto& cell_id : cell_id_list) {
        pair<int, int> temp = cell_position_map[cell_id];
        int current_hpwl = healfPerimeterWireLength(netlist_map[cell_id]);

        // ...
    }
}
