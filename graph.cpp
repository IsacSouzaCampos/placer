#include <iostream>
#include <math.h>
#include "graph.h"

Graph::Graph() = default;

void Graph::initialPosition(list<string> list) {
    int i = 0, j = 0;
    for(auto& list_ : list) {
        addCell(list_, i%rows, j%columns);
        cout << list_ << " " << i%rows << " " << j%columns << endl;
        if(!(++j%columns))
            ++i;
    }
}

void Graph::addCell(string cell_id, int row, int column) {
    try {
        if(row > rows-1 || column > columns-1)
            throw 1;
        cell_map[row+column*columns] = cell_id;
    } catch(exception& e) {
        cout << "erro: " << e.what() << endl;
    } catch(int e) {
        cout << "erro " << e << ": out of range" << endl;
    }
}

void Graph::addConection(string cell1, string cell2) {
    conections_map[cell1].push_back(cell2);
    conections_map[cell2].push_back(cell1);
}
