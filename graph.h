#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <list>
#include <math.h>
#include <vector>

using namespace std;

class Graph {
 public:
    Graph();
    int rows, columns;
    void readFile();
    const vector<string> split(const string& str, const char& c);
    void addToNetlist(string cell1, string cell2);
    vector<string> inputs_and_outputs;
    list<string> cells_list;
    map<string, list<string>> netlist_map;
    map<string, pair<int, int>> cell_position;
    map<pair<int, int>, string> position_content;
};

#endif
