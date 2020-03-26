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
    void printGrids(int rows, int columns, map<pair<int, int>, string> position_content);
    void initialPlacement(list<string> list);
    void addToNetlist(string cell1, string cell2);
    int healfPerimeterWireLength(pair<int, int> position, list<string> netlist);
    bool randomIterativeImprovementPlace(string cell, int temperature);
    void swap(pair<int, int> position1, pair<int, int> position2);
    void simulatedAnnealing();
    list<string> cells_list;
    map<string, list<string>> netlist_map;
    map<string, pair<int, int>> cell_position;
    map<pair<int, int>, string> position_content;
};

#endif
