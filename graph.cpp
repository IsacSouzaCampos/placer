#include <iostream>
#include <time.h>
#include <fstream>
#include "graph.h"

Graph::Graph() {
    readFile();
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            pair<int, int> grid = make_pair(i, j);
            position_content[grid] = "______";
        }
    }
}

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

        int c = 0;
        while(getline(myfile, line)) {
            if(line == "#INPUTS/OUTPUTS#")
                break;
            cells_list.push_back(line);
            cell_number[line] = c++;
        }

        // #INPUTS/OUTPUTS#
        while(getline(myfile, line)) {
            if(line == "#INPUTS/OUTPUTS CONNECTIONS#")
                break;
            vector<string> in_out = split(line, '-');
            vector<string> pos = split(in_out[1], ';');
            inputs_and_outputs.push_back(in_out[0]);
            cell_position[in_out[0]] = make_pair(stoi(pos[0]), stoi(pos[1]));
            cell_number[in_out[0]] = c++;
        }

        // #INPUTS/OUTPUTS CONNECTIONS#
        c = 0;
        while(getline(myfile, line)) {
            if(line == "#CONNECTIONS#")
                break;
            for(auto& cell : split(line, ';')) {
                vector<string> c_w = split(cell, '/'); // cell::wire weight
                netlist_map[c_w[0]].push_back(inputs_and_outputs[c]);
                wire_pad_weight[make_pair(inputs_and_outputs[c], c_w[0])] = stoi(c_w[1]);
                // wire_pad_weight[make_pair(c_w[0], inputs_and_outputs[c])] = stoi(c_w[1]);
            }
            ++c;
        }

        // #CONNECTIONS#
        while(getline(myfile, line)) {
            vector<string> vec;
            vector<string> cells;
            for(auto& v : split(line, '/')) vec.push_back(v);
            for(auto& v : split(vec[0], ':')) cells.push_back(v);
            addToNetlist(cells[0], cells[1]);
            wire_cell_weight[make_pair(cells[0], cells[1])] = stoi(vec[1]);
            // wire_cell_weight[make_pair(cells[1], cells[0])] = stoi(vec[1]);
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

void Graph::addToNetlist(string cell1, string cell2) {
    netlist_map[cell1].push_back(cell2);
    netlist_map[cell2].push_back(cell1);
}
