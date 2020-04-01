#include <iostream>
#include "simulated_annealing.h"
#include "graph.h"

SimulatedAnnealing::SimulatedAnnealing(Graph gr) {
    // gr = graph;
    map<pair<int, int>, string> best_position_content;
    int best_hpwl;

    initialPlacement();

    printGrids();
    
    best_hpwl = total_hpwl();
    cout << "\n" << best_hpwl << "\n" << endl;

    int higher = gr.rows > gr.columns ? gr.rows : gr.columns;
    for(int i = 0; i < higher; i++) {
        cout << i << endl;
        annealing();
        int current_hpwl = total_hpwl();
        if(current_hpwl < best_hpwl) {
            best_hpwl = current_hpwl;
            best_position_content = gr.position_content;
            cout << "!" << endl;
        }
    }

    cout << "\n" << best_hpwl << "\n" << endl;

    printGrids();
}

void SimulatedAnnealing::initialPlacement() {
    vector<pair<int, int>> grid_vec;
    int count = gr.rows*gr.columns;
    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++) {
            grid_vec.emplace_back(make_pair(i, j));
        }
    }

    for(auto& l : gr.cells_list) {
        srand(clock());
        int random = rand()%count--;
        int first = grid_vec[random].first;
        int second = grid_vec[random].second;
        
        gr.cell_position[l] = make_pair(first, second);
        gr.position_content[make_pair(first, second)] = l;

        grid_vec[random] = grid_vec[count];
    }
    // for(int i = 0; i < gr.rows; i++) {
    //     for(int j = 0; j < gr.columns; j++) {
    //         cout << gr.position_content[make_pair(i, j)] << " ";
    //     }
    //     cout << endl;
    // }
}

int SimulatedAnnealing::halfPerimeterWireLength(pair<int, int> position, list<string> netlist) {
    int x_min = position.first, y_min = position.second;
    int x_max = x_min, y_max = y_min;

    try {
        for(auto& cell : netlist) {
            // cout << gr.cell_position[net].first << endl;
            if(gr.cell_position[cell].first > x_max)
                x_max = gr.cell_position[cell].first;
            if(gr.cell_position[cell].first < x_min)
                x_min = gr.cell_position[cell].first;
            // cout << gr.cell_position[cell].second << endl;
            if(gr.cell_position[cell].second > y_max)
                y_max = gr.cell_position[cell].second;
            if(gr.cell_position[cell].second < y_min)
                y_min = gr.cell_position[cell].second;
        }
    } catch(exception e) {
        cout << "erro: " << e.what() << endl;
        return 0;
    }

    return (x_max-x_min)+(y_max-y_min);
}

bool SimulatedAnnealing::randomIterativeImprovementPlace(string cell, int temperature) {
    bool decreased = false;
    pair<int, int> current_position = gr.cell_position[cell];

    for(int i = 0; i < gr.rows*gr.columns; i++) {
        srand(clock()); // pra mudar sequencia de valores aleatorios
        int x = rand() % gr.rows, y = rand() % gr.columns;
        pair<int, int> new_position = make_pair(x, y);

        int initial_HPWL = halfPerimeterWireLength(current_position, gr.netlist_map[cell]);
        int final_HPWL = halfPerimeterWireLength(new_position, gr.netlist_map[cell]);

        int delta_l = final_HPWL - initial_HPWL;
        if(delta_l < 0 && final_HPWL > 0) {
            swap(current_position, new_position);
            current_position = gr.cell_position[cell];
            decreased = true;
        } else {
            if(temperature > 0) {
                double random = (double)rand()/RAND_MAX;
                double result = exp((-delta_l)/temperature);
                if(random < result) {
                    swap(current_position, new_position);
                    current_position = gr.cell_position[cell];
                }
            }
        }
    }

    return decreased;
}

void SimulatedAnnealing::swap(pair<int, int> current_position, pair<int, int> new_position) {
    string current_content = gr.position_content[current_position];
    string new_content = gr.position_content[new_position]; 

    string temp_str = gr.position_content[current_position];
    gr.position_content[current_position] = gr.position_content[new_position];
    gr.position_content[new_position] = temp_str;

    gr.cell_position[current_content] = new_position;
    gr.cell_position[new_content] = current_position;
}

int SimulatedAnnealing::total_hpwl() {
    int total_hpwl = 0;
    for(auto& cell : gr.cells_list)
        total_hpwl += halfPerimeterWireLength(gr.cell_position[cell], gr.netlist_map[cell]);
    return total_hpwl;
}

void SimulatedAnnealing::annealing() {
    int temperature = 10000;
    bool frozen = false;
    bool decreased;

    while(!frozen) {
        decreased = false;
        for(auto& cell : gr.cells_list) {
            if(randomIterativeImprovementPlace(cell, temperature))
                decreased = true;
        }
        // printGrids(rows, columns, position_content);
        if(decreased)
            temperature = 0.9*temperature;
        else
            frozen = true;
    }
}

void SimulatedAnnealing::printGrids() {
    for(int i = 0; i < gr.rows; i++) {
        for(int j = 0; j < gr.columns; j++) {
            cout << gr.position_content[make_pair(i, j)] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
