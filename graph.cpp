#include <iostream>
#include <time.h>
#include <vector>
#include "graph.h"

Graph::Graph() = default;

void Graph::printGrids(int rows, int columns, map<pair<int, int>, string> position_content) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            cout << position_content[make_pair(i, j)] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

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
        int first = grid_vec[random].first;
        int second = grid_vec[random].second;
        
        addCell(l, first, second);
        position_content[make_pair(first, second)] = l;

        grid_vec[random] = grid_vec[count];
    }
}

void Graph::addCell(string cell_id, int row, int column) {
    try {
        if(row > rows-1 || column > columns-1)
            throw 1;
        // get_int_from_id[cell_id] = number_of_cells;
        // get_id_from_int[number_of_cells++] = cell_id;
        cell_position[cell_id] = make_pair(row, column);
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

int Graph::healfPerimeterWireLength(pair<int, int> position, list<string> netlist) {
    int x_min = position.first, y_min = position.second;
    int x_max = x_min, y_max = y_min;

    try {
        for(auto& cell : netlist) {
            // cout << cell_position[net].first << endl;
            if(cell_position[cell].first > x_max)
                x_max = cell_position[cell].first;
            if(cell_position[cell].first < x_min)
                x_min = cell_position[cell].first;
            // cout << cell_position[cell].second << endl;
            if(cell_position[cell].second > y_max)
                y_max = cell_position[cell].second;
            if(cell_position[cell].second < y_min)
                y_min = cell_position[cell].second;
        }
    } catch(exception e) {
        cout << "erro: " << e.what() << endl;
        return 0;
    }

    return (x_max-x_min)+(y_max-y_min);
}

bool Graph::randomIterativeImprovementPlace(string cell, int temperature) {
    bool decreased = false;
    pair<int, int> current_position = cell_position[cell];

    for(int i = 0; i < rows*columns; i++) {
        srand(clock()); // pra mudar sequencia de valores aleatorios
        int x = rand() % rows, y = rand() % columns;
        pair<int, int> new_position = make_pair(x, y);

        int initial_HPWL = healfPerimeterWireLength(current_position, netlist_map[cell]);
        int final_HPWL = healfPerimeterWireLength(new_position, netlist_map[cell]);

        int delta_l = final_HPWL - initial_HPWL;
        if(delta_l < 0 && final_HPWL > 0) {
            swap(current_position, new_position);
            current_position = cell_position[cell];
            decreased = true;
        } else {
            if(temperature > 0) {
                double random = (double)rand()/RAND_MAX;
                double result = exp((-delta_l)/temperature);
                if(random < result) {
                    // cout << "#" << endl;
                    swap(current_position, new_position);
                    current_position = cell_position[cell];
                } else {
                    // cout << "-" << endl;
                }
            }
        }
    }

    return decreased;
}

void Graph::swap(pair<int, int> current_position, pair<int, int> new_position) {
    // cout << "swap" << endl;
    string current_content = position_content[current_position];
    string new_content = position_content[new_position]; 

    string temp_str = position_content[current_position];
    position_content[current_position] = position_content[new_position];
    position_content[new_position] = temp_str;

    cell_position[current_content] = new_position;
    cell_position[new_content] = current_position;
}

void Graph::simulatedAnnealing() {
    int temperature = 10000;
    bool frozen = false;
    bool decreased;

    while(!frozen) {
        decreased = false;
        for(auto& cell : cells_list) {
            if(randomIterativeImprovementPlace(cell, temperature))
                decreased = true;
        }
        // printGrids(rows, columns, position_content);
        if(decreased)
            temperature = 0.9*temperature;
        else
            frozen = true;
    }
}
