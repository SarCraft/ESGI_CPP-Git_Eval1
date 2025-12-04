#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid() : size(3) {
    cells.resize(size, vector<char>(size, ' '));
}

void Grid::display() const {
    cout << "\n";
    for (int i = 0; i < size; i++) {
        cout << " ";
        for (int j = 0; j < size; j++) {
            cout << cells[i][j];
            if (j < size - 1) cout << " | ";
        }
        cout << "\n";
        if (i < size - 1) {
            cout << " ---------\n";
        }
    }
    cout << "\n";
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

bool Grid::checkWin(char symbol) const {
    // Vérifier les lignes
    for (int i = 0; i < size; i++) {
        bool win = true;
        for (int j = 0; j < size; j++) {
            if (cells[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    
    // Vérifier les colonnes
    for (int j = 0; j < size; j++) {
        bool win = true;
        for (int i = 0; i < size; i++) {
            if (cells[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    
    // Vérifier la diagonale principale (haut-gauche à bas-droite)
    bool win = true;
    for (int i = 0; i < size; i++) {
        if (cells[i][i] != symbol) {
            win = false;
            break;
        }
    }
    if (win) return true;
    
    // Vérifier la diagonale inverse (haut-droite à bas-gauche)
    win = true;
    for (int i = 0; i < size; i++) {
        if (cells[i][size - 1 - i] != symbol) {
            win = false;
            break;
        }
    }
    if (win) return true;
    
    return false;
}

void Grid::reset() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cells[i][j] = ' ';
        }
    }
}