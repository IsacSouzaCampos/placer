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

        while(getline(myfile, line)) {
            if(line == "*")
                break;
            cells_list.push_back(line);
        }

        getline(myfile, line);
        for(auto& v : split(line, ':')) {
            vector<string> in_out = split(v, '-');
            vector<string> pos = split(in_out[1], ';');
            inputs_and_outputs.push_back(in_out[0]);
            cell_position[in_out[0]] = make_pair(stoi(pos[0]), stoi(pos[1]));
        }

        getline(myfile, line);
        int c = 0;
        for(auto& v : split(line, ':')) {
            for(auto& cell : split(v, ';')) {
                netlist_map[cell].push_back(inputs_and_outputs[c]);
            }
            ++c;
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

void Graph::addToNetlist(string cell1, string cell2) {
    netlist_map[cell1].push_back(cell2);
    netlist_map[cell2].push_back(cell1);
}
