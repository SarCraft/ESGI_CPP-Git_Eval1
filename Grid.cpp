#include "Grid.h"
#include <iostream>

Grid::Grid() : size(3) {
    cells.resize(size, std::vector<char>(size, ' '));
}

void Grid::display() const {
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << " ";
        for (int j = 0; j < size; j++) {
            std::cout << cells[i][j];
            if (j < size - 1) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < size - 1) {
            std::cout << " ---------\n";
        }
    }
    std::cout << "\n";
}

bool Grid::isFull() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (cells[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool Grid::placeSymbol(int row, int col, char symbol) {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return false; // Position hors limites
    }
    if (cells[row][col] != ' ') {
        return false; // Case déjà occupée
    }
    cells[row][col] = symbol;
    return true;
}

void Grid::reset() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cells[i][j] = ' ';
        }
    }
}