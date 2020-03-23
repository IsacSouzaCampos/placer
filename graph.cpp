#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include "graph.h"

Graph::Graph() = default;

void Graph::initialPlacement(list<string> list) {
    vector<pair<int, int>> grid_vec;
    int count = rows*columns;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            grid_vec.emplace_back(make_pair(i, j));
        }
    }

    for(auto& l : list) {
        srand(clock());
        int random = rand()%count--;
        addCell(l, gridVec[random].first, gridVec[random].second);
        grid_vec[random] = grid_vec[count];
    }
}

void Graph::addCell(string cell_id, int row, int column) {
    try {
        if(row > rows-1 || column > columns-1)
            throw 1;
        get_int_from_id[cell_id] = number_of_cells;
        get_id_from_int[number_of_cells++] = cell_id;
        cell_position_map[cell_id] = make_pair(row, column);
        // get_id_from_int[number_of_cells++] = cell_id;
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
    srand(clock()); // pra mudar sequencia de valores aleatorios
    int rand1 = rand() % number_of_cells;
    int rand2 = rand() % number_of_cells;
    string cell1 = get_id_from_int[rand1];
    string cell2 = get_id_from_int[rand2];

    int initial_HPWL1 = healfPerimeterWireLength(cell1, netlist_map[cell1]);
    int initial_HPWL2 = healfPerimeterWireLength(cell2, netlist_map[cell2]);

    int final_HPWL1 = healfPerimeterWireLength(cell2, netlist_map[cell1]);
    int final_HPWL2 = healfPerimeterWireLength(cell1, netlist_map[cell2]);

    int initial_total_HPWL = initial_HPWL1 + initial_HPWL2;
    int final_total_HPWL = final_HPWL1 + final_HPWL2;

    if(final_total_HPWL < initial_total_HPWL) {
        swap(cell1, cell2);
        return 1;
    }

    // cout << "cell1: " << cell1 << " - " << rand1 << endl;
    // cout << "cell2: " << cell2 << " - " << rand2 << endl;
    // cout << "\ninitial_HPWL1: " << initial_HPWL1 << endl;
    // cout << "initial_HPWL2: " << initial_HPWL2 << endl;
    // cout << "\nfinal_HPWL1: " << final_HPWL1 << endl;
    // cout << "final_HPWL2: " << final_HPWL2 << endl;
    // cout << "\ninitial_total_HPWL: " << initial_total_HPWL << endl;
    // cout << "final_total_HPWL: " << final_total_HPWL << endl;
    // cout << "--------------" << endl;
    return 0;
}

void Graph::swap(string cell1, string cell2) {
    // cout << "swap" << endl;
    pair<int, int> pair_temp = cell_position_map[cell1];
    cell_position_map[cell1] = cell_position_map[cell2];
    cell_position_map[cell2] = pair_temp;

    int int_temp = get_int_from_id[cell1];
    get_int_from_id[cell1] = get_int_from_id[cell2];
    get_int_from_id[cell2] = int_temp;

    string string_temp = get_id_from_int[get_int_from_id[cell1]];
    get_id_from_int[get_int_from_id[cell1]] = get_id_from_int[get_int_from_id[cell2]];
    get_id_from_int[get_int_from_id[cell2]] = string_temp;
}
