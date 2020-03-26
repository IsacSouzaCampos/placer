#include <iostream>
#include <time.h>
#include <fstream>
#include "graph.h"

Graph::Graph() = default;

void Graph::readFile() {
    string line;
    ifstream myfile ("data.txt");
    
    if(myfile.is_open()) {
        string line;
        vector<string> order;

        getline(myfile, line);
        for(auto& v : split(line, ';')) order.push_back(v);
        rows = stoi(order[0]);
        columns = stoi(order[1]);

        while(getline(myfile, line)) {
            if(line == "*")
                break;
            cells_list.push_back(line);
        }

        while(getline(myfile, line)) {
            vector<string> netlist;
            for(auto& v : split(line, ':')) netlist.push_back(v);
            for(auto& v : split(netlist[1], ';')) addToNetlist(netlist[0], v);
        }
    } else {
        cout << "Unable to open file" << endl;
    }
}

const vector<string> Graph::split(const string& str, const char& c) {
    string buff{""};
    vector<string> vec;

    for(auto& element : str) {
        if(element != c) buff += element;
        else { vec.push_back(buff); buff = ""; }
    }
    if(buff != "") vec.push_back(buff);

    return vec;
}

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
        
        cell_position[l] = make_pair(first, second);
        position_content[make_pair(first, second)] = l;

        grid_vec[random] = grid_vec[count];
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
                    swap(current_position, new_position);
                    current_position = cell_position[cell];
                }
            }
        }
    }

    return decreased;
}

void Graph::swap(pair<int, int> current_position, pair<int, int> new_position) {
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
