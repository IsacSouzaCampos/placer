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
    void initialPlacement(list<string> list);
    void addCell(string cell_id, int row, int column);
    void addToNetlist(string cell1, string cell2);
    int healfPerimeterWireLength(list<string> netlist);
    void randomIterativeImprovementPlace(list<string> cell_id_list);
    list<string> cells_list;
    map<int, string> cell_map;
    map<string, list<string>> netlist_map;
    map<string, pair<int, int>> cell_position_map;
};

#endif
