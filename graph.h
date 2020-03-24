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
    int healfPerimeterWireLength(pair<int, int> position, list<string> netlist);
    void randomIterativeImprovementPlace(string cell);
    void swap(pair<int, int> position1, pair<int, int> position2);
    list<string> cells_list;
    map<string, list<string>> netlist_map;
    map<string, pair<int, int>> cell_position;
    map<pair<int, int>, string> position_content;
    map<pair<int, int>, bool> isGridAvailable;
    int number_of_grids{0};
    int number_of_cells{0};
};

#endif
