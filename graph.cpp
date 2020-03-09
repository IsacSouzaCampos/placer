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
        cell_number_map[row+column*columns] = cell_id;
        cell_position_map[cell_id] = make_pair(row, column);
        // cell_number_map[number_of_cells++] = cell_id;
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

int Graph::healfPerimeterWireLength(string main_cell, list<string> netlist) {
    int x_min = cell_position_map[main_cell].first, y_min = cell_position_map[main_cell].second;
    int x_max = x_min, y_max = y_min;

    try {
        for(auto& net : netlist) {
            // cout << cell_position_map[net].first << endl;
            if(cell_position_map[net].first > x_max)
                x_max = cell_position_map[net].first;
            if(cell_position_map[net].first < x_min)
                x_min = cell_position_map[net].first;
            // cout << cell_position_map[net].second << endl;
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

int Graph::randomIterativeImprovementPlace() {
    string cell1 = cell_number_map[(int) rand() % number_of_cells];
    string cell2 = cell_number_map[(int) rand() % number_of_cells];

    int initial_HPWL1 = healfPerimeterWireLength(cell1, netlist_map[cell1]);
    int initial_HPWL2 = healfPerimeterWireLength(cell2, netlist_map[cell2]);

    int final_HPWL1 = healfPerimeterWireLength(cell2, netlist_map[cell1]);
    int final_HPWL2 = healfPerimeterWireLength(cell1, netlist_map[cell2]);

    int initial_total_HPWL = abs(initial_HPWL1 - initial_HPWL2);
    int final_total_HPWL = abs(final_HPWL1 - final_HPWL2);

    if(final_total_HPWL < initial_total_HPWL) {
        swap(cell1, cell2);
        return 1;
    }

    return 0;
}

void Graph::swap(string cell1, string cell2) {
    pair<int, int> temp = cell_position_map[cell1];
    cell_position_map[cell1] = cell_position_map[cell2];
    cell_position_map[cell2] = temp;
}
