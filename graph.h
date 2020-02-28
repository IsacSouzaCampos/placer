#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <string>
#include <list>

using namespace std;

class Graph {
 public:
    Graph();
    int rows, columns;
    void initialPosition(list<string> list);
    void addCell(string cell_id, int row, int column);
    void addConection(string cell1, string cell2);
    void healfPerimeterWireLength(string cell_id);
    list<string> cells_list;
    map<int, string> cell_map;
    map<string, list<string>> conections_map;
    map<string, pair<int, int>> cell_position_map;
};

#endif
