#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

using namespace std;

class Grid {
private:
    vector<vector<char>> cells;
    int size;

public:
    Grid();
    void display() const;
    bool placeSymbol(int row, int col, char symbol);
    bool isFull();
    bool checkWin(char symbol) const;
    void reset();
    vector<vector<char>> getCells() const;
};

#endif