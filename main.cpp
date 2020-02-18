#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int rows, columns;
    cin >> rows;
    cin >> columns;

    int grid[rows][columns];
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            grid[i][j] = 0;
        }
    }
}
