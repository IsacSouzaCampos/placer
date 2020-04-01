#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <list>
#include <vector>
#include <map>
#include "graph.h"

using namespace std;

class SimulatedAnnealing {
 public:
    SimulatedAnnealing(Graph gr);
    void initialPlacement();
    int halfPerimeterWireLength(pair<int, int> position, list<string> netlist);
    bool randomIterativeImprovementPlace(string cell, int temperature);
    void swap(pair<int, int> position1, pair<int, int> position2);
    int total_hpwl();
    void annealing();
    void printGrids();
    Graph gr;
};

#endif