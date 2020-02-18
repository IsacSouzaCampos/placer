#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>

using namespace std;

class Graph {
 public:
    Graph();
    int rows, columns;
    void addCell(string cell_num, int row, int column);
    map<int, string> cell_map;
};

#endif
