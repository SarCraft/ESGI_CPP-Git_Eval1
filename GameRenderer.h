#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "raylib.h"
#include "Grid.h"
#include "Joueur.h"
#include <string>

using namespace std;

class Game;

enum class GameMode;  // Forward declaration

class GameRenderer {
private:
    const int screenWidth = 600;
    const int screenHeight = 700;
    const int cellSize = 180;
    const int offsetX = 30;
    const int offsetY = 100;

public:
    GameRenderer();
    void drawModeSelection();
    void drawBoard(const Grid& grid, const Joueur* currentPlayer, bool gameOver, const string& winner);
    void drawNameSelection(const Game& game);
    bool getCellFromMouseClick(int mouseX, int mouseY, int& row, int& col);
    void initWindow();
    void closeWindow();
};

#endif
