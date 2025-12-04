#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

class Grid {
private:
    std::vector<std::vector<char>> cells;
    int size;

public:
    Grid();
    void display() const;
    bool placeSymbol(int row, int col, char symbol);
    bool isFull() const;
    bool checkWin(char symbol) const;
    void reset();
};

#endif